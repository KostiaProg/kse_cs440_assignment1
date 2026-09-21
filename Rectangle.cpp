#include "Rectangle.hpp"
#include <iostream>
using namespace std;

Rectangle::Rectangle() : Shape(), width(0), height(0) {}
Rectangle::Rectangle(int w, int h) : Shape(), width(w), height(h) {}
Rectangle::Rectangle(int posX, int posY, int w, int h) : Shape(posX, posY), width(w), height(h) {}
Rectangle::Rectangle(int posX, int posY, const string& c, int w, int h) : Shape(posX, posY, c), width(w), height(h) {}
Rectangle::Rectangle(int posX, int posY, bool f, int w, int h) : Shape(posX, posY, f), width(w), height(h) {}
Rectangle::Rectangle(int posX, int posY, const string& c, bool f, int w, int h) : Shape(posX, posY, c, f), width(w), height(h) {}

void Rectangle::draw(vector<vector<char>>& canvas) const {
    if (width <= 0 || height <= 0) {
        cout << "Invalid rectangle dimensions." << endl;
        return;
    }

    if (fill) {
        for (int i = y; i < y + height; ++i) {
            for (int j = x; j < x + width; ++j) {
                if (i >= 0 && i < (int)canvas.size() &&
                    j >= 0 && j < (int)canvas[0].size()) {
                    canvas[i][j] = '*';
                }
            }
        }
    } else {
        for (int j = x; j < x + width; ++j) {
            if (j >= 0 && j < (int)canvas[0].size()) {
                if (y >= 0 && y < (int)canvas.size()) canvas[y][j] = '*';
                int bottom = y + height - 1;
                if (bottom >= 0 && bottom < (int)canvas.size()) canvas[bottom][j] = '*';
            }
        }

        for (int i = y; i < y + height; ++i) {
            if (i >= 0 && i < (int)canvas.size()) {
                if (x >= 0 && x < (int)canvas[0].size())
                    canvas[i][x] = '*';
                int right = x + width - 1;
                if (right >= 0 && right < (int)canvas[0].size())
                    canvas[i][right] = '*';
            }
        }
    }
}

string Rectangle::info() const {
    return Shape::info() + ", Width: " + to_string(width) + ", Height: " + to_string(height) + " - Rectangle";
}

string Rectangle::saveInfo() const {
    return "rectangle " + to_string(x) + " " + to_string(y) + " " + color + " " +
           (fill ? "true" : "false") + " " + to_string(width) + " " + to_string(height);
}

int Rectangle::getWidth() const { return width; }
int Rectangle::getHeight() const { return height; }
void Rectangle::setWidth(int w) { width = w; }
void Rectangle::setHeight(int h) { height = h; }

Shape* Rectangle::create(int x, int y, const string& color, bool fill, stringstream& ss) {
    string ws, hs;
    if (!(ss >> ws >> hs)) return nullptr;

    int w, h;
    try {
        w = stoi(ws);
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

    return new Rectangle(x, y, color, fill, w, h);
}