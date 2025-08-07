#include <cstdint>
#include <vector>

typedef enum EUFOITextureType
{
    UFOI_TEX_AMBIENT,
    UFOI_TEX_DIFFUSE,
    UFOI_TEX_SPECULAR,
    UFOI_TEX_SHININESS,
    UFOI_TEX_ALPHA,
    UFOI_TEX_BUMP,
    UFOI_TEX_DISPLACMENT
} UFOITextureType;

typedef struct SUFOITexture
{
    UFOITextureType type;
    char* path;
} UFOITexture;

typedef struct SUFOIMaterial
{
    char* name;
    float ambient[3];
    float diffuse[3];
    float specular[3];
    float transparency;
    float transparency_filter[3];
    float optical_density;
    std::vector<UFOITexture*> textures;
} UFOIMaterial;

typedef struct SUFOIPart
{
    std::size_t indices_len;
    std::uint32_t* indices;
    UFOIMaterial* material;
} UFOIPart;

typedef struct SUFOIMesh
{
    char* mesh_name;
    std::vector<UFOIPart*> parts;
} UFOIMesh;

typedef struct SUFOIModel
{
    char* model_name;
    std::vector<UFOIMesh*> meshes;
} UFOIModel;

class UFOIScene
{
    public:
        std::vector<float> verts;
        std::vector<float> norms;
        std::vector<float> texcoords;
        std::vector<UFOIModel*> models;
        std::vector<UFOIMaterial*> materials;
        std::vector<UFOITexture*> textures;
        UFOIScene();
        ~UFOIScene();
};