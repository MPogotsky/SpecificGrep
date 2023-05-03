#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "Collectibles.hpp"

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

class Scout : protected ThreadBase
{
public:
    Scout() = delete;
    Scout(const std::string& directory, const std::string& pattern, int numberOfThreads = 4);
    ~Scout();

    int getSearchedFiles() const;
    int getFilesWithPattern() const;
    int getPatternHits() const;

    thread_map* getThreadLog() const;
    findings_map* getResults() const;

private:
    void searchTheArea(const fs::path &dir, asio::thread_pool &pool);
    void searchForPattern(const fs::path &file);

    void addToResults(const std::string& file, const finding_t& finding);
    void addToThreadLog(const std::string& file);

    std::string pattern;
    findings_map* results;
    thread_map* threadLog;

    std::atomic<int> searchedFiles;
    std::atomic<int> patternHits;

    static bmux coutMutex;
    static bmux threadLogMutex;
    static bmux resultsMutex;
};
