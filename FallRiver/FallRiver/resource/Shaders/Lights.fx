// application exposed variables
float4x4 gWorldInv : WORLD; // Value sent in

// global direction of light
float3 gLightDir : DIRECTION  // Value sent in
< string Object = "DirectionalLight"; >
= { 0, 0, 1 };

float3 gLightDir2 // Value sent in
= { 0, 1, 0 };

// Light
float3 gLightPos = {0,0,-.5}; // Value sent in
float3 gLightPos2 = {0,0,0}; // Value sent in
float gInnerCone  = 0.75f;
float gOuterCone  = 0.7f;
float gInnerCone2  = 0.75f;
float gOuterCone2  = 0.7f;
float gAttenuation = 2.7f;
float3 lightColor = float3(0.5,0.5,0.5);
float3 ambientLight;


// Other Lights
int gLightNum;
float3 gLightPos3[6] = {float3(0,0,-1), float3(0,0,-1), float3(0,0,-1), float3(0,0,-1), float3(0,0,-1), float3(0,0,-1)};
float3 gLightDir3[6] = {float3(0,0,1), float3(0,0,1), float3(0,0,1), float3(0,0,1), float3(0,0,1), float3(0,0,1)};
float gInnerCone3[6];
float gOuterCone3[6];
float3 lightColor3[6];


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

	float3 final = float3(0,0,0);
	float3 ldir = float3(0,0,0);
	float3 lightPos = mul(float4(gLightPos, 1), gWorldInv).xyz;
	float3 lightPos2 = mul(float4(gLightPos2, 1), gWorldInv).xyz;
	
	float3 	wnrm = normalize(input.transformed_norm);
	float diffuseLightAmount = 0;
	float attenuation = 0;
	surfacecolor = tex2D(gDiffuseSampler, input.uv);
	
	ldir = normalize(lightPos - input.world_pos);
	attenuation = 1.0 - saturate( abs(ldir)/ gAttenuation);
	float spotLightAmount = saturate( dot(normalize(-gLightDir), ldir));
	float lightRatio = 0;
	if(spotLightAmount > gInnerCone)
		lightRatio = 1;
	else if(spotLightAmount > gOuterCone)
		lightRatio = 1.0 - saturate((gInnerCone - spotLightAmount)/ (gInnerCone - gOuterCone));
		
	final = saturate( (lightRatio *  attenuation * lightColor));
		
	ldir = normalize(lightPos2 - input.world_pos);
	attenuation = 1.0 - saturate( abs(ldir)/ gAttenuation);
	spotLightAmount = saturate( dot(normalize(-gLightDir2), ldir));
	lightRatio = 0;
	if(spotLightAmount > gInnerCone2)
		lightRatio = 1;
	else if(spotLightAmount > gOuterCone2)
		lightRatio = 1.0 - saturate((gInnerCone2 - spotLightAmount)/ (gInnerCone2 - gOuterCone2));	
		
	final += saturate( (lightRatio *  attenuation * lightColor ));
	
	// Other Lights
	for( int i = 0; i < 6; ++i)
	{
		if( i < gLightNum)
		{
		lightPos = mul(float4(gLightPos3[i], 1), gWorldInv).xyz;
		ldir = normalize(lightPos - input.world_pos);
		attenuation = 1.0 - saturate( abs(ldir)/ gAttenuation);
		spotLightAmount = saturate( dot(normalize(-gLightDir3[i]), ldir));
		lightRatio = 0;
		if(spotLightAmount > gInnerCone3[i])
			lightRatio = 1;
		else if(spotLightAmount > gOuterCone3[i])
			lightRatio = 1.0 - saturate((gInnerCone3[i] - spotLightAmount)/ (gInnerCone3[i] - gOuterCone3[i]));	
			
		final += saturate( (lightRatio * attenuation * lightColor3[i] ));
		}
	}
	final = saturate(final  + (ambientLight)) * surfacecolor;
		
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
       //CullMode = CCW; // cull any counterclockwise polygons.
    }
}
