#include<iostream>
#include<fstream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

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
	virtual std::ostream& print(std::ostream& os)const
	{
	//return os << last_name << " " << first_name << " " << age << "лет";
		os.width(10);
		os << left;
		os << last_name;
		os.width(10);
		os << first_name;
		os.width(3);
		os << age <<" лет";
		return os;
	}
	virtual std::ofstream& print(std::ofstream& os)const
	{
	//return os << last_name << " " << first_name << " " << age << "лет";
		os.width(10);
		os << left;
		os << last_name;
		os.width(10);
		os << first_name;
		os.width(3);
		os << age ;
		return os;
	}
	virtual ifstream& scan(ifstream& is)
	{
		is >> last_name >> first_name >> age;
		return is;
	}
	
};

ostream& operator<<(ostream& os, const Human& obj)
{
	return obj.print(os);
}
ofstream& operator<<(ofstream& os, const Human& obj)
{
	return obj.print(os);
}
ifstream& operator>>(ifstream& is, Human& obj)
{
	return obj.scan(is);
}
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
	std::ostream& print(std::ostream& os)const
	{
		Human::print(os)<<" ";
		os.width(10);
		os << left;
		os << position;
		return os;
		
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Human::print(os) << " ";
		os.width(10);
		os << left;
		os << position;
		return os;

	}
	ifstream& scan(ifstream& is)
	{
		Human::scan(is);
		is >> position;
		return is;
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
		cout << "PECopyConstructor:\t" << this << endl;
	}

	
	~PermanentEmployee()
	{
		cout << "EPDeconstructor:\t" << this << endl;
	}
	std::ostream& print(std::ostream& os)const
	{
		
		Employee::print(os)<<" ";
		os.width(10);
		os << right;
		os << salary;
	    return os;
		
	}
	std::ofstream& print(std::ofstream& os)const
	{

		Employee::print(os) << " ";
		os.width(10);
		os << right;
		os << salary;
		return os;

	}
	ifstream& scan(ifstream& is)
	{
		Employee::scan(is);
		is >> salary;
		return is;
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
	std::ostream& print(std::ostream& os)const
	{
		Employee::print(os)<<" ";
		os << "Тариф: ";
		os.width(5);
		os << right;
		os << rate;
		os << " отработано: ";
		os.width(3);
		os<< hours<<" итого: " << get_salary();
		return os;
		
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Employee::print(os) << " ";
		
		os.width(10);
		os << right;
		os << rate;
		os.width(3);
		os << hours;
		return os;

	}
	ifstream& scan(ifstream& is)
	{
		Employee::scan(is);
		is >> rate >> hours;
		return is;
	}
	};
Employee* EmployeeFactory(const string& type)
{
	if (type.find("PermanentEmployee")!=std::string::npos)return new PermanentEmployee("", "", 0, "", 0);
	if (type.find("HourlyEmployee") != std::string::npos)return new HourlyEmployee("", "", 0, "", 0, 0);
}

//#define SAVE_TO_FILE
void main()
{
	setlocale(LC_ALL, "");

#ifdef SAVE_TO_FILE
	std::string str = "Hello";
	cout << str.c_str()[1] << endl;
	cout << typeid(str.c_str()).name() << endl;

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
		cout << "\n----------------------------------" << endl;
		//department[i]->print();
		cout << *department[i] << endl;
		total_salary += department[i]->get_salary();

	}
	/*PermanentEmployee pe;
	cout << "Введите информацию о сотруднике: ";
	cin >> pe;*/




	ofstream fout("file.txt");
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		fout.width(25);
		fout << left;
		fout << string(typeid(*department[i]).name()) + ":";
		fout << *department[i] << endl;
	}
	fout << "\n----------------------------------" << endl;
	fout << "Общая зарплата всего отдела:" << total_salary << endl;
	fout << "\n----------------------------------" << endl;
	fout.close();
	system("start notepad file.txt");
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		delete department[i];
	}
#endif // SAVE_TO_FILE
	int n = 0;//Размер массива
	Employee** department = nullptr;

	ifstream fin("file.txt");

	if (fin.is_open())
	{
		//1)Опред кол-во записей в файлеб для тогоБ чтобы выделить память под сотрудников
		string employee_type;
		
		for (; !fin.eof(); n++)
		{
			getline(fin, employee_type);
		}
		n--;
		cout << n << endl;
		//выделяем память под массив
		department = new Employee* [n] {};
		//возвращаем курсор в начало файла
		cout << fin.tellg() << endl;
		fin.clear();//очищаем поток
		fin.seekg(0);//задаем расположение курсора
		cout << fin.tellg() << endl;
		//4)загружаем данные из файла в массив
		for (int i = 0; i < n; i++)
		{
			getline(fin, employee_type, ':');
			department[i] = EmployeeFactory(employee_type);
			fin >> *department[i];
		}
	}
	else
	{
		cerr << "Error: file not found" << endl;
	}
	for (int i = 0; i < n; i++)
	{
		cout << *department[i]<<endl;
	}
	for (int i = 0; i < n; i++)
	{
		delete department[i];
	}
	delete[] department;
	fin.close();

}