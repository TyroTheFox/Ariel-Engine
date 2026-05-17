#include <engine/creators/3D/mesh_creator.h>

MeshCreator::MeshCreator() {}

MeshCreator::~MeshCreator() {}

MeshModel* MeshCreator::createActor(json* actorData) const {
    ModelLoader modelLoader = ModelLoader();
    TextureAssetLoader textureLoader = TextureAssetLoader();
    
    std::string id = actorData->at("id");
    std::string modelID = actorData->at("model");
    std::string textureID = actorData->at("texture");

    raylib::Model* model = modelLoader.getModelPtr(modelID);
    raylib::Texture2D* texture = textureLoader.getTexturePtr(textureID);

    MeshModel* mesh = new MeshModel(id, model, texture);

    mesh->setTextureTilingVector(
        actorData->contains("tilingX") ? actorData->at("tilingX").get<float>() : 0.5,
        actorData->contains("tilingY") ? actorData->at("tilingY").get<float>() : 0.5
    );

    if (actorData->contains("metalnessTexture")) {
        std::string id = actorData->at("metalnessTexture");
        raylib::Texture2D* newTexture = textureLoader.getTexturePtr(id);

        mesh->setMetalnessTexture(newTexture);
    }

    if (actorData->contains("normalTexture")) {
        std::string id = actorData->at("normalTexture");
        raylib::Texture2D* newTexture = textureLoader.getTexturePtr(id);

        mesh->setNormalTexture(newTexture);
    }

    if (actorData->contains("emissionTexture")) {
        std::string id = actorData->at("emissionTexture");
        raylib::Texture2D* newTexture = textureLoader.getTexturePtr(id);

        mesh->setEmissionTexture(newTexture);
    }

    if (actorData->contains("x")) {
        mesh->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        mesh->y = actorData->at("y");
    }

    if (actorData->contains("z")) {
        mesh->y = actorData->at("z");
    }

    if (actorData->contains("visible")) {
        mesh->visible = actorData->at("visible");
    }

    if (actorData->contains("metalness")) {
        mesh->setMetalness(actorData->at("metalness"));
    }

    if (actorData->contains("roughness")) {
        mesh->setRoughness(actorData->at("roughness"));
    }

    if (actorData->contains("occlusion")) {
        mesh->setOcclusion(actorData->at("occlusion"));
    }

    if (actorData->contains("scale")) {
        if (actorData->at("scale").is_number()) {
            mesh->scaleX = actorData->at("scale");
            mesh->scaleY = actorData->at("scale");
            mesh->scaleZ = actorData->at("scale");
        }

        if (actorData->at("scale").is_object()) {
            json scaleData = actorData->at("scale");

            if (scaleData.at("x")) {
                mesh->scaleX = scaleData.at("x");
            }

            if (scaleData.at("y")) {
                mesh->scaleY = scaleData.at("y");
            }

            if (scaleData.at("z")) {
                mesh->scaleZ = scaleData.at("z");
            }
        }
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            mesh->anchorX = actorData->at("anchor");
            mesh->anchorY = actorData->at("anchor");
            mesh->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                mesh->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                mesh->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                mesh->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("textureTilingX")) {
        mesh->x = actorData->at("textureTilingX");
    }

    if (actorData->contains("y")) {
        mesh->y = actorData->at("y");
    }


    if (actorData->contains("rotation")) {
        mesh->rotation = actorData->at("rotation");
    }

    if (actorData->contains("rotationAxis")) {
        if (actorData->at("rotationAxis").is_number()) {
            mesh->anchorX = actorData->at("rotationAxis");
            mesh->anchorY = actorData->at("rotationAxis");
            mesh->anchorZ = actorData->at("rotationAxis");
        }

        if (actorData->at("rotationAxis").is_object()) {
            json anchorData = actorData->at("rotationAxis");

            if (anchorData.at("x")) {
                mesh->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                mesh->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                mesh->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("tint")) {
        json colorData = actorData->at("tint");

        if (colorData.is_string()) {
            mesh->setTint(convertTextToColour(colorData.get<std::string>()));
        }

        if (colorData.is_object()) {
            mesh->setTint({
                colorData.contains("r") ? colorData.at("r").get<char>() : 0,
                colorData.contains("g") ? colorData.at("g").get<char>() : 0,
                colorData.contains("b") ? colorData.at("b").get<char>() : 0,
                colorData.contains("a") ? colorData.at("a").get<char>() : 255
            });
        }
    }

    if (actorData->contains("emissionColor")) {
        json colorData = actorData->at("emissionColor");

        if (colorData.is_string()) {
            mesh->setEmissionColor(convertTextToColour(colorData.get<std::string>()));
        }

        if (colorData.is_object()) {
            mesh->setEmissionColor({
                colorData.contains("r") ? colorData.at("r").get<char>() : 0,
                colorData.contains("g") ? colorData.at("g").get<char>() : 0,
                colorData.contains("b") ? colorData.at("b").get<char>() : 0,
                colorData.contains("a") ? colorData.at("a").get<char>() : 255
            });
        }
    }

    return mesh;
}