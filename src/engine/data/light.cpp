#include <engine/data/light.h>

Light::Light(std::string id, int type, int lightsCount, raylib::Vector3 position, raylib::Vector3 target, float intensity, raylib::Color color, raylib::Shader* shader) {
    this->enabled = true;
    this->type = type;
    this->position = position;
    this->target = target;
    this->color = color;
    this->intensity = intensity;

    this->id = id;
    this->lightID = lightsCount;

    // NOTE: Lighting shader naming must be the provided ones
    this->enabledLoc = shader->GetLocation(TextFormat("lights[%i].enabled", lightsCount));
    this->typeLoc = shader->GetLocation(TextFormat("lights[%i].type", lightsCount));
    this->positionLoc = shader->GetLocation(TextFormat("lights[%i].position", lightsCount));
    this->targetLoc = shader->GetLocation(TextFormat("lights[%i].target", lightsCount));
    this->colorLoc = shader->GetLocation(TextFormat("lights[%i].color", lightsCount));
    this->intensityLoc = shader->GetLocation(TextFormat("lights[%i].intensity", lightsCount));

    UpdateLightValues(shader);
}

Light::~Light() {
}

raylib::Color Light::getColor() {
    return this->color;
}

bool Light::isEnabled() {
    return this->enabled;
}

raylib::Vector3 Light::getPosition() {
    return this->position;
}

void Light::UpdateLightValues(raylib::Shader* shader) {
    // Send to shader light enabled state and type
    shader->SetValue(this->enabledLoc, &this->enabled, SHADER_UNIFORM_INT);
    shader->SetValue(this->typeLoc, &this->type, SHADER_UNIFORM_INT);

    // Send to shader light position values
    float position[3] = { this->position.x, this->position.y, this->position.z };
    shader->SetValue(this->positionLoc, position, SHADER_UNIFORM_VEC3);

    // Send to shader light color values
    float color[4] = { 
        (float)this->color.r/(float)255, 
        (float)this->color.g/(float)255,
        (float)this->color.b/(float)255, 
        (float)this->color.a/(float)255 
    };

    // Send to shader light target position values
    float target[3] = { this->target.x, this->target.y, this->target.z };
    shader->SetValue(this->targetLoc, target, SHADER_UNIFORM_VEC3);
    shader->SetValue(this->colorLoc, color, SHADER_UNIFORM_VEC4);
    shader->SetValue(this->intensityLoc, &this->intensity, SHADER_UNIFORM_FLOAT);
}