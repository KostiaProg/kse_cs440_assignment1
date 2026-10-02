#include "Line.hpp"
#include <iostream>
#include <cmath>
using namespace std;

Line::Line() : Shape(), x2(0), y2(0) {}
Line::Line(int x1, int y1, int x2, int y2) : Shape(x1, y1), x2(x2), y2(y2) {}
Line::Line(int x1, int y1, const string& c, int x2, int y2) : Shape(x1, y1, c, false), x2(x2), y2(y2) {}
Line::Line(int x1, int y1, const string& c, bool /*fill*/, int x2, int y2) : Shape(x1, y1, c, false), x2(x2), y2(y2) {}

void Line::draw(vector<vector<char>>& canvas) const {
    int x0 = x;
    int y0 = y;
    int x1 = x2;
    int y1 = y2;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x0 >= 0 && x0 < (int)canvas[0].size() && y0 >= 0 && y0 < (int)canvas.size()) {
            canvas[y0][x0] = '*';
        }

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

string Line::info() const {
    return Shape::info() + ", End Point: (" + to_string(x2) + ", " + to_string(y2) + ") - Line";
}

string Line::saveInfo() const {
    return "line " + to_string(x) + " " + to_string(y) + " " + color + " " +
           to_string(x2) + " " + to_string(y2);
}

int Line::getX2() const { return x2; }
int Line::getY2() const { return y2; }
void Line::setX2(int posX2) { x2 = posX2; }
void Line::setY2(int posY2) { y2 = posY2; }

Shape* Line::create(int x, int y, const string& color, bool /*fill*/, stringstream& ss) {
    string X2s, Y2s;
    if (!(ss >> X2s >> Y2s)) return nullptr;

    int X2, Y2;
    try {
        X2 = stoi(X2s);
    } catch (const invalid_argument&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    } catch (const out_of_range&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    }

    try {
        Y2 = stoi(Y2s);
    } catch (const invalid_argument&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    } catch (const out_of_range&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    }

    return new Line(x, y, color, X2, Y2);
}

void Line::edit(std::stringstream& ss) {
    int x2, y2;
    if (ss >> x2 >> y2) {
        setX2(x2);
        setY2(y2);
    }
    else cout << "Wrong input format" << endl;
}