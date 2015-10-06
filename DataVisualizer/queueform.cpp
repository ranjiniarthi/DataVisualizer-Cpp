#include "queueform.h"
#include "ui_queueform.h"

QueueForm::QueueForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueueForm)
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

    front_label = NULL;
}

QueueForm::~QueueForm()
{
    std::map <int, QLineEdit *>::iterator it;

    for (it=lmap.begin(); it!=lmap.end(); it++) {
        delete it->second;
    }

    if (front_label != NULL) {
        delete front_label;
    }

    delete ui;
}

void QueueForm::on_pushButton_2_clicked()
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

    if (front_label != NULL) {
        ui->gridLayout_3->removeWidget(front_label);
        front_label->hide();
        delete front_label;
        front_label = NULL;
    }

    num_of_entries++;

    rect.setRect(label_coordinates[0], label_coordinates[1],
                 label_coordinates[2], label_coordinates[3]);
    font.bold();

    rect.setRect(ledit_coordinates[0]+x, ledit_coordinates[1]+y,
                 ledit_coordinates[2]+w, ledit_coordinates[3]+h);
    QLineEdit *l = new QLineEdit(ui->widget);
    l->setFont(font);
    l->setText(val);
    l->setGeometry(rect);
    ui->gridLayout_3->addWidget(l, num_of_entries, 1, 1, 1, 0);
    l->show();

    if (front_label == NULL) {
        front_label = new QLabel(ui->widget);
        front_label->setFont(font);
        front_label->setGeometry(rect);
        front_label->setText("FRONT");
        ui->gridLayout_3->addWidget(front_label, num_of_entries, 0, 1, 1, 0);
    }
    lmap.insert(std::make_pair(num_of_entries, l));

    y +=30;
}

void QueueForm::on_pushButton_clicked()
{
    QString val;
    QRect rect;
    QFont font;
    std::map <int, QLineEdit *>::iterator it;

    it = lmap.find(num_of_entries);
    if (it != lmap.end()) {
        QLineEdit *ledit = it->second;
        ui->gridLayout_3->removeWidget(ledit);
        lmap.erase(it);
        delete ledit;
    }
    num_of_entries--;

    if (front_label != NULL) {
        ui->gridLayout_3->removeWidget(front_label);
        front_label->hide();
        delete front_label;
        front_label = NULL;
    }
}

void QueueForm::on_pushButton_3_clicked()
{

}
