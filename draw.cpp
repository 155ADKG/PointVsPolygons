#include "draw.h"

Draw::Draw(QWidget *parent) :
    QWidget(parent)
{
}

void Draw::mousePressEvent(QMouseEvent *e)
{
    // Get current cursor cords to point q
    double x = e->pos().x();
    double y = e->pos().y();


    cursor.setX(x);
    cursor.setY(y);
    QPointF q(x,y);

    // Call algorithms
    // TODO: if ray or winding
    for(int i=0; i<pols.size(); i++){
        position status = Algorithms::rayAlgorithm(q, pols[i]);
        qDebug() << "position: " << status;
        qDebug() << "winding?: " << draw_what;
    }



    ignoreDrawPols = true;
    repaint();

}


void Draw::paintEvent(QPaintEvent *e)
{
    const unsigned int r = 10;
    QPainter painter(this);
    painter.begin(this);

    // Draw current cursor
    painter.drawEllipse(cursor.x()-r/2, cursor.y()-r/2, r, r);

    if (!ignoreDrawPols){
    pol.clear();
    pols.clear();
    QPointF p1(0,rand()%100);QPointF p2(100,100);QPointF p3(200,0);QPointF p4(100,50);
    pol.push_back(p1);
    pol.push_back(p2);
    pol.push_back(p3);
    pol.push_back(p4);
    pols.push_back(pol);
}

    const unsigned n = pols.size();

    // Draw base polygons
    for (unsigned int i=0; i<n; i++)
    {
        const unsigned int m = pols[i].size();
        for (unsigned int j=0; j<m; j++)
        {
            painter.drawPolygon(pols[i]);
        }
    }

    painter.end();
    ignoreDrawPols=false;
}
