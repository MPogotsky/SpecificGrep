#include <iostream>
#include "SpecificGrep.hpp"

SpecificGrep::SpecificGrep()
    : Options(){};

SpecificGrep::~SpecificGrep(){};

void SpecificGrep::entryPoint(int argc, char *argv[])
{
    auto optionMap = parseArgumets(&argc, &argv);
    if(optionMap.empty())
    {
        exit(EXIT_FAILURE);
    }

    if (optionMap.count("help"))
    {
        printHelp();
        exit(EXIT_SUCCESS);
    }

    if (optionMap.count("pattern"))
    {
        std::cout << "Search for: " << optionMap["pattern"].as<std::string>() << std::endl;
    } else {
        std::cerr << "Error: No search pattern is specified" << std::endl;
        std::cerr << "Use --help for help" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (optionMap.count("dir"))
    {
        std::cout << "Directory: " << optionMap["dir"].as<std::string>() << std::endl;
    }

    if (optionMap.count("log_file"))
    {
        std::cout << "Loggin to: " << optionMap["log_file"].as<std::string>() << std::endl;
    }

    if (optionMap.count("result_file"))
    {
        std::cout << "Results to: " << optionMap["result_file"].as<std::string>() << std::endl;
    }

    if (optionMap.count("threads"))
    {
        std::cout << "Number of threads: " << optionMap["threads"].as<int>() << std::endl;
    }

    Scout scout(optionMap["dir"].as<std::string>(),
                optionMap["threads"].as<int>());
    filesToProceed = scout.getFindings();

    std::cout << "Number of entries: " << filesToProceed.size() << "\n";

    exit(EXIT_SUCCESS);
}
