#version 410

uniform sampler2D texSampler; // input texture sampler

in  vec2  vTC;         // input texture coordinate
out vec4  finalColor;  // output color

void main() 
{
  finalColor = texture(texSampler,vTC);
} 
