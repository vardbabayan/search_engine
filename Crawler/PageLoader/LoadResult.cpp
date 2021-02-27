#include "LoadResult.h"

LoadResult::LoadResult(const std::string body, int status) : body{body}, status{status} 
{
}

std::string LoadResult::getBody()
{
    return body;
}

int LoadResult::getStatus()
{
    return status;
}