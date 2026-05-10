#include <engine/creators/3D/mesh_creator.h>

MeshCreator::MeshCreator() {}

MeshCreator::~MeshCreator() {}

MeshModel* MeshCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");
    std::string modelID = actorData->at("model");
    std::string textureID = actorData->at("texture");

    raylib::Model* model = Ariel::Global::assetLoader.getModelPtr(modelID);
    raylib::Texture2D* texture = Ariel::Global::assetLoader.getTexturePtr(textureID);

    MeshModel* mesh = new MeshModel(id, model, texture);

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
                colorData.contains("r") ? colorData.at("r").get<char>() : 255,
                colorData.contains("g") ? colorData.at("g").get<char>() : 255,
                colorData.contains("b") ? colorData.at("b").get<char>() : 255,
                colorData.contains("a") ? colorData.at("a").get<char>() : 255
            });
        }
    }

    return mesh;
}