#ifndef POLE_H
#define POLE_H

#include <QWidget>
#include <QTime>

class Pole : public QWidget
{
    Q_OBJECT

public:
    int xpos;
    int ypos;
    int size;
    bool free_status;
    bool finish;
    int xback;
    int  yback;
    int xplanszy;
    int yplanszy;




public:
    explicit Pole(QWidget *parent=0);

signals:
public slots:
    bool is_free();
};

#endif // POLE_H
