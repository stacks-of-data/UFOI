#ifndef UFOI_HPP
#define UFOI_HPP

#include <cstdint>
#include <vector>

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

#endif