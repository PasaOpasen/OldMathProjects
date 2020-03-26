//				������� �� ��� ���
//				�������� �������
//				(� �������������� ������ 3-� ������������ ��������)
//				
//				23.10.2017 �.
//---------------------------------------------------------------------------------------

//#include "stdafx.h"
//#include <stdio.h>
//#include <math.h>
//#include <conio.h>

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Graph2016.h"
#include <math.h>
//
//using namespace std;


											// ����� ���������

double		a,b;							// ������� �������
double		c,d,							// ������ � ������� ������� �������
			Nx,Ny;							// ��� ������� �����. ����� �� � � �
int			n,k;							// *���������� ����� �����, �������� ������� �������
const double pi=3.14159265360;
double		*f,*y;

											// ���������� �������

double F(double x);							// ������ �����
double u(double x);							// ������ �������
double sqr(double x);						//
void Vvod();								// ������ ������
void Vyvod(double x,double y);				// ����� ����������
void Progon_3();							// ����� 3-�� ������������ ��������
double Nevas();
double PogRes();
void Ris();							    	// ��������� �������
//
//-------------------------------------------------------------------
//
int main()
{
	Vvod();
	Progon_3();
	Vyvod(Nevas(),PogRes());
	Ris();
}
//-------------------------------------------------------------------
#define sqr(x) (x)*(x)
//---------- ������ �����
double F(double x){return(-pi*pi*k*k*cos(pi*k*x));}
//---------- ������ �������
double u(double x){return(cos(pi*k*x));}
//---------- ������ ������
void Vvod()
{
	char		pust[100];
	FILE *fp;
	if ((fp=fopen("������.txt","r")) == 0)
	{
		printf("\n NO FILE");
		getchar();
		//exit(0);
	}
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%lf",&a);
	fscanf(fp,"%s",pust);fscanf(fp,"%lf",&b);
	fscanf(fp,"%s",pust);fscanf(fp,"%lf",&c);
	fscanf(fp,"%s",pust);fscanf(fp,"%lf",&d);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%lf",&Nx);
	fscanf(fp,"%s",pust);fscanf(fp,"%lf",&Ny);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&n);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&k);
	f = new double[n+1];
	y = new double[n+1];
	fclose(fp);
}
//---------- ����� ����������
void Vyvod(double x,double y)
{
	FILE *fp;
	fp=fopen("out.txt","w");
	fprintf(fp,"   ������� ������� ������ ��� ��� 2-�� �������:\n\n");
	fprintf(fp,"   ����������� ����������� ������ \n");
	fprintf(fp,"   �����                        %10d\n",n);
	fprintf(fp,"   ������� ������� ���� �����   %10.8f\n",x);
	fprintf(fp,"   ����������� ������������� �������\n");
	fprintf(fp,"   �����                        %10.8f",y);
	fclose(fp);
}
//---------- ����� 3-� ������������ ��������
void Progon_3()
{
	double *alpha,*betta;
	alpha = new double[n];
	betta = new double[n];
	double 
		u0=u(0),
		u1=u(1);
	double	
		b0,c0,								// 0-� ������
		ai,bi,ci,							// i-� ������, i=1,n-1
		an,bn;								// n-� ������
	//---------- ��������� ��� 1-� ������� �������    
	b0=1;c0=0;
	ai=1;bi=-2;ci=1;
	an=0;bn=1;
	{
		double h=(b-a)/n;
		double x=h;
		double h2=h*h;
		for(int i=1; i<n; i++)
		{
			f[i]=h2*F(x);
			x+=h;
		}
		f[0]=u0;
		f[n]=u1;
	}
	//---------- ������� ����
	alpha[n]=-an/bn;
	betta[n]=f[n]/bn;
	for (int i=n-1; i>=1; i--)
	{
		double s=alpha[i+1]*ci+bi;
		alpha[i]=-ai/s;
		betta[i]=(f[i]-betta[i+1]*ci)/s;
	}
	y[0]=(f[0]-c0*betta[1])/(b0+alpha[1]*c0);
	for (int i=1; i<=n; i++) y[i]=alpha[i]*y[i-1]+betta[i];
}
//---------- ���������� ������� ������� ����
double Nevas()
{
#define sqr(x) (x)*(x)
	double	
		b0,c0,								// 0-� ������
		ai,bi,ci,							// i-� ������, i=1,n-1
		an,bn;								// n-� ������
	//---------- ��������� ��� 1-� ������� �������    
	b0=1;c0=0;
	ai=1;bi=-2;ci=1;
	an=0;bn=1;
	double s=0;
	for (int i=1; i<n; i++) 
		s+=sqr(ai*y[i-1]+bi*y[i]+ci*y[i+1]-f[i]);
	s+=sqr(b0*y[0]+c0*y[1]-f[0])+sqr(an*y[n-1]+bn*y[n]-f[n]);
	return s;
}
//---------- ���������� ����������� ������������ �������
double PogRes()
{
	double s,max=0;
	double h=(b-a)/n;
	double x=a;
	for (int i=0; i<=n; i++)
	{
		s=fabs(y[i]-u(x)); 
		if (max<s) max=s;
		x+=h;
	}
	return max;
}
//---------- ��������� ��������
void Ris()
{
	const int	M=300;						// ���������� ����� ���������
	double h_p=(b-a)/M;						// ��� ���������
	double h=(b-a)/n;						// ��� �����
	//---------- �������� ����
	SetColor(250,250,255);
	SetWindow(a,b,c,d);
	SetColor(0,0,0);
	xyLine(0,0,Nx,Ny);

	//---------- ������ ������� �������
	double x=a;
	double Y=u(0);
	SetColor(0,180,120);
	SetPoint(x,Y);
	for (int i=1; i<=M; i++)
	{
		x+=h_p;
		Y=u(x);
		Line3(x,Y);
	}
	//---------- ������ ������������� ������� �� ����� ��
	x=a;
	Y=y[0];
	SetColor(200,0,50);
	SetPoint(x,Y);
	for (int i=1; i<=n; i++)
	{
		x+=h;
		Y=y[i];
		Line(x,Y);
	}
	CloseWindow("������.bmp");
}
