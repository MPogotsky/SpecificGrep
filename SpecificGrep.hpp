#pragma once

#include "Options.hpp"

class SpecificGrep : public Options
{
public:
    SpecificGrep();
    ~SpecificGrep();

    void parseArguments(int argc, char *argv[]);
};

inline SpecificGrep entryPoint;
