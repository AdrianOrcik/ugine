#type vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 uViewProjection;
uniform mat4 uTransform; 

out vec2 vTexCoord;

void main()
{
	vTexCoord = aTexCoord;
	gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0f);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform vec3 uColor;

void main()
{
	color = texture(uTexture, vTexCoord) * vec4(1.0, 0.8, 0.8, 1.0);
}