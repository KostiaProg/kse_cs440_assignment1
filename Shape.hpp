#pragma once
#include <string>
#include <vector>
#include <iostream>

class Shape {
protected:
    int x, y;
    std::string color;
    bool fill;

public:
    Shape();
    Shape(int posX, int posY);
    Shape(int posX, int posY, const std::string& c);
    Shape(int posX, int posY, bool f);
    Shape(int posX, int posY, const std::string& c, bool f);
    virtual ~Shape() = default;

    virtual void draw(std::vector<std::vector<char>>& canvas) const = 0;
    virtual std::string info() const;
    virtual std::string saveInfo() const = 0;

    // getters / setters
    int getX() const;
    int getY() const;
    std::string getColor() const;
    bool getFill() const;

    void setX(int posX);
    void setY(int posY);
    void setColor(const std::string& c);
    void setFill(bool f);
};