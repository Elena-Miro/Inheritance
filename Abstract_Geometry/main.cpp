#pragma warning(disable:4326)
#include<Windows.h>
#include<iostream>
using namespace std;

enum class Color    //������� ��� ������ color
{
	red=0x000000FF,
	green=0x0000FF00,
	blue=0x00FF0000,
	console_red=0xCC,
	console_green=0xAA,
	console_blue=0x99,
	console_default=0x07
};
class Shape
{
protected:
	unsigned int start_x;
	unsigned int start_y;
	unsigned int line_width;
	Color color;
public:
	void set_start_x(unsigned int start_x)
	{
		if (start_x > 300)start_x = 300;
		this->start_x = start_x;
	}
	void set_start_y(unsigned int start_y)
	{
		if (start_y > 300)start_y = 300;
		this->start_y = start_y;
	}
	void set_line_width(unsigned int line_width)
	{
		if (line_width > 20)line_width = 20;
		this->line_width = line_width;
	}
	Shape(Color color,unsigned int start_x,unsigned int start_y,unsigned int line_width):color(color)
	{
		set_start_x(start_x);
		set_start_y(start_y);
		set_line_width(line_width);
	}
	virtual ~Shape(){}
	virtual double get_area() const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;

};
class Square :public Shape
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		if (side <= 0)side = 10;
		this->side = side;
	}
	Square(double side, Color color,unsigned int start_x,unsigned int start_y,unsigned int line_width) 
		:Shape(color,start_x,start_y,line_width)
	{
		set_side(side);
	}
	~Square(){}

	double get_area()const
	{
		return side * side;
	}
	double get_perimeter()const
	{
		return side * 4;
	}
	void draw()const
	{
		/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)color);

		for (int i = 0; i < side; i++)
		{
			for (int i = 0; i < side; i++)
			{
				cout << "* ";
			}
			cout<< endl;
		}
		SetConsoleTextAttribute(hConsole, (WORD)Color::console_default);*/
		//H-Handle
		HWND hConsole = GetConsoleWindow();//�������� ���� �������, ����� � ���� � � ����������
		HDC hdc = GetDC(hConsole);//������� �������� ���������� ��� ����������� ����
		HPEN hPen = CreatePen(PS_SOLID,line_width, (COLORREF)color);//������� ��������,������� ����� �������� ������
		//PSSOLID-�������� ����� 5 ������� ����� 5 ���,���()
		SelectObject(hdc, hPen);//�������� ��������� ��������,���� �� � � ��������
		HBRUSH hBrush = CreateSolidBrush((COLORREF)color);//������� �����,����� ����������� ��������� ������
		SelectObject(hdc, hBrush);//�������� ��������� ����� //����� � �������� ���������� ��� ����, ����� ������� �������� �������� ��� ��������
		Rectangle(hdc, start_x, start_y, start_x+side, start_y+side);//������ �������
		DeleteObject(hBrush);//������� ��������� ����� � ��������
		DeleteObject(hPen);

		ReleaseDC(hConsole, hdc);//����������� �������� ����������
	}
};
void main()
{
	setlocale(LC_ALL, "");
	Square square(, Color::green,100,300,5);
	cout << "������� ��������:\t" << square.get_side() << endl;
	cout << "������� ��������:\t" << square.get_area() << endl;
	cout << "�������� �������:\t" << square.get_perimeter() << endl;
	square.draw();
}