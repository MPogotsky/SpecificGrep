#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <fstream>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace fs = boost::filesystem;
namespace asio = boost::asio;

using bmux = boost::mutex;
using lock_guard = boost::lock_guard<bmux>;


class ThreadBase
{
public:
    ThreadBase(int numberOfThreads);
    asio::thread_pool pool;
    static bmux poolMutex;

    void addNewTaskToPull(std::function<void()> func);
};

struct InFilefinding
{
    int lineNumber;
    std::string lineFound;
};

typedef struct InFilefinding finding_t;

using findings_map = std::map<std::string, std::vector<finding_t>>;

class Scout : protected ThreadBase
{
public:
    Scout(const std::string& directory, int numberOfThreads);
    ~Scout();

    void getResults() const;
    int getSearchedFiles() const;
    int getFilesWithPattern() const;
    int getPatternHits() const;

private:
    void searchTheArea(const fs::path &dir, asio::thread_pool &pool);
    void searchForPattern(const fs::path &file);

    // std::unique_ptr<std::vector<finding_t>> results;
    findings_map* results;
    std::atomic<int> searchedFiles;
    std::atomic<int> filesWithPattern;
    std::atomic<int> patternHits;

    static bmux coutMutex;
    static bmux findingsMutex;
};
