#include "LoadResult.hpp"

LoadResult::LoadResult() {}

LoadResult::LoadResult(std::shared_ptr<std::string> body, int status)
{
    this->body = body;
    this->status = status;
}

std::shared_ptr<std::string> LoadResult::getBody()
{
    return body;
}

int LoadResult::getStatus()
{
    return status;
}