#pragma once

#include <string>
#include <map>
#include <vector>

#include "sling.h"
#include "engine/actors/base_actor.h"

class Container: public BaseActor
{
private:
    std::map<std::string, BaseActor> children;
public:
    sl::Signal<> childAdded;
    sl::Signal<> childRemoved;  

    Container(std::string id) {
        this->id = id;
    }

    ~Container();

    void addChildren(std::vector<BaseActor> children) {
        for (int i = 0; i < children.size(); i++) {
            children[i].parent = this;
            this->children.insert({children[i].id, children[i]});
            this->childAdded.emit();
        }
    }

    void removeChildren(std::vector<std::string> children) {
        for (int i = 0; i < children.size(); i++) {
            const std::string childId = children[i];

            if (this->children.count(childId)) {
                BaseActor child = this->children.at(childId);
                child.parent = nullptr;
                this->children.erase(childId);
                this->childRemoved.emit();
            }
        }
    }

    void update();
    void render() override {
        if (!this->visible) {
            return;
        }

        this->calculateRenderedPosition();
    }
};