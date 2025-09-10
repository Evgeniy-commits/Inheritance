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
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);

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
			cout << "ѕлощадь фигуры: " << get_area() << endl;
			cout << "ѕериметр фигуры: " << get_perimetr() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETRS) :Shape(SHAPE_GIVE_PARAMETRS)
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
			cout << "ƒлина стороны квадрата: " << get_side() << endl;
			Shape::info();
		}
	};*/

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
		/*double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}*/
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
			HWND hwnd = GetConsoleWindow();  //1) ѕолучаем окно консоли
			HDC hdc = GetDC(hwnd);			//2) ѕолучаем контекст устройства (DC - Device Context) дл€ окна консоли
											// DC - это то начем мы будем рисовать
			//3) —оздадим инструменты, которыми мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); // арандаш (Pen) рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);   // исть (Brush) рисует заливку фигуры
			
			//4)¬ыберем созданные инструменты:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) ѕосле того, как все необходимые инструменты созданы и выбраны, можно рисовать
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);

			//6) hdc, hPen, hBrush занимают ресурсы, а ресурсы нужно освобождать
			DeleteObject(hBrush);
			DeleteObject(hPen);
			
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "—тороны: " << width << " x " << height << endl;
			Shape::info();
		}
	};

	class Square : public Rectangle
	{
		double side;
	public:
		Square (double side, SHAPE_TAKE_PARAMETRS) : Rectangle(side, side, SHAPE_GIVE_PARAMETRS)
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
		Circle(double radius, SHAPE_TAKE_PARAMETRS): Shape(SHAPE_GIVE_PARAMETRS)
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
			HWND hwnd = GetConsoleWindow();  //1) ѕолучаем окно консоли
			HDC hdc = GetDC(hwnd);			//2) ѕолучаем контекст устройства (DC - Device Context) дл€ окна консоли
			// DC - это то начем мы будем рисовать
			//3) —оздадим инструменты, которыми мы будем рисовать
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); // арандаш (Pen) рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);   // исть (Brush) рисует заливку фигуры

			//4)¬ыберем созданные инструменты:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) ѕосле того, как все необходимые инструменты созданы и выбраны, можно рисовать
			::Ellipse(hdc, start_x, start_y, start_x + 2*radius, start_y + 2*radius);

			//6) hdc, hPen, hBrush занимают ресурсы, а ресурсы нужно освобождать
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}

	};
}

void main()
{
	setlocale(LC_ALL, "");
	Geometry::Square square(150, 100, 100, 1, Geometry::Color::Red);
	/*cout << "ƒлина стороны квадрата: " << square.get_side() << endl;
	cout << "ѕлощадь квадрата: " << square.get_area() << endl;
	cout << "ѕериметр квадрата: " << square.get_perimetr() << endl;
	square.draw();*/
	cout << "\n-----------------------------------------\n" << endl;
	square.info();
	cout << "\n-----------------------------------------\n" << endl;
	Geometry::Rectangle rectangle(150, 100, 500, 100, 5, Geometry::Color::Orange);
	rectangle.info();
	cout << "\n-----------------------------------------\n" << endl;
	Geometry::Circle circle(50, 800, 200, 1, Geometry::Color::Yellow);
	circle.info();
	while (true)
	{
		square.draw();
		rectangle.draw();
		circle.draw();
	}
}