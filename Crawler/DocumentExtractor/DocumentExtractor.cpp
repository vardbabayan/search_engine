#include "DocumentExtractor.hpp"

DocumentInfo DocumentExtractor::extractInfo(HtmlDocument& doc)
{
    std::string title;
    std::string description;
    std::string text;
    doc.visitElements([&text, &title, &description](HtmlElement elem)
    { 
        if(!elem.isTagsForText())
        {
            return;
        }

        if(elem.isTagTitle())
        {
            title.append(elem.getInnerText());
        }

        if(elem.isTagForDescription())
        {
            description.append(elem.getInnerText());
        }

        text.append(elem.getInnerText());
    });

    return DocumentInfo(title, description, text);
}