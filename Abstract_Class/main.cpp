#include<iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0;//чисто виртуальный метод именно этот метод делает класс абстрактным
};
class GroundVehicle:public Vehicle
{


};

class Car :public GroundVehicle
{
public:
	void move()
	{
		cout << "Машина едет на 4 колесах" << endl;
	}
};
class Bike :public GroundVehicle
{
public:
	void move()
	{
		cout << "Мотоцикл едет на 2 колесах" << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "");
	//Vehicle v;
	Car bmw;
	bmw.move();
}