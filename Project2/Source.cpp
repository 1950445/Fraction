#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
//#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello Files"<<endl << endl;
	//1) ������� �����:
	std::ofstream fout;
	//2) ��������� �����:
	fout.open("File.txt",std::ios_base::app);
	//3) ����� � �����:
	fout << "Hello Files" << endl;
	fout << "�� ������" << endl;
	//4) ��������� �����:
	fout.close();

	system("strat notepad File.txt");
#endif //WRITE_TO_FILE
#ifdef READ_FROM_FILE
	//1) ������� �����
	std::ifstream fin;
	//2) ��������� �����
	fin.open("File.txt");
	//3) ���������, �������� �� �����
	while (!fin.eof())
	{
		
		const int SIZE = 10240;
		char sz_buffer[SIZE] = {};
		//fin >> sz_buffer;
		fin.getline(sz_biffer,SIZE)
		cout << sz_buffer << endl;
	}
	fin.close();
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif //READ_FROM_FILE


}