#include "HtmlElement.hpp"

HtmlElement::HtmlElement(GumboNode* node) : HtmlNode(node)
{
}

bool HtmlElement::isElement()
{
   return true;
}

bool HtmlElement::isTagA() const
{
    if(node->v.element.tag != GUMBO_TAG_A)
    {
        return false;        
    }
    return true;
}

std::string HtmlElement::getAttribute(const std::string& name)
{
    GumboAttribute* attribute = gumbo_get_attribute(&node->v.element.attributes, name.c_str());
    if(!attribute)
        return "";
            
    return std::string{attribute->value};
}