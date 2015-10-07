#include "bst.h"
#include "ui_bst.h"

Bst::Bst(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bst)
{
    ui->setupUi(this);
}

Bst::~Bst()
{
    delete ui;
}
