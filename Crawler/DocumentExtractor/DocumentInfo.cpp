#include "DocumentInfo.hpp"

DocumentInfo::DocumentInfo()  : title{}, description{}, text{}
{
}

DocumentInfo::DocumentInfo(const std::string& title, const std::string& description, const std::string& text)
    : title{title},  description{description}, text{text}
{ 
}

std::string DocumentInfo::getTitle()
{
    return title;
}

std::string DocumentInfo::getDescription()
{
    return description;
}

std::string DocumentInfo::getText()
{
    return text;
}