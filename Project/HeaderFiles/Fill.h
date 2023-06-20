#ifndef FILL_H
#define FILL_H

#include "Fill.cpp"
#include "Line.h"
void Fill_Circle(HDC,Point,int,int,COLORREF,bool);
void Fill_Draw8(HDC,int,int,int,int,COLORREF);



///Convex
void InitialTable(EdgeTable);
void EdgeCoverPoints(Point,Point,EdgeTable);
void Polygon_To_Table(vector<Point>,int,EdgeTable);
void draw_Polygon(HDC,EdgeTable,COLORREF);
void Fill_Polygon(HDC,vector<Point>,int,COLORREF);
///Non-Convex
void EdgeCoverPoints_NoN(Point , Point ,EdgeTable_NoN );
void Polygon_To_NoN_Table(vector<Point>,int ,EdgeTable_NoN);
void draw_NoN_Polygon(HDC,EdgeTable_NoN,COLORREF);
void Fill_NoN_Polygon(HDC,vector<Point>,int,COLORREF);

///Recursive
void Recursive_FloodFill(HDC,Point,COLORREF,COLORREF);
///NoN-Recursive
void NoN_Recursive_FloodFill(HDC,Point,COLORREF,COLORREF);



#endif // FILL_H
