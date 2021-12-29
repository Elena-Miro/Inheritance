#include<iostream>
#include<string>
using namespace std;
#define HUMAN_TAKE_PARAMETRS const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARAMETRS last_name,first_name,age
class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;

public:
	const std::string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
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
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	//Construction
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
	//Metods
    virtual void print()const
	{
		cout << last_name << " " << first_name << " " << age << "лет" << endl;
	}
};
#define STUDENT_TAKE_PARAMETRS const std::string& speciality, const std::string& group, double rating, double attendence
#define STUDENT_GIVE_PARAMETRS  speciality,group,rating,attendence

class Student :public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendence;

public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	const std::string& get_group() const
	{
		return group;
	}
	double get_rating() const
	{
		return rating;
	}
	double get_attendence()const
	{
		return attendence;
	}
	void set_speciality(const std::string & speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string & group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendence(double attendence)
	{
		this->attendence = attendence;
	}
	//Constructors
	Student
	(HUMAN_TAKE_PARAMETRS,STUDENT_TAKE_PARAMETRS)
		:Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendence(attendence);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	void print()const
	{
		Human::print();
		cout << speciality << " " << group << " " << rating << " " << attendence << " " << endl;
	}

};
#define TEACHER_TAKE_PARAMETRS const std::string& speciality, unsigned int experience, double evil
#define TEACER_GIVE_PARAMETRS speciality,experience,evil

class Teacher :public Human
{
	std::string speciality;
	unsigned int experience;
	double evil;
	

public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experience() const
	{
		return experience;
	}
	double get_evil() const
	{
		return evil;
	}
	
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}
	void set_evil(double evil)
	{
		this->evil = evil;
	}
	
	//Constructors
	Teacher
	(HUMAN_TAKE_PARAMETRS,TEACHER_TAKE_PARAMETRS)
		:Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_experience(experience);
		set_evil(evil);
		
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	void print()const
	{
		Human::print();
		cout << speciality << " " << experience << " " << evil << " " << endl;
	}

};
class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	//						Constructors:
	Graduate(
		HUMAN_TAKE_PARAMETRS,STUDENT_TAKE_PARAMETRS,const std::string& subject)
		:Student(HUMAN_GIVE_PARAMETRS,STUDENT_GIVE_PARAMETRS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	//						Methods:
	void print()const
	{
		Student::print();
		cout << subject << endl;
	}
};
//#define INHERITANCE_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef INHERITANCE_CHECK
	Human human("Connor", "John", 18);
	human.print();

	Student stud("Pinkman", "Jessie", 25, "Chemistry", "WW_123", 85, 95);
	stud.print();
	Teacher teach("Freeman", "Morgan", 55, "Chemistry", 20, 0);
	teach.print();
	Graduate grad("Shreder", "Hank", 40, "Cryminalistic", "WW_123", 90, 75, "How to catch Heizenberg");
	grad.print();
#endif // INHERITANCE_CHECK
	//Generalisation(up-cast)
	Human* group[] =
	{
	new Student("Pinkman", "Jessie", 25, "Chemistry", "WW_123", 85, 95),
	new Teacher("Freeman", "Morgan", 55, "Chemistry", 20, 0),
	new Graduate("Shreder", "Hank", 40, "Cryminalistic", "WW_123", 90, 75, "How to catch Heizenberg"),
	new Student("Vercetti","Tomas",30,"City business","Vice",98,99),
	new Teacher("Diaz", "Ricardo",55,"Weapons distribution",30,10),
	new Student("Montana","Antonio",30,"Cryminalistic","Vice",90,80),
	};
	cout << sizeof(group) / sizeof(Human*) << endl;//Вычисляем размер массивово в элементах
	//оператор sizeof()возвращает в байтах
	for (int i = 0; i < sizeof(group)/sizeof(Human*); i++)
	{
		//TRRI-Runtime Type Information
		cout << typeid(group[i]).name() << endl;
		group[i]->print();
		cout << "\n---------------------------------------\n";
	}
	/////////////////////////////
	for (int i = 0; i< sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}
}