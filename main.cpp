#include <QCoreApplication>
#include "bluetoothscanner.h"
#include "logger.h"
#include <gst/gst.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //CBluetoothScanner* bluetoothScanner = CBluetoothScanner::GetInstance();

    //bluetoothScanner->StartScanning();
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;
  GError* err;
  gchar* txt;


  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Build the pipeline */
  pipeline = gst_parse_launch ("playbin location=/home/konrad/Dropbox/01_The_Trail.mp3", NULL);

  /* Start playing */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);
  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

  /* Free resources */
  if (msg != NULL)
  {
    gst_message_parse_error(msg, &err, &txt);
    LOG_CRITICAL("GStreamer error. Error source: %s, Error message: %s", GST_OBJECT_NAME(msg->src), err->message);
    gst_message_unref (msg);
  }

  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);

    return a.exec();
}
