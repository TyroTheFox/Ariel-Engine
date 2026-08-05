#pragma once

#ifndef BASE_ACTOR_H
#define BASE_ACTOR_H

#include <string>

#include <sling.h>

#include <raygui-4.0/src/raygui.h>

enum ActorRenderType {
    ACTOR_2D, // 2D Actors rendered after 3D assets
    ACTOR_3D, // 3D Actors rendered using the gBuffer (typically meshes)
    ACTOR_3D_OVER, // 3D Actors rendered over top of the gBuffer rendered actors after the fact
    ACTOR_3D_BILLBOARD // Rendering Step specifically for billboards because they're rendered weirdly
};

class BaseActor {
    protected:
        float renderedX;
        float renderedY;
        float renderedZ;

        float renderedScaleX;
        float renderedScaleY;
        float renderedScaleZ;

        float renderedRotation;

        bool renderedVisible;

        float renderedWidth = 0;
        float renderedHeight = 0;

        ActorRenderType actorRenderType = ACTOR_2D;
    public:
        std::string id;
        std::string actorType;
        
        sl::Slot<float> onUpdate{this, &BaseActor::update};
        sl::Slot<> onRender{this, &BaseActor::render};
        
        float x;
        float y;
        float z;
        float pivotX;
        float pivotY;
        float pivotZ;

        float relativePosMode = false;
        
        float scaleX;
        float scaleY;
        float scaleZ;

        float anchorX;
        float anchorY;
        float anchorZ;
        
        float rotation;

        float height = 100;
        float width = 100;
        
        bool visible;
        
        BaseActor* parent;
        void* attachedScene;

        BaseActor();
        ~BaseActor();

        float getX();
        float getY();
        float getZ();

        float getScaleX();
        float getScaleY();
        float getScaleZ();

        float getAnchorX();
        float getAnchorY();
        float getAnchorZ();

        float getWidth();
        float getHeight();

        float getRotation();

        bool getVisible();

        ActorRenderType getActorRenderType();

        virtual void update(float dT);
        virtual void render();

        void calculateRenderedPosition();
};

#endif