#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QtGui>


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
    QVector<int> results;
public:
    explicit Draw(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

    TPolygons & getPols(){return pols;}

    QPointF & getCursor(){return cursor;}

signals:

public slots:

};

#endif // DRAW_H
