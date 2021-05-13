 #include "Document.hpp"

Document::Document()  
    : url{url}, title{}, description{}, text{}, time{time}
{
}

Document::Document(const std::string& url, const std::string& title, const std::string& description, const std::string& text, const std::time_t& time)
    : url{url}, title{title},  description{description}, text{text}, time{time}
{ 
}

Document::Document(int id, const std::string& url, const std::string& title, const std::string& description, const std::string& text, const std::time_t& time)
    : id{id}, url{url}, title{title},  description{description}, text{text}, time{time}
{ 
}

std::string Document::getUrl() const
{
    return url;
}

std::string Document::getTitle() const
{
    return title;
}

std::string Document::getDescription() const
{
    return description;
}

std::string Document::getText() const
{
    return text;
}