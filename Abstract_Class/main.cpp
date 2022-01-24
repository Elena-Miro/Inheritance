#include<iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0;//чисто виртуальный метод именно этот метод делает класс абстрактным
};
class WaterVehicle :public Vehicle
{

};
class Yacht : public WaterVehicle
{
public:
	void move()
	{
		cout << "Яхта плывет под парусом" << endl;
	}
};
class Boat : public WaterVehicle
{
public:
	void move()
	{
		cout << "Катер плывет при помощи мотора" << endl;
	}
};
class AirVehicle:public Vehicle
{

};
class Airplane : public AirVehicle
{
public:
	void move()
	{
		cout << "Самолет летит с помошью тяги от двигателя" << endl;
	}
};
class Helicopter :public AirVehicle
{
public:
	void move()
	{
		cout << "Вертолет летит за счет движущихся лопастей" << endl;
	}
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

	Yacht PeriniNavi;
	PeriniNavi.move();

	Boat SeaRay;
	SeaRay.move();

	Airplane Boeing;
	Boeing.move();

	Helicopter Robinson;
	Robinson.move();
}