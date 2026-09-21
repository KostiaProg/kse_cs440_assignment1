#pragma once
#include "Shape.hpp"
#include <sstream>

class Circle : public Shape {
private:
    int radius;

public:
    Circle();
    Circle(int r);
    Circle(int posX, int posY, int r);
    Circle(int posX, int posY, const std::string& c, int r);
    Circle(int posX, int posY, bool f, int r);
    Circle(int posX, int posY, const std::string& c, bool f, int r);

    void draw(std::vector<std::vector<char>>& canvas) const override;
    std::string info() const override;
    std::string saveInfo() const override;

    int getRadius() const;
    void setRadius(int r);

    static Shape* create(int x, int y, const std::string& color, bool fill, std::stringstream& ss);
};