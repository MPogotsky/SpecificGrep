#pragma once

#include <boost/filesystem.hpp>
#include "Collectibles.hpp"

class FileManager
{
public:
    FileManager();
    virtual ~FileManager();

    void writeLogsToFile(const std::string& path, thread_map* logs);
    void writeResultsToFile(const std::string& path, findings_map* results);
};
