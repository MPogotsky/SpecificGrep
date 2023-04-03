#include "Scout.hpp"

bmux Scout::coutMutex;
bmux Scout::filesMutex;
bmux Scout::poolMutex;
std::vector<std::string> Scout::findings;

Scout::Scout(const std::string &directory)
    : entryDir(directory)
{
    entryPoint();
}

Scout::~Scout(){};

void Scout::entryPoint()
{
    asio::thread_pool pool(boost::thread::hardware_concurrency());
    asio::post(pool, boost::bind(&Scout::searchTheArea, this, entryDir, boost::ref(pool)));

    pool.wait();
}

std::vector<std::string> Scout::getFindings() const
{
    return findings;
}

void Scout::searchTheArea(const fs::path &dir, asio::thread_pool &pool)
{
    for (fs::directory_entry &entry : fs::directory_iterator(dir, fs::directory_options::skip_permission_denied))
    {
        if (is_directory(entry.path()) && !is_empty(entry.path()))
        {
            lock_guard pool_lock(poolMutex);
            post(pool, boost::bind(&Scout::searchTheArea, this, entry.path(), boost::ref(pool)));
        }
        else if (is_regular_file(entry.path()) && !is_empty(entry.path()))
        {
            lock_guard lock(filesMutex);
            findings.push_back(entry.path().string());
        }
    }
}
