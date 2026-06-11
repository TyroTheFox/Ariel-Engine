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
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform sampler2D occlusionMap;

uniform int useTexAlbedo;
uniform int useTexNormal;
uniform int useTexSpecular;
uniform int useTexOcclusion;

// uniform vec2 tiling;
// uniform vec2 offset;

uniform vec4 albedoColor;

uniform float specularValue;
uniform float roughnessValue;
uniform float aoValue;
uniform float emissivePower;

vec3 calculateAlbedo() {
    vec4 albedo = texture(albedoMap, vec2(fragTexCoord.x, fragTexCoord.y));
    if (albedo.a == 0.0) discard;
    vec3 albedoRGB = vec3(albedoColor.x * albedo.x, albedoColor.y * albedo.y, albedoColor.z * albedo.z);

    return albedoRGB;
}

vec4 calculateSpecular() {
    return texture(specularMap, vec2(fragTexCoord.x, fragTexCoord.y));
}

vec3 calculateNormal() {
    vec3 N = texture(normalMap, vec2(fragTexCoord.x, fragTexCoord.y)).rgb;
    N = normalize(N * 2.0 - 1.0);
    N = normalize(N * TBN);

    return N;
}

vec4 calculateOcclusion() {
    return texture(occlusionMap, vec2(fragTexCoord.x, fragTexCoord.y));
}

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = fragPosition;

    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(fragNormal);

    // and the diffuse per-fragment color
    gAlbedo = calculateAlbedo();

    vec4 gSpecular = vec4(0);

    vec4 gOcclusion = vec4(0);

    if (useTexNormal == 1) {
        gNormal = calculateNormal();
    }

    if (useTexOcclusion == 1) {
        gOcclusion = calculateOcclusion();
    }

    if (useTexSpecular == 1) {
        gSpecular = calculateSpecular();
    }

    gEmissive = vec3(emissivePower);
    gMRA = mix(
        vec3(gOcclusion.x + aoValue, gOcclusion.y + aoValue, gOcclusion.z + aoValue), 
        vec3(gSpecular.x + specularValue, gSpecular.y + specularValue, gSpecular.z + specularValue),
        1.0
    ).rgb;

    gMRA = mix(gMRA, vec3(roughnessValue), 1.0);
}
