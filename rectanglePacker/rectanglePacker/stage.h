#ifndef STAGE_H
#define STAGE_H

#include <QWidget>

#include <QPainter>
#include <QRect>
#include <QPen>
#include <QBrush>

#include "SP/Layout.h"
#include "SP/Rect.h"
#include "mainwindow.h"

#include "vector"
#include <QMouseEvent>
#include <QPaintEvent>
using namespace RECTPACKING;

namespace Ui {
class Stage;
}

class Stage : public QWidget
{
    Q_OBJECT
    
public:
    explicit Stage(QWidget *parent = 0);
    ~Stage();
    void paintEvent(QPaintEvent *ev);
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    
public slots:
    void updateStage(Layout &layout);

signals:
    void removeRect(int);
private:
    QPoint transformXY(float xx , float yy);

    Ui::Stage *ui;
    MainWindow *m;

    std::vector<Rect> rects;
    float x;
    float y;
    float ss;

    QPen pen;
    QBrush brush;
};

#endif // STAGE_H
