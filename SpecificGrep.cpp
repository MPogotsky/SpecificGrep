#include <iostream>
#include "SpecificGrep.hpp"

SpecificGrep::SpecificGrep()
:declaredOptions(declareOptions())
{};

SpecificGrep::~SpecificGrep(){};

options_t SpecificGrep::declareOptions()
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

void SpecificGrep::printHelp() const
{
    std::cout << "Usage: \n" << "\t ./specific_grep PATTERN OPTIONS \n" << std::endl;
    std::cout << declaredOptions.standard << std::endl;
}

void SpecificGrep::parseArguments(int argc, char *argv[])
{
    if (argc == 1) {
        printHelp();
        exit(EXIT_FAILURE);
    }

    po::variables_map vm;
    try {
        po::command_line_parser parser(argc, argv);
        parser.options(declaredOptions.standard);
        parser.positional(declaredOptions.positional);
        po::store(parser.run(), vm);
        po::notify(vm);
    } catch (po::error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Use --help for help" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (vm.count("help")) {
        printHelp();
        exit(EXIT_SUCCESS);
    }

    if (vm.count("dir")) {
        std::cout << "Directory: " << vm["dir"].as<std::string>() << std::endl;
    }

    if (vm.count("log_file")) {
        std::cout << "Loggin to: " << vm["log_file"].as<std::string>() << std::endl;
    }

    if (vm.count("result_file")) {
        std::cout << "Results to: " << vm["result_file"].as<std::string>() << std::endl;
    }

    if (vm.count("threads")) {
        std::cout << "Number of threads: " << vm["threads"].as<int>() << std::endl;
    }

    if (vm.count("pattern")) {
        std::cout << "Search for: " << vm["pattern"].as<std::string>() << std::endl;
    }

    exit(EXIT_SUCCESS);
}
