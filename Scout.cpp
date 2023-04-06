#include "Scout.hpp"

bmux Scout::coutMutex;
bmux Scout::poolMutex;
bmux Scout::findingsMutex;

Scout::Scout(const std::string &directory, int numberOfThreads)
: pool(numberOfThreads)
{
    addNewTaskToPull(boost::bind(&Scout::searchTheArea, this, fs::path(directory), boost::ref(pool)));
    pool.wait();
}

Scout::~Scout(){};

std::vector<std::string> Scout::getFindings() const
{
    return findings;
}

int Scout::getSearchedFiles() const
{
    return searchedFiles;
}

int Scout::getFilesWithPattern() const
{
    return filesWithPattern;
}

int Scout::getPatternHits() const
{
    return patternHits;
}

void Scout::addNewTaskToPull(std::function<void()> func)
{
    lock_guard poolLock(poolMutex);
    post(pool, func);
}

void Scout::searchTheArea(const fs::path &dir, asio::thread_pool &pool)
{
    // Avoid empty files and directories not to waste time and recources
    for (fs::directory_entry &entry : fs::directory_iterator(dir))
    {
        try
        {
            if (!fs::is_empty(entry.path()))
            {
                if (fs::is_directory(entry.path()))
                {
                    addNewTaskToPull(boost::bind(&Scout::searchTheArea, this, entry.path(), boost::ref(pool)));
                }
                else if (fs::is_regular_file(entry.path()))
                {
                    addNewTaskToPull(boost::bind(&Scout::searchForPattern, this, entry.path()));
                }
            }
        }
        catch (const fs::filesystem_error &ex)
        {
            if (ex.code() == boost::system::errc::permission_denied)
            {
                lock_guard coutLock(coutMutex);
                std::cout << "Permission denied: " << ex.path1() << std::endl;
            }
            continue;
        }
    }
}

void Scout::searchForPattern(const fs::path &filePath)
{
    fs::ifstream file(filePath);
    std::string line;
    std::string pattern = "dir_1";

    searchedFiles++;

    while (std::getline(file, line))
    {
        auto searcher = std::boyer_moore_searcher(pattern.begin(), pattern.end());
        auto result = std::search(line.begin(), line.end(), searcher);
        if (result != line.end())
        {
            lock_guard findingsLock(findingsMutex);
            findings.push_back(line);
            patternHits++;
        }
    }

    file.close();
}
