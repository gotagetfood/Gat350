#version 430 core

in vec3 reflection_dir;

out vec4 fcolor;

uniform samplerCube cubeMap;

void main()
{
	//vec4 color1 = texture(cubeMap, refracton_dir);
	//mix(color1, color2);
	
	fcolor = texture(cubeMap, reflection_dir);
}
