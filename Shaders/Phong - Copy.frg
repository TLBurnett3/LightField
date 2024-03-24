#version 440

#define LIGHT_MAX 8

struct Light
{
	bool _switch;
	mat4 _mL;
};

uniform mat4  mM;
uniform Light L[LIGHT_MAX];
uniform int   frustum;

uniform sampler2D uTexture0;     // input texture sampler

in  vec3 vV;
in  vec2 vTC;
in  vec3 vN;

out vec4  finalColor;            // output color

void main() 
{
int lightsUsed = 0;
vec3 integral   = vec3(0);
vec3 vNf        = normalize(vN);

  for (int i = 0; i < LIGHT_MAX; i++)
  {
		if (L[i]._switch)
		{
		mat4 mTmp       = L[i]._mL;

			if (frustum == 0)
			{
				mTmp[3][0] = L[i]._mL[3][0];
				mTmp[3][1] = -L[i]._mL[3][2];
		  	mTmp[3][2] = L[i]._mL[3][1];
			}
			else if (frustum == 1)
			{
	  		mTmp[3][0] = -L[i]._mL[3][0];
			  mTmp[3][1] = L[i]._mL[3][2];
			  mTmp[3][2] = L[i]._mL[3][1];
			}
			else if (frustum == 2)
			{
	  		mTmp[3][0] = L[i]._mL[3][0];
				mTmp[3][1] = -L[i]._mL[3][2];
		  	mTmp[3][2] = -L[i]._mL[3][1];
			}

			{
			vec3  vL        = normalize(vec3(mTmp[3]) - vV);
			vec3  vR        = vec3(reflect(-vL, vNf));
			vec3  cA        = L[i]._mL[0].xyz * mM[0].xyz;
			vec3  cD        = L[i]._mL[1].xyz * dot(vL, vNf);
			float spec      = pow(max(dot(vL, vR), 0.0), 1.0);
			vec3  cS        = L[i]._mL[2].xyz * spec;
	  
				lightsUsed++;
				integral += (cA + cD + cS);
			}
		}

	//debug bright red if no lights enabled 
	if(lightsUsed == 0)
	{
	  finalColor = texture2D(uTexture0,vTC);
	}
	else
	{
	  integral = clamp(integral, 0.0, 1.0);
	  finalColor = texture2D(uTexture0,vTC) * vec4(integral, 1.0);
	}
  }
} 
