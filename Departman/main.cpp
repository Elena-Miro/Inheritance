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
#define EMPLOYEE_TAKE_PARAMETRS const std::string& position
#define EMPLOYEE_GIVE_PARAMETRS position
class Employee :public Human
{
	std::string position;
public:
	const std::string& get_position() const
	{
		return position;
	}
	void set_position(const std::string& position)
	{
		this->position = position;
	}
	virtual double get_salary()const = 0;
	Employee(HUMAN_TAKE_PARAMETRS,EMPLOYEE_TAKE_PARAMETRS):Human(HUMAN_GIVE_PARAMETRS)
	{
		set_position(position);
		cout << "EConstructor:\t" << this << endl;

	}
	~Employee()
	{
		cout << "EDeconstructor:\t" << this << endl;
	}
	void print()const
	{
		Human::print();
		cout << position;
		cout << endl;
	}
};
#define PERMANENT_EMLOYEE_TAKE_PARAMETRS double salary
#define PERMANENT_EMLOYEE_GIVE_PARAMETRS salary
class PermanentEmployee :public Employee
{
	double salary;
public:
	double get_salary()const
	{
		return salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}
	PermanentEmployee(HUMAN_TAKE_PARAMETRS, EMPLOYEE_TAKE_PARAMETRS, PERMANENT_EMLOYEE_TAKE_PARAMETRS)
		:Employee(HUMAN_GIVE_PARAMETRS, EMPLOYEE_GIVE_PARAMETRS)
	{
		set_salary(salary);
		cout << "PEConstructor:\t" << this << endl;
	}
	~PermanentEmployee()
	{
		cout << "EPDeconstructor:\t" << this << endl;
	}
	void print()const
	{
		Employee::print();
		cout << salary;
		cout << endl;
	}

};
#define HOURLY_EMPLOYEE_TAKE_PARAMETRS double rate, int hours
#define HOURLY_EMPLOYEE_GIVE_PARAMETRS rate,hours
class HourlyEmployee :public Employee
{
	double rate; //ставка за 1 час
	int hours;//кол-во отработанных часов
public:
	double get_rate()const
	{
		return rate;
	}
	int get_hours()const
	{
		return hours;
	}
	double get_salary()const
	{
		return rate * hours;
	}
	void set_rate(double rate)
	{
		this->rate = rate;
	}
	void set_hours(int hours)
	{
		this->hours = hours;
	}
	HourlyEmployee(HUMAN_TAKE_PARAMETRS, EMPLOYEE_TAKE_PARAMETRS, HOURLY_EMPLOYEE_TAKE_PARAMETRS)
		:Employee(HUMAN_GIVE_PARAMETRS, EMPLOYEE_GIVE_PARAMETRS)
	{
		set_rate(rate);
		set_hours(hours);
		cout << "HEConstructor:\t" << this << endl;
	}
	~HourlyEmployee()
	{
		cout << "HEDestructor:\t" << this << endl;
	}
	void print()const
	{
		Employee::print();
		cout << "Тариф: " << rate << " отработано: " << hours<<" итого: " << get_salary();
		cout << endl;
	}
	};
void main()
{
	std::string str = "Hello";
	cout << str.c_str()[1] << endl;
	cout << typeid(str.c_str()).name() << endl;

	setlocale(LC_ALL, "");
	Employee* department[] =
	{
		new PermanentEmployee("Rosenberg","Ken",30,"Lawer",2000),
		new PermanentEmployee("Diaz","Ricardo",50,"Boss",50000),
		new HourlyEmployee("Vercetty","Tomas",30,"Security",500,8),
	};
	department[0]->get_first_name().c_str();
	double total_salary = 0;
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		cout << "\n----------------------------------"<<endl;
		department[i]->print();
		total_salary += department[i]->get_salary();
		
	}
	cout << "\n----------------------------------"<<endl;
	cout << "Общая зарплата всего отдела:" << total_salary << endl;
	cout << "\n----------------------------------"<<endl;
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		delete department[i];
	}
}