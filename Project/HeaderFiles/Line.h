#ifndef LINE_H
#define LINE_H

#include "Line.cpp"
void Line_DDA       (HDC,Point,Point,COLORREF);
void Line_MIDPOINT  (HDC,Point,Point,COLORREF);
void Line_MIDPOINT_2(HDC,Point,Point,COLORREF);
void Line_PARAMETRIC(HDC,Point,Point,COLORREF);
void Line_Filling_Circle(HDC,int,int,int,int,COLORREF,bool);

#endif // LINE_H
