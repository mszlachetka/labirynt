#include "plansza.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTime>


Plansza::Plansza(QWidget *parent):QWidget(parent)
{
    g=new Pole;




    g->size=5;
    g->xpos=15;
    g->ypos=15;

    this->setMaximumHeight(400);
    this->setMaximumWidth(500);

    this->tpiksele=new Pole *[this->maximumWidth()/g->get_size()/2];
    for(int i=0;i<this->maximumWidth()/g->get_size()/2;i++)
    {
        this->tpiksele[i]=new Pole[this->maximumHeight()/2/g->get_size()];

    }

    this->tlawa=new Pole *[this->maximumWidth()/g->get_size()/2];
    for(int i=0;i<this->maximumWidth()/g->get_size()/2;i++)
    {
        this->tlawa[i]=new Pole[this->maximumHeight()/2/g->get_size()];


    }
    reset_Plansza();
    reset_Lawa();
    t=new QTimer;
    t->setInterval(100);
    t->start();
    connect(t,SIGNAL(timeout()),this,SLOT(tick()));
    this->czas=0;


}



void Plansza::paintEvent(QPaintEvent *)
{

    QPainter d(this);
     rysuj_Frame(&d);

    if(this->isgame())
    {
        generuj_Plansza();
        this->game_status=false;



    }
    rysuj_Plansza(&d);

    this->update(0,0,this->maximumWidth(),this->maximumHeight());

   // rysuj_Siatka(&d);

}



void Plansza::rysuj_Frame(QPainter *d)
{

    d->setBrush(Qt::yellow);
    d->setPen(Qt::darkMagenta);

    d->drawRect(0,0,this->maximumWidth()-1,this->maximumHeight()-1);
    d->setBrush(Qt::black);
    d->setPen(Qt::black);

    for(int i=0;i<this->maximumWidth()/g->get_size()/2;i++)
    {
        d->drawRect(0,0,this->maximumWidth(),2*this->tpiksele[i][0].size);
        d->drawRect(0,this->maximumHeight(),this->maximumWidth(),-2*this->tpiksele[i][0].size);
        this->tpiksele[i][0].free_status=false;
        this->tpiksele[i][0].Gwall=true;
        this->tpiksele[i][0].Dwall=false;
        this->tpiksele[i][0].Lwall=true;
        this->tpiksele[i][0].Pwall=true;




        this->tpiksele[i][39].free_status=false;
        this->tpiksele[i][39].Gwall=false;
        this->tpiksele[i][39].Dwall=true;
        this->tpiksele[i][39].Lwall=true;
        this->tpiksele[i][39].Pwall=true;




    }
    for(int i=0;i<this->maximumHeight()/g->get_size()/2;i++)
    {
        d->drawRect(0,0,2*this->tpiksele[i][0].size,this->maximumHeight());
        d->drawRect(this->maximumWidth(),0,-2*this->tpiksele[i][0].size,this->maximumHeight());
        this->tpiksele[0][i].free_status=false;

        this->tpiksele[0][i].Gwall=true;
        this->tpiksele[0][i].Dwall=true;
        this->tpiksele[0][i].Lwall=true;
        this->tpiksele[0][i].Pwall=false;




        this->tpiksele[49][i].free_status=false;

        this->tpiksele[49][i].Gwall=true;
        this->tpiksele[49][i].Dwall=true;
        this->tpiksele[49][i].Lwall=false;
        this->tpiksele[49][i].Pwall=true;


    }




}

void Plansza::rysuj_Gracz(QPainter *d, Pole *g)
{
    d->setBrush(Qt::green);
    d->setPen(Qt::darkMagenta);



    d->drawRect(g->get_xpos()-g->get_size()+2,g->get_ypos()-g->get_size()+2,2*g->get_size()-4,2*g->get_size()-4);
}
void Plansza::rysuj_Plansza(QPainter *d)
{
    d->setBrush(Qt::blue);
    d->setPen(Qt::blue);



    for(int i=0;i<50;i++)
        for(int j=0 ; j<40;j++)
        {
            if(!this->tpiksele[i][j].Pwall) d->drawLine(this->tpiksele[i][j].xpos+this->tpiksele[i][j].size,this->tpiksele[i][j].ypos+this->tpiksele[i][j].size,this->tpiksele[i][j].xpos+this->tpiksele[i][j].size,this->tpiksele[i][j].ypos-this->tpiksele[i][j].size);
            if(!this->tpiksele[i][j].Dwall)   d->drawLine(this->tpiksele[i][j].xpos-this->tpiksele[i][j].size,this->tpiksele[i][j].ypos+this->tpiksele[i][j].size,this->tpiksele[i][j].xpos+this->tpiksele[i][j].size,this->tpiksele[i][j].ypos+this->tpiksele[i][j].size);
            if(!this->tpiksele[i][j].Lwall)  d->drawLine(this->tpiksele[i][j].xpos-this->tpiksele[i][j].size,this->tpiksele[i][j].ypos+this->tpiksele[i][j].size,this->tpiksele[i][j].xpos-this->tpiksele[i][j].size,this->tpiksele[i][j].ypos-this->tpiksele[i][j].size);
            if(!this->tpiksele[i][j].Gwall)  d->drawLine(this->tpiksele[i][j].xpos-this->tpiksele[i][j].size,this->tpiksele[i][j].ypos-this->tpiksele[i][j].size,this->tpiksele[i][j].xpos+this->tpiksele[i][j].size,this->tpiksele[i][j].ypos-this->tpiksele[i][j].size);
            if(!this->tlawa[i][j].free_status && this->czas>80)
            {
                 d->setBrush(Qt::darkRed);
                 d->setPen(Qt::red);
                 d->drawRect(this->tlawa[i][j].get_xpos()-g->get_size(),this->tlawa[i][j].get_ypos()-g->get_size(),2*g->get_size(),2*g->get_size());
                  this->tlawa[i][j].colored=true;
                 d->setPen(Qt::blue);
            }

            if(this->tpiksele[i][j].xpos==g->xpos && this->tpiksele[i][j].ypos==g->ypos )
            {

                rysuj_Gracz(d,g);
                d->setBrush(Qt::blue);
                d->setPen(Qt::blue);

            }
            if(this->tpiksele[i][j].finish)
            {
                d->setBrush(Qt::red);
                d->drawEllipse(this->tpiksele[i][j].xpos-5,this->tpiksele[i][j].ypos-5,10,10);
            }
            if(this->tpiksele[i][j].finish && this->tpiksele[i][j].xpos==g->xpos && this->tpiksele[i][j].ypos==g->ypos)
            {

                this->move_status=false;
            }



                   if(this->tlawa[i][j].xpos==this->g->xpos && this->tlawa[i][j].ypos==this->g->ypos &&this->tlawa[i][j].colored )
                   {
                       if(this->czas>100) this->move_status=false;
                   }

}

}

void Plansza:: generuj_Plansza()
{
    qsrand(QTime::currentTime().msec());

    int kierunek;
    int counter=0;
    int x=20;
    int y=20;
      this->tpiksele[x][y].free_status=false;
    while(counter<100000)
    {
        kierunek=rand()%4+1;
        if((this->tpiksele[x+1][y].free_status==true || this->tpiksele[x][y+1].free_status==true || this->tpiksele[x-1][y].free_status==true || this->tpiksele[x][y-1].free_status==true)  )
        {
            if(kierunek==1)//prawo
            {
                if(x!=this->maximumWidth())
                {
                    if(this->tpiksele[x+1][y].free_status==true)
                    {

 this->tpiksele[x][y].Pwall=true;//stare pole


                        x++;

                        this->tpiksele[x][y].set_xback(x-1);
                        this->tpiksele[x][y].set_yback(y);

                       this->tpiksele[x][y].Lwall=true;




                    }

                }


            }
            else if(kierunek==2)//dol
            {

                if(y!=this->maximumHeight())
                {
                    if (this->tpiksele[x][y+1].free_status==true)
                    {

                       this->tpiksele[x][y].Dwall=true;

                        y++;

                        this->tpiksele[x][y].set_xback(x);
                        this->tpiksele[x][y].set_yback(y-1);
                 this->tpiksele[x][y].Gwall=true;



                    }

                }


            }
            else if(kierunek==3)//lewo
            {
                if(x!=0)
                {
                    if(this->tpiksele[x-1][y].free_status==true)
                    {
                    this->tpiksele[x][y].Lwall=true;





                        x--;

                        this->tpiksele[x][y].set_xback(x+1);
                        this->tpiksele[x][y].set_yback(y);
                    this->tpiksele[x][y].Pwall=true;


                    }

                }

            }
            else if(kierunek==4)//gora
            {
                if(y!=0)
                {
                    if( this->tpiksele[x][y-1].free_status==true)
                    {
                       this->tpiksele[x][y].Gwall=true;


                        y--;

                        this->tpiksele[x][y].set_xback(x);
                        this->tpiksele[x][y].set_yback(y+1);
                       this->tpiksele[x][y].Dwall=true;


                    }


                }

            }

            counter++;
             this->tpiksele[x][y].free_status=false;
        }
        else
        {
            this->tpiksele[x][y].free_status=false;






            x=this->tpiksele[x][y].xback;
            y=this->tpiksele[x][y].yback;


            counter++;


        }







    }

    for(int i=1;i<49;i++)
    {
        for(int j=1;j<39;j++)
        {
          if(this->tpiksele[i][j].free_status==true)
          {
              x=i;
              y=j;
              this->tpiksele[x][j].free_status=false;

              this->tpiksele[x][y].Gwall=true;
              this->tpiksele[x][y-1].Dwall=true;

              this->tpiksele[x][y].Pwall=true;
              this->tpiksele[x+1][y].Lwall=true;

              this->tpiksele[x][y].Dwall=true;
              this->tpiksele[x][y+1].Gwall=true;

              this->tpiksele[x][y].Lwall=true;
              this->tpiksele[x-1][y].Pwall=true;

          }
        }
    }

}

bool Plansza:: isgame(){return this->game_status;}

void Plansza::tick()
{
if(!this->game_pause)
{
    this->czas++;
if(this->czas>100)
{
    this->Heads.push_back(&this->tlawa[1][1]);
    this->tlawa[1][1].free_status=false;
    if(this->czas%12==0)
    {
        this->iteracja=this->Heads.size()-wykonane;
                wykonane=add_Lawa(wykonane,this->iteracja);
    }
}
}
}




void Plansza:: rysuj_Siatka(QPainter *d)
{
    for(int i=0;i<50;i++)
        for(int j=0 ; j<40;j++)
        {

            if(this->tpiksele[i][j].free_status==true)
            {
                d->setBrush(Qt::white);
                d->drawEllipse(this->tpiksele[i][j].get_xpos(),this->tpiksele[i][j].get_ypos(),3,3);



            }
            else
            {
                d->setBrush(Qt::red);
                d->drawEllipse(this->tpiksele[i][j].xpos,this->tpiksele[i][j].ypos,3,3);
            }
        }
}

void Plansza::reset_Plansza()
{
    this->filled_status=false;
    for(int i=0;i<this->maximumWidth()/g->get_size()/2;i++)
        for(int j=0 ; j<this->maximumHeight()/2/g->get_size();j++)
        {
            this->tpiksele[i][j].xpos=g->get_size()+i*2*g->get_size();
            this->tpiksele[i][j].ypos=g->get_size()+j*2*g->get_size();
            this->tpiksele[i][j].size=g->get_size();
            this->tpiksele[i][j].free_status=true;
            this->tpiksele[i][j].Gwall=false;
            this->tpiksele[i][j].Dwall=false;
            this->tpiksele[i][j].Lwall=false;
            this->tpiksele[i][j].Pwall=false;
            this->tpiksele[i][j].xback=i;//do testow
            this->tpiksele[i][j].yback=j;//do testow
            this->tpiksele[i][j].error=false;
             this->tpiksele[i][j].finish=false;
            this->tpiksele[i][j].colored=false;


            this->ruchy=0;


            if(i==this->maximumWidth()/g->get_size()/2-2 && j==this->maximumHeight()/2/g->get_size()-2 ) this->tpiksele[i][j].finish=true;


        }
}

void Plansza:: reset_Lawa()
{
    for(int i=0;i<this->maximumWidth()/g->get_size()/2;i++)
        for(int j=0 ; j<this->maximumHeight()/2/g->get_size();j++)
        {
            this->tlawa[i][j].xpos=g->get_size()+i*2*g->get_size();
            this->tlawa[i][j].ypos=g->get_size()+j*2*g->get_size();
            this->tlawa[i][j].size=g->get_size();
            this->tlawa[i][j].free_status=true;
            this->tpiksele[i][j].xback=i;//do testow
            this->tpiksele[i][j].yback=j;//do testow
            this->tlawa[i][j].xplanszy=i;
            this->tlawa[i][j].yplanszy=j;
            this->wykonane=0;
            this->iteracja=0;
            this->Heads.clear();
            this->tlawa[i][j].colored=false;

        }





}

int Plansza:: add_Lawa(int wykonane, int dowykonania)//zalewanie
{
    int i=wykonane;
    for(int i;i<dowykonania;i++)
        {
          if(this->tpiksele[this->Heads.at(i)->xplanszy+1][this->Heads.at(i)->yplanszy].Lwall && this->tlawa[this->Heads.at(i)->xplanszy+1][this->Heads.at(i)->yplanszy].free_status)
          {
              tlawa[this->Heads.at(i)->xplanszy+1][this->Heads.at(i)->yplanszy].free_status=0;
              this->Heads.push_back(&this->tlawa[this->Heads.at(i)->xplanszy+1][this->Heads.at(i)->yplanszy]);
          }
          if(this->tpiksele[this->Heads.at(i)->xplanszy-1][this->Heads.at(i)->yplanszy].Pwall && this->tlawa[this->Heads.at(i)->xplanszy-1][this->Heads.at(i)->yplanszy].free_status)
          {
              tlawa[this->Heads.at(i)->xplanszy-1][this->Heads.at(i)->yplanszy].free_status=0;
              this->Heads.push_back(&this->tlawa[this->Heads.at(i)->xplanszy-1][this->Heads.at(i)->yplanszy]);
          }
          if(this->tpiksele[this->Heads.at(i)->xplanszy][this->Heads.at(i)->yplanszy+1].Gwall && this->tlawa[this->Heads.at(i)->xplanszy][this->Heads.at(i)->yplanszy+1].free_status)
          {
              tlawa[this->Heads.at(i)->xplanszy][this->Heads.at(i)->yplanszy+1].free_status=0;
              this->Heads.push_back(&this->tlawa[this->Heads.at(i)->xplanszy][this->Heads.at(i)->yplanszy+1]);
          }
          if(this->tpiksele[this->Heads.at(i)->xplanszy][this->Heads.at(i)->yplanszy-1].Dwall && this->tlawa[this->Heads.at(i)->xplanszy][this->Heads.at(i)->yplanszy-1].free_status)
          {
              tlawa[this->Heads.at(i)->xplanszy][this->Heads.at(i)->yplanszy-1].free_status=0;
              this->Heads.push_back(&this->tlawa[this->Heads.at(i)->xplanszy][this->Heads.at(i)->yplanszy-1]);
          }
        }
    return wykonane;


}
