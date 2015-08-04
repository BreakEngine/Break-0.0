#include "AssetManager.h"
#include <Shader.h>
#include <Vertex2DPos.h>
#include <Engine.h>
#include <Vertex2DPosColorTex.h>
using namespace std;
using namespace Break::Assets;
using namespace Break::GXWrapper;

map<string,IAssetPtr> AssetManager::_assetTable = map<string,IAssetPtr>();

void AssetManager::addDefaultAssets()
{
	/************************ Default Shaders ************************/

	std::string glVertexShape2D = "#version 330\n"
			"layout(location = 0) in vec2 position;\n"
			"layout(location = 1) in vec4 color;\n"
			"layout(location = 2) in vec2 texCoord;\n"
			
			"uniform MatrixBuffer{\n"
				"mat4 model;\n"
				"mat4 view;\n"
				"mat4 projection;\n"
				"vec4 hasTexture;\n"
			"};\n"
			"out vec4 ocolor;\n"
			"out vec2 otex;\n"
			"out vec4 ohasTex;\n"
			"void main(){\n"
			"gl_Position = projection*view*model*vec4(position.xy,0,1);\n"
			"ocolor = color;\n"
			"otex = texCoord;\n"
			"ohasTex = hasTexture;\n"
			"}\n"
			;
	std::string glPixelShape2D = "#version 330\n"
			"in vec4 ocolor;\n"
			"in vec2 otex;\n"
			"in vec4 ohasTex;\n"
			"uniform sampler2D spTex;\n"
			"void main(){\n"
			"if(ohasTex.x==1){"
				"gl_FragColor = ocolor*texture(spTex,otex);\n"
			"}else\n"
				"gl_FragColor = ocolor;\n"
			"if(gl_FragColor.w==0)\n"
				"discard;"
			"}\n"
			;

	std::string dxVertexShape2D = "#pragma pack_matrix( row_major )\n"
		"struct VertexInputType\n"
		"{\n"
			"float2 position : POSITION;\n"
			"float4 color : COLOR0;\n"
			"float2 texCoord : TEXCOORD0;\n"
		"};\n"
		"cbuffer MatrixBuffer\n"
		"{\n"
			"matrix model;\n"
			"matrix view;\n"
			"matrix projection;\n"
			"float4 hasTexture;\n"
		"};\n"
		"struct PixelInputType\n"
		"{\n"
			"float4 position : SV_POSITION;\n"
			"float4 color : COLOR0;\n"
			"float2 texCoord : TEXCOORD0;\n"
			"float4 ohasTex : TEXCOORD1;\n"
		"};\n"

		"PixelInputType main(VertexInputType input)\n"
		"{\n"
			"PixelInputType output;\n"

			"output.position = float4(input.position.xy,0,1);\n"
			"output.position = mul(output.position,model);\n"
			"output.position = mul(output.position,view);\n"
			"output.position = mul(output.position,projection);\n"

			"output.color = input.color;\n"
			"output.texCoord = input.texCoord;\n"
			"output.ohasTex = hasTexture;\n"

			"return output;\n"
		"}\n";

	std::string dxPixelShape2D = "#pragma pack_matrix( row_major )\n"
		"struct PixelInputType\n"
		"{\n"
			"float4 position : SV_POSITION;\n"
			"float4 color : COLOR0;\n"
			"float2 texCoord : TEXCOORD0;\n"
			"float4 ohasTex : TEXCOORD1;\n"
		"};\n"
		"Texture2D spTex;\n"
		"SamplerState SampleType;\n"
		"float4 main(PixelInputType input) : SV_TARGET\n"
		"{\n"
			"float4 endColor;\n"
			"if(input.ohasTex.x==1)\n"
				"endColor = input.color *spTex.Sample(SampleType,input.texCoord);\n"
			"else\n"
				"endColor = input.color;\n"
				"if (endColor.w==0)\n"
					"discard;\n"
				"return endColor;\n"
		"}\n";

	ShaderPtr shape2DShader;
	if(Infrastructure::Engine::Instance->getAPI() == Infrastructure::API::OPENGL)
		shape2DShader = make_shared<GXWrapper::Shader>(glVertexShape2D,glPixelShape2D,Vertex2DPosColorTex::getDescription());
	else if(Infrastructure::Engine::Instance->getAPI() == Infrastructure::API::DIRECTX)
		shape2DShader = make_shared<GXWrapper::Shader>(dxVertexShape2D,dxPixelShape2D,Vertex2DPosColorTex::getDescription());

	shape2DShader->registerUniformBlock("MatrixBuffer",(64*3)+16,0,Shader::VERTEX);
	shape2DShader->registerUniform("model","MatrixBuffer",0,64);
	shape2DShader->registerUniform("view","MatrixBuffer",64,64);
	shape2DShader->registerUniform("projection","MatrixBuffer",2*64,64);
	shape2DShader->registerUniform("hasTexture","MatrixBuffer",3*64,16);
	shape2DShader->registerSampler("spTex",0,make_shared<SamplerState>(),Shader::PIXEL);

	shape2DShader->_name = "_shape2DShader";
	_assetTable["_shape2DShader"] = shape2DShader;
}

void AssetManager::cleanUp()
{
	_assetTable.clear();
}

IAsset* AssetManager::find(std::string name){
	auto res = _assetTable.find(name);
	if(res == _assetTable.end())
		return nullptr;
	else
		return res->second.get();
}

void AssetManager::add(IAssetPtr res){
	if(res){
		_assetTable[res->getName()] = res;
	}
}

void AssetManager::add(std::string name, IAssetPtr res)
{
	if(res){
		res->_name = name;
		_assetTable[res->getName()] = res;
	}
}