#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D gAlbedo;
uniform sampler2D gNormal;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(gAlbedo, fragTexCoord);
    if (texelColor.a == 0.0) discard;
    finalColor = texelColor * fragColor * colDiffuse;
}