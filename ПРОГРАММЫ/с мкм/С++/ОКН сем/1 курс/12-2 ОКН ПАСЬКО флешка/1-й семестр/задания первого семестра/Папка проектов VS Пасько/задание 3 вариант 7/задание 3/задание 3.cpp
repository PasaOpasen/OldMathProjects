#include <fstream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	int b[10];
	int i=0,f,k=0;

	ifstream fin("����.txt");

	for(i=0;i<10;i++) fin>>b[i];
	i=0;
	while(b[i]>=0)i++;

	f=b[i];
	for(i=1;i<10;i++) {if((b[i]<0)&&(b[i]>f)) f=b[i];}

	ofstream fout("�����.txt"); 
	fout<<"�������� �������:   ";
	for(i=0;i<10;i++) fout<<b[i]<<"   ";
	fout<<endl;
	fout <<"���������� ������������� �������=   "<<f<<endl;

	fout.close(); 

return 0;
}
