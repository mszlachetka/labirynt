#include "pole.h"
#include <QPainter>
#include <string>
using namespace std;

Pole::Pole(QWidget *parent): QWidget(parent)
{
}
int Pole:: get_xback() {return this->xback;}
int Pole:: get_yback() {return this->yback;}
int Pole:: get_xpos(){return this->xpos;}
int Pole:: get_ypos() {return this->ypos;}
int Pole:: get_size() {return this->size;}
bool Pole:: is_free() {return this->free_status;}
void Pole::set_xpos(int i) {this->xpos=i;}
void Pole::set_ypos(int i) {this->ypos=i;}
void Pole::set_size(int i) {this->size=i;}
void  Pole::set_xback(int i) {this->xback=i;}
void  Pole::set_yback(int i) {this->yback=i;}



