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
    v = new QIntValidator(0, 65535, this);
    ui->lineEdit->setValidator(v);
}


Queue::~Queue()
{
    delete ui;
}

// Insert an element into the
// Queue
void Queue::insertElem(QString val)
{
    QFont font;
    QGraphicsTextItem *l;
    QGraphicsRectItem *r;
    Ui::RectElement elem;
    QPen pen;

    font.bold();
    pen.setBrush(Qt::red);
    font.setBold(1);
    font.setWeight(10);
    if (!num_of_entries) {
        // Add a new element for the first time
        // Insert front and rear label here.
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

// Clean up the Queue Element
void Queue::cleanupElem(Ui::RectElement *elem)
{
    QGraphicsTextItem *l = elem->text;
    QGraphicsRectItem *r = elem->rect;
    ui->graphicsView->scene()->removeItem(l);
    ui->graphicsView->scene()->removeItem(r);
    delete l;
    delete r;
}

// Remove the element from Queue
void Queue::removeElem(int index)
{
    std::map<int, Ui::RectElement>::iterator it, it2;

    // Delete the element
    // and clean up the resource
    // Also make sure to shift
    // the other elements to the left.
    it = lmap.find(index);
    if (it != lmap.end()) {
        Ui::RectElement elem = it->second;
        cleanupElem(&elem);
        lmap.erase(it);
        QPointF pos;
        pos.setX(fline.x2()-10); pos.setY(fline.y2()+20);
        for (int i=2; i<(num_of_entries+1); i++) {
            it2 = lmap.find(i);
            if (it2 != lmap.end()) {
               lmap.insert(std::make_pair(i-1, it2->second));
               Ui::RectElement elem = it2->second;
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

// Inserting a new element to the
// front of the queue.
void Queue::on_pushButton_2_clicked()
{
    QString val;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //No value -- No-op!
    }
    ui->lineEdit->setText("");

    insertElem(val);
}

// Delete an element from the
// queue and clean up.
void Queue::on_pushButton_clicked()
{
    QString val;
    QRect rect;
    QFont font;
    std::map <int, Ui::RectElement>::iterator it, it2;

    if (!num_of_entries) {
        return;
    }

    // Remove the first element
    removeElem(1);
}

// Clear queue
void Queue::on_pushButton_3_clicked()
{
   std::map<int, Ui::RectElement>::iterator it;

   if  (!num_of_entries)
       return; // Do Nothing

   for (int i=1; i<(num_of_entries+1); i++) {
        it = lmap.find(i);
        if (it != lmap.end()) {
            Ui::RectElement elem = it->second;
            cleanupElem(&elem);
            lmap.erase(it);
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

// Add 10 random numbers to Queue
void Queue::on_pushButton_4_clicked()
{
    int randNum[10];

    Ui::genRand(randNum, 10);
    for (int i=0; i<10; i++) {
        insertElem(QString::number(randNum[i]));
    }
}
