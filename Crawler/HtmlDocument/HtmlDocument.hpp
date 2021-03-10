
#include <string>
#include <functional>

#include "HtmlElement.hpp"
#include "gumbo.h"

class HtmlDocument 
{
private:
    GumboOutput* output;
    std::string url;
public:
    HtmlDocument(const std::string& url);
    bool parse();
    void visitElements(std::function<void(HtmlElement)> visitor)
    {
        this->visitElement(output->root, visitor);
    }

    void visitElement(GumboNode* node, std::function<void(HtmlElement)> visitor)
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
};