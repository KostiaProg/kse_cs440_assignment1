#pragma once
#include "Shape.hpp"
#include <sstream>

class Rectangle : public Shape {
private:
    int width;
    int height;

public:
    Rectangle();
    Rectangle(int w, int h);
    Rectangle(int posX, int posY, int w, int h);
    Rectangle(int posX, int posY, const std::string& c, int w, int h);
    Rectangle(int posX, int posY, bool f, int w, int h);
    Rectangle(int posX, int posY, const std::string& c, bool f, int w, int h);

    void draw(std::vector<std::vector<char>>& canvas) const override;
    std::string info() const override;
    std::string saveInfo() const override;
    void edit(std::stringstream& ss) override;

    int getWidth() const;
    int getHeight() const;
    void setWidth(int w);
    void setHeight(int h);

    static Shape* create(int x, int y, const std::string& color, bool fill, std::stringstream& ss);
};