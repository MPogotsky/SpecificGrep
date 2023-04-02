#include <string>
#include <vector>

#include <iostream> // not necessary

#include "Scout.hpp"

Scout::Scout(const std::string &directory)
    : searchingArea(directory),
      findings({})
{
    searchTheArea();
}

Scout::~Scout(){};

void Scout::searchTheArea()
{
    for (auto const &dirEntry : std::filesystem::recursive_directory_iterator{searchingArea})
    {
        // Write down only non-empty file path`s inside findings
        if (dirEntry.is_regular_file())
        {
            if (!std::filesystem::is_empty(dirEntry.path()))
            {
                findings.push_back(dirEntry.path());
            }
        }
    }
}

std::vector<std::string> Scout::getFindings() const
{
    return findings;
}