// application exposed variables
float4x4 gWorld : WORLD; // Value sent in
float4x4 gViewProjection : VIEWPROJECTION; // Value sent in

// global direction of light
float3 gLightDir : DIRECTION  // Value sent in
< string Object = "DirectionalLight"; >
= { 0, 0, 1 };

// Light
float3 gLightPos = {0,0,0}; // Value sent in
float gInnerCone  = 0.95f;
float gOuterCone  = 0.9f;
float gAttenuation = 2.7f;
// 0 - Default Spotlight, 1 - Flashlight, 2 - Lighter, 3 - Mag light, 4 - Lantern 
int gSetting;  // Value sent in 

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
	worldloc = mul(worldloc, gWorld);
	worldnrm = normalize(mul(worldnrm, gWorld));
	//output.transformed_pos = mul(worldloc, gViewProjection);
	output.world_pos = worldloc.xyz;
   	output.transformed_norm = worldnrm.xyz;
	output.uv = input.uv;
	/* if(gSetting == 0)
	{
		gInnerCone = ;
		gOuterCone = ;
	}
	else if(gSetting == 2)
	{
		gInnerCone = ;
		gOuterCone = ;
	}
	else if(gSetting == 4)
	{
		gInnerCone = ;
		gOuterCone = ;
	} */
	// Test Below
	output.transformed_pos = float4(input.untransformed_pos, 1.0f);
	return output; 
}

float4 myPixelShader(VS_OUTPUT input) : COLOR
{
	/*float3 ambientLight = {0.25,0.25,0.25};
	float3 surfacecolor = float3(0,0,0);
	float3 final = float3(0,0,0);
	float3 ldir = float3(0,0,0);

	float3 	wnrm = normalize(input.transformed_norm);
	float diffuseLightAmount = 0;
	float attenuation = 0;
	
	if(gSetting == 1 || gSetting == 3)
	{
		ldir = -normalize(gLightDir);
		diffuseLightAmount = saturate(dot(ldir, wnrm));
		final = saturate( diffuseLightAmount * surfacecolor  + (ambientLight * surfacecolor));
	}
	else
	{
		ldir = normalize(gLightPos - input.world_pos);
		attenuation = 1.0 - saturate( abs(ldir)/ gAttenuation);
		diffuseLightAmount = saturate(dot(ldir, wnrm));
		float spotLightAmount = saturate( dot(normalize(-gLightDir), ldir));
		float lightRatio = 0;
		if(spotLightAmount > gInnerCone)
			lightRatio = 1;
		else if(spotLightAmount > gOuterCone)
			lightRatio = 1.0 - saturate((gInnerCone - spotLightAmount)/ (gInnerCone - gOuterCone));
		final = saturate( (lightRatio * diffuseLightAmount * attenuation * surfacecolor) + (ambientLight * surfacecolor));
	}*/
	//return float4(final,1);
	return tex2D(gDiffuseSampler, input.uv);
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
       //CullMode = CCW; // cull any counterclockwise polygons.
    }
}
