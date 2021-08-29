#include "LoadResult.hpp"

explicit LoadResult::LoadResult() {}

explicit LoadResult::LoadResult(std::shared_ptr<std::string> body, int status)
{
    this->body = body;
    this->status = status;
}

std::shared_ptr<std::string> LoadResult::getBody() const
{
    return this->body;
}

int LoadResult::getStatus() const
{
    return this->status;
}