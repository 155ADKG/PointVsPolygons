#include "algorithms.h"



int Algorithms::getPointLinePosition(const QPointF &p, const QPointF &p1, const QPointF &p2)
{
    //Vector u = p2-p1 and v = p2-p
    const double ux = p2.x() - p1.x();
    const double uy = p2.y() - p1.y();
    const double vx = p.x() - p1.x();
    const double vy = p.y() - p1.y();

    //Test criterion
    const double t = ux*vy - vx*uy;

    //P is in the left halfplpane
    if (t<0)
        return 1;

    //P is in the right halfplpane
    if (t>0)
        return 0;

    //P is on the edge
    return -1;
}

double Algorithms::getTwoVectorsOrientation(const QPointF &p1, const QPointF &p2, const QPointF &p3, const QPointF &p4)
{
    //Vector u = p2-p1 and v = p4-p3
    const double ux = p2.x() - p1.x();
    const double uy = p2.y() - p1.y();
    const double vx = p4.x() - p3.x();
    const double vy = p4.y() - p3.y();

    const double pi =2.0*asin(1.0);
    return acos((ux*vx + uy*vy)/(sqrt(ux*ux+uy*uy)*sqrt(vx*vx+vy*vy)))*(180/pi);

}

position Algorithms::rayAlgorithm(const QPointF &q, TPolygon P)
{
    unsigned int n_intersections = 0;
    unsigned int n = P.size();

    //Get first point, add to the polygon
    QPointF point = P[0];
    P.push_back(point);

    //Process all segments
    for (unsigned int i=0; i<n; i++){

        //Get segment points
        QPointF pi = P[i];
        QPointF pii = P[i+1];

        //Get reduced coordinates
        double xi = pi.x() - q.x();
        double yi = pi.y() - q.y();
        double xii = pii.x() - q.x();
        double yii = pii.y() - q.y();

        if (((xi>0) && (xii<=0)) || ((xi<0) && (xii>=0))){

            //Intersection
            double y = (xii*yi-xi*yii)/(xii-xi);
            if (fabs(y)<1.0e-10)
                return ON;

        }

        //Test if segment intersect the ray
        if (((yi>0) && (yii<=0)) || ((yi<0) && (yii>=0))){

            //Intersection
            double x = (xi*yii-xii*yi)/(yii-yi);

            //Intersection exists
            if (fabs(x)<1.0e-10)
                return ON;
            if (x>0)
                n_intersections++;

        }

    }

    //q inside P
    if (n_intersections%2)
        return IN;

    //q outside P
    else
        return OUT;


}

position Algorithms::windingAlgorithm(const QPointF &q, TPolygon P)
{

    unsigned int n = P.size();

    //get first point, add to the polygon
    QPointF point = P[0];
    P.push_back(point);

    double sum = 0;

    //process all segments
    for (unsigned int i=0; i<n; i++){

        //Get angle between u,v
        double omega = getTwoVectorsOrientation(q, P[i], q, P[i+1]);

        //Get position of q according to Pi, Pi+1
        int pos = getPointLinePosition(q, P[i], P[i+1]);

        //q is on left halfplane
        if (pos > 0)
            sum += omega;

        //q is on right halfplane
        else if (pos == 0)
            sum -= omega;

    }

    //Return
    const double epsilon = 1.0e-5;
    if (fabs(sum) < epsilon)
        return OUT;
    if (fabs((fabs(sum)-360)) < epsilon)
        return IN;
    else
        return ON;

}

