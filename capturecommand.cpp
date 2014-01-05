#include "capturecommand.h"

CaptureCommand::CaptureCommand(MCamera* camera, Message* message, QObject *parent):
    Command(camera, message, parent)
{
}


bool CaptureCommand::execute()
{
    switch(m_camera->capture("One_shot"))
    {
    case MCamera::NoError:
        return true;

    case MCamera::InitialisationError:
    case MCamera::CaptureError:
    case MCamera::GetFileError:
        return false;

    }
    return false;
}
