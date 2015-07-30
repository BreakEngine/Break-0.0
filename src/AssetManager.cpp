#include "AssetManager.h"
#include <Shader.h>
#include <Vertex2DPos.h>
#include <Engine.h>
using namespace std;
using namespace Break::Assets;
using namespace Break::GXWrapper;

map<string,IAssetPtr> AssetManager::_assetTable = map<string,IAssetPtr>();

void AssetManager::addDefaultAssets()
{
	/************************ Default Shaders ************************/

	std::string glVertexShape2D = "#version 330\n"
			"layout(location = 0) in vec2 position;\n"
			
			"uniform PerObj{\n"
				"vec4 ucolor;\n"
			"};\n"
			"out vec4 ocolor;\n"
			"void main(){\n"
			"gl_Position = vec4(position.xy,0,1);\n"
			"ocolor = ucolor;\n"
			"}\n"
			;
	std::string glPixelShape2D = "#version 330\n"
			"in vec4 ocolor;\n"
			"void main(){\n"
			"gl_FragColor = ocolor;\n"
			"}\n"
			;

	std::string dxVertexShape2D = "struct VertexInputType\n"
		"{\n"
			"float2 position : POSITION;\n"
		"};\n"
		"cbuffer PerObj\n"
		"{\n"
			"float4 ucolor;\n"
		"};\n"
		"struct PixelInputType\n"
		"{\n"
			"float4 position : SV_POSITION;\n"
			"float4 color : COLOR;\n"
		"};\n"

		"PixelInputType main(VertexInputType input)\n"
		"{\n"
			"PixelInputType output;\n"

			"output.position = float4(input.position.xy,0,1);\n"

			"output.color = ucolor;\n"

			"return output;\n"
		"}\n";

	std::string dxPixelShape2D = "struct PixelInputType\n"
		"{\n"
			"float4 position : SV_POSITION;\n"
			"float4 color : COLOR;\n"
		"};\n"
		"float4 main(PixelInputType input) : SV_TARGET\n"
		"{\n"
			"return input.color;\n"
		"}\n";

	ShaderPtr shape2DShader;
	if(Infrastructure::Engine::Instance->getAPI() == Infrastructure::API::OPENGL)
		shape2DShader = make_shared<GXWrapper::Shader>(glVertexShape2D,glPixelShape2D,Vertex2DPos::getDescription());
	else if(Infrastructure::Engine::Instance->getAPI() == Infrastructure::API::DIRECTX)
		shape2DShader = make_shared<GXWrapper::Shader>(dxVertexShape2D,dxPixelShape2D,Vertex2DPos::getDescription());

	shape2DShader->registerUniformBlock("PerObj",16,0,Shader::VERTEX);
	shape2DShader->registerUniform("ucolor","PerObj",0,16);

	shape2DShader->_name = "_shape2DShader";
	_assetTable["_shape2DShader"] = shape2DShader;
}

void AssetManager::cleanUp()
{
	_assetTable.clear();
}

IAssetPtr AssetManager::find(std::string name){
	auto res = _assetTable.find(name);
	if(res == _assetTable.end())
		return nullptr;
	else
		return res->second;
}

void AssetManager::add(IAsset* res){
	if(res){
		_assetTable[res->getName()] = IAssetPtr(res);
	}
}

void AssetManager::add(std::string name, IAsset* res)
{
	if(res){
		res->_name = name;
		_assetTable[res->getName()] = IAssetPtr(res);
	}
}