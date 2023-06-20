#include "Fill.h"

/**             Point-Clipping      **/
void Clipping_Point(HDC hdc,int X,int Y,int xleft,int ytop,int xright,int ybottom,COLORREF color){
    if(X>=xleft && X<=xright && Y>=ytop && Y<=ybottom){
        SetPixel(hdc,X,Y,color);
    }
}





/**             Line-Clipping       **/
union OutCode{
    unsigned All:4;
    struct{
        unsigned left:1 ,top:1, right:1, bottom:1;
    };
};
OutCode GetOutCode(double X,double Y,int xleft,int ytop,int xright,int ybottom){
    OutCode out;
    out.All = 0;
    if(X<xleft)     out.left = 1;
    if(X>xright)    out.right = 1;
    if(Y<ytop)      out.top = 1;
    if(Y>ybottom)   out.bottom = 1;
    return out;
}
void Line_Vertical_Intersect(double xStart,double yStart,double xEnd,double yEnd,int X,double *XI,double *YI){
    *XI = X;
    *YI = yStart + (X-xStart)*(yEnd-yStart)/(xEnd-xStart);
}
void Line_Horizontal_Intersect(double xStart,double yStart,double xEnd,double yEnd,int Y,double *XI,double *YI){
    *YI = Y;
    *XI = xStart + (Y-yStart)*(xEnd-xStart)/(yEnd-yStart);
}
void Clipping_CohenSuth(HDC hdc,int xStart,int yStart,int xEnd,int yEnd,int xleft,int ytop,int xright,int ybottom,COLORREF color){
    OutCode out1 = GetOutCode(xStart,yStart,xleft,ytop,xright,ybottom);
    OutCode out2 = GetOutCode(xEnd,yEnd,xleft,ytop,xright,ybottom);
    while( (out1.All || out2.All) && !(out1.All&out2.All) ){
        double XI , YI;
        if(out1.All){
            if(out1.left)       Line_Vertical_Intersect(xStart,yStart,xEnd,yEnd,xleft,&XI,&YI);
            else if(out1.top)   Line_Horizontal_Intersect(xStart,yStart,xEnd,yEnd,ytop,&XI,&YI);
            else if(out1.right) Line_Vertical_Intersect(xStart,yStart,xEnd,yEnd,xright,&XI,&YI);
            else                Line_Horizontal_Intersect(xStart,yStart,xEnd,yEnd,ybottom,&XI,&YI);

            xStart = XI;
            yStart = YI;
            out1 = GetOutCode(xStart,yStart,xleft,ytop,xright,ybottom);
        }else{
            if(out2.left)       Line_Vertical_Intersect(xStart,yStart,xEnd,yEnd,xleft,&XI,&YI);
            else if(out2.top)   Line_Horizontal_Intersect(xStart,yStart,xEnd,yEnd,ytop,&XI,&YI);
            else if(out2.right) Line_Vertical_Intersect(xStart,yStart,xEnd,yEnd,xright,&XI,&YI);
            else                Line_Horizontal_Intersect(xStart,yStart,xEnd,yEnd,ybottom,&XI,&YI);

            xEnd = XI;
            yEnd = YI;
            out2 = GetOutCode(xEnd,yEnd,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All){
        MoveToEx(hdc,xStart,yStart,NULL);
        LineTo(hdc,xEnd,yEnd);
    }
}










/**             Polygon-Clipping       **/
void Clipping_Polygon(HDC hdc,vector<Point>Points,int numOfPoints,int xleft,int ytop,int xright,int ybottom,COLORREF color){
    Point last_point = Points[numOfPoints-1];
    for(int i=0; i<numOfPoints; i++){
        Point curr_point = Points[i];
        Clipping_CohenSuth(hdc,last_point.x,last_point.y,curr_point.x,curr_point.y,xleft,ytop,xright,ybottom,color);
        last_point = curr_point;
    }
}










/***                Shapes          ***/
void Draw_Rectangle(HDC hdc,int left,int top,int right,int bottom, COLORREF color=RGB(0,0,0)){
    Line_MIDPOINT_2(hdc,left ,top   ,right,top   ,color);
    Line_MIDPOINT_2(hdc,left ,top   ,left ,bottom,color);
    Line_MIDPOINT_2(hdc,right,top   ,right,bottom,color);
    Line_MIDPOINT_2(hdc,left ,bottom,right,bottom,color);
}
void Draw_Square(HDC hdc,int &left,int &top,int &right,int &bottom, COLORREF color=RGB(0,0,0)){
    bottom = top + (right - left);

    Line_MIDPOINT_2(hdc,left ,top   ,right,top   ,color);
    Line_MIDPOINT_2(hdc,left ,top   ,left ,bottom,color);
    Line_MIDPOINT_2(hdc,right,top   ,right,bottom,color);
    Line_MIDPOINT_2(hdc,left ,bottom,right,bottom,color);
}
void Draw_Polygon(HDC hdc,vector<Point> Points,int numOfPoints,COLORREF color){
    Point last_point = Points[numOfPoints-1];
    for(int i=0; i<numOfPoints; i++){
        Point curr_point = Points[i];
        Line_MIDPOINT_2(hdc,last_point.x,last_point.y,curr_point.x,curr_point.y,color);
        last_point = curr_point;
    }
}

