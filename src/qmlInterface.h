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

public Q_SLOTS:
    void showPreviewVideo(bool show);
    QGst::ElementPtr getVideoSink();
    QGst::ElementPtr getVideoPreviewSink();

private:
    QGst::Ui::GraphicsVideoSurface *surfacePreview;
    QGst::Ui::GraphicsVideoSurface *surface;
};

#endif //QMLINTERFACE_H