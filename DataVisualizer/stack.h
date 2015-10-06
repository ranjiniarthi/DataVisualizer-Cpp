#ifndef STACK_H
#define STACK_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QLineF>

namespace Ui {
class stack;
}

class stack : public QWidget
{
    Q_OBJECT

public:
    explicit stack(QWidget *parent = 0);
    ~stack();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::stack *ui;
    QGraphicsScene *scene;
    int num_of_entries;
    QPointF tpoint;
    QLineF  tline;
    QGraphicsTextItem *top_label;
    QGraphicsLineItem *top_line;
    std::map<int, QGraphicsTextItem *> lmap;
};

#endif // STACK_H
