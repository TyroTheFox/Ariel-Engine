#include <engine/creators/3D/billboard_sprite_creator.h>

BillboardSpriteCreator::BillboardSpriteCreator() {}

BillboardSpriteCreator::~BillboardSpriteCreator() {}

BillboardSprite* BillboardSpriteCreator::createActor(json* actorData) const {
    TextureAssetLoader assetLoader = TextureAssetLoader();
    
    std::string id = actorData->at("id");
    std::string textureID = actorData->at("texture");
    std::string defaultAnimation = actorData->contains("defaultAnimation") ? actorData->at("defaultAnimation").get<std::string>() : "default";

    TextureAtlas* textureAtlas = assetLoader.getTextureAtlas(textureID);

    BillboardSprite* billboardSprite = new BillboardSprite(id, textureAtlas, defaultAnimation);

    if (actorData->contains("x")) {
        billboardSprite->x = actorData->at("x");
    }

    if (actorData->contains("y")) {
        billboardSprite->y = actorData->at("y");
    }

    if (actorData->contains("z")) {
        billboardSprite->y = actorData->at("z");
    }

    if (actorData->contains("visible")) {
        billboardSprite->visible = actorData->at("visible");
    }

    if (actorData->contains("scale")) {
        if (actorData->at("scale").is_number()) {
            billboardSprite->scaleX = actorData->at("scale");
            billboardSprite->scaleY = actorData->at("scale");
            billboardSprite->scaleZ = actorData->at("scale");
        }

        if (actorData->at("scale").is_object()) {
            json scaleData = actorData->at("scale");

            if (scaleData.at("x")) {
                billboardSprite->scaleX = scaleData.at("x");
            }

            if (scaleData.at("y")) {
                billboardSprite->scaleY = scaleData.at("y");
            }

            if (scaleData.at("z")) {
                billboardSprite->scaleZ = scaleData.at("z");
            }
        }
    }

    if (actorData->contains("normalTexture")) {
        std::string id = actorData->at("normalTexture");
        raylib::Texture2D* newTexture = assetLoader.getTexturePtr(id);

        billboardSprite->setNormalTexture(newTexture);
    }

    if (actorData->contains("occlusionTexture")) {
        std::string id = actorData->at("occlusionTexture");
        raylib::Texture2D* newTexture = assetLoader.getTexturePtr(id);

        billboardSprite->setOcclusionTexture(newTexture);
    }

    if (actorData->contains("specularTexture")) {
        std::string id = actorData->at("specularTexture");
        raylib::Texture2D* newTexture = assetLoader.getTexturePtr(id);

        billboardSprite->setSpecularTexture(newTexture);
    }

    if (actorData->contains("anchor")) {
        if (actorData->at("anchor").is_number()) {
            billboardSprite->anchorX = actorData->at("anchor");
            billboardSprite->anchorY = actorData->at("anchor");
            billboardSprite->anchorZ = actorData->at("anchor");
        }

        if (actorData->at("anchor").is_object()) {
            json anchorData = actorData->at("anchor");

            if (anchorData.at("x")) {
                billboardSprite->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                billboardSprite->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                billboardSprite->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("rotation")) {
        billboardSprite->rotation = actorData->at("rotation");
    }

    if (actorData->contains("rotationAxis")) {
        if (actorData->at("rotationAxis").is_number()) {
            billboardSprite->anchorX = actorData->at("rotationAxis");
            billboardSprite->anchorY = actorData->at("rotationAxis");
            billboardSprite->anchorZ = actorData->at("rotationAxis");
        }

        if (actorData->at("rotationAxis").is_object()) {
            json anchorData = actorData->at("rotationAxis");

            if (anchorData.at("x")) {
                billboardSprite->anchorX = anchorData.at("x");
            }

            if (anchorData.at("y")) {
                billboardSprite->anchorY = anchorData.at("y");
            }

            if (anchorData.at("z")) {
                billboardSprite->anchorZ = anchorData.at("z");
            }
        }
    }

    if (actorData->contains("origin")) {
        if (actorData->at("origin").is_number()) {
            billboardSprite->origin.SetX(actorData->at("origin"));
            billboardSprite->origin.SetY(actorData->at("origin"));
        }

        if (actorData->at("origin").is_object()) {
            json originData = actorData->at("origin");

            if (originData.at("x")) {
                billboardSprite->origin.SetX(originData.at("x"));
            }

            if (originData.at("y")) {
                billboardSprite->origin.SetY(originData.at("y"));
            }
        }
    }

    return billboardSprite;
}