#include "HtmlNode.hpp"

explicit HtmlNode::HtmlNode(GumboNode* node) : node{node}
{
}

bool HtmlNode::isElement() const
{
    if(!node)
        return false;

    if (node->type != GUMBO_NODE_ELEMENT)
        return false;

    return true;
}