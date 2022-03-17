#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
out vec2 v_TexCoord;


void main()
{
	gl_Position = position;
	v_TexCoord = texCoord;
}




#shader fragment
#version 330 core

in vec2 v_TexCoord;

out vec4 color;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
	color = texture(u_Texture, v_TexCoord) * u_Color;
}
