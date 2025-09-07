#include <iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0;
};

class GroundVehicle :public Vehicle{};
class AirVehicle :public Vehicle
{
	int altitude;
public:
	virtual void top_up() = 0;
	virtual void landing() = 0;
};

class Car : public GroundVehicle
{
public:
	void move() override 
	{
		cout << "ћашина едет по земле на колесах" << endl;
	}
};

class Bicycle :public GroundVehicle
{
public:
	void move() override
	{
		cout << "Ёто транспортное средство приводитс€ в движение мускульной силой" << endl;
	}
};

class Helicopter :public AirVehicle
{
public:
	void move() override
	{
		cout << "ѕеремещаетс€ на винтах" << endl;
	}
	void top_up() override
	{
		cout << "¬злетает с места не требу€ разгона" << endl;
	}
	void landing() override
	{
		cout << "ѕриземл€етс€ на любую ровную поверхность" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "Abstract Base Class" << endl;
	//Vehicle vehicle;
	Car bmw;
	bmw.move();

	Bicycle bike;
	bike.move();

	//AirVehicle av;
	Helicopter black_hawk;
	black_hawk.top_up();
	black_hawk.move();
	black_hawk.landing();

}