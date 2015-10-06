#ifndef STACKFORM_H
#define STACKFORM_H

#include <QWidget>
#include <QLabel>
#include "ui_stackform.h"
#include <map>

namespace Ui {
class StackForm;
}

class StackForm : public QWidget
{

public:
    explicit StackForm(QWidget *parent = 0);

    ~StackForm();
    void setupUiWidgets(QWidget *parent);
    void retranslateUiWidgets(QWidget *parent);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Q_OBJECT
    Ui::StackForm *ui;
    int label_coordinates[4];
    int ledit_coordinates[4];
    int num_of_entries;
    QLabel *top_label;
    std::map<int, QLineEdit *> lmap;
};

#endif // STACKFORM_H
