#include <iostream>
using namespace std;

#define pi  3.14

enum Color
{
	Red = 0x000000FF,
	Green =  0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Orange = 0x0000A5FF,
	White = 0x00FFFFFF
};

class Shape
{
	Color color;
public:
	Shape(Color color) : color(color) {}
	virtual double get_area()const = 0;
	virtual double get_perimetr()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "Площадь фигуры: " << get_area() << endl;
		cout << "Периметр фигуры: " << get_perimetr() << endl;
		draw();
	}
};

class Square :public Shape
{
	double side;
public:
	Square(double side, Color color) :Shape(color)
	{
		set_side(side);
	}
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		this->side = side; 
	}
	double get_area()const override
	{
		return side * side;
	}
	double get_perimetr()const override
	{
		return 4 * side;
	}
	void draw()const override
	{
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина стороны квадрата: " << get_side() << endl;
		Shape::info();
	}
};

class Rectangle :public Shape
{
	double side_a;
	double side_b;
public:
	Rectangle(double side_a, double side_b, Color color) :Shape(color)
	{
		set_side_a(side_a);
		set_side_b(side_b);
	}
	double get_side_a()const
	{
		return side_a;
	}
	double get_side_b()const
	{
		return side_b;
	}
	void set_side_a(double side_a)
	{
		this->side_a = side_a; 
	}
	void set_side_b(double side_b)
	{
		this->side_b = side_b; 
	}
	double get_area()const override
	{
		return side_a * side_b;
	}
	double get_perimetr()const override
	{
		return 2 * (side_a + side_b);
	}
	void draw()const override
	{
		for (int i = 0; i < side_a; i++)
		{
			for (int j = 0; j < side_b; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
		cout << endl;
	}
	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина сторон прямоугольника: " << get_side_a() << "\t" << get_side_b() << endl;
		Shape::info();
	}
};

class Triangle :public Shape
{
	double side_a;
	double side_b;
	double side_c;
public:
	Triangle(double side_a, double side_b, double side_c, Color color) :Shape(color)
	{
		set_side_a(side_a);
		set_side_b(side_b);
		set_side_с(side_c);
	}
	double get_side_a()const
	{
		return side_a;
	}
	double get_side_b()const
	{
		return side_b;
	}
	double get_side_c()const
	{
		return side_c;
	}
	void set_side_a(double side_a)
	{
		this->side_a = side_a; 
	}
	void set_side_b(double side_b)
	{
		this->side_b = side_b; 
	}
	void set_side_с(double side_c)
	{
		this->side_c = side_c; 
	}
	double get_area()const override
	{
		return sqrt(get_perimetr()/2*(get_perimetr()/2 - side_a)*(get_perimetr()/2 - side_b)*(get_perimetr()/2 - side_c));
	}
	double get_perimetr()const override
	{
		return side_a + side_b + side_c;
	}
	void draw()const override
	{
		cout << "Здесь могла быть ваша реклама!" << endl;
	}
	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Длина сторон треугольника: " << get_side_a() << "\t" << get_side_b() << "\t" << get_side_c() << endl;
		Shape::info();
	}
};

class Circle :public Shape
{
	double radius;
public:
	Circle(double radius, Color color) :Shape(color)
	{
		set_radius(radius);
	}
	double get_radius()const
	{
		return radius;
	}
	void set_radius(double radius)
	{
		this->radius = radius;
	}
	double get_area()const override
	{
		return radius * radius * pi;
	}
	double get_perimetr()const override
	{
		return 2 * pi * radius;
	}
	void draw()const override
	{
		cout << "Здесь могла быть ваша реклама!" << endl;
	}
	void info()const override
	{
		cout << typeid(*this).name() << endl;
		cout << "Радиус окружности : " << get_radius() << endl;
		Shape::info();
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Square square(5, Color::Red);
	cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimetr() << endl;
	square.draw();
	cout << "\n-----------------------------------------\n" << endl;
	square.info();
	cout << "\n-----------------------------------------\n" << endl;
	Rectangle rectangle(5, 10, Color::Green);
	rectangle.info();
	cout << "\n-----------------------------------------\n" << endl;
	Triangle triangle(3, 4, 5, Color::Blue);
	triangle.info();
	cout << "\n-----------------------------------------\n" << endl;
	Circle circle(10, Color::Yellow);
	circle.info();
	cout << "\n-----------------------------------------\n" << endl;
}