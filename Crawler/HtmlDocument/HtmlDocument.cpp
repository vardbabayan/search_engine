#include "HtmlDocument.hpp"

HtmlDocument::HtmlDocument(const std::string& url) : url{url}
{
}

bool HtmlDocument::parse()
{
    HtmlElement elem(output->root);
    
}

void HtmlDocument::visitElements(std::function<void(HtmlElement)> visitor)
{
    this->visitElement(output->root, visitor);
}

void HtmlDocument::visitElement(GumboNode* node, std::function<void(HtmlElement)> visitor)
{
    if(node->type != GUMBO_NODE_ELEMENT)
    {
        return;
    }

    visitor(HtmlElement(node));

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) 
    {
        visitElement(static_cast<GumboNode*>(children->data[i]), visitor);
    }
}