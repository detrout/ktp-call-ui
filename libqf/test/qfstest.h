#ifndef QFSTEST_H
#define QFSTEST_H
#include <QtTest/QtTest>
#include <QGlib/Value>
#include <QGst/Init>

#include "../qf.h"

class QFsTest : public QObject
{
    Q_OBJECT
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
