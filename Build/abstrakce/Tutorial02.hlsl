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
    float4 Color : COLOR0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : NORMAL;
    float4 Color : COLOR0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;

//input.Pos = mul( input.Pos, View );
    output.Pos = mul( input.Pos, World );
    //output.Pos.x +=  sin( output.Pos.y*1.1f + Time )*Waviness;
    //output.Pos.y += sin( output.Pos.y*0.1f + Time )*Waviness;
    //output.Pos.z += sin( output.Pos.y*1.0f + Time )*Waviness;
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
 
    //output.Norm = mul( input.Norm, World );
    
    output.Color = input.Color;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{
    
    
   
    return input.Color;
   
}


//--------------------------------------------------------------------------------------
// PSSolid - render a solid color
//--------------------------------------------------------------------------------------
float4 PSSolid( PS_INPUT input) : SV_Target
{
    return vOutputColor;
}
