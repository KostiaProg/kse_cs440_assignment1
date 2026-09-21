#include "Blackboard.hpp"
#include "Factories.hpp"
#include <iostream>
#include <sstream>
using namespace std;

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
        int x, y;
        try {
            x = stoi(xs);
        } catch (const invalid_argument&) {
            cout << "Wrong input format" << endl;
            return true;
        } catch (const out_of_range&) {
            cout << "Wrong input format" << endl;
            return true;
        }

        try {
            y = stoi(ys);
        } catch (const invalid_argument&) {
            cout << "Wrong input format" << endl;
            return true;
        } catch (const out_of_range&) {
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
        int xid, y;
        try {
            xid = stoi(xids);
        } catch (const invalid_argument&) {
            cout << "Wrong input format" << endl;
            return true;
        } catch (const out_of_range&) {
            cout << "Wrong input format" << endl;
            return true;
        }

        if (!(ss >> ys)) bb.select(xid);
        else {
            try {
                y = stoi(ys);
            } catch (const invalid_argument&) {
                cout << "Wrong input format" << endl;
                return true;
            } catch (const out_of_range&) {
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