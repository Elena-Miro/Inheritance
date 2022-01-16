#include<iostream>
#include<fstream>
using namespace std;
//#define WRITE_TO_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello world!" << endl;
	ofstream fout("file.txt", ios::app);
	fout << "Hello World" << endl;
	fout.close();
	system("notepad file.txt");
#endif // WRITE_TO_FILE

	const int SIZE = 10240;
	char buffer[SIZE]{};

	ifstream fin;//Создаем поток
	fin.open("file.txt");//Открыть файл
	if (fin.is_open())
	{
		while (!fin.eof())//пока не конец файла (end of file) читаем его

		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
	}
	else
	{
		cerr << "Error:file not found" << endl;
	}

	fin.close();//Закрыть файл
}