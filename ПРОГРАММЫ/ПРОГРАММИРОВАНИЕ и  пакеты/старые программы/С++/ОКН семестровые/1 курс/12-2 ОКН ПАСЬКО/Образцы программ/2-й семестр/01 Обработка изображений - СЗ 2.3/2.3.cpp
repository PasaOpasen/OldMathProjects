//				������� ��������� 
//				
//				��������� ��������� �����������
//				� ������� 24-���������� bmp-������
//				13 ������� 2015 �.				
//---------------------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "ReadImage.h"
#include <math.h>

using namespace std;

int		h,w;
char		*R,*G,*B;
int		kr,kg,kb,kx,variant;

void Vvod();
void Ris1();									// ����������� ������������ �����
void Ris2();									// ����������� �������
int f(int x,int y);
//---------------------------------------------------------------------------------------
int main()
{
	Vvod();
	GetSize("input3.bmp", &h, &w);				// ������ ������� ����� � ��������
											// (w -- ������, h -- ������)
	R = new char[h*w];
	G = new char[h*w];
	B = new char[h*w];
	ReadImageFromFile("input3.bmp",B,G,R);			// ��������� �������� �������� ������������ �����������:
											// R -- �������, G -- �������, B -- �����
	//switch (variant)
//	{
//		case 1:Ris1();break;
//		case 2:
             Ris2();
  //           break;
//	}
	WriteImage("output2.bmp",B,G,R);				// ������� bmp-���� � ���������� � ���� ���������� "�����������"
}
//---------------------------------------------------------------------------------------
void Vvod()
{
	char	pust[100];
	float  scan;
	FILE *fp;									// ��������� �� ����
	fp=fopen("in.txt","r");						// ������� ���� ��� ������
											// ������ �� �����
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&kr);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&kg);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&kb);
	
	//fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
//	fscanf(fp,"%d",&kx);fscanf(fp,"%s",pust);
//	fscanf(fp,"%s",pust);
//	fscanf(fp,"%d",&kx);fscanf(fp,"%s",pust);
//	fscanf(fp,"%s",pust);fscanf(fp,"%d",&variant);
//	
	fclose(fp);								// ������� ���� ��� ������
}
////---------------------------------------------------------------------------------------
//void Ris1()
//{
//	double sd=1,								// ��������� ��������� �������
//											// (����������� �������, ��� ��� �����, ��� =0)
//	dsd=(double)(w-kx+1)/h;						// ����� �� ��������� �� ���� ��� �� �����������
//											// � ������ ������ ������
//	int sdv;
//	for (int i=0;i<h;i++)
//	{
//		sdv=(int)sd;
//		for (int j=sdv;j<sdv+kx;j++)
//		{
//			R[i*w+j]=kr;
//			G[i*w+j]=kg;
//			B[i*w+j]=kb;
//		}
//		sd+=dsd;
//	}
//	sd=1;
//	for (int i=h-1;i>=0;i--)
//	{
//		sdv=(int)sd;
//		for (int j=sdv;j<sdv+kx;j++)
//		{
//			R[i*w+j]=kr;
//			G[i*w+j]=kg;
//			B[i*w+j]=kb;
//		}
//		sd+=dsd;
//	}   
//}
////---------------------------------------------------------------------------------------
void Ris2()
{ 
    
	for (int y=0;y<h;y++)
	for (int x=0;x<w;x++)
		{ 
             int r=R[y*w+x];if(r<0) r=r+255;
             int g=G[y*w+x];if(g<0) g=g+255;
             int b=B[y*w+x];if(b<0) b=b+255;
             
             int s=(r+g+b)/3;
              


if(s > 127) 
s = s+(int)((255-s)*0.3);
if(s < 127) s = s-(int)(s*0.3);

            R[y*w+x]=s;
			G[y*w+x]=s;
			B[y*w+x]=s;
		}
}
