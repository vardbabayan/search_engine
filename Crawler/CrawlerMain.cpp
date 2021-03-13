#include "PageLoader/PageLoader.cpp"
//#include "HtmlParser/ConstructHTMLTree.cpp"

int main()
{
    PageLoader t; 
    LoadResult url = t.loadURL("https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html");
    
    std::cout << *url.getBody().get();

    // ConstructHTMLTree tree(url.getBody());
    // GumboNode node = tree.getNode();
    // tree.searchAllLinks(url.getBody());
}