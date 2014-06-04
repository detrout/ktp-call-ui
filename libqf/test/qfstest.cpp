#include "qfstest.h"
#include <QGst/Bus>
#include <QGst/ElementFactory>

void QFsTest::setup_simple_conference(int id, QString element, QString cname, QFs::MediaType mediatype)
{
    QGst::BusPtr bus;
    pipeline = QGst::Pipeline::create("pipeline");
    QVERIFY(pipeline);

    //bus = pipeline->bus();
    // set_sync_handler
    // unref bus

    conference = QGst::ElementFactory::make(element, NULL).dynamicCast<QFs::Conference>();
    QVERIFY(conference);
    QVERIFY(pipeline->add(conference));

    session = conference->new_session(mediatype);
    QVERIFY(session);
    //session->property("tos").set<int>(2);
    //QCOMPARE(2, session->property("tos").get<int>());
}
