#ifndef PLANSZA_H
#define PLANSZA_H
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include "pole.h"
#include "sciana.h"
#include "lawa.h"



class Plansza : public QWidget
{

    Q_OBJECT

public:
    explicit Plansza(QWidget *parent = 0);
    bool game_status;
    bool move_status;
    bool game_pause;

    Pole *g;
    Sciana **tpiksele;
    Lawa **tlawa;
    QKeyEvent *w;

    double ruchy;
    int teleport_bar;
    int czas;
    int wykonane;
    QVector <Pole *> Heads;
private:
    QTimer *t;


signals:

public slots:
    void generuj_Plansza();

    void rysuj_Gracz(QPainter *d , Pole *g);
    void rysuj_Frame(QPainter *d);
    void rysuj_Plansza(QPainter *d);
    void reset_Plansza();
    void reset_Lawa();
    int add_Lawa(int, int);
    void paintEvent(QPaintEvent *);

    void rysuj_Siatka(QPainter *d);
    void doteleport();
    bool isgame();

    void tick();


};

#endif // PLANSZA_H
