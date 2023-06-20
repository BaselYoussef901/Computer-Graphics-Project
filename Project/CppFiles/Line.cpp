#include "struct.h"
void Line_DDA(HDC hdc,Point P1, Point P2, COLORREF color=RGB(0,0,255),bool thick=false,int spaced=0){
    int xStart = P1.x;
    int yStart = P1.y;
    int xEnd = P2.x;
    int yEnd = P2.y;

    int dx = xEnd-xStart;
    int dy = yEnd-yStart;
    SetPixel(hdc,xStart,yStart,color);
    if(abs(dx) >= abs(dy)){
        int form = 0;
        if(xStart > xEnd){
            swap(xStart,xEnd);
            swap(yStart,yEnd);
        }
        int X = xStart;
        double Y = yStart;
        double D2 = (double)dy/dx;

        bool switched = false;
        while(xEnd > X){
            if(spaced != 0){
                if(switched){
                    for(int i=0; i<spaced; i++){
                        X += 1;
                        Y += D2;
                    }
                    switched = !switched;
                }else{
                    for(int i=0; i<spaced; i++){
                        X += 1;
                        Y += D2;
                        SetPixel(hdc,X,round(Y),color);
                        if(thick){
                            SetPixel(hdc,X+1,round(Y)+1,color);
                            SetPixel(hdc,X-1,round(Y)-1,color);
                            SetPixel(hdc,X+1,round(Y)-1,color);
                            SetPixel(hdc,X-1,round(Y)+1,color);

                            SetPixel(hdc,X,round(Y)+1,color);
                            SetPixel(hdc,X+1,round(Y),color);
                            SetPixel(hdc,X,round(Y)-1,color);
                            SetPixel(hdc,X-1,round(Y),color);
                        }
                    }
                    switched = !switched;
                }
            }
            else{
                X += 1;
                Y += D2;
                SetPixel(hdc,X,round(Y),color);
                if(thick){
                    SetPixel(hdc,X+1,round(Y)+1,color);
                    SetPixel(hdc,X-1,round(Y)-1,color);
                    SetPixel(hdc,X+1,round(Y)-1,color);
                    SetPixel(hdc,X-1,round(Y)+1,color);

                    SetPixel(hdc,X,round(Y)+1,color);
                    SetPixel(hdc,X+1,round(Y),color);
                    SetPixel(hdc,X,round(Y)-1,color);
                    SetPixel(hdc,X-1,round(Y),color);
                }
            }
        }
    }
    else{
        if(yStart > yEnd){
            swap(yStart,yEnd);
            swap(xStart,xEnd);
        }
        double X = xStart;
        int Y = yStart;
        double D2 = (double)dx/dy;

        bool switched = false;
        while(yEnd > Y){
            if(spaced != 0){
                if(switched){
                    for(int i=0; i<spaced; i++){
                        Y += 1;
                        X += D2;
                    }
                    switched = !switched;
                }else{
                    for(int i=0; i<spaced; i++){
                        Y += 1;
                        X += D2;
                        SetPixel(hdc,X,round(Y),color);
                        if(thick){
                            SetPixel(hdc,X+1,round(Y)+1,color);
                            SetPixel(hdc,X-1,round(Y)-1,color);
                            SetPixel(hdc,X+1,round(Y)-1,color);
                            SetPixel(hdc,X-1,round(Y)+1,color);

                            SetPixel(hdc,X,round(Y)+1,color);
                            SetPixel(hdc,X+1,round(Y),color);
                            SetPixel(hdc,X,round(Y)-1,color);
                            SetPixel(hdc,X-1,round(Y),color);
                        }
                    }
                    switched = !switched;
                }
            }else{
                Y += 1;
                X += D2;
                SetPixel(hdc,X,round(Y),color);
                if(thick){
                    SetPixel(hdc,X+1,round(Y)+1,color);
                    SetPixel(hdc,X-1,round(Y)-1,color);
                    SetPixel(hdc,X+1,round(Y)-1,color);
                    SetPixel(hdc,X-1,round(Y)+1,color);

                    SetPixel(hdc,X,round(Y)+1,color);
                    SetPixel(hdc,X+1,round(Y),color);
                    SetPixel(hdc,X,round(Y)-1,color);
                    SetPixel(hdc,X-1,round(Y),color);
                }
            }
        }
    }
}
void Line_MIDPOINT_2(HDC hdc, int xStart,int yStart,int xEnd,int yEnd, COLORREF color) {
	///Known as Bresenham Algorithm
	int Dx = abs(xEnd - xStart);
	int Dy = abs(yEnd - yStart);
	int X = xStart;
	int Y = yStart;
	int D = Dx - Dy;
	SetPixel(hdc, X, Y, color);
	while (X != xEnd || Y != yEnd) {
		int D2 = 2 * D;
		if (D2 > -Dy) {
			D -= Dy;
			if (xStart < xEnd)
				X++;
			else
				X--;
		}
		if (D2 < Dx) {
			D += Dx;
			if (yStart < yEnd)
				Y++;
			else
				Y--;
		}
		SetPixel(hdc, X, Y, color);
	}
}
void Line_MIDPOINT(HDC hdc,Point P1, Point P2,COLORREF color=RGB(0,0,255),bool thick=false,int spaced=0){
    int xStart = P1.x;
    int yStart = P1.y;
    int xEnd = P2.x;
    int yEnd = P2.y;


    int dx = xEnd - xStart;
    int dy = yEnd - yStart;
    SetPixel(hdc,xStart,yStart,color);
    int X = xStart;
    int Y = yStart;
    //Mid Point has 4 Cases
    ///Slope -> ]1:inf[
    ///Slope -> [0:1]
    ///Slope -> [-1:0[
    ///Slope -> ]-inf:-1[
    double Slope = (double)dy/dx;
    if(Slope>1 || dx==0){               // ]1:inf[
        if(dy>=0 && dx>0){
            int D  = 2*dx - dy;
            int D1 = 2*dx;
            int D2 = 2*dx - 2*dy;
            bool switched = false;
            while(Y != yEnd){
                if(spaced != 0){
                    if(switched){
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                Y++ , D += D1;
                            else
                                X++ , Y++ , D += D2;


                            if(Y == yEnd)   break;
                        }
                        switched = !switched;
                    }
                    else{
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                Y++ , D += D1;
                            else
                                X++ , Y++ , D += D2;
                            SetPixel(hdc,X,Y,color);
                            if(thick){
                                SetPixel(hdc,X+1,Y+1,color);
                                SetPixel(hdc,X-1,Y-1,color);
                                SetPixel(hdc,X+1,Y-1,color);
                                SetPixel(hdc,X-1,Y+1,color);

                                SetPixel(hdc,X  ,Y+1,color);
                                SetPixel(hdc,X+1,Y  ,color);
                                SetPixel(hdc,X  ,Y-1,color);
                                SetPixel(hdc,X-1,Y  ,color);
                            }

                            if(Y == yEnd)   break;
                        }
                        switched = !switched;
                    }
                }else{
                    if(D <= 0)
                        Y++ , D += D1;
                    else
                        X++ , Y++ , D += D2;
                    SetPixel(hdc,X,Y,color);
                    if(thick){
                        SetPixel(hdc,X+1,Y+1,color);
                        SetPixel(hdc,X-1,Y-1,color);
                        SetPixel(hdc,X+1,Y-1,color);
                        SetPixel(hdc,X-1,Y+1,color);

                        SetPixel(hdc,X  ,Y+1,color);
                        SetPixel(hdc,X+1,Y  ,color);
                        SetPixel(hdc,X  ,Y-1,color);
                        SetPixel(hdc,X-1,Y  ,color);
                    }
                }
            }
        }
        else{
            int D  = -2*dx + dy;
            int D1 = -2*dx;
            int D2 = -2*dx + 2*dy;
            bool switched = false;
            while(Y != yEnd){
                if(spaced != 0){
                    if(switched){
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                Y-- , D += D1;
                            else
                                Y-- , X-- , D += D2;

                            if(Y == yEnd)   break;
                        }
                        switched = !switched;
                    }else{
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                Y-- , D += D1;
                            else
                                Y-- , X-- , D += D2;
                            SetPixel(hdc,X,Y,color);
                            if(thick){
                                SetPixel(hdc,X+1,Y+1,color);
                                SetPixel(hdc,X-1,Y-1,color);
                                SetPixel(hdc,X+1,Y-1,color);
                                SetPixel(hdc,X-1,Y+1,color);

                                SetPixel(hdc,X  ,Y+1,color);
                                SetPixel(hdc,X+1,Y  ,color);
                                SetPixel(hdc,X  ,Y-1,color);
                                SetPixel(hdc,X-1,Y  ,color);
                            }
                            if(Y == yEnd)   break;
                        }
                        switched = !switched;
                    }
                }else{
                    if(D <= 0)
                        Y-- , D += D1;
                    else
                        Y-- , X-- , D += D2;
                    SetPixel(hdc,X,Y,color);
                    if(thick){
                        SetPixel(hdc,X+1,Y+1,color);
                        SetPixel(hdc,X-1,Y-1,color);
                        SetPixel(hdc,X+1,Y-1,color);
                        SetPixel(hdc,X-1,Y+1,color);

                        SetPixel(hdc,X  ,Y+1,color);
                        SetPixel(hdc,X+1,Y  ,color);
                        SetPixel(hdc,X  ,Y-1,color);
                        SetPixel(hdc,X-1,Y  ,color);
                    }
                }
            }
        }
    }









    else if(Slope<=1 && Slope>=0){     // [0:1]
        if(dy>=0 && dx>0){
            int D  = dx-2*dy;
            int D1 = -2*dy;
            int D2 = 2*dx - 2*dy;
            bool switched = false;
            while(X != xEnd){
                if(spaced != 0){
                    if(switched){
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X++ , Y++ , D += D2;
                            else
                                X++ , D += D1;

                            if(X == xEnd)   break;
                        }
                        switched = !switched;
                    }else{
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X++ , Y++ , D += D2;
                            else
                                X++ , D += D1;
                            SetPixel(hdc,X,Y,color);
                            if(thick){
                                SetPixel(hdc,X+1,Y+1,color);
                                SetPixel(hdc,X-1,Y-1,color);
                                SetPixel(hdc,X+1,Y-1,color);
                                SetPixel(hdc,X-1,Y+1,color);

                                SetPixel(hdc,X  ,Y+1,color);
                                SetPixel(hdc,X+1,Y  ,color);
                                SetPixel(hdc,X  ,Y-1,color);
                                SetPixel(hdc,X-1,Y  ,color);
                            }
                            if(X == xEnd)   break;
                        }
                        switched = !switched;
                    }
                }else{
                    if(D <= 0)
                        X++ , Y++ , D += D2;
                    else
                        X++ , D += D1;
                    SetPixel(hdc,X,Y,color);
                    if(thick){
                        SetPixel(hdc,X+1,Y+1,color);
                        SetPixel(hdc,X-1,Y-1,color);
                        SetPixel(hdc,X+1,Y-1,color);
                        SetPixel(hdc,X-1,Y+1,color);

                        SetPixel(hdc,X  ,Y+1,color);
                        SetPixel(hdc,X+1,Y  ,color);
                        SetPixel(hdc,X  ,Y-1,color);
                        SetPixel(hdc,X-1,Y  ,color);
                    }
                }
            }
        }
        else{
            int D  = -dx + 2*dy;
            int D1 = 2*dy;
            int D2 = -2*dx + 2*dy;
            bool switched = false;
            while(X != xEnd){
                if(spaced != 0){
                    if(switched){
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                Y-- , X-- , D += D2;
                            else
                                X-- , D += D1;

                            if(X == xEnd)   break;
                        }
                        switched = !switched;
                    }else{
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                Y-- , X-- , D += D2;
                            else
                                X-- , D += D1;
                            SetPixel(hdc,X,Y,color);
                            if(thick){
                                SetPixel(hdc,X+1,Y+1,color);
                                SetPixel(hdc,X-1,Y-1,color);
                                SetPixel(hdc,X+1,Y-1,color);
                                SetPixel(hdc,X-1,Y+1,color);

                                SetPixel(hdc,X  ,Y+1,color);
                                SetPixel(hdc,X+1,Y  ,color);
                                SetPixel(hdc,X  ,Y-1,color);
                                SetPixel(hdc,X-1,Y  ,color);
                            }
                            if(X == xEnd)   break;
                        }
                        switched = !switched;
                    }
                }else{
                    if(D <= 0)
                        Y-- , X-- , D += D2;
                    else
                        X-- , D += D1;
                    SetPixel(hdc,X,Y,color);
                    if(thick){
                        SetPixel(hdc,X+1,Y+1,color);
                        SetPixel(hdc,X-1,Y-1,color);
                        SetPixel(hdc,X+1,Y-1,color);
                        SetPixel(hdc,X-1,Y+1,color);

                        SetPixel(hdc,X  ,Y+1,color);
                        SetPixel(hdc,X+1,Y  ,color);
                        SetPixel(hdc,X  ,Y-1,color);
                        SetPixel(hdc,X-1,Y  ,color);
                    }
                }
            }
        }
    }











    else if(Slope<0 && Slope>=-1){     //[-1:0[
        if(dx>0 && dy<=0){
            int D  = -dx - 2*dy;
            int D1 = -2*dy;
            int D2 = -2*dx - 2*dy;
            bool switched = false;
            while(X != xEnd){
                if(spaced != 0){
                    if(switched){
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X++ , D += D1;
                            else
                                X++ , Y-- , D += D2;

                            if(X == xEnd)   break;
                        }
                        switched = !switched;
                    }else{
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X++ , D += D1;
                            else
                                X++ , Y-- , D += D2;
                            SetPixel(hdc,X,Y,color);
                            if(thick){
                                SetPixel(hdc,X+1,Y+1,color);
                                SetPixel(hdc,X-1,Y-1,color);
                                SetPixel(hdc,X+1,Y-1,color);
                                SetPixel(hdc,X-1,Y+1,color);

                                SetPixel(hdc,X  ,Y+1,color);
                                SetPixel(hdc,X+1,Y  ,color);
                                SetPixel(hdc,X  ,Y-1,color);
                                SetPixel(hdc,X-1,Y  ,color);
                            }
                            if(X == xEnd)   break;
                        }
                        switched = !switched;
                    }
                }
                else{
                    if(D <= 0)
                        X++ , D += D1;
                    else
                        X++ , Y-- , D += D2;
                    SetPixel(hdc,X,Y,color);
                    if(thick){
                        SetPixel(hdc,X+1,Y+1,color);
                        SetPixel(hdc,X-1,Y-1,color);
                        SetPixel(hdc,X+1,Y-1,color);
                        SetPixel(hdc,X-1,Y+1,color);

                        SetPixel(hdc,X  ,Y+1,color);
                        SetPixel(hdc,X+1,Y  ,color);
                        SetPixel(hdc,X  ,Y-1,color);
                        SetPixel(hdc,X-1,Y  ,color);
                    }
                }
            }
        }
        else{
            int D  = dx + 2*dy;
            int D1 = 2*dy;
            int D2 = 2*dx + 2*dy;
            bool switched = false;
            while(X != xEnd){
                if(spaced != 0){
                    if(switched){
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X-- , D += D1;
                            else
                                X-- , Y++ , D += D2;

                            if(X == xEnd)   break;
                        }
                        switched = !switched;
                    }else{
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X-- , D += D1;
                            else
                                X-- , Y++ , D += D2;
                            SetPixel(hdc,X,Y,color);
                            if(thick){
                                SetPixel(hdc,X+1,Y+1,color);
                                SetPixel(hdc,X-1,Y-1,color);
                                SetPixel(hdc,X+1,Y-1,color);
                                SetPixel(hdc,X-1,Y+1,color);

                                SetPixel(hdc,X  ,Y+1,color);
                                SetPixel(hdc,X+1,Y  ,color);
                                SetPixel(hdc,X  ,Y-1,color);
                                SetPixel(hdc,X-1,Y  ,color);
                            }

                            if(X == xEnd)   break;
                        }
                        switched = !switched;
                    }
                }else{
                    if(D <= 0)
                        X-- , D += D1;
                    else
                        X-- , Y++ , D += D2;
                    SetPixel(hdc,X,Y,color);
                    if(thick){
                        SetPixel(hdc,X+1,Y+1,color);
                        SetPixel(hdc,X-1,Y-1,color);
                        SetPixel(hdc,X+1,Y-1,color);
                        SetPixel(hdc,X-1,Y+1,color);

                        SetPixel(hdc,X  ,Y+1,color);
                        SetPixel(hdc,X+1,Y  ,color);
                        SetPixel(hdc,X  ,Y-1,color);
                        SetPixel(hdc,X-1,Y  ,color);
                    }
                }
            }
        }
    }














    else if(Slope<-1 || dx==0){         //]-inf:-1[
        if(dy<0 && dx>=0){
            int D  = -2*dx - dy;
            int D1 = -2*dx;
            int D2 = -2*dx - 2*dy;
            bool switched = false;
            while(Y != yEnd){
                if(spaced != 0){
                    if(switched){
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X++ , Y-- , D += D2;
                            else
                                Y-- , D += D1;

                            if(Y == yEnd)   break;
                        }
                        switched = !switched;
                    }else{
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X++ , Y-- , D += D2;
                            else
                                Y-- , D += D1;
                            SetPixel(hdc,X,Y,color);
                            if(thick){
                                SetPixel(hdc,X+1,Y+1,color);
                                SetPixel(hdc,X-1,Y-1,color);
                                SetPixel(hdc,X+1,Y-1,color);
                                SetPixel(hdc,X-1,Y+1,color);

                                SetPixel(hdc,X  ,Y+1,color);
                                SetPixel(hdc,X+1,Y  ,color);
                                SetPixel(hdc,X  ,Y-1,color);
                                SetPixel(hdc,X-1,Y  ,color);
                            }
                            if(Y == yEnd)   break;
                        }
                        switched = !switched;
                    }
                }else{
                    if(D <= 0)
                        X++ , Y-- , D += D2;
                    else
                        Y-- , D += D1;
                    SetPixel(hdc,X,Y,color);
                    if(thick){
                        SetPixel(hdc,X+1,Y+1,color);
                        SetPixel(hdc,X-1,Y-1,color);
                        SetPixel(hdc,X+1,Y-1,color);
                        SetPixel(hdc,X-1,Y+1,color);

                        SetPixel(hdc,X  ,Y+1,color);
                        SetPixel(hdc,X+1,Y  ,color);
                        SetPixel(hdc,X  ,Y-1,color);
                        SetPixel(hdc,X-1,Y  ,color);
                    }
                }
            }
        }
        else{
            int D  = 2*dx + dy;
            int D1 = 2*dx;
            int D2 = 2*dx + 2*dy;
            bool switched = false;
            while(Y != yEnd){
                if(spaced != 0){
                    if(switched){
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X-- , Y++ , D += D2;
                            else
                                Y++ , D += D1;

                            if(Y == yEnd)   break;
                        }
                        switched = !switched;
                    }else{
                        for(int i=0; i<spaced; i++){
                            if(D <= 0)
                                X-- , Y++ , D += D2;
                            else
                                Y++ , D += D1;
                            SetPixel(hdc,X,Y,color);
                            if(thick){
                                SetPixel(hdc,X+1,Y+1,color);
                                SetPixel(hdc,X-1,Y-1,color);
                                SetPixel(hdc,X+1,Y-1,color);
                                SetPixel(hdc,X-1,Y+1,color);

                                SetPixel(hdc,X  ,Y+1,color);
                                SetPixel(hdc,X+1,Y  ,color);
                                SetPixel(hdc,X  ,Y-1,color);
                                SetPixel(hdc,X-1,Y  ,color);
                            }

                            if(Y == yEnd)   break;
                        }
                        switched = !switched;
                    }
                }else{
                    if(D <= 0)
                        X-- , Y++ , D += D2;
                    else
                        Y++ , D += D1;
                    SetPixel(hdc,X,Y,color);
                    if(thick){
                        SetPixel(hdc,X+1,Y+1,color);
                        SetPixel(hdc,X-1,Y-1,color);
                        SetPixel(hdc,X+1,Y-1,color);
                        SetPixel(hdc,X-1,Y+1,color);

                        SetPixel(hdc,X  ,Y+1,color);
                        SetPixel(hdc,X+1,Y  ,color);
                        SetPixel(hdc,X  ,Y-1,color);
                        SetPixel(hdc,X-1,Y  ,color);
                    }
                }
            }
        }
    }
}

void Line_PARAMETRIC(HDC hdc,Point P1, Point P2,COLORREF color=RGB(0,0,255),bool thick=false,int spaced=0){
    int xStart = P1.x;
    int yStart = P1.y;
    int xEnd = P2.x;
    int yEnd = P2.y;


    double dx = xEnd - xStart;
    double dy = yEnd - yStart;
    SetPixel(hdc,xStart,yStart,color);

    double t=0.0;
    bool switched = false;
    for(double t=0; t<=1; ){
        if(spaced != 0){
            if(switched){
                for(int i=0; i<spaced; i++){
                    t += 0.005;
                }
                switched = !switched;
            }else{
                for(int i=0; i<spaced; i++){
                    double X = xStart + t*dx;
                    double Y = yStart + t*dy;
                    SetPixel(hdc,round(X),round(Y),color);
                    if(thick){
                        SetPixel(hdc,round(X)+1,round(Y)+1,color);
                        SetPixel(hdc,round(X)-1,round(Y)-1,color);
                        SetPixel(hdc,round(X)+1,round(Y)-1,color);
                        SetPixel(hdc,round(X)-1,round(Y)+1,color);

                        SetPixel(hdc,round(X)  ,round(Y)+1,color);
                        SetPixel(hdc,round(X)+1,round(Y)  ,color);
                        SetPixel(hdc,round(X)  ,round(Y)-1,color);
                        SetPixel(hdc,round(X)-1,round(Y)  ,color);
                    }
                    t += 0.005;
                }
                switched = !switched;
            }
        }
        else{
            double X = xStart + t*dx;
            double Y = yStart + t*dy;
            SetPixel(hdc,round(X),round(Y),color);
            if(thick){
                SetPixel(hdc,round(X)+1,round(Y)+1,color);
                SetPixel(hdc,round(X)-1,round(Y)-1,color);
                SetPixel(hdc,round(X)+1,round(Y)-1,color);
                SetPixel(hdc,round(X)-1,round(Y)+1,color);

                SetPixel(hdc,round(X)  ,round(Y)+1,color);
                SetPixel(hdc,round(X)+1,round(Y)  ,color);
                SetPixel(hdc,round(X)  ,round(Y)-1,color);
                SetPixel(hdc,round(X)-1,round(Y)  ,color);
            }
            t += 0.001;
        }
    }
}



void Line_Filling_Circle(HDC hdc,int XC,int YC,int X,int Y,int Quarter,COLORREF color){
    Point P_Center(XC,YC);
    if(Quarter==1){
        Point P_Pass1(XC+X , YC-Y);
        Point P_Pass2(XC+Y , YC-X);
        Line_DDA(hdc,P_Center,P_Pass1,color,false);
        Line_DDA(hdc,P_Center,P_Pass2,color,false);
    }
    if(Quarter==2){
        Point P_Pass1(XC-X , YC-Y);
        Point P_Pass2(XC-Y , YC-X);
        Line_DDA(hdc,P_Center,P_Pass1,color,false);
        Line_DDA(hdc,P_Center,P_Pass2,color,false);
    }
    if(Quarter==3){
        Point P_Pass1(XC-X , YC+Y);
        Point P_Pass2(XC-Y , YC+X);
        Line_DDA(hdc,P_Center,P_Pass1,color,false);
        Line_DDA(hdc,P_Center,P_Pass2,color,false);
    }
    if(Quarter==4){
        Point P_Pass1(XC+X , YC+Y);
        Point P_Pass2(XC+Y , YC+X);
        Line_DDA(hdc,P_Center,P_Pass1,color,false);
        Line_DDA(hdc,P_Center,P_Pass2,color,false);
    }
}
