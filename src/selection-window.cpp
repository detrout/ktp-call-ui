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

#include "selection-window.h"

struct SelectionWindow::Private
{
    QRubberBand *rubberBand;
    QLabel *label;
    QPoint mypoint;
    QEventLoop loop;
    QRect shape;
    QGraphicsDropShadowEffect *shadowEffect;
};

/*! Makes a semi-transparent window in full screen, and allows selection with the \a rubberBand
 */
SelectionWindow::SelectionWindow(QWidget *parent=0): QMainWindow(parent), d(new Private)
{
    setWindowFlags(Qt::Window);
    QWidget::setAttribute( Qt::WA_TranslucentBackground, true);
    connect(this, SIGNAL(breakLoop()), &d->loop, SLOT(quit()));

    d->label=new QLabel(this);
    d->label->setStyleSheet("background-color: rgba(0, 0, 20, 30);");
    d->label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    d->label->setTextFormat(Qt::RichText);
    d->label->setText("<h1 align=center>Click and drag to select</h1><h2 align=center><strong>Press Return to Accept or Esc to select full screen</strong></h2>");
    setCentralWidget(d->label);

    d->shape.setCoords(0,0,0,0);

    d->shadowEffect = new QGraphicsDropShadowEffect(this);
    d->shadowEffect->setBlurRadius(10.0);
    d->shadowEffect->setColor(palette().color(QPalette::HighlightedText));
    d->shadowEffect->setOffset(0.0);
    setGraphicsEffect(d->shadowEffect);

    d->rubberBand = new QRubberBand(QRubberBand::Rectangle, this);//new rectangle band


}

//! \return size and position of the selected region
QRect SelectionWindow::getShape()
{
    showFullScreen();
    d->loop.exec();
    return(d->shape);
}

//! Start the \a rubberBand when click
void SelectionWindow::mousePressEvent(QMouseEvent *event)
{
    d->mypoint = event->pos();
    d->rubberBand->setGeometry(QRect(d->mypoint, QSize()));
    d->rubberBand->show();
}

//! Change the size of the \a rubberBand when drag
void SelectionWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()!=Qt::NoButton){
        d->rubberBand->setGeometry(QRect(d->mypoint, event->pos()).normalized());//Area Bounding
    }
}

//! Set size of the \a rubberBand when release the mouse
void SelectionWindow::mouseReleaseEvent(QMouseEvent *event)
{
    d->rubberBand->setGeometry(QRect(d->mypoint, event->pos()).normalized());//Area Bounding
}

//! Press \a return to accept and \a escape to select full-screen
void SelectionWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            d->shape.setSize(size());
            Q_EMIT(breakLoop());
            break;
        case Qt::Key_Return:
            d->shape.setTopLeft(d->rubberBand->pos());
            d->shape.setSize(d->rubberBand->size());
            Q_EMIT(breakLoop());
            break;
    }
    QMainWindow::keyPressEvent(event);
}
SelectionWindow::~SelectionWindow()
{
    delete d;
}

