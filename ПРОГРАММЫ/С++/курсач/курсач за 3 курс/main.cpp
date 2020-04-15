//���������, ������� ������� ����������� ������� ������ ������� ��� ��������� �������
//������� ������ �. �.
//� ��������� ��� ��������� ��������������� 19.10.2017
//��� ����������� ���� � ������� ������� ��������� �� ��� ����� ������� ����� ����������� ����������
//��������� ��� �� ������

//set_locale

//����������� ��������� �������������
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
//����������� ������������ ���
using namespace std;



//��������� ����� �� ���������
struct basp {
	double x;//���������� ����� � ��������� ������������
	double y;
	//������� ��������� ���������� � ����� z, ��������������� �������� �������� �����
	double potfunc(basp z) {
		return log(1 / sqrt((z.x - x)*(z.x - x) + (z.y - y)*(z.y - y)));
	}
};
//���������� ����� �������
double eudistance(basp z, basp w) {
	return sqrt((z.x - w.x)*(z.x - w.x) + (z.y - w.y)*(z.y - w.y));
}
double fpow(int i, int j, basp z);



int M0 = 1000; //���������� ����� ��� ��������������

//����� ������� ������ 
class curve {
private:
	double a;//��������� �������� ���������
	double b;//�������� �������� ���������
	double(*u)(double);
	double(*v)(double);
	double h;//�������� ���� ��� ���� ������
	int M;
	void geth(int MM) {
		M = MM;
		h = (b - a) / M;//���������� ���� ����������� ��������
	}
	basp transfer(double t) {//������� ����� �� ������ �� �������� ���������
		basp point;
		point.x = u(t);
		point.y = v(t);
		return point;
	}

public:

	curve(double a0, double b0, double(*uu)(double), double(*vv)(double)) {//�����������
		a = a0; b = b0;
		u = uu; v = vv;
	}
	curve() {
		a = 0; b = 0;
	}

	double firstkind(double(*f)(basp)) {//���������� �������������� ��������� ������� ���� �� ���� ������ �� ������� f
		geth(M0);
		double value = 0;
		for (int k = 0; k <= M - 1; k++) value += f(transfer((a + (k + 1)*h + a + (k)*h) / 2))*eudistance(transfer(a + (k + 1)*h), transfer(a + (k)*h));
		return value;
	}

	double firstkind(int i, int j) {//���������� �������������� ��������� ������� ���� �� ���� ������ �� ������� fpow(int i,int j,basp z)
		geth(M0);
		double value = 0;
		for (int k = 0; k <= M - 1; k++) value += fpow(i, j, transfer((a + (k + 1)*h + a + (k)*h) / 2))*eudistance(transfer(a + (k + 1)*h), transfer(a + (k)*h));
		return value;
	}
};

//����� ���� � �������� �� �������
class syst {
private:
	int n;//����������� �������
public:
	double **a, *b, *x;//��������� �� ������� � �������

	void make(int k) {}//�������� ���������� � ���������� ������������ �������
		n = k;
		a = new double *[n];
		for (int i = 0; i < n; i++)
			a[i] = new double[n];
		b = new double[n];
		x = new double[n];
	}
	
	
	void Gauss(){
		
	}
	
	void Holets() {} //������� ��������� ��=b ������� ���������, ���������� ������� � �������� ������
	  //�������� ��������������� �������
		double **t = new double *[n];
		for (int i = 0; i < n; i++)
			t[i] = new double[n];

		//������ ��� ������
		t[0][0] = sqrt(a[0][0]);
		for (int j = 1; j < n; j++)t[0][j] = sqrt(a[0][j]) / t[0][0];

		for (int j = 1; j < n; j++) {
			double sum = 0;
			for (int k = 0; k <= j - 1; k++) sum += t[k][j] * t[k][j];
			t[j][j] = sqrt(a[j][j] - sum);
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (i < j) {
					double sum = 0;
					for (int k = 0; k <= i - 1; k++) sum += t[k][i] * t[k][j];
					t[i][j] = (a[i][j] - sum) / t[i][i];
				}
				else if (j < i) {
					t[i][j] = 0;
				}
			}

//
		double **c = new double *[n];
		for (int i = 0; i < n; i++)
			c[i] = new double[n];
		for (int i = 0; i < n; i++)for (int j = 0; j < n; j++) {
			double s = 0;
			for (int k = 0; k < n; k++)s += t[k][i] * t[k][j];
			c[i][j] = s;
		}

		cout << "������� c:" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << endl;
			for (int j = 0; j < n; j++)cout << c[i][j] << " ";
		}


		cout << "������� t:" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << endl;
			for (int j = 0; j < n; j++)cout << t[i][j] << " ";
		}

//

		//�������� ��� ������     
		double *y = new double[n];
		y[0] = b[0] / t[0][0];
		for (int i = 1; i < n; i++) {
			double sum = 0;
			for (int k = 0; k <= i - 1; k++) sum += t[k][i] * y[k];
			y[i] = (b[i] - sum) / t[i][i];
		}
		x[n - 1] = y[n - 1] / t[n - 1][n - 1];
		for (int i = n - 2; i > 0; i--)
		{
			double sum = 0;
			for (int k = i + 1; k < n; k++) sum += t[i][k] * x[k];
			x[i] = (y[i] - sum) / t[i][i];
		}
	}


};


//���������� ����������
basp *mas;//��������� �� ������ ����� ���������
curve mycurve;//������� �������, � ������� �������� ���. ���������
syst mysystem;//�������, ������� ������� ������
double(*fi)(basp);//��������� �� ��������� �������
int circle, gf, N;//����� �������, ��������� ������� � ���������� �������� �����

const int kgf = 2;//���������� ��������� ������� �� ���� ������





//��������� �������������� ��� �������
	//���� ������� 3
double u1(double t) {
	return 3 * cos(t);
}
double v1(double t) {
	return 3 * cos(t);
}
//�������������� ����������� �� �������� 2
double u2(double t) {
	if ((t >= 0) && (t <= 4))return t;
	if ((t >= 4) && (t <= 6))return 12 - 2 * t;
}
double v2(double t) {
	if ((t >= 0) && (t <= 2))return t*sqrt(3);
	if ((t >= 2) && (t <= 4))return -sqrt(3)*t + 4 * sqrt(3);
	if ((t >= 4) && (t <= 6))return 0;
}
//������� �� �������� 4
double u3(double t) {
	if ((t >= 0) && (t <= 4))return t;
	if ((t >= 4) && (t <= 8))return 4;
	if ((t >= 8) && (t <= 12))return 12 - t;
	if ((t >= 12) && (t <= 16))return 0;
}
double v3(double t) {
	if ((t >= 0) && (t <= 4))return 0;
	if ((t >= 4) && (t <= 8))return t - 4;
	if ((t >= 8) && (t <= 12))return 4;
	if ((t >= 12) && (t <= 16))return 16 - t;
}

//��������� ������� � ������ ��������� �������
double g11(basp point) {
	return cos(point.x)*cos(point.y);
}
double g12(basp point) {
	return sin(point.y);
}
double g21(basp point) {
	return point.x*point.x + 4;
}
double g22(basp point) {
	return pow(point.x, 5) + point.x*point.y*point.y;
}
double g31(basp point) {
	return log(abs(point.x*point.y) + 2 * point.x);
}
double g32(basp point) {
	return cos(2 * point.x) / cos(point.x*point.y); //�������� �������� ��-�� ������ �����
}
double(*gfunctions[3][kgf])(basp) = { g11,g12,g21,g22,g31,g32 };

//������� ������������ �������
double fpow(int i, int j, basp z) {
	if ((i == N) && (j == N)) return fi(z)*fi(z);
	if (i == N) return mas[j].potfunc(z)*fi(z);
	if (j == N) return mas[i].potfunc(z)*fi(z);
	return mas[i].potfunc(z)*mas[j].potfunc(z);
}

//������������ ���������� ��������������� �������
void building();
void read();
void screening();
bool comp(basp a, basp b);
void exceptionmas(basp *mas);
void excep(int i, basp *a);
void display();
void writeAerror();
void writeerror(double eps);
void matrixpower(double *Ax, double **a, double *x);
void error();
void search();


//�������� �������
int main()
{
	 setlocale( LC_ALL,"Russian" );
	
	building();//������ � ������ � �������
	search();//����� �������
	return 0;
}



void building()
{
	read();//������ ������ �� �����
	display();//������������� ������ ���� ������ �� ����� - ������� � ��������� �������
	screening();//���������� �� ������� ����� ���������� �����

   /*cout<<circle<<" "<<gf<<endl;
   for (int i = 0; i < N; i++) cout<<mas[i].x <<" "<< mas[i].y<<endl;*/
}

//��������������� ��� "������ ������ � ������ � �������"
void read()
{
	char buff[150];//�������� ���������������� ����������� �������
	int k = 0; //�������
	double r;//��������������� �������������� �����	
	ifstream fin("input.txt"); //���������� ������� ��� ������ �� �����
	fin >> buff;//������ �������� ��������� ����������
	fin >> circle;//������ ������ �������
	fin >> buff;
	fin >> gf;//������ ������ ��������� �������
	fin >> buff;

	while (fin >> r) k++;//���� ���������� ����� �����������, ���������� � �������� 
	N = k / 2;//���������� �������� ��������� �������� �����
	mas = new basp[N];//�������� ������� �����

	fin.clear();
	fin.seekg(0, ios::beg);//��������� ��������� �� ������ �����, ����� ������� �������� ������
	fin >> buff; fin >> circle; fin >> buff; fin >> gf; fin >> buff;
	for (int i = 0; i < N; i++) fin >> mas[i].x >> mas[i].y;//���������� ������� �����
	fin.close();
}

void screening()
{
	sort(mas, mas + N, comp);//���������� ����� �� �����������
	exceptionmas(mas);//���������� ������������� �����
}

bool comp(basp a, basp b)//������� �����������
{
	if (a.y < b.y)return true;//c�������� �� ������ ����������
	else if (a.y > b.y) return false;
	else return a.x < b.x;//���� ������ ���������� �����, ��������� �� ������ ����������
}

void exceptionmas(basp *mas)//���������� �� ������� ������������� ���������
{
	for (int i = 1; i < N; i++)
	{
		if (mas[i - 1].x == mas[i].x && mas[i - 1].y == mas[i].y) { excep(i, mas); N--; i--; }//�������� �� ������� ����� ������������� ���������
	}
}

void excep(int i, basp *a)//�������� �� ������� �������� i
{
	for (int j = i; j < N - 1; j++) a[j] = a[j + 1];
}

//��������� �� ������
void writeAerror()
{
	ofstream fout("output.txt");
	fout << "�������������� ����� ��������� ������� ��� �������" << endl;
	exit(0);
	fout.close();
}


void display() {}//������������� ������ ���� ������ �� ����� ������� � ��������� ������
	curve c1(0, 2 * 3.1415, u1, v1);
	curve c2(0, 6, u2, v2);
	curve c3(0, 16, u3, v3);

	switch (circle) {
	case 1:
		mycurve = c1;
		break;
	case 2:
		mycurve = c2;
		break;
	case 3:
		mycurve = c3;
		break;
	default:
		writeAerror();
	}

	if (gf > kgf)writeAerror();//���� ��������� ����� ������ ����� ��������� ������� �� ������
	else fi = gfunctions[circle - 1][gf - 1];//��������� ������� - ������� � ������� gf ��� ������ � ������� circle
}

//����� ��������
void writeerror(double *x, double eps) {
	ofstream fout("output.txt");

	fout << "������ �������:" << endl;
	for (int i = 0; i < N; i++) fout << x[i] << endl;
	fout << "������� ������������ ������� � ��������� �������� ��� ����� �������� ������� " << N << " ����� " << eps << endl;
	fout.close();
}

//���������� ������� Ax ������������ a*x ������� �� ������
void matrixpower(double *Ax, double **a, double *x) {
	for (int i = 0; i < N; i++) {
		double sum = 0;
		for (int j = 0; j < N; j++) sum += a[i][j] * x[j];
		Ax[i] = sum;
	}
}

//���������� � ����� �������� �� ���������� �������
void error() {

	double p = mycurve.firstkind(N, N), sum = 0;

	double *Ax = new double[N];
	matrixpower(Ax, mysystem.a, mysystem.x);

	for (int i = 0; i < N; i++) sum += mysystem.x[i] * Ax[i];//mycurve.firstkind(i,N);
	double eps = abs(p - sum);
	writeerror(mysystem.x, eps);
}

void search()
{
	mysystem.make(N);//������� ������� �������, ������� ������� �������� �����

			//��������� �������
	for (int i = 0; i < N; i++) {
		mysystem.b[i] = mycurve.firstkind(i, N);
		mysystem.a[i][i] = 2;//mycurve.firstkind(i,i);
		for (int j = i + 1; j < N; j++) {
			double tmp = i % 5 + j % 8;//mycurve.firstkind(i,j);
			mysystem.a[i][j] = tmp;
			mysystem.a[j][i] = tmp;
		}
	}



	cout << "������� ������� � ��������� ������: " << endl;
	for (int i = 0; i < N; i++)
	{
		cout << endl;
		for (int j = 0; j < N; j++)cout << mysystem.a[i][j] << " ";
	}
	cout << endl; cout << endl;
	for (int i = 0; i < N; i++) cout << mysystem.b[i] << endl; cout << endl;


	//������ �������
	//mysystem.Holets();
mysystem.Gauss();

	/*	double *Ax = new double[N];
		matrixpower(Ax, mysystem.a, mysystem.x);
		double s = 0;
		for (int i = 0; i < N; i++) s += sqrt((Ax[i] - mysystem.b[i])*(Ax[i] - mysystem.b[i]));
		cout << endl;
		cout << "������� = " << s << endl;cout << "������������ ������� ������� �� ��������� ������� " << endl;
		for (int i = 0; i < N; i++) cout << Ax[i] << endl; cout << endl;*/




		//������� �������, ����� � ������� �����������		
	error();
}

