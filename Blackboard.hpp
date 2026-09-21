#pragma once
#include "Shape.hpp"
#include <vector>
#include <string>
#include <sstream>

class Blackboard {
private:
    const int width;
    const int height;
    std::vector<Shape*> shapes;
    std::vector<std::vector<char>> canvas;
    int selectedShape_id = -1;
    std::string fileName;

public:
    Blackboard(const std::string& FileName = "shapes.txt", int W = 100, int H = 25);
    ~Blackboard();

    void draw();
    void list() const;
    void getShapes() const;

    void add(Shape* shape);
    void remove();
    void clear();

    void changeFill();
    void paint(const std::string& color);
    void move(int x, int y);
    void editParams(std::stringstream& stream);

    void select(int id);
    void select(int x, int y);

    void save();
    void load();
};