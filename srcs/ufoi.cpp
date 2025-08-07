#include <ufoi_internal.hpp>

UFOIParser::UFOIParser():
    _page_size(2048)
{}

UFOIParser::UFOIParser(size_t page_size):
    _page_size(page_size)
{}

UFOIParser::~UFOIParser()
{

}

UFOIScene* UFOIParser::parse(const std::string& path)
{

}