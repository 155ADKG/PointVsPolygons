#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <QtGui>

typedef QVector<QPointF> TPolygon;

enum position
{
    IN   =  1,
    OUT  =  0,
    ON   = -1
};

class Algorithms
{
    public:
        static position rayAlgorithm(const QPointF &q, TPolygon P);

        static int getPointLinePosition(const QPointF &p, const QPointF &p1, const QPointF &p2);

        static double getTwoVectorsOrientation(const QPointF &p1, const QPointF &p2, const QPointF &p3, const QPointF &p4);

        static position windingAlgorithm(const QPointF &q, TPolygon P);
    Algorithms();
};

#endif // ALGORITHMS_H
