#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plansza.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);
    p = new Plansza;
    ui->gridLayout_2->addWidget(p,0,0,0,0);
    setWindowTitle("LABIRYNT");

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_actionO_Qt_triggered()
{
    QApplication::aboutQt();
    p->game_pause=false;
    p->move_status=true;

}

void MainWindow::on_pushButton_3_pressed()
{
    QApplication::exit();
}


void MainWindow::on_pushButton_clicked()
{
    p->g->xpos=15;
    p->g->ypos=15;
    p->move_status=true;
    p->reset_Plansza();
    p->reset_Lawa();
    p->czas=0;


    p->game_status=true;
    ui->lcdNumber->display(0);



}










void MainWindow::on_pushButton_2_clicked()
{
    p->game_pause=true;
    p->move_status=false;
}


void MainWindow::on_pushButton_8_clicked()
{
    p->game_pause=false;
    p->move_status=true;
}

void MainWindow::on_actionO_Qt_hovered()
{
    p->game_pause=true;
    p->move_status=false;
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
    {

        if(this->p->tpiksele[this->p->g->xpos/this->p->g->get_size()/2][this->p->g->ypos/this->p->g->get_size()/2].Gwall && this->p->move_status)
        {
            p->g->ypos-=10;
            p->repaint();
            this->p->ruchy++;
            p->teleport_bar+=1;
            ui->progressBar->setValue(p->teleport_bar);
            ui->lcdNumber->display(this->p->ruchy);

        }
    }
        break;

    case Qt::Key_S:
    {
        if(this->p->tpiksele[this->p->g->xpos/this->p->g->get_size()/2][this->p->g->ypos/this->p->g->get_size()/2].Dwall && this->p->move_status)
        {
            p->g->ypos+=10;
            p->repaint();
            this->p->ruchy++;
            p->teleport_bar+=1;
            ui->progressBar->setValue(p->teleport_bar);
            ui->lcdNumber->display(this->p->ruchy);
        }

    }
        break;

    case Qt::Key_D:
    {

        if(this->p->tpiksele[this->p->g->xpos/this->p->g->get_size()/2][this->p->g->ypos/this->p->g->get_size()/2].Pwall && this->p->move_status)
        {
            p->g->xpos+=10;
            p->repaint();
            this->p->ruchy++;
            p->teleport_bar+=1;
            ui->progressBar->setValue(p->teleport_bar);
            ui->lcdNumber->display(this->p->ruchy);
        }
    }
        break;
    case Qt::Key_Q:
    {
        p->doteleport();
    }
        break;

    case Qt::Key_A:
    {

        if(this->p->tpiksele[this->p->g->xpos/this->p->g->get_size()/2][this->p->g->ypos/this->p->g->get_size()/2].Lwall && this->p->move_status)
        {
            p->g->xpos-=10;
            p->repaint();
            this->p->ruchy++;
            p->teleport_bar+=1;
            ui->progressBar->setValue(p->teleport_bar);
            ui->lcdNumber->display(this->p->ruchy);
        }
    }
        break;



    default:
        QWidget::keyPressEvent(event);
    }
}

