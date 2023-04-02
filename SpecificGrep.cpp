#include <iostream>
#include "SpecificGrep.hpp"

SpecificGrep::SpecificGrep()
    : Options(){};

SpecificGrep::~SpecificGrep(){};

void SpecificGrep::entryPoint(int argc, char *argv[])
{
    if (argc == 1)
    {
        printHelp();
        exit(EXIT_FAILURE);
    }

    po::variables_map vm;
    try
    {
        po::command_line_parser parser(argc, argv);
        parser.options(declared.standard);
        parser.positional(declared.positional);
        po::store(parser.run(), vm);
        po::notify(vm);
    }
    catch (po::error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Use --help for help" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (vm.count("help"))
    {
        printHelp();
        exit(EXIT_SUCCESS);
    }

    if (vm.count("dir"))
    {
        std::cout << "Directory: " << vm["dir"].as<std::string>() << std::endl;
    }

    if (vm.count("log_file"))
    {
        std::cout << "Loggin to: " << vm["log_file"].as<std::string>() << std::endl;
    }

    if (vm.count("result_file"))
    {
        std::cout << "Results to: " << vm["result_file"].as<std::string>() << std::endl;
    }

    if (vm.count("threads"))
    {
        std::cout << "Number of threads: " << vm["threads"].as<int>() << std::endl;
    }

    if (vm.count("pattern"))
    {
        std::cout << "Search for: " << vm["pattern"].as<std::string>() << std::endl;
    }

    exit(EXIT_SUCCESS);
}
