#pragma once

#ifndef BASE_ACTOR_H
#define BASE_ACTOR_H

#include <string>

#include <sling.h>

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
    public:
        std::string id;
        
        sl::Slot<float> onUpdate{this, &BaseActor::update};
        sl::Slot<> onRender{this, &BaseActor::render};
        
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

        virtual void update(float dT);
        virtual void render();

        void calculateRenderedPosition();
};

#endif