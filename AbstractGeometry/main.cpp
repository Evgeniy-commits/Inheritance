#define _USE_MATH_DEFINES
#include <iostream>
#include <Windows.h>

using namespace std;

//#define pi	3.14

namespace Geometry
{
	enum Color
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Orange = 0x0000A5FF,
		White = 0x00FFFFFF
	};

#define SHAPE_TAKE_PARAMETRS   int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETRS   start_x, start_y, line_width, color

	class Shape
	{
	protected:
		HDC hdc;
		HPEN hPen;
		HBRUSH hBrush;
		Color color;
		int start_x;
		int start_y;
		int line_width;
	public:
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 16;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 768;

		Shape(SHAPE_TAKE_PARAMETRS) : color(color)
		{
			hdc = GetDC(GetConsoleWindow());
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
			hPen = CreatePen(PS_SOLID, line_width, color);
			hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
		}
		~Shape()
		{
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(GetConsoleWindow(), hdc);
		}
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x > MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		int filter_size(int size) const
		{
			return size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		int get_start_x() const
		{
			return start_x;
		}
		int get_start_y() const
		{
			return start_y;
		}
		int get_line_width() const
		{
			return line_width;
		}
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
	
	class Rectangle : public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETRS) :Shape(SHAPE_GIVE_PARAMETRS)
		{
			set_width(width);
			set_height(height);
		}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		double get_area()const override
		{
			return width * height;
		}
		double get_perimetr()const override
		{
			return 2 * (width + height);
		}
		void draw()const override
		{
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Стороны: " << width << " x " << height << endl;
			Shape::info();
		}
	};

	class Square : public Rectangle
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETRS) : Rectangle(side, side, SHAPE_GIVE_PARAMETRS)
		{
			set_side(side);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side() const
		{
			return side;
		}

	};

	class Circle : public Shape
	{
		double radius;
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETRS) : Shape(SHAPE_GIVE_PARAMETRS)
		{
			set_radius(radius);
		}
		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		double get_radius() const
		{
			return radius;
		}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimetr()const override
		{
			return 2 * M_PI * radius;
		}
		void draw()const override
		{
			::Ellipse(hdc, start_x, start_y, start_x + 2 * radius, start_y + 2 * radius);
		}

	};

	class Triangle : public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETRS) : Shape(SHAPE_GIVE_PARAMETRS) {}
		virtual double get_height()const = 0;
	};

	class EquilateralTriangle : public Triangle
	{
		//равносторонний
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETRS) : Triangle(SHAPE_GIVE_PARAMETRS)
		{
			set_side(side);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side() const
		{
			return side;
		}
		double get_height() const override
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const override
		{
			return side * get_height() / 2;
		}
		double get_perimetr()const override
		{
			return 3 * side;
		}
		void draw()const override
		{

			const POINT vertices[] =
			{
				{start_x, start_y + get_height()},
				{start_x + side, start_y + get_height()},
				{start_x + side / 2, start_y}
			};
			::Polygon(hdc, vertices, 3);
		}
	};
	class RectangularTriangle : public Triangle
	{
		double side;
		double height;
	public:
		RectangularTriangle(double side, double height, SHAPE_TAKE_PARAMETRS) : Triangle(SHAPE_GIVE_PARAMETRS)
		{
			set_side(side);
			set_height(height);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		double get_side() const
		{
			return side;
		}
		double get_height() const override
		{
			return height;
		}
		double get_area()const override
		{
			return side * get_height() / 2;
		}
		double get_perimetr()const override
		{
			return side + height + sqrt(pow(side, 2) + pow(height, 2));
		}
		void draw()const override
		{

			const POINT vertices[] =
			{
				{start_x, start_y + get_height()},
				{start_x + side, start_y + get_height()},
				{start_x, start_y}
			};
			::Polygon(hdc, vertices, 3);
		}
	};
	class DefaultTriangle : public Triangle
	{
		double side_a;
		double side_b;
		double side_c;
	public:
		DefaultTriangle(double side_a,double side_b,double side_c,  SHAPE_TAKE_PARAMETRS) : Triangle(SHAPE_GIVE_PARAMETRS)
		{
			set_side_a(side_a);
			set_side_b(side_b);
			set_side_c(side_c);
			
		}
		void set_side_a(double side_a)
		{
			this->side_a = filter_size(side_a);
		}
		void set_side_b(double side_b)
		{
			this->side_b = filter_size(side_b);
		}
		void set_side_c(double side_c)
		{
			this->side_c = filter_size(side_c);
		}
		double get_side_a() const
		{
			return side_a;
		}
		double get_side_b() const
		{
			return side_b;
		}
		double get_side_c() const
		{
			return side_c;
		}
		double get_height() const override
		{
			return 2 * get_area() / side_a;
		}
		double get_area()const override
		{
			return sqrt(get_perimetr()/2 * (get_perimetr()/2 - side_a)*(get_perimetr()/2 - side_b)*(get_perimetr()/2 - side_c));
		}
		double get_perimetr()const override
		{
			return side_a + side_b + side_c;
		}
		void draw()const override
		{

			const POINT vertices[] =
			{
				{start_x, start_y + get_height()},
				{start_x + side_a, start_y + get_height()},
				{start_x + sqrt(pow(side_c, 2) - pow(get_height(), 2)), start_y}
			};
			::Polygon(hdc, vertices, 3);
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	Geometry::Square square(150, 100, 100, 1, Geometry::Color::Red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimetr() << endl;
	square.draw();*/
	cout << "\n-----------------------------------------\n" << endl;
	square.info();
	cout << "\n-----------------------------------------\n" << endl;
	Geometry::Rectangle rectangle(150, 100, 500, 100, 5, Geometry::Color::Orange);
	rectangle.info();
	cout << "\n-----------------------------------------\n" << endl;
	Geometry::Circle circle(50, 800, 200, 1, Geometry::Color::Yellow);
	circle.info();
	cout << "\n-----------------------------------------\n" << endl;
	Geometry::EquilateralTriangle e_triangle(100, 550, 350, 16, Geometry::Color::Green);
	e_triangle.info();
	cout << "\n-----------------------------------------\n" << endl;
	Geometry::RectangularTriangle recttriangle(100, 150, 300, 300, 16, Geometry::Color::Blue);
	recttriangle.info();
	cout << "\n-----------------------------------------\n" << endl;
	Geometry::DefaultTriangle deftriangle(120, 105, 50, 400, 350, 16, Geometry::Color::White);
	deftriangle.info();
	cout << "\n-----------------------------------------\n" << endl;
	while (true)
	{
		square.draw();
		rectangle.draw();
		circle.draw();
		e_triangle.draw();
		recttriangle.draw();
		deftriangle.draw();
	}
}