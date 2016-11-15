#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QtGui>
#include "algorithms.h"


typedef QVector<QPointF> TPolygon;
typedef QVector<QPolygonF> TPolygons;

class Draw : public QWidget
{
    Q_OBJECT
private:
    TPolygon pol;
    TPolygons pols;
    QPointF cursor;
    bool ignoreDrawPols;
    QVector<bool> results;
    bool draw_what;


public:
    int typeAlgorithms;

    explicit Draw(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void setDrawWhat(bool draw_what_){ draw_what = draw_what_; }
    QPointF & getCursor(){ return cursor; }

signals:

public slots:

};

#endif // DRAW_H
