#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedo;
layout (location = 3) out vec3 gEmissive;
layout (location = 4) out vec3 gMRA;

in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;
in mat3 TBN;

uniform sampler2D albedoMap;
uniform sampler2D mraMap;
uniform sampler2D normalMap;
uniform sampler2D emissiveMap; // r: Hight g:emissive

uniform int useTexAlbedo;
uniform int useTexNormal;
uniform int useTexMRA;
uniform int useTexEmissive;

uniform vec2 tiling;
uniform vec2 offset;

uniform vec4 albedoColor;
uniform vec4 emissiveColor;

uniform float normalValue;
uniform float metallicValue;
uniform float roughnessValue;
uniform float aoValue;
uniform float emissivePower;

vec3 calculateAlbedo() {
    vec3 albedo = texture(albedoMap, vec2(fragTexCoord.x * tiling.x + offset.x, fragTexCoord.y * tiling.y + offset.y)).rgb;
    albedo = vec3(albedoColor.x * albedo.x, albedoColor.y * albedo.y, albedoColor.z * albedo.z);

    return albedo;
}

vec4 calculateMRA() {
    vec4 mra = texture(mraMap, vec2(fragTexCoord.x * tiling.x + offset.x, fragTexCoord.y * tiling.y + offset.y));
    return mra;
}

vec3 calculateNormal() {
    vec3 N = texture(normalMap, vec2(fragTexCoord.x * tiling.x + offset.y, fragTexCoord.y * tiling.y + offset.y)).rgb;
    N = normalize(N * 2.0 - 1.0);
    N = normalize(N * TBN);

    return N;
}

vec3 calculateEmissive() {
    return (texture(emissiveMap, vec2(fragTexCoord.x * tiling.x + offset.x, fragTexCoord.y * tiling.y + offset.y)).rgb).g * emissiveColor.rgb * emissivePower;
}

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = fragPosition;

    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(fragNormal);

    // and the diffuse per-fragment color
    gAlbedo = calculateAlbedo();

    gEmissive = vec3(0);

    float metallic = clamp(metallicValue, 0.0, 1.0);
    float roughness = clamp(roughnessValue, 0.0, 1.0);
    float ao = clamp(aoValue, 0.0, 1.0);

    if (useTexNormal == 1) {
        gNormal = calculateNormal();
    }

    if (useTexMRA == 1) {
        vec4 mra = calculateMRA();

        metallic = clamp(mra.r + metallicValue, 0.04, 1.0);
        roughness = clamp(mra.g + roughness, 0.04, 1.0);
        ao = (mra.b + aoValue) * 0.5;
    }

    if (useTexEmissive == 1) {
        gEmissive = calculateEmissive();
    }

    gMRA = vec3(metallic, roughness, ao);
}
