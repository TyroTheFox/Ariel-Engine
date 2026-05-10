#include <engine/creators/2D/text_creator.h>

TextCreator::TextCreator() {}
TextCreator::~TextCreator() {}

Text* TextCreator::createActor(json* actorData) const {
    raylib::Font defaultFont = GetFontDefault();

    std::string id = actorData->at("id");
    std::string fontID = actorData->contains("font") ? actorData->at("font") : "";

    raylib::Font* font = fontID == "" ? &defaultFont : Ariel::Global::assetLoader.getFontPtr(fontID);

    Text* text = new Text(id, font);

    if (actorData->contains("x")) {
        text->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        text->y = actorData->at("y");
    }

    if (actorData->contains("visible")) {
        text->visible = actorData->at("visible");
    }

    if (actorData->contains("text")) {
        text->setText(actorData->at("text"));
    }

    if (actorData->contains("wordWrap")) {
        text->setWordWrap(actorData->at("wordWrap"));
    }

    if (actorData->contains("wordWrapBounds")) {
        json wordWrapBounds = actorData->at("wordWrapBounds");

        text->setWordWrapBounds({
            wordWrapBounds.at("x"),
            wordWrapBounds.at("y"),
            wordWrapBounds.at("width"),
            wordWrapBounds.at("height")
        });
    }

    if (actorData->contains("colour")) {
        json textColour = actorData->at("colour");

        if (textColour.is_string()) {
            text->setColour(convertTextToColour(actorData->at("colour")));
        }

        if (textColour.is_array()) {
            text->setColour(raylib::Color(textColour.at(0), textColour.at(1), textColour.at(2), textColour.at(3)));
        }
    }

    if (actorData->contains("spacing")) {
        text->setSpacing(actorData->at("spacing"));
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            text->anchorX = actorData->at("anchor");
            text->anchorY = actorData->at("anchor");
            text->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                text->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                text->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                text->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        text->rotation = actorData->at("rotation");
    }

    return text;
}
