#include "LinkEntry.hpp"
#include <vector>
#include <map>

class LinkRepository
{
private:
    std::map<int, LinkEntry> source;
public:
    std::vector<LinkEntry> getAll();
    LinkEntry getById(int id);
    void save(LinkEntry entry);
};