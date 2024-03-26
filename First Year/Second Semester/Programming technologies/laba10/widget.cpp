
#include "widget.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::paintEvent(QPaintEvent* )
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // сглаживание
    painter.setPen(QPen(Qt::black, 2)); // черный контур толщиной 2 пикселя
    painter.setBrush(QColor(255, 69, 0, 128)); // оранжевый цвет заливки
    QRectF rect1(100, 100, 200, 200); // прямоугольник для первой части фигуры
    QRectF rect2(100, 100, 200, 200); // прямоугольник для второй части фигуры
    int startAngle = 90; // начальный угол
    int spanAngle = 90; // угол дуги
    painter.translate(rect1.center()); // начало координат в центр первого прямоугольника
    painter.rotate(startAngle); // поворачиваем на начальный угол
    painter.drawPie(QRectF(-rect1.width()/2, -rect1.height()/2, rect1.width(), rect1.height()), 0, spanAngle * 16); // рисуем первую часть фигуры
    painter.setBrush(QColor(0, 128, 128, 128)); // бирюзовый цвет заливки
    painter.resetTransform(); // сброс трансформации
    painter.translate(rect2.center()); // начало координат в центр второго прямоугольника
    painter.rotate(startAngle + 180); // поворачиваем на начальный угол + 180 градусов
       painter.drawPie(QRectF(-rect2.width()/2, -rect2.height()/2, rect2.width(), rect2.height()), 0, spanAngle * 16); // рисуем вторую часть фигуры

}
