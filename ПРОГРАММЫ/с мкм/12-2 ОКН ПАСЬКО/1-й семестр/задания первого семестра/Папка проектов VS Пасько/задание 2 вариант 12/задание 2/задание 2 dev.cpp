#include <fstream>
#include <cmath>
using namespace std;

void main()
{
	setlocale(LC_ALL, "rus");
	int n,i,times,timec,timef;
	clock_t timeBegin,timeEnd;
	double a[10], b[10];
	float sum=0,composition=0,function=0;

	ifstream fin("����.txt");
	fin>>n;
	for(i=0;i<10;i++) fin>>a[i];
	for(i=0;i<10;i++) fin>>b[i];

timeBegin=clock();
	for(i=0;i<n;i++)
	{
		sum+=a[i]+b[i];
	}
    timeEnd=clock();
    times=timeBegin-timeEnd;
    	
	timeBegin=clock();
		for(i=0;i<n;i++)
	{
		composition+=a[i]*b[i];}
		timeEnd=clock();
    timec=timeBegin-timeEnd;
		
		timeBegin=clock();
		for(i=0;i<n;i++)
	{
		function+=acos(a[i]*b[i]);}
timeEnd=clock();
    timen=timeBegin-timeEnd;
	
	ofstream fout("�����.txt"); 

	fout <<"����� ���� ="<<sum<<"�����="<<times<<endl;
	fout <<"����� ������������ ="<<composition<<"�����="<<timec<<endl;
	fout <<"����� ������� �� ������������ ="<<"�����="<<timef<<endl;

	fout.close(); 


}
