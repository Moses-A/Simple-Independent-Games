//Heap Data Member
//Demonstrates an object with a dynamically allocated data member
// Author is Moses Arocha

#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

WORD GetConsoleTextAttribute (HANDLE hCon)
{
  CONSOLE_SCREEN_BUFFER_INFO con_info;
  GetConsoleScreenBufferInfo(hCon, &con_info);
  return con_info.wAttributes;
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int saved_colors = GetConsoleTextAttribute(hConsole);

class Robots
{
	public: 
	    Robots(const string& name = "", int age = 0);  
	    ~Robots();                   //destructor prototype   
	    Robots(const Robots& c);    //copy constructor prototype
	    Robots& Robots::operator=(const Robots& c);  //overloaded assignment op
	    void Greet() const; 
	
	private:
	    string* m_pName; // this is a pointer to the string object
	    int m_Age;
};

Robots::Robots(const string& name, int age)
{
    cout << "\n\n (We Are Constructing The Robot...)\n\n";
    m_pName = new string(name); // this assigns memory for the string, assigns name ot it, then points to m_pName to it
    m_Age = age;  // this has no pointer involved
}

Robots::~Robots()                        //destructor definition
{
    cout << "\n (We Are Destroying The Robot...)\n";
    delete m_pName;						// this deletes the value of m_pName, it is then redefined
}

Robots::Robots(const Robots& c)        //copy constructor definition
{
    cout << "\n\n (We Are Copying This Perfect Robot...)\n";
    m_pName = new string(*(c.m_pName));
    m_Age = c.m_Age;
}

Robots& Robots::operator=(const Robots& c)  //overloaded assignment op def
{
    cout << "\n\n (Uh, Oh. We Have Overloaded On Creating...)\n\n";
    if (this != &c)
    {
        delete m_pName;
        m_pName = new string(*(c.m_pName));
        m_Age = c.m_Age;
    }
    return *this;
}

void Robots::Greet() const
{
     cout << " I'm " << *m_pName << " and I'm " << m_Age << " years old. ";
     cout << "\n My Barcode Name Is: " << cout << &m_pName << endl; // The pointer address for name
}

void testDestructor();
void testCopyConstructor(Robots aCopy);
void testAssignmentOp();

/* This code demontrates the different treatments that data members experience
    as they are destroyed, copied, and assigned*/

int main()
{
	SetConsoleTextAttribute(hConsole, 0x08); // Sets The Color To Gray

	string NewRobotName;
	nt NewRobotAge;

	testDestructor();
	cout << endl;
	
	cout << "\n The Last Robot Was Defective. Please Create A New One.\n";
	cin.ignore();
	cout << " What Would You Like To Name The New Robot? : ";
	getline(cin, NewRobotName);

	cout << "\n Please Enter How Old " << NewRobotName << " Is: ";

	while(!(cin >> NewRobotAge))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max_digits10, '\n'); // if max_digits(10) doesn't work, try digits alone
		cout << " This Is An Invalid Input: ";
	}

	Robots rob(NewRobotName, NewRobotAge); // this is the different treatment of data, with age
	rob.Greet();

	testCopyConstructor(rob); // the copying of the newly defined robot
	rob.Greet();
	cout << endl;
	cout << " We Must Delete That Robot. It Was Evil...\n\n";

	testAssignmentOp();

    return 0;
}

void testDestructor()
{
	string RobotName;
	int RobotAge;
	cout << "\t Welcome To The Robot Factory!\n\n";
	cout << " Please Enter What You Want To Name The Robot: ";
	getline(cin,RobotName);

	cout << "\n Please Enter How Old " << RobotName << " Is: ";

	while(!(cin >> RobotAge))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max_digits10, '\n');
		cout << " This Is An Invalid Input: ";
	}

    Robots toDestroy(RobotName, RobotAge); // string variable is stored on the Heap; string object
    toDestroy.Greet(); // shoots over to the Greet function in the toDestroy
}

void testCopyConstructor(Robots aCopy)  
{
    aCopy.Greet(); // this duplicates the information, so you can delete the path to one
}

void testAssignmentOp()
{
	string RobotNameTry;
	int RobotAgeTry;

	cout << "\n\n We Messed Up Again... Hopefully Third Time Is A Charm...\n\n";
	cin.ignore();
	cout << " What Would You Like To Name The New Robot? : ";
	getline(cin, RobotNameTry);

	cout << "\n Please Enter How Old " << RobotNameTry << " Is: ";

	while(!(cin >> RobotAgeTry))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max_digits10, '\n');
		cout << " This Is An Invalid Input: ";
	}

    Robots rob1(RobotNameTry, RobotAgeTry);
    Robots rob2("rob2", 9);
    rob2 = rob1; // it creates two objects, the assigns the values of one to another
    rob1.Greet();  
    rob2.Greet();
    cout << endl;
    
	
	cout << " Please Wait Was We Fix the Problem...\n" << endl;
	Sleep(10000);

	cout << " We Are Attempting To Start All Over Again.\n" << endl;
    Robots rob3("rob", 11);
    rob3 = rob2;
    rob3.Greet();
	cout << endl;
	cout << " Now We Must DELETE EVERYTHING! \n" << endl << endl;
}
