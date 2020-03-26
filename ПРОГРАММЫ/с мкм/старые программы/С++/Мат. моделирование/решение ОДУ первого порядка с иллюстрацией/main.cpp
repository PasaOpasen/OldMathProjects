#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "Graph.h"
using namespace std;

double tau,y00,T, a0,b0,c0,d0;
double* y;
int n;

double u(double x)
{
	return sin(x)+1;
}

double f(double t,double x)
{
	return cos(x);
}


void input()
{
	char buff[100];
	ifstream fin("input.txt");
	fin>>buff;
	fin>>tau;
	fin>>buff;
	fin>>y00;
	fin>>buff;
	fin>>T;
	fin.close();
	//cout<<tau<<' '<<y00<<' '<<T;
}

void search()
{
	n=(T-0)/tau;
	y= new double[n];
	y[0]=y00;
	double xx=0;
	for (int i=1;i<n;i++)
	{y[i]=y[i-1]+tau*f(0,xx);
	xx+=tau;
	}
	
}

void output()
{
	double max=abs(y[0]-u(0));
	for(int i=1;i<n;i++)
	{if(abs(y[i]-u(i*tau))> max) max=abs(y[i]-u(i*tau));
	//cout<<y[i]<<" \t"<<u(i*tau)<<endl;
	}
	
	ofstream fout("output.txt");
	fout<<"���������� �� ������� ������� ����� "<<max;
	fout.close();
	
}

void Risf()
{
	SetColor(0, 255, 0); // ������ ���� ����� (������)
	SetPoint(0,y00); // ������������� ������ �� ����� 
	
	const double eps=0.0001;
	for(double i=eps;i<=T;i+=eps)Line2(i,u(i)); 
	
}
void RisL()
{
	SetColor(30, 5, 150); // ������ ���� ����� 
	SetPoint(0,y00); // ������������� ������ �� �����
	for(int i=1;i<n;i++) Line2(i*tau,y[i]); 
	
}

//���������������
void illustrating()
{
	double max=y[0],min=y[0];
	for (int i=1;i<n;i++)
	{if(y[i]<min) min=y[i];
	if(y[i]>max) max=y[i];
	}
	//������������� �������� ����
	a0 = -1 + 0;
	b0 = 1 + T;
	c0 = -1 + min;
	d0 = 1 + max;

	SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
	SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B)
	// � ��������� [a,b]x[c,d]
	SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
	xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � ������ 1 � 1 �� �

	// ������ ������
	Risf(); 
	RisL();

	CloseWindow();// ��������� ���� (������� bmp-����)

}

int main()
{
	input();//���� ������
	search();//����� �������
	output();//���������� � ����� �����
	illustrating();//����������� �������
	
	
	return 0;
}
