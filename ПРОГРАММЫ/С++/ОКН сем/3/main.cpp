#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

const double pi=3.1415;
double t, h, T, X,*a,*b,eps;
int kk;

void read()
{ifstream fin("input.txt");

fin>>t>>h>>T>>X;//���� ����� � �����

fin.close();
}

void write(double eps)
{ofstream fout("output.txt");

fout<<eps<<endl;//����� �����������

fout.close();
}

int main() {
	read();

ofstream fout("output.txt");	
	
	
	kk=1/h;
	 
	a = new double[kk+1]; 
	b = new double[kk+1];
	
	double c=t/h/h;//����������� ��� ����������
	
	for(int j=0;j<=kk;j++) 
	{
	b[j]=sin(4*pi*j*h)+1;//���������� ������ ������� ����
	//fout<<b[j]<<" \t";
    }
    fout<<endl;
    
    
	for(double k=t;k<=T;k+=t)
	{
	   a[0]=1;// fout<<a[0]<<" \t";
	   for(int j=1;j<=kk-1;j++)
	   {
		a[j]=b[j]+c*(b[j+1]-2*b[j]+b[j-1]);//���������� ���� ����
		//fout<<a[j]<<" \t";		
	   }
	   a[kk]=1;	//fout<<a[kk]<<" \t"<<endl;
	   
	   for(int j=0;j<=kk;j++)
	   {
		b[j]=a[j];//������ ���� ������� �������		
	   }
	}
	
	
	eps=fabs(a[int(X/h)]-(exp(-16*pi*pi*T)*sin(4*pi*X)+1));
	
	cout<<a[int(X/h)]<<' '<<(exp(-16*pi*pi*T)*sin(4*pi*X)+1)<<' '<<fabs(a[int(X/h)]-exp(-16*pi*pi*T)*sin(4*pi*X)-1)<<endl;
	
    write(eps);
	return 0;
}
