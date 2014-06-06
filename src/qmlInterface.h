#include <cstdlib>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QGraphicsObject>
#include <QGst/ElementFactory>
#include <QGst/Ui/GraphicsVideoSurface>
#include <QGst/Init>

#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

class QmlInterface: public QDeclarativeView{


    Q_OBJECT

public:
    QmlInterface(QWidget* parent = 0);

    void setLabel(const QString name, const QString imageUrl);
    void showVideo(bool show);
    void changeHoldIcon(QString icon);

public Q_SLOTS:
    QGst::ElementPtr getVideoSink();
    QGst::ElementPtr getVideoPreviewSink();

Q_SIGNALS:
    //to outside
    void hangupClicked();
    void holdClicked();
    void muteClicked(bool toggled);
    void showMyVideoClicked(bool toggled);
    void showDialpadClicked(bool toggled);

    //to inside
    void soundChangeState(bool toggled);
    void showMyVideoChangeState(bool toggled);
    void showDialpadChangeState(bool toggled);

private:
    void setupSignals();
    QGst::Ui::GraphicsVideoSurface *surfacePreview;
    QGst::Ui::GraphicsVideoSurface *surface;

};

#endif //QMLINTERFACE_H