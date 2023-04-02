#pragma once

#include "Options.hpp"

class SpecificGrep : public Options
{
public:
    SpecificGrep();
    ~SpecificGrep();

    void entryPoint(int argc, char *argv[]);
};

inline SpecificGrep specificGrep;
