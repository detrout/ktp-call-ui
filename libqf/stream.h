#ifndef QFS_STREAM_H
#define QFS_STREAM_H
#include "qf.h"

namespace QFs {
/** Wrapper for FsStream */
class QFS_EXPORT Stream : public QGlib::Object
{
    QFS_WRAPPER(Stream)
};
};

QFS_REGISTER_TYPE(QFs::Stream) //codegen: GType=FS_TYPE_STREAM
#endif
