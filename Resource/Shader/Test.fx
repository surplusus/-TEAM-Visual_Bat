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
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Default_DirectX_Effect_Pass_0_Model : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 matProjection : Projection;
float4x4 matView : View;
float4x4 matWorld : World;
struct VS_INPUT 
{
   float4 mPosition : POSITION0;
   float2 mTexCoord : TEXCOORD0;
   
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION0;
   float2 mTexCoord : TEXCOORD0;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.mPosition = mul( Input.mPosition  , matWorld );
   Output.mPosition = mul( Output.mPosition , matView);
   Output.mPosition = mul( Output.mPosition , matProjection);
   
   Output.mTexCoord = Input.mTexCoord;
   
   return( Output );
   
}
texture BaseTexture_Tex
<
   string ResourceName = ".\\Ez\\ASSETS\\Characters\\Ezreal\\Skins\\Base\\Particles\\Ezreal_Base_Q_mis_trail.dds";
>;
sampler BaseTexture = sampler_state
{
   Texture = (BaseTexture_Tex);
};
struct PS_INPUT
{
      float2 mTexCoord : TEXCOORD0;
};
float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{   
   float4 albedo = tex2D(BaseTexture,Input.mTexCoord);
   return albedo.rgba;

   
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}
