// application exposed variables
float4x4 gWorldInv : WORLD; // Value sent in

// global direction of light
float3 gLightDir[20];  // Value sent in


// Light
float3 gLightPos[20]; // Value sent in
float gInnerCone[20];
float gOuterCone[20];
float3 gColor[20];
float gAttenuation = 2.7f;

// texture to be used
Texture2D gDiffuseTexture : DIFFUSE = NULL;
// the matching sampler

sampler gDiffuseSampler = sampler_state 
{
    Texture = <gDiffuseTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

// create vertex shader inputs (must match the vertex declalightRation in C++)
struct VS_INPUT
{
    float3 untransformed_pos	: POSITION0;
	float3 untransformed_norm	: NORMAL0;
	float2 uv					: TEXCOORD0;
};

// vertex shader outputs
struct VS_OUTPUT
{
    float4 transformed_pos	: POSITION0;
    float3 transformed_norm	: TEXCOORD0;
	float3 world_pos		: TEXCOORD1;
	float2 uv				: TEXCOORD2;
};

VS_OUTPUT myVertexShader(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float4 worldloc = float4(input.untransformed_pos, 1.0f);
	float4 worldnrm = float4(input.untransformed_norm, 0.0f);
	output.transformed_pos = float4(input.untransformed_pos, 1.0f);
	output.world_pos = worldloc.xyz;
   	output.transformed_norm = worldnrm.xyz;
	output.uv = input.uv;
	return output; 
}

float4 myPixelShader(VS_OUTPUT input) : COLOR
{
	float3 surfacecolor = float3(0,0,0);
	surfacecolor = tex2D(gDiffuseSampler, input.uv);
	float3 ambientLight = {1,1,1};
	float3 final = float3(0,0,0);
	for( int i = 0; i < 20; ++i)
	{
		float3 ldir = float3(0,0,0);
		float3 lightPos = mul(float4(gLightPos[i], 1), gWorldInv).xyz;
		float3 	wnrm = normalize(input.transformed_norm);
		float attenuation = 0;

		ldir = normalize(lightPos - input.world_pos);
		attenuation = 1.0 - saturate( abs(ldir)/ gAttenuation);
		float spotLightAmount = saturate( dot(normalize(-gLightDir[i]), ldir));
		float lightRatio = 0;
		if(spotLightAmount > gInnerCone[i])
			lightRatio = 1;
		else if(spotLightAmount > gOuterCone[i])
			lightRatio = 1.0 - saturate((gInnerCone[i] - spotLightAmount)/ (gInnerCone[i] - gOuterCone[i]));
		final += saturate( (lightRatio *  attenuation * gColor[i]));
	}
	final += (ambientLight);
	final = saturate(final)* surfacecolor;
	return float4(final,1);
}

technique myTechnique
{
    pass FirstPass
    {
        vertexShader = compile vs_3_0 myVertexShader();
        pixelShader  = compile ps_3_0 myPixelShader();

		//ShadeMode = GOURAUD; // smooth color interpolation across triangles
        //FillMode = SOLID; // no wireframes, no point drawing.
		ZEnable = FALSE;
       //CullMode = NONE; // cull any counterclockwise polygons.
    }
}
