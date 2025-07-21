//Academy
#include <iostream>

using namespace std;

#define HUMAN_TAKE_PARAMETRS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETRS  last_name, first_name, age

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//Constructor
	Human(HUMAN_TAKE_PARAMETRS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//Methods
	void info()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
};

#define STUDENT_TAKE_PARAMETRS const std::string& spesiality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETRS spesiality,group, rating, attendance

class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality() const
	{
		return speciality;
	}
	const std::string& get_group() const
	{
		return speciality;
	}
	double get_rating() const
	{
		return rating;
	}
	double get_attendance() const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//Constructor
	Student(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS):Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(spesiality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SContructor:\t" << this << endl;
	}
	~Student()
	{		
		cout << "SDestructor:\t" << this << endl;
	}

	//Methods
	void info()const
	{
		Human::info();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
};

#define TEACHER_TAKE_PARAMETRS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETRS speciality, experience

class Teacher:public Human
{
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality() const
	{
		return speciality;
	}
	int get_expirience() const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_expirience(int experience)
	{
		this->experience = experience;
	}

	//Constructors
	Teacher( HUMAN_TAKE_PARAMETRS, TEACHER_TAKE_PARAMETRS ):Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_expirience(experience);
		cout << "TContructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//Methods
	void info()const
	{
		Human::info();
		cout << speciality << " " << experience << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");

	Human human("Montana", "Antonio", 25);
	human.info();
	
	Student student("Pincman", "Jessie", 22, "Chemistry", "WW_220", 95, 98);
	student.info();

	Teacher teacher("Pin", "Jes", 50, "Chemistry", 25);
	teacher.info();
}