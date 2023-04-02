#pragma once

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
    const options_t declared;
    void printHelp() const;

private:
    options_t declareOptions();
};
