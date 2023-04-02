#include <iostream>
#include "Options.hpp"

Options::Options()
:declared(declareOptions())
{};

Options::~Options(){};

options_t Options::declareOptions()
{
    options_t specificGrepOpt;

    specificGrepOpt.standard.add_options()
        ("help",            "These menu")
        ("dir,d",           po::value<std::string>()->default_value("."),
                            "Start directory (subfolders aware)")
        ("log_file,l",      po::value<std::string>()->default_value("specific_grep.log"),
                            "Name of the log file")
        ("result_file, r",  po::value<std::string>()->default_value("specific_grep.txt"),
                            "Name of the file where result is given")
        ("threads, t",      po::value<int>()->default_value(4),
                            "Number of threads in the pool")
        ("pattern",         po::value<std::string>(), "Search pattern")
    ;

    specificGrepOpt.positional.add("pattern", 1);

    return specificGrepOpt;
}

void Options::printHelp() const
{
    std::cout << "Usage: \n"
              << "\t ./specific_grep PATTERN OPTIONS \n"
              << std::endl;
    std::cout << declared.standard << std::endl;
}
