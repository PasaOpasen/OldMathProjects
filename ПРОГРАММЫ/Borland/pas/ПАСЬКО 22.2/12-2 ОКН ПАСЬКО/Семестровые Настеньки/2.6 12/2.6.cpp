#include <cstdlib>
#include <iostream>
#include <stdio.h>
//#include "ReadImage.h"
#include <math.h>
#include "Graph.h"
using namespace std;

double	a,b,c,d,x1, x2,eps,Nx,Ny,xn,xk;
int	nRis;	
char pust[100];
float  scan;
FILE *fp=fopen("in.txt","r");	
FILE *pf=fopen("out.txt","w");

void Vvod();									
void line();									
double f(double x);
double df(double x);
double fy(double x,double x1,double x2);
void Ris();
void risk(double x1,double x2,int k);


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
	fscanf(fp,"%f",&scan);x1=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);x2=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);eps=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%f",&scan);nRis=(int)scan;

	//fprintf(pf,"%f %f %f %f %f %f %f %f %f %d\n",a,b,c,d,Nx,Ny,x1,x2,eps,nRis);


	fclose(fp);

}



void line()
{   int k=0;

while(fabs(f(c))>=eps)
{
risk(x1,x2,k);
c= x1-f(x1)/(f(x2)-f(x1))*(x2-x1);
if(f(c)*f(x1)>0) x1=c;
else x2=c;
k++;

}


fprintf(pf,"����������� ");fprintf(pf,"%f \n",eps);
fprintf(pf,"����� �������� "); fprintf(pf,"%d \n",k);
fprintf(pf,"������ ");fprintf(pf,"%f \n",x1);

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



void risk(double x1,double x2,int k)
{											
	SetColor(30*k,10*k,50);    			            // ������ ���� �����
	double step=(b-a)/nRis;
	double x=b;
	SetPoint(x,fy(x,x1,x2));							// ������������� ������
	for (int i=0; i<nRis; i++)
	{ 
		x-=step;
		Line2(x,fy(x,x1,x2));
		
		if(fy(x,x1,x2)<=f(x1)) break;							// ������ �������, 
		// ����������� ������ � ������ (�,�)											// � ���������� ������ � ��� �����
	}

	CloseWindow();

}





double f(double x)
{
	return (sin(x)+pow(x,8)-1);
}

double fy(double x,double x1,double x2)
{

return f(x1)+(f(x2)-f(x1))/(x2-x1)*(x-x1); 
}



