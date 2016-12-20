#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QtGui>
#include "algorithms.h"
#include "sortbyxasc.h"


typedef QVector<QPoint> TPolygon;
typedef QVector<QPolygon> TPolygons;

class Draw : public QWidget
{
    Q_OBJECT
private:
    TPolygons pols;
    QPoint cursor;
    bool ignoreDrawPols;
    QVector<bool> results;
    bool draw_what = false;


public:
    int typeAlgorithms;

    explicit Draw(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    QPoint generatePoint();
    void generatePolygons(int n);
    void setDrawWhat(bool draw_what_){ draw_what = draw_what_; }
    QPoint & getCursor(){ return cursor; }

signals:

public slots:

};

#endif // DRAW_H
