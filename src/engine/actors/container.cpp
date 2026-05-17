#include <engine/actors/container.h>

Container::Container(std::string name) {
    this->id = name;
    this->children = std::map<std::string, BaseActor*>{};
}

Container::~Container() {}

void Container::addChildren(BaseActor* addedActor) {
    addedActor->parent = this;
    this->children.insert({addedActor->id, addedActor});
    this->childAdded.emit();
}

void Container::removeChildren(std::string childId) {
    if (this->children.count(childId)) {
        BaseActor* child = this->children.at(childId);
        child->parent = nullptr;
        this->children.erase(childId);
        this->childRemoved.emit();
    }
}

void Container::update(float dT) {}

void Container::render() {
    if (!this->visible) {
        return;
    }

    this->calculateRenderedPosition();
}