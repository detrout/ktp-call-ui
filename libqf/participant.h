#ifndef QFS_PARTICIPANT_H
#define QFS_PARTICIPANT_H
#include "qf.h"

namespace QFs {
/** Wrapper for  FsParticipant */
class QFS_EXPORT Participant : public QGlib::Object
{
    QFS_WRAPPER(Participant)
};
};

QFS_REGISTER_TYPE(QFs::Participant) //codegen: GType=FS_TYPE_PARTICIPANT
#endif
