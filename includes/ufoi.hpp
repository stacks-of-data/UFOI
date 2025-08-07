#ifndef UFOI_HPP
#define UFOI_HPP

#include <cstdint>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <exception>

namespace UFOI
{
    typedef enum ETextureType
    {
        UFOI_TEX_AMBIENT,
        UFOI_TEX_DIFFUSE,
        UFOI_TEX_SPECULAR,
        UFOI_TEX_SHININESS,
        UFOI_TEX_ALPHA,
        UFOI_TEX_BUMP,
        UFOI_TEX_DISPLACMENT
    } TextureType;

    typedef struct STexture
    {
        UFOI::TextureType type;
        char* path;
    } Texture;

    typedef struct SMaterial
    {
        char* name;
        float ambient[3];
        float diffuse[3];
        float specular[3];
        float transparency_filter[3];
        float transparency;
        float optical_density;
        std::vector<UFOI::Texture*> textures;
    } Material;

    typedef struct SPart
    {
        std::vector<std::uint32_t> indices;
        UFOI::Material* material;
    } Part;

    typedef struct SMesh
    {
        char* mesh_name;
        std::vector<UFOI::Part*> parts;
    } Mesh;

    typedef struct SModel
    {
        char* model_name;
        std::vector<UFOI::Mesh*> meshes;
    } Model;

    class AccessError: public std::exception
    {
        const char* what() const noexcept;
    };

    class FileNotFound: public std::exception
    {
        const char* what() const noexcept;
    };

    class ReadAccessDenied: public std::exception
    {
        const char* what() const noexcept;
    };

    class OpenFileError: public std::exception
    {
        const char* what() const noexcept;
    };

    class FileStatError: public std::exception
    {
        const char* what() const noexcept;
    };

    class MemoryMapError: public std::exception
    {
        const char* what() const noexcept;
    };
}

class UFOIScene
{
    public:
        std::vector<float> verts;
        std::vector<float> norms;
        std::vector<float> texcoords;
        std::vector<UFOI::Model*> models;
        std::vector<UFOI::Material*> materials;
        std::vector<UFOI::Texture*> textures;
        UFOIScene();
        ~UFOIScene();
};

class UFOIParser
{
    private:
        bool _bLogging;
        const std::string* _path;
        __off_t _map_size;
        size_t _page_size;
        size_t _line;
        UFOIScene* _scene;
        char* _map_addr;
        char* _map_end;
        std::list<UFOI::Model*> _list_models;
        std::unordered_map<std::string, UFOI::Material*> _materials;
        std::unordered_map<std::string, UFOI::Texture*> _textures;
        std::list<float*> _verts_pages;
        std::list<float*> _norms_pages;
        std::list<float*> _texcoords_pages;
        void parseMapFile();
        void parseProcessData();
        void cleanParser();
        bool tokenCmp(char* map_ptr, char* token);
    public:
        UFOIParser();
        UFOIParser(bool bLogging, size_t page_size);
        ~UFOIParser();
        UFOIScene* parse(const std::string& path);
};

#endif