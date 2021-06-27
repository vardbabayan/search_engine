 #include "Document.hpp"

Document::Document()  
    : url{url}, title{}, description{}, text{}, time{time}
{
}

Document::Document(const std::string& url, const std::string& title, 
                    const std::string& description, const std::string& text)
    : url{url}, title{title},  description{description}, text{text}
{ 
}

Document::Document(int id, const std::string& url, const std::string& title, 
                    const std::string& description, const std::string& text)
    : id{id}, url{url}, title{title},  description{description}, text{text}
{ 
}


int Document::getId() const
{
    return id;
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