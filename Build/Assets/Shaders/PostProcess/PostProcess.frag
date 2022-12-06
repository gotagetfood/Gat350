#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 
    
uniform sampler2D textureMap; 
  
void main() 
{ 
    vec3 color = texture(textureMap, texcoord).rgb; 
    // black / white 
    vec3 avg = {color.b , color.r , color.g}; 
    fcolor = vec4(avg, 1); 
} 
