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
		cout << "������ ���� �� ����� �� �������" << endl;
	}
};

class Bicycle :public GroundVehicle
{
public:
	void move() override
	{
		cout << "��� ������������ �������� ���������� � �������� ���������� �����" << endl;
	}
};

class Helicopter :public AirVehicle
{
public:
	void move() override
	{
		cout << "������������ �� ������" << endl;
	}
	void top_up() override
	{
		cout << "�������� � ����� �� ������ �������" << endl;
	}
	void landing() override
	{
		cout << "������������ �� ����� ������ �����������" << endl;
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