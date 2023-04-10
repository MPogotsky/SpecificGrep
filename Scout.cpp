#include "Scout.hpp"

bmux Scout::coutMutex;
bmux ThreadBase::poolMutex;
bmux Scout::findingsMutex;

ThreadBase::ThreadBase(int numberOfThreads)
    : pool(numberOfThreads){};

void ThreadBase::addNewTaskToPull(std::function<void()> func)
{
    lock_guard poolLock(poolMutex);
    post(pool, func);
}

Scout::Scout(const std::string &directory, int numberOfThreads)
    : ThreadBase(numberOfThreads), results(new findings_map())
{
    addNewTaskToPull(boost::bind(&Scout::searchTheArea, this, fs::path(directory), boost::ref(pool)));
    pool.wait();
}

Scout::~Scout()
{
    delete[] results;
}

void Scout::getResults() const
{
    for (auto it = results->begin(); it != results->end(); ++it)
    {
        std::cout << it->first << ": ";

        for (size_t i = 0; i < it->second.size(); ++i)
        {
            std::cout << it->second.at(i).lineNumber << ":";
            std::cout << it->second.at(i).lineFound << "\n";
        }

        std::cout << std::endl;
    }
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

    int lineCounter = 1;

    while (std::getline(file, line))
    {
        auto searcher = std::boyer_moore_searcher(pattern.begin(), pattern.end());
        auto result = std::search(line.begin(), line.end(), searcher);

        if (result != line.end())
        {
            lock_guard findingsLock(findingsMutex);

            std::string file = filePath.string();
            finding_t finding;
            finding.lineNumber = lineCounter;
            finding.lineFound = line;

            auto iter = results->find(file);
            if (iter != results->end())
            {
                iter->second.push_back(finding);
            }
            else
            {
                std::vector<finding_t> findingsNew;
                findingsNew.push_back(finding);
                results->insert(std::make_pair(filePath.string(), findingsNew));
            }

            patternHits++;
        }
        lineCounter++;
    }

    file.close();
}
