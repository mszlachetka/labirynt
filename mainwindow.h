#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plansza.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionO_Qt_triggered();
    void on_pushButton_3_pressed();
    void on_pushButton_clicked();
    void keyPressEvent(QKeyEvent *event);







    void on_pushButton_2_clicked();



    void on_pushButton_8_clicked();

    void on_actionO_Qt_hovered();




private:
    Ui::MainWindow *ui;
    Plansza *p;

};

#endif // MAINWINDOW_H
