//				������� ��������� 
//				
//				����-�����
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
//#include <math.h>


using namespace std;

int n,sum;								// ����������� �������, ����� ������
int a[100];

void Vvod();
void Vyvod();
void Res();

int main()
{
	printf("Rasmernost massiva n = (<= 100) \n");
	scanf("%d",&n);
	printf("Znachenie n ravno %5d\n",n);
	printf("Dlja prodolzenija -- <Enter>");
	getchar();
	getchar();
	Vvod();
	Res();
	Vyvod();
}
void Vvod()
{
	char  pust[100];
	int scan;
	FILE *fp;								// ��������� �� ����
	fp=fopen("in.txt","r");					// ������� ���� ��� ������
										// ������ �� �����
	fscanf(fp,"%s",pust);
    fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);
	for (int i=0; i<n; i++) 
	{
		fscanf(fp,"%d",&scan);
		a[i]=scan;
	}
										// �������� ������������ ������
	printf("a[%d] = %4d",n-1,a[n-1]);
	getchar();
	fclose(fp);							// ������� ���� ��� ������
}
void Vyvod()
{
	FILE *fp;
	fp=fopen("out.txt","w");		 			// ������� ���� ��� ������
	// ������ � ����
	fprintf(fp,"  �������� ������\n\n");
	int j=0;
	for (int i=0; i<n; i++)
	{
		if (j==10)
		{
			fprintf(fp,"\n");
			j=0;
		}
		fprintf(fp,"%3d",a[i]);
		j++;
	}
	fprintf(fp,"\n\n  ����� ��������� �������\n");
	fprintf(fp,"  ����� %8d",sum);
	fclose(fp);	
}
//
//----------
//
void Res()
{
	sum=0;
	for (int i=0;i<n;i++)
		sum+=a[i];
}
