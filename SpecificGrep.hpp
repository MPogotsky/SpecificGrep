#pragma once

#include <boost/program_options.hpp>

namespace po = boost::program_options;

typedef struct opt
{
    opt():standard("Options"){};
    po::options_description standard;
    po::positional_options_description positional;
} options;

typedef options options_t;

class SpecificGrep
{
public:
    SpecificGrep();
    ~SpecificGrep();

    void parseArguments(int argc, char *argv[]);
private:
    const options_t declaredOptions;

    options_t declareOptions();
    void printHelp() const;
};

inline SpecificGrep entryPoint;
