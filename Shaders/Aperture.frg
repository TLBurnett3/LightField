#version 410

//-----------------------------------------------------------------------------
// Defines
#define MAX_HOMOGRAPHIES  512
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
layout (std140) uniform Homographies 
{
  mat4 mH[MAX_HOMOGRAPHIES];
};

uniform sampler2D texSampler;                 // input texture sampler 0 

uniform ivec2        iIdx;                    // sub image index
uniform ivec2        nI;                      // number of images
uniform float        aD;                      // aperture diameter (0 to 1.0)

uniform ivec2        iS;                      // size of a subimage and rendered image size

in  vec2  vTC;                                // input texture coordinate
out vec4  finalColor;                         // output color
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------
void main() 
{
vec2    fx    = vTC * vec2(iS);                   // convert to image space (0,0 to image size)
ivec2   aRad  = ivec2(vec2(nI) * aD * 0.5);
ivec2   bIdx  = iIdx - aRad;
ivec2   eIdx  = iIdx + aRad;
vec4    clr   = vec4(0); 
float   n     = 0;
ivec2   idx;   

  bIdx = clamp(bIdx,ivec2(0),nI - 1);
  eIdx = clamp(eIdx,ivec2(0),nI - 1);
 
  for (idx.y = bIdx.y;idx.y <= eIdx.y;idx.y++)   
  {
    for (idx.x = bIdx.x;idx.x <= eIdx.x;idx.x++) 
    {
    int   i   = (idx.y * nI.x) + idx.x;
    vec2  dx  = vec2(idx) / vec2(nI);            // location of subimage within plenoptic image
    vec2  lfx = vec2(mH[i] * vec4(fx,0,1));      // apply homography

      lfx /= vec2(iS);                           // convert back to texture space
      lfx /= vec2(nI);                           // offset within subimage
      dx   += lfx;                               // add location of subimage

      clr  += texture(texSampler,dx);            // running sum of color
      n++;
    }
  }

  finalColor = clr / n;
}

