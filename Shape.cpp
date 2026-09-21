#include "Shape.hpp"
using namespace std;

Shape::Shape() : x(0), y(0), color("black"), fill(false) {}
Shape::Shape(int posX, int posY) : x(posX), y(posY), color("black"), fill(false) {}
Shape::Shape(int posX, int posY, const string& c) : x(posX), y(posY), color(c), fill(false) {}
Shape::Shape(int posX, int posY, bool f) : x(posX), y(posY), color("black"), fill(f) {}
Shape::Shape(int posX, int posY, const string& c, bool f) : x(posX), y(posY), color(c), fill(f) {}

string Shape::info() const {
    return "Position: (" + to_string(x) + ", " + to_string(y) +
           "), Color: " + color + ", Fill: " + (fill ? "Yes" : "No");
}

int Shape::getX() const { return x; }
int Shape::getY() const { return y; }
string Shape::getColor() const { return color; }
bool Shape::getFill() const { return fill; }

void Shape::setX(int posX) { x = posX; }
void Shape::setY(int posY) { y = posY; }
void Shape::setColor(const string& c) { color = c; }
void Shape::setFill(bool f) { fill = f; }