#include "DocumentInfo.hpp"

explicit DocumentInfo::DocumentInfo()  : title{}, description{}, text{}
{
}

explicit DocumentInfo::DocumentInfo(const std::string& title, const std::string& description, const std::string& text)
    : title{title},  description{description}, text{text}
{ 
}

std::string DocumentInfo::getTitle() const
{
    return title;
}

std::string DocumentInfo::getDescription() const
{
    return description;
}

std::string DocumentInfo::getText() const
{
    return text;
}