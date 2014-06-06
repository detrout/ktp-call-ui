#include <cstdlib>
#include <QGst/ElementFactory>
#include <QGst/Ui/GraphicsVideoSurface>
#include <QGst/Init>

#include "qmlInterface.h"

QmlInterface::QmlInterface(QWidget* parent): QDeclarativeView(parent)
{
    surface = new QGst::Ui::GraphicsVideoSurface(this);
    rootContext()->setContextProperty(QLatin1String("videoSurface"), surface);

    surfacePreview = new QGst::Ui::GraphicsVideoSurface(this);
    rootContext()->setContextProperty(QLatin1String("videoPreviewSurface"), surfacePreview);

    setSource(QUrl::fromLocalFile("/home/kaditx/projects/qmlGui/Main.qml"));
    setResizeMode(QDeclarativeView::SizeRootObjectToView);

    setupSignals();
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
void QmlInterface::showVideo(bool show)
{
    QMetaObject::invokeMethod(rootObject(), "showVideo", Q_ARG(QVariant, show));
}
void QmlInterface::changeHoldIcon(QString icon)
{
    QMetaObject::invokeMethod(rootObject(), "changeHoldIcon", Q_ARG(QVariant, icon));
}

void QmlInterface::setupSignals()
{
    //GUI->logic
    connect(rootObject(), SIGNAL(hangupClicked()), this, SIGNAL(hangupClicked()));
    connect(rootObject(), SIGNAL(holdClicked()), this, SIGNAL(holdClicked()));
    connect(rootObject(), SIGNAL(soundClicked(bool)), this, SIGNAL(muteClicked(bool)));
    connect(rootObject(), SIGNAL(showMyVideoClicked(bool)), this, SIGNAL(showMyVideoClicked(bool)));
    connect(rootObject(), SIGNAL(showMyDialpadClicked(bool)), this, SIGNAL(showDialpadClicked(bool)));

    //logic->GUI
    connect(this, SIGNAL(soundChangeState(bool)),rootObject(), SIGNAL(soundChangeState(bool)));
    connect(this, SIGNAL(showMyVideoChangeState(bool)),rootObject(), SIGNAL(showMyVideoChangeState(bool)));
    connect(this, SIGNAL(showDialpadChangeState(bool)),rootObject(), SIGNAL(showDialpadChangeState(bool)));
}
