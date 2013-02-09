#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QString>
#include <gphoto2/gphoto2-camera.h>

class MCamera : public QObject
{
    Q_OBJECT
public:
    enum Error{
        NoError,
        InitialisationError,
        CaptureError,
        GetFileError
    };

    explicit MCamera(QObject *parent = 0);
    virtual ~MCamera();

    QString lastFileName(){return m_filename;}
    
    Error initialisation();
signals:
    void photoCaptured();
public slots:
    Error capture(QString fileName);
private:
    Camera *m_camera;
    GPContext *m_context;
    QString m_filename;
};

#endif // CAMERA_H
