#include <cstdlib>
#include <QGst/ElementFactory>
#include <QGst/Ui/GraphicsVideoSurface>
#include <QGst/Init>
#include "qmlInterface.h"

QmlInterface::QmlInterface(QWidget* parent): QDeclarativeView(parent)
{
    surface = new QGst::Ui::GraphicsVideoSurface(this);
    rootContext()->setContextProperty(QLatin1String("videoSurface"), surface);
    //player->setVideoSink(surface->videoSink());

    surfacePreview = new QGst::Ui::GraphicsVideoSurface(this);
    rootContext()->setContextProperty(QLatin1String("videoPreviewSurface"), surfacePreview);

    setSource(QUrl::fromLocalFile("/home/kaditx/projects/qmlGui/Main.qml"));
    setResizeMode(QDeclarativeView::SizeRootObjectToView);

}

void QmlInterface::setLabel(const QString name, const QString imageUrl)
{
    QMetaObject::invokeMethod(rootObject(), "setLabel", Q_ARG(QVariant, name), Q_ARG(QVariant, imageUrl));
}

QGst::ElementPtr QmlInterface::getVideoSink()
{
    return( surface->videoSink());
}

QGst::ElementPtr QmlInterface::getVideoPreviewSink()
{
    return surfacePreview->videoSink();
}

void QmlInterface::showPreviewVideo(bool show) //TODO click from actions and from app. :S
{
    QMetaObject::invokeMethod(rootObject(), "showPreviewVideo", Q_ARG(QVariant, show));
}
void QmlInterface::showVideo(bool show)
{
    QMetaObject::invokeMethod(rootObject(), "showVideo", Q_ARG(QVariant, show));
}
