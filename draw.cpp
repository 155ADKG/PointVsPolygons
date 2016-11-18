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
    // TODO: if ray or windingreturn
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
    QMap<int, double> omegas;
    omegas.insert(0,0);
    for (int i=0;i<(n-2);i++)
    {
        if (Algorithms::getPointLinePosition(gen_points[0],gen_points[1],gen_points[i+2]) == 1)
            omegas.insert(i+1,-1.0*Algorithms::getTwoVectorsOrientation(gen_points[0],gen_points[1],gen_points[0],gen_points[i+2]));
        else
            omegas.insert(i+1,Algorithms::getTwoVectorsOrientation(gen_points[0],gen_points[1],gen_points[0],gen_points[i+2]));


    }

    QList<double> omg = omegas.values();
    qSort(omg.begin(),omg.end(),sortByXAsc());
    TPolygon big_pol;
    big_pol.push_back(gen_points[0]);

    for (int i=0;i<(n-1);i++)
    {
        for (int j=0;j<(n-1);j++)
        {
            if (omegas[j] == omg[i])
            {
               big_pol.push_back(gen_points[j+1]);

            }
        }

    }


    pol = big_pol;
    pols.push_back(pol);

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
    generatePolygons(30);


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
