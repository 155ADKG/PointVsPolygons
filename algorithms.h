#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <QtGui>

typedef QVector<QPointF> TPolygon;

class Algorithms
{
    public:
        static int rayAlgorithm(const QPointF &q, TPolygon P);

        static int getPointLinePosition(const QPointF &p, const QPointF &p1, const QPointF &p2);

        static double getTwoVectorsOrientation(const QPointF &p1, const QPointF &p2, const QPointF &p3, const QPointF &p4);

        static int windingAlgorithm(const QPointF &q, TPolygon P);
    Algorithms();
};

#endif // ALGORITHMS_H
