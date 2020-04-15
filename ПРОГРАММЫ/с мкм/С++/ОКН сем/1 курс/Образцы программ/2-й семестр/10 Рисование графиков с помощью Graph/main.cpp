//				��������� �������� � �������������� ���������� Graph
//				
//				21 ����� 2015 �.
//---------------------------------------------------------------------------------------

//#include "stdafx.h"
//#include <stdio.h>
//#include <math.h>
//#include <conio.h>
//#include <ctime>

#include <cstdlib>
#include <iostream>
//#include <ctime>
#include <math.h>
#include "Graph.h"


												// ����� ���������

double a,b,c,d,									// ������� �������
Nx,Ny;											// ���� ������� �� � � �� �
double pi=3.141592;
int	nRis;										// ���������� ����� �� x
int rC[2],gC[2],bC[2];
												// ���������� �������
double f1(double x);
double f2(double x);
void Vvod();
void Ris();
//------------------------------------------
int main()
{
	Vvod();
	Ris();
}
//------------------------------------------
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
	SetColor(rC[0],gC[0],bC[0]);    			// ������ ���� �����
	double step=(b-a)/nRis;
	double x=a;
	SetPoint(x,f1(x));							// ������������� ������
	for (int i=0; i<nRis; i++)
	{ 
		x+=step;
		Line2(x,f1(x));							// ������ �������, 
												// ����������� ������ � ������ (�,�)
												// � ���������� ������ � ��� �����
	}
												// ������ 2-� ������
	SetColor(rC[1],gC[1],bC[1]);    			// ������ ���� �����
	x=a;
	SetPoint(x,f2(x));							// ������������� ������
	for (int i=0; i<nRis; i++)
	{ 
		x+=step;
		Line(x,f2(x));							// ������ �������, 
												// ����������� ������ � ������ (�,�)
												// � ���������� ������ � ��� �����
	}
	CloseWindow();								// ��������� ���� (������� bmp-����)
}
//------------------------------------------
double f1(double x)
{
	return (sin(3*pi*x));
}
double f2(double x)
{
	return (sin(pi*x));
}
//------------------------------------------
void Vvod()
{
	char		pust[100];
	float		scan;							// ��������������� ���������� ��� ������ �� �����
	FILE *fp;									// ��������� �� ����
	fp=fopen("in.txt","r");						// ������� ���� ��� ������
												// ������ �� �����
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);a=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);b=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);c=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);d=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Nx=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);Ny=scan;
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&nRis);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%d",&rC[0]);fscanf(fp,"%d",&gC[0]);fscanf(fp,"%d",&bC[0]);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%d",&rC[1]);fscanf(fp,"%d",&gC[1]);fscanf(fp,"%d",&bC[1]);
	//    printf("nRis =%6d rC[0] =%3d  gC[1] =%3d\n",nRis,rC[0],gC[1]);
	//    printf("b =%6f c =%6f\n",b,c);
	//    getchar();


	fclose(fp);
}
