#ifndef GSTREAMERAUDIO_H
#define GSTREAMERAUDIO_H

#include <QObject>
#include <QThread>
#include <QList>
#include <logger.h>
#include <gst/gst.h>

class CGstreamerAudioDevice : public QObject
{
    Q_OBJECT

public:

    enum class PlayerState : char
    {
        E_NOT_INITIALIZED,
        E_STOPPED,
        E_PLAYING,
        E_PAUSED,
        E_ERROR
    };

    static CGstreamerAudioDevice* GetInstance();

    ~CGstreamerAudioDevice();

    void SetAudioFileToPlayout(std::string filePath);

    void StartPlaying();

    void StartPlaying(std::string filePath);

    void ParseMessage(GstMessage* msg);

    GstElement* AddPipelineElementInOrder(const char *elemFactoryName, const char *elemName);

    void ClearPipeline();


public slots:

    void onAudioSamplesReceived();


signals:

    void ErrorReceivedSignal();

private:
    CGstreamerAudioDevice();

    PlayerState m_currentState;

    /// File name of the currently set file
    std::string m_currentFileName;

    /// Pipeline connecting all the elements in audio route
    GstElement* m_pPipeline;

    /// Bus on which errors and other messages will be captured
    GstBus* m_pMessageBus;

    QList<GstElement*> m_pipelineElementList;

    GstElement* m_pSource;

    GstElement* m_pMp3Decoder;

    GstElement* m_pAudioConverter;

    GstElement* m_pSink;

    QThread* m_pThread;

    bool m_CreatePipeline();

    void m_ClearPipeline();

    static std::map<PlayerState, std::string> s_statesNames;
};

#endif // GSTREAMERAUDIO_H
