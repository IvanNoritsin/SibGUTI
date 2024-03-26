#include <iostream>

using namespace std;

class StudentGroup {
private:
	string type;
	int course;
	string name;

public:
	StudentGroup(string p_type, int p_course, string p_name) {
		type = p_type;
		course = p_course;
		name = p_name;
	}

	void output() {
		cout << "--------------------\n" << "Type: " << type << "\nCourse: " << course << "\nName: " << name << "\n--------------------" << endl;
	}

	string GetType() {
		return type;
	}

	void SetType(string t) {
		type = t;
	}

	int GetCourse() {
		return course;
	}

	void SetCourse(int c) {
		course = c;
	}

	string GetName() {
		return name;
	}

	void SetName(string n) {
		name = n;
	}
};


int main() {
	StudentGroup a("University", 1, "IA-232");
	StudentGroup b("College", 2, "AB-115");
	StudentGroup c("University", 4, "IP-817");

	a.output();
	b.output();
	c.output();

	a.SetName("IA-231");
	b.SetCourse(3);
	c.SetType("College");

	cout << endl;

	cout << "Name a: " << a.GetName() << endl;
	cout << "Course b: " << b.GetCourse() << endl;
	cout << "Type c: " << c.GetType() << endl;

	cout << endl;

	a.output();
	b.output();
	c.output();

	return 0;
}