#ifndef BHEAP_H
#define BHEAP_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QPointF>

#define MAX_ENTRIES 500

namespace Ui {
class Bheap;

typedef struct {
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;
    QGraphicsLineItem *plink;
    QPointF *pos;
} Node;
};

class Bheap : public QWidget
{
    Q_OBJECT

public:
    explicit Bheap(QWidget *parent = 0);
    ~Bheap();
    void insertbheap();
    void removeMin();
    void adjustsceneRect(QRectF offset);
    void deleteNode(Ui::Node *node);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Bheap *ui;
    QGraphicsScene *scene;
    int num_of_entries;
    Ui::Node *hmap[MAX_ENTRIES];
    QString heap[MAX_ENTRIES];
    int heap_height;
    QRectF scene_coords, base_coords;
    QValidator *v;
};

#endif // BHEAP_H
