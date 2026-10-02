#pragma once
#include "Shape.hpp"
#include <sstream>

class Triangle : public Shape {
private:
    int base;
    int height;

public:
    Triangle();
    Triangle(int b, int h);
    Triangle(int posX, int posY, int b, int h);
    Triangle(int posX, int posY, const std::string& c, int b, int h);
    Triangle(int posX, int posY, bool f, int b, int h);
    Triangle(int posX, int posY, const std::string& c, bool f, int b, int h);

    void draw(std::vector<std::vector<char>>& canvas) const override;
    std::string info() const override;
    std::string saveInfo() const override;

    int getBase() const;
    int getHeight() const;
    void setBase(int b);
    void setHeight(int h);

    static Shape* create(int x, int y, const std::string& color, bool fill, std::stringstream& ss);
    virtual void edit(std::stringstream& ss) override;
};