#include <farstream/fs-codec.h>
#include "codec.h"

namespace QFs {
struct Codec::Private
{
    FsCodec *codec;

    Private() : codec(0) {};
};

Codec::Codec() :
   d(new Private)
{
}

Codec::Codec(int id, const char *encoding_name, MediaType media_type, quint32 clock_rate) :
   d(new Private())
{
    Q_ASSERT_X(d, "Codec", "Unable to create private storage");
    d->codec = fs_codec_new(id, encoding_name, static_cast<FsMediaType>(static_cast<int>(media_type)), clock_rate);
    Q_ASSERT_X(d->codec, "Codec", "Unable to create farstream codec");
}

Codec::~Codec()
{
    if (d && d->codec) {
        fs_codec_destroy(d->codec);
        d->codec = 0;
    }
}

QString Codec::name() const
{
    if (d->codec) {
        QString name(d->codec->encoding_name);
        return name;
    } else {
        return QString();
    }
}

QString Codec::toString() const
{
    gchar *gname = fs_codec_to_string(d->codec);
    QString name(static_cast<char *>(gname));
    g_free(gname);
    return name;
}
};
