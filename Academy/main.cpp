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
	static const int TYPE_WIDTH = 12;
	static const int NAME_WIDTH = 12;
	static const int AGE_WIDTH = 5;
	static int count;
	std::string last_name;
	std::string first_name;
	int age;
public:
	static int get_count()
	{
		return count;
	}
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
		count++;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
		count--;
	}

	//Methods
	virtual std::ostream& info(std::ostream& os)const
	{
		//return os << last_name << " " << first_name << " " << age;
		os.width(TYPE_WIDTH);
		os << std::left;
		os << std::string(strchr(typeid(*this).name(), ' ') + 1) + ":";
		os.width(NAME_WIDTH);
		os << last_name;
		os.width(NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
	}

	virtual std::istream& scan(std::istream& is)
	{
		return is >> last_name >> first_name >> age;
	}
};

int Human::count = 0;
std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}

std::istream& operator>>(std::istream& is, Human& obj)
{
	return obj.scan(is);
}

#define STUDENT_TAKE_PARAMETRS const std::string& spesiality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETRS spesiality,group, rating, attendance

class Student :public Human
{
	static const int SPECIALITY_WIDTH = 32;
	static const int GROUP_WIDTH = 8;
	static const int RAT_WIDTH = 8;
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
		//return Human::info(os) << " " << speciality << " " << group << " " << rating << " " << attendance;
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RAT_WIDTH);
		os << rating;
		os.width(RAT_WIDTH);
		os << attendance;
		return os;
	}

	std::istream& scan(std::istream& is) override
	{
		Human::scan(is);
		char sz_buffer[SPECIALITY_WIDTH + 1] = {};
		is.read(sz_buffer, SPECIALITY_WIDTH);
		for (int i = SPECIALITY_WIDTH - 1; sz_buffer[i] == ' '; i--) sz_buffer[i] = 0;
		
		while (sz_buffer[0] == ' ')
			for (int i = 0; sz_buffer[i]; i++) sz_buffer[i] = sz_buffer[i + 1];
		
		speciality = sz_buffer; //сохраняем специальность в соотв. поле
		is >> group >> rating >> attendance;
		return is;
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
		return Student::info(os) << topic_of_graduation_project << " " << practice_mark << " " << final_exam_mark << " " << graduation_mark;
	}

	std::istream& scan(std::istream& is) override
	{
		Student::scan(is);
		is >> topic_of_graduation_project >> practice_mark >> final_exam_mark >> graduation_mark;
		return is;
	}
};


#define TEACHER_TAKE_PARAMETRS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETRS speciality, experience

class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 32;
	static const int EXPIRIENCE_WIDTH = 22;
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
		//return Human::info(os) << speciality << " " << experience;
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(EXPIRIENCE_WIDTH);
		os << experience;
		return os;
	}


	std::istream& scan(std::istream& is) override
	{
		Human::scan(is);
		char sz_buffer[SPECIALITY_WIDTH + 1] = {};
		is.read(sz_buffer, SPECIALITY_WIDTH);
		for (int i = SPECIALITY_WIDTH - 1; sz_buffer[i] == ' '; i--) sz_buffer[i] = 0;

		while (sz_buffer[0] == ' ')
			for (int i = 0; sz_buffer[i]; i++) sz_buffer[i] = sz_buffer[i + 1];

		speciality = sz_buffer; //сохраняем специальность в соотв. поле
		is >> experience;
		return is;
	}
};


void Print(Human* group[], const int n)
{
	for (int i(0); i < n; i++)
	{
		group[i]->info(cout);
		cout << delimiter << endl;
	}
	cout << "Количество объектов: " << group[0]->get_count() << endl;
	cout << "Количество объектов: " << Human::get_count() << endl;
}

void Save(Human* group[], const int n, const std::string& filename)
{
	std::ofstream fout(filename);
	for (int i(0); i < n; i++)
	{
		fout << *group[i] << endl;
	}
	fout.close();
	std::string cmd = "notepad ";
	cmd += filename;
	system(cmd.c_str());
}

void Clear(Human* group[], const int n)
{
	for (int i(0); i < n; i++)
	{
		delete group[i];
		cout << delimiter << endl;
	}
}
Human* HumanFactory(const std::string& type)
{
	Human* human = nullptr;
	if (strstr(type.c_str(), "Human")) human = new Human("", "", 0);
	else if (strstr(type.c_str(), "Student")) human = new Student("", "", 0, "", "", 0, 0);
	else if (strstr(type.c_str(), "Graduate")) human = new Graduate("", "", 0, "", "", 0, 0, "", 0, 0, 0);
	else if (strstr(type.c_str(), "Teacher")) human = new Teacher("", "", 0, "", 0);
	return human;
}

Human** Load(const std::string& filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		n = 0;
		std::string buffer;
		while (!fin.eof())
		{
			std::getline(fin, buffer);
			if (buffer.size() < 20) continue;
			n++;
		}
		cout << "Количество объектов: " << n << endl;
		group = new Human* [n];
		cout << "Position " << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);

		for (int i = 0; i < n; i++)
		{
			std::string buffer;
			std::getline(fin, buffer, ':');
			if (buffer.size() < 5) continue;
			group[i] = HumanFactory(buffer);
			fin >> *group[i];
		}
	}

	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	return group;
}



//#define INHERITANCE
//#define POLYMORPHISM


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
		new Teacher("Pin", "Jes", 50, "Chemistry Chem", 25),
		new Graduate("Sara", "Coner", 25, "Chemistry", "WW_520", 95, 98, "fertilizers", 5, 5, 5),
		new Student("Jonh", "Coner", 30, "Chemistry", "WW_220", 95, 98),
		new Teacher("Pinoc", "DjJes", 50, "Chemistry Chem", 20)
	};

	Print(group, sizeof(group) / sizeof(group[0]));
	Save(group, sizeof(group) / sizeof(group[0]), "group.txt");
	

	for (int i(0); i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
		cout << delimiter << endl;
	}

#endif // POLYMORPHISM
	int n;
	Human** group = Load("group.txt", n);
	Print(group, n);
	Save(group, n, "group_example.txt");
	Clear(group, n);
}
