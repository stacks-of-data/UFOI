#ifndef UFOI_INTERNAL_HPP
#define UFOI_INTERNAL_HPP

#include <ufoi.hpp>
#include <list>
#include <unordered_map>
#include <string>

class UFOIParser
{
    private:
        size_t _page_size;
        std::list<UFOI::Model*> _list_models;
        std::unordered_map<std::string, UFOI::Material*> _materials;
        std::unordered_map<std::string, UFOI::Texture*> _textures;
        std::list<float*> _verts_pages;
        std::list<float*> _norms_pages;
        std::list<float*> _texcoords_pages;
    public:
        UFOIParser();
        UFOIParser(size_t page_size);
        ~UFOIParser();
        UFOIScene* parse(const std::string& path);
};

#endif