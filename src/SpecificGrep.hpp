#pragma once

#include <iostream>
#include <memory>

#include "Options.hpp"
#include "FileManager.hpp"
#include "Scout.hpp"

class SpecificGrep : public Options, public FileManager
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
};

inline std::unique_ptr<SpecificGrep> specificGrep(SpecificGrep::getInstance());
