#include <cstdlib>
#include <iostream>
//#include <conio.h>

using namespace std;

int   n;
char  *RUB;

void Vvod();
void Vyvod();

int main()
{
	Vvod();
	switch (n%100)
	{
	case 11 : case 12 : case 13 : case 14 : RUB="������"; break;
	default :
		switch (n%10)
		{
		case 0: case 5: case 6: case 7: case 8: case 9 : 
			RUB="������"; break;
		case 1 : 
			RUB="�����"; break;
		case 2 : case 3 : case 4 : 
			RUB="�����"; break;
		}
	}
	Vyvod();
}

//
//--------- ������� � ���������
//int   n;
//char  RUB[10];
//char  R1[10]="������",R2[10]="�����",R3[10]="�����";
//
//void Vvod();
//void Vyvod();
//
//int main()
//{
//    Vvod();
//    switch (n%100)
//    {
//           case 11 : case 12 : case 13 : case 14 : 
//                               for (int i=0;i<10; i++)
//                               RUB[i]=R1[i];
//                               break;
//           default :
//                   switch (n%10)
//                   {
//                          case 0: case 5: case 6: case 7: case 8: case 9 : 
//                               for (int i=0;i<10; i++)
//                               RUB[i]=R1[i];
//                               break;
//                          case 1 : 
//                               for (int i=0;i<10; i++)
//                               RUB[i]=R2[i];
//                               break;
//                          case 2 : case 3 : case 4 : 
//                               for (int i=0;i<10; i++)
//                               RUB[i]=R3[i];
//                               break;
//                   }
//    }
//    Vyvod();
//}


//
//----------	���� ������
//
void Vvod()
{
	char   pust[100];
	FILE *fp;							// ��������� �� ����
	fp=fopen("in.txt","r");				// ������� ���� ��� ������
									// ������ �� �����
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&n);
	fclose(fp);						// ������� ���� ��� ������
}
//
//----------	����� ������
//
void Vyvod()
{
	FILE *fp;
	fp=fopen("out.txt","w");		 	    	// ������� ���� ��� ������
									// ������ � ����
	fprintf(fp,"  N ������\n\n");
	fprintf(fp,"  �����: %10d %s",n,RUB);
	fclose(fp);	
}
