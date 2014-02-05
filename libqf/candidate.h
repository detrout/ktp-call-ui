#ifndef QFS_CANDIDATE_H
#define QFS_CANDIDATE_H
#include "qf.h"

namespace QFs {
/** Wrapper for FsCandidate */
class QFS_EXPORT Candidate : public QGlib::Object
{
    QFS_WRAPPER(Candidate)
};
};

QFS_REGISTER_TYPE(QFs::Candidate) //codegen: GType=FS_TYPE_CANDIDATE
#endif
