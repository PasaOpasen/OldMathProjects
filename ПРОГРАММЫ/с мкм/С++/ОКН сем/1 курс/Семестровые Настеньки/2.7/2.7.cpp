#include <cstdlib>
#include <iostream>
#include <stdio.h>
//#include "ReadImage.h"
#include <math.h>
#include "Graph.h"
using namespace std;

double	a,b,c,d,x0,eps,Nx,Ny,xn,xk;
double *p;
int	nRis,n;	
char pust[100];
float  scan;
FILE *fp=fopen("in.txt","r");	
FILE *pf=fopen("out.txt","w");

void Vvod();									
void line();									
double f(double x);
void Ris();
double ip(double x);


int main()
{
	Vvod();

	Ris();		
	line();

fclose(fp);
fclose(pf);	
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
	fscanf(fp,"%d",&nRis);
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%d",&n);

	p = new double [n+1];


	//fprintf(pf,"%f %f %f %f %f %f %d %d\n",a,b,c,d,Nx,Ny,nRis,n);


								
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
	SetColor(0,0,255);    			            // ������ ���� �����
	double step=(b-a)/nRis;
	double x=a;
	SetPoint(x,f(x));							// ������������� ������
	for (int i=0; i<nRis; i++)
	{ 
		x+=step;
		Line2(x,f(x));							// ������ �������, 
		// ����������� ������ � ������ (�,�)											// � ���������� ������ � ��� �����
	}

	CloseWindow();								// ��������� ���� (������� bmp-����)
}

void line()
{   
	double h=(b-a)/n;
	for (int i=0; i<=n;i++) p[i]=a+i*h;




	SetColor(0,255,0);    			            
	double step=(b-a)/nRis;
	double x=a;
	SetPoint(x,ip(x));							
	for (int i=0; i<nRis; i++)
	{ 
		x+=step;
		Line2(x,ip(x));							
											
	}

	CloseWindow();		


}


double f(double x)
{
	return (sin(8*x)+x*x);

}

double ip(double x)
{



	double ttt=0;
	double B;
	for (int i=0;i<=n;i++)
	{    B=1;
	     for(int j=0;j<=n;j++)
	     {z1:
	        if(j==i)
	         {j++;
	          goto z1;
	         }
	     else B*=(x-p[j])/(p[i]-p[j]);
	     }
	ttt+=f(p[i])*B;fprintf(pf,"%f \n",B);
	}

	return ttt;

}



