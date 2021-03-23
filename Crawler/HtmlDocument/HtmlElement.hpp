#ifndef Html_Element
#define Html_Element

#include "HtmlNode.hpp"

#include <string>

class HtmlElement : HtmlNode
{
public:
    HtmlElement(GumboNode* node);

    // always true
    bool isElement() override;

    // check is <a> or not
    bool isTagA() const;

    // if tag contains attribute then take it
    std::string getAttribute(const std::string& name);
};

#endif