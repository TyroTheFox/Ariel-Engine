#pragma once

#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <map>
#include <vector>

#include <sling.h>
#include <engine/actors/base_actor.h>

class Container: public BaseActor
{
private:
protected:
    std::map<std::string, BaseActor*> children;
public:
    sl::Signal<> childAdded;
    sl::Signal<> childRemoved;  

    Container();
    Container(std::string name);

    ~Container();

    void addChildren(BaseActor* addedActor);

    void removeChildren(std::string childId);

    void update(float dT) override;
    void render() override;
};

#endif