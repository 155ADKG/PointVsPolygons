#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <QtGui>

typedef QVector<QPoint> TPolygon;

enum position
{
    IN   =  1,
    OUT  =  0,
    ON   = -1
};

class Algorithms
{
    public:
        static position rayAlgorithm(const QPoint &q, TPolygon P);

        static int getPointLinePosition(const QPoint &p, const QPoint &p1, const QPoint &p2);

        static double getTwoVectorsOrientation(const QPoint &p1, const QPoint &p2, const QPoint &p3, const QPoint &p4);

        static position windingAlgorithm(const QPoint &q, TPolygon P);
    Algorithms();
};

#endif // ALGORITHMS_H
