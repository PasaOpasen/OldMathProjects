//������� ��������� ���������������� ����� ����� �����, ������ �. �., 20.11.2017
#include <fstream>
#include <iostream>
#include <cmath>
#include "Graph2016.h"
using namespace std;


const double pi = 3.1415;
double t, hh, T, X, *up, *b, eps, a0, b0, c0, d0;
int kk;
double k=10;

//������� �������
double u(double t, double x)
{
	//return exp(-16 * pi * pi * t)*sin(4 * pi*x) + 1;
	//return (cos(x)+sin(x))*t;
	return t*cos(k*x);
}
//��������� ����
double f(double t, double x)
{
	//return 0;
	//return (1+t)*(cos(x)+sin(x));
	return cos(k*x)+t*k*k*cos(k*x);
}

//������ �� �����
void read()
{
	ifstream fin("input.txt");
	char buff[100];
	fin >> buff; fin >> t;//������ ���� �� �������
	fin >> buff; fin >> hh;//��� �� ����������
	fin >> buff; fin >> T;//����� �� �������
	fin >> buff; fin >> X;//������ ����� �� ����������

	fin.close();
}

//����� �����������
void write(double eps)
{
	ofstream fout("output.txt");

	fout << eps << endl;//����� �����������

	fout.close();
}

//����� ������� � ����� �� �����
void search()
{
	kk = 1 / hh;

	up = new double[kk + 1];
	b = new double[kk + 1];

	double c = t / hh / hh;//����������� ��� ����������

	for (int j = 0; j <= kk; j++)
	{
		b[j] = u(0, j*hh);//���������� ������ ������� ����
	}

	for (double k = t; k <= T; k += t)
	{
		up[0] = u(k, 0);// fout<<a[0]<<" \t";
		for (int j = 1; j <= kk - 1; j++)
		{
			up[j] = b[j] + c*(b[j + 1] - 2 * b[j] + b[j - 1]) + t*f(k, j*hh);//���������� ���� ����		
		}
		up[kk] = u(k, 1);

		for (int j = 0; j <= kk; j++)
		{
			b[j] = up[j];//������ ���� ������� �������		
		}
	}


	eps = fabs(up[int(X / hh)] - u(T, X));
}

//����� �������� ������� � ���������� �����
double search(double tt, double xx)
{
	T = tt; X = xx;
	kk = 1 / hh;

	up = new double[kk + 1];
	b = new double[kk + 1];

	double c = t / hh / hh;//����������� ��� ����������

	for (int j = 0; j <= kk; j++)
	{
		b[j] = u(0, j*hh);//���������� ������ ������� ����
	}

	for (double k = t; k <= T; k += t)
	{
		up[0] = u(k, 0);// fout<<a[0]<<" \t";
		for (int j = 1; j <= kk - 1; j++)
		{
			up[j] = b[j] + c*(b[j + 1] - 2 * b[j] + b[j - 1]) + t*f(k, j*hh);//���������� ���� ����		
		}
		up[kk] = u(k, 1);

		for (int j = 0; j <= kk; j++)
		{
			b[j] = up[j];//������ ���� ������� �������		
		}
	}
	return up[int(X / hh)];
}

//���������� �������
void Risf(double tt)
{
	SetColor(0, 255, 0); // ������ ���� ����� (������)
	SetPoint(0, u(tt, 0)); // ������������� ������ �� ����� 

	const double eps = 0.0001;
	for (double i = eps; i <= 1; i += eps) Line2(i, u(tt, i));

}
//�������� ������
void RisL(double tt)
{
	SetColor(30, 5, 150); // ������ ���� ����� 
	SetPoint(0,up[0]); // ������������� ������ �� �����
	for (int i = 1; i <= kk; i ++) Line2(i*hh, up[i]);
	 
	//SetPoint(0,search(tt, 0)); // ������������� ������ �� �����
	//double r = 0.2;
	//for (double i = r; i <= 1; i += r) Line2(i, search(tt, i));
}

double minf(double z, double x)
{
	if(z<x) return z;
	return x;
}

//���������������
void illustrating(double tt)
{ 
	double max = u(tt, 0), min = max;
    eps = 0.001;
	//����� �������� ���� �� y
	for (double i = eps; i <= 1; i += eps)
	{
		if (u(tt, i) < min) min = u(tt, i);
		if (u(tt, i) > max) max = u(tt, i);
	}

	//������������� �������� ����
	a0 = -0.5;
	b0 = 1.5;
	c0 = -1 +minf(0,min); 
	d0 = 1 + max;

	SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
	SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B) � ��������� [a,b]x[c,d]
	SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
	xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � ������ 1 � 1 �� �

	// ������ ������
	Risf(tt);
	RisL(tt);

	CloseWindow("�������.bmp");// ��������� ���� (������� bmp-����)

}


int main() 
{
	read();
	search();
	write(eps);
	
	illustrating(2);
	return 0;
}
