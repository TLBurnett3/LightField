#version 410

//-----------------------------------------------------------------------------
uniform sampler2D   texSampler;                 // input texture sampler 0 

uniform vec2        iIdx;                       // sub image index
uniform vec2        nI;                         // number of images
uniform float       aD;                         // aperture diameter (0 to 1.0)

in  vec2  vTC;                                  // input texture coordinate
out vec4  finalColor;                           // output color
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------
void main() 
{
float aR   = min(nI.x,nI.y);
vec2  cX;

  cX.x   =       (iIdx.x / nI.x) + (1 / nI.x * 0.5);
  cX.y   = 1.0 - (iIdx.y / nI.y) - (1 / nI.y * 0.5);
 
  aR = 1.0 / aR / 2.0;
  aR = max(aD * 0.5,aR);

  finalColor  = texture(texSampler,vTC); 

  cX -= vTC;

  if (length(cX) < aR)
    finalColor.g  = 1;   
}

