#ifndef LOAD_RESULT_H
#define LOAD_RESULT_H

#include <iostream>
#include <string>
#include <memory>

class LoadResult
{
private:
    /**
     * stores the response body 
    */
    std::shared_ptr<std::string> body;

    /**
     * stores the response status
     */
    int status;

public:
    explicit LoadResult();
    
    explicit LoadResult(std::shared_ptr<std::string> body, int status);

    /**
     * return html code of the page
     */
    std::shared_ptr<std::string> getBody() const;

    /** 
     * return response status after request
     */
    int getStatus() const;
};

#endif