/*
 *  Copyright (C) 2014 Ekaitz Zárraga <ekaitz.zarraga@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <cstdlib>
#include <QGst/ElementFactory>
#include <QGst/Ui/GraphicsVideoSurface>
#include <QGst/Init>

#include "qml-interface.h"

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

void QmlInterface::setHoldEnabled(bool enable)
{
    QMetaObject::invokeMethod(rootObject(), "setHoldEnabled", Q_ARG(QVariant, enable));
}
void QmlInterface::setSoundEnabled(bool enable)
{
    QMetaObject::invokeMethod(rootObject(), "setSoundEnabled", Q_ARG(QVariant, enable));
}
void QmlInterface::setShowDialpadEnabled(bool enable)
{
    QMetaObject::invokeMethod(rootObject(), "setShowDialpadEnabled", Q_ARG(QVariant, enable));
}


void QmlInterface::setupSignals()
{
    //GUI->logic
    connect(rootObject(), SIGNAL(hangupClicked()), this, SIGNAL(hangupClicked()));
    connect(rootObject(), SIGNAL(holdClicked()), this, SIGNAL(holdClicked()));
    connect(rootObject(), SIGNAL(soundClicked(bool)), this, SIGNAL(muteClicked(bool)));
    connect(rootObject(), SIGNAL(showMyVideoClicked(bool)), this, SIGNAL(showMyVideoClicked(bool)));
    connect(rootObject(), SIGNAL(showDialpadClicked(bool)), this, SIGNAL(showDialpadClicked(bool)));
    connect(rootObject(), SIGNAL(exitFullScreen()), this, SIGNAL(exitFullScreen()));

    //logic->GUI
    connect(this, SIGNAL(soundChangeState(bool)),rootObject(), SIGNAL(soundChangeState(bool)));
    connect(this, SIGNAL(showMyVideoChangeState(bool)),rootObject(), SIGNAL(showMyVideoChangeState(bool)));
    connect(this, SIGNAL(showDialpadChangeState(bool)),rootObject(), SIGNAL(showDialpadChangeState(bool)));
}
