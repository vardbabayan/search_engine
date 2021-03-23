#include <ctime>
#include <string>

class LinkEntry 
{
public:    
    time_t createTime;
    bool isCrawle;
    std::string url;
    int id;

    LinkEntry() : createTime{}, isCrawle{false}, url{""}, id{-1} {}
};