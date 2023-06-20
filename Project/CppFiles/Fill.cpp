#include "struct.h"
typedef struct{
    int xleft;
    int xright;
} EdgeTable[1000];
struct EdgeRec{
    double x;
    double MinV;
    int Ymax;
    EdgeRec(double x=0.0,int Ymax=0,double MinV=0.0){
        this->x = x;
        this-> Ymax = Ymax;
        this->MinV = MinV;
    }
};
typedef list<EdgeRec> EdgeTable_NoN[1000];
///Fill Circle with Lines - Circles
void Fill_LCircle(HDC hdc,Point Center,int radius,int Quarter,COLORREF color){
    Circle_Direct(hdc,Center,radius,color);
    double Y = radius;
    double X = 0;
    Line_Filling_Circle(hdc,Center.x,Center.y,X,Y,Quarter,color);
    while(X<Y){
        X++;
        Y = sqrt(radius*radius - X*X);
        Line_Filling_Circle(hdc,Center.x,Center.y,round(X),round(Y),Quarter,color);
    }
}

void Fill_CCircle(HDC hdc,Point Center,int radius,int Quarter,COLORREF color){
    double r=0.0;
    Circle_Direct(hdc,Center,radius,color);
    while(r <= radius){
        double X = 0;
        double Y = r;
        double D = 1 - r;
        Circle_Filling_Circle(hdc, Center.x, Center.y, round(X), round(Y), Quarter, color);
        while (X < Y) {
            if (D < 0) {
                D += 2*X + 2;
            }else {
                D += 2*(X - Y) + 5;
                Y--;
            }
            X++;
            Circle_Filling_Circle(hdc, Center.x, Center.y, round(X), round(Y), Quarter, color);
        }
        r++;
    }
}




///Convex
void InitialTable(EdgeTable Table){
    for(int i=0; i<1000; i++){
        Table[i].xleft = INT_MAX;
        Table[i].xright = INT_MIN;
    }
}
void EdgeCoverPoints(Point p1,Point p2,EdgeTable Table){
    if(p1.y == p2.y)
        return;

    if(p1.y > p2.y)
        swap(p1,p2);

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    double InverseSlope = (double)dx/dy;
    double X = p1.x;
    int Y = p1.y;

    while(Y < p2.y){
        if(X < Table[Y].xleft)
            Table[Y].xleft = (int)ceil(X);
        if(X > Table[Y].xright)
            Table[Y].xright = (int)floor(X);
        Y++;
        X += InverseSlope;
    }
}
void Polygon_To_Table(vector<Point>points,int numOfPoints,EdgeTable Table){
    Point last_point = points[numOfPoints-1];
    for(int i=0; i<numOfPoints; i++){
        Point next_point = points[i];
        EdgeCoverPoints(last_point , next_point , Table);
        last_point = next_point;
    }
}
void draw_Polygon(HDC hdc,EdgeTable Table,COLORREF color=RGB(0,255,255)){
    for(int i=0; i<1000; i++){
        if(Table[i].xleft < Table[i].xright){
            //We can use a draw line or just iterate over each pixel
            //Line_direct(hdc,Table[i].xleft,i,Table[i].xright,i,color);
            for(int j=Table[i].xleft; j<=Table[i].xright; j++){
                SetPixel(hdc,j,i,color);
            }
        }
    }
}
void Fill_Polygon(HDC hdc,vector<Point>points,int numOfPolygons,COLORREF color=RGB(0,255,255)){
    EdgeTable Table;
    InitialTable(Table);
    Polygon_To_Table(points,numOfPolygons,Table);
    draw_Polygon(hdc,Table,color);
}
///Non-Convex
void EdgeCoverPoints_NoN(Point P1, Point P2,EdgeTable_NoN NoN_Table){
    if(P1.y == P2.y)
        return;

    if(P1.y > P2.y)
        swap(P1,P2);
    EdgeRec Edge_Rec(P1.x , P2.y , (double)(P2.x - P1.x)/(P2.y - P1.y));
    NoN_Table[P1.y].push_back(Edge_Rec);
}
void Polygon_To_NoN_Table(vector<Point>points,int numOfPoints,EdgeTable_NoN NoN_Table){
    Point last_point = points[numOfPoints-1];
    for(int i=0; i<numOfPoints; i++){
        Point next_point = points[i];
        EdgeCoverPoints_NoN(last_point , next_point , NoN_Table);
        last_point = next_point;
    }
}
void draw_NoN_Polygon(HDC hdc,EdgeTable_NoN NoN_Table,COLORREF color=RGB(0,255,255)){
    int Y = 0;
    list<EdgeRec>::iterator it;
    while(NoN_Table[Y].size() == 0)
        Y++;

    list<EdgeRec> ShownPolygon = NoN_Table[Y];
    while(ShownPolygon.size() != 0){
        ShownPolygon.sort([](EdgeRec &a,EdgeRec &b){return a.x < b.x;});    //Sort Points
        for(it=ShownPolygon.begin(); it!=ShownPolygon.end(); it++){
            EdgeRec &curr_edge = *it;
            it++;
            if(it == ShownPolygon.end())
                break;
            EdgeRec &next_edge = *it;
            Line_MIDPOINT_2(hdc, ceil(curr_edge.x) , Y, floor(next_edge.x), Y, color);
        }
        Y++;
        for(it=ShownPolygon.begin(); it!=ShownPolygon.end(); ){
            if(it->Ymax == Y)
                it = ShownPolygon.erase(it);
            else
                it++;
        }
        for(it = ShownPolygon.begin(); it!=ShownPolygon.end(); it++)
            it->x = it->x + it->MinV;
        if(NoN_Table[Y].size() != 0)
            ShownPolygon.splice(ShownPolygon.end() , NoN_Table[Y]);
    }
}
void Fill_NoN_Polygon(HDC hdc,vector<Point>points,int numOfPolygons,COLORREF color=RGB(0,255,255)){
    EdgeTable_NoN NoN_Table;
    Polygon_To_NoN_Table(points,numOfPolygons,NoN_Table);
    draw_NoN_Polygon(hdc,NoN_Table,color);
}














///Recursive
void Recursive_FloodFill(HDC hdc,int X,int Y,COLORREF back_color,COLORREF front_color){
    COLORREF color = GetPixel(hdc,X,Y);
    if(color == back_color || color == front_color)
        return;

    SetPixel(hdc,X,Y,front_color);
    Recursive_FloodFill(hdc, X+1, Y, back_color, front_color);
    Recursive_FloodFill(hdc, X, Y+1, back_color, front_color);
    Recursive_FloodFill(hdc, X-1, Y, back_color, front_color);
    Recursive_FloodFill(hdc, X, Y-1, back_color, front_color);
}
///Non-Recursive
struct Vertex{
    int x;
    int y;
    Vertex(int x=0,int y=0){
        this->x=x;
        this->y=y;
    }
};
void NoN_Recursive_FloodFill(HDC hdc,Point P,COLORREF back_color,COLORREF front_color){
    stack<Vertex> st;
    Vertex curr_vertex(P.x,P.y);
    st.push(curr_vertex);
    while(!st.empty()){
        Vertex last_vertex = st.top();
        st.pop();
        COLORREF color = GetPixel(hdc,last_vertex.x , last_vertex.y);
        if(color == back_color || color == front_color)
            continue;
        else{
            SetPixel(hdc,last_vertex.x,last_vertex.y,front_color);
            Vertex v1(last_vertex.x  ,  last_vertex.y+1);
            Vertex v2(last_vertex.x  ,  last_vertex.y-1);
            Vertex v3(last_vertex.x+1  ,  last_vertex.y);
            Vertex v4(last_vertex.x-1  ,  last_vertex.y);
            st.push(v1);
            st.push(v2);
            st.push(v3);
            st.push(v4);
        }
    }
}







