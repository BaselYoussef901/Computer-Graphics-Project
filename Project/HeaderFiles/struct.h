#ifndef STRUCT_H
#define STRUCT_H
struct Point{
    int x,y;
    Point(int x=0,int y=0){
        this->x = x;
        this->y = y;
    }
};
struct Shape{
    int xleft,ytop,xright,ybottom;
    Shape(int a=0,int b=0,int c=0,int d=0){
        xleft = a;
        ytop = b;
        xright = c;
        ybottom = d;
    }
};
#endif // STRUCT_H
