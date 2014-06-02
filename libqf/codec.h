#ifndef QFS_CODEC_H
#define QFS_CODEC_H
#include "qf.h"
#include "enums.h"

namespace QFs {

/** Wrapper for FsCodec */
class QFS_EXPORT Codec : public QObject
{
public:
    Codec();
    Codec(int id, const char *encoding_name, QFs::MediaType media_type, quint32 clock_rate);
    ~Codec();

    QString name() const;
    QString toString() const;
private:
    class Private;
    Private *d;

};

class QFS_EXPORT CodecList : public QGlib::Object
{
    QFS_WRAPPER(CodecList)
};

};

QFS_REGISTER_TYPE(QFs::Codec) //codegen: GType=FS_TYPE_CODEC
QFS_REGISTER_TYPE(QFs::CodecList) // codegen: GType=FS_TYPE_CODEC_LIST
#endif
