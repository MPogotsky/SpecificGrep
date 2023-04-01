#pragma once


class SpecificGrep
{
public:
    SpecificGrep();
    ~SpecificGrep();

    void parseArguments(int argc, char *argv[]);

};

inline SpecificGrep entryPoint;
