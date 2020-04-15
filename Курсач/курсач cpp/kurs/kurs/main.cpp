//���������, ������� �� ����������� ��������� ����� ������� ����� ��� ������, ��� ������������, ������������ ����� �������� ����� ��� ���������, �������� ���� ��� ����� ������� � ���������� ��������������; 
             //��������� ������������ �������, ���� ��� �������
//������� ������ �. �.
//� ��������� ��� ��������� ��������������� 30.04.2017
//��������� ����� ������� ������� search() � illustrating()
//��� ����������� ���� � ������� ������� ��������� �� ��� ����� ������� ����� ����������� ����������
//��������� �������� ��� ������������ � ��������� ������, ��������� �� ����������� (��?)


//��������� �������������
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "Graph.h"
//����������� ������������ ���
using namespace std;


struct Point {//���������� ����� �� ���������
	double x;//���� - ���������� �� �
	double y;
};

//���������� ����������
int m;//���������� �������� ��������� ����� ���������
int kt;//���������� �������� ��������� ��������� ����� ���������, �� ���� ��������� ����� ����� ���������� �������������
Point z1[3], z2[3]; //��� ��������� �������, � ������� ����� ������������� ������� ��������� ������������� 
Point *mas;//��������� �� ������ ����� ���������
double a0, b0, c0, d0;//������� ����
const double eps = 0.01;//�����������
const int nRis = 250;//���������� ����� (����� ��� ���������������)


//������������ ���������� ��������������� �������
void building();
void search();
void illustrating();
void read();
void screening();
double P(double a, double b, double c);
void write1();
void write2();
void exceptionmas(Point *mas);
void excep(int i, Point *a);
void Ris(Point *z, int i, int j);
double f(double x, Point *z, int i, int j);
double min3(double a, double b, double c);
double max3(double a, double b, double c);
double eudistance(Point a, Point b);
bool triangleanswer(Point mas1, Point mas2, Point mas3);
bool triangleanswer(Point *a, int k);
int compx(Point a, Point b);
int compy(Point a, Point b);




//�������� �������
int main()
{
	building();//������ � ������ � �������
	search();//����� �������

//��������� ���������
	return 0;
}



//���� ��������������� ������� ��� main (�������� �������)
void building()
{
	read();//������ ������ �� �����
	screening();//���������� �� ������� ����� ���������� �����

}
void search()
{
	Point* internalpoints = new Point[kt - 3];//������ "���������� �����", � ������� ��� ������� ������������ �������� ������������ ����� ������������ ���������� �����, ��� �� ����� ������ �� ��� ����� ���������� �����������, ��� ��� ����� ��������

	for (int t11 = 0; t11 < (kt - 2); t11++)//���� ������ ����� ������� ������������
	{
		for (int t12 = t11++; t12 < (kt - 1); t12++)
			for (int t13 = t12++; t13 < (kt); t13++)
			{
				double a, b, c;//���������� ������ ������������
				a = eudistance(mas[t11], mas[t12]);//���������� ����� ������� t11 � t12
				b = eudistance(mas[t13], mas[t12]);//���������� ����� ������� t13 � t12
				c = eudistance(mas[t11], mas[t13]);//���������� ����� ������� t11 � t13
				if (triangleanswer(mas[t11], mas[t12], mas[t13]))//��������, ���������� �� ����� �����������
				{
					z1[1] = mas[t11];
					z1[2] = mas[t12];
					z1[3] = mas[t13]; //�������� ����� �������� ������������ � ��� ������

					double p1, p2, p3;//���������� ���������� �� ��������� ������
					int k = -1; //������, ������ ���������� ��������� ����� ������ ������������
					for (int s = 0; s < kt; s++)
					{
						if (triangleanswer(mas[s], mas[t12], mas[t13]) && triangleanswer(mas[t11], mas[s], mas[t13]) && triangleanswer(mas[t11], mas[t12], mas[s]))//���� ����� �������� ������������ � ��������� ��� ���������� ������������
						{

							p1 = eudistance(mas[t11], mas[s]);//���������� ����� ������� t11 � s
							p2 = eudistance(mas[t12], mas[s]);//���������� ����� ������� t12 � s
							p3 = eudistance(mas[t13], mas[s]);//���������� ����� ������� t13 � s

							if (max3(p1, p2, p3) >= max3(a, b, c)) continue; //�������� ������������ �������
							if (P(a, p1, p2) + P(b, p2, p3) + P(c, p1, p3) > P(a, b, c)) continue;//�������� ������������ ������� (����������� �������� �)
							k++;//���� �� ����� ����������� ������������ �������, ������������� �������
							internalpoints[k] = mas[s];//�������� ��������� �����
						}
					}
					if (triangleanswer(internalpoints, k))//���� � ������� ���������� ����� ���������� ������, ���������� �����������
					{
						write1();//����� �����
						//������� � ���������������, ��� ������� �������	
						illustrating();//��������������� �������
						return;//����������� ������ ��������� (���������� ������� ������)
					}

				}
			}
	}
	write2();//����, ����� �� ����� �������, ��������� �� ����� �������, ���������� � ���, ��� ������� �� ����������
	exit(0);//...� ��������� ���������� ������
}


//���� ��������������� ������� ���������� �������

   //��������������� ��� "������ ������ � ������ � �������"
void read()
{
	char buff[50];//�������� ���������������� ����������� �������
	int k = 0; //�������
	ifstream fin("input.txt"); //���������� ������� ��� ������ �� �����
	fin >> buff;//������ �������� ��������� ����������
	while (fin >> m) k++;//���� ���������� ����� �����������, ���������� � �������� 
	m = k / 2;//���������� �������� ���������
	if (m < 6) { ofstream fout("output.txt"); fout << "����� ������� ����"; fout.close(); exit(0); }//������� �� �������� ���������
	mas = new Point[m];//�������� ������� �����

	ifstream file("input.txt");//��������� ��������� �� ������ �����, ����� ������� �������� ������
	fin >> buff;
	for (int i = 0; i < m; i++) fin >> mas[i].x >> mas[i].y;//���������� ������� �����
	fin.close();
}
void screening()
{
	sort(mas, mas + m, compx);//���������� ����� �� ����������� (�� ������ ����������)
	int i = 0;
	for (int j = 1; j < m; j++)
	{
		if (mas[j - 1].x != mas[j].x)//���� �������� �������� ����� ������ ���������� �� �
		{
			sort(mas + i, mas + j - 1, compy);//����������� �������, ��� ��������� ���������� �� �, �� ������ ����������
			i = j;
		}
	}
	exceptionmas(mas);//���������� ������������� �����

	if (kt < 6) { ofstream fout("output.txt"); fout << "������ ����� ������� ����"; fout.close(); exit(0); }//������� �� �������� ���������
}

  //��������������� ��� "������"
double P(double a, double b, double c)
{
	double p, s;
	p = (a + b + c) / 2;//������������
	s = sqrt(p*(p - a)*(p - b)*(p - c));//�������
	return s;
}

void write1()
{
	ofstream fout("output.txt");
	fout << "������� ������� ������������" << endl;
	for (int i = 0; i < 3; i++)fout << z1[i].x << " " << z1[i].y << endl;
	fout << "������� ������� ������������" << endl;
	for (int i = 0; i < 3; i++)fout << z2[i].x << " " << z2[i].y << endl;
	fout.close();
}

void write2()
{
	ofstream fout("output.txt"); fout << "����� �� �������"; fout.close();
}


int compx(Point a, Point b)//������� ����������� ��� ������ ����������
{
	return a.x < b.x;//��������� �� ������ ����������
}

int compy(Point a, Point b)//������� ����������� ��� ������ ����������
{
	return a.y < b.y;//��������� �� ������ ����������
}

void exceptionmas(Point *mas)//���������� �� ������� ������������� ���������
{
	kt = m;
	for (int i = 1; i < kt; i++)
	{
		if (mas[i - 1].x == mas[i].x && mas[i - 1].y == mas[i].y) { excep(i, mas); kt--; i--; }//�������� �� ������� ����� ������������� ���������
	}
}

void excep(int i, Point *a)//�������� �� ������� �������� i
{
	for (int j = i; j < kt - 1; j++) a[j] = a[j++];
}  
double min3(double a, double b, double c)//������� �� ������ ���������
{
	return min(min(a, b), c);
}

double max3(double a, double b, double c)//�������� �� ������ ���������
{
	return max(max(a, b), c);
}

double eudistance(Point a, Point b)//���������� ����� �������
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

bool triangleanswer(Point mas1, Point mas2, Point mas3)
{
	double a, b, c;//���������� ������ ������������
	a = eudistance(mas1, mas2);//���������� ����� ������� mas1 � mas2
	b = eudistance(mas3, mas2);//���������� ����� ������� mas3 � mas2
	c = eudistance(mas1, mas3);//���������� ����� ������� mas1 � mas3

	if ((a + b < c) && (a + c < b) && (c + b < a))//�������� ���������� ������������
		return true;
	else return false;
}

bool triangleanswer(Point *a, int k)
{
	for (int t1 = 0; t1 < (k + 1 - 2); t1++)//���� ������ ����� ������������
		for (int t2 = t1++; t2 < (k + 1 - 1); t2++)
			for (int t3 = t2++; t3 < k + 1; t3++)
			{
				if (triangleanswer(a[t1], a[t2], a[t3]))//���� ����� ���������� �����������, �� ��� ����� ������������ � ������ ����� ����������� ������������
				{
					z2[1] = a[t1];
					z2[2] = a[t2];
					z2[3] = a[t3];
					return true;
				}
				else return false;
			}
}  

  //���������������
void illustrating()
{
	//������������� �������� ����
	a0 = -10 + min3(z1[1].x, z1[2].x, z1[3].x);
	b0 = 20 + max3(z1[1].x, z1[2].x, z1[3].x);
	c0 = -10 + min3(z1[1].y, z1[2].y, z1[3].y);
	d0 = 20 + max3(z1[1].y, z1[2].y, z1[3].y);


	SetColor(250, 250, 250);	// ������ ������� ���� ���� (�����)
	SetWindow(a0, b0, c0, d0);	// ������ ���� (������� ������� R,G,B)
	// � ��������� [a,b]x[c,d]
	SetColor(0, 0, 0);	// ������ ���� ������������ ���� (������)
	xyLine(a0, 0, 1, 1);	// ������ ���, �������������� � �. (a,0)
	// � ����� ������� �� � ������ 1
	// � 1 �� �

	// ������ ������
	Ris(z1, 1, 2); //������� ����� ������ � ������ �������� ������� ������������
	Ris(z1, 3, 2);//������� ����� ������� � ������ �������� ������� ������������
	Ris(z1, 1, 3);//������� ����� ������ � ������� �������� ������� ������������
	Ris(z2, 1, 2);
	Ris(z2, 3, 2);
	Ris(z2, 1, 3);//������� ����� ������ � ������� �������� ������� ������������

	CloseWindow();// ��������� ���� (������� bmp-����)

}

void Ris(Point *z, int i, int j)//����������� ������� ����� ������� zi � zj
{
	SetColor(0, 255, 0); // ������ ���� �����
	double step = (b0 - a0) / nRis;
	double x = b0;
	SetPoint(x, f(x, z, i, j)); // ������������� ������
	for (int i = 0; i < nRis; i++)
	{
		x -= step;
		Line2(x, f(x, z, i, j));// ������ �������,����������� ������ � ������ (�,�), � ���������� ������ � ��� �����	
		if (f(x, z, i, j) <= c0 + eps) break;
	}
}

double f(double x, Point *z, int i, int j)//������ ����� ������� zi � zj
{
	if ((z[j].x - z[i].x) == 0) return 0;
	else return (x*(z[j].y - z[i].y) - z[i].x*z[j].y + z[j].x*z[i].y) / (z[j].x - z[i].x);
}


