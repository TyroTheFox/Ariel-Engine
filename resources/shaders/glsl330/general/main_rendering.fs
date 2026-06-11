#version 330

#define MAX_LIGHTS              128

#define LIGHT_DIRECTIONAL       0
#define LIGHT_POINT             1

#define PI 3.14159265358979323846

struct Light {
    int enabled;
    int type;
    vec3 position;
    vec3 target;
    vec4 color;
    float intensity;
};

// Input vertex attributes (from vertex shader)
in vec2 texCoord;

// Output fragment color
out vec4 finalColor;

// gBuffer values
uniform sampler2D gPosition;
uniform sampler2D gNormal;

uniform sampler2D gAlbedo;
uniform sampler2D gEmissive;
uniform sampler2D gMRA;

uniform sampler2D gOcclusion;
uniform sampler2D gSpecular;

// Input uniform values
uniform int numOfLights;

uniform float gamma;
uniform float exposure;

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPos;

uniform vec3 ambientColor;
uniform float ambient;

// Reflectivity in range 0.0 to 1.0
// NOTE: Reflectivity is increased when surface view at larger angle
vec3 SchlickFresnel(float hDotV, vec3 refl) {
    return refl + (1.0 - refl) * pow(clamp(1.0 - hDotV, 0.0, 1.0), 5.0);
}

float GgxDistribution(float nDotH,float roughness)
{
    float a = roughness * roughness * roughness * roughness;
    float d = nDotH * nDotH * (a - 1.0) + 1.0;
    d = PI * d * d;
    return (a / max(d, 0.0000001));
}

float GeomSmith(float nDotV,float nDotL,float roughness)
{
    float r = roughness + 1.0;
    float k = r * r / 8.0;
    float ik = 1.0 - k;
    float ggx1 = nDotV / (nDotV * ik + k);
    float ggx2 = nDotL / (nDotL * ik + k);
    return ggx1 * ggx2;
}

vec3 calculateRadiance(vec3 fragPosition, vec3 lightPosition, vec4 lightColor, float lightIntensity) {
    float dist = length(lightPosition - fragPosition);     // Compute distance to light
    float attenuation = 1.0 / (dist * dist);                   // Compute attenuation
    vec3 radiance = lightColor.rgb * lightIntensity * attenuation; // Compute input radiance, light energy comming in

    return radiance;
}

vec3 calculateLightAccum(int i, vec3 fragPosition, vec3 albedo, vec3 N, vec3 V, vec3 baseRefl, float roughness, vec3 metallic) {
    vec3 lightAccum = vec3(0.0);
    
    vec3 L = normalize(lights[i].position - fragPosition);      // Compute light vector
    vec3 H = normalize(V + L);                             // Compute halfway bisecting vector

    // Cook-Torrance BRDF distribution function
    float nDotV = max(dot(N,V), 0.0000001);
    float nDotL = max(dot(N,L), 0.0000001);
    float hDotV = max(dot(H,V), 0.0);
    float nDotH = max(dot(N,H), 0.0);

    float D = GgxDistribution(nDotH, roughness);    // Larger the more micro-facets aligned to H
    float G = GeomSmith(nDotV, nDotL, roughness);   // Smaller the more micro-facets shadow
    vec3 F = SchlickFresnel(hDotV, baseRefl);       // Fresnel proportion of specular reflectance

    vec3 radiance = calculateRadiance(fragPosition, lights[i].position, lights[i].color, lights[i].intensity);
    vec3 spec = (D * G * F) / (4.0 * nDotV * nDotL);

    // Difuse and spec light can't be above 1.0
    // kD = 1.0 - kS  diffuse component is equal 1.0 - spec comonent
    vec3 kD = vec3(1.0) - F;

    // Mult kD by the inverse of metallnes, only non-metals should have diffuse light
    kD.x *= 1.0 - metallic.r;
    kD.y *= 1.0 - metallic.g;
    kD.z *= 1.0 - metallic.b;

    lightAccum = ((kD * albedo.rgb / PI + spec) * radiance * nDotL) * lights[i].enabled; // Angle of light has impact on result

    return lightAccum;
}

vec3 ComputePBR()
{
    vec3 fragPosition = texture(gPosition, texCoord).rgb;
    vec3 fragNormal = texture(gNormal, texCoord).rgb;

    vec3 albedo = texture(gAlbedo, texCoord).rgb;

    float metallic = texture(gMRA, texCoord).r;
    float roughness = texture(gMRA, texCoord).g;
    float ao = texture(gMRA, texCoord).b;

    vec3 emissive = texture(gEmissive, texCoord).rgb;

    // vec3 SpecularMap = texture2D(gSpecular, texCoord).rgb;

    // vec3 OcclusionMap = texture2D(gOcclusion, texCoord).rgb;

    vec3 N = normalize(fragNormal);
    vec3 V = normalize(viewPos - fragPosition);

    vec3 baseRefl = vec3(0);
    vec3 metallicVec = vec3(0);

    // If  dia-electric use base reflectivity of 0.04 otherwise ut is a metal use albedo as base reflectivity
    baseRefl = mix(vec3(0.04), albedo.rgb, metallic);
    metallicVec = vec3(metallic, metallic, metallic);

    vec3 lightAccum = vec3(0.0);  // Acumulate lighting lum

    for (int i = 0; i < numOfLights; i++)
    {
        lightAccum += calculateLightAccum(i, fragPosition, albedo, N, V, baseRefl, roughness, metallicVec);
    }

    vec3 ambientFinal = (ambientColor + albedo) * ambient * vec3(0.03);

    return (ambientFinal + lightAccum * ao + emissive);
}

void main()
{
    vec3 color = ComputePBR();

    // HDR tonemapping
    color = vec3(1.0) - exp(-color * exposure);

    // Gamma correction
    color = pow(color, vec3(1.0 / gamma));

    finalColor = vec4(color, 1.0);
}