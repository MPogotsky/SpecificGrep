#pragma once

#include <filesystem>

class Scout
{
public:
    explicit Scout(const std::string& directory);
    ~Scout();
    std::vector<std::string> getFindings() const;
private:
    std::vector<std::string> findings;
    std::filesystem::path searchingArea;
    void searchTheArea();
};