#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedo;
layout (location = 3) out vec3 gOcclusion;
layout (location = 4) out vec3 gSpecular;

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

vec3 calculateAlbedo() {
    vec3 albedo = texture(albedoMap, vec2(fragTexCoord.x, fragTexCoord.y)).rgb;
    albedo = vec3(albedoColor.x * albedo.x, albedoColor.y * albedo.y, albedoColor.z * albedo.z);

    return albedo;
}

vec3 calculateSpecular() {
    return texture(specularMap, vec2(fragTexCoord.x, fragTexCoord.y)).rgb;
}

vec3 calculateNormal() {
    vec3 N = texture(normalMap, vec2(fragTexCoord.x, fragTexCoord.y)).rgb;
    N = normalize(N * 2.0 - 1.0);
    N = normalize(N * TBN);

    return N;
}

vec3 calculateOcclusion() {
    return texture(occlusionMap, vec2(fragTexCoord.x, fragTexCoord.y)).rgb;
}

void main()
{
    // store the fragment position vector in the first gbuffer texture
    gPosition = fragPosition;

    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(fragNormal);

    // and the diffuse per-fragment color
    gAlbedo = calculateAlbedo();

    gSpecular = vec3(0);

    gOcclusion = vec3(0);

    if (useTexNormal == 1) {
        gNormal = calculateNormal();
    }

    if (useTexOcclusion == 1) {
        gOcclusion = calculateOcclusion();
    }

    if (useTexSpecular == 1) {
        gSpecular = calculateSpecular();
    }
}
