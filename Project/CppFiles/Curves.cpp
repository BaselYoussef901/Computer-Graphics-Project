bool valid(int xx,int yy,int left,int top,int right,int bottom){
    return xx>left && xx<right && yy>top && yy<bottom;
}

void Curve_Hermite(HDC hdc,Point P1,Point T1,Point P2,Point T2,COLORREF color,int xleft=0,int ytop=0,int xright=800,int ybottom=800){
    double A0 = (double)P1.x;
    double A1 = (double)T1.x;
    double A2 = -3*(double)P1.x - 2*(double)T1.x + 3*(double)P2.x - (double)T2.x;
    double A3 = 2*(double)P1.x + (double)T1.x - 2*(double)P2.x + (double)T2.x;

    double B0 = (double)P1.y;
    double B1 = (double)T1.y;
    double B2 = -3*(double)P1.y - 2*(double)T1.y + 3*(double)P2.y - (double)T2.y;
    double B3 = 2*(double)P1.y + (double)T1.y - 2*(double)P2.y + (double)T2.y;

    for(double t=0; t<=1; t+=0.0001){
        double t2 = t*t;
        double t3 = t2*t;

        double X = A0 + A1*t + A2*t2 + A3*t3;
        double Y = B0 + B1*t + B2*t2 + B3*t3;
        if(valid(round(X),round(Y),xleft,ytop,xright,ybottom))
                SetPixel(hdc, round(X), round(Y), color);
    }
}

void Curve_Bezier(HDC hdc,Point p1,Point p2,Point p3,Point p4,COLORREF color,int xleft=0,int ytop=0,int xright=800,int ybottom=800){
    for(double t=0; t<=1; t+=0.0001){
        double Xu = (pow((1-t),3)*p1.x) + 3*(t*pow((1-t),2)*p2.x) + 3*((1-t)*pow(t,2)*p3.x) + (pow(t,3)*p4.x);
        double Yu = (pow((1-t),3)*p1.y) + 3*(t*pow((1-t),2)*p2.y) + 3*((1-t)*pow(t,2)*p3.y) + (pow(t,3)*p4.y);
        if(valid(round(Xu),round(Yu),xleft,ytop,xright,ybottom))
                SetPixel(hdc, round(Xu), round(Yu), color);
    }
}













void Curve_Hermite_Filling(HDC hdc,int xleft,int ytop,int xright,int ybottom,COLORREF color,bool Up_Down=true){
    if(Up_Down){
        int radius = abs(xright-xleft);
        int UpToDown = abs(ytop-ybottom) + 0.5*ybottom;    //Gives it more down valid position
        Point P1(xleft,ytop - 0.25*ytop);
        Point T1(xleft + radius/3 + 0.19*xright , ytop);    //shifting point 2 - a little
        Point P2(xleft + 2*radius/3 + 0.20*xright , ytop);  //shifting point 3 - a little
        Point T2(xright , ytop + 0.50*ybottom);             //Gives it more curveness
        while(UpToDown > 0){
            Curve_Hermite(hdc,P1,T1,P2,T1,color,xleft,ytop,xright,ybottom);

            UpToDown--;
            P1.y++;
            T1.y++;
            P2.y++;
            T2.y++;
        }

    }else{
        int radius = abs(xright-xleft);
        int LeftToRight = abs(ytop-ybottom);
        Point P1(xleft, ytop);
        Point T1(xleft, ytop + radius/3);
        Point P2(xleft, ytop + 2*radius/3);
        Point T2(xleft, ybottom);
        while(LeftToRight > 0){
            Curve_Hermite(hdc,P1,T1,P2,T1,color,xleft,ytop,xright,ybottom);

            LeftToRight--;
            P1.x++;
            T1.x++;
            P2.x++;
            T2.x++;
        }
    }
}






void Curve_Bezier_Filling(HDC hdc,int xleft,int ytop,int xright,int ybottom,COLORREF color,bool Up_Down=false){
    if(Up_Down){
        int radius = abs(xright-xleft);
        int UpToDown = abs(ytop-ybottom);
        Point P1(xleft,ytop);
        Point P2(xleft + radius/3  , ytop);
        Point P3(xleft + 2*radius/3  , ytop);
        Point P4(xright , ytop);
        while(UpToDown>0){
            Curve_Bezier(hdc,P1,P2,P3,P4,color,xleft,ytop,xright,ybottom);

            UpToDown--;
            P1.y++;
            P2.y++;
            P3.y++;
            P4.y++;
        }
    }else{
        int radius = abs(ybottom - ytop);
        int LeftToRight = abs(xright - xleft);
        Point P1(xleft, ytop);
        Point P2(xleft, ytop + radius/3);
        Point P3(xleft, ytop + 2*radius/3);
        Point P4(xleft, ybottom);
        while(LeftToRight>0){
            Curve_Bezier(hdc,P1,P2,P3,P4,color,xleft,ytop,xright,ybottom);

            LeftToRight--;
            P1.x++;
            P2.x++;
            P3.x++;
            P4.x++;
        }
    }
}







///     >>> Cardinal Spline Curve


void DrawCardinalSpline(HDC hdc,vector<Point>P,int n,double c,int numpix)
{
    double c1=1-c;
    Point T0(c1*(P[2].x-P[0].x),c1*(P[2].y-P[0].y));
    for(int i=2;i<n-1;i++)
    {
        Point T1(c1*(P[i+1].x-P[i-1].x),c1*(P[i+1].y-P[i-1].y));
        Curve_Hermite(hdc,P[i-1],T0,P[i],T1,numpix);
        T0=T1;
    }
}
