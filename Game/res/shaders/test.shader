#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 texCoord;
uniform mat4 transform;
uniform mat4 proj;
uniform mat4 view;

void main()
{
	gl_Position = proj * view * transform * vec4(aPos, 1.0);
	texCoord = aTexCoord;
};

#shader fragment

#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture, texCoord);
	//FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
}