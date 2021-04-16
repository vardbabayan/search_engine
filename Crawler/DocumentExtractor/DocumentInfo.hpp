#ifndef DOCUMENT_INFO
#define DOCUMENT_INFO

#include <string>

class DocumentInfo
{
private:
    std::string title;
    std::string description;
    std::string text;

public:
    DocumentInfo();
    DocumentInfo(const std::string& title, const std::string& description, const std::string& text);

    std::string getTitle();
    std::string getDescription();
    std::string getText();
};

#endif
