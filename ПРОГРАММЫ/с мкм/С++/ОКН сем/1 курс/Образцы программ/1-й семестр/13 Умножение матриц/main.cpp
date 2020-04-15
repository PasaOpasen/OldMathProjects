//              ������� ���������
//              ��������� ������ ������� ��������� 
//              ��� �������� ����������� ������� ���������� ���������
//              �� ����������� ��������� � ������
//
//              13 �������� 2014 �.

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;

											// �������
#define N	(1024*1024)						// ������������ ����������� ����
											
typedef double matrix[N];
matrix 		A,B,C;

int			n,n_cikle;
double		a,b;
int         timeR,timeR1,timeR2;
clock_t		timeBegin,timeEnd;

void Vvod();
void Vyvod();
void Umn_ij();
void Umn_ji();
void Umn();     

int main()
{
    
    Vvod();    
    //
    //----------	��������� �������	
    //
    for (int i=0; i<n; i++)
    	for (int j=0; j<n; j++)
    	{
    		int k=i*n+j;
    		A[k]=a;
    		B[k]=b;
    	}
    Umn_ij();
    Umn_ji();
    Umn();	
   	Vyvod();
}
//
//----------	���� ������
//
void Vvod()
{
     char		pust[100];
     float		scan;
    FILE *fp;									// ��������� �� ����
    fp=fopen("file_in.txt","r");				// ������� ���� ��� ������
       											// ������ �� �����
    fscanf(fp,"%s",pust);fscanf(fp,"%d",&n);
    fscanf(fp,"%s",pust);fscanf(fp,"%d",&n_cikle);
    fscanf(fp,"%s",pust);
    fscanf(fp,"%f",&scan);a=scan;
    fscanf(fp,"%f",&scan);b=scan;
    fclose(fp);									// ������� ���� ��� ������
}
//
//----------	����� ������
//
void Vyvod()
{
     int pr;
    FILE *fp;
    fp=fopen("file_out.txt","w");		 		// ������� ���� ��� ������
    											// ������ � ����
    fprintf(fp,"  ��������� ������\n\n");
	fprintf(fp,"  ����������� ������� �����  %4d\n\n",n);
    fprintf(fp,"  ������              �����           ���������\n");
    fprintf(fp,"  ���������           ����������      � ���������\n\n");
    pr=(100*timeR)/timeR;
    fprintf(fp,"  ������� (i,j)     %8d           %4d\n\n",timeR,pr);
    pr=(100*timeR1)/timeR;
    fprintf(fp,"  ������� (j,i)     %8d           %4d\n\n",timeR1,pr);
    pr=(100*timeR2)/timeR;
    fprintf(fp,"  �� ������� (i,j)  %8d           %4d\n\n",timeR2,pr);
    fclose(fp);	
}
//
//----------	������� ��������� (i,j)
//
void Umn_ij()
{    
    timeBegin = clock();						// ����� ������ ����������
    
    for (int m=0; m<n_cikle; m++)
    {
    for (int i=0; i<n; i++)
    	for (int j=0; j<n; j++)	C[i*n+j]=0;
    for (int i=0; i<n; i++)
    	for (int j=0; j<n; j++)
    		for (int k=0; k<n; k++) C[i*n+j]+=A[i*n+k]*B[k*n+j];
    }
    timeEnd = clock();							// ����� ��������� ����������
    int time=timeEnd-timeBegin;
    if (time<1) timeR=1;
	else timeR=time;
}
//
//----------	������� ��������� (j,i)
//
void Umn_ji()
{
    timeBegin = clock();						// ����� ������ ����������
    for (int m=0; m<n_cikle; m++)
    {
    for (int i=0; i<n; i++)
    	for (int j=0; j<n; j++)	C[i*n+j]=0;
    for (int j=0; j<n; j++)
    	for (int i=0; i<n; i++)
    		for (int k=0; k<n; k++) C[i*n+j]+=A[i*n+k]*B[k*n+j];
    }
    timeEnd = clock();							// ����� ��������� ����������
    timeR1=timeEnd-timeBegin;
}
//
//----------	��������� "�� �������"
//
void Umn()
{
    timeBegin = clock();						// ����� ������ ����������
    
    for (int m=0; m<n_cikle; m++)
    {
    for (int i=0; i<n; i++)
    	for (int j=0; j<n; j++)	C[i*n+j]=0;
    for (int i=0; i<n; i++)
    	for (int k=0; k<n; k++)
    			for (int j=0; j<n; j++) C[i*n+j]+=A[i*n+k]*B[k*n+j];
    }
    timeEnd = clock();							// ����� ��������� ����������
    timeR2=timeEnd-timeBegin;
}
