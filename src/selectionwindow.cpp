// http://stackoverflow.com/questions/19066804/implementing-resize-handles-on-qrubberband-is-qsizegrip-relevant

#include <QX11Info>
#include "selectionwindow.h"

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
    //SELECT A WINDOW
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

