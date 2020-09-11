#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <assert.h>
#include <iostream>
#include <sstream>

#include "main.h"
#include "LoadingBYOND.h"
#include "tiny_obj_loader.h"

class Mesh {
public:
	LPDIRECT3DVERTEXBUFFER9 vBuffer;
	LPDIRECT3DDEVICE9 pDevice;
	std::vector<LPDIRECT3DTEXTURE9> tex;
	int vCount;
	D3DXVECTOR3 position;
	D3DXMATRIX matRotateX;
	D3DXMATRIX matRotateY;
	D3DXMATRIX matRotateZ;
	D3DXMATRIX matRotateScale;
	D3DXMATRIX finalMatrix;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::map<std::string, UINT> textures;

	Mesh();
	Mesh(LPDIRECT3DDEVICE9 _pDevice);
	void Draw();
	void SetTexture(std::string texName);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void LoadObj(OBJStruct* objStruct, OBJStruct* matStruct = nullptr);
	void LoadObj(const char* name);
};