#include "qfstest.h"

#include "../session.h"
#include "../conference.h"
#include "../codec.h"
#include "../enums.h"

#include "qfstest.h"

//#include <farstream/fs-conference.h>
#include <farstream/fs-codec.h>

class CodecTest : public QFsTest
{
    Q_OBJECT
private Q_SLOTS:
    void createEmptyCodecTest();
    void getCodecWithoutConfigList();
};

void CodecTest::createEmptyCodecTest()
{
    QFs::Codec c(0, "Null", QFs::MediaType::MediaTypeAudio, 8000);

    setup_simple_conference(1, "fsrtpconference", "alice@127.0.0.1", QFs::MediaTypeAudio);
    QVERIFY(session);
}

void CodecTest::getCodecWithoutConfigList()
{

    // get codecs farstream way
    GList *codec_list1;
    g_object_get(session, "codecs-without-config", &codec_list1, NULL);
    QVERIFY(codec_list1);

    GList *codec_list2;
    g_object_get(session, "codecs-without-config", &codec_list2, NULL);
    QVERIFY(codec_list2);

    QVERIFY(fs_codec_list_are_equal(codec_list1, codec_list2));

    // get codecs QFs way
    QGlib::Value codec_value = session->property("codecs-without-config");
    QVERIFY(codec_value.isValid());

    // Did we actually get a valid GList *?
    GList *codec_value_ptr = static_cast<GList *>(codec_value.get<gpointer>());
    QVERIFY(codec_value_ptr);

    // now try to extract the pointer into our wrapper class
    QFs::CodecListPtr codec_value_list = codec_value.get<QFs::CodecListPtr>();

    // need some way of converting QFs::CodecListPtr to a GList * for this to work
    // QVERIFY(fs_codec_list_are_equal(codec_list1, codec_value_list));

    // Cleanup gobject pointers
    fs_codec_list_destroy(codec_list1);
    fs_codec_list_destroy(codec_list2);

}

QTEST_APPLESS_MAIN(CodecTest)
#include "moc_qfstest.cpp"
#include "codectest.moc"
