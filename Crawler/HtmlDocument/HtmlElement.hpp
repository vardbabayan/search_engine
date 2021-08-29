#ifndef HTML_ELEMENT
#define HTML_ELEMENT

#include "HtmlNode.hpp"
#include <string>

class HtmlElement : public HtmlNode
{
public:
    explicit HtmlElement(GumboNode* node);

    /**
     * always true
     */
    bool isElement() const override;

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
     * if tag contains an attribute, then take it
     */
    std::string getAttribute(const std::string& name) const;

    /**
     * get text from current element
     */
    std::string getInnerText() const;
};

#endif
