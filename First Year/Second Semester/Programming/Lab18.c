#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

class StudentGroup {
public:
    string type;
    int course;

public:
    StudentGroup(){}

    StudentGroup(string p_type, int p_course) {
        type = p_type;
        course = p_course;
    }

    void output() {
        cout << "--------------------\n" << "Type: " << type << "\nCourse: " << course << "\n--------------------" << endl;
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

};

bool sort_s(const StudentGroup& t1, const StudentGroup& t2) {
    return t1.course < t2.course;
}

int main() {
    int a, N, M, j = 0;
    cout << "Size of vector: ";
    cin >> N;
    vector <string> v{"College", "University"};
    vector <StudentGroup> sg(N);
    vector <StudentGroup> sg1;
    srand(time(NULL));
    for (int i = 0; i < sg.size(); i++) {
        sg[i] = StudentGroup(v[rand() % 2], rand() % 4 + 1);
    }

    for (int i = 0; i < sg.size(); i++) {
        sg[i].output();
        cout << endl;
    }

    cout << "*****************************************************************************************";
    cout << endl;

    for (int i = 0; i < sg.size(); i++) {
        if (sg[i].GetCourse() >= 3) {
            sg1.push_back(sg[i]);
        }
    }

    for (int i = 0; i < sg1.size(); i++) {
        sg1[i].output();
        cout << endl;
    }

    if (sg1.empty()) {
        cout << "The vector sg1 is empty" << endl;
    }

    else {
        cout << "The vector sg1 is not empty" << endl;
        sort(sg1.begin(), sg1.end(), sort_s);
        cout << endl;
        cout << "*****************************************************************************************";
        cout << endl;

        for (int i = 0; i < sg1.size(); i++) {
            sg1[i].output();
            cout << endl;
        }
    }


    return 0;
}
