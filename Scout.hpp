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


class Scout
{
public:
    Scout(const std::string& directory, int numberOfThreads);
    ~Scout();

    std::vector<std::string> getFindings() const;
    int getSearchedFiles() const;
    int getFilesWithPattern() const;
    int getPatternHits() const;

private:
    void searchTheArea(const fs::path &dir, asio::thread_pool &pool);
    void searchForPattern(const fs::path &file);

    std::vector<std::string> findings;
    std::atomic<int> searchedFiles;
    std::atomic<int> filesWithPattern;
    std::atomic<int> patternHits;

    asio::thread_pool pool;
    static bmux coutMutex;
    static bmux findingsMutex;
    static bmux poolMutex;
    void addNewTaskToPull(std::function<void()> func);
};
