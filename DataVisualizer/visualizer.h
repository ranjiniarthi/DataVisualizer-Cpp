#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QPointF>

#define MAX_ENTRIES 500

namespace Ui {
   void genRand(int *list, int count);
   typedef struct {
       QGraphicsRectItem *rect;
       QGraphicsTextItem *text;
   } RectElement;
   typedef struct {
       QGraphicsEllipseItem *ellipse;
       QGraphicsTextItem *text;
       QGraphicsLineItem *plink;
       QPointF *pos;
   } EllipseElement;
}

#endif // VISUALIZER_H
