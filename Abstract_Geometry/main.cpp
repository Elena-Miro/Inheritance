﻿#define _USE_MATH_DEFINES
#pragma warning(disable:4326)
#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;
namespace Geometry
{

	enum class Color    //создаем тип данных color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		console_red = 0xCC,
		console_green = 0xAA,
		console_blue = 0x99,
		console_default = 0x07
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
		Shape(Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}
		virtual double get_area() const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info() const
		{
			cout << "Площадь:\t" << get_area() << endl;
			cout << "Периметр:\t" << get_perimeter() << endl;
			draw();
		}
		
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
		Square(double side, Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_side(side);
		}
		~Square() {}

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
			HPEN hPen = CreatePen(PS_SOLID, line_width, (COLORREF)color);//создаем карандаш,который будет рисовать контур
			//PSSOLID-сплошная линия 5 толщина линии 5 пкс,ргб()
			SelectObject(hdc, hPen);//выбираем созданный карандаш,чтоб им м б рисовать
			HBRUSH hBrush = CreateSolidBrush((COLORREF)color);//создаем кисть,кисть закрашивает замкнутые фигуры
			SelectObject(hdc, hBrush);//выбираем созданную кисть //кисть и карандаш выбираются для того, чтобы функция ректенгл понимала чем рисовать
			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);//рисует квадрат
			DeleteObject(hBrush);//удаляем созданную кисть и карандаш
			DeleteObject(hPen);

			ReleaseDC(hConsole, hdc);//освобождаем контекст устройства

		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны:" << side << endl;
			Shape::info();
		}
	};
	class Rectangle :public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 20;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 10;
			this->length = length;
		}
		Rectangle
		(
			double width, double length,
			Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width
		) :Shape(color, start_x, start_y, line_width)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double get_area()const
		{
			return width * length;
		}
		double get_perimeter()const
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow();//получаем окно консоли, чтобы к нему м б обратиться
			HDC hdc = GetDC(hConsole);//создаем контекст устройства для полученного окна
			HPEN hPen = CreatePen(PS_SOLID, line_width, (COLORREF)color);//создаем карандаш,который будет рисовать контур
			//PSSOLID-сплошная линия 5 толщина линии 5 пкс,ргб()
			SelectObject(hdc, hPen);//выбираем созданный карандаш,чтоб им м б рисовать
			HBRUSH hBrush = CreateSolidBrush((COLORREF)color);//создаем кисть,кисть закрашивает замкнутые фигуры
			SelectObject(hdc, hBrush);//выбираем созданную кисть //кисть и карандаш выбираются для того, чтобы функция ректенгл понимала чем рисовать
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);//рисует квадрат
			DeleteObject(hBrush);//удаляем созданную кисть и карандаш
			DeleteObject(hPen);

			ReleaseDC(hConsole, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина:\t" << width << endl;
			cout << "Длина:\t" << length << endl;
			Shape::info();
		}
	};
	class Circle:public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0)radius = 10;
			this->radius = radius;
		}
		Circle
		(double radius,
			Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) :
			Shape(color, start_x, start_y, line_width)
		{
			set_radius(radius);
		}
		~Circle(){}
		double get_area()const
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const
		{
			return 2 * M_PI * radius;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow();//получаем окно консоли, чтобы к нему м б обратиться
			HDC hdc = GetDC(hConsole);//создаем контекст устройства для полученного окна
			HPEN hPen = CreatePen(PS_SOLID, line_width, (COLORREF)color);//создаем карандаш,который будет рисовать контур
			//PSSOLID-сплошная линия 5 толщина линии 5 пкс,ргб()
			SelectObject(hdc, hPen);//выбираем созданный карандаш,чтоб им м б рисовать
			HBRUSH hBrush = CreateSolidBrush((COLORREF)color);//создаем кисть,кисть закрашивает замкнутые фигуры
			SelectObject(hdc, hBrush);//выбираем созданную кисть //кисть и карандаш выбираются для того, чтобы функция ректенгл понимала чем рисовать
			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());//рисует квадрат
			DeleteObject(hBrush);//удаляем созданную кисть и карандаш
			DeleteObject(hPen);

			ReleaseDC(hConsole, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус:\t" << radius<<endl;
			Shape::info();
		}
	};
	//class Triangle:public Shape
	//{
	//	double a;
	//	double b;
	//	double c;
	//	
	//	
	//public:
	//	double get_a() const
	//	{
	//		return a;
	//	}
	//	double get_b()const
	//	{
	//		return b;
	//	}
	//	double get_c()const
	//	{
	//		return c;
	//	}
	//	void set_a(double a)
	//	{
	//		if (a <= 0)a = 5;
	//		this->a = a;
	//	}
	//	void set_b(double b)
	//	{
	//		if (b <= 0)b = 5;
	//		this->b = b;
	//	}
	//	void set_c(double c)
	//	{
	//		if (c <= 0)c = 5;
	//		this->c = c;
	//	}
	//	Triangle(double a, double b, double c,
	//		Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) :
	//		Shape(color, start_x, start_y, line_width)
	//	{
	//		set_a(a);
	//		set_b(b);
	//		set_c(c);
	//		
	//	}
	//	~Triangle(){}
	//	double get_perimeter()const
	//	{
	//		return a + b + c;
	//	}
	//	double get_area()const
	//	{
	//		return sqrt(((a + b + c) / 2) * (((a + b + c) / 2) - a) * (((a + b + c) / 2) - b) * (((a + b + c) / 2) - c));
	//	}
	//	void draw()const
	//	{
	//		HWND hConsole = GetConsoleWindow();//получаем окно консоли, чтобы к нему м б обратиться
	//		HDC hdc = GetDC(hConsole);//создаем контекст устройства для полученного окна
	//		HPEN hPen = CreatePen(PS_SOLID, line_width, (COLORREF)color);//создаем карандаш,который будет рисовать контур
	//		//PSSOLID-сплошная линия 5 толщина линии 5 пкс,ргб()
	//		SelectObject(hdc, hPen);//выбираем созданный карандаш,чтоб им м б рисовать
	//		HBRUSH hBrush = CreateSolidBrush((COLORREF)color);//создаем кисть,кисть закрашивает замкнутые фигуры
	//		SelectObject(hdc, hBrush);//выбираем созданную кисть //кисть и карандаш выбираются для того, чтобы функция ректенгл понимала чем рисовать
	//		::Polygon(hdc,, 3);//рисует квадрат
	//		DeleteObject(hBrush);//удаляем созданную кисть и карандаш
	//		DeleteObject(hPen);
	//		ReleaseDC(hConsole, hdc);
	//	}
	//	void Move(double start_x, double start_y):Shape()
	//	{
	//		Shape a.Move(start_x, start_y);
	//	}
	//};

	class Triangle :public Shape
	{
	public:
		virtual double get_height()const = 0;
		Triangle(Color color, unsigned int start_x, unsigned int start_y, unsigned	int line_width) 
			:Shape(color, start_x, start_y, line_width) {}
		~Triangle() {}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
		double height;
	public:
		Geometry::EquilateralTriangle(double side, Color color, unsigned int start_x, unsigned int start_y, unsigned	int line_width)
			:Triangle(color, start_x, start_y, line_width)
		{
			set_side(side);
		}
		double get_side()
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		~EquilateralTriangle() {};
		double get_perimeter()const
		{
			return side * 3;
		}
		double get_height() const
		{
			return sqrt(side * side - side * side / 4);
		}
		double get_area()const
		{
			return (sqrt(3) *( side*side)/4);
		}
		
		void draw()const
		{
			
			
			
			HWND hConsole = GetConsoleWindow();//получаем окно консоли, чтобы к нему м б обратиться
			HDC hdc = GetDC(hConsole);//создаем контекст устройства для полученного окна
			HPEN hPen = CreatePen(PS_SOLID, line_width, (COLORREF)color);//создаем карандаш,который будет рисовать контур
			//PSSOLID-сплошная линия 5 толщина линии 5 пкс,ргб()
			SelectObject(hdc, hPen);//выбираем созданный карандаш,чтоб им м б рисовать
			HBRUSH hBrush = CreateSolidBrush((COLORREF)color);//создаем кисть,кисть закрашивает замкнутые фигуры
			SelectObject(hdc, hBrush);//выбираем созданную кисть //кисть и карандаш выбираются для того, чтобы функция ректенгл понимала чем рисовать
			const POINT point[] = {
				{start_x,start_y + side},
				{start_x + side,start_y + side},
				{start_x + side / 2,start_y+side-get_height() }
			};
			::Polygon(hdc,point, 3);//рисует треугольник
			DeleteObject(hBrush);//удаляем созданную кисть и карандаш
			DeleteObject(hPen);

			ReleaseDC(hConsole, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны:" << side << endl;
			Shape::info();
		}
	};
}
void main()
{
	setlocale(LC_ALL, "");
	//Geometry::Square square(100,Geometry:: Color::green,0,300,5);
	/*cout << "Сторона квадрата:\t" << square.get_side() << endl;
	cout << "Площадь квадрата:\t" << square.get_area() << endl;
	cout << "Периметр квдрата:\t" << square.get_perimeter() << endl;
	square.draw();*/
	//square.info();

	//Geometry::Rectangle rect(100, 50, Geometry::Color::red, 110, 400, 5);
	//rect.info();

	//Geometry::Circle circle(30, Geometry::Color::blue, 500, 50, 5);
	//circle.info();

	Geometry::EquilateralTriangle EquilateralTriangle(100, Geometry::Color::blue, 0, 500, 5);
	EquilateralTriangle.info();
	

	



}