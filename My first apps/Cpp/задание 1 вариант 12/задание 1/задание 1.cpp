
#include <fstream>
using namespace std;

void main()
{
   setlocale(LC_ALL, "rus");

	int x;

	ifstream fin("����.txt");
	fin>>x;

	ofstream fout("�����.txt"); 

	if(x%12==0){fout << x<<"/12="<<x/12<<"  ������� ������"<<endl;} 
	else fout <<" 8965193646 "<<endl;

		fout.close(); 


}
