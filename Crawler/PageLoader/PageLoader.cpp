#include "PageLoader.hpp"

#include <curl/curl.h>
#include <cerrno>

size_t PageLoader::writeFunction(char *ptr, size_t size, size_t nmemb, void* data) 
{
    std::string* str = (std::string*)data;
    str->append(ptr, size * nmemb);
    return size * nmemb;
}

LoadResult PageLoader::loadURL(const std::string& url)
{
    CURL* curl = curl_easy_init();
    CURLcode result;

    if(!curl)
    {
        std::cerr << "init curl failed\n";
        return LoadResult(nullptr, false);
    }

    std::string* response_body = new std::string;
    long response_status;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)response_body);
    
    /* Perform request, result will get a return code */
    result = curl_easy_perform(curl);    
    if(result != CURLE_OK)
    {
        std::cerr << "perform problem\n";
        return LoadResult(nullptr, false);
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_status);
    curl_easy_cleanup(curl);

    return LoadResult(std::shared_ptr<std::string>(response_body), response_status);
}