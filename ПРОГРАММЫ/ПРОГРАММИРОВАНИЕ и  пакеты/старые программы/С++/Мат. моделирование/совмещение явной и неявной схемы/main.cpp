//������� ��������� ���������������� ����� ������� �����, ������ �. �., 03.12.2017
#include <fstream>
#include <iostream>
#include <cmath>
#include "Graph2016.h"
using namespace std;


const double pi = 3.1415;
double t, hh, T, X, *up,*upn, *down,*downn, eps, a0, b0, c0, d0,*y,*f,*a,*b,*c,*alp,*bet;
int kk,n,k=10;

//������� �������
double u(double t, double x)
{
	//return exp(-16 * pi * pi * t)*sin(4 * pi*x) + 1;
	//return (cos(x)+sin(x))*t;
	return t*cos(k*x);
}
//��������� ����
double func(double t, double x)
{
	//return 0;
	//return (1+t)*(cos(x)+sin(x));
	return cos(k*x) + t*k*k*cos(k*x);
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

//����� �� ������� �-� ��������������� ��������
void SLAU(double* down,double ti)//���������� ������� ������� ��������
{
	double con=t/hh/hh;
    //����������
	for (int i = 1; i <= n; i++) f[i] = down[i-1]+t*func(ti, (i-1)*hh);//���������� ���������� ������� ���������� �����������

	b[1] = 1+2*con;
	c[1] = 0;
	for (int i = 2; i < n; i++)
	{
		b[i] = 1+2*con;
		c[i] = -con;
		a[i] = c[i];
	}
	b[n] = 1+2*con;
	a[n] = 0;
 
    //������ ���
	alp[2] = -c[1] / b[1];
	bet[2] = f[1] / b[1];
	for (int i = 2; i < n; i++)
	{
		double val = b[i] + a[i] * alp[i];
		alp[i + 1] = -c[i] / val;
		bet[i + 1] = (-a[i] * bet[i] + f[i]) / val;
	}

	//�������� ���
	y[n] = (-a[n] * bet[n] + f[n]) / (b[n] + a[n] * alp[n]);
	for (int i = n - 1; i >= 1; i--)
	{
		y[i] = alp[i + 1] * y[i + 1] + bet[i + 1];
	}
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
	down = new double[kk + 1];
	
	upn = new double[kk + 1];
	downn = new double[kk + 1];
	
	//��� ��������������� �������  
	n = int(T / hh-1);
	y = new double[n + 1];
	f = new double[n + 1];
	a = new double[n + 1];
	b = new double[n + 1];
	c = new double[n + 1];
	alp = new double[n + 1];
	bet = new double[n + 1];

	double cc = t / hh / hh;//����������� ��� ����������

	for (int j = 0; j <= kk; j++)
	{
		down[j] = u(0, j*hh);//���������� ������ ������� ����
		downn[j] = u(0, j*hh);//���������� ������ ������� ����
	}

	for (double k = t; k <= T; k += t)
	{
		up[0] = u(k, 0);// fout<<a[0]<<" \t";
		upn[0] = u(k, 0);// fout<<a[0]<<" \t";
		for (int j = 1; j <= kk - 1; j++)
		{
			up[j] = down[j] + cc*(down[j + 1] - 2 * down[j] + down[j - 1]/**/) + t*func(k, j*hh);//���������� ���� ����
			
			SLAU(downn,k);
			upn[j] = y[j + 1];
		}
		up[kk] = u(k, 1);
        upn[kk] = u(k, 1);

		for (int j = 0; j <= kk; j++)
		{
			down[j] = up[j];//������ ���� ������� �������
			downn[j] = upn[j];		
		}
	}

	eps = fabs(upn[int(X / hh)] - u(T, X));
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
void RisL(double tt,double* uu)
{
	//SetColor(30, 5, 150); // ������ ���� ����� 
	SetPoint(0, uu[0]); // ������������� ������ �� �����
	for (int i = 1; i <= kk; i++) Line2(i*hh, uu[i]);
}

double minf(double z, double x)
{
	if (z < x) return z;
	return x;
}

//���������������
void illustrating()
{
	double tt = T;
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
	c0 = -1 + minf(0, min);
	d0 = 1 + max;

	SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
	SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B) � ��������� [a,b]x[c,d]
	SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
	xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � ������ 1 � 1 �� �

	// ������ ������
	Risf(tt);
	SetColor(30, 5, 150); // ������ ���� ����� 
	RisL(tt,up);
	SetColor(200, 0, 0); // ������ ���� ����� 
	RisL(tt,upn);

	CloseWindow("�������.bmp");// ��������� ���� (������� bmp-����)

}


int main()
{
	read();
	search();
	write(eps);
	illustrating();
	return 0;
}
