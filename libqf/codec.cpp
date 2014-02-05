
QString Codec::name() const
{
    FsCodec *codec = object<FsCodec>();
    QString name(codec->encoding_name);
    return name;
}

QString Codec::toString() const
{
    gchar *gname = fs_codec_to_string(object<FsCodec>());
    QString name(static_cast<char *>(gname));
    g_free(gname);
    return name;
}
