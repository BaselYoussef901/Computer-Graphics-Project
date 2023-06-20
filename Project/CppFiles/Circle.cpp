#include "struct.h"
void Circle_Draw8(HDC hdc, int XC, int YC, int X, int Y,COLORREF color) {
	SetPixel(hdc, XC + X, YC + Y, color);
	SetPixel(hdc, XC - X, YC + Y, color);
	SetPixel(hdc, XC + X, YC - Y, color);
	SetPixel(hdc, XC - X, YC - Y, color);

	SetPixel(hdc, XC + Y, YC + X, color);
	SetPixel(hdc, XC - Y, YC + X, color);
	SetPixel(hdc, XC + Y, YC - X, color);
	SetPixel(hdc, XC - Y, YC - X, color);
}
void Thick_Circle(HDC hdc,int XC,int YC,int X,int Y,COLORREF color){
    ////{8 Condition -> each condition has 8 points (64 condition)
    ///XC+X     YC+Y
    SetPixel(hdc, XC+X+1  ,  YC+Y+1  ,  color);
    SetPixel(hdc, XC+X-1  ,  YC+Y-1  ,  color);
    SetPixel(hdc, XC+X+1  ,  YC+Y-1  ,  color);
    SetPixel(hdc, XC+X-1  ,  YC+Y+1  ,  color);
    SetPixel(hdc, XC+X+1  ,  YC+Y+0  ,  color);
    SetPixel(hdc, XC+X+0  ,  YC+Y+1  ,  color);
    SetPixel(hdc, XC+X-1  ,  YC+Y+0  ,  color);
    SetPixel(hdc, XC+X+0  ,  YC+Y-1  ,  color);
    ///XC-X     YC-Y
    SetPixel(hdc, XC-X+1  ,  YC-Y+1  ,  color);
    SetPixel(hdc, XC-X-1  ,  YC-Y-1  ,  color);
    SetPixel(hdc, XC-X+1  ,  YC-Y-1  ,  color);
    SetPixel(hdc, XC-X-1  ,  YC-Y+1  ,  color);
    SetPixel(hdc, XC-X+1  ,  YC-Y+0  ,  color);
    SetPixel(hdc, XC-X+0  ,  YC-Y+1  ,  color);
    SetPixel(hdc, XC-X-1  ,  YC-Y+0  ,  color);
    SetPixel(hdc, XC-X+0  ,  YC-Y-1  ,  color);
    ///XC+X     YC-Y
    SetPixel(hdc, XC+X+1  ,  YC-Y+1  ,  color);
    SetPixel(hdc, XC+X-1  ,  YC-Y-1  ,  color);
    SetPixel(hdc, XC+X+1  ,  YC-Y-1  ,  color);
    SetPixel(hdc, XC+X-1  ,  YC-Y+1  ,  color);
    SetPixel(hdc, XC+X+1  ,  YC-Y+0  ,  color);
    SetPixel(hdc, XC+X+0  ,  YC-Y+1  ,  color);
    SetPixel(hdc, XC+X-1  ,  YC-Y+0  ,  color);
    SetPixel(hdc, XC+X+0  ,  YC-Y-1  ,  color);
    ///XC-X     YC+Y
    SetPixel(hdc, XC-X+1  ,  YC+Y+1  ,  color);
    SetPixel(hdc, XC-X-1  ,  YC+Y-1  ,  color);
    SetPixel(hdc, XC-X+1  ,  YC+Y-1  ,  color);
    SetPixel(hdc, XC-X-1  ,  YC+Y+1  ,  color);
    SetPixel(hdc, XC-X+1  ,  YC+Y+0  ,  color);
    SetPixel(hdc, XC-X+0  ,  YC+Y+1  ,  color);
    SetPixel(hdc, XC-X-1  ,  YC+Y+0  ,  color);
    SetPixel(hdc, XC-X+0  ,  YC+Y-1  ,  color);

    /**Same as up (but switch Y with X and vice versa).**/

    ///XC+Y     YC+X
    SetPixel(hdc, XC+Y+1  ,  YC+X+1  ,  color);
    SetPixel(hdc, XC+Y-1  ,  YC+X-1  ,  color);
    SetPixel(hdc, XC+Y+1  ,  YC+X-1  ,  color);
    SetPixel(hdc, XC+Y-1  ,  YC+X+1  ,  color);
    SetPixel(hdc, XC+Y+1  ,  YC+X+0  ,  color);
    SetPixel(hdc, XC+Y+0  ,  YC+X+1  ,  color);
    SetPixel(hdc, XC+Y-1  ,  YC+X+0  ,  color);
    SetPixel(hdc, XC+Y+0  ,  YC+X-1  ,  color);
    ///XC-Y     YC-X
    SetPixel(hdc, XC-Y+1  ,  YC-X+1  ,  color);
    SetPixel(hdc, XC-Y-1  ,  YC-X-1  ,  color);
    SetPixel(hdc, XC-Y+1  ,  YC-X-1  ,  color);
    SetPixel(hdc, XC-Y-1  ,  YC-X+1  ,  color);
    SetPixel(hdc, XC-Y+1  ,  YC-X+0  ,  color);
    SetPixel(hdc, XC-Y+0  ,  YC-X+1  ,  color);
    SetPixel(hdc, XC-Y-1  ,  YC-X+0  ,  color);
    SetPixel(hdc, XC-Y+0  ,  YC-X-1  ,  color);
    ///XC+Y     YC-X
    SetPixel(hdc, XC+Y+1  ,  YC-X+1  ,  color);
    SetPixel(hdc, XC+Y-1  ,  YC-X-1  ,  color);
    SetPixel(hdc, XC+Y+1  ,  YC-X-1  ,  color);
    SetPixel(hdc, XC+Y-1  ,  YC-X+1  ,  color);
    SetPixel(hdc, XC+Y+1  ,  YC-X+0  ,  color);
    SetPixel(hdc, XC+Y+0  ,  YC-X+1  ,  color);
    SetPixel(hdc, XC+Y-1  ,  YC-X+0  ,  color);
    SetPixel(hdc, XC+Y+0  ,  YC-X-1  ,  color);
    ///XC-Y     YC+X
    SetPixel(hdc, XC-Y+1  ,  YC+X+1  ,  color);
    SetPixel(hdc, XC-Y-1  ,  YC+X-1  ,  color);
    SetPixel(hdc, XC-Y+1  ,  YC+X-1  ,  color);
    SetPixel(hdc, XC-Y-1  ,  YC+X+1  ,  color);
    SetPixel(hdc, XC-Y+1  ,  YC+X+0  ,  color);
    SetPixel(hdc, XC-Y+0  ,  YC+X+1  ,  color);
    SetPixel(hdc, XC-Y-1  ,  YC+X+0  ,  color);
    SetPixel(hdc, XC-Y+0  ,  YC+X-1  ,  color);
}
void Circle_Direct(HDC hdc, Point Center,double raduis,COLORREF color,bool thick=false,int spaced=0){
    //Circle Equation:
    double Y = raduis;
    double X = 0;
    Circle_Draw8(hdc,Center.x,Center.y,X,Y,color);
    bool switched = false;
    while(X<Y){
        if(spaced != 0){
            if(switched){
                for(int i=0; i<spaced; i++)
                    X++;
                switched = !switched;
            }else{
                for(int i=0; i<spaced; i++){
                    X++;
                    Y = sqrt(raduis*raduis - X*X);
                    Circle_Draw8(hdc,Center.x,Center.y,round(X),round(Y),color);
                    if(thick){
                        Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
                    }
                }
                switched = !switched;
            }
        }else{
            X++;
            Y = sqrt(raduis*raduis - X*X);
            Circle_Draw8(hdc,Center.x,Center.y,round(X),round(Y),color);
            if(thick){
                Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
            }
        }
    }
}
void Circle_Polar(HDC hdc, Point Center,double raduis,COLORREF color,bool thick=false,int spaced=0){
    double X = raduis;
    double Y = 0;
    double theta=0;
    double D_theta=1.0/raduis;
    Circle_Draw8(hdc,Center.x,Center.y,round(X),round(Y),color);
    bool switched = false;
    while(X>Y){
        if(spaced != 0){
            if(switched){
                for(int i=0; i<spaced; i++){
                    theta += D_theta;
                    X = raduis * cos(theta);
                    Y = raduis * sin(theta);
                }
                switched = !switched;
            }else{
                for(int i=0; i<spaced; i++){
                    theta += D_theta;
                    X = raduis * cos(theta);
                    Y = raduis * sin(theta);
                    Circle_Draw8(hdc,Center.x,Center.y,round(X),round(Y),color);
                    if(thick)
                        Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
                }
                switched = !switched;
            }
        }else{
            theta += D_theta;
            X = raduis * cos(theta);
            Y = raduis * sin(theta);
            Circle_Draw8(hdc,Center.x,Center.y,round(X),round(Y),color);
            if(thick)
                Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
        }
    }
}
void Circle_IterativePolar(HDC hdc, Point Center,double raduis,COLORREF color,bool thick=false,int spaced=0){
    double D_theta = 1.0/raduis;
    double cD_theta = cos(D_theta);
    double sD_theta = sin(D_theta);

    double X = 0;
    double Y = raduis;
    Circle_Draw8(hdc,Center.x,Center.y,round(X),round(Y),color);
    bool switched = false;
    while(X<Y){
        if(spaced != 0){
            if(switched){
                for(int i=0; i<spaced; i++){
                    Y = X*sD_theta + Y*cD_theta;
                    X = X*cD_theta - Y*sD_theta;
                    if(X >= Y)  break;
                }
                switched = !switched;
            }else{
                for(int i=0; i<spaced; i++){
                    Y = X*sD_theta + Y*cD_theta;
                    X = X*cD_theta - Y*sD_theta;
                    Circle_Draw8(hdc,Center.x,Center.y,round(X),round(Y),color);
                    if(thick)
                        Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
                    if(X >= Y)  break;
                }
                switched = !switched;
            }
        }else{
            Y = X*sD_theta + Y*cD_theta;
            X = X*cD_theta - Y*sD_theta;
            Circle_Draw8(hdc,Center.x,Center.y,round(X),round(Y),color);
            if(thick)
                Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
        }
    }
}
void Circle_MidPoint(HDC hdc,Point Center,double raduis,COLORREF color,bool thick=false,int spaced=0){
    double X = 0;
	double Y = raduis;
	double D = 1 - raduis;
	Circle_Draw8(hdc, Center.x, Center.y, round(X), round(Y), color);
	bool switched = false;
	while (X < Y) {
        if(spaced != 0){
            if(switched){
                for(int i=0; i<spaced; i++){
                    if (D < 0) {
                        D += 2*X + 2;
                    }else {
                        D += 2*(X - Y) + 5;
                        Y--;
                    }
                    X++;
                }
                switched = !switched;
            }else{
                for(int i=0; i<spaced; i++){
                    if (D < 0) {
                        D += 2*X + 2;
                    }else {
                        D += 2*(X - Y) + 5;
                        Y--;
                    }
                    X++;
                    Circle_Draw8(hdc, Center.x, Center.y, round(X), round(Y), color);
                    if(thick)
                        Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
                }
                switched = !switched;
            }
        }else{
            if (D < 0) {
                D += 2*X + 2;
            }else {
                D += 2*(X - Y) + 5;
                Y--;
            }
            X++;
            Circle_Draw8(hdc, Center.x, Center.y, round(X), round(Y), color);
            if(thick)
                Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
        }
    }
}
void Circle_ModifiedMidPoint(HDC hdc, Point Center,double raduis,COLORREF color,bool thick=false,int spaced=0){
    double X = 0;
    double Y = raduis;
    double D = 1 - raduis;
    double D1 = 3;
    double D2 = 5 - 2*raduis;
    Circle_Draw8(hdc, Center.x, Center.y, round(X), round(Y), color);
    bool switched = false;
    while(X<Y){
        if(spaced != 0){
            if(switched){
                for(int i=0; i<spaced; i++){
                    if(D < 0){
                        D += D1;
                        D2 += 2;
                    }else{
                        D += D2;
                        D2 += 4;
                        Y--;
                    }
                    D1 += 2;
                    X++;
                }
                switched = !switched;
            }else{
                for(int i=0; i<spaced; i++){
                    if(D < 0){
                        D += D1;
                        D2 += 2;
                    }else{
                        D += D2;
                        D2 += 4;
                        Y--;
                    }
                    D1 += 2;
                    X++;
                    Circle_Draw8(hdc, Center.x, Center.y, round(X), round(Y), color);
                    if(thick)
                        Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
                }
                switched = !switched;
            }

        }else{
            if(D < 0){
                D += D1;
                D2 += 2;
            }else{
                D += D2;
                D2 += 4;
                Y--;
            }
            D1 += 2;
            X++;
            Circle_Draw8(hdc, Center.x, Center.y, round(X), round(Y), color);
            if(thick)
                Thick_Circle(hdc,Center.x,Center.y,round(X),round(Y),color);
        }
    }
}

void Circle_Filling_Circle(HDC hdc,int XC,int YC,int X,int Y,int Quarter,COLORREF color){
    if(Quarter == 1){
        SetPixel(hdc, XC+X , YC-Y, color);
        SetPixel(hdc, XC+Y , YC-X, color);
    }
    if(Quarter == 2){
        SetPixel(hdc, XC-X , YC-Y, color);
        SetPixel(hdc, XC-Y , YC-X, color);
    }
    if(Quarter == 3){
        SetPixel(hdc, XC-X , YC+Y, color);
        SetPixel(hdc, XC-Y , YC+X, color);
    }
    if(Quarter == 4){
        SetPixel(hdc, XC+X , YC+Y, color);
        SetPixel(hdc, XC+Y , YC+X, color);
    }
}

