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
    explicit DocumentInfo();
    explicit DocumentInfo(const std::string& title, const std::string& description, const std::string& text);

    std::string getTitle() const;
    std::string getDescription() const;
    std::string getText() const;
};

#endif
