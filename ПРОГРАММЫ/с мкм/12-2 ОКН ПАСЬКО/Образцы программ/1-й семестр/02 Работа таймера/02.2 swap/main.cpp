//				������� ��������� 
//				
//				������ �������
//
//				08 ������ 2015 �.				
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

int n;                                      		// ����������� ��������
double *a,*b,ai,bi;
int *a_i,*b_i,param;
int timeSwap1,timeSwap2;

#define swap_d(x,y) {double s=x;x=y;y=s;}
#define swap_i(x,y) {int s=x;x=y;y=s;}
#define swap2(x,y) {x+=y;y=x-y;x-=y;}

void Vvod();
void Vyvod();
void Generation_d(int n);                          	// �������� �������� a � b
void Generation_i(int n);
void Res_d();
void Res_i();

int main()
{
    	Vvod();
    	if (param==0)
    	{
    		Generation_d(n);
	    	Res_d();
		Vyvod();
	}
	else
	{
    		Generation_i(n);
	    	Res_i();
		Vyvod();
	}
}
void Vvod()
{
    	char pust[100];
    	float 	scan;
    	FILE *fp;								// ��������� �� ����
    	fp=fopen("in.txt","r");				    	// ������� ���� ��� ������
                                            		// ������ �� �����
    	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);fscanf(fp,"%d",&n);
    	fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);ai=scan;
    	fscanf(fp,"%s",pust);fscanf(fp,"%f",&scan);bi=scan;
    	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%d",&param);
//    printf("n =%6d ai =%2d  bi =%2d\n",n,ai,bi);
//    getchar();
    	fclose(fp);							// ������� ���� ��� ������
}
void Vyvod()
{
    	FILE *fp;
    	fp=fopen("out.txt","w");		 			// ������� ���� ��� ������
				                            	// ������ � ����
				                            	
    	//fprintf(fp,"  a[100] = %4.2f  b[100] = %4.2f\n\n",a[100],b[100]);
    	fprintf(fp,"  ����� ���������� swap1 ����� %d\n",timeSwap1);
    	fprintf(fp,"  ����� ���������� swap2 ����� %d\n",timeSwap2);
    	fclose(fp);	
}
void Generation_d(int n)
{
    	a = new double[n];
   	b = new double[n];
    	for (int i=0;i<n;i++)
    	{
        	a[i]=ai;
        	b[i]=bi;
    	}
}
void Generation_i(int n)
{
    	a_i = new int[n];
   	b_i = new int[n];
   	int ai_i=(int)ai,bi_i=(int)bi;
    	for (int i=0;i<n;i++)
    	{
        	a_i[i]=ai_i;
        	b_i[i]=bi_i;
    	}
}
//
//----------
//
void Res_d()
{
    	clock_t	timeBegin,timeEnd;
    	timeBegin = clock();					// ����� ������ ����������

    	for (int i=0;i<n;i++)
    		swap_d(a[i],b[i]);
    	timeEnd = clock();						// ����� ��������� ����������
    	timeSwap1=timeEnd-timeBegin;
    	
	timeBegin = clock();
    	for (int i=0;i<n;i++)
   		swap2(a[i],b[i]);
    	timeEnd = clock();						// ����� ��������� ����������
    	timeSwap2=timeEnd-timeBegin;
}
void Res_i()
{
    	clock_t	timeBegin,timeEnd;
    	timeBegin = clock();					// ����� ������ ����������

    	for (int i=0;i<n;i++)
    		swap_i(a_i[i],b_i[i]);
    	timeEnd = clock();						// ����� ��������� ����������
    	timeSwap1=timeEnd-timeBegin;
    	
	timeBegin = clock();
    	for (int i=0;i<n;i++)
   		swap2(a_i[i],b_i[i]);
    	timeEnd = clock();						// ����� ��������� ����������
    	timeSwap2=timeEnd-timeBegin;
}
