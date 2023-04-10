#include "FileManager.hpp"

FileManager::FileManager(){};
FileManager::~FileManager(){};

void FileManager::writeLogsToFile(const std::string& path, thread_map* logs)
{
    boost::filesystem::ofstream outputFile;
    outputFile.open(path);

    for (auto it = logs->begin(); it != logs->end(); ++it)
    {
        outputFile << it->first << ": " << it->second << std::endl;
    }
    outputFile.close();
}

void FileManager::writeResultsToFile(const std::string& path, findings_map* results)
{
    boost::filesystem::ofstream outputFile;
    outputFile.open(path);

    for (auto it = results->begin(); it != results->end(); ++it)
    {
        outputFile << it->first << ":\n";

        for (size_t i = 0; i < it->second.size(); ++i)
        {
            outputFile << it->second.at(i).lineNumber << ":";
            outputFile << it->second.at(i).lineFound << std::endl;
        }
    }
    outputFile.close();
}