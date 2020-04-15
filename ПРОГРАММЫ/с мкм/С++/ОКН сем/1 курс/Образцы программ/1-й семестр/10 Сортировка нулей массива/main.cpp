//				��������� ���������� �������
//				(������� �������� -- ������; 
//				������� ��������� ��������� �����������)
//				23 ������� 2015 �.				
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

using namespace std;

int n,k,param1,param2,param3,time0;						// 
int *a;
//int n=20;
//int a[20]={1,0,0,4,5,7,0,0,0,0,10,11,12,0,0,15,16,0,18,19};

#define	swap(x,y)	{int s=x;x=y;y=s;}

void Vvod();
void Gena();								// ��������� �������
void Sort_0();								//
void Sort_1();	
void Vyvod_0();
void Vyvod_1();

int main()
{
    	Vvod();
    	Gena();
    	Sort_0();
    	Vyvod_0();
    	Gena();
   	Sort_1();
	Vyvod_1();
}
void Vvod()
{
    	char  pust[100];
    	FILE *fp;								// ��������� �� ����
    	fp=fopen("in.txt","r");				    	// ������� ���� ��� ������
                                            		// ������ �� �����
    	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);
    	fscanf(fp,"%d",&n);
    	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
    	fscanf(fp,"%d",&param1);
    	fscanf(fp,"%s",pust);
    	fscanf(fp,"%d",&k);
    	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);
    	fscanf(fp,"%d",&param2);
    	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
    	fscanf(fp,"%d",&param3);
//	printf("%d  %d %d",param1,param2,param3);
//    	getchar();
    	fclose(fp);							// ������� ���� ��� ������
}
void Gena()
{
	a = new int[n];
	if (param1==0)
	{
		for (int i=0;i<n;i++) a[i]=0;
		for (int i=0;i*k<n;i++) a[i*k+1]=i+1;
	}
	else
	{
		for (int i=0;i<n;i++) a[i]=i;
		for (int i=0;i*k<n;i++) a[i*k+1]=0;
		a[5]=a[6]=a[7]=0;
	}
}
void Sort_0()
{
	clock_t	timeBegin,timeEnd;
    	timeBegin = clock();					// ����� ������ ����������
	int m=0;
	for (int i=0; i<n;i++)
	{
		if (a[i]!=0)
		{
			swap(a[i],a[m]);
			m++;
		}
	}
    	timeEnd = clock();
    	time0=timeEnd-timeBegin;
}
void Sort_1()
{
	clock_t	timeBegin,timeEnd;
    	timeBegin = clock();					// ����� ������ ����������
	int m=0;
	for (m=n-1;m>=0;m--)
	if (a[m]!=0) break;						// m ��������� �� �������� �������
	if (param2==0)
	for (int i=m-1; i>=0;i--)				// ������� ��� ���������� �������
	{
		if (a[i]==0)
		{
			swap(a[i],a[m]);
			m--;
		}
	}
	else
	for (int i=m-1; i>=0;i--)				// ������� � ����������� �������
	{
		if (a[i]==0)
		{
			for (int j=i;j<m;j++) 
			a[j]=a[j+1];
			a[m]=0;
			m--;
		}
	}
    	timeEnd = clock();
    	time0=timeEnd-timeBegin;
}
void Vyvod_0()
{
    	FILE *fp;
    	fp=fopen("out.txt","w");		 			// ������� ���� ��� ������
				                            	// ������ � ����
    	fprintf(fp,"  ���������� �������, ������� �������� -- ������\n\n");
    	fprintf(fp,"  ����������� ������� = %d\n",n);
	if (param1==0)
	fprintf(fp,"  ������ �������� ����� �����\n\n");
	else
	fprintf(fp,"  ������ �������� ���� �����\n\n");
	fprintf(fp,"  ������ ���������� (������ ����� �������),\n");
	fprintf(fp,"  ������� ��������� ��������� �����������\n\n");
	if (param3==0) ;
	else
	{
    		fprintf(fp,"  ������ 20 ��������� ���������������� �������:\n\n");
    		int j=1;
    		for (int i=0; i < 20; i++,j++)
    		{    
			fprintf(fp,"%10d",a[i]);
			if (j==10)
			{
				j=0;
			fprintf(fp,"\n");
			}
		}
		fprintf(fp,"\n\n  ��������� 40 ��������� ���������������� �������:\n\n");
    		j=1;
    		for (int i=0; i < 40; i++,j++)
    		{    
			fprintf(fp,"%10d",a[n-40+i]);
			if (j==10)
			{
				j=0;
				fprintf(fp,"\n");
			}
		}
		fprintf(fp,"\n\n");
	}
    	fprintf(fp,"  ����� ���������� = %5d ��",time0);
    	fclose(fp);	
}
void Vyvod_1()
{
    	FILE *fp;
    	fp=fopen("out.txt","a");		 			// ������� ���� ��� ������
				                            	// ������ � ����
    	fprintf(fp,"\n\n  ������ ���������� (������ ������ ������),\n");
	if (param2==0)
	fprintf(fp,"  ������� ��������� ��������� �� �����������\n\n");
	else
	fprintf(fp,"  ������� ��������� ��������� �����������\n\n");
	if (param3==0) ;
	else
	{
    		fprintf(fp,"  ������ 20 ��������� ���������������� �������:\n\n");
    		int j=1;
    		for (int i=0; i < 20; i++,j++)
    		{    
			fprintf(fp,"%10d",a[i]);
			if (j==10)
			{
				j=0;
				fprintf(fp,"\n");
			}
		}
		fprintf(fp,"\n\n  ��������� 40 ��������� ���������������� �������:\n\n");
    		j=1;
    		for (int i=0; i < 40; i++,j++)
    		{    
			fprintf(fp,"%10d",a[n-40+i]);
			if (j==10)
			{
				j=0;
				fprintf(fp,"\n");
			}
		}
		fprintf(fp,"\n\n");
	}
    	fprintf(fp,"  ����� ���������� = %5d ��",time0);
    	fclose(fp);	
}
