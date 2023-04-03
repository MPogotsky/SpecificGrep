#pragma once

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
    explicit Scout(const std::string& directory);
    ~Scout();

    std::vector<std::string> getFindings() const;

private:
    void entryPoint();
    void searchTheArea(const fs::path &dir, asio::thread_pool &pool);

    fs::path entryDir;
    static std::vector<std::string> findings;

    static bmux coutMutex;
    static bmux filesMutex;
    static bmux poolMutex;
};
