//ahmed mohamed fathy hussien
//20190068

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
 #define UNICODE
#endif
#include <tchar.h>
#include <windows.h>
#include <cmath>
#include <string>
#include <cstring>
#include <math.h>
#include <fstream>
#include <stack>
#include <vector>
#include <iostream>
#include <sstream>
#define MAXENTRIES 800
using namespace std ;
/* Declare Windows procedure */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
HMENU hmenu;
HMENU bmenu;
HWND g_hWnd;
/* Make the class name into a global variable */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int WINAPI WinMain (HINSTANCE hThisInstance,
HINSTANCE hPrevInstance,
LPSTR lpszArgument,
int nCmdShow)
{
HWND hwnd;
/* This is the handle for our window */
MSG messages; /* Here messages to the application are saved */
WNDCLASSEX wincl; /* Data structure for the windowclass */
/* The Window structure */
wincl.hInstance = hThisInstance;
wincl.lpszClassName = szClassName;
wincl.lpfnWndProc = WindowProcedure; /* This function is called by windows */
wincl.style = CS_DBLCLKS; /* Catch double-clicks */
wincl.cbSize = sizeof (WNDCLASSEX);
/* Use default icon and mouse-pointer */
wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
wincl.hCursor = LoadCursor (NULL, IDC_HAND);/**mouse look*/
wincl.lpszMenuName = NULL; /* No menu */
wincl.cbClsExtra = 0; /* No extra bytes after the window class */
wincl.cbWndExtra = 0;
/* structure or the window instance */
/* Use Windows's default colour as the background of the window */
wincl.hbrBackground = (HBRUSH) COLOR_WINDOWFRAME ;/**window color*/
/* Register the window class, and if it fails quit the program */
if (!RegisterClassEx (&wincl))
return 0;
/* The class is registered, let's create the program*/
hwnd = CreateWindowEx (
0, /* Extended possibilites for variation */
szClassName, /* Classname */
_T("Code::Blocks Template Windows App"), /* Title Text */
WS_OVERLAPPEDWINDOW, /* default window */
CW_USEDEFAULT, /* Windows decides the position */
CW_USEDEFAULT, /* where the window ends up on the screen */
600, /* The programs width */
500, /* and height in pixels */
HWND_DESKTOP, /* The window is a child-window to desktop */
NULL, /* No menu */
hThisInstance, /* Program Instance handler */
NULL/* No Window Creation data */
);
/* Make the window visible on the screen */
//Use it in clean screen
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

void draw8Point(HDC hdc,int xc,int yc,int x,int y,COLORREF c){
SetPixel(hdc,xc+x,yc+y,c);
SetPixel(hdc,xc-x,yc+y,c);
SetPixel(hdc,xc-x,yc-y,c);
SetPixel(hdc,xc+x,yc-y,c);
SetPixel(hdc,xc+y,yc+x,c);
SetPixel(hdc,xc-y,yc+x,c);
SetPixel(hdc,xc-y,yc-x,c);
SetPixel(hdc,xc+y,yc-x,c);
}

int Round(double x){
    return (int)(0.5+x);
}

void Swap(int &a, int &b){
    int t = a;
    a = b;
    b = t;
}
void Swap2nd(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}
//line algorithms

void parametricLine(HDC hdc,int x1,int y1,int x2,int y2, COLORREF s)
{
    double dx=x2-x1;
    double dy=y2-y1;
    for(double t=0; t<1; t+=0.001)
    {
        int x=x1+(dx*t);
        int y=y1+(dy*t);
        SetPixel(hdc,x,y,s);
    }
}
void midPointLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int d, d1, d2;

    if (dx == 0 && dy == 0)
    {
        SetPixel(hdc, x1, y1, c);
       // save(x1, y1, c);
        return;
    }
    if (abs(dy) < abs(dx))
    {
        if (x1 > x2)
        {
            Swap2nd(x1, y1, x2, y2);
            dy *= -1;
            dx *= -1;
        }
        int x = x1, y = y1;
        SetPixel(hdc, x, y, c);
      //  save(x, y, c);

        if (dy > 0) //f(x+1,y+0.5)
        {
            d = dx - 2 * dy;
            d1 = -2 * dy;
            d2 = 2 * (dx - dy);
        }
        else //f(x-1,y+0.5)
        {
            d = dx + 2 * dy;
            d1 = 2 * dy;
            d2 = 2 * (dx + dy);
        }

        while (x < x2)
        {
            x++;
            if (d > 0)
            {
                d += d1;
            }
            else
            {
                d += d2;

                if (dy > 0)
                    y++;
                else
                    y--;
            }
            SetPixel(hdc, x, y, c);
        //    save(x, y, c);
        }
    }
    else if (abs(dx) < abs(dy))
    {
        if (y1 > y2)
        {
            Swap2nd(x1, y1, x2, y2);
            dy *= -1;
            dx *= -1;
        }
        int x = x1, y = y1;
        SetPixel(hdc, x, y, c);
//        save(x, y, c);

        if (dx > 0)		//f(x+0.5,y+1)
        {
            d = dy - 2 * dx;
            d1 = -2 * dx;
            d2 = 2 * (dy - dx);
        }
        else //f(x-0.5,y+1)
        {
            d = dy + 2 * dx;
            d1 = 2 * dx;
            d2 = 2 * (dy + dx);
        }

        while (y < y2)
        {
            y++;
            if (d > 0)
            {
                d += d1;
            }
            else
            {
                d += d2;
                if (dx > 0)
                    x++;
                else
                    x--;
            }
            SetPixel(hdc, x, y, c);
//            save(x, y, c);
        }
    }
}


void DrawDDALine(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color){
int dx=xe-xs;
int dy=ye-ys;
SetPixel(hdc,xs,ys,color);
if(abs(dx)>=abs(dy)){
    int x=xs,xinc= dx>0?1:-1;
    double y=ys,yinc=(double)dy/dx*xinc;
    while(x!=xe){
        x+=xinc;
        y+=yinc;
        SetPixel(hdc,x,round(y),color);
      }
   }
else{
    int y=ys,yinc= dy>0?1:-1;
    double x=xs,xinc=(double)dx/dy*yinc;
    while(y!=ye){
        x+=xinc;
        y+=yinc;
        SetPixel(hdc,round(x),y,color);
        }
     }
}

//Circle algorithms
void DirectPolar(HDC hdc,int xc,int yc,int r,COLORREF C)
{

double dtheta=1.0 / r;
for(double theta=0; theta<6.28; theta+=dtheta)
{
double x=Round(xc+r*cos(theta));
double y=Round(yc+r*sin(theta));
SetPixel(hdc,x,y,C);
}
}
void Polar(HDC hdc,int xc,int yc,int r,COLORREF C){
double dtheta=1.0 / r;
double c=cos(dtheta);
double s=sin(dtheta);
double x=r;
double y=0;
draw8Point(hdc,xc,yc,Round(x),Round(y),C);//first 8 point
    while(x>y){
    x=x*c-y*s;
    y=x*s+y*c;
    draw8Point(hdc,xc,yc,Round(x),Round(y),C);
    }
 }
void midpointCircle(HDC hdc,int xc,int yc,int r,COLORREF C)
{

double y=r,x=0,d=1-r;
draw8Point(hdc,xc,yc,Round(x),Round(y),C);
    while(x<=y)
    {
        if(d<0){
        d+=2*x+3;
        x++;
        }
        else{
        d+=2*(x-y)+5;
        x++;
        y--;
        }
    draw8Point(hdc,xc,yc,Round(x),Round(y),C);
    }
}

void modifiedMidpoint(HDC hdc,int xc,int yc,int r,COLORREF C)
{

int x=0,y=r;
int d=1-r;
int d1=3;
int d2=5-2*r;
    while(x<=y){

        if(d<0){
        d+=d1;
        d2+=2;
        d1+=2;
        x++;
        }
        else{
        d+=d2;
        d2+=4;
        y--;
        d1+=2;
        x++;
        }
    draw8Point(hdc,xc,yc,Round(x),Round(y),C);
    }
}


//draw 8 point for filling quarter of the circle with line
void drawEightFQuartile(HDC hdc,int x,int y,int xc,int yc , int nq){

 if (nq==1){
        DrawDDALine(hdc,xc , yc,xc+x,yc-y,RGB(100,0,0));
        DrawDDALine(hdc,xc , yc,xc+y,yc-x,RGB(100,0,0));
        }
//quarter one

else if (nq==2){
        DrawDDALine(hdc,xc , yc, xc-x,yc-y,RGB(100,0,0));
        DrawDDALine(hdc,xc , yc,xc-y,yc-x,RGB(100,0,0));
        }
//quarter two

else if (nq==3){
        DrawDDALine(hdc,xc , yc,xc -x,yc+ y,RGB(100,0,0));
        DrawDDALine(hdc,xc , yc,xc-y,yc+x,RGB(100,0,0));
         }
//quarter three

 else if (nq==4){
        DrawDDALine(hdc,xc , yc, xc+x,yc+y,RGB(100,0,0));
        DrawDDALine(hdc,xc , yc,xc+y,yc+x,RGB(100,0,0));
         }
//quarter four


    SetPixel(hdc,xc+x,yc+y,RGB(100,0,0));
    SetPixel(hdc,xc-x,yc+y,RGB(100,0,0));
    SetPixel(hdc,xc-x,yc-y,RGB(100,0,0));
    SetPixel(hdc,xc+x,yc-y,RGB(100,0,0));
    SetPixel(hdc,xc+y,yc+x,RGB(100,0,0));
    SetPixel(hdc,xc-y,yc+x,RGB(100,0,0));
    SetPixel(hdc,xc-y,yc-x,RGB(100,0,0));
    SetPixel(hdc,xc+y,yc-x,RGB(100,0,0));

}
//this fuction for filling quarter of the circle with line
void CircleFQuarter(HDC hdc,int xc,int yc,int r , int nq){
int x=0;
int y=r;
double d=1-r;

    drawEightFQuartile(hdc,x,y,xc,yc , nq);
while(x<=y)
{

    if(d<=0){
        d=d+2*x+3;
        x++;
    }

    else{
        d=d+2*(x-y)+5;
        x++;
        y--;
    }
    drawEightFQuartile(hdc,x,y,xc,yc , nq);

   }

}

//ellipse algorithms
void Draw4Points(HDC hdc, int xc,int yc,int x,int y,COLORREF c){

    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc-x,yc-y,c);
}
void Ellipse(HDC hdc,int xc,int yc,int A,int B,COLORREF c){
    int x=0;
    int y=B;
    int d=(B*B)-((A*A)*(B+0.25));
    int d1=2*((B*B)*x)+3*(B*B);
    int d2=(B*B)*(2*x+3)+2*(A*A)*(1-y);
    Draw4Points(hdc,xc,yc,x,y,c);
    while (x*(B*B)<y*(A*A))
    {
        if (d<0)
        {
            d+=d1;
        }
        else if(d>0)
        {
            d+=d2;
            y--;
        }
        x++;
        Draw4Points(hdc,xc,yc,x,y,c);
    }
}

void DrawEllipsePolar(HDC hdc, int xc, int yc, int A, int B , COLORREF c){
    double x = A, y = 0, dtheta = 1.0 /A;
     Draw4Points(hdc, xc, yc, x, y , c);
    for (double theta = 0 ; theta < 0.5 * 3.1415 ; theta += dtheta)
    {
        x = A * cos(theta);
        y = B * sin(theta);
        Draw4Points(hdc, xc, yc, Round(x), Round(y) , c);
    }
}

void midpointEllipse(HDC hdc,int xc,int yc,double a,double b,COLORREF c){

    long x,y,a_sqr,b_sqr, fx,fy, d;
    float tmp1,tmp2;
    x=0;
    y=b;
    a_sqr=a*a;
    b_sqr=b*b;
    fx=2*b_sqr*x;
    fy=2*a_sqr*y;
    d=b_sqr-(a_sqr*b)+(a_sqr*0.25);
    do
    {
        Draw4Points(hdc,xc,yc,x,y,c);
        if(d<0)
        {
            d=d+fx+b_sqr;
        }
        else
        {
            y=y-1;
            d=d+fx+b_sqr-fy;
            fy=fy-(2*a_sqr);
        }
        x=x+1;
        fx=fx+(2*b_sqr);
    }
    while(fx<fy);
    tmp1=(x+0.5)*(x+0.5);
    tmp2=(y-1)*(y-1);
    d=b_sqr*tmp1+a_sqr*tmp2-(a_sqr*b_sqr);
    do
    {
        Draw4Points(hdc,xc,yc,x,y,c);
        if(d>0)
            d=d-fy+a_sqr;
        else
        {
            x=x+1;
            d=d+fx-fy+a_sqr;
            fx=fx+(2*b_sqr);
        }
        y=y-1;
        fy=fy-(2*a_sqr);
    }
    while(y>=0);
}

//recursive flood fill
void FloodFill(HDC hdc,int x,int y,COLORREF Cb,COLORREF Cf){
        COLORREF C=GetPixel(hdc,x,y);
        if(C==Cb || C==Cf)return;
         SetPixel(hdc,x,y,Cf);
        FloodFill(hdc,x+1,y,Cb,Cf);
        FloodFill(hdc,x-1,y,Cb,Cf);
        FloodFill(hdc,x,y+1,Cb,Cf);
        FloodFill(hdc,x,y-1,Cb,Cf);
}
//non recursive flood fill
struct Vertex{
int x,y;
Vertex(int x,int y):x(x),y(y){}
};

void NRFloodFill(HDC hdc,int x,int y,COLORREF Cb,COLORREF Cf){
    stack<Vertex> S;
    S.push(Vertex(x,y));
    while(!S.empty())
    {
    Vertex v=S.top();
    S.pop();

    COLORREF c=GetPixel(hdc ,v.x,v.y);
    if(c==Cb || c==Cf)continue;
    SetPixel(hdc,v.x,v.y,Cf);
    S.push(Vertex(v.x+1,v.y));
    S.push(Vertex(v.x-1,v.y));
    S.push(Vertex(v.x,v.y+1));
    S.push(Vertex(v.x,v.y-1));
    }
}

struct Entry
{
    int xleft, xright;
};

//xleft --> infinity, xright --> -infinity
void InitEntries(Entry table[])
{
    for (int i = 0; i < MAXENTRIES; i++)
    {
        table[i].xleft = INT_MAX;
        table[i].xright = -INT_MAX;
    }
}

void ScanEdge(POINT v1, POINT v2, Entry table[]){

    if (v1.y == v2.y)return;
    if (v1.y > v2.y)swap(v1, v2);
    double minv = (double)(v2.x - v1.x) / (v2.y - v1.y);//  1/m
    double x = v1.x;
    int y = v1.y;
    while (y < v2.y)
    {
        if (x < table[y].xleft)
            table[y].xleft = (int)ceil(x);
        if (x > table[y].xright)
            table[y].xright = (int)floor(x);

        y++;
        x += minv;

    }
 }

void DrawScanLines(HDC hdc, Entry table[], COLORREF color){
    for (int y = 0;y < MAXENTRIES;y++)
        if (table[y].xleft < table[y].xright)
        {
            for (int x = table[y].xleft;x <= table[y].xright;x++)//in every index from xleft to xright
            {
                SetPixel(hdc, x, y, color);
            }
        }

 }

void ConvexFill(HDC hdc, POINT p[], int n, COLORREF color)
{
    Entry* table = new Entry[MAXENTRIES];
    InitEntries(table);
    POINT v1 = p[n - 1];
    for (int i = 0;i < n;i++){

        POINT v2 = p[i];
        ScanEdge(v1, v2, table);
        v1 = p[i];
    }
    DrawScanLines(hdc, table, color);
    delete table;
}

/*  This function is called by the Windows function DispatchMessage()  */
int x11 , y11 , x22 , y22 , Y , y ,R1,x_c,y_c,x_2,y_2 , R ,x_c6, y_c6 ,x_6 , y_6;
int x_c3, y_c3 , x_3 ,  y_3 , x_c4 , y_c4 ,x_4 , y_4,x_c5, y_c5 ,x_5 , y_5,
x_c7, y_c7 ,x_7 , y_7,x_c8, y_c8 ,x_8 , y_8 , Y1 ;

int Numofpoints =1 ;
int nn = 1 ;
int Num_of_Points=1;
POINT P[5];
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
             HDC hdc=GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {


         case WM_RBUTTONDBLCLK:
      if (Numofpoints == 1)
      {
         x_c=LOWORD(lParam);
         y_c=HIWORD(lParam);
         Numofpoints++;
      }

      else if (Numofpoints==2) //parametric line
      {
         x_2=LOWORD(lParam);
         y_2=HIWORD(lParam);

        parametricLine(hdc ,x_c , y_c , x_2 , y_2 , RGB(250,126,125));

        Numofpoints ++ ;
      }
         else if (Numofpoints==3)
      {
         x_c3=LOWORD(lParam);
         y_c3=HIWORD(lParam);


        Numofpoints ++ ;
      }
         else if (Numofpoints==4)//midpoint line
      {
         x_3=LOWORD(lParam);
         y_3=HIWORD(lParam);

        midPointLine(hdc ,x_c3 , y_c3 , x_3 , y_3 , RGB(200,100,150));

        Numofpoints ++ ;
      }

         else if (Numofpoints==5)
      {
         x_c4=LOWORD(lParam);
         y_c4=HIWORD(lParam);

        Numofpoints ++ ;
      }
         else if (Numofpoints==6) //dda line
      {
         x_4=LOWORD(lParam);
         y_4=HIWORD(lParam);

        DrawDDALine(hdc ,x_c4 , y_c4 , x_4 , y_4 , RGB(200,100,150));

        Numofpoints ++ ;
      }

       else if (Numofpoints==7)
      {
         x_c5=LOWORD(lParam);
         y_c5=HIWORD(lParam);

        Numofpoints ++ ;
      }
         else if (Numofpoints==8) // direct polar
      {
         x_5=LOWORD(lParam);
         y_5=HIWORD(lParam);

        R = Round(sqrt(pow(x_5-x_c5,2.0)+pow(y_5-y_c5,2.0)));
        DirectPolar(hdc ,x_c5 , y_c5 , R, RGB(200,100,150));

        Numofpoints ++ ;
      }

     else if (Numofpoints==9)
      {
         x_c6=LOWORD(lParam);
         y_c6=HIWORD(lParam);

        Numofpoints ++ ;
      }
     else if (Numofpoints==10) //polar
      {
         x_6=LOWORD(lParam);
         y_6=HIWORD(lParam);

        R1 = Round(sqrt(pow(x_6-x_c6,2.0)+pow(y_6-y_c6,2.0)));
        Polar(hdc ,x_c6 , y_c6 ,R1, RGB(200,100,150));

        Numofpoints ++ ;
      }
      else if (Numofpoints==11)
      {
         x_c7=LOWORD(lParam);
         y_c7=HIWORD(lParam);

        Numofpoints ++ ;
      }
     else if (Numofpoints==12)//midpoint circle
      {
         x_7=LOWORD(lParam);
         y_7=HIWORD(lParam);

        R1 = Round(sqrt(pow(x_7-x_c7,2.0)+pow(y_7-y_c7,2.0)));
        midpointCircle(hdc ,x_c7 , y_c7 ,R1, RGB(200,100,150));

        Numofpoints ++ ;
      }
        else if (Numofpoints==13)
      {
         x_c8=LOWORD(lParam);
         y_c8=HIWORD(lParam);

        Numofpoints ++ ;
      }
     else if (Numofpoints==14) // modified mid point
      {
         x_8=LOWORD(lParam);
         y_8=HIWORD(lParam);

        R1 = Round(sqrt(pow(x_8-x_c8,2.0)+pow(y_8-y_c8,2.0)));
        modifiedMidpoint(hdc ,x_c8 , y_c8 ,R1, RGB(200,100,150));

        Numofpoints ++ ;
      }
       else if (Numofpoints==15)
      {
         x_c8=LOWORD(lParam);
         y_c8=HIWORD(lParam);

        Numofpoints ++ ;
      }
     else if (Numofpoints==16) // filling quarter of circle
      {
         x_8=LOWORD(lParam);
         y_8=HIWORD(lParam);

        R1 = Round(sqrt(pow(x_8-x_c8,2.0)+pow(y_8-y_c8,2.0)));
        CircleFQuarter(hdc,x_c8,y_c8,R1 , nn );

        Numofpoints ++;
      }
         else if (Numofpoints==17)
      {
         x_c8=LOWORD(lParam);
         y_c8=HIWORD(lParam);

        Numofpoints ++ ;
      }
     else if (Numofpoints==18) //  ellipse
      {
         x_8=LOWORD(lParam);
         y_8=HIWORD(lParam);

        midpointEllipse(hdc,x_8,y_8,20,30,RGB(200,100,150));
        NRFloodFill(hdc , x_8 , y_8 , RGB(200,100,150) ,Y );
        Numofpoints ++ ;
      }
       else if (Numofpoints==19)
      {
         x_c8=LOWORD(lParam);
         y_c8=HIWORD(lParam);

        Numofpoints ++ ;
      }
     else if (Numofpoints==20) // midpoint ellipse
      {
         x_8=LOWORD(lParam);
         y_8=HIWORD(lParam);

        midpointEllipse(hdc,x_8,y_8,20,30,Y);
        NRFloodFill(hdc , x_8 , y_8 , RGB(200,100,150) , Y );
        Numofpoints =0 ;
      }
           break;

        case WM_LBUTTONDBLCLK:
      if(Num_of_Points==1)
        {
           P[0].x = LOWORD(lParam);
           P[0].y = HIWORD(lParam);
           Num_of_Points++;
        }
        else if(Num_of_Points==2)
        {
           P[1].x=LOWORD(lParam);
           P[1].y=HIWORD(lParam);
           Num_of_Points++;
        }
        else if(Num_of_Points==3)
        {
           P[2].x=LOWORD(lParam);
           P[2].y=HIWORD(lParam);
           Num_of_Points++;
        }
        else if(Num_of_Points==4)
        {
           P[3].x=LOWORD(lParam);
           P[3].y=HIWORD(lParam);
           Num_of_Points++;
        }
        else if(Num_of_Points==5)
        {
           P[4].x=LOWORD(lParam);
           P[4].y=HIWORD(lParam);
           Num_of_Points++;
           //change pen color//
           SelectObject(hdc, GetStockObject(DC_PEN));
           SetDCPenColor(hdc, RGB(60,239,161));

           Polygon(hdc, P, 5);
        }
        else if(Num_of_Points==6)
        {
           ConvexFill(hdc, P, 5, RGB(60,239,161) );
           Num_of_Points=0;
        }

      //  x11=LOWORD(lParam);
      //  y11=HIWORD(lParam);
          break ;

         case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */

            break;


        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
