#include <ctime>
#include <string>

class LinkEntry 
{
private:    
    time_t createTime;
    bool isCrawle;
    std::string url;
    int id;
};