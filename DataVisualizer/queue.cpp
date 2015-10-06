#include "queue.h"
#include "ui_queue.h"

Queue::Queue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Queue)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-500, -500, 1000, 1000);

    num_of_entries = 0;

    // Set the position for front
    // and rear labels
    fpoint.setX(-500);
    fpoint.setY(-500);
    fline.setLine(-480, -480, -480, -460);
    rline.setLine(-480, -387, -480, -410);
    rpoint.setX(-500);
    rpoint.setY(-387);
}


Queue::~Queue()
{
    delete ui;
}

// Inserting a new element to the
// front of the queue.
void Queue::on_pushButton_2_clicked()
{
    QString val;
    QFont font;
    QGraphicsTextItem *l;
    QGraphicsRectItem *r;
    Ui::Element elem;
    QPen pen;

    pen.setBrush(Qt::red);
    val = ui->lineEdit->text();
    if (val == "") {
        return; //No value -- No-op!
    }
    ui->lineEdit->setText("");

    font.setBold(1);
    font.setWeight(10);
    if (!num_of_entries) {
        // Add a new element for the first time
        // Insert front and rear label here.
        QFont font;
        font.bold();
        front_label = scene->addText("Front", font);
        front_label->setPos(fpoint);
        front_line = scene->addLine(fline);
        rear_label = scene->addText("Rear", font);
        rear_label->setPos(rpoint);
        rear_line = scene->addLine(rline);
        ui->graphicsView->setScene(scene);
        l = ui->graphicsView->scene()->addText(val, font);
        l->setPos(rline.x2()-10, rline.y2()-30);
        r = ui->graphicsView->scene()->addRect(rline.x2()-20, rline.y2()-40, 50, 40, pen);
    } else {
        // Add consequetive elements
        l = ui->graphicsView->scene()->addText(val, font);
        rpoint.setX(rpoint.x()+50);
        rear_label->setPos(rpoint);
        rline.setLine(rline.x1()+50, rline.y1(), rline.x2()+50, rline.y2());
        rear_line->setLine(rline);
        l->setPos(rline.x2()-10, rline.y2()-30);
        r = ui->graphicsView->scene()->addRect(rline.x2()-20, rline.y2()-40, 50, 40, pen);
    }

    elem.text = l;
    elem.rect = r;
    num_of_entries++;
    lmap.insert(std::make_pair(num_of_entries, elem));
}


// Delete an element from the
// queue and clean up.
void Queue::on_pushButton_clicked()
{
    QString val;
    QRect rect;
    QFont font;
    std::map <int, Ui::Element>::iterator it, it2;

    if (!num_of_entries) {
        return;
    }

    // Delete the element
    // and clean up the resource
    // Also make sure to shift
    // the other elements to the left.
    it = lmap.find(1);
    if (it != lmap.end()) {
        Ui::Element elem = it->second;
        QGraphicsTextItem *l = elem.text;
        QGraphicsRectItem *r = elem.rect;
        ui->graphicsView->scene()->removeItem(l);
        ui->graphicsView->scene()->removeItem(r);
        lmap.erase(it);
        delete l;
        delete r;
        QPointF pos;
        pos.setX(fline.x2()-10); pos.setY(fline.y2()+20);
        for (int i=2; i<(num_of_entries+1); i++) {
            it2 = lmap.find(i);
            if (it2 != lmap.end()) {
               lmap.insert(std::make_pair(i-1, it2->second));
               Ui::Element elem = it2->second;
               QGraphicsRectItem *r = elem.rect;
               QGraphicsTextItem *t = elem.text;
               t->setPos(pos.x(), pos.y());
               r->setRect(pos.x()-10, pos.y()-10, 50, 40);
               lmap.erase(it2);
               pos.setX(pos.x()+50);
            }
        }
    }
    num_of_entries--;

    if (num_of_entries) {
        rpoint.setX(rpoint.x()-50);
        rear_label->setPos(rpoint);
        rline.setLine(rline.x1()-50, rline.y1(), rline.x2()-50, rline.y2());
        rear_line->setLine(rline);
    } else {
        if (front_label)
           delete front_label;
        if (rear_label)
            delete rear_label;
        if (front_line)
           delete front_line;
        if (rear_line)
           delete rear_line;
    }
}

// Clear queue
void Queue::on_pushButton_3_clicked()
{
   std::map<int, Ui::Element>::iterator it;

   if  (!num_of_entries)
       return; // Do Nothing

   for (int i=1; i<(num_of_entries+1); i++) {
        it = lmap.find(i);
        if (it != lmap.end()) {
            Ui::Element elem = it->second;
            QGraphicsTextItem *l = elem.text;
            QGraphicsRectItem *r = elem.rect;
            ui->graphicsView->scene()->removeItem(l);
            ui->graphicsView->scene()->removeItem(r);
            lmap.erase(it);
            delete l; delete r;
        }
    }

    if (front_label)
       delete front_label;
    if (rear_label)
        delete rear_label;
    if (front_line)
       delete front_line;
    if (rear_line)
       delete rear_line;

    fpoint.setX(-500);
    fpoint.setY(-500);
    fline.setLine(-480, -480, -480, -460);
    rline.setLine(-480, -387, -480, -410);
    rpoint.setX(-500);
    rpoint.setY(-387);
    num_of_entries=0;
}
