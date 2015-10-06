#ifndef STACK_H
#define STACK_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QLineF>
#include "visualizer.h"

namespace Ui {
class stack;
}

class stack : public QWidget
{
    Q_OBJECT

public:
    explicit stack(QWidget *parent = 0);
    ~stack();
    void insertElem(QString val);
    void removeElem(int idx);
    void cleanupElem(Ui::RectElement *elem);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::stack *ui;
    QGraphicsScene *scene;
    int num_of_entries;
    QPointF tpoint;
    QLineF  tline;
    QGraphicsTextItem *top_label;
    QGraphicsLineItem *top_line;
    std::map<int, Ui::RectElement> lmap;
};

#endif // STACK_H
