//Academy
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define delimiter "\n---------------------------------------\n"

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
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//Methods
	virtual std::ostream& info(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}

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
	Student(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS) :Human(HUMAN_GIVE_PARAMETRS)
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
	std::ostream& info(std::ostream& os)const override
	{
		return Human::info(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
	}
};

#define GRADUATE_TAKE_PARAMETRS const std::string& topic_of_graduation_project, int practice_mark, int final_exam_mark, int graduation_mark
#define GRADUATE_GIVE_PARAMETRS topic_of_graduation_project, practice_mark, final_exam_mark, graduation_mark

class Graduate :public Student
{
	std::string topic_of_graduation_project;
	int practice_mark;
	int final_exam_mark;
	int graduation_mark;
public:
	const std::string& get_topic_of_graduation_project() const
	{
		return topic_of_graduation_project;
	}
	int get_practice_mark() const
	{
		return practice_mark;
	}
	int get_final_exam_mark() const
	{
		return final_exam_mark;
	}
	int get_graduation_mark() const
	{
		return graduation_mark;
	}
	void set_topic_of_graduation_project(const std::string& topic_of_graduation_project)
	{
		this->topic_of_graduation_project = topic_of_graduation_project;
	}
	void set_practice_mark(int practice_mark)
	{
		this->practice_mark = practice_mark;
	}
	void set_final_exam_mark(int final_exam_mark)
	{
		this->final_exam_mark = final_exam_mark;
	}
	void set_graduation_mark(int graduation_mark)
	{
		this->graduation_mark = graduation_mark;
	}

	//Constructor
	Graduate(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS, GRADUATE_TAKE_PARAMETRS) :Student(HUMAN_GIVE_PARAMETRS, STUDENT_GIVE_PARAMETRS)
	{
		set_topic_of_graduation_project(topic_of_graduation_project);
		set_practice_mark(practice_mark);
		set_final_exam_mark(final_exam_mark);
		set_graduation_mark(graduation_mark);
		cout << "GContructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//Methods
	std::ostream& info(std::ostream& os)const override
	{
		return Student::info(os) << "\n"
			<< "Тема дипломного проекта: " << topic_of_graduation_project << "\n"
			<< "Оценка за практику: " << practice_mark << "\n"
			<< "Оценка за гос. экзамен: " << final_exam_mark << "\n"
			<< "Оценка за дипломный проект: " << graduation_mark;
	}
};


#define TEACHER_TAKE_PARAMETRS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETRS speciality, experience

class Teacher :public Human
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
	Teacher(HUMAN_TAKE_PARAMETRS, TEACHER_TAKE_PARAMETRS) :Human(HUMAN_GIVE_PARAMETRS)
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
	std::ostream& info(std::ostream& os) const override
	{
		return Human::info(os) << speciality << " " << experience;
	}
};

//#define INHERITANCE
#define POLYMORPHISM

void main()
{
	setlocale(LC_ALL, "");

#ifdef INHERITANCE
	//Human human("Montana", "Antonio", 25);
//human.info();
//
//Student student("Pincman", "Jessie", 22, "Chemistry", "WW_220", 95, 98);
//student.info();

//Teacher teacher("Pin", "Jes", 50, "Chemistry", 25);
//teacher.info();

	Graduate graduate("Sara", "Coner", 25, "Chemistry", "WW_520", 95, 98, "nitrite fertilizers", 5, 5, 5);
	graduate.info();
#endif // INHERITANCE

#ifdef POLYMORPHISM
	Human* group[] =
	{
		new Student("Pincman", "Jessie", 22, "Chemistry", "WW_220", 95, 98),
		new Teacher("Pin", "Jes", 50, "Chemistry", 25),
		new Graduate("Sara", "Coner", 25, "Chemistry", "WW_520", 95, 98, "nitrite fertilizers", 5, 5, 5),
		new Student("Jonh", "Coner", 30, "Chemistry", "WW_220", 95, 98),
		new Teacher("Pinoc", "DjJes", 50, "Chemistry", 20)
	};

	std::ofstream fout("group.txt");
	for (int i(0); i < sizeof(group) / sizeof(group[0]); i++)
	{	
		group[i]->info(cout);
		fout << *group[i] << endl;
		cout << delimiter << endl;
	}
	fout.close();


	system("notepad group.txt");
	for (int i(0); i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
		cout << delimiter << endl;
	}

#endif // POLYMORPHISM

}
