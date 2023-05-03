#pragma once

#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

typedef struct opt
{
    opt() : standard("Options"){};
    po::options_description standard;
    po::positional_options_description positional;
} options;

typedef options options_t;

class Options
{
public:
    Options();
    virtual ~Options();

protected:
    po::variables_map parseArgumets(int *argc, char ***argv);
    void printHelp() const;

private:
    const options_t declared;
    options_t declareOptions();
};
