//				������� ��������� 
//				
//				���������� ������� Arth(x), ln(1+x), sin(x) � arcsin(x) � ���������
//
//				18 ������� 2014 �.				
//---------------------------------------------------------------------------------------

//#include "stdafx.h"
//#include <stdio.h>
//#include <math.h>
//#include <conio.h>
//#include <ctime>

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;

const int N=100;								// ������������ ����������� ����
int n;											// ����������� ��������
double eps;										// �������� ���������� �������

double x[N],y[N],dx[N];
int nMax,nM[N];
char fun[10],fun1[8]="Arth(x)",fun2[8]="ln(1+x)",fun3[8]="sin(x)",fun4[10]="arcsin(x)";

void Vvod();
void Vyvod();
double Arth(double x);
double ln(double x);
double f_sin(double x);
double f_arcsin(double x);

int main()
{

	Vvod();
	for (int i=0;i<n;i++)
	{
		y[i]=Arth(x[i]);
		nM[i]=nMax;
		dx[i]=fabs(x[i]-tanh(y[i]));
	}
	for (int i=0;i<7;i++) fun[i]=fun1[i];
	Vyvod();

	for (int i=0;i<n;i++)
	{
		y[i]=ln(x[i]);
		nM[i]=nMax;
		dx[i]=fabs(x[i]-exp(y[i])+1);
	}
	for (int i=0;i<7;i++) fun[i]=fun2[i];
	Vyvod();

	for (int i=0;i<n;i++)
	{
		y[i]=f_sin(x[i]);
		nM[i]=nMax;
		dx[i]=fabs(x[i]-asin(y[i]));
	}
	for (int i=0;i<7;i++) fun[i]=fun3[i];
	Vyvod();

	for (int i=0;i<n;i++)
	{
		y[i]=f_arcsin(x[i]);
		nM[i]=nMax;
		dx[i]=fabs(x[i]-sin(y[i]));
	}
	for (int i=0;i<10;i++) fun[i]=fun4[i];
	Vyvod();
}
//
//----------	���� ������
//
void Vvod()
{
	char		pust[100];
	float scan;
	FILE *fp;									// ��������� �� ����
	fp=fopen("in.txt","r");						// ������� ���� ��� ������
												// ������ �� �����
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&n);
	fscanf(fp,"%s",pust);
	for (int i=0;i<n;i++)
	{
		fscanf(fp,"%f",&scan);
		x[i]=scan;
	}
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);eps=scan;
	fclose(fp);									// ������� ���� ��� ������
}
//
//----------	����� ������
//
void Vyvod()
{
	FILE *fp;
	fp=fopen("out.txt","a");		 			// ������� ���� ��� ������
												// ������ � ����
	fprintf(fp,"  ���������� �������� ������� %s\n",fun);
	fprintf(fp,"  � ��������� eps = %12.9f\n\n",eps);
	fprintf(fp,"  x[i]      f(x[i])        �����������   ����������\n");
	fprintf(fp,"                                         ���������\n");
	for (int i=0;i<n;i++)
		fprintf(fp,"%7.3f     %10.7f     %12.10f   %5d\n",x[i],y[i],dx[i],nM[i]);
	fprintf(fp,"\n");
	fclose(fp);	
}
//
//----------
//
double Arth(double x)
{
	nMax=1;
	double s=0;
	double ai=x;
	for (int i=1; fabs(ai/i)>eps; i+=2,nMax++)
	{
		s+=ai/i;
		ai*=x*x;
	}
	return(s);
}
double ln(double x)
{
	nMax=1;
	double s=0;
	double ai=x;
	for (int i=1; fabs(ai/i)>eps; i++,nMax++)
	{
		s+=ai/i;
		ai*=-x;
	}
	return(s);
}
double f_sin(double x)
{
	nMax=1;
	double s=0;
	double ai=x;
	for (int i=3; fabs(ai)>eps; i+=2,nMax++)
	{
		s+=ai;
		ai*=-x*x/i/(i-1);
	}
	return(s);
}
double f_arcsin(double x)
{
	nMax=1;
	double s=x;
	double ai=x;
	for (int i=2; fabs(ai/(i-1))>eps; i+=2,nMax++)
	{
		ai*=x*x*(i-1)/i;
		s+=ai/(i+1);
	}
	return(s);
}
