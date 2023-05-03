#pragma once

#include <string>
#include <map>
#include <vector>

#include <boost/thread/thread.hpp>


struct InFilefinding
{
    int lineNumber;
    std::string lineFound;
};

typedef struct InFilefinding finding_t;

using findings_map = std::map<std::string, std::vector<finding_t>>;
using thread_map = std::map<boost::thread::id, std::string>;