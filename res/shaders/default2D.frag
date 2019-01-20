#version 330 core
out vec4 FragColor;

in vec2 texturePos;
in vec4 colorVal;

uniform sampler2D textu;

void main()
{
	FragColor = colorVal;
    //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    //FragColor = mix(texture(texRussia, texPos), texture(texKappa, texPos*5), vec4(texture(texKappa, texPos*5)).a * 0.8);
    //FragColor = texture2D(textu, texPos);
}