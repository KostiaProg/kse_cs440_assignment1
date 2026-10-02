#pragma once
#include "Shape.hpp"
#include <sstream>

class Line : public Shape {
private:
    int x2;
    int y2;

public:
    Line();
    Line(int x1, int y1, int x2, int y2);
    Line(int x1, int y1, const std::string& c, int x2, int y2);
    Line(int x1, int y1, const std::string& c, bool fill, int x2, int y2);

    void draw(std::vector<std::vector<char>>& canvas) const override;
    std::string info() const override;
    std::string saveInfo() const override;
    void edit(std::stringstream& ss) override;

    int getX2() const;
    int getY2() const;
    void setX2(int posX2);
    void setY2(int posY2);

    static Shape* create(int x, int y, const std::string& color, bool fill, std::stringstream& ss);
};