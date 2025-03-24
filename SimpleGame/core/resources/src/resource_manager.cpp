#include <string>
#include <fstream>
#include <sstream>
#include "external/stb_image/stb_image.h"
#include "resources/inc/resource_manager.h"

static bool LoadShaderFromFile(std::string& _str, const char* _path)
{
	std::ifstream file(_path);
	if (!file.is_open()) return false;

	std::stringstream ss;
	ss << file.rdbuf();
	_str = ss.str();

	file.close();
	return true;
}

bool TextureManager::LoadFromFile(tx::id _id, const char* _path)
{
	if (!_path) return false;

	stbi_set_flip_vertically_on_load(true);
	int width, height, channels;
	unsigned char* data = stbi_load(_path, &width, &height, &channels, 0);
	if (!data) return false;

	Texture* texture = new Texture();
	if (!texture) return false;
	if (!texture->Create(data, width, height, channels))
	{
		stbi_image_free(data);
		delete texture;
		return false;
	}

	Push(_id, texture);
	stbi_image_free(data);
	return true;
}

bool ShaderManager::LoadFromFile(sh::id _id, const char* _vert, const char* _frag, const char* _geom)
{
	std::string v_str;
	std::string f_str;
	std::string g_str;

	if (!LoadShaderFromFile(v_str, _vert)) return false;
	if (!LoadShaderFromFile(f_str, _frag)) return false;
	if (_geom)
		if (!LoadShaderFromFile(g_str, _geom)) return false;

	Shader* shader = new Shader();
	if (!shader) return false;
	if (!shader->Create(v_str.c_str(), f_str.c_str(), _geom ? g_str.c_str() : nullptr))
	{
		delete shader;
		return false;
	}

	Push(_id, shader);
	return true;
}

bool MeshManager::Create(msh::id _id)
{
	Mesh* mesh = new Mesh();
	if (!mesh) return false;
	if (!mesh->Create())
	{
		delete mesh;
		return false;
	}

	Push(_id, mesh);
	return true;
}
