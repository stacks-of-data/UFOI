#include <ufoi.hpp>
#include <list>
#include <unordered_map>
#include <string>

class UFOIParser
{
    private:
        size_t _page_size;
        std::list<UFOIModel*> _list_models;
        std::unordered_map<std::string, UFOIMaterial*> _materials;
        std::unordered_map<std::string, UFOITexture*> _textures;
        std::list<float*> _verts_pages;
        std::list<float*> _norms_pages;
        std::list<float*> _texcoords_pages;
    public:
        UFOIParser();
        UFOIParser(size_t page_size);
        ~UFOIParser();
        UFOIScene* parse(const std::string& path);
};