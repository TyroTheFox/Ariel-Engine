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
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform sampler2D gNormal;
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

uniform vec2 resolution;
uniform vec3 falloff;

// Output fragment color
out vec4 finalColor;

void main()
{
    vec4 DiffuseColor = texture(texture0, fragTexCoord);
    if (DiffuseColor.a == 0.0) discard;

    //RGB of our normal map
	vec3 NormalMap = texture2D(gNormal, fragTexCoord).rgb;

    vec3 lightAccum = vec3(0.0);  // Acumulate lighting lum
    for (int i = 0; i < numOfLights; i++)
    {
        //The delta position of light
	    vec3 LightDir = vec3(lights[i].position.xy - (gl_FragCoord.xy / resolution.xy), lights[i].position.z);

        LightDir.x *= resolution.x / resolution.y;

        //Determine distance (used for attenuation) BEFORE we normalize our LightDir
	    float D = length(LightDir);
        
        //normalize our vectors
        vec3 N = normalize(NormalMap * 2.0 - 1.0);
        vec3 L = normalize(LightDir);

        //Pre-multiply light color with intensity
        //Then perform "N dot L" to determine our diffuse term
        vec3 Diffuse = (lights[i].color.rgb * lights[i].color.a) * max(dot(N, L), 0.0);

        //pre-multiply ambient color with intensity
        vec3 Ambient = ambientColor.rgb * ambient;
        
        //calculate attenuation
        float Attenuation = 1.0 / ( falloff.x + (falloff.y*D) + (falloff.z*D*D) );

        lightAccum += Ambient + Diffuse * Attenuation;
    }

    vec3 FinalColor = DiffuseColor.rgb * lightAccum;

    finalColor = vec4(FinalColor, DiffuseColor.a);
}