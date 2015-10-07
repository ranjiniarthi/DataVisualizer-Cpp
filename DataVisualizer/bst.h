#ifndef BST_H
#define BST_H

#include <QWidget>

namespace Ui {
class Bst;
}

class Bst : public QWidget
{
    Q_OBJECT

public:
    explicit Bst(QWidget *parent = 0);
    ~Bst();

private:
    Ui::Bst *ui;
};

#endif // BST_H
