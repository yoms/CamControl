#include "mcamera.h"
#include <QDebug>
#include <fcntl.h>

MCamera::MCamera(QObject *parent) :
    QObject(parent)
{
}
MCamera::Error MCamera::initialisation()
{
    gp_camera_new (&m_camera);
    m_context = gp_context_new();
    // set callbacks for camera messages
    gp_context_set_error_func(m_context, [](GPContext */*context*/, const char *format, va_list args, void */*data*/) {
        QString error;
        error.vsprintf(format, args);
        qDebug() << error;
    }, NULL);

    gp_context_set_message_func(m_context, [](GPContext */*context*/, const char *format, va_list args, void */*data*/) {
        QString message;
        message.vsprintf(format, args);
        qDebug() << message;
    }, NULL);

    int ret = gp_camera_init(m_camera, m_context);
    if (ret < GP_OK) {
        qDebug() << "No camera auto detected.\n";
        gp_camera_free(m_camera);
        return InitialisationError;
    }
    return NoError;
}

MCamera::Error MCamera::capture(QString fileName)
{
    m_filename = fileName;
    int retval;
    CameraFilePath camera_file_path;


    retval = gp_camera_capture(m_camera, GP_CAPTURE_IMAGE, &camera_file_path, m_context);

    if (retval) {
        qDebug() << "Error on capture\n";
        return CaptureError;
    }
    int waittime = 2000;
    CameraEventType type;
    void *data;

    while(1) {
        retval = gp_camera_wait_for_event(m_camera, waittime, &type, &data, m_context);
        if(type == GP_EVENT_TIMEOUT) {
            break;
        }
        else if (type == GP_EVENT_CAPTURE_COMPLETE) {
            qDebug() << "Capture completed\n";
            waittime = 100;
        }
        else if (type != GP_EVENT_UNKNOWN) {
            qDebug() << QString("Unexpected event received from camera: %d\n").arg((int)type);
        }
    }
    emit photoCaptured();
    return NoError;
}
MCamera::~MCamera()
{
    // close camera
    gp_camera_unref(m_camera);
    gp_context_unref(m_context);
}
