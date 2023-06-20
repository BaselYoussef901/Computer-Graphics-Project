#ifndef CIRCLE_H
#define CIRCLE_H

#include "Circle.cpp"
void Thick_Circle           (HDC,int,int,int,int,COLORREF);
void Circle_Direct          (HDC,Point,double,COLORREF,bool,int);
void Circle_Polar           (HDC,Point,double,COLORREF,bool,int);
void Circle_IterativePolar  (HDC,Point,double,COLORREF,bool,int);
void Circle_MidPoint        (HDC,Point,double,COLORREF,bool,int);
void Circle_ModifiedMidPoint(HDC,Point,double,COLORREF,bool,int);
void Circle_Draw8           (HDC,int,int,int,int,COLORREF);
void Quarter_Conditions     (HDC,int,int,int,int,int,COLORREF);
#endif // CIRCLE_H
