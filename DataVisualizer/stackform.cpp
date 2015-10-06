#include "stackform.h"

using namespace std;


StackForm::StackForm(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::StackForm)
{
    ui->setupUi(this);
   // setupUiWidgets(this);
    num_of_entries=0;
    label_coordinates[0]=70;
    label_coordinates[1]=110;
    label_coordinates[2]=31;
    label_coordinates[3]=21;

    ledit_coordinates[0]=120;
    ledit_coordinates[1]=100;
    ledit_coordinates[2]=31;
    ledit_coordinates[3]=21;

    top_label = NULL;
}

StackForm::~StackForm()
{
    std::map <int, QLineEdit *>::iterator it;

    for (it=lmap.begin(); it!=lmap.end(); it++) {
        delete it->second;
    }

    if (top_label != NULL) {
        delete top_label;
    }

    delete ui;
}

void StackForm::on_pushButton_clicked()
{
    QString val;
    QRect rect;
    QFont font;
    std::map <int, QLineEdit *>::iterator it;

    int count=0;
    for (it=lmap.begin(); it!=lmap.end(); it++) {
        QLineEdit *ledit = it->second;
        ui->gridLayout_3->removeWidget(ledit);
        ledit->hide();
    }

    it = lmap.find(num_of_entries);
    if (it != lmap.end()) {
        QLineEdit *ledit = it->second;
        ui->gridLayout_3->removeWidget(ledit);
        lmap.erase(it);
        delete ledit;
    }

    num_of_entries--;
    if (!num_of_entries) {
        ui->gridLayout_3->removeWidget(top_label);
        top_label->hide();
        delete top_label;
        top_label = NULL;
    }

    std::map<int, QLineEdit *>::reverse_iterator rit;
    count = 0;
    for (rit=lmap.rbegin(); rit!=lmap.rend(); rit++) {
        QLineEdit *ledit = rit->second;
        ui->gridLayout_3->addWidget(ledit, count++, 1, 1, 1, 0);
        ledit->show();
    }
}

void StackForm::on_pushButton_2_clicked()
{
    static int x=0, y=0, w=0, h=0;
    QString val;
    QRect rect;
    QFont font;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //Do Nothing
    }

    ui->lineEdit->setText("");

    rect.setRect(label_coordinates[0], label_coordinates[1],
                 label_coordinates[2], label_coordinates[3]);
    font.bold();
    if (num_of_entries==0) {
       top_label = new QLabel(ui->widget);
       top_label->setText("TOP");
       top_label->setFont(font);
       top_label->setGeometry(rect);
       ui->gridLayout_3->addWidget(top_label, 0, 0, 1, 1,0);
       top_label->show();
    }

    int count=0;
    std::map<int, QLineEdit *>::iterator it;
    for (it=lmap.begin(); it!=lmap.end(); it++) {
        QLineEdit *ledit = it->second;
        ui->gridLayout_3->removeWidget(ledit);
        ledit->hide();
    }

    rect.setRect(ledit_coordinates[0]+x, ledit_coordinates[1]+y,
                 ledit_coordinates[2]+w, ledit_coordinates[3]+h);
    QLineEdit *l = new QLineEdit(ui->widget);
    l->setFont(font);
    l->setText(val);
    l->setGeometry(rect);
    ui->gridLayout_3->addWidget(l, 0, 1, 1, 1, 0);
    l->show();

    std::map<int, QLineEdit *>::reverse_iterator rit;
    count = 1;
    for (rit=lmap.rbegin(); rit!=lmap.rend(); rit++) {
        QLineEdit *ledit = rit->second;
        ui->gridLayout_3->addWidget(ledit, count++, 1, 1, 1, 0);
        ledit->show();
    }
    lmap.insert(std::make_pair(++num_of_entries, l));

    y +=30;

}

void StackForm::on_pushButton_3_clicked()
{
    std::map<int, QLineEdit *>::iterator it;
    for (int i=1; i<(num_of_entries+1); i++) {
        it = lmap.find(i);
        if (it != lmap.end()) {
            QLineEdit *ledit = it->second;
            ui->gridLayout_3->removeWidget(ledit);
            lmap.erase(it);
            delete ledit;
        }
    }
    num_of_entries=0;
    ui->gridLayout_3->removeWidget(top_label);
    top_label->hide();
    delete top_label;
    top_label = NULL;
}
