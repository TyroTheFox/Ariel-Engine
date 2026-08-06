#include <engine/creators/GUI/button_creator.h>

ButtonCreator::ButtonCreator() {}
ButtonCreator::~ButtonCreator() {}

Button* ButtonCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");

    Button* button = new Button(id);

    if (actorData->contains("x")) {
        button->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        button->y = actorData->at("y");
    }

    if (actorData->contains("relativePos")) {
        button->relativePosMode = actorData->at("relativePos");
    }

    if (actorData->contains("visible")) {
        button->visible = actorData->at("visible");
    }

    if (actorData->contains("text")) {
        button->setText(actorData->at("text"));
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            button->anchorX = actorData->at("anchor");
            button->anchorY = actorData->at("anchor");
            button->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                button->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                button->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                button->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        button->rotation = actorData->at("rotation");
    }

    return button;
}
