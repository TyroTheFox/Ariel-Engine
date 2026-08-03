#include <engine/creators/container_creator.h>

ContainerCreator::ContainerCreator() {}
ContainerCreator::~ContainerCreator() {}

Container* ContainerCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");

    Container* container = new Container(id);

    if (actorData->contains("x")) {
        container->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        container->y = actorData->at("y");
    }

    if (actorData->contains("visible")) {
        container->visible = actorData->at("visible");
    }

    if (actorData->contains("scale")) {
        if (actorData->at("scale").is_number()) {
            container->scaleX = actorData->at("scale");
            container->scaleY = actorData->at("scale");
            container->scaleZ = actorData->at("scale");
        }

        if (actorData->at("scale").is_object()) {
            json scaleData = actorData->at("scale");

            if (scaleData.at("x")) {
                container->scaleX = scaleData.at("x");
            }

            if (scaleData.at("y")) {
                container->scaleY = scaleData.at("y");
            }

            if (scaleData.at("z")) {
                container->scaleZ = scaleData.at("z");
            }
        }
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            container->anchorX = actorData->at("anchor");
            container->anchorY = actorData->at("anchor");
            container->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                container->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                container->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                container->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        container->rotation = actorData->at("rotation");
    }

    return container;
}
