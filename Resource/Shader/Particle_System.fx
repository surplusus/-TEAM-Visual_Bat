//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Particle Effects
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Snake
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Single Pass
//--------------------------------------------------------------//
string Particle_Effects_Snake_Single_Pass_Particles : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\QuadArray.3ds";

float4x4 matProjection : ViewProjection;
float4x4 matView : View;
float time_0_X : Time0_X;
float4x4 matWorld;
struct VS_OUTPUT {
   float4 Pos: POSITION;
   float2 texCoord: TEXCOORD0;
   float color: TEXCOORD1;
};
struct VS_INPUT
{
   float4 Pos :POSITION;
};
VS_OUTPUT Particle_Effects_Snake_Single_Pass_Vertex_Shader_main(VS_INPUT Input){
   VS_OUTPUT Out;

   float3 pos;
   // Billboard the quads.
   // The view matrix gives us our right and up vectors.
   pos = 15 * Input.Pos.z * (Input.Pos.x * matView[0] + Input.Pos.y * matView[1]);


   // Move the quads around along some odd path
   float t = time_0_X + 2.0f*Input.Pos.z;
   
   pos.x += 50 * cos(1.24 * t);
   //pos.y += 50 * sin(2.97 * t) * cos(0.81 * t);
   //pos.z += 50 * cos(t) * sin(t * 1.231);

   Out.Pos = mul(matProjection, float4(pos, 1));
   Out.texCoord = Input.Pos.xy;
   Out.color = Input.Pos.z;
      Input.Pos = mul(Out.Pos,matWorld);
   return Out;
}
float particleExp
<
   string UIName = "particleExp";
   string UIWidget = "Numeric";
   bool UIVisible =  true;
   float UIMin = 0.00;
   float UIMax = 0.10;
> = float( 0.70 );
texture Flame_Tex
<
   string ResourceName = ".\\Ez\\ASSETS\\Characters\\Ezreal\\Skins\\Base\\Particles\\Ezreal_Base_Q_mis_trail.dds";
>;
sampler Palette = sampler_state
{
   Texture = (Flame_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
   MIPFILTER = LINEAR;
   ADDRESSU = CLAMP;
   ADDRESSV = CLAMP;
   ADDRESSW = CLAMP;
};
texture Texture1_Tex
<
   string ResourceName = ".\\Ez\\ASSETS\\Characters\\Ezreal\\Skins\\Base\\Particles\\Ezreal_Ashe_Base_ground_CrackNoise_mult.dds";
>;
sampler Texture1 = sampler_state
{
   Texture = (Texture1_Tex);
};
struct PS_INPUT
{
   float2 texCoord: TEXCOORD0;
   float2 texCoord1:TEXCOORD1;
    float color: TEXCOORD1;
};
float4 Particle_Effects_Snake_Single_Pass_Pixel_Shader_main(PS_INPUT Input) : COLOR {
   float4 albedo  = tex2D(Palette,Input.texCoord);
   float4 albedo2 = tex2D(Texture1,Input.texCoord1);
   float4 tex =  (albedo+albedo2)*albedo.a;
   return (1 - pow(dot(Input.texCoord, Input.texCoord), particleExp))*tex ;
   
}


//--------------------------------------------------------------//
// Technique Section for Particle Effects
//--------------------------------------------------------------//
technique Snake
{
   pass Single_Pass
   {
      ZWRITEENABLE = FALSE;
      SRCBLEND = ONE;
      DESTBLEND = ONE;
      CULLMODE = NONE;
      ALPHABLENDENABLE = TRUE;

      VertexShader = compile vs_3_0 Particle_Effects_Snake_Single_Pass_Vertex_Shader_main();
      PixelShader = compile ps_3_0 Particle_Effects_Snake_Single_Pass_Pixel_Shader_main();
   }

}

