#ifndef DOCUMENT
#define DOCUMENT

#include <string>
#include <ctime>

class Document
{
private:
    int id;
    std::string url;
    std::string title;
    std::string description;
    std::string text;
    std::time_t time;

public:
    Document();
    
    Document(const std::string& url, const std::string& title, 
            const std::string& description, const std::string& text);

    Document(int id, const std::string& url, const std::string& title, 
            const std::string& description, const std::string& text);

    int getId() const;
    std::string getUrl() const;
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getText() const;
};

#endif
