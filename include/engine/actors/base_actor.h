#pragma once

#ifndef BASE_ACTOR_H
#define BASE_ACTOR_H

#include <string>
#include <engine/render/rendering_shader.h>

#include <sling.h>

enum ActorRenderType {
    ACTOR_2D,
    ACTOR_3D
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

        ActorRenderType actorRenderType = ACTOR_2D;
    public:
        std::string id;
        std::string actorType;
        
        sl::Slot<float> onUpdate{this, &BaseActor::update};
        sl::Slot<RenderingShader*> onRender{this, &BaseActor::render};
        
        float x;
        float y;
        float z;
        float pivotX;
        float pivotY;
        float pivotZ;
        
        float scaleX;
        float scaleY;
        float scaleZ;

        float anchorX;
        float anchorY;
        float anchorZ;
        
        float rotation;
        
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

        float getRotation();

        bool getVisible();

        ActorRenderType getActorRenderType();

        virtual void update(float dT);
        virtual void render(RenderingShader* shader);

        void calculateRenderedPosition();
};

#endif