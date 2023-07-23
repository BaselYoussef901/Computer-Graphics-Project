#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif






#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int xStart,yStart,xEnd,yEnd,raduis;
COLORREF Color = RGB(0,0,0);
int red,green,blue;




void Line_MidPoint(HDC hdc, int xStart, int yStart, int xEnd, int yEnd, COLORREF color) {
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


void Line_draw8(HDC hdc,int XC,int YC,int xRaduis,int yRaduis,COLORREF color,bool Diagonal){
    if(Diagonal){
        Line_MidPoint(hdc, XC, YC, XC+yRaduis, YC+xRaduis, color);   //Down-Right
        Line_MidPoint(hdc, XC, YC, XC-yRaduis, YC+xRaduis, color);   //Down-Left
        Line_MidPoint(hdc, XC, YC, XC+yRaduis, YC-xRaduis, color);   //Up-Right
        Line_MidPoint(hdc, XC, YC, XC-yRaduis, YC-xRaduis, color);   //Up-Left
    }else{
        Line_MidPoint(hdc, XC, YC, XC+xRaduis, YC+yRaduis, color);   //Up
        Line_MidPoint(hdc, XC, YC, XC+xRaduis, YC-yRaduis, color);   //Down
        Line_MidPoint(hdc, XC, YC, XC+yRaduis, YC+xRaduis, color);   //Right
        Line_MidPoint(hdc, XC, YC, XC-yRaduis, YC+xRaduis, color);   //Left
    }
}

void Circle_draw8(HDC hdc, int XC, int YC, int X, int Y,COLORREF color) {
	SetPixel(hdc, XC + X, YC + Y, color);
	SetPixel(hdc, XC - X, YC + Y, color);
	SetPixel(hdc, XC + X, YC - Y, color);
	SetPixel(hdc, XC - X, YC - Y, color);

	SetPixel(hdc, XC + Y, YC + X, color);
	SetPixel(hdc, XC - Y, YC + X, color);
	SetPixel(hdc, XC + Y, YC - X, color);
	SetPixel(hdc, XC - Y, YC - X, color);
}


void Circle_MidPoint(HDC hdc, int xCenter,int yCenter,int Raduis,COLORREF color) {
	//xCenter -? xStart		&&	  yCenter -? yStart
	bool isDiagonal = false;
	int X = 0;
	int Y = Raduis;
	//New X and New Y
	int D = 1 - Raduis;
	Circle_draw8(hdc, xCenter, yCenter, X, Y, color);
    Line_draw8(hdc, xCenter, yCenter, X, Y, color, isDiagonal);
	while (X < Y) {
        X++;
		if (D < 0) {
			D += 2*X + 2;
		}else {
			Y--;
			D += 2*(X - Y) + 5;
		}
		Circle_draw8(hdc, xCenter, yCenter, X, Y, color);
	}
    Line_draw8(hdc, xCenter, yCenter, X, Y, color, isDiagonal=true);

}

























/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow){

    cout<<"\n\t\t\tHola, Soy Dora. Welcome To my Little Tiny Assignment!"<<endl;
    cout<<"Team Members:\n  -Hossam Sultan\t(20200148).\n  -Seif El-Dein Yasser\t(20200241).\n  -Basel Youssef\t(20200111).\n";
    cout<<"\n\nPlease Enter Red Value[0:255]: ";   cin>>red;
    red = (red>=0 && red<=255 ? red : 0);
    cout<<"Please Enter green Value[0:255]: ";   cin>>green;
    green = (green>=0 && green<=255 ? green : 0);
    cout<<"Please Enter blue Value[0:255]: ";   cin>>blue;
    blue = (blue>=0 && blue<=255 ? blue : 0);
    Color = RGB(red,green,blue);




    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Circle MidPoint within lines"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           500,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */



LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {

        case WM_LBUTTONDBLCLK:
            xStart = LOWORD(lParam);
            yStart = HIWORD(lParam);
            break;
        case WM_RBUTTONDBLCLK:
            xEnd = LOWORD(lParam);
            yEnd = HIWORD(lParam);
            raduis = sqrt(pow(xEnd - xStart, 2)) + sqrt(pow(yEnd - yStart, 2));
            //Line_MidPoint(hdc, xStart, yStart, xEnd, yEnd, Color);
            Circle_MidPoint(hdc, xStart, yStart, raduis, Color);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
