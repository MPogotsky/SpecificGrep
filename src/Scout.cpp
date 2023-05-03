#include "Scout.hpp"

bmux Scout::coutMutex;
bmux ThreadBase::poolMutex;
bmux Scout::threadLogMutex;
bmux Scout::resultsMutex;

ThreadBase::ThreadBase(int numberOfThreads)
    : pool(numberOfThreads){};

void ThreadBase::addNewTaskToPull(std::function<void()> func)
{
    lock_guard poolLock(poolMutex);
    post(pool, func);
}

Scout::Scout(const std::string &directory, const std::string& pattern, int numberOfThreads)
    : ThreadBase(numberOfThreads), pattern(pattern),
      searchedFiles({0}), patternHits({0}),
      results(new findings_map()), threadLog(new thread_map())
{
    addNewTaskToPull(boost::bind(&Scout::searchTheArea, this, fs::path(directory), boost::ref(pool)));
    pool.wait();
}

Scout::~Scout()
{
    delete[] results;
    delete[] threadLog;
}

findings_map* Scout::getResults() const
{
    return results;
}

thread_map* Scout::getThreadLog() const
{
    return threadLog;
}

int Scout::getSearchedFiles() const
{
    return searchedFiles.load();
}

int Scout::getFilesWithPattern() const
{
    return static_cast<int>(results->size());
}

int Scout::getPatternHits() const
{
    return patternHits.load();
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

void Scout::addToResults(const std::string& file, const finding_t& finding)
{
    lock_guard findingsLock(resultsMutex);
    auto iter = results->find(file);
    if (iter != results->end())
    {
        iter->second.push_back(finding);
    }
    else
    {
        results->insert(std::make_pair(file, std::vector<finding_t>{}));
        results->at(file).push_back(finding);
    }
    patternHits++;
}

void Scout::addToThreadLog(const std::string& file)
{
    lock_guard logLock(threadLogMutex);
    auto thrId = boost::this_thread::get_id();
    auto tmp = std::make_pair(thrId, file);

    auto iter = threadLog->insert(std::make_pair(thrId, file));
    if(!iter.second){
        threadLog->at(thrId)+= (", " + file);
    }
    searchedFiles++;
}

void Scout::searchForPattern(const fs::path &filePath)
{
    fs::ifstream file(filePath);
    std::string line;

    addToThreadLog(filePath.filename().string());

    int lineCounter = 1;

    while (std::getline(file, line))
    {
        auto searcher = std::boyer_moore_searcher(pattern.begin(), pattern.end());
        auto result = std::search(line.begin(), line.end(), searcher);
        if (result != line.end())
        {
            // std::string file = filePath.string();
            finding_t finding;
            finding.lineNumber = lineCounter;
            finding.lineFound = line;
            addToResults(filePath.string(), finding); 
        }
        lineCounter++;
    }
    file.close();
}
