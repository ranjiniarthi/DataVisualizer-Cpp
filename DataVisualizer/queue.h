#ifndef QUEUE_H
#define QUEUE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QLineF>

namespace Ui {
class Queue;

typedef struct {
    QGraphicsRectItem *rect;
    QGraphicsTextItem *text;
} Element;

}

class Queue : public QWidget
{
    Q_OBJECT

public:
    explicit Queue(QWidget *parent = 0);
    ~Queue();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Queue *ui;
    QGraphicsScene *scene;
    int num_of_entries;
    QPointF fpoint, rpoint;
    QLineF  fline, rline;
    QGraphicsTextItem *front_label;
    QGraphicsTextItem *rear_label;
    QGraphicsLineItem *front_line;
    QGraphicsLineItem *rear_line;
    std::map<int, Ui::Element> lmap;
};

#endif // QUEUE_H
