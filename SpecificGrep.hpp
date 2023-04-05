#pragma once

#include <iostream>
#include <memory>

#include "Options.hpp"
#include "Scout.hpp"

class SpecificGrep : public Options
{
public:
    SpecificGrep(SpecificGrep &other) = delete;
    SpecificGrep(SpecificGrep &&other) = delete;
    ~SpecificGrep();

    static SpecificGrep* getInstance()
    {
        static SpecificGrep *instance = nullptr;
        instance = new SpecificGrep();
        return instance;
    }

    void entryPoint(int argc, char *argv[]);

    void operator=(const SpecificGrep &) = delete;
private:
    SpecificGrep();
    std::vector<std::string> filesToProceed;
};

inline std::unique_ptr<SpecificGrep> specificGrep(SpecificGrep::getInstance());
