//--------------------------------------------------------------------------------------
// File: Tutorial06.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------



Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );


cbuffer cbChangeOnResize : register( b1 )
{
    matrix Projection;
};

cbuffer cbChangesEveryFrame : register( b2 )
{
    float Waviness;
    float Time;
    matrix World;
    matrix View;
    float4 vMeshColor;
    float4 vLightDir[3];
    float4 vLightColor[3];
    float4 vOutputColor;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL0;
    float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : NORMAL;
    float2 Tex : TEXCOORD0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;


    output.Pos = mul( input.Pos, World );
    output.Pos.x +=  sin( output.Pos.y*1.1f + Time )*Waviness;
    //output.Pos.y += sin( output.Pos.y*0.1f + Time )*Waviness;
    //output.Pos.z += sin( output.Pos.y*1.0f + Time )*Waviness;
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Norm = mul( input.Norm, World );
    
    output.Tex = input.Tex;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{
    float4 finalColor = 0;
    
    //do NdotL lighting for 3 lights
    for(int i=0; i<3; i++)
    {
        finalColor += saturate( dot( (float3)vLightDir[i],input.Norm) * vLightColor[i] );
	//finalColor += saturate( dot( (float3)vLightDir[i],input.Norm) * vMeshColor );
	//finalColor += saturate( dot( (float3)vLightDir[i],input.Norm) * input.Color );
	//finalColor += saturate(vLightColor[i]);
    }
    //finalColor += saturate( dot( (float3)vLightDir[0],input.Norm) * input.Color );
    //finalColor += saturate( dot( (float3)vLightDir[0],input.Norm) * vMeshColor );
    finalColor.a = 1;
    //return finalColor;
    return txDiffuse.Sample( samLinear, input.Tex ) * finalColor;
}


//--------------------------------------------------------------------------------------
// PSSolid - render a solid color
//--------------------------------------------------------------------------------------
float4 PSSolid( PS_INPUT input) : SV_Target
{
    return vOutputColor;
}
