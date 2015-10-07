#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    queueui.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    stackui.show();
}

void MainWindow::on_pushButton_3_clicked()
{
    bheapui.show();
}

void MainWindow::on_pushButton_4_clicked()
{
    bstui.show();
}
