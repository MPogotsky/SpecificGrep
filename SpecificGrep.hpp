#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Options.hpp"

class SpecificGrep
{
public:
    SpecificGrep();
    ~SpecificGrep();

    void parseArguments(int argc, char *argv[]);

};

inline SpecificGrep entryPoint;
