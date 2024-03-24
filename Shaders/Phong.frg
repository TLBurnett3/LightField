#version 440

uniform sampler2D texSampler;    
uniform vec3      lightPosition;  
uniform vec4      lightAmbient;  
uniform vec4      lightDiffuse;  
uniform vec4      lightSpecular;  
uniform vec3      cameraPosition;  

in vec3 vV;
in vec2 vTC;
in vec3 vN;
in vec3 vFPos;

out vec4  finalColor;             

void main() 
{
vec4 cT = texture(texSampler,vTC);
vec3 vL = normalize(lightPosition - vFPos);
vec3 vR = reflect(-vL,vN);
vec3 vC = normalize(cameraPosition - vFPos);
vec4 cA = lightAmbient  * cT;
vec4 cD = max(dot(vN,vL),0.0) * lightDiffuse  * cT;
vec4 cS = pow(max(dot(vC,vR),0.0), 32) * lightSpecular * cT; 

  finalColor = clamp((cA + cD + cS),0.0,1.0);
} 
