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

    results.clear();
    position status;
    // Call algorithms
    // TODO: if ray or winding
    for(int i=0; i<pols.size(); i++){
        if (draw_what)
            status = Algorithms::windingAlgorithm(q, pols[i]);
        else
            status = Algorithms::rayAlgorithm(q, pols[i]);

        if (status == IN || status == ON)
            results.push_back(true);
        else
            results.push_back(false);
        qDebug() << "winding?: " << draw_what;
        qDebug() << "position: " << status;

    }



    ignoreDrawPols = true;
    repaint();

}

QPoint Draw::generatePoint()
{
    QPoint point(rand()%400,rand()%400);

    return point;
}

void Draw::generatePolygons(int n){
    TPolygon gen_points;
    for (int i=0;i<n;i++)
    {
        gen_points.push_back(generatePoint());
    }
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
    results.clear();
//    generatePolygons(10);

    QPointF p1(0,rand()%100);QPointF p2(100,100);QPointF p3(200,0);QPointF p4(100,50);
    pol.push_back(p1);
    pol.push_back(p2);
    pol.push_back(p3);
    pol.push_back(p4);
    pols.push_back(pol);

    pol.clear();
    p1.setX(200);p1.setY(100 + rand()%100);p2.setX(100);p2.setY(100);p3.setX(200);p3.setY(0);p4.setX(300);p4.setY(350);
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
        painter.drawPolygon(pols[i]);
    }

    //Set style for drawing results
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::Dense1Pattern);
    QPainterPath path;


    //Draw polygons marked by results
    for (int i=0;i<results.size();i++)
    {
        if (results[i] == true)
        {
            path.addPolygon(pols[i]);
            painter.drawPolygon(pols[i]);
            painter.fillPath(path, brush);
        }

    }

    painter.end();
    ignoreDrawPols=false;
}
