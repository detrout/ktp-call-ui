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

    QGst::ElementPtr getVideoSink();
    QGst::ElementPtr getVideoPreviewSink();

public Q_SLOTS:
    void setHoldEnabled(bool enable);
    void setSoundEnabled(bool enable);
    void setShowDialpadEnabled(bool enable);

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