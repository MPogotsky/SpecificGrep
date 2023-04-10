#include "SpecificGrep.hpp"

SpecificGrep::SpecificGrep(){};

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

    Scout scout(optionMap["dir"].as<std::string>(),
                optionMap["pattern"].as<std::string>(),
                optionMap["threads"].as<int>());

    writeLogsToFile(optionMap["log_file"].as<std::string>(), scout.getThreadLog());
    writeResultsToFile(optionMap["result_file"].as<std::string>(), scout.getResults());

    std::cout << "Searched files: " << scout.getSearchedFiles() << std::endl;
    std::cout << "Files with patterns: " << scout.getFilesWithPattern() << std::endl;
    std::cout << "Pattern hits: " << scout.getPatternHits() << std::endl;

    std::cout << "Result file: " << optionMap["result_file"].as<std::string>() << std::endl;
    std::cout << "Log file: " << optionMap["log_file"].as<std::string>() << std::endl;
    std::cout << "Used threads: " << optionMap["threads"].as<int>() << std::endl;


    exit(EXIT_SUCCESS);
}
