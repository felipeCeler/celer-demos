#version 430 core

layout(points) in;
layout(triangle_strip, max_vertices=24) out;


uniform vec4 max_point;
uniform vec4 min_point;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;


out VertexData
{
   vec4 color;
} VertexOut;


void main(void)
{

	float near = 0.1;
	float far  = 500.0;

	vec4 v[8];

	// Top  and bottom face in world coordinates
	v[0] = vec4( max_point.x , max_point.y , max_point.z, 1.0 );
	v[1] = vec4( max_point.x , max_point.y , min_point.z, 1.0 );
	v[2] = vec4( min_point.x , max_point.y , min_point.z, 1.0 );
	v[3] = vec4( min_point.x , max_point.y , max_point.z, 1.0 );

	v[4] = vec4( max_point.x , min_point.y , max_point.z, 1.0 );
	v[5] = vec4( min_point.x , min_point.y , max_point.z, 1.0 );
	v[6] = vec4( min_point.x , min_point.y , min_point.z, 1.0 );
	v[7] = vec4( max_point.x , min_point.y , min_point.z, 1.0 );

	v[0] =  ProjectionMatrix * ViewMatrix * v[0];
	v[1] =  ProjectionMatrix * ViewMatrix * v[1];
	v[2] =  ProjectionMatrix * ViewMatrix * v[2];
	v[3] =  ProjectionMatrix * ViewMatrix * v[3];

	v[4] =  ProjectionMatrix * ViewMatrix * v[4];
	v[5] =  ProjectionMatrix * ViewMatrix * v[5];
	v[6] =  ProjectionMatrix * ViewMatrix * v[6];
	v[7] =  ProjectionMatrix * ViewMatrix * v[7];


	// Top Face
	VertexOut.color = vec4( 1.0,0.0,0.0,1.0);
	gl_Position = v[0]/v[0].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,0.0,0.0,1.0);
	gl_Position = v[1]/v[1].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,0.0,0.0,1.0);
	gl_Position = v[3]/v[3].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,0.0,0.0,1.0);
	gl_Position = v[2]/v[2].w;
	EmitVertex();

	EndPrimitive();

	// Bottom Face
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[4]/v[4].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[5]/v[5].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[7]/v[7].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[6]/v[6].w;
	EmitVertex();

	EndPrimitive();

	// Back Face
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[1]/v[1].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[2]/v[2].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[7]/v[7].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[6]/v[6].w;
	EmitVertex();

	EndPrimitive();

	// Front Face
	VertexOut.color = vec4( 1.0,1.0,0.0,1.0);
	gl_Position = v[0]/v[0].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[3]/v[3].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[4]/v[4].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[5]/v[5].w;
	EmitVertex();

	EndPrimitive();

	// Right Face
	VertexOut.color = vec4( 1.0,0.0,1.0,1.0);
	gl_Position = v[0]/v[0].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[4]/v[4].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[1]/v[1].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[7]/v[7].w;
	EmitVertex();

	EndPrimitive();

	// Left Face
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[2]/v[2].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[6]/v[6].w;
	EmitVertex();
	VertexOut.color = vec4( 0.0,1.0,1.0,1.0);
	gl_Position = v[3]/v[3].w;
	EmitVertex();
	VertexOut.color = vec4( 1.0,1.0,1.0,1.0);
	gl_Position = v[5]/v[5].w;
	EmitVertex();

	EndPrimitive();

}


