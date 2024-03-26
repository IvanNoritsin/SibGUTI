
#include "massiv.h"
#include "./ui_massiv.h"
#include "QRandomGenerator"
#include "QMessageBox"
#include <math.h>


Massiv::Massiv(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Massiv)
{
    ui->setupUi(this);
}

Massiv::~Massiv()
{
    delete ui;
}




void Massiv::on_random_triggered()
{
    int vector[40];
    for (int i = 0; i < 40; i++){
        vector[i] = rand()  % 31 - 15;
    }

    for (int i = 0; i < 40; i++){
        vector[i] = sqrt((M_PI/6) * vector[i] + 8);
    }
    int column = ui->tableWidget->currentColumn();
    for(int i=0;i<40;i++)
    {
        // создание указателя на объект класса - ячейку таблицы
        QTableWidgetItem *item=new QTableWidgetItem();
        // значение из массива заносится в объект
        item->setData(Qt::DisplayRole,vector[i]);
        // в ячейку таблицы записывается число
        ui->tableWidget->setItem(i,column,item);
    }
}



void Massiv::on_sort_asc_triggered()
{
    ui->tableWidget->sortItems(ui->tableWidget->currentColumn());
}


void Massiv::on_sort_desc_triggered()
{

}


void Massiv::on_green_triggered()
{
    ui->tableWidget->currentItem()->setBackground(Qt::green);
}

void Massiv::on_blue_triggered()
{
    ui->tableWidget->currentItem()->setBackground(Qt::blue);
}


void Massiv::on_red_triggered()
{
    ui->tableWidget->currentItem()->setBackground(Qt::red);
}


void Massiv::on_sum_triggered()
{
    QString str[10];
    int i=0, sum=0;
    while (i<10)
    {
        // проход по столбцу и запись чисел в массив
        str[i]=ui->tableWidget->item(i,ui->tableWidget->currentColumn())->text();
        // преобразование в целое число
        int x=str[i].toInt();
        if (x<0)
            sum=sum+x;
        i++;
    }
    // преобразование полученной суммы из числа в строку и вывод
    QMessageBox::information(this,"Инфо","Сумма значений в столбце равна " + QString::number(sum));

}


void Massiv::on_Exit_triggered()
{
    QApplication::exit();
}


void Massiv::on_About_triggered()
{
QMessageBox::about(this,"О программе", "<b>Пример</b> работы с виджетами Qt");
}


void Massiv::on_add_column_triggered()
{
    ui->tableWidget->insertColumn(ui->tableWidget->currentColumn());

}


void Massiv::on_col_width_contents_triggered()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void Massiv::on_align_right_triggered()
{
    ui->tableWidget->currentItem()->setTextAlignment(Qt::AlignRight|Qt::AlignBottom);
}


void Massiv::on_align_center_triggered()
{
    ui->tableWidget->currentItem()->setTextAlignment(Qt::AlignCenter);
}


void Massiv::on_format_clean_triggered()
{
    ui->tableWidget->currentItem()->setTextAlignment(Qt::AlignVertical_Mask);
    ui->tableWidget->currentItem()->setBackground(Qt::NoBrush);
}

void Massiv::on_col_width_hand_triggered()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

