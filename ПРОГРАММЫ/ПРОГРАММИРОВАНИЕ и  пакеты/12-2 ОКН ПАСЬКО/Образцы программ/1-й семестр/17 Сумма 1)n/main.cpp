//				������� ��������� 
//				
//				����� 1/�
//
//				15 ������� 2015 �.				
//---------------------------------------------------------------------------------------

//#include "stdafx.h"
//#include <stdio.h>
//#include <math.h>
//#include <conio.h>
//#include <ctime>

#include <cstdlib>
#include <iostream>
#include <ctime>
//#include <math.h>

//using namespace std;

double sum;								// �����
double n_min,n_max;							// ������� ������ �����
int timeSum;

void Vvod();
void Vyvod();
void Res();

int main()
{
	Vvod();
	Res();
	Vyvod();
}
void Vvod()
{
	char  pust[100];
	float scan;
	FILE *fp;								// ��������� �� ����
	fp=fopen("in.txt","r");					// ������� ���� ��� ������
										// ������ �� �����
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%e",&scan);n_min=scan;
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%e",&scan);n_max=scan;
										// �������� ������������ ������
//	printf("n_max = %e",n_max);
//	getchar();
	fclose(fp);							// ������� ���� ��� ������
}
void Vyvod()
{
	FILE *fp;
	fp=fopen("out.txt","w");		 			// ������� ���� ��� ������
										// ������ � ����
	fprintf(fp,"  ���������� ����� sum_{i=n_min}^n_max (1/i)\n\n");
	fprintf(fp,"  n_min = %e\n",n_min);
	fprintf(fp,"  n_max = %e\n",n_max);
	fprintf(fp,"  �������� �����   = %18.16e\n",sum);
	//fprintf(fp,"  �������� 1/n_max = %18.16e\n",1./n_max);
    	fprintf(fp,"  ����� ���������� = %d ��",timeSum);
	fclose(fp);	
}
//
//----------
//
void Res()
{
	sum=0;
	clock_t	timeBegin,timeEnd;
    	timeBegin = clock();					// ����� ������ ����������
//	for (long long int i=(long long int)n_min;i<=n_max;i++)
//		sum+=1./i;
	for (double i=n_min;i<=n_max;i+=1)
		sum+=1/i;
	timeEnd = clock();						// ����� ��������� ����������
    	timeSum=timeEnd-timeBegin;
}
