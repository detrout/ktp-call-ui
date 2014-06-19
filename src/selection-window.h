/*
 *  Copyright 2014  Ekaitz Zárraga <ekaitzzarraga@gmail.com>
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H
#include <QMainWindow>
#include <QtGui>


#include <QtGui/QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QPixmap>
#include <QRubberBand>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>
#include <QSize>



class SelectionWindow : public QMainWindow
{
    Q_OBJECT
private:
    QRubberBand *rubberBand;
    QLabel *label;
    QPoint mypoint;
    QEventLoop loop;
    QRect shape;
    QGraphicsDropShadowEffect *shadowEffect;
public:
    SelectionWindow(QWidget *parent);
    virtual ~SelectionWindow();
    QRect getShape();
private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
Q_SIGNALS:
    void breakLoop(void);

    void returnRegion(QRect);
};

#endif // SELECTIONWINDOW_H
