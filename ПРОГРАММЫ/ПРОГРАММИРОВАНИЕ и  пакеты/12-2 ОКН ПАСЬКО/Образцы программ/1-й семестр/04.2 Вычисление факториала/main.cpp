//              ������� ��������
//              ��� ����������� �������� ������ ������ ��������
//
//              13 �������� 2014 �.

#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

int	n;

void Vvod();

int main()
{
    	FILE *fp;
    	fp=fopen("out.txt","w");		 			// ������� ���� ��� ������
				                         	// ������ � ����
    	fprintf(fp,"  ���������� ����������\n\n");
    	fprintf(fp,"  ������ int\n\n");
    	Vvod();
    	int fakt=1;
    	for(int i=1; i<=n; i++)
    	{
          fakt*=i;
          fprintf(fp,"  i = %3d   %2d! = %12d\n",i,i,fakt);
    	}

    	fprintf(fp,"\n\n  ������ long int\n\n");
    	long int longfakt=1;
    	for(int i=1; i<=n; i++)
    	{
          longfakt*=i;
          fprintf(fp,"  i = %3d   %2d! = %12d\n",i,i,longfakt);
    	}
    
    	fprintf(fp,"\n\n  ������ float\n\n");
    	float floatfakt=1;
    	for(int i=1; i<=n; i++)
    	{
          floatfakt*=i;
          fprintf(fp,"  i = %3d   %2d! = %22.f\n",i,i,floatfakt);
    	}   
      
    	fprintf(fp,"\n\n  ������ double\n\n");
    	double doblefakt=1;
    	for(int i=1; i<=n; i++)
    	{
          doblefakt*=i;
          fprintf(fp,"  i = %3d   %2d! = %22.f\n",i,i,doblefakt);
    	}      
    	fclose(fp);  
}
void Vvod()
{
    	char		pust[100];
    	float		scan;
    	FILE *fp;								// ��������� �� ����
    	fp=fopen("in.txt","r");			     	// ������� ���� ��� ������
       									// ������ �� �����
    	fscanf(fp,"%s",pust);
    	fscanf(fp,"%s",pust);fscanf(fp,"%d",&n);
    	fclose(fp);							// ������� ���� ��� ������
}
