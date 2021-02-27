#include "PageLoader.h"

#include <curl/curl.h>
#include <iostream>

LoadResult PageLoader::loadURL(const std::string url)
{
    std::string resultHTML;

    CURL* curl = curl_easy_init();

    if(!curl)
    {
        std::cout << "init curl failed\n";
        return LoadResult("", 0);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, resultHTML.c_str());

    CURLcode result = curl_easy_perform(curl);
    if(result != CURLE_OK)
    {
        // fprintf(stderr, "download problem %s\n", curl_easy_strerror(result));
        return LoadResult("", 0);
    }

    curl_easy_cleanup(curl);

    std::cout << resultHTML << "\n";
    return LoadResult(resultHTML, 1);
}