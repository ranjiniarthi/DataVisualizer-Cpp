#include "stack.h"
#include "ui_stack.h"

stack::stack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stack)
{
    ui->setupUi(this);

    // Init entries
    num_of_entries=0;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-1000, -1000, 2000, 2000);

    tpoint.setX(-1000);
    tpoint.setY(-907);
    tline.setLine(-980, -907, -980, -930);

    // Set the position for rear label
    QFont font;
    font.bold();
    top_label = scene->addText("Top", font);
    top_label->setPos(tpoint);
    top_line = scene->addLine(tline);
    ui->graphicsView->setScene(scene);
}

stack::~stack()
{
    if (top_label)
       delete top_label;
    if (top_line)
       delete top_line;

    delete ui;
}

void stack::insertElem(QString val)
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
    if (!num_of_entries) { // Add first node
        ui->graphicsView->setScene(scene);
        l = ui->graphicsView->scene()->addText(val, font);
        l->setPos(tline.x2()-10, tline.y2()-30);
        r = ui->graphicsView->scene()->addRect(tline.x2()-20, tline.y2()-40, 50, 40, pen);
    } else { // Add consequetive nodes and set the top at the right position.
        l = ui->graphicsView->scene()->addText(val, font);
        tpoint.setX(tpoint.x()+50);
        top_label->setPos(tpoint);
        tline.setLine(tline.x1()+50, tline.y1(), tline.x2()+50, tline.y2());
        top_line->setLine(tline);
        l->setPos(tline.x2()-10, tline.y2()-30);
        r = ui->graphicsView->scene()->addRect(tline.x2()-20, tline.y2()-40, 50, 40, pen);
    }

    elem.text = l;
    elem.rect = r;
    num_of_entries++;
    lmap.insert(std::make_pair(num_of_entries, elem));
    printf ("Inserted Element :%d\n", num_of_entries);
}

void stack::cleanupElem(Ui::RectElement *elem) {
    QGraphicsTextItem *l = elem->text;
    QGraphicsRectItem *r = elem->rect;
    ui->graphicsView->scene()->removeItem(l);
    ui->graphicsView->scene()->removeItem(r);
    delete l;
    delete r;
}

void stack::removeElem(int idx)
{
    std::map<int, Ui::RectElement>::iterator it;

    it = lmap.find(idx);
    if (it != lmap.end()) {
        Ui::RectElement elem = it->second;
        cleanupElem(&elem);
        lmap.erase(it);
    }
    num_of_entries--;

    // Move the "Top" label to point to the right position
    if (num_of_entries) {
        tpoint.setX(tpoint.x()-50);
        top_label->setPos(tpoint);
        tline.setLine(tline.x1()-50, tline.y1(), tline.x2()-50, tline.y2());
        top_line->setLine(tline);
    }
}

// Push an element to the stack
void stack::on_pushButton_2_clicked()
{
    QString val;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //Do Nothing
    }
    ui->lineEdit->setText("");

    insertElem(val);
}

// Pop an element from stack and cleanup.
void stack::on_pushButton_clicked()
{
    QString val;
    QRect rect;
    QFont font;
    std::map <int, Ui::RectElement>::iterator it;

    if (!num_of_entries) {
        return;
    }

    // Pop an element and clean up.
    removeElem(num_of_entries);
}

//Clear stack
void stack::on_pushButton_3_clicked()
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
    tpoint.setX(tpoint.x()-40*(num_of_entries-1));
    top_label->setPos(tpoint);
    tline.setLine(tline.x1()-40*(num_of_entries-1), tline.y1(), tline.x2()-40*(num_of_entries-1), tline.y2());
    top_line->setLine(tline);
    num_of_entries=0;
}

//Add 10 random numbers to stack
void stack::on_pushButton_4_clicked()
{
    int randNum[10];

    Ui::genRand(randNum, 10);
    for (int i=0; i<10; i++) {
        insertElem(QString::number(randNum[i]));
    }
}
