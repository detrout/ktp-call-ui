#include "qfstest.h"

#include "../session.h"
#include "../conference.h"
#include "../codec.h"
#include "../enums.h"

#include <farstream/fs-conference.h>
#include <farstream/fs-session.h>
#include <QGst/Bin>
#include <QGst/ElementFactory>

#include "qfstest.h"

class SessionTest : public QFsTest
{
    Q_OBJECT
private Q_SLOTS:
    void valueTest();
};

void SessionTest::valueTest()
{
    QGst::ElementPtr element = QGst::ElementFactory::make("fsrtpconference");
    QVERIFY(!element.isNull());
    QFs::ConferencePtr conference = element.dynamicCast<QFs::Conference>();
    QVERIFY(!conference.isNull());
    QFs::SessionPtr session = conference->new_session(QFs::MediaType::MediaTypeAudio);
    QVERIFY(!session.isNull());
    QGlib::Value conference_value = session->property("conference");
    QFs::ConferencePtr c2 = conference_value.get<QFs::ConferencePtr>();
    QCOMPARE(c2, conference);
    QVERIFY(!c2.isNull());
    //QFs::CodecPtr codec = session->property("current-send-codec").get<QFs::CodecPtr>();
    //QVERIFY(!codec.isNull());
    GList *codecs = 0;
    GList *codec = 0;
    g_object_get(session, "codecs-without-config", &codecs, NULL);
    for (codec = codecs; codec->next != NULL; codec = codec->next) {
        qDebug() << "Codec: " << (static_cast<FsCodec *>(codec->data))->encoding_name;
    }
    g_list_free(codecs);
}
QTEST_APPLESS_MAIN(SessionTest)
#include "moc_qfstest.cpp"
#include "sessiontest.moc"
