#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec4 fragColor;
out vec3 fragNormal;
out mat3 TBN;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    if (texelColor.a == 0.0) discard;
    vec3 N = texelColor.rgb;
    N = normalize(texelColor.rgb * 2.0 - 1.0);
    N = normalize(N * TBN);

    finalColor = vec4(N.x, N.y, N.z, 1.0);
}