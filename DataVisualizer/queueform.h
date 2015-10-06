#ifndef QUEUEFORM_H
#define QUEUEFORM_H

#include <QWidget>
#include <QLabel>
#include "ui_QueueForm.h"
#include <map>

namespace Ui {
class QueueForm;
}

class QueueForm : public QWidget
{
    Q_OBJECT

public:
    explicit QueueForm(QWidget *parent = 0);
    ~QueueForm();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::QueueForm *ui;
    int label_coordinates[4];
    int ledit_coordinates[4];
    int num_of_entries;
    QLabel *front_label;
    std::map<int, QLineEdit *> lmap;
};

#endif // QUEUEFORM_H
