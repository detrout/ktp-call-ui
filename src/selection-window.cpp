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

SelectionWindow::SelectionWindow(QWidget *parent=0): QMainWindow(parent)
{
    setWindowFlags(Qt::Window);
    QWidget::setAttribute( Qt::WA_TranslucentBackground, true);
    connect(this, SIGNAL(breakLoop()), &loop, SLOT(quit()));

    label=new QLabel(this);
    label->setStyleSheet("background-color: rgba(0, 0, 20, 30);");
    label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    label->setTextFormat(Qt::RichText);
    label->setText("<h1 align=center>Click and drag to select</h1><h2 align=center><strong>Press Return to Accept or Esc to select full screen</strong></h2>");
    setCentralWidget(label);

    shape.setCoords(0,0,0,0);

    shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10.0);
    shadowEffect->setColor(palette().color(QPalette::HighlightedText));
    shadowEffect->setOffset(0.0);
    setGraphicsEffect(shadowEffect);

    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);//new rectangle band


}
QRect SelectionWindow::getShape()
{
    showFullScreen();
    loop.exec();
    return(shape);
}
void SelectionWindow::mousePressEvent(QMouseEvent *event)
{
    mypoint = event->pos();
    rubberBand->setGeometry(QRect(mypoint, QSize()));
    rubberBand->show();
}

void SelectionWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()!=Qt::NoButton){
        rubberBand->setGeometry(QRect(mypoint, event->pos()).normalized());//Area Bounding
    }
}

void SelectionWindow::mouseReleaseEvent(QMouseEvent *event)
{
    rubberBand->setGeometry(QRect(mypoint, event->pos()).normalized());//Area Bounding
}

void SelectionWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    //TODO SELECT A WINDOW
}

void SelectionWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            shape.setSize(size());
            Q_EMIT(breakLoop());
            break;
        case Qt::Key_Return:
            shape.setTopLeft(rubberBand->pos());
            shape.setSize(rubberBand->size());
            Q_EMIT(breakLoop());
            break;
    }
    QMainWindow::keyPressEvent(event);
}
SelectionWindow::~SelectionWindow()
{
}

