#include <engine/render/shader_objects/shader_manager.h>

std::map<std::string, RenderingShader*> ShaderManager::shaderCache{};

std::string ShaderManager::defaultShader = "pbr";

std::unordered_map<std::string, int> ShaderManager::shaderLocationIndexes {
    {"SHADER_LOC_COLOR_AMBIENT",            SHADER_LOC_COLOR_AMBIENT},
    {"SHADER_LOC_VERTEX_POSITION",          SHADER_LOC_VERTEX_POSITION},
    {"SHADER_LOC_VERTEX_TEXCOORD02",        SHADER_LOC_VERTEX_TEXCOORD02},
    {"SHADER_LOC_VERTEX_NORMAL",            SHADER_LOC_VERTEX_NORMAL},
    {"SHADER_LOC_VERTEX_TANGENT",           SHADER_LOC_VERTEX_TANGENT},
    {"SHADER_LOC_VERTEX_COLOR",             SHADER_LOC_VERTEX_COLOR},
    {"SHADER_LOC_MATRIX_MVP",               SHADER_LOC_MATRIX_MVP},
    {"SHADER_LOC_MATRIX_VIEW",              SHADER_LOC_MATRIX_VIEW},
    {"SHADER_LOC_MATRIX_PROJECTION",        SHADER_LOC_MATRIX_PROJECTION},
    {"SHADER_LOC_MATRIX_MODEL",             SHADER_LOC_MATRIX_MODEL},
    {"SHADER_LOC_MATRIX_NORMAL",            SHADER_LOC_MATRIX_NORMAL},
    {"SHADER_LOC_VECTOR_VIEW",              SHADER_LOC_VECTOR_VIEW},
    {"SHADER_LOC_COLOR_DIFFUSE",            SHADER_LOC_COLOR_DIFFUSE},
    {"SHADER_LOC_COLOR_SPECULAR",           SHADER_LOC_COLOR_SPECULAR},
    {"SHADER_LOC_COLOR_AMBIENT",            SHADER_LOC_COLOR_AMBIENT},
    {"SHADER_LOC_MAP_ALBEDO",               SHADER_LOC_MAP_ALBEDO},
    {"SHADER_LOC_MAP_METALNESS",            SHADER_LOC_MAP_METALNESS},
    {"SHADER_LOC_MAP_NORMAL",               SHADER_LOC_MAP_NORMAL},
    {"SHADER_LOC_MAP_ROUGHNESS",            SHADER_LOC_MAP_ROUGHNESS},
    {"SHADER_LOC_MAP_OCCLUSION",            SHADER_LOC_MAP_OCCLUSION},
    {"SHADER_LOC_MAP_EMISSION",             SHADER_LOC_MAP_EMISSION},
    {"SHADER_LOC_MAP_HEIGHT",               SHADER_LOC_MAP_HEIGHT},
    {"SHADER_LOC_MAP_CUBEMAP",              SHADER_LOC_MAP_CUBEMAP},
    {"SHADER_LOC_MAP_IRRADIANCE",           SHADER_LOC_MAP_IRRADIANCE},
    {"SHADER_LOC_MAP_PREFILTER",            SHADER_LOC_MAP_PREFILTER},
    {"SHADER_LOC_MAP_BRDF",                 SHADER_LOC_MAP_BRDF},
    {"SHADER_LOC_VERTEX_BONEIDS",           SHADER_LOC_VERTEX_BONEIDS},
    {"SHADER_LOC_VERTEX_BONEWEIGHTS",       SHADER_LOC_VERTEX_BONEWEIGHTS},
    {"SHADER_LOC_MATRIX_BONETRANSFORMS",    SHADER_LOC_MATRIX_BONETRANSFORMS},
    {"SHADER_LOC_VERTEX_INSTANCETRANSFORM", SHADER_LOC_VERTEX_INSTANCETRANSFORM},
};

ShaderManager::ShaderManager() {}

ShaderManager::~ShaderManager() {}

void ShaderManager::loadManifest(json jsonData) {
    
    json shaderManifest = jsonData.at("shaders");

    for (auto& entry : shaderManifest) {
        std::string id = entry.at("id");
        std::string vertex = entry.at("vertex");
        std::string frag = entry.at("frag");
        bool isDefault = entry.contains("default") ? entry.at("default").get<bool>() : false;

        RenderingShader* foundShader = new RenderingShader(vertex, frag);

        this->shaderCache.insert({id, foundShader});

        if (isDefault) {
            this->defaultShader = id;
        }

        if (entry.contains("locations")) {
            json locationData = entry.at("locations");

            for (auto& locationEntry : locationData) {
                std::string index = locationEntry.at("index");
                std::string uniformName = locationEntry.at("uniformName");

                foundShader->setShaderLocation(this->convertStringToShaderLocationIndex(index), uniformName);
            }
        }
    }
}

void ShaderManager::unloadCurrentManifest() {
    for (const auto& [key, value] : this->shaderCache) {
        if (value->shaderInstance.IsValid()) {
            delete value;
        }
    }

    this->shaderCache.clear();
}

int ShaderManager::convertStringToShaderLocationIndex(std::string indexName) {
    auto it = this->shaderLocationIndexes.find(indexName);

    if (it != this->shaderLocationIndexes.end()) {
        return it->second;
    } else { 
        return SHADER_LOC_VERTEX_POSITION;
    }
}

RenderingShader* ShaderManager::getShaderPtr(std::string shaderID) {
    auto it = this->shaderCache.find(shaderID);

    if (it == this->shaderCache.end()) {
        // Element Not Found
        return nullptr;
    }

    auto shaderPtr = this->shaderCache.at(shaderID);

    return shaderPtr;
}

RenderingShader* ShaderManager::getDefaultShaderPtr() {
    return this->shaderCache.at(this->defaultShader);
}