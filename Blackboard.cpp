#include "Blackboard.hpp"
#include "Factories.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Line.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

Blackboard::Blackboard(const string& FileName, int W, int H)
    : width(W), height(H), fileName(FileName), selectedShape_id(-1) {
    canvas.resize(height, vector<char>(width, ' '));
}

Blackboard::~Blackboard() {
    clear();
}

void Blackboard::draw() {
    for (auto& shape : shapes)
        if (shape) shape->draw(canvas);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x)
            cout << canvas[y][x];
        cout << endl;
    }

    for (auto& row : canvas)
        fill(row.begin(), row.end(), ' ');
}

void Blackboard::list() const {
    for (size_t i = 0; i < shapes.size(); ++i) {
        if (!shapes[i]) continue;
        cout << i << " " << shapes[i]->info() << endl;
    }
}

void Blackboard::getShapes() const {
    cout << "Shapes on the blackboard:" << endl;
    cout << "triangle: x, y, color, fill, base, height" << endl;
    cout << "rectangle: x, y, color, fill, width, height" << endl;
    cout << "circle: x, y, color, fill, radius" << endl;
    cout << "line: x1, y1, color, x2, y2" << endl;
}

void Blackboard::add(Shape* shape) {
    if (!shape) return;

    if (shape->getX() < 0 || shape->getX() >= width ||
        shape->getY() < 0 || shape->getY() >= height) {
        cout << "Outside of blackboard" << endl;
        delete shape;
        return;
    }

    bool found = false;
    for (auto& s : shapes) {
        if (!s) {
            s = shape;
            found = true;
            break;
        }
    }

    if (!found) shapes.push_back(shape);
}

void Blackboard::remove() {
    if (selectedShape_id != -1) {
        delete shapes[selectedShape_id];
        shapes[selectedShape_id] = nullptr;
        selectedShape_id = -1;
    } else {
        cout << "No shape selected" << endl;
    }
}

void Blackboard::clear() {
    for (auto& shape : shapes)
        if (shape) delete shape;
    shapes.clear();
    selectedShape_id = -1;
}

void Blackboard::changeFill() {
    if (selectedShape_id != -1)
        shapes[selectedShape_id]->setFill(!shapes[selectedShape_id]->getFill());
    else
        cout << "No shape selected" << endl;
}

void Blackboard::paint(const string& color) {
    if (selectedShape_id != -1)
        shapes[selectedShape_id]->setColor(color);
    else
        cout << "No shape selected" << endl;
}

void Blackboard::move(int x, int y) {
    if (selectedShape_id != -1) {
        shapes[selectedShape_id]->setX(x);
        shapes[selectedShape_id]->setY(y);
    } else {
        cout << "No shape selected" << endl;
    }
}

void Blackboard::editParams(stringstream& stream) {
    if (selectedShape_id == -1) {
        cout << "No shape selected" << endl;
        return;
    }

    if (auto* tria = dynamic_cast<Triangle*>(shapes[selectedShape_id])) {
        int b, h;
        if (stream >> b >> h) {
            tria->setBase(b);
            tria->setHeight(h);
        } else cout << "Wrong input format" << endl;
    }
    else if (auto* rect = dynamic_cast<Rectangle*>(shapes[selectedShape_id])) {
        int w, h;
        if (stream >> w >> h) {
            rect->setWidth(w);
            rect->setHeight(h);
        } else cout << "Wrong input format" << endl;
    }
    else if (auto* circ = dynamic_cast<Circle*>(shapes[selectedShape_id])) {
        int r;
        if (stream >> r) {
            circ->setRadius(r);
        } else cout << "Wrong input format" << endl;
    }
    else if (auto* line = dynamic_cast<Line*>(shapes[selectedShape_id])) {
        int x2, y2;
        if (stream >> x2 >> y2) {
            line->setX2(x2);
            line->setY2(y2);
        } else cout << "Wrong input format" << endl;
    }
    else {
        cout << "Wrong input format" << endl;
    }
}

void Blackboard::select(int id) {
    if (id >= 0 && id < (int)shapes.size() && shapes[id])
        selectedShape_id = id;
    else
        cout << "Invalid shape ID" << endl;
}

void Blackboard::select(int x, int y) {
    bool found = false;
    for (size_t i = 0; i < shapes.size(); ++i) {
        if (!shapes[i]) continue;
        if (shapes[i]->getX() == x && shapes[i]->getY() == y) {
            selectedShape_id = static_cast<int>(i);
            found = true;
            break;
        }
    }
    if (!found) cout << "Invalid coordinates" << endl;
}

void Blackboard::save() {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Couldn't open the file " << fileName << endl;
        return;
    }

    for (auto& shape : shapes) {
        if (!shape) continue;
        file << shape->saveInfo() << endl;
    }
    file.close();
}

void Blackboard::load() {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Couldn't open the file " << fileName << endl;
        return;
    }

    clear();

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        addParser(*this, ss);
    }
    file.close();
}