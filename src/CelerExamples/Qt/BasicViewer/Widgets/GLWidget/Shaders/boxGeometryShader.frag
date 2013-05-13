#version 430 core


in VertexData
{
   vec4 color;
} VertexOut;

out vec4 outputColor;

in vec2 texcoord;

void main(void)
{
	outputColor = VertexOut.color ;
}
