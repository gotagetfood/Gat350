#version 430 core
 
in vec3 position;
//in vec3 normal;
in vec2 texcoord;
in mat3 tbn;

out vec4 fcolor; //pizel to draw

struct Light {
	vec3 ambient;
	vec3 color;
	vec4 position;
};

struct Material{
	vec3 color;
	float shininess;

	vec2 uv_tilling;
	vec2 uv_offset;
};

uniform Light light;
uniform Material material;
 
layout (binding = 0) uniform sampler2D diffuseMap;
layout (binding = 1) uniform sampler2D normalMap;
layout (binding = 2) uniform sampler2D specularMap;
layout (binding = 3) uniform sampler2D emissiveMap; 

void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	//ambient
	ambient = light.ambient * material.color;

	//calculate light direction (unit vector)
	vec3 light_dir = normalize(vec3(light.position) - position);

	//calculate light intensity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal), 0);
	// caluclate diffuse color
	diffuse = light.color * material.color * intensity;

	//Specular
	specular = vec3(0);
	if (intensity > 0){
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}
}
 
void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	
	vec2 ttexcoord = (texcoord * material.uv_tilling) + material.uv_offset;
	vec3 normal = texture(normalMap, ttexcoord).rgb;

	normal = (normal * 2) - 1;
	normal = normalize(tbn * normal);

	phong(position, normal, ambient, diffuse, specular);
	
	vec4 diffuseColor = texture(diffuseMap, ttexcoord);
	vec4 specularColor = texture(specularMap, ttexcoord);
	vec4 emissiveColor = texture(emissiveMap, ttexcoord);

	fcolor	= emissiveColor + vec4(ambient + diffuse,1) * diffuseColor + (vec4(specular,1) * specularColor);

	// 0 - 1 -> -1 - 1

	


	// vec4 texture_color = texture(diffuseMap,ttexcoord);
	///vec4 texture_color = mix(texture(texture1,ttexcoord), texture(texture2, ttexcoord),0.4);

	//fcolor = texture_color;
	 //fcolor = vec4(ambient + diffuse, 1) * diffuseColor + (vec4(specular, 1));

}
