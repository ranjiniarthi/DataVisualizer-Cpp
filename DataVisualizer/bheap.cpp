#include "bheap.h"
#include "ui_bheap.h"
#include <QGraphicsEllipseItem>
#include "math.h"
#include "stdio.h"

Bheap::Bheap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bheap)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(-250, -250, 500, 500);
    scene->setFocus();

    scene_coords.setX(-250); scene_coords.setY(-250);
    scene_coords.setWidth(500); scene_coords.setHeight(500);
    base_coords = scene_coords;
    num_of_entries = 0;
    heap_height = 0;
    v = new QIntValidator(0, 65535, this);
    ui->lineEdit->setValidator(v);
}

Bheap::~Bheap()
{
    delete ui;
}

// API to adjust scene size if the tree grows
// bigger.
void Bheap::adjustsceneRect(QRectF offset)
{
    if (offset.height() > scene_coords.height()) {
        printf("1 ");
        if (offset.y() > 0) {
            offset.setY(scene_coords.y()-(offset.y()-scene_coords.y()));
        }
        scene_coords.setX(offset.y()); scene_coords.setY(offset.y());
        scene_coords.setWidth(offset.height()); scene_coords.setHeight(offset.height());
    } else if (offset.width() > scene_coords.width()) {
        printf("2 ");
        if (offset.x() > 0) {
            offset.setX(scene_coords.x()-(offset.x()-scene_coords.x()));
        }
        scene_coords.setX(offset.x()); scene_coords.setY(offset.x());
        scene_coords.setWidth(offset.width()); scene_coords.setHeight(offset.width());
    }
    printf("Setting SceneRec to %g %g %g\n", scene_coords.x(), scene_coords.y(), scene_coords.width());
    ui->graphicsView->setSceneRect(scene_coords.x(),scene_coords.y(), scene_coords.width(), scene_coords.height());
}

// API to clean up node
void Bheap::deleteNode(Ui::Node *node)
{
     ui->graphicsView->scene()->removeItem(node->ellipse);
     ui->graphicsView->scene()->removeItem(node->text);
     if (node->plink != NULL) {
         ui->graphicsView->scene()->removeItem(node->plink);
     }
     delete node->ellipse;
     delete node->text;
     delete node->pos;
     delete node->plink;
     delete node;
}

// This API deals with removing a node
// and readjusting the parent nodes back
// to the previous position if there is
// a height change.
void Bheap::removeMin()
{
    //Cleanup the old node
    deleteNode(hmap[num_of_entries+1]);

    QFont font;
    int new_height = (int)(log2((double)num_of_entries));
    int leaves = pow(2,new_height);
    double offset=0;
    int curr_height, prev_height;
    curr_height=prev_height=0;
    for (int pos=1; pos<(num_of_entries+1); pos++) {
         Ui::Node *n = hmap[pos];
         QGraphicsTextItem *t = n->text;
         curr_height = (int)log2((double)pos);
         // If the height decreases, we can shrink the tree
         // to make room for further inserts
         if (new_height<heap_height) {
             Ui::Node *parent = hmap[pos/2];
             // If we are at (height > 1), the node
             // have to be moved according to the parent.
             if (pos/2) {
                 QGraphicsLineItem *l = n->plink;
                 QLineF line = l->line();
                 // If the new height of our heap is N, we have
                 // 2^N leaves. Out of that, we will have 1/2^curr_height
                 // for the subtree rooted at "curr_height". We
                 // want to know that so we can position the nodes
                 // back to where they were before expansion.
                 if (curr_height != prev_height) {
                     offset = leaves/pow(2,curr_height);
                     prev_height = curr_height;
                 }
                 if (pos%2) {
                     n->pos->setX(parent->pos->x()-(offset*50)); n->pos->setY(n->pos->y()-10);
                     line.setLine(n->pos->x()+25, n->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                 } else {
                     n->pos->setX(parent->pos->x()+(offset*50)); n->pos->setY(n->pos->y()-10);
                     line.setLine(n->pos->x()+25, n->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                 }
                 l->setLine(line);
             } else {
                 n->pos->setX(n->pos->x()-new_height*50);
             }
             // Set the ellipse and text at their right
             // position calculated above
             QGraphicsEllipseItem *e = n->ellipse;
             e->setRect(n->pos->x(), n->pos->y(), 40, 20);
             t->setPos(n->pos->x()+8, n->pos->y());

             //Shrink the scene size to starting size
             qreal new_w = (n->pos->x())*2;
             qreal new_h = ((int)n->pos->y())*2;

             if ((new_w < (int)scene_coords.width() && new_w > (int)base_coords.width()) ||
                 (new_h < (int)scene_coords.height() && new_w > (int)base_coords.width())) {
                 adjustsceneRect(base_coords);
             }
         }
         // Set the right value in the text
         t->setPlainText(heap[pos-1]);
    }
    heap_height = log2((double)num_of_entries);
}

// This API is to draw the node for the
// element inserted and link it to the parent
// Most of the logic deals with adjusting the
// parent node positions to make room for the
// ones.
void Bheap::insertbheap()
{
    QFont font;
    Ui::Node *node = NULL;

    node = new Ui::Node;
    if (node == NULL) {
        return; //Bail out -- NO MEM
    }

    font.setBold(0);
    if (num_of_entries==1) {
        // Insert the first node at top left of the scene.
        node->pos = new QPointF;
        node->pos->setX(-120); node->pos->setY(-240);
        QGraphicsEllipseItem *e = ui->graphicsView->scene()->addEllipse(node->pos->x(), node->pos->y(), 40, 20);
        ui->graphicsView->scene()->setFocusItem(e, Qt::OtherFocusReason);
        node->ellipse = e;
        node->ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
        node->text = ui->graphicsView->scene()->addText(heap[num_of_entries-1], font);
        node->text->setPos(node->pos->x()+8, node->pos->y());
        node->plink = NULL;
        hmap[num_of_entries] = node;
        heap_height=1;
    } else {

       // Adjust the previous entries for position + contents
       // after the new insert.

       int new_height = (int)(log2((double)num_of_entries));
       int leaves = pow(2,new_height);
       double offset=0;
       int curr_height, prev_height;
       curr_height=prev_height=0;
       for (int pos=1; pos<num_of_entries; pos++) {
            Ui::Node *n = hmap[pos];
            QGraphicsTextItem *t = n->text;
            curr_height = (int)log2((double)pos);
            // If the height increase, we need to position
            // the nodes farther to make room for the next level.
            if (new_height>heap_height) {
                Ui::Node *parent = hmap[pos/2];
                // If we are at (height > 1), the nodes
                // have to be moved according to the parent.
                if (pos/2) {
                    QGraphicsLineItem *l = n->plink;
                    QLineF line = l->line();
                    // If the new height of our heap is N, we have
                    // 2^N leaves. Out of that, we will have 1/2^curr_height
                    // for the subtree rooted at "curr_height". We
                    // want to know that so we can position ourselves
                    // right to make room for the subtrees/leaves.
                    if (curr_height != prev_height) {
                        offset = leaves/pow(2,curr_height);
                        prev_height = curr_height;
                    }
                    if (pos%2) {
                        n->pos->setX(parent->pos->x()+(offset*50)); n->pos->setY(n->pos->y()+10);
                        line.setLine(n->pos->x()+25, n->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                    } else {
                        n->pos->setX(parent->pos->x()-(offset*50)); n->pos->setY(n->pos->y()+10);
                        line.setLine(n->pos->x()+25, n->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                    }
                    l->setLine(line);
                } else {
                    n->pos->setX(n->pos->x()+new_height*50);
                }
                // Set the right position for the ellipse and the text as calculated
                QGraphicsEllipseItem *e = n->ellipse;
                e->setRect(n->pos->x(), n->pos->y(), 40, 20);
                t->setPos(n->pos->x()+8, n->pos->y());

                //Adjust the scene size if we are expanding
                qreal new_w = (n->pos->x())*2;
                qreal new_h = ((int)n->pos->y())*2;

                if ((new_w > (int)scene_coords.width()) || (new_h > (int)scene_coords.height())) {
                    QRectF coords;
                    coords.setX(n->pos->x()); coords.setY(n->pos->y());
                    coords.setWidth(abs(new_w)); coords.setHeight(abs(new_h));
                    adjustsceneRect(coords);
                }
            }
            t->setPlainText(heap[pos-1]);
        }
        heap_height = log2((double)num_of_entries);
        if (!(num_of_entries%2)) { // Insert the Left Child to the left of its parent
            Ui::Node *parent = hmap[num_of_entries/2];
            if (parent != NULL) {
                node->pos = new QPointF;
                node->pos->setX(parent->pos->x()-50); node->pos->setY(parent->pos->y()+30);
                node->ellipse = ui->graphicsView->scene()->addEllipse(node->pos->x(), node->pos->y(), 40, 20);
                node->ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
                node->text = ui->graphicsView->scene()->addText(heap[num_of_entries-1], font);
                node->text->setPos(node->pos->x()+8, node->pos->y());
                node->plink= ui->graphicsView->scene()->addLine(node->pos->x()+20, node->pos->y(), parent->pos->x()+10, parent->pos->y()+20);
                hmap[num_of_entries] = node;
             }
        } else { // Insert the Right Child at the right of its parent
            Ui::Node *parent = hmap[num_of_entries/2];
            if (parent != NULL) {
                node->pos = new QPointF;
                node->pos->setX(parent->pos->x()+50); node->pos->setY(parent->pos->y()+30);
                node->ellipse = ui->graphicsView->scene()->addEllipse(node->pos->x(), node->pos->y(), 40, 20);
                node->ellipse->setFlag(QGraphicsItem::ItemIsMovable, true);
                node->text = ui->graphicsView->scene()->addText(heap[num_of_entries-1], font);
                node->text->setPos(node->pos->x()+8, node->pos->y());
                node->plink = ui->graphicsView->scene()->addLine(node->pos->x()+10, node->pos->y(), parent->pos->x()+20, parent->pos->y()+20);
                hmap[num_of_entries] = node;
            }
        }
        // Adjust the scene size if we need to
        int new_w = ((int)node->pos->x())*2;
        int new_h = ((int)node->pos->y())*2;

        if ((new_w > (int)scene_coords.width()) || (new_h > (int)scene_coords.height())) {
            QRectF coords;
            coords.setX(node->pos->x()); coords.setY(node->pos->y());
            coords.setWidth(abs(new_w)); coords.setHeight(abs(new_h));
            adjustsceneRect(coords);
        }
    }
}


// Insert element to Heap
void Bheap::on_pushButton_2_clicked()
{
    QString val;
    int pos;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //Do Nothing
    }
    ui->lineEdit->setText("");

    num_of_entries++;
    heap[num_of_entries-1] = val;

    // Heapify. Place the newly
    // inserted element in its right place.
    pos = num_of_entries;
    while (pos>1) {
        if (heap[pos-1].toInt() < heap[pos/2-1].toInt()) {
            QString tmp;
            tmp = heap[pos-1];
            heap[pos-1] = heap[pos/2-1];
            heap[pos/2-1] = tmp;
        }
        pos = pos/2;
    }
    insertbheap();
}


// Remove Element from Heap
void Bheap::on_pushButton_clicked()
{
    int pos, minPos;

    heap[0] = heap[num_of_entries-1];
    heap[num_of_entries-1] = "0";
    num_of_entries--;

    // HeapDown. Move the last element
    // to its right position.
    pos = 1;
    while ((pos<num_of_entries) &&
           (heap[pos-1] != "0")) {
        printf("Pos: %d\n", pos);
        // Get the array position for the minimum
        if (((2*pos-1)<num_of_entries) &&
            (heap[2*pos].toInt() > heap[2*pos-1].toInt())) {
            minPos = 2*pos;
        } else if ((2*pos) < num_of_entries) {
            minPos = 2*pos+1;
        } else {
            minPos = pos;
        }
        if (heap[pos-1].toInt() > heap[minPos-1].toInt()) {
            QString tmp;
            tmp = heap[pos-1];
            heap[pos-1] = heap[minPos-1];
            heap[minPos-1] = tmp;
            pos = minPos;
        } else {
            break;
        }
    }

    removeMin();
}


//Clear Heap
void Bheap::on_pushButton_3_clicked()
{
    for (int node=1; node<(num_of_entries+1); node++) {
        heap[node-1] = "0";
        deleteNode(hmap[node]);
    }
    num_of_entries=0;
}
