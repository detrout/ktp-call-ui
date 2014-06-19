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
