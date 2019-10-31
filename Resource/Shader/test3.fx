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
string Particle_Effects_Snake_Single_Pass_Particles : ModelData = "..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\QuadArray.3ds";

float4x4 matProjection
<
   string UIName = "matProjection";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
> = float4x4( 2.25, 0.00, 0.00, 0.00, 0.00, 2.41, 0.00, 0.00, 0.00, 0.00, 1.00, 199.20, 0.00, 0.00, 1.00, 200.00 );
float4x4 matView
<
   string UIName = "matView";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
> = float4x4( 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00 );
float fTime;
float4x4 matWorld
<
   string UIName = "matWorld";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
> = float4x4( 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00 );
float fHeight
<
   string UIName = "fHeight";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 1.00 );
float fWidth
<
   string UIName = "fWidth";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float( 1.00 );
struct VS_OUTPUT {
   float4 Pos: POSITION;
   float2 texCoord: TEXCOORD0;
   float color: TEXCOORD1;
};
struct VS_INPUT
{
float4 Pos : POSITION;
};
VS_OUTPUT Particle_Effects_Snake_Single_Pass_Vertex_Shader_main(VS_INPUT Input: POSITION){
      VS_OUTPUT Out;
   matrix matWV = mul(matWorld,matView);
   matrix matWVP = mul(matWV,matProjection);
   Out.Pos = mul(Input.Pos,matWV);
   
   float3 pos = Input.Pos.z * (Input.Pos.x * matWV[0] + Input.Pos.y * matWV[1]);

   float t = fTime;
  // pos.x = (Input.Pos.x);
  // pos.y = (Input.Pos.y);
  // pos.z = (Input.Pos.z);
   float4 Size;
   Size.z =  Input.Pos.z * fHeight;
   Size.x =  Input.Pos.x / (fWidth*2);
   
   
   
   Out.Pos = float4(pos,1);
   Out.Pos = mul(Out.Pos,matWVP);
 //  Out.Pos = mul(Out.Pos,matWorld);
//   Out.Pos = mul(Out.Pos,matView);
//   Out.Pos = mul(Out.Pos,matProjection);
   
   Out.texCoord = Size.xz;
   Out.color = Input.Pos.x; 
   return Out;
}
float particleExp
<
   string UIName = "particleExp";
   string UIWidget = "Numeric";
   bool UIVisible =  true;
   float UIMin = 0.00;
   float UIMax = 0.50;
> = float( 0.07 );
sampler Palette;
struct PS_INPUT
{
float2 texCoord : TEXCOORD0;
float color : TEXCOORD1;
};
float4 Particle_Effects_Snake_Single_Pass_Pixel_Shader_main(PS_INPUT Input) : COLOR {


   return (1 - pow(dot(Input.texCoord, Input.texCoord), particleExp)) ;
}


//--------------------------------------------------------------//
// Technique Section for Particle Effects
//--------------------------------------------------------------//
technique Snake
{
   pass Single_Pass
   {
      ALPHABLENDENABLE = TRUE;
      CULLMODE = NONE;
      DESTBLEND = ONE;
      SRCBLEND = SRCALPHA;
      ZWRITEENABLE = FALSE;

      VertexShader = compile vs_3_0 Particle_Effects_Snake_Single_Pass_Vertex_Shader_main();
      PixelShader = compile ps_3_0 Particle_Effects_Snake_Single_Pass_Pixel_Shader_main();
   }

}

