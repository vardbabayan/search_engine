#ifndef HTML_ELEMENT
#define HTML_ELEMENT

#include "HtmlNode.hpp"

#include <string>

class HtmlElement : HtmlNode
{
public:
    HtmlElement(GumboNode* node);

    /**
     * always true
     */
    bool isElement() override;

    /**
     * check is <a> or not
     */
    bool isTagA() const;

    /**
     * check tags for text
     */
    bool isTagsForText() const;

    /**
     * check is tag <title> or not
     */
    bool isTagTitle() const;

    /**
     * check is tag <meta> or not
     */
    bool isTagForDescription() const;

    /**
     * if tag contains attribute then take it
     */
    std::string getAttribute(const std::string& name);

    /**
     * get text from current element
     */
    std::string getInnerText();
};

#endif
