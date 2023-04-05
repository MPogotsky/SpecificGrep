#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

#include <boost/filesystem.hpp>

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

private:
    void searchTheArea(const fs::path &dir, asio::thread_pool &pool);

    static std::vector<std::string> findings;

    static bmux coutMutex;
    static bmux filesMutex;
    static bmux poolMutex;
};
