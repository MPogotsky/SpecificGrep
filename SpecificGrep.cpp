#include <iostream>
#include "SpecificGrep.hpp"

SpecificGrep::SpecificGrep()
    : Options(){};

SpecificGrep::~SpecificGrep(){};

void SpecificGrep::entryPoint(int argc, char *argv[])
{
    auto option = parseArgumets(&argc, &argv);

    if (option.count("help"))
    {
        printHelp();
        exit(EXIT_SUCCESS);
    }

    if (option.count("pattern"))
    {
        std::cout << "Search for: " << option["pattern"].as<std::string>() << std::endl;
    } else {
        std::cerr << "Error: No search pattern is specified" << std::endl;
        std::cerr << "Use --help for help" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (option.count("dir"))
    {
        std::cout << "Directory: " << option["dir"].as<std::string>() << std::endl;
    }

    if (option.count("log_file"))
    {
        std::cout << "Loggin to: " << option["log_file"].as<std::string>() << std::endl;
    }

    if (option.count("result_file"))
    {
        std::cout << "Results to: " << option["result_file"].as<std::string>() << std::endl;
    }

    if (option.count("threads"))
    {
        std::cout << "Number of threads: " << option["threads"].as<int>() << std::endl;
    }

    exit(EXIT_SUCCESS);
}
