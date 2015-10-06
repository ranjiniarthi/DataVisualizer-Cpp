#include "stack.h"
#include "ui_stack.h"

stack::stack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stack)
{
    ui->setupUi(this);

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

// Push an element to the stack
void stack::on_pushButton_2_clicked()
{
    QString val;
    QFont font;
    QGraphicsTextItem *l;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //Do Nothing
    }
    ui->lineEdit->setText("");

    if (!num_of_entries) { // Add first node
        l = ui->graphicsView->scene()->addText(val, font);
        l->setPos(tline.x2()-5, tline.y2()-10);
    } else { // Add consequetive nodes and set the top at the right position.
        l = ui->graphicsView->scene()->addText(val, font);
        tpoint.setX(tpoint.x()+40);
        top_label->setPos(tpoint);
        tline.setLine(tline.x1()+40, tline.y1(), tline.x2()+40, tline.y2());
        top_line->setLine(tline);
        l->setPos(tline.x2()-5, tline.y2()-10);
    }

    num_of_entries++;
    lmap.insert(std::make_pair(num_of_entries, l));
}

// Pop an element from stack and cleanup.
void stack::on_pushButton_clicked()
{
    QString val;
    QRect rect;
    QFont font;
    std::map <int, QGraphicsTextItem *>::iterator it;

    if (!num_of_entries) {
        return;
    }

    // Pop an element and clean up.
    it = lmap.find(num_of_entries);
    if (it != lmap.end()) {
        QGraphicsTextItem *l = it->second;
        ui->graphicsView->scene()->removeItem(l);
        lmap.erase(it);
        delete l;
    }
    num_of_entries--;

    // Move the "Top" label to point to the right position
    if (num_of_entries) {
        tpoint.setX(tpoint.x()-40);
        top_label->setPos(tpoint);
        tline.setLine(tline.x1()-40, tline.y1(), tline.x2()-40, tline.y2());
        top_line->setLine(tline);
    }
}

//Clear stack
void stack::on_pushButton_3_clicked()
{
    std::map<int, QGraphicsTextItem *>::iterator it;
     for (int i=1; i<(num_of_entries+1); i++) {
         it = lmap.find(i);
         if (it != lmap.end()) {
             QGraphicsTextItem *l = it->second;
             ui->graphicsView->scene()->removeItem(l);
             lmap.erase(it);
             delete l;
         }
     }
     tpoint.setX(tpoint.x()-40*(num_of_entries-1));
     top_label->setPos(tpoint);
     tline.setLine(tline.x1()-40*(num_of_entries-1), tline.y1(), tline.x2()-40*(num_of_entries-1), tline.y2());
     top_line->setLine(tline);
}
