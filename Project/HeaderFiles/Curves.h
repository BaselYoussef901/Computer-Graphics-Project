#ifndef CURVES_H
#define CURVES_H

#include "Curves.cpp"
bool valid(int,int,int,int,int,int);
void Curve_Hermite(HDC,Point,Point,Point,Point,COLORREF,int,int,int,int);
void Curve_Bezier(HDC,Point,Point,Point,Point,COLORREF,int,int,int,int);
void Curve_Hermite_Filling(HDC,int,int,int,int,COLORREF,bool);
void Curve_Bezier_Filling(HDC,int,int,int,int,COLORREF,bool);


struct Vector2
{
double x,y;
Vector2(double a=0,double b=0)
{
x=a; y=b;
}
};



void DrawCardinalSpline(HDC ,vector<Point> ,int ,double ,int );




#endif // CURVES_H
