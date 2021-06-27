#ifndef WEB_SITE
#define WEB_SITE

#include <string>
#include <vector>
#include <ctime>

class Website
{
private:
    int id;
    std::string domain;
    std::string homepage;
    std::time_t updated;

public:
    Website();
    Website(const std::string& domain, const std::string& homepage);
    Website(const std::string& domain, const std::string& homepage, std::time_t time);
    Website(int id, const std::string& domain, const std::string& homepage);
    
    int getId() const;
    std::string getDomain() const;
    std::string getHomePage() const;
    std::time_t getLastCrawleTime() const;
};

#endif
