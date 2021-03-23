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
    LoadResult();
    
    LoadResult(std::shared_ptr<std::string> body, int status);

    // return html code represented in string
    std::shared_ptr<std::string> getBody();

    // return responce status 
    int getStatus();
};

#endif