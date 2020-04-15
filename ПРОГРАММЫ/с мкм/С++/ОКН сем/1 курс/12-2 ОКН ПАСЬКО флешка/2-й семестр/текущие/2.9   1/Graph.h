#include "ReadImage.h"

int h,w;
char *R, *G,*B;
//
// ---------- ���������� ����������
//
int  xWindow,yWindow;                       // ������ � ������ ����
int  rColor,gColor,bColor;                  // ����
int  xPoint,yPoint;                         // ������� ��������� �������
int  x0Point,y0Point;                       // ���������� "������ ���������"
double aWindow,bWindow,cWindow,dWindow;     // ���������� ��������-� � ������-� ������ ����
double xMastab,yMastab;                     // �������� �� x � y
double kWindow=0.9;                         // �-� ��� ������� �����. ����� �� ������ ����

//
// ---------- �������
//
void SetWindow(double a,double b,double c,double d);
                                            // �������� ���� �� bmp-�����
                                            // (������� w � h -- ������������ ���������
                                            // ����� input.bmp);
                                            // ��������������� ��������� ����:
                                            // a,b -- �������������� �������
                                            // c,d -- ������������ �������;
                                            // ����������� ����������� ��������� 
                                            // (��������, "������ ���������")
                                            // � ���������� �������� �������
void ReadWindow(char* FileName,double a,double b,double c,double d);
                                            // �� ��, ��� � SetWindow �� ��� ������� ����
void CloseWindow();                         // �������� ����
void SetColor(int r,int g,int b);           // ������� �����
void SetPoint(double x,double y);           // ������� ������� ��������� �������
void xyLine(double x0,double y0,double delx,double dely);
                                            // ��������� ���� ���������:
                                            // (x0,y0) -- ����� �� �����������,
                                            // delx,dely -- ���� �������
                                            // �������������� � ������������ ���
void Line(double x,double y);               // �������, ����������� ������� ����� � ������ (x,y)
void Line2(double x,double y);              // ������� Line
void Line3(double x,double y);              // ����� ������� Line
// -----------------------------------------
void SetWindow(double a,double b,double c,double d)
{
     GetSize("input.bmp", &h, &w);
	 R = new char[h*w];
	 G = new char[h*w];
	 B = new char[h*w];
	 ReadImageFromFile("input.bmp",B,G,R);
     xWindow=w;
     yWindow=h;
                                            // ��������� ����:
                                            // a,b -- �������������� �������
                                            // c,d -- ������������ �������
                                            //
                                            // � ���������� ����������� ���������� 
                                            // (��������, "������ ���������")
     aWindow=a;
     bWindow=b;
     xMastab=xWindow*kWindow/(bWindow-aWindow);
     cWindow=c;
     dWindow=d;
     yMastab=yWindow*kWindow/(dWindow-cWindow);
     x0Point=(int)(xWindow*(1-kWindow)/2);
     y0Point=(int)(yWindow*(1-kWindow)/2);

     for (int i=0;i<xWindow*yWindow;i++) 
     {
         R[i]=rColor;
         G[i]=gColor;
         B[i]=bColor;
     }
}
// -----------------------------------------
void ReadWindow(char* FileName,double a,double b,double c,double d)
{
     GetSize(FileName, &h, &w);
	 R = new char[h*w];
	 G = new char[h*w];
	 B = new char[h*w];
	 ReadImageFromFile(FileName,B,G,R);
     xWindow=w;
     yWindow=h;
                                            // ��������� ����:
                                            // a,b -- �������������� �������
                                            // c,d -- ������������ �������
                                            //
                                            // � ���������� ����������� ���������� 
                                            // (��������, "������ ���������")
     aWindow=a;
     bWindow=b;
     xMastab=xWindow*kWindow/(bWindow-aWindow);
     cWindow=c;
     dWindow=d;
     yMastab=yWindow*kWindow/(dWindow-cWindow);
     x0Point=(int)(xWindow*(1-kWindow)/2);
     y0Point=(int)(yWindow*(1-kWindow)/2);
}
// -----------------------------------------
void CloseWindow()
{
     WriteImage("output.bmp", B,G,R);
}
// -----------------------------------------
void SetColor(int r,int g,int b)
{
     rColor=r;
     gColor=g;
     bColor=b;
}
// -----------------------------------------
void xyLine(double x0,double y0,double delx,double dely)
{
                                            // ������ �������������� ���
    int yP=(int)((y0-cWindow)*yMastab)+y0Point;
    for (int j=x0Point/2;j<xWindow-x0Point/2;j++) 
    {
        int Point=yP*xWindow+j;
        R[Point]=rColor;
        G[Point]=gColor;
        B[Point]=bColor;
    }
                                            // ������ �������
    int jl=5;
    int iN=yP-jl,iV=yP+jl;
    for (int j=xWindow-x0Point/2-jl;j<=xWindow-x0Point/2;j++)
        {
            int Point=iV*xWindow+j;
            R[Point]=rColor;
            G[Point]=gColor;
            B[Point]=bColor;
            Point=iN*xWindow+j;
            R[Point]=rColor;
            G[Point]=gColor;
            B[Point]=bColor;
            iV--;iN++;
        }
                                            // ������ ������� �� ���
    for (double x=x0+delx;x<=bWindow;x+=delx)
    {
        int X=(int)((x-aWindow)*xMastab)+x0Point;
        for (int i=yP-jl;i<yP+jl;i++)
        {
            int Point=i*xWindow+X;
            R[Point]=rColor;
            G[Point]=gColor;
            B[Point]=bColor;
        }
    }
    for (double x=x0-delx;x>=aWindow;x-=delx)
    {
        int X=(int)((x-aWindow)*xMastab)+x0Point;
        for (int i=yP-jl;i<yP+jl;i++)
        {
            int Point=i*xWindow+X;
            R[Point]=rColor;
            G[Point]=gColor;
            B[Point]=bColor;
        }
    }
                                            // ������ ������������ ���
    int xP=(int)((x0-aWindow)*xMastab)+x0Point;
    for (int i=y0Point/2;i<yWindow-y0Point/2;i++) 
    {
        int Point=i*xWindow+xP;
        R[Point]=rColor;
        G[Point]=gColor;
        B[Point]=bColor;
    }
                                            // ������ �������
    int il=5;
    int iL=xP-il,iP=xP+il;
    for (int i=yWindow-y0Point/2-il;i<=yWindow-y0Point/2;i++)
        {
            int Point=i*xWindow+iP;
            R[Point]=rColor;
            G[Point]=gColor;
            B[Point]=bColor;
            Point=i*xWindow+iL;
            R[Point]=rColor;
            G[Point]=gColor;
            B[Point]=bColor;
            iP--;iL++;
 
       }
                                            // ������ ������� �� ���
    for (double y=y0+dely;y<=dWindow;y+=dely)
    {
        int Y=(int)((y-cWindow)*yMastab)+y0Point;
        for (int j=xP-il;j<xP+il;j++)
        {
            int Point=Y*xWindow+j;
            R[Point]=rColor;
            G[Point]=gColor;
            B[Point]=bColor;
        }
    }
    
    for (double y=y0-dely;y>=cWindow;y-=dely)
    {
        int Y=(int)((y-cWindow)*yMastab)+y0Point;
        for (int j=xP-il;j<xP+il;j++)
        {
            int Point=Y*xWindow+j;
            R[Point]=rColor;
            G[Point]=gColor;
            B[Point]=bColor;
        }
    }
}
// -----------------------------------------
void SetPoint(double x,double y)
{
     xPoint=(int)((x-aWindow)*xMastab)+x0Point;
     if (y>dWindow) y=dWindow;
     if (y<cWindow) y=cWindow;
     yPoint=(int)((y-cWindow)*yMastab)+y0Point;
}
// -----------------------------------------
void Line(double x,double y)
{
    if (x>bWindow) x=bWindow;
    if (x<aWindow) x=aWindow;
    if (y>dWindow) y=dWindow;
    if (y<cWindow) y=cWindow;
    int xP=(int)((x-aWindow)*xMastab)+x0Point;
    int yP=(int)((y-cWindow)*yMastab)+y0Point;
    int a,b,c,d;
    if (xP>=xPoint)
    {
        a=xPoint;c=yPoint;
        b=xP;d=yP;
    }
    else
    {
        a=xP;c=yP;
        b=xPoint;d=yPoint;
    }
   	xPoint=xP;                              // ���������� ����� ���������� �������
    yPoint=yP;
				                            // ������ ������� [(a,c),(b,d)]
   	double s=0,ds;                          // ����� � ����� �� y �� ���� ��� �� x
    if (a==b) ds=d-c;
    else ds=((double)(d-c))/(b-a);
    int i=a,j1=c,j2;
    do
    {
        s+=ds;
        j2=c+(int)s;
        if (j2>=j1)							// ���� ������ �� �������
            for (int j=j1;j<=j2;j++)		// ������ ����� (i,j)
            {
                int Point=j*xWindow+i;
                R[Point]=rColor;
                G[Point]=gColor;
                B[Point]=bColor;
            }
        else								// ���� ������ �������
            for (int j=j1;j>=j2;j--)
            {
                int Point=j*xWindow+i;
                R[Point]=rColor;
                G[Point]=gColor;
                B[Point]=bColor;
            }
        j1=j2;
        i++;
    }
    while (i<b);
}
// -----------------------------------------
void Line2(double x,double y)
{
    if (x>bWindow) x=bWindow;
    if (x<aWindow) x=aWindow;
    if (y>dWindow) y=dWindow;
    if (y<cWindow) y=cWindow;
    int xP=(int)((x-aWindow)*xMastab)+x0Point;
    int yP=(int)((y-cWindow)*yMastab)+y0Point;
    int a,b,c,d;
    if (xP>=xPoint)
    {
        a=xPoint;c=yPoint;
        b=xP;d=yP;
    }
    else
    {
        a=xP;c=yP;
        b=xPoint;d=yPoint;
    }
   	xPoint=xP;                              // ���������� ����� ���������� �������
    yPoint=yP;
				                            // ������ ������� [(a,c),(b,d)]
   	double s=0,ds;                          // ����� � ����� �� y �� ���� ��� �� x
    if (a==b) ds=d-c;
    else ds=((double)(d-c))/(b-a);
    int i=a,j1=c,j2;
    do
    {
        s+=ds;
        j2=c+(int)s;
        if (j2>=j1)							// ���� ������ �� �������
            for (int j=j1;j<=j2;j++)		// ������ ����� (i,j)
            {
                int Point=j*xWindow+i;
                R[Point]=R[Point+1]=R[Point+xWindow]=R[Point+xWindow+1]=rColor;
                G[Point]=G[Point+1]=G[Point+xWindow]=G[Point+xWindow+1]=gColor;
                B[Point]=B[Point+1]=B[Point+xWindow]=B[Point+xWindow+1]=bColor;
            }
        else								// ���� ������ �������
            for (int j=j1;j>=j2;j--)
            {
                int Point=j*xWindow+i;
                R[Point]=R[Point+1]=R[Point+xWindow]=R[Point+xWindow+1]=rColor;
                G[Point]=G[Point+1]=G[Point+xWindow]=G[Point+xWindow+1]=gColor;
                B[Point]=B[Point+1]=B[Point+xWindow]=B[Point+xWindow+1]=bColor;
            }
        j1=j2;
        i++;
    }
    while (i<b);
}
// -----------------------------------------
void Line3(double x,double y)
{
    if (x>bWindow) x=bWindow;
    if (x<aWindow) x=aWindow;
    if (y>dWindow) y=dWindow;
    if (y<cWindow) y=cWindow;
    int xP=(int)((x-aWindow)*xMastab)+x0Point;
    int yP=(int)((y-cWindow)*yMastab)+y0Point;
    int a,b,c,d;
    if (xP>=xPoint)
    {
        a=xPoint;c=yPoint;
        b=xP;d=yP;
    }
    else
    {
        a=xP;c=yP;
        b=xPoint;d=yPoint;
    }
   	xPoint=xP;                              // ���������� ����� ���������� �������
    yPoint=yP;
				                            // ������ ������� [(a,c),(b,d)]
   	double s=0,ds;                          // ����� � ����� �� y �� ���� ��� �� x
    if (a==b) ds=d-c;
    else ds=((double)(d-c))/(b-a);
    int i=a,j1=c,j2;
    do
    {
        s+=ds;
        j2=c+(int)s;
        if (j2>=j1)							// ���� ������ �� �������
            for (int j=j1;j<=j2;j++)		// ������ ����� (i,j)
            {
                int Point=j*xWindow+i;
                R[Point]=R[Point+1]=R[Point+2]=
                R[Point+xWindow]=R[Point+xWindow+1]=R[Point+xWindow+2]=
                R[Point+2*xWindow]=R[Point+2*xWindow+1]=R[Point+2*xWindow+2]=rColor;
                G[Point]=G[Point+1]=G[Point+2]=
                G[Point+xWindow]=G[Point+xWindow+1]=G[Point+xWindow+2]=
                G[Point+2*xWindow]=G[Point+2*xWindow+1]=G[Point+2*xWindow+2]=gColor;
                B[Point]=B[Point+1]=B[Point+2]=
                B[Point+xWindow]=B[Point+xWindow+1]=B[Point+xWindow+2]=
                B[Point+2*xWindow]=B[Point+2*xWindow+1]=B[Point+2*xWindow+2]=bColor;
            }
        else								// ���� ������ �������
            for (int j=j1;j>=j2;j--)
            {
                int Point=j*xWindow+i;
                R[Point]=R[Point+1]=R[Point+2]=
                R[Point+xWindow]=R[Point+xWindow+1]=R[Point+xWindow+2]=
                R[Point+2*xWindow]=R[Point+2*xWindow+1]=R[Point+2*xWindow+2]=rColor;
                G[Point]=G[Point+1]=G[Point+2]=
                G[Point+xWindow]=G[Point+xWindow+1]=G[Point+xWindow+2]=
                G[Point+2*xWindow]=G[Point+2*xWindow+1]=G[Point+2*xWindow+2]=gColor;
                B[Point]=B[Point+1]=B[Point+2]=
                B[Point+xWindow]=B[Point+xWindow+1]=B[Point+xWindow+2]=
                B[Point+2*xWindow]=B[Point+2*xWindow+1]=B[Point+2*xWindow+2]=bColor;
            }
        j1=j2;
        i++;
    }
    while (i<b);
}
