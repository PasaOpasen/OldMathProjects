//				������� ��������� 
//				
//				������ ������ � ��������
//				(������ � ���� � �������� �������)
//				27 �������� 2015 �.				
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

int n=10;                                   		// ����������� �������
int a[10];


void Vvod();
void Res();


int main()
{
    	Vvod();
    	Res();
}
void Vvod()
{
    	char  pust[100];
    	int scan;
    	FILE *fp;								// ��������� �� ����
    	fp=fopen("in.txt","r");				    	// ������� ���� ��� ������
                                            		// ������ �� �����
    	fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);
    	for (int i=0; i<n; i++)
	    {
			fscanf(fp,"%d",&scan); 
			a[i]=scan;
		}

    	fclose(fp);							// ������� ���� ��� ������
}
void Res()
{
    	FILE *fp;
    	fp=fopen("out.txt","w");		 			// ������� ���� ��� ������
				                            	// ������ � ����
    	fprintf(fp,"  ������ ������� � ���� � �������� �������\n\n");
    	fprintf(fp,"  �������� ������\n\n");
    	for (int i=0; i<n; i++) 
		fprintf(fp,"%3d",a[i]);
    	fprintf(fp,"\n\n  ������ � �������� �������\n\n");
    	for (int i=0; i<n; i++)
    		fprintf(fp,"%3d",a[n-1-i]);
    	fclose(fp);	
}
