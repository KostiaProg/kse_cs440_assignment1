#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_map>
#include <vector>
#include <string>

#include <functional>

using namespace std;
class Blackboard;
void addParser(Blackboard& bb, stringstream& ss);


// Shapes: triangle, rectangle, circle, line, MB polygon
class Shape {
protected:
    int x;
    int y;

    string color; // MB ACTUAL COLOR
    bool fill;
public:
    Shape() : color("black"), fill(false), x(0), y(0) {}
    Shape(int posX, int posY) : color("black"), fill(false), x(posX), y(posY) {}
    Shape(int posX, int posY, const string& c) : x(posX), y(posY), color(c), fill(false) {}
    Shape(int posX, int posY, bool f) : x(posX), y(posY), color("black"), fill(f) {}
    Shape(int posX, int posY, const string& c, bool f) : x(posX), y(posY), color(c), fill(f) {}

    virtual void draw(vector<vector<char>>& canvas) const = 0;

    virtual string info() const {
        return "Position: (" + to_string(x) + ", " + to_string(y) + "), Color: " + color + ", Fill: " + (fill ? "Yes" : "No");
    };

    virtual string saveInfo() const = 0;

    // getters
    int getX() const { return x; }
    int getY() const { return y; }
    string getColor() const { return color; }
    bool getFill() const { return fill; }

    // setters
    void setX(int posX) { x = posX; }
    void setY(int posY) { y = posY; }
    void setColor(const string& c) { color = c; }
    void setFill(bool f) { fill = f; }
};


class Triangle : public Shape {
private:
    int base;
    int height;
public:
    Triangle() : Shape(), base(0), height(0) {}
    Triangle(int b, int h) : Shape(), base(b), height(h) {}
    Triangle(int posX, int posY, int b, int h) : Shape(posX, posY), base(b), height(h) {}
    Triangle(int posX, int posY, const string& c, int b, int h) : Shape(posX, posY, c), base(b), height(h) {}
    Triangle(int posX, int posY, bool f, int b, int h) : Shape(posX, posY, f), base(b), height(h) {}
    Triangle(int posX, int posY, const string& c, bool f, int b, int h) : Shape(posX, posY, c, f), base(b), height(h) {}

    void draw(vector<vector<char>>& canvas) const override {
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

                // full base
                if (i == height - 1) {
                    for (int px = left; px <= right; ++px) {
                        if (px >= 0 && px < (int)canvas[0].size()) {
                            canvas[py][px] = '*';
                        }
                    }
                }
            }
            else {
                for (int px = left; px <= right; ++px) {
                    if (px >= 0 && px < (int)canvas[0].size()) canvas[py][px] = '*';
                }
            }
        } 
    }

    string info() const override {
        return Shape::info() + ", Base: " + to_string(base) + ", Height: " + to_string(height) + " - Triangle";
    }

    string saveInfo() const override {
        return "triangle " + to_string(x) + " " + to_string(y) + " " + color + " " + (fill ? "true" : "false") + " " + to_string(base) + " " + to_string(height);
    }

    // getters
    int getBase() const { return base; }
    int getHeight() const { return height; }

    // setters
    void setBase(int b) { base = b; }
    void setHeight(int h) { height = h; }

    // statics for factories
    static Shape* create(int x, int y, const string& color, bool fill, stringstream& ss) {
        string bs, hs;
        if (!(ss >> bs >> hs)) return nullptr;

        size_t check;
        int b = stoi(bs, &check);
        if (check != bs.size()) {
            cout << "Wrong input format" << endl;
            return nullptr;
        }

        size_t check2;
        int h = stoi(hs, &check2);
        if (check2 != hs.size()) {
            cout << "Wrong input format" << endl;
            return nullptr;
        }

        return new Triangle(x, y, color, fill, b, h);
    }
};

class Rectangle : public Shape {
private:
    int width;
    int height;
public:
    Rectangle() : Shape(), width(0), height(0) {}
    Rectangle(int w, int h) : Shape(), width(w), height(h) {}
    Rectangle(int posX, int posY, int w, int h) : Shape(posX, posY), width(w), height(h) {}
    Rectangle(int posX, int posY, const string& c, int w, int h) : Shape(posX, posY, c), width(w), height(h) {}
    Rectangle(int posX, int posY, bool f, int w, int h) : Shape(posX, posY, f), width(w), height(h) {}
    Rectangle(int posX, int posY, const string& c, bool f, int w, int h) : Shape(posX, posY, c, f), width(w), height(h) {}

    void draw(vector<vector<char>>& canvas) const override {
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
        }
        else {
            for (int j = x; j < x + width; ++j) {
                if (j >= 0 && j < (int)canvas[0].size()) {
                    if (y >= 0 && y < (int)canvas.size()) canvas[y][j] = '*';
                    int bottom = y + height - 1;
                    if (bottom >= 0 && bottom < (int)canvas.size()) canvas[bottom][j] = '*';
                }
            }

            // left and right vertical edges
            for (int i = y; i < y + height; ++i) {
                if (i >= 0 && i < (int)canvas.size()) {
                    // left
                    if (x >= 0 && x < (int)canvas[0].size())
                        canvas[i][x] = '*';
                    // right
                    int right = x + width - 1;
                    if (right >= 0 && right < (int)canvas[0].size())
                        canvas[i][right] = '*';
                }
            }
        }
    }

    string info() const override {
        return Shape::info() + ", Width: " + to_string(width) + ", Height: " + to_string(height) + " - Rectangle";
    }

    string saveInfo() const override {
        return "rectangle "  + to_string(x) + " " + to_string(y) + " " + color + " " + (fill ? "true" : "false") + " " + to_string(width) + " " + to_string(height);
    }

    // getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // setters
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }

    // static for factories
    static Shape* create(int x, int y, const string& color, bool fill, stringstream& ss) {
        string ws, hs;
        if (!(ss >> ws >> hs)) return nullptr;

        size_t check;
        int w = stoi(ws, &check);
        if (check != ws.size()) {
            cout << "Wrong input format" << endl;
            return nullptr;
        }

        size_t check2;
        int h = stoi(hs, &check2);
        if (check2 != hs.size()) {
            cout << "Wrong input format" << endl;
            return nullptr;
        }

        return new Rectangle(x, y, color, fill, w, h);
    }
};

class Circle : public Shape {
private:
    int radius;
public:
    Circle() : Shape(), radius(0) {}
    Circle(int r) : Shape(), radius(r) {}
    Circle(int posX, int posY, int r) : Shape(posX, posY), radius(r) {}
    Circle(int posX, int posY, const string& c, int r) : Shape(posX, posY, c), radius(r) {}
    Circle(int posX, int posY, bool f, int r) : Shape(posX, posY, f), radius(r) {}
    Circle(int posX, int posY, const string& c, bool f, int r) : Shape(posX, posY, c, f), radius(r) {}

    void draw(vector<vector<char>>& canvas) const override {
        if (radius <= 0) {
            cout << "Invalid circle radius." << endl;
            return;
        }

        int rSquare = radius * radius;
        for (int i = -radius; i <= radius; ++i) {
            for (int j = -radius; j <= radius; ++j) {
                int sumSquares = i * i + j * j;

                bool onCircle = false;
                if (fill) onCircle = (sumSquares <= rSquare);
                else onCircle = (sumSquares >= rSquare - radius) && (sumSquares <= rSquare + radius);

                if (onCircle) {
                    int posX = x + j;
                    int posY = y + i;
                    if (posX >= 0 && posX < (int)canvas[0].size() && posY >= 0 && posY < (int)canvas.size()) {
                        canvas[posY][posX] = '*';
                    }
                }
            }
        }
    }

    string info() const override {
        return Shape::info() + ", Radius: " + to_string(radius) + " - Circle";
    }
    \
    string saveInfo() const override {
        return "circle "  + to_string(x) + " " + to_string(y) + " " + color + " " + (fill ? "true" : "false") + " " + to_string(radius);
    }

    // getters
    int getRadius() const { return radius; }

    // setters
    void setRadius(int r) { radius = r; }

    // static for factories
    static Shape* create(int x, int y, const string& color, bool fill, stringstream& ss) {
        string rs;
        if (!(ss >> rs)) return nullptr;

        size_t check;
        int r = stoi(rs, &check);
        if (check != rs.size()) {
            cout << "Wrong input format" << endl;
            return nullptr;
        }


        return new Circle(x, y, color, fill, r);
    }
};

class Line : public Shape {
private:
    int x2;
    int y2;
public:
    Line() : Shape(), x2(0), y2(0) {}
    Line(int x1, int y1, int x2, int y2) : Shape(x1, y1), x2(x2), y2(y2) {}
    Line(int x1, int y1, const string& c, int x2, int y2) : Shape(x1, y1, c, false), x2(x2), y2(y2) {}
    Line(int x1, int y1, const string& c, bool fill, int x2, int y2) : Shape(x1, y1, c, false), x2(x2), y2(y2) {}

    void draw(vector<vector<char>>& canvas) const override {
        int x0 = x;
        int y0 = y;
        int x1 = x2;
        int y1 = y2;

        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (x0 != x1 || y0 != y1) {
            if (x0 >= 0 && x0 < (int)canvas[0].size() && y0 >= 0 && y0 < (int)canvas.size()) {
                canvas[y0][x0] = '*';
            }

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }

    string info() const override {
        return Shape::info() + ", End Point: (" + to_string(x2) + ", " + to_string(y2) + ") - Line";
    }

    string saveInfo() const override {
        return "line "  + to_string(x) + " " + to_string(y) + " " + color + " " + (fill ? "true" : "false") + " " + to_string(x2) + " " + to_string(y2);
    }

    // getters
    int getX2() const { return x2; }
    int getY2() const { return y2; }

    // setters
    void setX2(int posX2) { x2 = posX2; }
    void setY2(int posY2) { y2 = posY2; }

    // static for factories
    static Shape* create(int x, int y, const string& color, bool fill, stringstream& ss) {
        string X2s, Y2s;
        if (!(ss >> X2s >> Y2s)) return nullptr;

        size_t check;
        int X2 = stoi(X2s, &check);
        if (check != X2s.size()) {
            cout << "Wrong input format" << endl;
            return nullptr;
        }

        size_t check2;
        int Y2 = stoi(Y2s, &check2);
        if (check2 != Y2s.size()) {
            cout << "Wrong input format" << endl;
            return nullptr;
        }

        return new Line(x, y, color, X2, Y2);
    }
};



class Blackboard {
private:
    const int width = 100;
    const int height = 25;

    vector<Shape*> shapes;
    vector<vector<char>> canvas;
    int selectedShape_id = -1;

    string fileName = "shapes.txt";

public:
    Blackboard(const string& FileName = "shapes.txt", const int W = 100, const int H = 25) : width(W), height(H), fileName(FileName) {
        canvas.resize(height, vector<char>(width, ' '));
    }
    ~Blackboard() {
        clear();
    }

    void draw() {
        for (auto& shape : shapes) if (shape) shape->draw(canvas);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) cout << canvas[y][x];
            cout << endl;
        }

        for (auto& row : canvas) fill(row.begin(), row.end(), ' ');
    }

    // info
    void list() const {
        for (size_t i = 0; i < shapes.size(); ++i) {
            if (!shapes[i]) continue;
            cout << i << " " << shapes[i]->info() << endl;
        }
    }

    void getShapes() const {
        cout << "Shapes on the blackboard:" << endl;
        cout << "triangle: x, y, color, fill, base, height" << endl;
        cout << "rectangle: x, y, color, fill, width, height" << endl;
        cout << "circle: x, y, color, fill, radius" << endl;
        cout << "line: x1, y1, color, x2, y2" << endl;
    }


    // edit bb
    void add (Shape* shape) {
        if (shape->getX() < 0 || shape->getX() >= width || shape->getY() < 0 || shape->getY() >= height) {
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

    void remove() {
        if (selectedShape_id != -1) {
            delete shapes[selectedShape_id];
            shapes[selectedShape_id] = nullptr;
            selectedShape_id = -1;
        }
        else cout << "No shape selected" << endl;
    }

    void clear() {
        for (auto& shape : shapes) if (shape) delete shape;
        shapes.clear();
        selectedShape_id = -1;
    }

    // edit shapes
    void changeFill() {
        if (selectedShape_id != -1) shapes[selectedShape_id]->setFill(!shapes[selectedShape_id]->getFill());
        else cout << "No shape selected" << endl;
    }

    void paint(const string& color) {
        if (selectedShape_id != -1) shapes[selectedShape_id]->setColor(color);
        else cout << "No shape selected" << endl;
    }


    void move(int x, int y) {
        if (selectedShape_id != -1) {
            shapes[selectedShape_id]->setX(x);
            shapes[selectedShape_id]->setY(y);
        }
        else cout << "No shape selected" << endl;
    }

    void editParams(stringstream& stream) {
        if (selectedShape_id == -1) {
            cout << "No shape selected" << endl;
            return;
        }

        if (auto tria = dynamic_cast<Triangle*>(shapes[selectedShape_id])) {
            int b, h;
            if (stream >> b >> h) {
                tria->setBase(b);
                tria->setHeight(h);
            }
            else cout << "Wrong input format";
        }
        else if (auto rect = dynamic_cast<Rectangle*>(shapes[selectedShape_id])) {
            int w, h;
            if (stream >> w >> h) {
                rect->setWidth(w);
                rect->setHeight(h);
            }
            else cout << "Wrong input format";
        }
        else if (auto circle = dynamic_cast<Circle*>(shapes[selectedShape_id])) {
            int r;
            if (stream >> r) {
                circle->setRadius(r);
            }
            else cout << "Wrong input format";
        }
        else if (auto line = dynamic_cast<Line*>(shapes[selectedShape_id])) {
            int x2, y2;
            if (stream >> x2 >> y2) {
                line->setX2(x2);
                line->setY2(y2);
            }
            else cout << "Wrong input format";
        }
        else cout << "Wrong input format";
    }

    // select shape
    void select(int id) {
        if (id >= 0 && id < shapes.size() && shapes[id]) selectedShape_id = id;
        else cout << "Invalid shape ID" << endl;
    }

    void select(int x, int y) {
        bool found = false;
        for (int i = 0; i < shapes.size(); ++i) {
            if (!shapes[i]) continue;

            if (shapes[i]->getX() == x && shapes[i]->getY() == y) {
                selectedShape_id = i;
                found = true;
                break;
            }
        }
        if (!found) cout << "Invalid coordinates" << endl;
    }

    // file operations
    void save() {
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

    void load() {
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
};


// FACTORIES
using addShapeFactory = function<Shape*(int, int, const string&, bool, stringstream&)>;
unordered_map<string, addShapeFactory> addShapeRegistry {
    {"triangle", &Triangle::create},
    {"rectangle", &Rectangle::create},
    {"circle", &Circle::create},
    {"line", &Line::create}
};

// FNS
void addParser(Blackboard& bb, stringstream& ss) {
    string shapeType, xs, ys, fills, color;
    if (!(ss >> shapeType >> xs >> ys >> color)) {
        cout << "Wrong input format" << endl;
        return;
    }

    // i hate parsing
    size_t check;
    int x = stoi(xs, &check);
    if (check != xs.size()) {
        cout << "Wrong input format" << endl;
        return;
    }

    size_t check2;
    int y = stoi(ys, &check2);
    if (check2 != ys.size()) {
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

bool handleCommands(Blackboard& bb, string& command) {
    if (command == "") return true;

    stringstream ss(command);
    string action;
    ss >> action;

    if (action == "draw") bb.draw();
    else if (action == "list") bb.list();
    else if (action == "shapes") bb.getShapes();
    else if (action == "add") addParser(bb, ss);
    else if (action == "remove") bb.remove();
    else if (action == "clear") bb.clear();
    else if (action == "fill") bb.changeFill();
    else if (action == "paint") {
        string color;
        if (!(ss >> color)) {
            cout << "Wrong input format" << endl;
            return true;
        }
        bb.paint(color);

        string fills;
        if (ss >> fills && (fills == "true" || fills == "1")) bb.changeFill();
    }
    else if (action == "move") {
        string xs, ys;
        if (!(ss >> xs >> ys)) {
            cout << "Wrong input format" << endl;
            return true;
        }

        // i hate parsing
        size_t check;
        int x = stoi(xs, &check);
        if (check != xs.size()) {
            cout << "Wrong input format" << endl;
            return true;
        }

        size_t check2;
        int y = stoi(ys, &check2);
        if (check2 != ys.size()) {
            cout << "Wrong input format" << endl;
            return true;
        }

        bb.move(x, y);
    }
    else if (action == "edit") bb.editParams(ss);
    else if (action == "select") {
        string xids, ys;
        if (!(ss >> xids)) {
            cout << "Wrong input format" << endl;
            return true;
        }

        // i hate parsing
        size_t check = 0;
        int xid = stoi(xids, &check);
        if (check != xids.size()) {
            cout << "Wrong input format" << endl;
            return true;
        }

        if (!(ss >> ys)) bb.select(xid);
        else {
            size_t check2;
            int y = stoi(ys, &check2);
            if (check2 != ys.size()) {
                cout << "Wrong input format" << endl;
                return true;
            }
            bb.select(xid, y);
        }
    }
    else if (action == "save") bb.save();
    else if (action == "load") bb.load();
    else if (action == "quit" || action == "q") return false;
    else cout << "Unkown action" << endl;

    return true;
}

int main() {
    Blackboard bb;
    
    bool work = true;
    while (work) {
        string command;
        if (!std::getline(std::cin, command)) break;  
        work = handleCommands(bb, command);
    }
    
    return 0;
}