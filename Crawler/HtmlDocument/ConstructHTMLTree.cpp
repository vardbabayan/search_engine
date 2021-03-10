#include "ConstructHTMLTree.hpp"

ConstructHTMLTree::ConstructHTMLTree(std::shared_ptr<std::string> url)
{
    // this->output = gumbo_parse(url.get()->c_str());
    // this->node = output->root;
}

void ConstructHTMLTree::extractLinks(GumboNode* node)
{
    if (node->type != GUMBO_NODE_ELEMENT)
        return;

    if (node->v.element.tag != GUMBO_TAG_A ) 
    {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) 
        {
            extractLinks(static_cast<GumboNode*>(children->data[i]));
        }
        
    }

    GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
    
    if(href) 
    {
        std::cout << href->value << std::endl;
    }
}

void ConstructHTMLTree::searchAllLinks(std::shared_ptr<std::string> url)
{
    this->output = gumbo_parse(url.get()->c_str());

    extractLinks(output->root);

    gumbo_destroy_output(&kGumboDefaultOptions, this->output);
}

GumboOutput ConstructHTMLTree::getOutput()
{
    return *output;
}

GumboNode ConstructHTMLTree::getNode()
{
    return *node;
}

ConstructHTMLTree::~ConstructHTMLTree()
{
    gumbo_destroy_output(&kGumboDefaultOptions, this->output);
}