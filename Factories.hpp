#pragma once
#include "Shape.hpp"
#include "Blackboard.hpp"
#include <functional>
#include <unordered_map>
#include <sstream>
#include <string>

using addShapeFactory = std::function<Shape*(int, int, const std::string&, bool, std::stringstream&)>;

extern std::unordered_map<std::string, addShapeFactory> addShapeRegistry;

void addParser(Blackboard& bb, std::stringstream& ss);