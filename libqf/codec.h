#ifndef QFS_CODEC_H
#define QFS_CODEC_H
#include "qf.h"

namespace QFs {

/** Wrapper for FsCodec */
class QFS_EXPORT Codec : public QGlib::Object
{
    QFS_WRAPPER(Codec)

public:
    QString name() const;
    QString toString() const;
};

};

QFS_REGISTER_TYPE(QFs::Codec) //codegen: GType=FS_TYPE_CODEC
#endif
