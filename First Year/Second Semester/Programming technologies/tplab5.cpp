#include <iostream>
#include <math.h>

using namespace std;

class EquilateralTriangle {
    protected:
        double side;

    public:
        EquilateralTriangle(double s) {
            side = s;
        }

        double getHeight() {
            return sqrt(3) / 2 * side;
        }

        double getBisector() {
            return sqrt(3) / 2 * side;
        }

        double getPerimeter() {
            return 3 * side;
        }

        double getArea() {
            return sqrt(3) / 4 * side * side;
        }

        void printInfo() {
            cout << "Equilateral Triangle:" << endl;
            cout << "Side length: " << side << endl;
            cout << "Height: " << getHeight() << endl;
            cout << "Bisector: " << getBisector() << endl;
            cout << "Perimeter: " << getPerimeter() << endl;
            cout << "Area: " << getArea() << endl;
        }
};

class RegularPyramid : public EquilateralTriangle {
    private:
        double apothem;

    public:
        RegularPyramid(double s, double h) : EquilateralTriangle(s) {
            apothem = h;
        }

        double getVolume() {
            return getArea() * apothem / 3;
        }

        double getArea() {
            return EquilateralTriangle::getArea() + 3 * getBaseArea();
        }

        double getBaseArea() {
            return sqrt(3) / 4 * side * side;
        }

        void printInfo() {
            cout << "Regular Pyramid:" << endl;
            cout << "Side length: " << side << endl;
            cout << "Height: " << apothem << endl;
            cout << "Perimeter: " << getPerimeter() << endl;
            cout << "Base Area: " << getBaseArea() << endl;
            cout << "Surface Area: " << getArea() << endl;
            cout << "Volume: " << getVolume() << endl;
        }
};

int main() {
    EquilateralTriangle t(5);
    t.printInfo();

    RegularPyramid p(5, 7);
    p.printInfo();

    return 0;
}