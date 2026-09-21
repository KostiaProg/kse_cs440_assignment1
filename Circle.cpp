#include "Circle.hpp"
#include <iostream>
using namespace std;

Circle::Circle() : Shape(), radius(0) {}
Circle::Circle(int r) : Shape(), radius(r) {}
Circle::Circle(int posX, int posY, int r) : Shape(posX, posY), radius(r) {}
Circle::Circle(int posX, int posY, const string& c, int r) : Shape(posX, posY, c), radius(r) {}
Circle::Circle(int posX, int posY, bool f, int r) : Shape(posX, posY, f), radius(r) {}
Circle::Circle(int posX, int posY, const string& c, bool f, int r) : Shape(posX, posY, c, f), radius(r) {}

void Circle::draw(vector<vector<char>>& canvas) const {
    if (radius <= 0) {
        cout << "Invalid circle radius." << endl;
        return;
    }

    int rSquare = radius * radius;
    for (int i = -radius; i <= radius; ++i) {
        for (int j = -radius; j <= radius; ++j) {
            int sumSquares = i * i + j * j;

            bool onCircle = false;
            if (fill) onCircle = (sumSquares <= rSquare);
            else onCircle = (sumSquares >= rSquare - radius) && (sumSquares <= rSquare + radius);

            if (onCircle) {
                int posX = x + j;
                int posY = y + i;
                if (posX >= 0 && posX < (int)canvas[0].size() &&
                    posY >= 0 && posY < (int)canvas.size()) {
                    canvas[posY][posX] = '*';
                }
            }
        }
    }
}

string Circle::info() const {
    return Shape::info() + ", Radius: " + to_string(radius) + " - Circle";
}

string Circle::saveInfo() const {
    return "circle " + to_string(x) + " " + to_string(y) + " " + color + " " +
           (fill ? "true" : "false") + " " + to_string(radius);
}

int Circle::getRadius() const { return radius; }
void Circle::setRadius(int r) { radius = r; }

Shape* Circle::create(int x, int y, const string& color, bool fill, stringstream& ss) {
    string rs;
    if (!(ss >> rs)) return nullptr;

    int r;
    try {
        r = stoi(rs);
    } catch (const invalid_argument&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    } catch (const out_of_range&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    }

    return new Circle(x, y, color, fill, r);
}