//				���� ������� � �������������� ���������� Graph
//				
//				05.01.2015 �.
//---------------------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Graph.h"
#include <math.h>

using namespace std;


											// ����� ���������

double		T,								// ������� ���������� ����������
            g,                              // ��������� ���������� ������� (���� �� ��������� ���������� �����, �� 0)
			x_0,y_0,ugol,V,					// ��������� ���������, ���� ���������� � �������� ������
			Kvx,Kvy1,Kvy2,Kvy3,				// ��������� �������, �������� ������������� �������
			zx,zy,Macca,					// ���������� �������������� ���� � ��� �����
			b,c,d,							// ������ � ������� ������� �������
			Nx,Ny;                          // ���� ������� �� � � �� �

int		    n;								// ���������� ����� �� �������

											// ���������� �������
double fx(double t,double x,double x1,double y,double y1);
double fy(double t,double x,double x1,double y,double y1);
double Kv(double y);						// ������������� �������
void Vvod();
//------------------------------------------
int main()
{
	Vvod();
	double pi=3.141592;
	SetColor(250,250,255);                  // ������ ������� ���� ����
    SetWindow(0,b,c,d);                     // ������ ���� (������� ������� R,G,B)
                                            // � ��������� [0,b]x[c,d]
    SetColor(0,0,0);                        // ������ ���� ������������ ����
	xyLine(0,0,Nx,Ny);                      // ������ ���, �������������� � �. (0,0)
	                                        // � ����� ������� �� � ������ Nx
	                                        // � Ny -- �� �
											// ������ ������������� ����
	{
		SetColor(50,0,100);    			    // ������ ���� �����

		double Psi=0,d=0.25;
		double s=2*pi/20;
		SetPoint(zx+d,zy);                  // ������������� ������
		for (int i=0; i<20; i++)
		{ 
			Psi+=s;
			double x=zx+d*cos(Psi), y=zy+d*sin(Psi);
			Line(x,y);                      // ������ �������, 
                                            // ����������� ������ � ������ (�,�)
                                            // � ���������� ������ � ��� �����
		}
	}
											// ������� ���������� �������
	double tau=T/n;
	double x=x_0,y=y_0,x1=V*cos(pi*ugol/180),y1=V*sin(pi*ugol/180);
	SetColor(200,0,0);
	SetPoint(x,y);

	for(double t=0;((t<=T)&&(y>=0));t+=tau)
	{
		x+=tau*x1;
		x1+=tau*fx(t,x,x1,y,y1);
		y+=tau*y1;
		y1+=tau*fy(t,x,x1,y,y1);
		Line(x,y);
	}
    CloseWindow();                          // ��������� ���� (������� bmp-����)
}
//------------------------------------------
double fx(double t,double x,double x1,double y,double y1)
{
	double r=(zx-x)*(zx-x)+(zy-y)*(zy-y);
	double R=(r<0.001)? 0.001:r;
	return(-Kv(y)*x1*x1*x1+Macca/R*/*cos*/((zx-x)/sqrt(R)));
}
//------------------------------------------
double fy(double t,double x,double x1,double y,double y1)
{
	//double g=9.81;
	double r=(zx-x)*(zx-x)+(zy-y)*(zy-y);
	double R=(r<0.001)? 0.001:r;
	return(-g-Kv(y)*y1*y1*y1+Macca/R*/*sin*/((zy-y)/sqrt(R)));
}
//------------------------------------------
double Kv(double y)
{
	double Kvy;
	if (y<1) Kvy=Kvy1;
	else 
	{
		if (y<4) Kvy=Kvy2;
		else Kvy=Kvy3;
	}
	return(Kvx*Kvy);
}
//------------------------------------------
void Vvod()
{
	char		pust[100];
	float		scan;						// ��������������� ���������� ��� ������ �� �����
	FILE *fp;								// ��������� �� ����
	fp=fopen("in.txt","r");					// ������� ���� ��� ������
	                                        // ������ �� �����
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);T=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);b=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);c=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);d=scan;
	fscanf(fp,"%s",pust);
    fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Nx=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Ny=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);x_0=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);y_0=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);ugol=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);V=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%d",&n);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Kvx=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Kvy1=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Kvy2=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Kvy3=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);g=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);zx=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);zy=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Macca=scan;
	fclose(fp);
}
