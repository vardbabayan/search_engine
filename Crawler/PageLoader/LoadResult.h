#ifndef LOAD_RESULT_H
#define LOAD_RESULT_H

#include <string>

class LoadResult
{
private:
    /**
     * stores the response body 
    */
    std::string body;

    /**
     * stores the response status
     */
    int status;

public:
    LoadResult(const std::string body, int status);
    std::string getBody();
    int getStatus();
};

#endif