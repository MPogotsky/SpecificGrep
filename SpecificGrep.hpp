#pragma once

#include "Options.hpp"
#include "Scout.hpp"

class SpecificGrep : public Options
{
public:
    SpecificGrep();
    ~SpecificGrep();

    void entryPoint(int argc, char *argv[]);

private:
    std::vector<std::string> filesToProceed;
};

inline SpecificGrep specificGrep;
