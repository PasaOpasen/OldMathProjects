//				������� ��������� 
//				
//				�� 1.6 -- ������ ������ � ��������
//
//				06 ������ 2015 �.				
//---------------------------------------------------------------------------------------

//#include "stdafx.h"
//#include <stdio.h>
//#include <math.h>
//#include <conio.h>
//#include <ctime>

#include <cstdlib>
#include <iostream>
//#include <ctime>
//#include <math.h>

//using namespace std;

int n,sum;								// ������� �������, ����� ������
int *a;

void Vvod();
void Vyvod();
int Res();
#define A(i,j) a[(i)*n+j]

int main()
{
	Vvod();
	sum=Res();
	Vyvod();
}
void Vvod()
{
	char  pust[100];
	int scan;
	FILE *fp;								// ��������� �� ����
	fp=fopen("in.txt","r");					// ������� ���� ��� ������
										// ������ �� �����
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%d",&n);
	a=new int[n*n];
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	for (int i=0; i<n*n; i++) 
		fscanf(fp,"%d",&a[i]);
//	printf("a[%d] = %4d",9,a[9]);
//	getchar();
	fclose(fp);							// ������� ���� ��� ������
}
void Vyvod()
{
	FILE *fp;
	fp=fopen("out.txt","w");		 			// ������� ���� ��� ������
										// ������ � ����
	fprintf(fp,"  �������� ������\n\n");
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		fprintf(fp,"%3d",A(i,j));
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n\n  ����� ��������� ��������� �������\n");
	fprintf(fp,"  ��� �������� ���������� ����� %8d",sum);
	fclose(fp);	
}
//
//----------
//
int Res()
{
	#define sqr(x) (x)*(x)
	int s=0;
	for (int i=1;i<n;i++)
	for (int j=n-i;j<n;j++)
		s+=sqr(A(i,j));
	return (s);
}
