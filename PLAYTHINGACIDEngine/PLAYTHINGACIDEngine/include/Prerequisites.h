#pragma once
// librerias std
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <fstream>
#include <unordered_map>

//third parties
#include <SFML/Graphics.hpp>
#include "Memory\TSharedPointer.h"
#include "Memory\TWeakPointer.h"
#include "Memory\TStaticPtr.h"
#include "Memory\TUniquePtr.h"


//imgui

// MACRO for safe release of resources
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

#define MESSAGE(classObj, method, state)             \
{                                                    \
 std::ostringstream os_;                             \
 os_ << classObj << "::" << method << " : "          \
  << "[CREATION OF RESOURCE" << ": " << state "] \n";\
 std::cerr << os_.str();                             \
}

#define ERROR(classObj, method, errorMSG)                \
{                                                        \
 std::ostringstream os_;                                 \
 os_ << "ERROR : " << classObj << "::" << method << " : "\
  << "  Error in data from params [" << errorMSG"] \n";  \
 std::cerr << os_.str();                                 \
 exit(1);                                                \
}

//ENUMS
enum
 ShapeType {
 EMPTY = 0,
 CIRCLE = 1,
 RECTANGLE = 2,
 TRIANGLE = 3,
 POLYGON = 4
};