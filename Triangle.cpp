#include "Triangle.hpp"
#include <iostream>
using namespace std;

Triangle::Triangle() : Shape(), base(0), height(0) {}
Triangle::Triangle(int b, int h) : Shape(), base(b), height(h) {}
Triangle::Triangle(int posX, int posY, int b, int h) : Shape(posX, posY), base(b), height(h) {}
Triangle::Triangle(int posX, int posY, const string& c, int b, int h) : Shape(posX, posY, c), base(b), height(h) {}
Triangle::Triangle(int posX, int posY, bool f, int b, int h) : Shape(posX, posY, f), base(b), height(h) {}
Triangle::Triangle(int posX, int posY, const string& c, bool f, int b, int h) : Shape(posX, posY, c, f), base(b), height(h) {}

void Triangle::draw(vector<vector<char>>& canvas) const {
    if (base <= 0 || height <= 0) {
        cout << "Invalid triangle dimensions." << endl;
        return;
    }

    for (int i = 0; i < height; ++i) {
        int currentWidth = 1 + (base - 1) * i / (height - 1);
        if (height == 1) currentWidth = base;

        int left = x - currentWidth / 2;
        int right = left + currentWidth - 1;
        int py = y + i;

        if (py < 0 || py >= (int)canvas.size()) continue;

        if (!fill) {
            if (left >= 0 && left < (int)canvas[0].size()) canvas[py][left] = '*';
            if (right >= 0 && right < (int)canvas[0].size() && right != left) canvas[py][right] = '*';

            if (i == height - 1) {
                for (int px = left; px <= right; ++px) {
                    if (px >= 0 && px < (int)canvas[0].size()) {
                        canvas[py][px] = '*';
                    }
                }
            }
        } else {
            for (int px = left; px <= right; ++px) {
                if (px >= 0 && px < (int)canvas[0].size()) canvas[py][px] = '*';
            }
        }
    }
}

string Triangle::info() const {
    return Shape::info() + ", Base: " + to_string(base) + ", Height: " + to_string(height) + " - Triangle";
}

string Triangle::saveInfo() const {
    return "triangle " + to_string(x) + " " + to_string(y) + " " + color + " " +
           (fill ? "true" : "false") + " " + to_string(base) + " " + to_string(height);
}

int Triangle::getBase() const { return base; }
int Triangle::getHeight() const { return height; }
void Triangle::setBase(int b) { base = b; }
void Triangle::setHeight(int h) { height = h; }

Shape* Triangle::create(int x, int y, const string& color, bool fill, stringstream& ss) {
    string bs, hs;
    if (!(ss >> bs >> hs)) return nullptr;

    int b, h;
    try {
        b = stoi(bs);
    } catch (const invalid_argument&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    } catch (const out_of_range&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    }

    try {
        h = stoi(hs);
    } catch (const invalid_argument&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    } catch (const out_of_range&) {
        cout << "Wrong input format" << endl;
        return nullptr;
    }

    return new Triangle(x, y, color, fill, b, h);
}