#include <iostream>
#include <boost/program_options.hpp>
#include "SpecificGrep.hpp"

namespace po = boost::program_options;

SpecificGrep::SpecificGrep(){};

SpecificGrep::~SpecificGrep(){};


void SpecificGrep::parseArguments(int argc, char *argv[])
{
    po::options_description desc("Options");
    desc.add_options()
        ("dir,d", po::value<std::string>()->default_value("."), "Start directory where program needs to look for files (also in subfolders)")
        ("log_file,l", po::value<std::string>()->default_value("specific_grep.log"), "Name of the log file")
        ("help", "These menu")
    ;

    po::variables_map vm;
    if (argc == 1) {
        std::cout << desc << std::endl;
        exit(EXIT_FAILURE);
    }

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (po::error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Use --help for help" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-") {
            std::cerr << "Error: invalid command line syntax" << std::endl;
            std::cerr << "Use --help for help" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (vm.count("dir")) {
        std::cout << "Directory: " << vm["dir"].as<std::string>() << std::endl;
    }

    if (vm.count("log_file")) {
        std::cout << "Output file name: " << vm["log_file"].as<std::string>() << std::endl;
    } else {
        std::cout << "Output file not set.\n";
    }

}
