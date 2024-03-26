
#ifndef MASSIV_H
#define MASSIV_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class Massiv; }
QT_END_NAMESPACE

class Massiv : public QMainWindow

{
    Q_OBJECT

public:
    Massiv(QWidget *parent = nullptr);
    ~Massiv();

private slots:
    void on_random_triggered();

    void on_sort_asc_triggered();

    void on_sort_desc_triggered();

    void on_green_triggered();

    void on_sum_triggered();

    void on_Exit_triggered();

    void on_About_triggered();

    void on_add_column_triggered();

    void on_col_width_contents_triggered();

    void on_align_right_triggered();

    void on_align_center_triggered();

    void on_format_clean_triggered();

    void on_blue_triggered();

    void on_red_triggered();

    void on_col_width_hand_triggered();

private:
    Ui::Massiv *ui;
};

#endif // MASSIV_H
