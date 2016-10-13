#include <iostream>
using namespace std;

class student
{
	private:
		string name;
		int grade;
	public:
		student()
		{
			name = "Neil";
			grade = 14;
		}
		void setName(string newName)
		{
			name = newName;
		}
		string getName()
		{
			return name;
		}
		void setGrade(int newGrade)
		{
			grade = newGrade;
		}
		int getGrade()
		{
			return grade;
		}
};

void graduate(student* s)
{
	int newGrade = s->getGrade();
	newGrade++;
	s->setGrade(newGrade);
}

int main()
{
	student *s = new student();
	cout << s->getName() << " is in grade " << s->getGrade() << endl;
	graduate(s);
	cout << s->getName() << " is in grade " << s->getGrade() << endl;
	return 0;
}