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
in vec2 fragTexCoord;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gOcclusion;
uniform sampler2D gSpecular;
uniform vec4 colDiffuse;

// Input uniform values
uniform int numOfLights;

uniform float gamma;
uniform float exposure;

// Input lighting values
uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPos;

uniform vec3 ambientColor;
uniform float ambient;

// Output fragment color
out vec4 finalColor;

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

vec3 calculateLightAccum(int i, vec3 fragPosition, vec3 albedo, vec3 N, vec3 V, vec3 baseRefl, float roughness, vec3 specular) {
    vec3 lightAccum = vec3(0.0);
    
    // vec3 LightDir = vec3(lights[i].position.xy - (fragPosition.xy / resolution.xy), lights[i].position.z);
    // LightDir.x *= resolution.x / resolution.y;
    
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
    kD.x *= 1.0 - specular.r;
    kD.y *= 1.0 - specular.g;
    kD.z *= 1.0 - specular.b;

    lightAccum = albedo.rgb* lights[i].enabled; // Angle of light has impact on result

    return lightAccum;
}

void main()
{
    vec4 DiffuseColor = texture(texture0, fragTexCoord);
    if (DiffuseColor.a == 0.0) discard;

    vec3 PositionMap = texture2D(gPosition, fragTexCoord).rgb;

    //RGB of our normal map
	vec3 NormalMap = texture2D(gNormal, fragTexCoord).rgb;

    vec3 OcclusionMap = texture2D(gOcclusion, fragTexCoord).rgb;

    vec3 SpecularMap = texture2D(gSpecular, fragTexCoord).rgb;
    float roughness = 0.5;

    vec3 N = normalize(NormalMap * 2.0 - 1.0);
    vec3 V = normalize(viewPos - PositionMap);

    vec3 baseRefl = mix(vec3(0.04), DiffuseColor.rgb, SpecularMap);

    vec3 lightAccum = vec3(0.0);  // Acumulate lighting lum
    for (int i = 0; i < numOfLights; i++)
    {
        // //The delta position of light
	    // vec3 LightDir = vec3(lights[i].position.xy - (gl_FragCoord.xy / resolution.xy), lights[i].position.z);

        // LightDir.x *= resolution.x / resolution.y;

        // //Determine distance (used for attenuation) BEFORE we normalize our LightDir
	    // float D = length(LightDir);
        
        // //normalize our vectors
        // vec3 L = normalize(LightDir);

        // //Pre-multiply light color with intensity
        // //Then perform "N dot L" to determine our diffuse term
        // vec3 Diffuse = (lights[i].color.rgb * lights[i].color.a) * max(dot(N, L), 0.0);

        // //pre-multiply ambient color with intensity
        // vec3 Ambient = ambientColor.rgb * ambient;
        
        // //calculate attenuation
        // float Attenuation = 1.0 / ( falloff.x + (falloff.y*D) + (falloff.z*D*D) );

        // lightAccum += Ambient + Diffuse * Attenuation;

        lightAccum += calculateLightAccum(i, PositionMap, DiffuseColor.rgb, N, V, baseRefl, roughness, SpecularMap);
    }

    // vec3 FinalColor = DiffuseColor.rgb * lightAccum;

    // finalColor = vec4(FinalColor, DiffuseColor.a);

    vec3 ambientFinal = (ambientColor + DiffuseColor.rbg) * ambient;

    ambientFinal = (ambientFinal + lightAccum * OcclusionMap);

    // HDR tonemapping
    ambientFinal = vec3(1.0) - exp(-ambientFinal * exposure);

    // Gamma correction
    ambientFinal = pow(ambientFinal, vec3(1.0 / gamma));

    finalColor = vec4(ambientFinal, DiffuseColor.a);
}