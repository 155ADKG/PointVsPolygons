#include "draw.h"

Draw::Draw(QWidget *parent) :
    QWidget(parent)
{
    //setCursor(Qt::CrossCursor);
}

void Draw::mousePressEvent(QMouseEvent *e)
{
    // Get current cursor cords to point q
    double x = e->pos().x();
    double y = e->pos().y();

qDebug()<< "x: "<< x<<"  y: "<<y;
    cursor.setX(x);
    cursor.setY(y);
    QPoint q(x,y);

    results.clear();
    position status;

    // Call algorithms
    for(int i=0; i<pols.size(); i++){
        if (draw_what)
            status = Algorithms::windingAlgorithm(q, pols[i]);
        else
            status = Algorithms::rayAlgorithm(q, pols[i]);

        if (status == IN || status == ON)
            results.push_back(true);
        else
            results.push_back(false);

    }



    ignoreDrawPols = true;
    repaint();

}

QPoint Draw::generatePoint()
{
    unsigned int ht = this->height();
    unsigned int wd = this->width();

    QPoint point(rand()%wd,rand()%ht);

    return point;
}



void Draw::generatePolygons(int n){

    //Generate points
    pols.clear();
    TPolygon gen_points;
    for (int i=0;i<n;i++)
    {
        gen_points.push_back(generatePoint());
    }

    //Calculate angles from first two points
    QMap<int, double> omegas;
    omegas.insert(0,0);
    for (int i=0;i<(n-2);i++)
    {
        if (Algorithms::getPointLinePosition(gen_points[0],gen_points[1],gen_points[i+2]) == 1)
            omegas.insert(i+1,-1.0*Algorithms::getTwoVectorsOrientation(gen_points[0],gen_points[1],gen_points[0],gen_points[i+2]));
        else
            omegas.insert(i+1,Algorithms::getTwoVectorsOrientation(gen_points[0],gen_points[1],gen_points[0],gen_points[i+2]));


    }

    //Sort angles
    QList<double> omg = omegas.values();
    qSort(omg.begin(),omg.end(),sortByXAsc());

    //Insert first point into polygon
    TPolygon big_pol;
    big_pol.push_back(gen_points[0]);


    //Insert sorted points into polygon
    for (int i=0;i<(n-1);i++)
    {
        for (int j=0;j<(n-1);j++)
        {
            if (omegas[j] == omg[i])
            {
               big_pol.push_back(gen_points[j+1]);

               //Close current polygon, add to pols
               if ((rand()%3 + 1) == 1 || i == n/2)
               {
                   pols.push_back(big_pol);

                   //Prepare polygon to next points
                   big_pol.clear();
                   big_pol.push_back(gen_points[0]);
                   big_pol.push_back(gen_points[j+1]);
               }

            }
        }

    }

}


void Draw::paintEvent(QPaintEvent *)
{
    const unsigned int r = 10;
    QPainter painter(this);
    painter.begin(this);

    // Draw current cursor
    painter.drawEllipse(cursor.x()-r/2, cursor.y()-r/2, r, r);

    if (!ignoreDrawPols){

        results.clear();

        if (push_gen){
            generatePolygons(rand()%50 + 10);
        }

        qDebug() << pols;


//    TPolygon pol1;
//    QPoint p1(1,1);
//    QPoint p2(101,1);
//    QPoint p3(101,101);
//    QPoint p4(1,101);
//    pol1.push_back(p1);
//    pol1.push_back(p2);
//    pol1.push_back(p3);
//    pol1.push_back(p4);

//    TPolygon pol2;
//    QPoint pp1(201,1);
//    QPoint pp2(101,1);
//    QPoint pp3(101,101);
//    QPoint pp4(201,101);
//    pol2.push_back(pp1);
//    pol2.push_back(pp2);
//    pol2.push_back(pp3);
//    pol2.push_back(pp4);

//    pols.push_back(pol1);
//    pols.push_back(pol2);

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
            painter.setPen(QPen(Qt::black, 2));
            path.addPolygon(pols[i]);
            painter.drawPolygon(pols[i]);
            painter.fillPath(path, brush);
        }

    }

    painter.end();
    ignoreDrawPols=false;
    push_gen=false;
}
