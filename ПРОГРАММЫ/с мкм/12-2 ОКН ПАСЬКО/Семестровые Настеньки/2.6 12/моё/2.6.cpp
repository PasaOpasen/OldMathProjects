#include <cstdlib>
#include <iostream>
#include <stdio.h>
//#include "ReadImage.h"
#include <math.h>
#include "Graph.h"
using namespace std;

double	a,b,c,d,x0,eps,Nx,Ny,xn,xk;
int	nRis;	
char pust[100];
float  scan;
FILE *fp=fopen("in.txt","r");	
FILE *pf=fopen("out.txt","w");

void Vvod();									
void line();									
double f(double x);
double df(double x);
double fy(double x,double xk);
void Ris();
void risk(double xk,int k);


int main()
{
	Vvod();

	Ris();		
	line();

}


void Vvod()
{

	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan); a=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);b=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);c=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);d=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);Nx=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);Ny=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);x0=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);eps=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);nRis=(int)scan;

	//fprintf(pf,"%f %f %f %f %f %f %f %f %d\n",a,b,c,d,Nx,Ny,x0,eps,nRis);


	fclose(fp);

}



void line()
{   int k=0;


double x=x0;
//h=0.00001;
//double du=(f(x+h)-f(x))/h;
//du =df(x);

while(fabs(f(x))>=eps)
{
//x=x-f(x)/du;
x=x-f(x)/df(x);
k++;

if (k==1) risk(x,k);
if (k==2) risk(x,k);
}



//	 if (f(a)*f(b)>0) // ���� ����� ������� �� ����� ������� ����������, �� ����� ��� �����
//                  fprintf(pf,"��� �����");
//                           else
//                           {
//                           if (f(a)*d2f(a)>0) xk  = a; // ��� ������ ��������� ����� ��������� f(x0)*d2f(x0)>0 ?
//                                  else xk = b;
//                           xn = xk-f(xk)/df(xk); // ������� ������ �����������
//                        
//                           while(fabs(xk-xn) > eps) // ���� �� ��������� ����������� ��������, ����� ���������� ���������
//                           {
//                                  xk = xn;
//                                  xn = xk-f(xk)/df(xk); // ��������������� ������� �������
//                           }
//                    fprintf(pf,"������ ");fprintf(pf,"%f \n",xn);
//                    }


fprintf(pf,"����������� ");fprintf(pf,"%f \n",eps);
fprintf(pf,"����� �������� "); fprintf(pf,"%d \n",k);
fprintf(pf,"������ ");fprintf(pf,"%f \n",x);
x0=x;

fclose(pf);		

}


void Ris()
{  
	SetColor(250,250,250);						// ������ ������� ���� ����
	SetWindow(a,b,c,d);							// ������ ���� (������� ������� R,G,B)
	// � ��������� [a,b]x[c,d]
	SetColor(0,0,0);							// ������ ���� ������������ ����
	xyLine(a,0,Nx,Ny);							// ������ ���, �������������� � �. (a,0)
	// � ����� ������� �� � ������ Nx
	// � Ny -- �� �
	// ������ 1-� ������
	SetColor(0,255,0);    			            // ������ ���� �����
	double step=(b-a)/nRis;
	double x=b;
	SetPoint(x,f(x));
						// ������������� ������
	for (int i=0; i<nRis; i++)
	{ 
		x-=step;
		if ((f(x)>c+eps)&(f(x)<d-eps))Line2(x,f(x));
		//if(f(x)<=c+eps) break;								// ������ �������, 
		// ����������� ������ � ������ (�,�)											// � ���������� ������ � ��� �����
	}

	CloseWindow();								// ��������� ���� (������� bmp-����)
}



void risk(double xk, int k)
{											
	SetColor(30*k,10*k,50);    			            // ������ ���� �����
	double step=(b-a)/nRis;
	double x=b;
	SetPoint(x,fy(x,xk));							// ������������� ������
	for (int i=0; i<nRis; i++)
	{ 
		x-=step;
		Line2(x,fy(x,xk));
		if(fy(x,xk)<=0) break;							// ������ �������, 
		// ����������� ������ � ������ (�,�)											// � ���������� ������ � ��� �����
	}

	CloseWindow();

}





double f(double x)
{
	return (sin(x)+pow(x,7)-1);
	//return x*x-2;
}

double df(double x)
{    return (cos(x)+7*pow(x,6));
	//return 2*x;
}

double fy(double x,double xk)
{
double h=0.00001;
double du=(f(xk+h)-f(xk))/h;

//return (du*(x-xk)+f(xk));
return (df(xk)*(x-xk)+f(xk));
}



