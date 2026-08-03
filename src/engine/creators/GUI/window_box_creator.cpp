#include <engine/creators/GUI/window_box_creator.h>

WindowBoxCreator::WindowBoxCreator() {}
WindowBoxCreator::~WindowBoxCreator() {}

WindowBox* WindowBoxCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");

    WindowBox* windowBox = new WindowBox(id);

    if (actorData->contains("x")) {
        windowBox->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        windowBox->y = actorData->at("y");
    }

    if (actorData->contains("visible")) {
        windowBox->visible = actorData->at("visible");
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            windowBox->anchorX = actorData->at("anchor");
            windowBox->anchorY = actorData->at("anchor");
            windowBox->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                windowBox->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                windowBox->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                windowBox->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        windowBox->rotation = actorData->at("rotation");
    }

    return windowBox;
}
