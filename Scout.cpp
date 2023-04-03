#include "Scout.hpp"

bmux Scout::coutMutex;
bmux Scout::filesMutex;
bmux Scout::poolMutex;
std::vector<std::string> Scout::findings;

Scout::Scout(const std::string &directory, int numberOfThreads)
{
    asio::thread_pool pool(numberOfThreads);
    asio::post(pool, boost::bind(&Scout::searchTheArea, this, fs::path(directory), boost::ref(pool)));

    pool.wait();
}

Scout::~Scout(){};

std::vector<std::string> Scout::getFindings() const
{
    return findings;
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
                    lock_guard poolLock(poolMutex);
                    post(pool, boost::bind(&Scout::searchTheArea, this, entry.path(), boost::ref(pool)));
                }
                else if (fs::is_regular_file(entry.path()))
                {
                    lock_guard poolLock(filesMutex);
                    findings.push_back(entry.path().string());
                }
            }
        }
        catch (const fs::filesystem_error &ex)
        {
            if (ex.code() == boost::system::errc::permission_denied)
            {
                lock_guard poolLock(coutMutex);
                std::cout << "Permission denied: " << ex.path1() << std::endl;
            }
            continue;
        }
    }
}
