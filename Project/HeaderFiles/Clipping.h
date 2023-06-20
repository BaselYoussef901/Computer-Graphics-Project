#ifndef CLIPPING_H
#define CLIPPING_H

#include "Clipping.cpp"


void Clipping_Point(HDC,int,int,int,int,int,int,COLORREF);

OutCode GetOutCode(double,double,int,int,int,int);
void Line_Vertical_Intersect(double,double,double,double,int,double,double);
void Line_Horizontal_Intersect(double,double,double,double,int,double,double);
void Clipping_CohenSuth(HDC,int,int,int,int,int,int,int,int,COLORREF);

void Clipping_Polygon(HDC,vector<Point>,int,int,int,int,int,COLORREF);





void Draw_Rectangle(HDC,int,int,int,int, COLORREF, Shape&);
void Draw_Square(HDC,int&,int&,int&,int&, COLORREF, Shape&);
void Draw_Polygon(HDC,vector<Point>,int,COLORREF);
#endif // CLIPPING_H
