#include "gstreameraudio.h"

/// Mapping of the player's states to the strings for debug purpose
std::map<CGstreamerAudioDevice::PlayerState, std::string> CGstreamerAudioDevice::s_statesNames =
{
    {   CGstreamerAudioDevice::PlayerState::E_NOT_INITIALIZED, "E_NOT_INITIALIZED"},
    {   CGstreamerAudioDevice::PlayerState::E_STOPPED, "E_STOPPED"},
    {   CGstreamerAudioDevice::PlayerState::E_PLAYING, "E_PLAYING"},
    {   CGstreamerAudioDevice::PlayerState::E_PAUSED, "E_PAUSED"},
    {   CGstreamerAudioDevice::PlayerState::E_ERROR, "E_ERROR"}
};

CGstreamerAudioDevice::CGstreamerAudioDevice() :
    m_currentState(PlayerState::E_NOT_INITIALIZED),
    m_pPipeline(nullptr),
    m_pMessageBus(nullptr),
    m_pSource(nullptr),
    m_pMp3Decoder(nullptr),
    m_pAudioConverter(nullptr),
    m_pSink(nullptr)
{
    gst_init(nullptr, nullptr);

    m_CreatePipeline();

    m_pThread = new QThread();

    connect(this, SIGNAL(destroyed(QObject*)), m_pThread, SLOT(deleteLater()));
    this->moveToThread(m_pThread);

    m_pThread->start();
}

CGstreamerAudioDevice::~CGstreamerAudioDevice()
{
    m_ClearPipeline();
}


CGstreamerAudioDevice* CGstreamerAudioDevice::GetInstance()
{
    static CGstreamerAudioDevice s_instance;

    return &s_instance;
}

void CGstreamerAudioDevice::SetAudioFileToPlayout(std::__cxx11::string filePath)
{
    LOG_DBG("Opening the file: %s", filePath);

    if(!m_pSource)
    {
        LOG_CRITICAL("No source element yet created");
        return;
    }

    m_currentFileName = filePath;

    /// Notify the location of the file to the source element
    g_object_set(m_pSource, "location", filePath.c_str(), NULL);

    m_currentState = PlayerState::E_STOPPED;
}

GstElement* CGstreamerAudioDevice::AddPipelineElementInOrder(const char* elemFactoryName, const char* elemName)
{
    if(!m_pPipeline)
    {
        LOG_FATAL("Pipeline not created!!! Pipeline: %p", m_pPipeline);
        return nullptr;
    }

    GstElement* elem = gst_element_factory_make(elemFactoryName, elemName);

    if(!elem)
    {
        LOG_CRITICAL("Could not create element name: %s, of given type: %s", elemName, elemFactoryName);
        return nullptr;
    }

    if(!gst_bin_add(GST_BIN(m_pPipeline), elem))
    {
        LOG_CRITICAL("Could not add element (name: %s, factoryName: %s) to the bin", elemName, elemFactoryName);
        return nullptr;
    }

    /// If not the first element
    if(!m_pipelineElementList.empty())
    {
        /// Link the previous element with the current one
        GstElement* prevElem = m_pipelineElementList[m_pipelineElementList.size()-1];
        gchar* prevName = gst_element_get_name(prevElem);

        LOG_DBG("Linking previus element: %s to current one: %s", prevName, elemName);

        if(!gst_element_link(prevElem, elem))
        {
            LOG_CRITICAL("Error while linking elements!!! Source: %s, Destination: %s", prevName, elemName);
            g_free(prevName);
            return nullptr;
        }

        g_free(prevName);
    }

    m_pipelineElementList.append(elem);
    return elem;
}

void CGstreamerAudioDevice::StartPlaying()
{
    LOG_DBG("Current state: %s", s_statesNames[m_currentState]);

    if( m_currentState == PlayerState::E_STOPPED ||
        m_currentState == PlayerState::E_PAUSED)
    {
        if(gst_element_set_state(m_pPipeline, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE)
        {
            LOG_CRITICAL("Cannot set the player in playing state.");
        }

        /// Block until end of stream or error occurs
        GstMessage* msg = gst_bus_timed_pop_filtered(m_pMessageBus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
        ParseMessage(msg);
    }
    else
    {
        LOG_WARNING("Not in STOPPED or PAUSED state. Doing nothing");
    }

    return;
}

void CGstreamerAudioDevice::StartPlaying(std::__cxx11::string fileName)
{
    SetAudioFileToPlayout(fileName);

    StartPlaying();
}

void CGstreamerAudioDevice::ParseMessage(GstMessage *msg)
{
    switch(GST_MESSAGE_TYPE(msg))
    {
    case GST_MESSAGE_EOS:
        LOG_DBG("End of stream. Going to state stopped...");

        m_currentState = PlayerState::E_STOPPED;
        m_currentFileName = "";

        break;

    case GST_MESSAGE_ERROR:
        GError* e;
        gchar* debug_info;
        gst_message_parse_error(msg, &e, &debug_info);
        LOG_CRITICAL("Error received during playout of: %s. ERROR MESSAGE: \n%s", GST_ELEMENT_NAME(msg->src), e->message );
        if(debug_info)
        {
            LOG_DBG("Additional debug info: %s", debug_info);
        }
        g_clear_error(&e);
        g_free(debug_info);
        break;

    default:
        break;
    }

    gst_element_set_state(m_pPipeline, GST_STATE_NULL);
    gst_message_unref(msg);
}

void CGstreamerAudioDevice::onAudioSamplesReceived()
{

}

bool CGstreamerAudioDevice::m_CreatePipeline()
{
    LOG_DBG("Creating a pipeline");
    m_pPipeline = gst_pipeline_new("Audio pipeline");

    if(m_pPipeline == nullptr)
    {
        LOG_FATAL("Could not create pipeline holder. Aborting process...");
        m_ClearPipeline();
        return false;
    }

    m_pMessageBus = gst_pipeline_get_bus((GstPipeline*)m_pPipeline);
    if(!m_pMessageBus)
    {
        LOG_FATAL("Could not create pipeline's message bus");
        m_ClearPipeline();
        return false;
    }

    m_pSource = AddPipelineElementInOrder("filesrc", "Audio source");
    m_pMp3Decoder = AddPipelineElementInOrder("mad", "MP3 decoder");
    m_pAudioConverter = AddPipelineElementInOrder("audioconverter", "Audio converter");
    m_pSink = AddPipelineElementInOrder("alsasink" , "Audio sink");

    if(!(m_pSource && m_pMp3Decoder && m_pAudioConverter && m_pSink))
    {
        m_ClearPipeline();
        return false;
    }

    return true;
}

void CGstreamerAudioDevice::m_ClearPipeline()
{
    LOG_DBG("Dumping pipeline. Freeing its resources");
    if(m_pMessageBus)
    {
        gst_object_unref(m_pMessageBus);
        m_pMessageBus = nullptr;
    }

    if(m_pPipeline)
    {
        gst_element_set_state(m_pPipeline, GST_STATE_NULL);
        gst_object_unref(m_pPipeline);
        m_pPipeline = nullptr;
    }

    m_pipelineElementList.clear();

    m_currentFileName = "";

    m_currentState = PlayerState::E_NOT_INITIALIZED;
}
