#include <engine/creators/GUI/label_creator.h>

LabelCreator::LabelCreator() {}
LabelCreator::~LabelCreator() {}

Label* LabelCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");

    Label* label = new Label(id);

    if (actorData->contains("x")) {
        label->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        label->y = actorData->at("y");
    }

    if (actorData->contains("relativePos")) {
        label->relativePosMode = actorData->at("relativePos");
    }

    if (actorData->contains("visible")) {
        label->visible = actorData->at("visible");
    }

    if (actorData->contains("text")) {
        label->setText(actorData->at("text"));
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            label->anchorX = actorData->at("anchor");
            label->anchorY = actorData->at("anchor");
            label->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                label->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                label->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                label->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        label->rotation = actorData->at("rotation");
    }

    return label;
}
