//              ������� ��������
//              ��� ����������� �������� ������ ������ ��������
//
//              13 �������� 2014 �.

#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

int a,n;

void Vvod();

int main()
{
    	FILE *fp;
    	fp=fopen("out.txt","w");		 			// ������� ���� ��� ������
				                         	// ������ � ����
    	Vvod();
    	fprintf(fp,"  ���������� %d^n\n\n",a);
    	fprintf(fp,"  ������ int \n\n");
    	int P2n=1;
    	for(int i=1; i<=n; i++)
    	{
          P2n*=a;
          fprintf(fp,"  i = %3d   %d^%-2d = %12d\n",i,a,i,P2n);
    	}

    	fprintf(fp,"\n\n  ������ long int\n\n");
    	long int longP2n=1;
    	for(int i=1; i<=n; i++)
    	{
          longP2n*=a;
          fprintf(fp,"  i = %3d   %d^%-2d = %12d\n",i,a,i,longP2n);
    	}
    
    	fprintf(fp,"\n\n  ������ float\n\n");
    	float floatP2n=1;
    	for(int i=1; i<=n; i++)
    	{
          floatP2n*=a;
          fprintf(fp,"  i = %3d   %d^%-2d = %22.f\n",i,a,i,floatP2n);
    	}   
      
    	fprintf(fp,"\n\n  ������ double\n\n");
    	double dobleP2n=1;
    	for(int i=1; i<=n; i++)
    	{
          dobleP2n*=a;
          fprintf(fp,"  i = %3d   %d^%-2d = %22.f\n",i,a,i,dobleP2n);
    	}      
    	fclose(fp);  
}
void Vvod()
{
     char		pust[100];
     float	scan;
    	FILE *fp;								// ��������� �� ����
    	fp=fopen("in.txt","r");			     	// ������� ���� ��� ������
       									// ������ �� �����
    	fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);fscanf(fp,"%d",&a);
    	fscanf(fp,"%s",pust);fscanf(fp,"%d",&n);
    	fclose(fp);							// ������� ���� ��� ������
}
