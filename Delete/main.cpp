#include <iostream>
#include <string>
using namespace std;

#define HUMAN_TAKE_PARAMETRS const std::string& last_name,const std::string first_name,unsigned int age
#define HUMAN_GIVE_PARAMETRS last_name,first_name,age
class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;

public:
	const std::string& get_first_name() const
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

	Human(HUMAN_TAKE_PARAMETRS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor" << this << endl;
	}

	virtual void print() const
	{
		cout << last_name << " " << first_name << " " << age << "years" << endl;
	}

 };
#define STUDENT_TAKE_PARAMETRS const std::string& speciality, const std::string& group, double raiting, double attendance
#define STUDENT_GIVE_PARAMETRS speciality,group,raiting,attendance
class Student :public Human
{
	std::string speciality;
	std::string group;
	double raiting;
	double attendance;
public:
	const std::string& get_speciality()
	{
		return speciality;
	}
	const std::string& get_group()
	{
		return group;
	}
	double get_rating()
	{
		return raiting;
	}
	double get_attendance()
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
	void set_raiting(double raiting)
	{
		this->raiting = raiting;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	Student(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS) :
		Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_group(group);
		set_raiting(raiting);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	void print()const
	{
		Human::print();
		cout << speciality << " " << group << " " << raiting << " " << attendance << endl;
	}
};
#define TEACHER_TAKE_PARAMETRS const std::string& speciality, unsigned int experience,double evil
#define TEACHER_GIVE_PARAMETRS speciality,experience,evil
class Teacher :public Human
{
	std::string& speciality;
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
	double get_evil()const
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

	Teacher(HUMAN_TAKE_PARAMETRS, TEACHER_TAKE_PARAMETRS)
		:Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_experience(experience);
		set_evil(evil);
		cout<<"TConstructor:\t"<<this<<endl;
	}
	~Teacher()
	{
		cout << "TDeconstructor:\t" << this << endl;
	}
	void print() const
	{
		Human::print();
		cout << speciality << " " << experience << " " << evil << endl;
	}
};
class Graduade:public Student
{
	std::string subject;
public:
	const std::string& get_subject() const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	Graduade(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS, const std::string& subject)
		: Student(HUMAN_GIVE_PARAMETRS, STUDENT_GIVE_PARAMETRS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduade()
	{
		cout << "GDeconstructor:\t" << this << endl;
	}
	void print() const
	{
		Student::print();
		cout << subject << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "");

	Human* group[]=
	{
		new Teacher("Freeman", "Morgan", 55, "Chemistry", 20, 0),
		new Student("Pinkman", "Jessie", 25, "Chemistry", "WW_123", 85, 95),
		new Graduade("Shreder", "Hank", 40, "Cryminalistic", "WW_123", 90, 75, "How to catch Heizenberg"),
	};
}