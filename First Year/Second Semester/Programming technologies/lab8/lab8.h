
#ifndef LAB8_H
#define LAB8_H

#include <QMainWindow>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class lab8; }
QT_END_NAMESPACE

class lab8 : public QMainWindow

{
    Q_OBJECT

public:
    lab8(QWidget *parent = nullptr);
    ~lab8();

private:
    Ui::lab8 *ui;
    QTimer *timer;

public slots:
    void onTimeout();
private slots:
    void on_actionStart_triggered();
    void on_pushButton_clicked();
    void on_actionStop_triggered();
    void on_actionExit_triggered();
};

#endif // LAB8_H
