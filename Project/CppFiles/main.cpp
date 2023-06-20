#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <list>
#include <stack>
using namespace std;
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Curves.h"
#include "Clipping.h"
#include "Fill.h"



struct Color{
    int r,g,b;
    Color(int r=0,int g=0,int b=0){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

template<class T>
void Reset_Points(vector<T>&,int);
void Menu(HWND);
void FillColors(Color[]);

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow){
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
    wincl.hCursor = LoadCursor (NULL, IDC_CROSS);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) GetStockObject(RGB(255,255,255));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("CG - Project'23 | Dr.Reda ELkhoriby"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           600,                 /* The programs width */
           400,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0)){
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}






























bool HDCToFile(const char* FilePath, HDC Context, RECT Area, uint16_t BitsPerPixel){
    uint32_t Width = Area.right - Area.left;
    uint32_t Height = Area.bottom - Area.top;

    Width = 1200;
    Height = 600;

    BITMAPINFO Info;
    BITMAPFILEHEADER Header;
    memset(&Info, 0, sizeof(Info));
    memset(&Header, 0, sizeof(Header));
    Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = Height;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = BitsPerPixel;
    Info.bmiHeader.biCompression = BI_RGB;
    Info.bmiHeader.biSizeImage = Width * Height;
    Header.bfType = 0x4D42;
    Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    char* Pixels = NULL;
    HDC MemDC = CreateCompatibleDC(Context);
    HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
    DeleteObject(SelectObject(MemDC, Section));
    BitBlt(MemDC, 0, 0, Width, Height, Context, Area.left, Area.top, SRCCOPY);
    DeleteDC(MemDC);

    std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
    if (hFile.is_open())
    {
        hFile.write((char*)&Header, sizeof(Header));
        hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
        hFile.write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
        hFile.close();
        DeleteObject(Section);
        return true;
    }

    DeleteObject(Section);
    return false;
}
void load(HWND hWnd, HDC& hdc){
    HBITMAP hBitmap;
    hBitmap = (HBITMAP)::LoadImage(NULL, "Kat.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HDC hLocalDC;
    hLocalDC = CreateCompatibleDC(hdc);
    BITMAP qBitmap;
    int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
    BOOL qRetBlit = BitBlt(hdc, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
    SelectObject(hLocalDC, hOldBmp);
    DeleteDC(hLocalDC);
    DeleteObject(hBitmap);
}







































/*  This function is called by the Windows function DispatchMessage()  */
static vector<Point>Points(105);
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
    static COLORREF color = RGB(0,0,0);
    static int x,y,poi=0;
    static int Quarter=1,radius=0,brush=0;
    static Color Colors[11];
    HDC hdc = GetDC(hwnd);
    static int left,top,right,bottom;
    static vector<Point>Points_History;
    static vector<Shape>Shapes_History;
    static bool Thick = false;

    static vector<Point>Polygon_Points;
    static bool Draw_Poly = true;
    static Shape Clip;

    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
        {
            switch(wParam){
                //Color
                case 0:  {color = RGB(Colors[0].r  , Colors[0].g  , Colors[0].b);   break;  }
                case 1:  {color = RGB(Colors[1].r  , Colors[1].g  , Colors[1].b);   break;  }
                case 2:  {color = RGB(Colors[2].r  , Colors[2].g  , Colors[2].b);   break;  }
                case 3:  {color = RGB(Colors[3].r  , Colors[3].g  , Colors[3].b);   break;  }
                case 4:  {color = RGB(Colors[4].r  , Colors[4].g  , Colors[4].b);   break;  }
                case 5:  {color = RGB(Colors[5].r  , Colors[5].g  , Colors[5].b);   break;  }
                case 6:  {color = RGB(Colors[6].r  , Colors[6].g  , Colors[6].b);   break;  }
                case 7:  {color = RGB(Colors[7].r  , Colors[7].g  , Colors[7].b);   break;  }
                case 8:  {color = RGB(Colors[8].r  , Colors[8].g  , Colors[8].b);   break;  }
                case 9:  {color = RGB(Colors[9].r  , Colors[9].g  , Colors[9].b);   break;  }
                case 10: {color = RGB(Colors[10].r , Colors[10].g , Colors[10].b);  break;  }
                case 11: {load(hwnd,hdc);      break;   }
                case 12: {
                        RECT rect;
                        if(GetWindowRect(hwnd , &rect)){
                            HDCToFile("Kat.BMP" , hdc, rect, 24);
                            ReleaseDC(hwnd , hdc);
                        }
                        break;
                    }

                //Shapes
                case 50: {Draw_Poly = false;      Draw_Square       (hdc,left,top,right,bottom,color);     Clip.xleft = left, Clip.xright = right, Clip.ytop = top , Clip.ybottom = bottom;     break;  }
                case 51: {Draw_Poly = false;      Draw_Rectangle    (hdc,left,top,right,bottom,color);     Clip.xleft = left, Clip.xright = right, Clip.ytop = top , Clip.ybottom = bottom;     break;  }
                case 52: {Draw_Poly = false;      Draw_Polygon      (hdc,Polygon_Points,Polygon_Points.size(),color);                break;  }

                //Line
                case 101: {Draw_Poly = false;      Line_DDA       (hdc,Points[poi-2],Points[poi-1],color,Thick,brush);      break;}
                case 102: {Draw_Poly = false;      Line_MIDPOINT  (hdc,Points[poi-2],Points[poi-1],color,Thick,brush);      break;}
                case 103: {Draw_Poly = false;      Line_PARAMETRIC(hdc,Points[poi-2],Points[poi-1],color,Thick,brush);      break;}

                //Circle
                case 201: {Draw_Poly = false;      Circle_Direct          (hdc,Points[poi-2],radius,color,Thick,brush);         break;  }
                case 202: {Draw_Poly = false;      Circle_Polar           (hdc,Points[poi-2],radius,color,Thick,brush);         break;  }
                case 203: {Draw_Poly = false;      Circle_IterativePolar  (hdc,Points[poi-2],radius,color,Thick,brush);         break;  }
                case 204: {Draw_Poly = false;      Circle_MidPoint        (hdc,Points[poi-2],radius,color,Thick,brush);         break;  }
                case 205: {Draw_Poly = false;      Circle_ModifiedMidPoint(hdc,Points[poi-2],radius,color,Thick,brush);         break;  }

                //Ellipse
                case 301: {Draw_Poly = false;      Ellipse_Direct  (hdc,Points[poi-2],Points[poi-1],color);     break;  }
                case 302: {Draw_Poly = false;      Ellipse_Polar   (hdc,Points[poi-2],Points[poi-1],color);     break;  }
                case 303: {Draw_Poly = false;      Ellipse_MidPoint(hdc,Points[poi-2],Points[poi-1],color);     break;  }

                //Curves
                case 401: {Draw_Poly = false;      Curve_Hermite(hdc,Points[poi-4],Points[poi-3],Points[poi-2],Points[poi-1],color);                        break;  }
                case 402: {Draw_Poly = false;      Curve_Bezier(hdc,Points[poi-4],Points[poi-3],Points[poi-2],Points[poi-1],color);                         break;  }
                case 403: {Draw_Poly = false;      DrawCardinalSpline(hdc,Points,poi,0.5,color);                         break;  }

                //Fill
                case 501: {Draw_Poly = false;      cout<<"Which Quarter To Fill [1:4]: ";  cin>>Quarter;   Fill_LCircle(hdc,Points[poi-2],radius,Quarter,color);         break;  }
                case 502: {Draw_Poly = false;      cout<<"Which Quarter To Fill [1:4]: ";  cin>>Quarter;   Fill_CCircle(hdc,Points[poi-2],radius,Quarter,color);         break;  }
                case 503: {Draw_Poly = false;      Curve_Hermite_Filling  (hdc,left,top,right,bottom,color,true);       break;  }
                case 504: {Draw_Poly = false;      Curve_Bezier_Filling   (hdc,left,top,right,bottom,color,false);      break;  }
                case 505: {Draw_Poly = false;      Fill_Polygon           (hdc,Polygon_Points,(int)Polygon_Points.size(),color);                            break;  }
                case 506: {Draw_Poly = false;      Fill_NoN_Polygon       (hdc,Polygon_Points,(int)Polygon_Points.size(),color);                            break;  }
                case 507: {Draw_Poly = false;      Recursive_FloodFill    (hdc,Points[poi-1].x,Points[poi-1].y,color,RGB(255,0,0));                          break;  }
                case 508: {Draw_Poly = false;      NoN_Recursive_FloodFill(hdc,Points[poi-1],color,RGB(255,0,0));                                            break;  }

                //Clipping
                case 604: {Draw_Poly = false;      Clipping_Point    (hdc,Points[poi-1].x,Points[poi-1].y,Clip.xleft,Clip.ytop,Clip.xright,Clip.ybottom,color);                                             break;  }
                case 605: {Draw_Poly = false;      Clipping_CohenSuth(hdc,Points[poi-2].x,Points[poi-2].y,Points[poi-1].x,Points[poi-1].y,Clip.xleft,Clip.ytop,Clip.xright,Clip.ybottom,color);             break;  }
                case 606: {Draw_Poly = false;      Clipping_Polygon  (hdc,Polygon_Points,(int)Polygon_Points.size(),Clip.xleft,Clip.ytop,Clip.xright,Clip.ybottom,color);                                                                      break;  }

                //brush
                case 911: {brush = 3;       break;  }
                case 912: {brush = 30;      break;  }
                case 913: {brush = 0;       break;  }
                case 914: {Thick = true;    break;  }
                case 915: {Thick = false;   break;  }
            }
            ReleaseDC(hwnd,hdc);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            Points[poi].x = x;
            Points[poi].y = y;
            Points_History.push_back(Points[poi]);
            if(Draw_Poly == false){
                Draw_Poly = true;
                Polygon_Points.clear();
            }
            Polygon_Points.push_back(Points[poi]);
            poi++;
            cout<<"Saved-Points: "<<(int)Points_History.size()<<"\t\tPoint: "<<poi<<"\t["<<x<<","<<y<<"]\n";
            cout<<"Thick: "<<Thick<<" | Brush: "<<brush<<" | ";
            if(poi>=2){
                radius = sqrt(   ((Points[poi-1].x-Points[poi-2].x)*(Points[poi-1].x-Points[poi-2].x))    +    ((Points[poi-1].y-Points[poi-2].y)*(Points[poi-1].y-Points[poi-2].y))    );
                cout<<"Radius: "<<radius;
                cout<<"\tPoly: "<<Polygon_Points.size();
            }
            cout<<endl;
            if(poi>=3){
                left = Points[poi-3].x;
                top = Points[poi-3].y;
                right = Points[poi-2].x;
                bottom = Points[poi-1].y;
                Shape shape(left,top,right,bottom);
                Shapes_History.push_back(shape);
                cout<<"Left: "<<left<<" | Top: "<<top<<" | Right: "<<right<<" | Bottom:"<<bottom<<endl;
            }
            cout<<endl;
            ReleaseDC(hwnd,hdc);
            break;
        }
        case WM_RBUTTONDOWN:
        {

            ReleaseDC(hwnd,hdc);
            break;
        }
        case WM_LBUTTONDBLCLK:                  //Reseting data
        {
            Beep(500,800);
            MessageBox(hwnd,"Reseting History","Clearing Data",MB_OK);
            radius = 0;
            poi = 0;
            Reset_Points(Points,105);
            Reset_Points(Points_History , (int)Points_History.size());
            Reset_Points(Shapes_History , (int)Shapes_History.size());
            ReleaseDC(hwnd,hdc);
            system("cls");
            ReleaseDC(hwnd, hdc);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255)); // White color brush
            FillRect(hdc, &clientRect, hBrush);
            DeleteObject(hBrush);
            ReleaseDC(hwnd, hdc);
            break;
        }

        case WM_CREATE:
        {
            FillColors(Colors);
            Menu(hwnd);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}


























void FillColors(Color Colors[]){
    Colors[0].r  = 255 , Colors[0].g  = 255 , Colors[0].b  = 255;     ///White
    Colors[1].r  = 0   , Colors[1].g  = 0   , Colors[1].b  = 0;       ///Black
    Colors[2].r  = 255 , Colors[2].g  = 0   , Colors[2].b  = 0;       ///Red
    Colors[3].r  = 0   , Colors[3].g  = 255 , Colors[3].b  = 0;       ///Green
    Colors[4].r  = 0   , Colors[4].g  = 0   , Colors[4].b  = 255;     ///Blue
    Colors[5].r  = 160 , Colors[5].g  = 160 , Colors[5].b  = 160;     ///Grey
    Colors[6].r  = 0   , Colors[6].g  = 204 , Colors[6].b  = 204;     ///Cyan
    Colors[7].r  = 102 , Colors[7].g  = 51  , Colors[7].b  = 0;       ///Brown
    Colors[8].r  = 255 , Colors[8].g  = 52  , Colors[8].b  = 255;     ///Pink
    Colors[9].r  = 127 , Colors[9].g  = 0   , Colors[9].b  = 255;     ///Violet
    Colors[10].r = 255 , Colors[10].g = 127 , Colors[10].b = 0;       ///Orange
}
template<class T>
void Reset_Points(vector<T> &reseting,int _size){
    for(int i=0; i<_size; i++){
        reseting.pop_back();
    }
    Points = vector<Point>(105);
}
void Menu(HWND hwnd){
    HMENU MenuContainer = CreateMenu();
    HMENU DrawMenu = CreateMenu();
    AppendMenu(DrawMenu,MF_STRING,50,"Square");
    AppendMenu(DrawMenu,MF_STRING,51,"Rectangle");
    AppendMenu(DrawMenu,MF_STRING,52,"Polygon");
    /**                             Line Menu                           **/
    HMENU LineMenu = CreateMenu();
    AppendMenu(LineMenu,MF_STRING,101,"DDA");
    AppendMenu(LineMenu,MF_STRING,102,"MidPoint");
    AppendMenu(LineMenu,MF_STRING,103,"Parametric");
    AppendMenu(DrawMenu,MF_POPUP,(UINT_PTR)LineMenu,"Line");
    /**                             Circle Menu                         **/
    HMENU CircleMenu = CreateMenu();
    AppendMenu(CircleMenu,MF_STRING,201,"Direct");
    AppendMenu(CircleMenu,MF_STRING,202,"Polar");
    AppendMenu(CircleMenu,MF_STRING,203,"Iterative-Polar");
    AppendMenu(CircleMenu,MF_STRING,204,"MidPoint");
    AppendMenu(CircleMenu,MF_STRING,205,"Modified-MidPoint");
    AppendMenu(DrawMenu,MF_POPUP,(UINT_PTR)CircleMenu,"Circle");
    /**                             Ellipse Menu                        **/
    HMENU EllipseMenu = CreateMenu();
    AppendMenu(EllipseMenu,MF_STRING,301,"Direct");
    AppendMenu(EllipseMenu,MF_STRING,302,"Polar");
    AppendMenu(EllipseMenu,MF_STRING,303,"MidPoint");
    AppendMenu(DrawMenu,MF_POPUP,(UINT_PTR)EllipseMenu,"Ellipse");
    /**                             Curves Menu                         **/
    HMENU CurveMenu = CreateMenu();
    AppendMenu(CurveMenu,MF_STRING,401,"Hermite");
    AppendMenu(CurveMenu,MF_STRING,402,"Bezier");
    AppendMenu(CurveMenu,MF_STRING,403,"Cardinal Spline");
    AppendMenu(DrawMenu,MF_POPUP,(UINT_PTR)CurveMenu,"Curves");
    AppendMenu(MenuContainer,MF_POPUP,(UINT_PTR)DrawMenu,"Draw");
    AppendMenu(MenuContainer,NULL,NULL,NULL);
    /**                             Fill Menu                           **/
    HMENU FillingMenu = CreateMenu();
    HMENU FillingCircle = CreateMenu();
    HMENU FillingSquare = CreateMenu();
    HMENU FillingRectangle = CreateMenu();
    HMENU FillingPolygon = CreateMenu();
    HMENU FloodFill = CreateMenu();
    AppendMenu(FillingCircle,MF_STRING,501,"Lines\t[Input]");
    AppendMenu(FillingCircle,MF_STRING,502,"Circles\t[Input]");
    AppendMenu(FillingSquare,MF_STRING,503,"Hermit\t[Vertical]");
    AppendMenu(FillingRectangle,MF_STRING,504,"Bezier\t[Horizontal]");
    AppendMenu(FillingPolygon,MF_STRING,505,"Convex");
    AppendMenu(FillingPolygon,MF_STRING,506,"Non-Convex");
    AppendMenu(FloodFill,MF_STRING,507,"Recursive");
    AppendMenu(FloodFill,MF_STRING,508,"Non-Recursive");
    AppendMenu(FillingMenu,MF_POPUP,(UINT_PTR)FillingCircle,"Circle");
    AppendMenu(FillingMenu,MF_POPUP,(UINT_PTR)FillingSquare,"Square");
    AppendMenu(FillingMenu,MF_POPUP,(UINT_PTR)FillingRectangle,"Rectangle");
    AppendMenu(FillingMenu,MF_POPUP,(UINT_PTR)FillingPolygon,"Polygon");
    AppendMenu(FillingMenu,MF_POPUP,(UINT_PTR)FloodFill,"Flood Fill");
    AppendMenu(MenuContainer,MF_POPUP,(UINT_PTR)FillingMenu,"Filling");
    AppendMenu(MenuContainer,NULL,NULL,NULL);
    /**                             Clipping Menu                       **/
    HMENU ClippingMenu = CreateMenu();
    AppendMenu(ClippingMenu,MF_STRING,604,"Point");
    AppendMenu(ClippingMenu,MF_STRING,605,"Line\t[Cohen]");
    AppendMenu(ClippingMenu,MF_STRING,606,"Polygon");
    AppendMenu(MenuContainer,MF_POPUP,(UINT_PTR)ClippingMenu,"Clipping");
    AppendMenu(MenuContainer,NULL,NULL,NULL);
    /**                             Methods Menu                        **/
    HMENU MethodsMenu = CreateMenu();
    AppendMenu(MethodsMenu,MF_STRING,911,"Dots");
    AppendMenu(MethodsMenu,MF_STRING,912,"Lines");
    AppendMenu(MethodsMenu,MF_STRING,913,"Full");
    AppendMenu(MethodsMenu,MF_STRING,999,NULL);
    AppendMenu(MethodsMenu,MF_STRING,914,"Thick");
    AppendMenu(MethodsMenu,MF_STRING,915,"Thin");
    AppendMenu(MenuContainer,MF_POPUP,(UINT_PTR)MethodsMenu,"brush");
    AppendMenu(MenuContainer,NULL,NULL,NULL);
    /**                             Set-Colors                          **/
    HMENU ColorMenu = CreateMenu();
    AppendMenu(ColorMenu,MF_STRING,0,"White");
    AppendMenu(ColorMenu,MF_STRING,1,"Black");
    AppendMenu(ColorMenu,MF_STRING,2,"Red");
    AppendMenu(ColorMenu,MF_STRING,3,"Green");
    AppendMenu(ColorMenu,MF_STRING,4,"Blue");
    AppendMenu(ColorMenu,MF_STRING,5,"Grey");
    AppendMenu(ColorMenu,MF_STRING,6,"Cyan");
    AppendMenu(ColorMenu,MF_STRING,7,"Brown");
    AppendMenu(ColorMenu,MF_STRING,8,"Pink");
    AppendMenu(ColorMenu,MF_STRING,9,"Violet");
    AppendMenu(ColorMenu,MF_STRING,10,"Orange");
    AppendMenu(MenuContainer,MF_POPUP,(UINT_PTR)ColorMenu,"Color");
    /**                             Load - Save                         **/
    HMENU Functionality = CreateMenu();
    AppendMenu(Functionality,MF_STRING,11,"Load");
    AppendMenu(Functionality,MF_STRING,12,"Save");
    AppendMenu(MenuContainer,MF_POPUP,(UINT_PTR)Functionality,"XXX");


    SetMenu(hwnd,MenuContainer);
}
