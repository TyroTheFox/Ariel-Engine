#include "engine/creators/2D/shape_creator.h"

ShapeCreator::ShapeCreator(){}
ShapeCreator::~ShapeCreator(){}

Shape* ShapeCreator::createActor(json* actorData) const {
    std::string id = actorData->at("id");

    Shape* shape = new Shape(id);

    if (actorData->contains("x")) {
        shape->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        shape->y = actorData->at("y");
    }

    if (actorData->contains("visible")) {
        shape->visible = actorData->at("visible");
    }

    if (actorData->contains("draw")) {
        shape->drawData = actorData->at("draw");
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            shape->anchorX = actorData->at("anchor");
            shape->anchorY = actorData->at("anchor");
            shape->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                shape->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                shape->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                shape->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        shape->rotation = actorData->at("rotation");
    }

    return shape;
}