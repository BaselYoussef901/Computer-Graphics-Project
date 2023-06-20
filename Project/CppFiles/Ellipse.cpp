
void Ellipse_Draw4(HDC hdc,int XC,int YC,int X,int Y,COLORREF color){
    SetPixel(hdc,XC+X,YC+Y,color);
    SetPixel(hdc,XC-X,YC+Y,color);
    SetPixel(hdc,XC+X,YC-Y,color);
    SetPixel(hdc,XC-X,YC-Y,color);
}

void Ellipse_Direct(HDC hdc,Point P1,Point P2,COLORREF color){
    int xCenter = P1.x;
    int yCenter = P1.y;
    int xEnd = P2.x;
    int yEnd = P2.y;

    double X = 0;
    double Y = yEnd;
    Ellipse_Draw4(hdc,xCenter,yCenter,X,Y,color);
    while(X*yEnd*yEnd < Y*xEnd*xEnd){
        X++;
        Y = yEnd * sqrt(1.0-(X*X)/(xEnd*xEnd));
        Ellipse_Draw4(hdc,xCenter,yCenter,round(X),round(Y),color);
    }
    X = xEnd;
    Y = 0;
    Ellipse_Draw4(hdc,xCenter,yCenter,X,Y,color);
    while(Y*xEnd*xEnd < X*yEnd*yEnd){
        Y++;
        X = xEnd * sqrt(1.0-(Y*Y)/(yEnd*yEnd));
        Ellipse_Draw4(hdc,xCenter,yCenter,round(X),round(Y),color);
    }
}
void Ellipse_Polar(HDC hdc,Point P1,Point P2,COLORREF color){
    int xCenter = P1.x;
    int yCenter = P1.y;
    int xEnd = P2.x;
    int yEnd = P2.y;

    if(xCenter > xEnd){
        swap(xCenter,xEnd);
        swap(yCenter,yEnd);
    }
    double theta = 0;
    int A = xEnd - xCenter;
    int B = yEnd - yCenter;
    double X=(double)A;
    double Y=0.0;
    double D_theta = 1.0/max(A,B);
    while(theta<90 || X>0){  //One condition is enough
        X =  A*cos(theta);
        Y =  B*sin(theta);
        theta+=D_theta;
        Ellipse_Draw4(hdc,xCenter,yCenter,round(X),round(Y),color);
    }
}
void Ellipse_MidPoint(HDC hdc,Point P1,Point P2,COLORREF color){
    int xCenter = P1.x;
    int yCenter = P1.y;
    int xEnd = P2.x;
    int yEnd = P2.y;


    int X = 0;
    int Y = yEnd;
    Ellipse_Draw4(hdc,xCenter,yCenter,X,Y,color);
    int D1 = 4*yEnd*yEnd - 4*yEnd*xEnd*xEnd + xEnd*xEnd;
    int C1 = 12*yEnd*yEnd;
    int C2 = 12*yEnd*yEnd + 8*xEnd*xEnd - 8*xEnd*xEnd*yEnd;
    int C1_Delta = 8*yEnd*yEnd;
    int C2_Delta = C1_Delta + 8*xEnd*xEnd;
    while(Y*xEnd*xEnd > X*yEnd*yEnd){
        if(D1<0){
            D1 += C1;
            C2 += C1_Delta;
        }else{
            D1 += C2;
            C2 += C2_Delta;
            Y--;
        }
        C1 += C1_Delta;
        X++;
        Ellipse_Draw4(hdc,xCenter,yCenter,X,Y,color);
    }


    X = xEnd;
    Y = 0;
    Ellipse_Draw4(hdc,xCenter,yCenter,X,Y,color);
    D1 = 4*xEnd*xEnd - 4*xEnd*yEnd*yEnd + yEnd*yEnd;
    C1 = 12*xEnd*xEnd;
    C2 = 12*xEnd*xEnd + 8*yEnd*yEnd - 8*yEnd*yEnd*xEnd;
    C1_Delta = 8*xEnd*xEnd;
    C2_Delta = C1_Delta + 8*yEnd*yEnd;
    while(X*yEnd*yEnd > Y*xEnd*xEnd){
        if(D1<0){
            D1 += C1;
            C2 += C1_Delta;
        }else{
            D1 += C2;
            C2 += C2_Delta;
            X--;
        }
        C1 += C1_Delta;
        Y++;
        Ellipse_Draw4(hdc,xCenter,yCenter,X,Y,color);
    }
}



void Ellipse_MidPoint_2(HDC hdc,Point P1,Point P2,COLORREF c){
    int xc = P1.x;
    int yc = P1.y;
    int xEnd = P2.x;
    int yEnd = P2.y;


    int x=0;
    int y=yEnd;
    Ellipse_Draw4(hdc,xc,yc,x,y,c);
    while(y*xEnd*xEnd>x*yEnd*yEnd)
    {
        int d = 4*yEnd*yEnd + 8*yEnd*yEnd*x + xEnd*xEnd - 4*xEnd*xEnd*y + 4*xEnd*xEnd*y*y + 4*yEnd*yEnd*x*x - 4*yEnd*yEnd*xEnd*xEnd;
        if(d<0)
            x++;
        else{
            x++;
            y--;
        }
        Ellipse_Draw4(hdc,xc,yc,x,y,c);
    }
    x=xEnd;
    y=0;
    Ellipse_Draw4(hdc,xc,yc,x,y,c);
    while(y*xEnd*xEnd<x*yEnd*yEnd){
        int d = 4*xEnd*xEnd + 8*xEnd*xEnd*y + yEnd*yEnd - 4*yEnd*yEnd*x + 4*yEnd*yEnd*x*x + 4*xEnd*xEnd*y*y - 4*xEnd*xEnd*yEnd*yEnd;
        if(d<0)
            y++;
        else{
            y++;
            x--;
        }
        Ellipse_Draw4(hdc,xc,yc,x,y,c);
    }
}

