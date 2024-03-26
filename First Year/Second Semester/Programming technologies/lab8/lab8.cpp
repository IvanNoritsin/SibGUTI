
#include "lab8.h"
#include "./ui_lab8.h"

#define dt 1
#define d2 2


int k = 0, m = 0;

lab8::lab8(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lab8)
{
    ui->setupUi(this);
    QPixmap pixmap("D:/QT Projects/RIS/bg1.jpg");
    pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
}

lab8::~lab8()
{
    delete ui;
}

void lab8::onTimeout()
{
    if(ui->label->geometry().x() < 1300 && m == 0)
    {
        ui->label->setPixmap(QPixmap("D:/QT Projects/RIS/podlodka-transformed_(2)-transformed.png"));
        ui->label_4->setPixmap(QPixmap("D:/QT Projects/RIS/fish (1).png"));
        ui->label_5->setPixmap(QPixmap("D:/QT Projects/RIS/meduza (1).png"));
        ui->label->setGeometry(ui->label->geometry().x()+dt,150,361,231);
        ui->label_2->setGeometry(ui->label_2->geometry().x()-d2,20,431,171);
        ui->label_3->setGeometry(ui->label_3->geometry().x()-dt, 130, 1321, 661);
        ui->label_4->setGeometry(ui->label_4->geometry().x()-d2, 400, 401, 311);
        ui->label_5->setGeometry(ui->label_5->geometry().x()-dt, 110, 161, 161);
        ui->label_6->setGeometry(ui->label_6->geometry().x()-dt,420,691,241);

        if (k == 2 && ui->label->geometry().x() == 0){
            m = 1;
        }

    }

    else if(ui->label->geometry().x() > -300 && m == 1){
        ui->label->setPixmap(QPixmap("D:/QT Projects/RIS/podlodka-transformed_(2)-transformed_2.png"));
        ui->label->setGeometry(ui->label->geometry().x()-d2,150,361,231);
        ui->label_3->setGeometry(ui->label_3->geometry().x()-d2, 130, 1321, 661);
        if (k == 4 && ui->label->geometry().x() == 180){
            timer->stop();
        }
    }



    else
    {
        if (k == 0){
            QPixmap pixmap2("D:/QT Projects/RIS/bg2.jpg");
            pixmap2 = pixmap2.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Window, pixmap2);
            this->setPalette(palette);
            ui->label_2->setGeometry(1300, 20, 431, 171);
            ui->label_2->setPixmap(QPixmap("D:/QT Projects/RIS/shark-transformed (1).png"));
            ui->label_6->setGeometry(270, 420, 691, 241);
            ui->label_6->setPixmap(QPixmap("D:/QT Projects/RIS/swordfish.png"));
            ui->label->setGeometry(-400,150,361,231);
            k = 1;
        }

        else if(k == 1){
            QPixmap pixmap3("D:/QT Projects/RIS/bg3.jpg");
            pixmap3 = pixmap3.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Window, pixmap3);
            this->setPalette(palette);
            ui->label_3->setGeometry(1220, 130, 1321, 661);
            ui->label_3->setPixmap(QPixmap("D:/QT Projects/RIS/wow-o9bRF9hDj-transformed-0bLANAEev-transformed.png"));
            ui->label->setGeometry(-400,150,361,231);
            k = 2;
        }

        else if(k == 2){
            QPixmap pixmap2("D:/QT Projects/RIS/bg2.jpg");
            pixmap2 = pixmap2.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Window, pixmap2);
            this->setPalette(palette);
            ui->label->setGeometry(1400,150,361,231);
            ui->label_3->setGeometry(1820, 130, 1321, 661);
            k = 3;
        }

        else if(k == 3){
            QPixmap pixmap("D:/QT Projects/RIS/bg1.jpg");
            pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
            QPalette palette;
            palette.setBrush(QPalette::Window, pixmap);
            this->setPalette(palette);
            ui->label_7->setGeometry(-10, -160, 1101, 941);
            ui->label_7->setPixmap(QPixmap("D:/QT Projects/RIS/krok-PhotoRoom.png-PhotoRoom.png"));
            ui->label->setGeometry(1400,150,361,231);
            ui->label_3->setGeometry(1820, 130, 1321, 661);
            k = 4;
        }
    }


}



void lab8::on_actionStart_triggered()
{
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer->start(8);
}



void lab8::on_pushButton_clicked()
{
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer->start(100);
}


void lab8::on_actionStop_triggered()
{
    timer->stop();
}


void lab8::on_actionExit_triggered()
{
    QApplication::exit();
}

