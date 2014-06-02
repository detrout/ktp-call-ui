#ifndef QFSTEST_H
#define QFSTEST_H
#include <QtTest/QtTest>
#include <QGlib/Value>
#include <QGst/Init>
#include <QGst/Element>
#include <QGst/Pipeline>

#include "../session.h"
#include "../qf.h"
#include "../enums.h"
#include "../conference.h"

class QFsTest : public QObject
{
    Q_OBJECT

public:
    void setup_simple_conference(int id, QString element, QString cname, QFs::MediaType mediatype);


protected:
    // data for simple conference
    int id;
    QString cname;

    QGst::PipelinePtr pipeline;
    QFs::ConferencePtr conference;
    QFs::SessionPtr session;
    QGst::ElementPtr fakesrc;

    bool started;
    // GList *streams;
    //end simple conference

private Q_SLOTS:
    void initTestCase() {
        QGst::init();
        QFs::init();
    }

    void cleanupTestCase() {
        QGst::cleanup();
        //QFs::cleanup();
    }
};

#endif
