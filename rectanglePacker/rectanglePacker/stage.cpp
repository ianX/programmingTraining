#include "stage.h"
#include "ui_stage.h"

#include <iostream>
using namespace std;

Stage::Stage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stage),
    pen(Qt::SolidLine),
    brush(Qt::green)
{
    ui->setupUi(this);
}

Stage::~Stage()
{
    delete ui;
}

void Stage::updateStage(Layout &layout)
{
    //m = mwin;
    pair<float,float> fp = layout.compBorder();
    vector<Rect> r = layout.getRects();
    rects.clear();
    rects.insert(rects.end(),r.begin(),r.end());
    x = fp.first;
    y = fp.second;
    std::cout<< "update :"<<layout.compArea()<<std::endl;
    this->repaint();
}

void Stage::paintEvent(QPaintEvent *ev)
{

    QPainter painter(this);
    QSize s = size();
    qreal sx = 0.9 * s.width()/x;
    qreal sy = 0.9 * s.height()/y;
    ss = sx > sy ? sy:sx;
    painter.scale(ss,ss);
    std::cout<<"paint, w:"<<s.width()<<" h:"<<s.height()<<" ss:"<<ss<<" x:"<<ss*x<<" y:"<<ss*y<<std::endl;
    painter.translate((s.width()/ss-x)/2,(s.height()/ss - y)/2);
    painter.setPen(pen);
    painter.setBrush(brush);
    for(int i=0 ; i < rects.size() ; ++i)
    {
        Rect r = rects[i];
        QRect rect(r.lb.x,r.lb.y,r.width,r.height);
        painter.drawRect(rect);
    }
}

QPoint Stage::transformXY(float xx, float yy)
{
    QSize s = size();
    return QPoint(xx/ss - (s.width()/ss-x)/2,
                  yy/ss - (s.height()/ss-y)/2);
}

void Stage::mouseReleaseEvent(QMouseEvent *e)
{
    QPoint p = transformXY(e->x(),e->y());
    int lx = p.x();
    int ly = p.y();
    if(e->button() == Qt::RightButton)
    {
        int rm = -1;
        for(int i = 0;i<rects.size();++i)
        {
            Rect r = rects[i];
            if(r.lb.x<lx && r.lb.x+r.width > lx && r.lb.y < ly && r.lb.y+r.height > ly)
            {
                rm = i;
                break;
            }
        }
        if(rm == -1)
            return;
        emit removeRect(rm);
    }
    else if(e->button() == Qt::LeftButton)
    {

    }
}

void Stage::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        QPoint p = transformXY(e->x(),e->y());
    }
}

void Stage::mouseMoveEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        QPoint p = transformXY(e->x(),e->y());
    }
}
