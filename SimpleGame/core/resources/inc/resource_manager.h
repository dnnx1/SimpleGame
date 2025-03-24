#pragma once
#include <assert.h>
#include <map>
#include <array>
#include "resources/inc/texture.h"
#include "resources/inc/shader.h"
#include "resources/inc/mesh.h"
#include "resources/pub/tx_textures.h"
#include "resources/pub/sh_shaders.h"
#include "resources/pub/msh_meshes.h"

template <typename ID, typename T, int Size>
class ResourceManager
{
public:
								ResourceManager();
	virtual						~ResourceManager();

	T&							Get(ID _id);
protected:
	void						Push(ID _id, T* _res);
private:
	std::array<T*, Size>		m_list;
};

class TextureManager : public ResourceManager<tx::id, Texture, tx::__count>
{
public:
	bool						LoadFromFile(tx::id _id, const char* _path);
private:
};

class ShaderManager : public ResourceManager<sh::id, Shader, sh::__count>
{
public:
	bool						LoadFromFile(sh::id _id, const char* _vert, const char* _frag, const char* _geom = nullptr);
private:
};

class MeshManager : public ResourceManager<msh::id, Mesh, msh::__count>
{
public:
	bool						Create(msh::id _id);
private:
};

struct Resources
{
	TextureManager				textures;
	ShaderManager				shaders;
	MeshManager					meshes;
};

#include "resources/inc/resource_manager.inl"