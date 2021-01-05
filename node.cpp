#include "node.h"
#include "gate.h"

void line::delayedConstruction(node *n, uint sub)
{
    this->n=n;
    this->sub=sub;
}

bool line::getIsEvaling()
{
    if(isConst)
        return false;
    else
        return this->n->isEvaling;
}

bool line::get()
{
    if(isConst)
        return constVal;
    else
        return n->eval()[sub];
}

pos line::stru(QGraphicsScene* scene,uint tabNum,uint tabNum1)
{
    if(isConst)
    {
        int x=-400;
        int y=50;
        x=(qAbs(x)*tabNum)/3+x;
        y=(y*tabNum1*2)+y;
        pos posself(x,y); //根据传入的层级和一些其它的信息计算自己应该所在的坐标
        QGraphicsEllipseItem *Ellipse=new QGraphicsEllipseItem;
        Ellipse->setRect(x-25,y-25,50,50);
        scene->addItem(Ellipse);
        QGraphicsTextItem *text=new QGraphicsTextItem(QString::fromStdString(this->getName()));
        text->setFont(QFont("微软雅黑",10));
        text->setPos(x,y);
        scene->addItem(text);
        return posself;
    }
    else
       return n->stru(scene,tabNum,tabNum1);
}
