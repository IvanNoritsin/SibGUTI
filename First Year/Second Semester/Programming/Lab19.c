#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <list>

using namespace std;

class Train {
private:
    int Number;
    string Station;
    int Time;

public:
    Train() {}

    Train(int num, string st, int tm) {
        Number = num;
        Station = st;
        Time = tm;
    }

    void Output() {
        cout << "Number: " << Number << endl << "Station: " << Station << endl << "Time: " << Time << endl << "*******************" << endl;
    }

    int GetNumber() {
        return Number;
    }

    void SetNumber(int num) {
        Number = num;
    }

    string GetStation() {
        return Station;
    }

    void SetStation(string st) {
        Station = st;
    }

    int GetTime() {
        return Time;
    }

    void SetTime(int tm) {
        Time = tm;
    }
};




int main() {
    list <Train> TrainList;
    int num, tm, sw, f = 0;
    string st;

    while (1) {
        cout << "Train number: ";
        cin >> num;
        if (num == 0) break;
        cout << endl;
        cout << "Destination station: ";
        cin >> st;
        cout << endl;
        cout << "Departure time: ";
        cin >> tm;
        cout << endl << "--------------------------" << endl;
        TrainList.push_back(Train(num, st, tm));
    }

    do {
    cout << "Menu" << endl << "Press '1' to display the list" << endl << "Press '2' to search by train number" << endl << "Press '3' to search for trains by station name" << endl << "-> ";
    cin >> sw;
    
        switch (sw) {
        case 1:
            cout << "*******************" << endl;
            for (auto i = TrainList.begin(); i != TrainList.end(); i++) {
                i->Output();
            }
            break;
        case 2:
            cout << "Enter the number of the train you are looking for: ";
            cin >> num;
            cout << endl;
            for (auto i = TrainList.begin(); i != TrainList.end(); i++) {
                if (i->GetNumber() == num) {
                    cout << "*******************" << endl;
                    i->Output();
                    f = 1;
                }
            }
            if (f == 0) {
                cout << "Train not found";
            }
            break;
        case 3:
            cout << "Enter the destination station: ";
            cin >> st;
            f = 0;
            for (auto i = TrainList.begin(); i != TrainList.end(); i++) {
                if (i->GetStation() == st) {
                    cout << "*******************" << endl;
                    i->Output();
                    f = 1;
                }
            }
            if (f == 0) {
                cout << "No trains to" << st << "station found";
            }
            break;
        }
    } while (sw != 0);

        return 0;
    }
