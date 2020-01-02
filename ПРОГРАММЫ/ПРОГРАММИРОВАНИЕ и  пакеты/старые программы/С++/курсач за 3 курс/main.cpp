//���������, ������� ������� ����������� ������� ������ ������� ��� ��������� ������� ������� �������� �����������
//������� ������ �. �.
//� ��������� ��� ��������� ��������������� 27.02.2018

//����������� ��������� �������������
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <string>
#include "Graph2016.h"
#include "stringconvert.h"
#include <dir.h>

//����������� ������������ ���
using namespace std;

class BasisPoint {//����� �� ���������
	public:
	double x;//���������� ����� � ��������� ������������
	double y;
	//������� ��������� ���������� � ����� z, ��������������� �������� �������� �����
	double Potentialf(BasisPoint z)
	{
		return log(1 / sqrt((z.x - x)*(z.x - x) + (z.y - y)*(z.y - y)));
	}

}*masPoints;//��������� �� ������ ����� ���������

	
	double Eudistance(BasisPoint z, BasisPoint w)//���������� ����� ������� 
	{
		return sqrt((z.x - w.x)*(z.x - w.x) + (z.y - w.y)*(z.y - w.y));
	}

//���������� ������ ����� ����� ������� �������
double BasisFuncPow(int i, int j, BasisPoint z);
double Nev(double **a, double *y, double *f);

namespace Func_in_matrix //������������ �������, ��������� � ��������� � ���������
{
	void Matrix_power(double *Ax, double **a, double *x, int k)//��������� ������������ ������� �� ������ 
	{
		for (int i = 0; i < k; i++)
		{
			double sum = 0;
			for (int j = 0; j < k; j++) sum += a[i][j] * x[j];
			Ax[i] = sum;
		}
	}

	void Vector_difference(double *r, double *Ax, double *b, int t)//�������� ���� ��������
	{
		for (int i = 0; i < t; i++) r[i] = Ax[i] - b[i];
	}

	double Scalar_power(double *r, double *rr, int t) //������������ ��������� ������������ ���� ��������
	{
		double s = 0;
		for (int i = 0; i < t; i++) s += r[i] * rr[i];
		return s;
	}

	void Vector_on_scalar(double *s, double tau, double *r, int t)//��������� ������� �� ������
	{
		for (int i = 0; i < t; i++) s[i] = tau*r[i];
	}

	void Vector_sum(double *sum, double *s, double *x, int t)//����� ��������
	{
		for (int i = 0; i < t; i++) sum[i] = x[i] + s[i];
	}

	void Vector_assingment(double *x, double *s, int t)//������������ ������ ������� �������
	{
		Vector_on_scalar(x, 1, s, t);
	}

}


//���������� ����������
int ITER_INTEG = 5000; //���������� ����� ��� ��������������
double(*fi)(BasisPoint);//��������� �� ��������� ������� �� �����
double(*fi0)(BasisPoint);
int CIRCLE, GF, N;//����� �������, ��������� ������� � ���������� �������� �����
bool zero;// ������� ������� ��������� � �������
const int KGF = 8, MAXCIRCLE = 4;//����� ��������� �������
const double EPS = 0.00001, EPSS = 0, CONSTANT = 1, pi = 3.14159;//������������ � ��������� ������ �����������
double RESULT, NEVA; //�������� ������������� � �������
//double *goldmas;//��������� �� ������ ����� ��� ������������ �������������
int cr = 250, cg = 0, cb = 0, mr = 0, mg = 250, mb = 0; //�������� ��������� ��� ������
char dir_Curve_name[50], dir_func_name[50], chstr[100];//��� ���������� ����� � ��������
string sl = "\\", bstr;

double VALUE_FOR_ULTRA = 10;//
double MIN_RADIUS = 0.5;//������ �������
double MAX_RADIUS = 3.5;//������ ��� �������

//������� ������������ �������� �������
double BasisFuncPow(int i, int j, BasisPoint z)
{
	if ((i == N) && (j == N)) return fi(z)*fi(z);
	if (i == N) return masPoints[j].Potentialf(z)*fi(z);
	if (j == N) return masPoints[i].Potentialf(z)*fi(z);
	return masPoints[i].Potentialf(z)*masPoints[j].Potentialf(z);
}

//����� ������� ������ 
class Curve
{
private:
	double(*u)(double);//�������������� ���������
	double(*v)(double);
	double _h; //�������� ���� ��� ���� ������
	int M;//����� �����
	void Get_h(int MM) {
		M = MM;
		_h = (b - a) / M; //���������� ���� ����������� ��������
	}

public:
	BasisPoint Transfer(double t) {//������� ����� �� ������ �� �������� ���������
		BasisPoint point;
		point.x = u(t);
		point.y = v(t);
		return point;
	}

	double a;//��������� �������� ���������
	double b;//�������� �������� ���������

	Curve(double a0, double b0, double(*uu)(double), double(*vv)(double)) {//������ �����������
		a = a0; b = b0;
		u = uu; v = vv;
		//fi=fi0;
	}
	Curve() {//���������� �����������
		a = 0; b = 0;
	}

	double Firstkind(double(*f)(BasisPoint)) {//���������� �������������� ��������� ������� ���� �� ���� ������ �� ������� f ������� �������� (� ��������� �� ������������)
		Get_h(ITER_INTEG);
		double value = 0;
		for (int k = 0; k <= M - 1; k++) value += f(Transfer((a + (k + 1)*_h + a + (k)*_h) / 2))*Eudistance(Transfer(a + (k + 1)*_h), Transfer(a + (k)*_h));
		return value;
	}

	double Firstkind(int i, int j) {//���������� �������������� ��������� ������� ���� �� ���� ������ �� ������� BasisFuncPow(int i,int j,BasisPoint z)
		Get_h(ITER_INTEG);
		double value = 0;
		//for (int k = 0; k <= M - 1; k++) value += BasisFuncPow(i, j, Transfer((a + (k + 1)*h + a + (k)*h) / 2))*Eudistance(Transfer(a + (k + 1)*h), Transfer(a + (k)*h));//����� ���������������
		for (int k = 1; k <= M; k++) value += (BasisFuncPow(i, j, Transfer(a + (k)*_h)) + BasisFuncPow(i, j, Transfer(a + (k - 1)*_h)))*Eudistance(Transfer(a + (k - 1)*_h), Transfer(a + (k)*_h)) / 2;//����� ��������

		//����� �������� ������������ ��������
		/*double sum1=0,sum2=0;
		for (double k = 0; k <= M - 1; k+=0.5){
			sum1+=BasisFuncPow(i, j, Transfer((a + (2*k)*h)));
			sum2+=BasisFuncPow(i, j, Transfer((a + (2*k-1)*h)));
		}
		value=h/3*(BasisFuncPow(i, j, Transfer(a))+BasisFuncPow(i, j, Transfer(b))+4*sum2+2*sum1);*/

		/*double EPS=0.0001;
		double I=EPS+1, I1=0;//I-���������� ����������� �������� ���������, I1-�����, � ��`����� N.
		for (int N=2; (N<=8)||(fabs(I1-I)>EPS); N*=2)
		{
			double hh, sum2=0, sum4=0, sum=0,e=hh/3;
			hh=(b-a)/(2*N);//��� ��������������.
			for (int i=1; i<=2*N-1; i+=2)
			{
				sum4+=BasisFuncPow(i, j, Transfer(a+hh*i));//�������� � ��������� ���������, ������� ����� �������� �� 4.
				sum2+=BasisFuncPow(i, j, Transfer(a+hh*(i+1)));//�������� � ������� ���������, ������� ����� �������� �� 2.
			}
			sum=BasisFuncPow(i, j, Transfer(a))+4*sum4+2*sum2-BasisFuncPow(i, j, Transfer(b));//�������� �������� f(b) ��� ��� ����� ��������� ��� ������.
			I=I1;
			I1=e*sum;
			cout<<N<<" "<<I1<<" "<<fabs(I1-I)<<endl;
		}
		*/
		return value;
	}

	~Curve() {
		//cout<<"Object "<<this<<" has deleted"<<endl;
	}

}myCurve;//������� �������, � ������� �������� ���. ���������

double sgn(double a) //������
{
	if (a > 0) return 1;
	if (a < 0) return -1;
	return 0;
}

//������������ �������� ������� � ������
namespace TestFuncAndCurve {
	//��������� �������������� ��� �������
		//���������� ������� MIN_RADIUS
	double u1(double t) {
		return MIN_RADIUS * cos(t);
	}
	double v1(double t) {
		return MIN_RADIUS * sin(t);
	}

	//��������������� ���������� ������� MAX_RADIUS (����� ������� ������� �������� �����)
	double u1h(double t) {
		return MAX_RADIUS * cos(t);
	}
	double v1h(double t) {
		return MAX_RADIUS * sin(t);
	}

	//�������������� ����������� �� �������� MIN_RADIUS
	double u2(double t) {
		if ((t >= 0) && (t <= 2 * MIN_RADIUS))return t / 2;
		if ((t >= 2 * MIN_RADIUS) && (t <= 3 * MIN_RADIUS))return 3 * MIN_RADIUS - 1 * t;
	}
	double v2(double t) {
		if ((t >= 0) && (t <= MIN_RADIUS))return t / 2 * sqrt(3);
		if ((t >= MIN_RADIUS) && (t <= 2 * MIN_RADIUS))return -t / 2 * sqrt(3) + MIN_RADIUS * sqrt(3);
		if ((t >= 2 * MIN_RADIUS) && (t <= 3 * MIN_RADIUS))return 0;
	}
	double dis = MAX_RADIUS - MIN_RADIUS, mdx = dis / 2, mdy = mdx / sqrt(3);//�������, ��-�� ������������ ���� ���������� ������ ���������� ���������� ����� ������� � ���� � �� �� �����
		//��������������� �������������� ����������� �� �������� MAX_RADIUS
	double u2h(double t) {
		dis = MAX_RADIUS - MIN_RADIUS; mdx = dis / 2;//�� ���� ������ ������ �������� ���,������� �� ����������, �� ���������
		if ((t >= 0) && (t <= 2 * MAX_RADIUS))return t / 2 - mdx;
		if ((t >= 2 * MAX_RADIUS) && (t <= 3 * MAX_RADIUS))return 3 * MAX_RADIUS - 1 * t - mdx;
	}
	double v2h(double t) {
		dis = MAX_RADIUS - MIN_RADIUS; mdx = dis / 2; mdy = mdx / sqrt(3);
		if ((t >= 0) && (t <= MAX_RADIUS))return t / 2 * sqrt(3) - mdy;
		if ((t >= MAX_RADIUS) && (t <= 2 * MAX_RADIUS))return -t / 2 * sqrt(3) + MAX_RADIUS * sqrt(3) - mdy;
		if ((t >= 2 * MAX_RADIUS) && (t <= 3 * MAX_RADIUS))return 0 - mdy;
	}

	//������� �� �������� MIN_RADIUS
	double u3(double t) {
		if ((t >= 0) && (t <= MIN_RADIUS))return t;
		if ((t >= MIN_RADIUS) && (t <= 2 * MIN_RADIUS))return MIN_RADIUS;
		if ((t >= 2 * MIN_RADIUS) && (t <= 3 * MIN_RADIUS))return 3 * MIN_RADIUS - t;
		if ((t >= 3 * MIN_RADIUS) && (t <= 4 * MIN_RADIUS))return 0;
	}
	double v3(double t) {
		if ((t >= 0) && (t <= MIN_RADIUS))return 0;
		if ((t >= MIN_RADIUS) && (t <= 2 * MIN_RADIUS))return t - MIN_RADIUS;
		if ((t >= 2 * MIN_RADIUS) && (t <= 3 * MIN_RADIUS))return MIN_RADIUS;
		if ((t >= 3 * MIN_RADIUS) && (t <= 4 * MIN_RADIUS))return 4 * MIN_RADIUS - t;
	}
	//��������������� ������� �� �������� MAX_RADIUS
	double u3h(double t) {
		dis = MAX_RADIUS - MIN_RADIUS; mdx = dis / 2;
		if ((t >= 0) && (t <= MAX_RADIUS))return t - mdx;
		if ((t >= MAX_RADIUS) && (t <= 2 * MAX_RADIUS))return MAX_RADIUS - mdx;
		if ((t >= 2 * MAX_RADIUS) && (t <= 3 * MAX_RADIUS))return 3 * MAX_RADIUS - t - mdx;
		if ((t >= 3 * MAX_RADIUS) && (t <= 4 * MAX_RADIUS))return 0 - mdx;
	}
	double v3h(double t) {
		dis = MAX_RADIUS - MIN_RADIUS;	mdx = dis / 2;
		if ((t >= 0) && (t <= MAX_RADIUS))return 0 - mdx;
		if ((t >= MAX_RADIUS) && (t <= 2 * MAX_RADIUS))return t - MAX_RADIUS - mdx;
		if ((t >= 2 * MAX_RADIUS) && (t <= 3 * MAX_RADIUS))return MAX_RADIUS - mdx;
		if ((t >= 3 * MAX_RADIUS) && (t <= 4 * MAX_RADIUS))return 4 * MAX_RADIUS - t - mdx;
	}

	//������
	double u4(double t) {
		if ((t >= 0) && (t <= MIN_RADIUS))return t;
		if ((t >= MIN_RADIUS) && (t <= 1.5*MIN_RADIUS))return 3 * MIN_RADIUS - 2 * t;
	}
	double v4(double t) {
		if ((t >= 0) && (t <= 0.5*MIN_RADIUS))return sqrt(MIN_RADIUS*MIN_RADIUS - (t - MIN_RADIUS)*(t - MIN_RADIUS));
		if ((t >= 0.5*MIN_RADIUS) && (t <= MIN_RADIUS))return sqrt(MIN_RADIUS*MIN_RADIUS - t*t);
		if ((t >= MIN_RADIUS) && (t <= 1.5*MIN_RADIUS))return 0;
	}

	double u4h(double t) {
		dis = MAX_RADIUS - MIN_RADIUS; mdx = dis / 2; mdy = mdx / sqrt(3);
		if ((t >= 0) && (t <= MAX_RADIUS))return t - mdx;
		if ((t >= MAX_RADIUS) && (t <= 1.5*MAX_RADIUS))return 3 * MAX_RADIUS - 2 * t - mdx;
	}
	double v4h(double t) {
		dis = MAX_RADIUS - MIN_RADIUS; mdx = dis / 2; mdy = mdx*sqrt(3) / 2;
		if ((t >= 0) && (t <= 0.5*MAX_RADIUS))return sqrt(MAX_RADIUS*MAX_RADIUS - (t - MAX_RADIUS)*(t - MAX_RADIUS)) - mdy;
		if ((t >= 0.5*MAX_RADIUS) && (t <= MAX_RADIUS))return sqrt(MAX_RADIUS*MAX_RADIUS - t*t) - mdy;
		if ((t >= MAX_RADIUS) && (t <= 1.5*MAX_RADIUS))return 0 - mdy;
	}

	//��������� ������� � ������ ��������� �������
	double g1(BasisPoint point)
	{
		return cos(point.x)*cos(point.y);
	}
	double g2(BasisPoint point)
	{
		return sin(point.y);
	}
	double g3(BasisPoint point)
	{
		return point.x*point.x + 4;
	}

	double g4(BasisPoint point) {
		return CONSTANT;
	}
	/*double g40(BasisPoint point)//�� �� ����� �������, �� ��� ��� ����� myCurve
{
	double dis = MAX_RADIUS - MIN_RADIUS, dx = dis / 2, dy = dx / 2 * sqrt(3);
	BasisPoint center1, center2;//������ ���� �����������
	center1.x = 0 - dx;
	center1.y = 0 - dy;
	center2.x = MIN_RADIUS + dis - dx;
	center2.y = 0 - dy;

	if (point.y < 0 - dy) return CONSTANT;
	else
	{
		if ((point.x >= -dx) && (point.x <= MIN_RADIUS + dis / 2))//���� ������ ���������� ����������� ������� �������
		{
			if (point.y == 0-dy) return 0;
			if (Eudistance(center1, point) == MIN_RADIUS + dis) return 0.5;
			if (Eudistance(center2, point) == MIN_RADIUS + dis) return -0.5;
			else return CONSTANT;
		}
		else return CONSTANT;
	}*/
	/*
		BasisPoint center1, center2;//������ ���� �����������
		center1.x = 0;
		center1.y = 0;
		center2.x = MIN_RADIUS;
		center2.y = 0;
		if (point.y < 0) return CONSTANT;
		else
		{
			if ((point.x >= 0) && (point.x <= MIN_RADIUS))//���� ������ ���������� ����������� ������� �������
			{
				if (point.y == 0) return 0;
				if (Eudistance(center1, point) == MIN_RADIUS) return 0.5;
				if (Eudistance(center2, point) == MIN_RADIUS) return -0.5;
				else return CONSTANT;
			}
			else return CONSTANT;
		}
	}*/

	double g5(BasisPoint point)
	{
		return masPoints[0].Potentialf(point);
	}

	double g6(BasisPoint point)
	{
		return log(abs(point.x*point.y) + 1) + 2 * point.x;
	}
	double g7(BasisPoint point)
	{
		if (cos(point.x*point.y) != 0)return cos(2 * point.x) / cos(point.x*point.y);
		return 1;
	}

	double g8(BasisPoint point)
	{
		double dx = MIN_RADIUS / 2, dy = MIN_RADIUS / 2 * sqrt(3), argument;
		BasisPoint d = point; //d.x=-0.25;d.y=-0.25;
		d.x -= dx; d.y -= dy;//����� � ������ ���������

		if (d.x == 0) argument = pi / 2 * sgn(d.y);
		else
		{
			if (d.y == 0) argument = pi*sgn(-1 + sgn(d.x));
			else argument = atan(d.y / d.x) + sgn(fabs(d.x) - d.x)*sgn(d.y)*pi;
		}
		//return argument;
		//cout<<d.x<<" "<<d.y<<" �������� � ����: "<<argument/pi<<endl;

		if ((-pi <= argument) && (argument < -2 * pi / 3)) return -1. / 2;
		if ((-2 * pi / 3 <= argument) && (argument <= -pi / 3)) return 0;//return 1; //������� �����
		if ((-pi / 3 < argument) && (argument <= pi / 2)) return 1. / 2;//return 1; //��� �� �����
		/*if ((pi / 2 < argument) && (argument <= pi))*/return -1. / 2;
	}

	double(*GFunctions[KGF])(BasisPoint) = { g1,g2,g3,g4,g5,g6,g7,g8 };
}

//����� ���� � �������� �� �������
class SLAU {
private:
	int size;//����������� �������

public:
	double **a, *b, *x;//��������� �� ������� � ������� (��������� � �������)

	double Nev(double **a, double *x, double *b, int t)//������� ��������� �������
	{
		double *Ax = new double[t];
		Func_in_matrix::Matrix_power(Ax, a, x, t);
		double s = 0;
		for (int i = 0; i < t; i++) s += ((Ax[i] - b[i])*(Ax[i] - b[i]));
		return sqrt(s);
	}

	double Error(int k) //��������� �����������
	{
		double p = myCurve.Firstkind(N, N), sum = 0;

		double *Ax = new double[N];
		Func_in_matrix::Matrix_power(Ax, a, x, k);
		for (int i = 0; i < k; i++) sum += x[i] * Ax[i];
		double EPS = abs(p - sum);
		return sqrt(EPS);
	}

	void Make(int k) {//�������� ���������� � ���������� ������������ �������� � �������� ������������
		size = k;
		a = new double *[size];
		for (int i = 0; i < size; i++)
			a[i] = new double[size];
		b = new double[size];
		x = new double[size];
		for (int i = 0; i < size; i++)x[i] = 0;
	}

	void Gauss(int t)//����� ������
	{
		//�������� ��������������� ������� �������
		double **matrix = new double *[size];
		for (int i = 0; i < size; i++)
			matrix[i] = new double[size + 1];
		//������������ � ��������� ������ ��������
		for (int i = 0; i < size; i++) {
			matrix[i][size + 1] = b[i];
			for (int j = 0; j < size; j++) matrix[i][j] = a[i][j];
		}

		double m;//������������� ���������

		//������ ��� (��� ������ �������, ������ ��� ��������)
		for (int j = 0; j < t; j++) {

			for (int i = j + 1; i < t; i++)
			{
				m = matrix[i][j] / matrix[j][j];

				for (int _h = j; _h < t; _h++)
					matrix[i][_h] -= m*matrix[j][_h];
				matrix[i][size + 1] -= matrix[j][size + 1] * m;
			}
		}

		//�������� ���		
		for (int j = t - 1; j >= 0; j--)
		{
		z2:
			for (int i = j - 1; i >= 0; i--)
			{
				if (matrix[j][j] == 0)
				{
					j--;
					goto z2;
				}
				m = matrix[i][j] / matrix[j][j];

				matrix[i][size + 1] -= matrix[j][size + 1] * m;
				matrix[i][j] -= m*matrix[j][j];
			}
		}

		//���������� �������
		for (int i = 0; i < t; i++)
		{
			x[i] = matrix[i][size + 1] / matrix[i][i];
		}

		NEVA = Nev(a, x, b, t);//������� �����������
	}

	void Holets(int z) //������� ��������� ��=b ������� ���������, ���������� ������� � �������� ������
	{
		//�������� ��������������� �������
		double **t = new double *[z];
		for (int i = 0; i < z; i++)
			t[i] = new double[z];

		//������ ��� ������
		t[0][0] = sqrt(a[0][0]);
		for (int j = 1; j < z; j++)	t[0][j] = /*sqrt(fabs(*/a[0][j]/*))*/ / t[0][0];

		for (int i = 1; i < z; i++)
			for (int j = 0; j < z; j++)
			{
				if (j < i) t[i][j] = 0;
				else if (i == j)
				{
					double sum = 0;
					for (int k = 0; k <= j - 1; k++) sum += t[k][j] * t[k][j];
					t[j][j] = sqrt(fabs(a[j][j] - sum));//��� ������ �� ����������
				}
				else
				{
					double sum = 0;
					for (int k = 0; k <= i - 1; k++) sum += t[k][i] * t[k][j];
					t[i][j] = (a[i][j] - sum) / t[i][i];
				}

			}
		/*
		for (int j = 1; j < size; j++) {
			double sum = 0;
			for (int k = 0; k <= j - 1; k++) sum += t[k][j] * t[k][j];
			t[j][j] = sqrt(fabs(a[j][j] - sum));
		}

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				if (i < j) {
					double sum = 0;
					for (int k = 0; k <= i - 1; k++) sum += t[k][i] * t[k][j];
					t[i][j] = (a[i][j] - sum) / t[i][i];
				}
				else if (j < i) {
					t[i][j] = 0;
				}
			}*/

			/*
						//�������� �������
						cout << "������� a:" << endl;
						for (int i = 0; i < z; i++)
						{
							for (int j = 0; j < z; j++)cout << a[i][j] << " ";
							cout << endl;
						}
						//������������ ������� t �� �����������������
						double **c = new double *[z];
						for (int i = 0; i < z; i++)
							c[i] = new double[z];

						for (int i = 0; i < z; i++)
							for (int j = 0; j < z; j++) {
								double s = 0;
								for (int k = 0; k < size; k++)s += t[k][i] * t[k][j];
								c[i][j] = s;
							}

						cout << endl;
						cout << "������� c=(t)T*t:" << endl;
						for (int i = 0; i < z; i++)
						{

							for (int j = 0; j < z; j++)cout << c[i][j] << " ";
							cout << endl;
						}

						cout << endl;
						cout << "������� t:" << endl;
						for (int i = 0; i < z; i++)
						{

							for (int j = 0; j < z; j++)cout << t[i][j] << " ";
							cout << endl;
						}
			*/
			//�������� ��� ������     
		double *y = new double[z];
		y[0] = b[0] / t[0][0];
		//cout << y[0]<< endl;
		for (int i = 1; i < z; i++)
		{
			double sum = 0;
			for (int k = 0; k <= i - 1; k++) sum += t[k][i] * y[k];
			y[i] = (b[i] - sum) / t[i][i];
			//cout << y[i]<< endl;
		}

		x[z - 1] = y[z - 1] / t[z - 1][z - 1];
		for (int i = z - 2; i >= 0; i--)
		{
			double sum = 0;
			for (int k = i + 1; k < z; k++) sum += t[i][k] * x[k];
			x[i] = (y[i] - sum) / t[i][i];
		}

		NEVA = Nev(a, x, b, z);
	}

	void Jak(int t)//����� ����� 
	{
		for (int i = 0; i < t; i++) x[i] = 0/*b[i]*/;//������ ����������� - ��������� ������
		double E, EPSJ = 0.000001, NE = Nev(a, x, b, t);
		int num = 0, maxI = t*t;//����������, ��������� � ����������� ��������
		while ((Nev(a, x, b, t) > EPSJ) && (num <= maxI) /*&& (Nev(a, x, b, t) <= NE)*/)
		{
			NE = Nev(a, x, b, t);
			//cout<<NE<<endl;
			for (int i = 0; i < t; i++)
			{
				E = 0;
				for (int j = 0; j < t; j++)
				{
				z1:
					if (j == i)
					{
						j++;
						goto z1;
					}
					else
					{
						E += a[i][j] * x[j];
					}
				}
				x[i] = (b[i] - E) / a[i][i];
			}
			num++;

		}

		NEVA = Nev(a, x, b, t);
	}

	void Speedy(int t)//����� ������������� ������
	{
		for (int i = 0; i < t; i++) x[i] = b[i];//������ ����������� - ��������� ������

		double E = Nev(a, x, b, t), EPSJ = /*0.000001*/EPSS;
		int num = 0, maxI = t*t;//����������, ��������� � ����������� ��������
		double *Ax = new double[t];
		double *r = new double[t];
		double *Ar = new double[t];
		double *s = new double[t];
		double *sum = new double[t];

		while ((Nev(a, x, b, t) > EPSJ) && (num <= maxI))//���� 1) ������� �������, 2) ����� ��� �� �����, 3) ������� �������
		{
			Func_in_matrix::Matrix_power(Ax, a, x, t);//������������ ������� �� ������ Ax=a*x
			Func_in_matrix::Vector_difference(r, Ax, b, t);//�������� ���� �������� r=Ax-b
			Func_in_matrix::Matrix_power(Ar, a, r, t);//Ar=a*r
			double tau = Func_in_matrix::Scalar_power(r, r, t) / Func_in_matrix::Scalar_power(Ar, r, t);//��������� ������������ ���� �������� tau=(r,r)/(Ar,r)
			Func_in_matrix::Vector_on_scalar(s, -tau, r, t);//��������� ������� �� ������ s=-tau*r
			Func_in_matrix::Vector_sum(sum, s, x, t);//����� �������� sum=x+s=x-tau*r...

		   /*if(Nev(a, x, b, t)>Nev(a,sum,b,t))
		   {*/
			E = Nev(a, x, b, t);//��������� �������
			Func_in_matrix::Vector_assingment(x, sum, t);//������������ ������ ������� �������
		/*}
		else break;*/

		//cout << E << " " << num << endl;

		/*Func_in_matrix::Vector_sum(sum, b, x, t);
		Func_in_matrix::Vector_on_scalar(s, 1/2, sum, t);
		Func_in_matrix::Vector_assingment(x, sum, t);*/

			num++;

		}
		NEVA = Nev(a, x, b, t);
	}

	void Speedy0(int t)//����� ������������� ������ (��� ���������� ����������)
	{
		double E = Nev(a, x, b, t), EPSJ = /*0.000001*/EPSS;
		int num = 0, maxI = t/**t*/;//����������, ��������� � ����������� ��������
		double *Ax = new double[t];
		double *r = new double[t];
		double *Ar = new double[t];
		double *s = new double[t];
		double *sum = new double[t];

		while ((Nev(a, x, b, t) > EPSJ) && (num <= maxI))//���� 1) ������� �������, 2) ����� ��� �� �����, 3) ������� �������
		{
			Func_in_matrix::Matrix_power(Ax, a, x, t);//������������ ������� �� ������ Ax=a*x
			Func_in_matrix::Vector_difference(r, Ax, b, t);//�������� ���� �������� r=Ax-b
			Func_in_matrix::Matrix_power(Ar, a, r, t);//Ar=a*r
			double tau = Func_in_matrix::Scalar_power(r, r, t) / Func_in_matrix::Scalar_power(Ar, r, t);//��������� ������������ ���� �������� tau=(r,r)/(Ar,r)
			Func_in_matrix::Vector_on_scalar(s, -tau, r, t);//��������� ������� �� ������ s=-tau*r
			Func_in_matrix::Vector_sum(sum, s, x, t);//����� �������� sum=x+s=x-tau*r...

		   /*if(Nev(a, x, b, t)>Nev(a,sum,b,t))
		   {*/
			E = Nev(a, x, b, t);//��������� �������
			Func_in_matrix::Vector_assingment(x, sum, t);//������������ ������ ������� �������
		/*}
		else break;*/

		//cout << E << " " << num << endl;

		/*Func_in_matrix::Vector_sum(sum, b, x, t);
		Func_in_matrix::Vector_on_scalar(s, 1/2, sum, t);
		Func_in_matrix::Vector_assingment(x, sum, t);*/

			num++;

		}
	}

	void Minimize_coef(int t)//����������� �������������
	{
		cout << "�������� ������������� ��� ����� ������� " << t << " =" << endl;
		cout << "�� ������������� �������������� �����������:\t" << Error(t) << endl;
		double sum = 0;
		int r = 5;
		for (int k = 1; k <= r; k++)
		{
			for (int i = t - 1; i >= 0; i--)
			{
				for (int j = 0; j < t; j++)
				{
					if (j != i) sum += x[j] * a[i][j];
				}
				x[i] = (b[i] - sum) / a[i][i];
				sum = 0;
			}
			cout << "����� ������������� �������������� ����������� " << k << " ���:\t" << Error(t) << endl;
		}

	}
	/*
		void Minimize_coef2(int t,double pog)//����������� �������������
		{
			double sum = 0;
	while(Error(t)>pog){
				for (int i = t - 1; i >= 0; i--)
				{
					for (int j = 0; j < t; j++)
					{
						if (j != i) sum += x[j] * a[i][j];
					}
					x[i] = (b[i] - sum) / a[i][i];
					sum = 0;
				}

	}
		}
	*/
	void GaussSpeedy(int t)
	{
		Gauss(t);
		Speedy0(t);
		NEVA = Nev(a, x, b, t);
	}

	void GaussSpeedyMinimize(int t)//��������� � �������������� �������������� �����������
	{
		Gauss(t);
		Speedy0(t);
		Minimize_coef(t);
		NEVA = Nev(a, x, b, t);
	}

	void UltraHybrid(int t)//��������� � ������������ ������������ �� ��������� ����������
	{
		//double tmp=10;
		//if(t!=0) tmp=Error(t-1);
		double *c = new double[t];
		//if(t>=1){Gauss+Speedy(t-1);}
		for (int i = 0; i < t - 1; i++)c[i] = x[i];

		double sum = 0;
		GaussSpeedy(t);

		if ((VALUE_FOR_ULTRA < Error(t)) && (t >= 1))//���� ����������� ������� - ��������� ���
		{
			for (int i = 0; i < t - 1; i++) x[i] = c[i]; x[t - 1] = 0;
			if (t != 0)
			{
				for (int j = 0; j < t - 1; j++)
				{
					sum += x[j] * a[t - 1][j];
				}
				x[t - 1] = (b[t - 1] - sum) / a[t - 1][t - 1];
				sum = 0;

				double tmp1 = Error(t);

				if (VALUE_FOR_ULTRA < tmp1)//����������� ����� �������
				{
					for (int i = 0; i < t - 1; i++) x[i] = c[i]; x[t - 1] = 0;
				}
			}
		}
		VALUE_FOR_ULTRA = Error(t);

		NEVA = Nev(a, x, b, t);

	}

	/*	void SuperSpeedy(int t)//����� �� �������������� ��������
		{
			double *c = new double[t]; for (int i = 0; i < t - 1; i++)c[i] = x[i];
			double sum = 0;
			//tmp=Error(t);
			//cout<<" f "<<endl;
			Gauss+Speedy(t);
			//cout<<bool(tmp<Error(t))<<" "<<tmp<<" "<<Error(t)<<endl;

			if (tmp < Error(t))//���� ����������� ������� - ��������� ���
			{
				//cout<<Error(t)<<endl;
				for (int i = 0; i < t - 1; i++) x[i] = c[i]; x[t - 1] = 0;
				//cout<<Error(t)<<endl;
				//Minimize_coef2(t,tmp);
				//Minimize_coef(t);
				if (t != 0)
				{
					for (int j = 0; j < t - 1; j++)
					{
						sum += x[j] * a[t - 1][j];
					}
					x[t - 1] = (b[t - 1] - sum) / a[t - 1][t - 1];
					sum = 0;

					double tmp1 = Error(t);

					if (tmp < tmp1)//����������� ����� �������
					{
						for (int i = 0; i < t - 1; i++) x[i] = c[i]; x[t - 1] = 0;
					}
				}

							double E = Nev(a, x, b, t), EPSJ = EPSS;
							int num = 0, maxI = t*t*t;//����������, ��������� � ����������� ��������
							double *Ax = new double[t];
							double *r = new double[t];
							double *Ar = new double[t];
							double *s = new double[t];
							double *sum = new double[t];
							double pog1 = Error(t),pog2=pog1;

							while ((Nev(a, x, b, t) > EPSJ) && (num <= maxI) && (pog2 <= pog1))//���� 1) ������� �������, 2) ����� ��� �� �����, 3) ����������� �������
							{
								pog1 = Error(t);
								Func_in_matrix::Matrix_power(Ax, a, x, t);//������������ ������� �� ������ Ax=a*x
								Func_in_matrix::Vector_difference(r, Ax, b, t);//�������� ���� �������� r=Ax-b
								Func_in_matrix::Matrix_power(Ar, a, r, t);//Ar=a*r
								double tau = Func_in_matrix::Scalar_power(r, r, t) / Func_in_matrix::Scalar_power(Ar, r, t);//��������� ������������ ���� �������� tau=(r,r)/(Ar,r)
								Func_in_matrix::Vector_on_scalar(s, -tau, r, t);//��������� ������� �� ������ s=-tau*r
								Func_in_matrix::Vector_sum(sum, s, x, t);//����� �������� sum=x+s=x-tau*r...

								E = Nev(a, x, b, t);//��������� �������
								Func_in_matrix::Vector_assingment(x, sum, t);//������������ ������ ������� �������
								num++;
								pog2=Error(t);
							}

			}
			tmp = Error(t);

			NEVA = Nev(a, x, b, t);
		}*/

	~SLAU() {
		//cout<<"Object "<<this<<" has deleted"<<endl;
	}

}MySLAU;//�������, ������� ������� ������

//������������ �������
enum Method { Gauss, Holets, Jak, Speedy, GaussSpeedy, GaussSpeedyMinimize, UltraHybrid } baseMethod = UltraHybrid;
void Method_des(int i, Method mett)
{
	switch (mett)
	{
	case Gauss:
		MySLAU.Gauss(i);
		break;
	case Holets:
		MySLAU.Holets(i);
		break;
	case Jak:
		MySLAU.Jak(i);
		break;
	case Speedy:
		MySLAU.Speedy(i);
		break;
	case GaussSpeedy:
		MySLAU.GaussSpeedy(i);
		break;
	case GaussSpeedyMinimize:
		MySLAU.GaussSpeedyMinimize(i);
		break;
	case UltraHybrid:
		MySLAU.UltraHybrid(i);
		break;
	}
}

namespace ForDesigion
{

	double Random_eps() //��������� ���������� ����� �� ������
	{
		double e = rand() % 25 * EPS / 25, p = rand(), q = rand();
		if (sgn(p - q) < 0) return sgn(p - q)*min(MAX_RADIUS - MIN_RADIUS, e) / 100;
		return sgn(p - q)*e;
	}

	void FillMassiv(Curve c, int z) //��������� ������ �������� ����� �� ����� ���� - ����� ����� ������ � �� ������� �����
	{
		N = z;
		//delete[] masPoints;//�������� ������ ��� ������
		masPoints = new BasisPoint[N];
		//goldmas = new double[N];//������ ����� ��� ������������ ������������ �����
		//fillgoldmas(c,z,goldmas);

		for (int i = 0; i < z; i++)
		{
			masPoints[i] = c.Transfer(c.a + (c.b - c.a)*i / z);
			//masPoints[i] = c.Transfer(goldmas[i]);
			double l = Random_eps() / sqrt(2);
			masPoints[i].x += l;
			masPoints[i].y += l;

		}
	}

	void RandomSwapping(int p) //���������� ������ masPoints � � ��������
	{
		for (int i = 1; i <= p; i++)
		{
			int a = rand() % N, b = rand() % N;
			swap(masPoints[a], masPoints[b]);
		}
		/*
		//����������� ������� ��� fillgoldmas
		double rek(Curve c, int i) {
			return 0;
		}
		//��������� ������ ��������� ����� ��� ������������ �������������
		void fillgoldmas(Curve c, int k, double *m) {
			m[0] = c.a;
			m[1] = (c.a + c.b) / 2;
			int t = 2;
			while (t <= k) {
				m[t] = m[t / 2] / 2;//������ ������� ����
				for (int i = 1; i <= (t - 1) / 2; i++) m[t + i] = m[t] + rek(c, i);//������ �������� ��������� ����
				for (int i = (t - 1) / 2 + 1; i <= t - 1; i++) {//������ �������� ��������� ����
					int e = 1;
					m[t + i] = m[t + i - e];
					e++;
				}
				t *= 2;
			}

		}
		*/
	}

	void ReadFile()
	{
		char buff[150];//�������� ���������������� ����������� �������
		int k = 0; //�������
		double r;//��������������� �������������� �����	
		ifstream fin("input.txt"); //���������� ������� ��� ������ �� �����
		fin >> buff;//������ �������� ��������� ����������
		fin >> CIRCLE;//������ ������ �������
		fin >> buff;
		fin >> GF;//������ ������ ��������� �������
		fin >> buff;

		while (fin >> r) k++;//���� ���������� ����� �����������, ���������� � �������� 
		N = k / 2;//���������� �������� ��������� �������� �����
		masPoints = new BasisPoint[N];//�������� ������� �����

		fin.clear();
		fin.seekg(0, ios::beg);//��������� ��������� �� ������ �����, ����� ������� �������� ������, �� ��� � �������
		fin >> buff; fin >> CIRCLE; fin >> buff; fin >> GF; fin >> buff;
		for (int i = 0; i < N; i++) fin >> masPoints[i].x >> masPoints[i].y;//���������� ������� �����
		fin.close();
	}

	void read_rand()
	{
		char buff[150];//�������� ���������������� ����������� �������
		int k = 0; //�������
		double r;//��������������� �������������� �����	
		ifstream fin("input.txt"); //���������� ������� ��� ������ �� �����
		fin >> buff;//������ �������� ��������� ����������
		fin >> CIRCLE;//������ ������ �������
		fin >> buff;
		fin >> GF;//������ ������ ��������� �������
		fin.close();
	}

	void DeleteElement(int i, BasisPoint *a) //�������� �� ������� �������� i
	{
		for (int j = i; j < N - 1; j++) a[j] = a[j + 1];
		N--;
	}

	void ExceptionMas(BasisPoint *masPoints)//���������� �� ������� ������������� ���������
	{
		for (int i = 1; i < N; i++)
		{
			if (masPoints[i - 1].x == masPoints[i].x && masPoints[i - 1].y == masPoints[i].y) { DeleteElement(i, masPoints);  i--; }//�������� �� ������� ����� ������������� ���������
		}
	}
	bool Comporator(BasisPoint a, BasisPoint b)//������� �����������
	{
		if (a.y < b.y)return true;//c�������� �� ������ ����������
		else if (a.y > b.y) return false;
		else return a.x < b.x;//���� ������ ���������� �����, ��������� �� ������ ����������
	}
	void Screening()
	{
		sort(masPoints, masPoints + N, Comporator);//���������� ����� �� �����������
		ExceptionMas(masPoints);//���������� ������������� �����
	}

	//��������� �� ������
	void WriteAboutError()
	{
		ofstream fout("output.txt");
		fout << "�������������� ����� ��������� ������� ��� �������! ����� ������� " << CIRCLE << " ������ ������� � " << KGF << " ��������� �������!" << endl;
		exit(0);
		fout.close();
	}
	void Display() //������������� ������ ���� ������ �� ����� ������� � ��������� ������
	{
		if ((GF <= 0) || (GF > KGF) || (CIRCLE > MAXCIRCLE) || (CIRCLE <= 0)) WriteAboutError();//���� ��������� ����� ������ ����� ��������� ������� �� ������
		else
		{
			fi = TestFuncAndCurve::GFunctions[GF - 1];//��������� ������� - ������� � ������� GF ��� ������ � ������� CIRCLE

			/*if(GF=4) fi0=TestFuncAndCurve::g40;
			else fi0=fi;*/

			Curve c1(0, 2 * pi, TestFuncAndCurve::u1, TestFuncAndCurve::v1);
			Curve c2(0, 3 * MIN_RADIUS, TestFuncAndCurve::u2, TestFuncAndCurve::v2);
			Curve c3(0, 4 * MIN_RADIUS, TestFuncAndCurve::u3, TestFuncAndCurve::v3);
			Curve c4(0, 1.5 * MIN_RADIUS, TestFuncAndCurve::u4, TestFuncAndCurve::v4);
			switch (CIRCLE) {
			case 1:
				myCurve = c1;
				break;
			case 2:
				myCurve = c2;
				break;
			case 3:
				myCurve = c3;
				break;
			case 4:
				myCurve = c4;
				//fi = TestFuncAndCurve::g40;
				break;
			}
		}

	}

	void Building(int t)//���������� ������� ����� ��� ������ �� ����� ��� ��� �������������
	{
		if (t > 0)//���������� ������� �������� ����� �� �� ����� 
		{
			read_rand();//������ ������ �� �� �����
			Display();//������������� ������ ���� ������ �� ����� - ������� � ��������� �������

			Curve c1(0, 2 * pi, TestFuncAndCurve::u1h, TestFuncAndCurve::v1h);//������, � ����������� ������� ��� ����� �������
			Curve c2(0, 3 * MAX_RADIUS, TestFuncAndCurve::u2h, TestFuncAndCurve::v2h);
			Curve c3(0, 4 * MAX_RADIUS, TestFuncAndCurve::u3h, TestFuncAndCurve::v3h);
			Curve c4(0, 1.5 * MAX_RADIUS, TestFuncAndCurve::u4h, TestFuncAndCurve::v4h);

			switch (CIRCLE) {
			case 1:
				FillMassiv(c1, t);//��������� ������
				break;
			case 2:
				FillMassiv(c2, t);//��������� ������
				break;
			case 3:
				FillMassiv(c3, t);//��������� ������
				break;
			case 4:
				FillMassiv(c4, t);//��������� ������
				//fi= TestFuncAndCurve::GFunctions[GF - 1];
				break;
			}

			//for (int i = 0; i < N; i++) cout<<masPoints[i].x <<" "<< masPoints[i].y<<endl;cout<<endl;
			RandomSwapping(N * 2);//���������� ������ � ������� ��������
			//for (int i = 0; i < N; i++) cout<<masPoints[i].x <<" "<< masPoints[i].y<<endl;cout<<endl;
		}
		else
		{
			ReadFile();//������ ������ �� �����
			Display();//������������� ������ ���� ������ �� ����� - ������� � ��������� �������
			Screening();//���������� �� ������� ����� ���������� �����
			RandomSwapping(N * 2);//���������� ������
		}
		/*cout<<CIRCLE<<" "<<GF<<endl;
		for (int i = 0; i < N; i++) cout<<masPoints[i].x <<" "<< masPoints[i].y<<endl;*/
	}
	void Building(int t, int g, int cu)//���������� ������� ����� ��� ������ �� ����� ��� ��� �������������
	{
		GF = g;
		CIRCLE = cu;
		Display();//������������� ������ ���� ������ �� ����� - ������� � ��������� �������
		Curve c1(0, 2 * pi, TestFuncAndCurve::u1h, TestFuncAndCurve::v1h);//������, � ����������� ������� ��� ����� �������
		Curve c2(0, 3 * MAX_RADIUS, TestFuncAndCurve::u2h, TestFuncAndCurve::v2h);
		Curve c3(0, 4 * MAX_RADIUS, TestFuncAndCurve::u3h, TestFuncAndCurve::v3h);
		Curve c4(0, 1.5 * MAX_RADIUS, TestFuncAndCurve::u4h, TestFuncAndCurve::v4h);

		switch (CIRCLE) {
		case 1:
			FillMassiv(c1, t);//��������� ������
			break;
		case 2:
			FillMassiv(c2, t);//��������� ������
			break;
		case 3:
			FillMassiv(c3, t);//��������� ������
			break;
		case 4:
			FillMassiv(c4, t);//��������� ������
			//fi= TestFuncAndCurve::GFunctions[GF - 1];
			break;
		}

		//for (int i = 0; i < N; i++) cout<<masPoints[i].x <<" "<< masPoints[i].y<<endl;cout<<endl;
		RandomSwapping(N * 2);//���������� ������ � ������� ��������
		//for (int i = 0; i < N; i++) cout<<masPoints[i].x <<" "<< masPoints[i].y<<endl;cout<<endl;
	}
	void WriteError(double *x, double EPS) //����� �������� (����� ������ �������)
	{
		//������ � ����
		char buf[250];
		string str;
		memset(buf, 0, sizeof(buf));
		string d1 = toString(baseMethod), d2 = toString(N), d3 = toString(MIN_RADIUS), d4 = toString(MAX_RADIUS), d5 = toString(GF), d6 = toString(CIRCLE);
		str = "������ ������� � �������� ������������� ��� ������� " + d5 + " ������� " + d1 + " ��� ����� ������� " + d2 + ".txt";
		strncpy(buf, str.c_str(), sizeof(buf) - 1);

		ofstream fout(buf);
		fout << "������ ������� (" << N << " �����):" << endl;
		for (int i = 0; i < N; i++) fout << x[i] << endl;
		fout << "������������ ������� ��� ���������� ������� " << N << " ����� " << NEVA << endl;//������� �������
		fout << "������� ������������ ������� � ��������� �������� ��� ����� �������� ������� " << N << " ����� " << EPS << endl;
		RESULT = EPS;
		fout.close();
	}

	void Matrix_power(double *Ax, double **a, double *x) //���������� ������� Ax ������������ a*x ������� �� ������
	{
		for (int i = 0; i < N; i++)
		{
			double sum = 0;
			for (int j = 0; j < N; j++) sum += a[i][j] * x[j];
			Ax[i] = sum;
		}
	}

	//������� �������
	double Nev(double **a, double *x, double *b)
	{
		double *Ax = new double[N];
		Matrix_power(Ax, a, x);
		double s = 0;
		for (int i = 0; i < N; i++) s += ((Ax[i] - b[i])*(Ax[i] - b[i]));
		return sqrt(s);
	}

	void Error()//���������� � ����� �������� �� ���������� �������
	{
		double p = myCurve.Firstkind(N, N), sum = 0;
		double *Ax = new double[N];
		Matrix_power(Ax, MySLAU.a, MySLAU.x);
		for (int i = 0; i < N; i++) sum += MySLAU.x[i] * Ax[i];//myCurve.Firstkind(i,N);
		WriteError(MySLAU.x, sqrt(abs(p - sum)));
	}

	void Search()
	{
		MySLAU.Make(N);//������� ������� �������, ������� ����� �������� �����

		for (int i = 0; i < N; i++) //��������� �������
		{
			MySLAU.b[i] = myCurve.Firstkind(i, N);
			MySLAU.a[i][i] = myCurve.Firstkind(i, i);
			for (int j = i + 1; j < N; j++) //��� ��� ������� ��������������
			{
				double tmp = myCurve.Firstkind(i, j);
				MySLAU.a[i][j] = tmp;
				MySLAU.a[j][i] = tmp;
			}
		}

		/*cout << "������� ������� � ��������� ������: " << endl;
		for (int i = 0; i < N; i++)
		{
			cout << endl;
			for (int j = 0; j < N; j++)cout << MySLAU.a[i][j] << " ";
		}
		cout << endl; cout << endl;
		for (int i = 0; i < N; i++) cout << MySLAU.b[i] << endl; cout << endl;*/


		//-----------------------------------------������ �������-----------------------------------
		Method_des(N, baseMethod);
		//cout << "������� ��� "<<N<<" ������� = " << Nev(MySLAU.a, MySLAU.x, MySLAU.b) << endl;

		//������� �������, ����� � ������� �����������		
		Error();
	}
}

namespace ForFixity//��� ��������� ������� ����������� ������������� �� ����� �����
{
	double Min(double a, double b)
	{
		if (a < b) return a;
		return b;
	}

	double ReturnError() //������� �����������
	{
		double p = myCurve.Firstkind(N, N), sum = 0;

		double *Ax = new double[N];
		ForDesigion::Matrix_power(Ax, MySLAU.a, MySLAU.x);
		for (int i = 0; i < N; i++) sum += MySLAU.x[i] * Ax[i];
		return sqrt(abs(p - sum));
	}

	void Show(double *Errors) //��������� ������ ������� �� ������ ������� ����� 
	{
		double max = log10(Errors[0]), min = log10(Errors[N - 1]);
		for (int i = 0; i < N; i++)//����������� �������� � ���������
		{
			double tmp = log10(Errors[i]);
			if (tmp < min) min = tmp;
			if (tmp > max) max = tmp;
		}

		//������ ������� ����
		double	a0 = -1 + 0,
			b0 = 1 + N,
			c0 = -1 + min,
			d0 = 1 + max;

		SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
		SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B) � ��������� [a,b]x[c,d]
		SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
		xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � ������ 1 � 0.1 �� �

		SetColor(250, 0, 0); // ������ ���� ����� (�������)
		SetPoint(0, myCurve.Firstkind(N, N)); // ������������� ������ �� ����� 

		for (int i = 0; i < N; i++) Line2(i + 1, log10(Errors[i])); //cout<<i<<" "<<Errors[i]<<endl;

		char buf[250];
		string str;
		memset(buf, 0, sizeof(buf));
		string d2 = toString(N), d3 = toString(GF), d4 = toString(CIRCLE), d5 = toString(GF), d6 = toString(baseMethod);
		//str = "������ 2 �������� ������������� � ����������� �� ����� �������� ������� (" + d2 + ").bmp";
		str = "������ 2 �������� ������������� ������� (" + d3 + ") �� ������� (" + d4 + ") ������� " + d6 + " � ����������� �� ����� �������� ������� (" + d2 + ").bmp";
		strncpy(buf, str.c_str(), sizeof(buf) - 1);
		CloseWindow(buf);
		//CloseWindow("������ 2 �������� ������������� � ����������� �� ����� �������� �������.bmp");// ��������� ���� (������� bmp-����)
	}

	void Show(double *ErrorsA, double *ErrorsB, Method A, Method B) //��������� ������ ������� �� ������ ������� ����� 
	{
		double max = log10(ErrorsA[0]), min = log10(ErrorsA[N - 1]);
		for (int i = 0; i < N; i++)//����������� �������� � ���������
		{
			double tmp = log10(ErrorsA[i]);
			double tmpp = log10(ErrorsB[i]);
			if (tmp < min) min = tmp;
			if (tmp > max) max = tmp;
			if (tmpp < min) min = tmpp;
			if (tmpp > max) max = tmpp;
		}

		//������ ������� ����
		double	a0 = -1 + 0,
			b0 = 1 + N,
			c0 = -1 + min,
			d0 = 1 + max;

		SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
		SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B) � ��������� [a,b]x[c,d]
		SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
		xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � ������ 1 � 0.1 �� �

		SetColor(250, 0, 0); // ������ ���� ����� (�������)
		SetPoint(0, myCurve.Firstkind(N, N)); // ������������� ������ �� ����� 

		for (int i = 0; i < N; i++) Line2(i + 1, log10(ErrorsA[i])); //cout<<i<<" "<<Errors[i]<<endl;

		SetColor(0, 250, 0); // ������ ���� ����� (�������)
		SetPoint(0, myCurve.Firstkind(N, N)); // ������������� ������ �� ����� 
		for (int i = 0; i < N; i++) Line2(i + 1, log10(ErrorsB[i])); //cout<<i<<" "<<Errors[i]<<endl;

/*
		SetColor(0, 0, 250); // ������ ���� ����� (�����)
		SetPoint(0, myCurve.Firstkind(N, N)); // ������������� ������ �� �����
		for (int i = 0; i < N; i++) Line2(i + 1, Min(log10(ErrorsA[i]),log10(ErrorsB[i]))); //cout<<i<<" "<<Errors[i]<<endl;
*/

		char buf[250];
		string str;
		memset(buf, 0, sizeof(buf));
		string d2 = toString(N), d3 = toString(GF), d4 = toString(CIRCLE), d5 = toString(A), d6 = toString(B);
		//str = "������ 2 �������� ������������� � ����������� �� ����� �������� ������� (" + d2 + ").bmp";
		str = "������ 2 �������� ������������� ������� (" + d3 + ") �� ������� (" + d4 + ") � ����������� �� ����� �������� ������� (" + d2 + ") ��� ������� " + d5 + " (�������) � " + d6 + " (������).bmp";
		strncpy(buf, str.c_str(), sizeof(buf) - 1);
		CloseWindow(buf);
		//CloseWindow("������ 2 �������� ������������� � ����������� �� ����� �������� �������.bmp");// ��������� ���� (������� bmp-����)
	}

	double Error(int k) //��������� �����������
	{
		double p = myCurve.Firstkind(N, N), sum = 0;

		double *Ax = new double[N];
		Func_in_matrix::Matrix_power(Ax, MySLAU.a, MySLAU.x, k);
		for (int i = 0; i < k; i++) sum += MySLAU.x[i] * Ax[i];
		double EPS = abs(p - sum);
		return sqrt(EPS);

	}

	void Create(double *Errors)
	{
		cout << "��� ������� � ����������� �� ����� �����:" << endl;
		for (int i = 0; i < N/* - 1*/; i++)
		{
			Method_des(i, baseMethod);//������ ��������� ������� ������ �������
			Errors[i] = Error(i);//��������� ������ ������������
			/*
			if ((i > 0) && (Errors[i] > Errors[i - 1]))//���� ��������� ������, ���������� ������� ������������� ������
			{
				Method_des(i, Gauss+Speedy);//������ ��������� ������� ������ �������
				Errors[i] = Error(i);//��������� ������ ������������
			}
			*/

			if (i % 10 == 0) cout << i + 1 << " -> " << Errors[i] << endl;//�������� ������ �������
		}
		//Errors[N - 1] = RESULT;
	}

	void Create(double *ErrorsA, double *ErrorsB, Method A, Method B)
	{
		cout << "��� ������� � ����������� �� ����� �����:" << endl;
		for (int i = 0; i < N; i++)
		{
			Method_des(i, A);//������ ��������� ������� ������ �������
			ErrorsA[i] = Error(i);//��������� ������ ������������
			if (i % 10 == 0) cout << i + 1 << " (A) -> " << ErrorsA[i] << endl;//�������� ������ �������

		}//��� ������������� ������-������� ���������� ��������� �� ��� �����
		for (int i = 0; i < N; i++)
		{
			Method_des(i, B);//������ ��������� ������� ������ �������
			ErrorsB[i] = Error(i);//��������� ������ ������������
			if (i % 10 == 0) cout << i + 1 << " (B) -> " << ErrorsB[i] << endl;//�������� ������ �������
		}
	}

	void WriteAboutZero(int NN, int GFf, int cCIRCLE, Method meth, int num)//��������� �� ������ ��� ������� 2
	{
		//������ � ����
		char buf[250];
		string str;
		memset(buf, 0, sizeof(buf));
		string d2 = toString(NN), d3 = toString(GFf), d4 = toString(cCIRCLE), d6 = toString(meth);
		str = "��������� �� ������ ��� ������� 2 ������������ (��� log) �������� ������������� ������� (" + d3 + ") �� ������� (" + d4 + ") ������� " + d6 + " � ����������� �� ����� �������� ������� (" + d2 + ").txt";
		strncpy(buf, str.c_str(), sizeof(buf) - 1);
		ofstream fout(buf);
		fout << "���������� ��������� ��������������� ������, ��������� �� �������� " << num << "(=0) ������� ��������� �������� -infinity";
		fout.close();
	}

	void WriteMassiv(double *x) //����� ������� ������������
	{
		//������ � ����
		char buf[250];
		string str;
		memset(buf, 0, sizeof(buf));
		string d2 = toString(N), d3 = toString(GF), d4 = toString(CIRCLE), d6 = toString(baseMethod);
		str = "���� 2 ������������ (��� log) �������� ������������� ������� (" + d3 + ") �� ������� (" + d4 + ") ������� " + d6 + " � ����������� �� ����� �������� ������� (" + d2 + ").txt";
		strncpy(buf, str.c_str(), sizeof(buf) - 1);
		ofstream fout(buf);

		zero = true;//����� ��� 
		int j;//����� � ����
		double min = x[0], max = x[0], mins = -1, maxs = -1;//����������� �������, ������������, ������ ������, ������������ ������
		int mini = 0, maxi = 0, mins1 = -1, maxs1 = -1, mins2 = -1, maxs2 = -1;//��������������� ������
		for (int i = 0; i < N; i++)
		{
			fout << x[i] << endl;
			if (x[i] == 0)
			{
				zero = false;//���� ����
				j = i;//������������� �����
			}
			//����� ������������ � ������������� ��������
			if (x[i] < min) {
				min = x[i]; mini = i;
			}
			else if (x[i] > max) {
				max = x[i]; maxi = i;
			}
		}

		for (int i = 1; i < N; i++)
		{
			if (x[i] - x[i - 1] > 0)
			{
				mins = x[i] - x[i - 1];
				mins1 = i - 1;
				mins2 = i;
				maxs = mins;
				maxs1 = mins1;
				maxs2 = mins2;
				for (int j = i + 1; j < N; j++)
				{
					double p = x[j] - x[j - 1];
					if (p > 0)
					{
						if (p > maxs)
						{
							maxs = p;
							maxs1 = j - 1;
							maxs2 = j;
						}
					}
				}
				goto end1;
			}
		}
	end1:
		fout << endl;
		fout << "������ �������:" << endl;
		fout << "1)����������� �������� " << min << " �� �������� " << mini << endl;
		fout << "2)������������ �������� " << max << " �� �������� " << maxi << endl;
		if (mins > 0)
		{
			fout << "3)������ ������ " << mins << " � �������a " << mins1 << " �� ������� " << mins2 << endl;
			fout << "4)������������ ������ " << maxs << " � �������a " << maxs1 << " �� ������� " << maxs2 << endl;
		}

		fout.close();

		if (!zero) WriteAboutZero(N, GF, CIRCLE, baseMethod, j);//�������� ��������� �� ������
	}

}

namespace ForQuality
{
	void Draw_CIRCLE(double radius, int R, int G, int B)//���������� ����������
	{
		SetColor(R, G, B); // ������ ���� ����� 
		double d = radius - MIN_RADIUS;
		Curve c3(0, 3 * radius, TestFuncAndCurve::u2h, TestFuncAndCurve::v2h);
		switch (CIRCLE) {
		case 1:
			SetPoint(radius, 0); // ������������� ������ �� ����� 
			for (double i = EPS; i <= 2 * pi; i += EPS) Line2(radius*cos(i), radius*sin(i));//������ CIRCLE	
			break;
		case 2://�����������
			SetPoint(-0.5*d, -0.5*d / sqrt(3));
			Line2(-0.5*d + radius, -0.5*d / sqrt(3));
			Line2(-0.5*d + 0.5*radius, -0.5*d / sqrt(3) + 0.5*radius*sqrt(3));
			Line2(-0.5*d, -0.5*d / sqrt(3));
			//Line2(c3.Transfer(radius).x, c3.Transfer(radius).y);
			//Line2(c3.Transfer(2*radius).x, c3.Transfer(2*radius).y);
			//Line2(c3.Transfer(3*radius).x, c3.Transfer(3*radius).y);

			/*cout<<-0.5*d<<" "<< -0.5*d/sqrt(3)<<endl;
			cout<<-0.5*d + radius<<" "<< -0.5*d/sqrt(3)<<endl;
			cout<<-0.5*d + 0.5*radius<<" "<< -0.5*d/sqrt(3) + 0.5*radius*sqrt(3)<<endl;
			cout<<-0.5*d<<" "<< -0.5*d/sqrt(3)<<endl;*/
			break;
		case 3://�������
			SetPoint(-0.5*d + 0, -0.5*d + 0);
			Line2(-0.5*d, -0.5*d + radius);
			Line2(-0.5*d + radius, -0.5*d + radius);
			Line2(-0.5*d + radius, -0.5*d + 0);
			Line2(-0.5*d + 0, -0.5*d + 0);
			break;
		case 4://������
			SetPoint(-0.5*d + 0, -0.25*d*sqrt(3) + 0);
			Line2(-0.5*d + radius, -0.25*d*sqrt(3) + 0);

			for (double i = EPS; i <= pi / 3; i += EPS) Line2(radius*cos(i) - 0.5*d, radius*sin(i) - 0.25*d*sqrt(3));//������ CIRCLE	
			for (double i = 2 * pi / 3; i <= pi; i += EPS) Line2(radius*cos(i) - 0.5*d + radius, radius*sin(i) - 0.25*d*sqrt(3));//������ CIRCLE
			break;
		}


	}
	void Draw_mas(BasisPoint* r, int R, int G, int B)//���������� ������ �����
	{
		SetColor(R, G, B); // ������ ���� �����
		double e = 0.01;
		for (int i = 0; i < N; i++)
		{
			SetPoint(r[i].x - 100 * EPS, r[i].y - e); // ������������� ������ �� ����� 
			Line2(r[i].x + 100 * EPS, r[i].y + e);//������ line
			SetPoint(r[i].x - 100 * EPS, r[i].y + e); // ������������� ������ �� ����� 
			Line2(r[i].x + 100 * EPS, r[i].y - e);//������ line
		}

	}
}

//��������� ��������������� �������
void Illustrating(double(*fi)(BasisPoint), BasisPoint *masPoints, double *x, Curve myCurve, int m);
void Fixity();
void Fixity(Method A, Method B);
void Quality(int s, int d, int g, int cu);
void Desigion(int s);
void Pictures_qua(int m, int minN, int maxN, int cu);
void Pictures_fix(int minN, int maxN, int cu);
void Pictures_ill(int minN, int maxN, int hh);

void FileGrafic()//�������� �������� �� ������ � �����
{
	char buff[150], tmp;//�������� ���������������� ����������� �������
	int a, b, c, d;
	ifstream fin("�������� ��������.txt"); //���������� ������� ��� ������ �� �����
	fin >> buff;//������ �������� ��������� ����������
	fin >> tmp;
	if (tmp == '+')//��� ��� ������������
	{
		fin >> buff;
		fin >> CIRCLE;
		fin >> buff;
		fin >> GF;
		//ForDesigion::Display();
		fin >> buff;
		fin >> a;
		Desigion(a);//���������� ������� �� ����� (0) ��� ��� ������������� (>0), ������� � ����� �������
		//Illustrating(fi, masPoints, MySLAU.x, myCurve, 1);// ������ ��������� ������� � �����������
		Fixity();//������ ����������� ����������� ������������� �� ����� �������� �����
	}
	else for (int i = 1; i <= 6; i++) fin >> buff;

	fin >> buff;//������ �������� ��������� ����������
	fin >> tmp;
	if (tmp == '+')
	{
		fin >> buff;
		fin >> a;
		fin >> buff;
		fin >> b;
		fin >> buff;
		fin >> c;
		Pictures_fix(a, b, c);
	}
	else for (int i = 1; i <= 6; i++) fin >> buff;

	fin >> buff;//������ �������� ��������� ����������
	fin >> tmp;
	if (tmp == '+')
	{
		fin >> buff;
		fin >> a;
		fin >> buff;
		fin >> b;
		fin >> buff;
		fin >> c;
		fin >> buff;
		fin >> d;
		Pictures_qua(a, b, c, d);
	}
	else for (int i = 1; i <= 8; i++) fin >> buff;

	fin.close();
}

void Make_TestFuncAndCurve()//������� �������� �������
{
	//���������� ������� � �����
	/*double	a0 = -MAX_RADIUS*1.1,
		b0 = -a0,
		c0 = a0,
		d0 = -a0;
	SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
	SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B) � ��������� [a,b]x[c,d]
	SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
	xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � � �� �
	ForQuality::Draw_CIRCLE(1, 255, 0, 0);

	CloseWindow("���������.bmp");*/
	//MAX_RADIUS=MIN_RADIUS; //���� ������� ���, �� ����� ����������
	Desigion(7);

	//Curve q(0,1.5*MAX_RADIUS,TestFuncAndCurve::u4h,TestFuncAndCurve::v4h);
	//cout << TestFuncAndCurve::g4(q.Transfer(0.25*MAX_RADIUS)) << " " << TestFuncAndCurve::g4(q.Transfer(0.80*MAX_RADIUS)) << " " << TestFuncAndCurve::g4(q.Transfer(1.3*MAX_RADIUS)) << endl;
	/*BasisPoint a,b,c;
	a.x=-1;a.y=0;
	b.x=1;b.y=0;
	c.x=0;c.y=-1;
	cout << TestFuncAndCurve::g8(a) << " " << TestFuncAndCurve::g8(b) << " " << TestFuncAndCurve::g8(c) << endl;*/
	mkdir("name_dir");
	ofstream fout("name_dir\\new_file.txt");
	fout.close();
	/*cout << TestFuncAndCurve::g8(myCurve.Transfer(0.25*MIN_RADIUS)) << " " << TestFuncAndCurve::g8(myCurve.Transfer(0.80*MIN_RADIUS)) << " " << TestFuncAndCurve::g8(myCurve.Transfer(1.3*MIN_RADIUS)) << endl;
	cout << myCurve.Transfer(0.25*MIN_RADIUS).x << " " << myCurve.Transfer(0.25*MIN_RADIUS).y << endl;
	cout << myCurve.Transfer(0.8*MIN_RADIUS).x << " " << myCurve.Transfer(0.8*MIN_RADIUS).y << endl;
	cout << myCurve.Transfer(1.3*MIN_RADIUS).x << " " << myCurve.Transfer(1.3*MIN_RADIUS).y << endl;*/
	//cout<<atan((0.3-0.25*sqrt(3))/0.15)<<" "<<-pi/3<<endl;
	//cout<<myCurve.a<<" "<<myCurve.b<<endl;
}

//�������� �������
int main()
{
	setlocale(LC_ALL, "Russian");

	//FileGrafic();
	//Make_TestFuncAndCurve();

	//Desigion(18);//���������� ������� �� ����� (0) ��� ��� ������������� (>0), ������� � ����� �������
	//Illustrating(fi, masPoints, MySLAU.x, myCurve, 1);// ������ ��������� ������� � �����������
	//Fixity();//������ ����������� ����������� ������������� �� ����� �������� �����

	//Quality(10, 8, 0, 0);//������ ����������� ����������� �� ������, ����� ������� ������� �������� �����
	//Pictures_fix(30, 180, 30);//�������� ����������� ����������� ������������� ��� �� 30 �� 40 �������, ��� 30
	//Pictures_qua(40, 25, 105, 50);//�������� ����������� ����������� �� ������ ��� 20 ������� � ������� �� 40 �� 100 � ����� 20
	Pictures_ill(4,10,3);//������� ����������� ��� 4-10 ������� � ����� 3

	return 0;
}

void Desigion(int s)
{
	ForDesigion::Building(s);//������ � ������ � �������
	ForDesigion::Search();//����� ������� � ����� �����������
}
void Desigion(int s, int g, int cu) {
	ForDesigion::Building(s, g, cu);//������ � ������ � �������
	ForDesigion::Search();//����� ������� � ����� �����������
}

//���������������
void Illustrating(double(*fi)(BasisPoint), BasisPoint *masPoints, double *x, Curve myCurve, int m)
{
	//fi=fi0;
	/*const double EPS = 0.0001;*/
	double max = fi(myCurve.Transfer(myCurve.a)), min = max;//����� ������������ � ������������� �������� ��������� �������

	for (double i = myCurve.a + EPS; i <= myCurve.b; i += EPS)
	{
		double tmp = fi(myCurve.Transfer(i));
		if (tmp < min) min = tmp;
		if (tmp > max) max = tmp;
	}

	//������������� �������� ����
	double	a0 = -myCurve.a - 1 + 0,
		b0 = 1 + myCurve.b,
		c0 = -1 + min,
		d0 = 1 + max;

	SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
	SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B)
	// � ��������� [a,b]x[c,d]
	SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
	xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � ������ 1 � 1 �� �

	// ������ ������ ��������� �������
	SetColor(0, 255, 0); // ������ ���� ����� (������)
	SetPoint(myCurve.a, fi(myCurve.Transfer(myCurve.a))); // ������������� ������ �� ����� 
	for (double i = myCurve.a + EPS; i <= myCurve.b - EPS; i += EPS)Line2(i, fi(myCurve.Transfer(i)));

	// ������� ���� m ������������� �������

	double sum = 0;
	SetColor(101, 10, 150); // ������ ���� �����

	for (int i = 1; i <= N; i++) sum += x[i - 1] * masPoints[i - 1].Potentialf(myCurve.Transfer(myCurve.a));

	SetPoint(myCurve.a, sum); // ������������� ������ �� ����� 

	cout << "���������� ��������� ������� ��� �������.������ " << CIRCLE << ". " << GF << endl;

	for (double j = myCurve.a + EPS; j <= myCurve.b; j += EPS)
	{
		sum = 0;
		for (int i = 1; (i <= N); i++) {
			sum += x[i - 1] * masPoints[i - 1].Potentialf(myCurve.Transfer(j));
		}
		Line2(j, sum);
	}

	//
	//	int k = abs(N-0*m);
	//	while (k <= N) {
	//
	//		double sum = 0;
	//		SetColor(20 * k, 10 * k, 15 * k); // ������ ���� �����
	//
	//		for (int i = 1; (i <= k) /*&& (i <= N)*/; i++) {
	//			sum += x[i - 1] * masPoints[i - 1].Potentialf(myCurve.Transfer(myCurve.a));
	//		}
	//		SetPoint(myCurve.a, sum); // ������������� ������ �� ����� 
	//
	//		for (double j = myCurve.a + EPS; j <= myCurve.b; j += EPS) {
	//			sum = 0;
	//			for (int i = 1; (i <= k) /*&& (i <= N)*/; i++) {
	//				sum += x[i - 1] * masPoints[i - 1].Potentialf(myCurve.Transfer(j));
	//			}
	//			Line2(j, sum);
	//		}
	//
	//		k += m;
	//	}


   //������ � ���� bmp
	char buf[150];
	string str;
	memset(buf, 0, sizeof(buf));
	string d1 = toString(GF), d2 = toString(CIRCLE), d3 = toString(N);
	str = "������ 1 ��������� ������� (" + d1 + ") � � ����������� ��� ����� �������� ����� (" + d3 + ") �� ������ (" + d2 + ").bmp";

	strncpy(buf, str.c_str(), sizeof(buf) - 1);
	CloseWindow(buf);
	//CloseWindow("������ 1 ��������� ������� � � �����������.bmp");// ��������� ���� (������� bmp-����)

//fi=TestFuncAndCurve::GFunctions[GF-1];
}

void Fixity() {//������ ������� (����� �����������)->(���������� �� ��������� �������)

	VALUE_FOR_ULTRA = 10;//?
	double *Errors = new double[N];//������ ������������
	ForFixity::Create(Errors);//��������� ������ ������
	ForFixity::WriteMassiv(Errors);//������� �����������
	if (zero)ForFixity::Show(Errors);//���������� �������� ������
}

void Fixity(Method A, Method B) {//������ ������� (����� �����������)->(���������� �� ��������� �������) ��� ������� A � B
	VALUE_FOR_ULTRA = 10;//?
	double *ErrorsA = new double[N];//������ ������������ A
	double *ErrorsB = new double[N];//������ ������������ A
	ForFixity::Create(ErrorsA, ErrorsB, A, B);//��������� ������ ������
	/*if (zero)*/ForFixity::Show(ErrorsA, ErrorsB, A, B);//���������� �������� ������
}

void Quality(int s, int d, int g, int cu)//������ ����������� �������� ������������� �� ������� ��� s �������� � d ������
{

	//tmp=10;//?
	double *Errors = new double[d];//������ ������������
	double EPSs = (MAX_RADIUS - MIN_RADIUS) / d;

	//���������� ������� � �����
	double	a0 = -MAX_RADIUS*1.1,
		b0 = -a0,
		c0 = a0,
		d0 = -a0;
	SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
	SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B) � ��������� [a,b]x[c,d]
	SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
	xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � � �� �

	ForQuality::Draw_CIRCLE(MIN_RADIUS, 250, 0, 0);//���������� ���c��� ����������� ���������� //������ �� ������

	//���������� �������
	cout << cu/*CIRCLE*/ << ". " << g/*GF*/ << ". ��� ������� � ����������� �� �������:" << endl;
	int i = 0;
	double tmp = MAX_RADIUS;
	bool isred = false;//������� ������ � ������ ����
	for (MAX_RADIUS = MIN_RADIUS + EPSs; MAX_RADIUS <= tmp; MAX_RADIUS += EPSs)
	{
		VALUE_FOR_ULTRA = 10;
		if ((g != 0) && (cu != 0))Desigion(s, g, cu);
		else Desigion(s);
		Errors[i] = ForFixity::ReturnError();

		mr = 0;
		mg = int(fabs(250 - i - 1)) % 250;
		mb = int(fabs(i)) % 250;
		ForQuality::Draw_CIRCLE(MAX_RADIUS, mr, mg, 0);//���������� ����������
		if (Errors[i] == 0) { mr = 250; mg = 0; mb = 0; isred = true; }//���� �� ���� ������ �������� �����������, ���������� �� ��������
		ForQuality::Draw_mas(masPoints, mr, mg, mb);//���������� ����� ������� masPoints

		if (i % 10 == 0) cout << "���������� ��� ������� ������� " << MIN_RADIUS << " � ������� ������ " << MAX_RADIUS << " ����� " << Errors[i] << endl;
		i++;
		if (i == d) break;
	}
	cout << "------������ ������ �������" << endl;

	//������ � ���� ������� � �������
	char buf[250];
	string str, newstr;
	memset(buf, 0, sizeof(buf));
	string d1 = toString(s), d2 = toString(d), d3 = toString(MIN_RADIUS), d4 = toString(MAX_RADIUS), d5 = toString(GF), d6 = toString(CIRCLE), d7 = toString(baseMethod);
	//str = "���� 3 ������������ �������� ������������� ��������� ������� (" + d5 + ") �� ������ (" + d6 + ") ������� " + d7 + " � ����������� �� �������,(" + d1 + ") ������������� �������, (" + d2 + ") ������ ����� ������������ �������� (" + d3 + ") � (" + d4 + ").txt";
	str = "���� 3 ������������ �������� ������������� ������� " + d7 + " � ����������� �� �������,(" + d1 + ") ������������� �������, (" + d2 + ") ������ ����� ������������ �������� (" + d3 + ") � (" + d4 + ").txt";
	newstr = bstr + sl + str;//������ �����
	strncpy(buf, newstr.c_str(), sizeof(buf) - 1);
	ofstream fout(buf);


	if (isred) {

		//������ � ���� bmp ������� ������ � �����
		memset(buf, 0, sizeof(buf));
		//str = "������ 3.2 ������ � �������� ����������� ��� ��������� ������� (" + d5 + ") �� ������ (" + d6 + ") ������� " + d7 + " � ����������� �� �������,(" + d1 + ") ������������� �������, (" + d2 + ") ������ ����� ������������ �������� (" + d3 + ") � (" + d4 + ").bmp";
		str = "������ 3.2 ������ � �������� ����������� ������� " + d7 + " � ����������� �� �������,(" + d1 + ") ������������� �������, (" + d2 + ") ������ ����� ������������ �������� (" + d3 + ") � (" + d4 + ").bmp";
		newstr = bstr + sl + str;//������ �����
		strncpy(buf, newstr.c_str(), sizeof(buf) - 1);
		CloseWindow(buf);
	}

	zero = true;//����� ��� 
	int j;//����� ����
	double min = Errors[0], max = Errors[0], mins = -1, maxs = -1;//����������� �������, ������������, ������ ������, ������������ ������
	int mini = 0, maxi = 0, mins1 = -1, maxs1 = -1, mins2 = -1, maxs2 = -1;//��������������� ������
	for (int i = 0; i < d; i++)
	{
		fout << Errors[i] << " \t --> log10 = " << log10(Errors[i]) << endl;
		if ((Errors[i] <= 0) || (Errors[i] != Errors[i]))//�������� �� 0 � �� NaN
		{
			zero = false;
			j = i;
		}
		//����� ������������ � ������������� ��������
		if (Errors[i] < min) {
			min = Errors[i]; mini = i;
		}
		else if (Errors[i] > max) {
			max = Errors[i]; maxi = i;
		}

	}

	for (int i = 1; i < d; i++)
	{
		if (Errors[i] - Errors[i - 1] > 0)
		{
			mins = Errors[i] - Errors[i - 1];
			mins1 = i - 1;
			mins2 = i;
			maxs = mins;
			maxs1 = mins1;
			maxs2 = mins2;
			for (int j = i + 1; j < d; j++)
			{
				double p = Errors[j] - Errors[j - 1];
				if (p > 0)
				{
					if (p > maxs)
					{
						maxs = p;
						maxs1 = j - 1;
						maxs2 = j;
					}
				}
			}
			goto end1;
		}
	}
end1:
	fout << endl;
	fout << "������ �������:" << endl;
	fout << "1)����������� �������� " << min << " �� �������� " << mini << endl;
	fout << "2)������������ �������� " << max << " �� �������� " << maxi << endl;
	if (mins > 0)
	{
		fout << "3)������ ������ " << mins << " � �������a " << mins1 << " �� ������� " << mins2 << endl;
		fout << "4)������������ ������ " << maxs << " � �������a " << maxs1 << " �� ������� " << maxs2 << endl;
	}
	if (!zero) fout << "���������� ��������� ��������������� ������, ��������� �� �������� " << j + 1 << " (������ " << MIN_RADIUS + j*EPSs << ") ������� ��������� �������� " << log10(Errors[j]);
	/*if (!zero)//���� ���� ����, ������� ����� � ����
	{
		//������ � ����
		char buff[300];
		string strr;
		memset(buff, 0, sizeof(buff));
		strr = "��������� �� ������ ��� ������� 3 ������������ �������� ������������� ��������� ������� (" + d5 + ") �� ������ (" + d6 + ") ������� " + d7 + " � ����������� �� �������,(" + d1 + ") ������������� �������, (" + d2 + ") ������ ����� ������������ �������� (" + d3 + ") � (" + d4 + ").txt";
		strncpy(buff, strr.c_str(), sizeof(buff) - 1);
		ofstream fout(buff);//cout<<buff;
		fout << "���������� ��������� ��������������� ������, ��������� �� �������� " << j << "(������ "<<j*EPSs<<") ������� ��������� �������� -infinity";
		fout.close();
	}*/
	//else//����� ������� ������
	else //���������� ������, ���� ��� �����
	{
		double maxx = log10(Errors[0]), minn = max;
		for (int i = 1; i < d; i++)
		{
			double tmp = log10(Errors[i]);
			if (tmp < minn) minn = tmp;

			if (tmp > maxx) maxx = tmp;
		}

		//����������� �� ����� (��� ����, ����� ������ �������� ������ � �������)
		//double kmin=0; if(min<kmin) kmin=min;
		double	a0 = 0 - MIN_RADIUS / 100,
			b0 = /*1+ d*/MAX_RADIUS*1.2 /*+ EPSs*/,
			c0 = /*-MIN_RADIUS / 100 +*/ minn,
			d0;
		if (maxx > 0) d0 = /*1 +*/ maxx; else d0 = -a0;
		//cout << a0 << " " << b0 << " " << c0 << " " << d0 << endl;

		SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
		SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B) � ��������� [a,b]x[c,d]
		SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
		xyLine(0, 0, 1, 1);	// ������ ���, �������������� � �. (0,0), � ����� ������� �� � � �� �

		SetColor(250, 0, 0); // ������ ���� ����� (�������)
		SetPoint(MIN_RADIUS + EPSs, log10(Errors[0])); // ������������� ������ �� ����� 
		for (int i = 1; i < d; i++)
			Line2(MIN_RADIUS + (i + 1)*EPSs, log10(Errors[i]));//������ ��������

		//������ � ���� bmp
		memset(buf, 0, sizeof(buf));
		//str = "������ 3.1 �������� ������������� ��������� ������� (" + d5 + ") �� ������ (" + d6 + ") ������� " + d7 + " � ����������� �� �������,(" + d1 + ") ������������� �������, (" + d2 + ") ������ ����� ������������ �������� (" + d3 + ") � (" + d4 + ").bmp";
		str = "������ 3.1 �������� ������������� ������� " + d7 + " � ����������� �� �������,(" + d1 + ") ������������� �������, (" + d2 + ") ������ ����� ������������ �������� (" + d3 + ") � (" + d4 + ").bmp";
		newstr = bstr + sl + str;//������ �����
		strncpy(buf, newstr.c_str(), sizeof(buf) - 1);
		CloseWindow(buf);
	}
	fout.close();
}

//���������� ������� �������� ��� �� minN �� maxN �������, cu ������
void Pictures_fix(int minN, int maxN, int cu)
{
	int t = int(MAXCIRCLE*KGF*((maxN - minN) / cu + 1)), ind = 0;

	for (CIRCLE = 1; CIRCLE <= MAXCIRCLE; CIRCLE++)
	{
		for (GF = 1; GF <= KGF; GF++)
		{
			for (int m = minN; m <= maxN; m += cu)
			{
				ind++;
				Desigion(m, GF, CIRCLE);//���������� ������� �� ����� (0) ��� ��� ������������� (>0), ������� � ����� �������
				Fixity();//������ ����������� ����������� ������������� �� ����� �������� �����
				cout << "-------�������� " << t - ind << endl;
			}
		}
	}
}
//�������� ��� m ������� � ������� �� minN �� maxN � ����� cu
void Pictures_qua(int m, int minN, int maxN, int cu)
{
	string str1, str2;
	int tt = int(MAXCIRCLE*KGF*((maxN - minN) / cu + 1)), ind = 0;
	for (CIRCLE = 1; CIRCLE <= MAXCIRCLE; CIRCLE++)
	{
		memset(dir_Curve_name, 0, sizeof(dir_Curve_name));
		string d5 = toString(GF), d6 = toString(CIRCLE), d7 = toString(baseMethod);
		str1 = "������ ��� ������ " + d6;
		strncpy(dir_Curve_name, str1.c_str(), sizeof(dir_Curve_name) - 1);
		mkdir(dir_Curve_name);//������� ����� ��� ������

		for (GF = 1; GF <= KGF; GF++)
		{
			memset(dir_func_name, 0, sizeof(dir_func_name));
			string d5 = toString(GF), d6 = toString(CIRCLE), d7 = toString(baseMethod);
			str2 = "��� ��������� ������� " + d5;
			strncpy(dir_func_name, str2.c_str(), sizeof(dir_func_name) - 1);
			bstr = str1 + sl + str2;
			strncpy(chstr, bstr.c_str(), sizeof(chstr) - 1);
			mkdir(chstr);//������� � ��� ����� ��� �������

			for (int t = minN; t <= maxN; t += cu)
			{
				ind++;
				Quality(m, t, GF, CIRCLE);//������ ����������� ����������� �� ������, ����� ������� ������� �������� �����
				cout << "-------�������� " << tt - ind << endl;
			}
		}
	}
}

void Pictures_ill(int minN, int maxN, int cu)//�������� ����������� ��� minN-maxN ������� c ����� cu
{
	int t = int(MAXCIRCLE*KGF*((maxN - minN) / cu + 1)), ind = 0;

		for (CIRCLE = 1; CIRCLE <= MAXCIRCLE; CIRCLE++)
		{
			for (GF = 1; GF <= KGF; GF++)
			{
	for (int m = minN; m <= maxN; m += cu)
	{
		ind++;
		Desigion(m/*, GF, CIRCLE*/);//���������� ������� �� ����� (0) ��� ��� ������������� (>0), ������� � ����� �������
		Illustrating(fi, masPoints, MySLAU.x, myCurve, 1);// ������ ��������� ������� � �����������
		cout << "-------�������� " << t - ind << endl;
	}
			}
		}
}
