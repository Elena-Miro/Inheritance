#pragma warning(disable:4326)
#include<Windows.h>
#include<iostream>
using namespace std;

enum class Color    //создаем тип данных color
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
		HWND hConsole = GetConsoleWindow();//получаем окно консоли, чтобы к нему м б обратиться
		HDC hdc = GetDC(hConsole);//создаем контекст устройства для полученного окна
		HPEN hPen = CreatePen(PS_SOLID,line_width, (COLORREF)color);//создаем карандаш,который будет рисовать контур
		//PSSOLID-сплошная линия 5 толщина линии 5 пкс,ргб()
		SelectObject(hdc, hPen);//выбираем созданный карандаш,чтоб им м б рисовать
		HBRUSH hBrush = CreateSolidBrush((COLORREF)color);//создаем кисть,кисть закрашивает замкнутые фигуры
		SelectObject(hdc, hBrush);//выбираем созданную кисть //кисть и карандаш выбираются для того, чтобы функция ректенгл понимала чем рисовать
		Rectangle(hdc, start_x, start_y, start_x+side, start_y+side);//рисует квадрат
		DeleteObject(hBrush);//удаляем созданную кисть и карандаш
		DeleteObject(hPen);

		ReleaseDC(hConsole, hdc);//освобождаем контекст устройства
	}
};
void main()
{
	setlocale(LC_ALL, "");
	Square square(100, Color::green,100,300,5);
	cout << "Сторона квадрата:\t" << square.get_side() << endl;
	cout << "Площадь квадрата:\t" << square.get_area() << endl;
	cout << "Периметр квдрата:\t" << square.get_perimeter() << endl;
	square.draw();
}