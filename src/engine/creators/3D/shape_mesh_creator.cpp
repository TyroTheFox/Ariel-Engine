#include <engine/creators/3D/shape_mesh_creator.h>

ShapeMeshCreator::ShapeMeshCreator() {}

ShapeMeshCreator::~ShapeMeshCreator() {}

ShapeMesh* ShapeMeshCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");

    ShapeMesh* mesh = new ShapeMesh(id);

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

    if (actorData->contains("draw")) {
        mesh->drawData = actorData->at("draw");
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

    return mesh;
}