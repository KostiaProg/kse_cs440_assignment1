#include "Factories.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Line.hpp"
#include <iostream>
using namespace std;

unordered_map<string, addShapeFactory> addShapeRegistry {
    {"triangle",  &Triangle::create},
    {"rectangle", &Rectangle::create},
    {"circle",    &Circle::create},
    {"line",      &Line::create}
};

void addParser(Blackboard& bb, stringstream& ss) {
    string shapeType, xs, ys, fills, color;
    if (!(ss >> shapeType >> xs >> ys >> color)) {
        cout << "Wrong input format" << endl;
        return;
    }

    // i hate parsing
    int x, y;
    try {
        x = stoi(xs);
    } catch (const invalid_argument&) {
        cout << "Wrong input format" << endl;
        return;
    } catch (const out_of_range&) {
        cout << "Wrong input format" << endl;
        return;
    }

    try {
        y = stoi(ys);
    } catch (const invalid_argument&) {
        cout << "Wrong input format" << endl;
        return;
    } catch (const out_of_range&) {
        cout << "Wrong input format" << endl;
        return;
    }
    
    bool fill = false;
    if (shapeType != "line") {
        if (!(ss >> fills)) {
            cout << "Wrong input format" << endl;
            return;
        }

        if (fills == "true" || fills == "1") fill = true;
        else if (fills != "false" && fills != "0")  {
            cout << "Wrong input format" << endl;
            return;
        }
    }


    auto it = addShapeRegistry.find(shapeType);
    if (it == addShapeRegistry.end()) {
        std::cout << "Unknown shape: " << shapeType << "\n";
        return;
    }

    bb.add(it->second(x, y, color, fill, ss));
}