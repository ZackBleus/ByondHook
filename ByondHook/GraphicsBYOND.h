#pragma once
#include <d3d9.h>
#include <d3dx9.h>


void InitVolatileResources(LPDIRECT3DDEVICE9 pDevice);
void ReleaseVolatileResources(LPDIRECT3DDEVICE9 pDevice);
bool CreateMeshGeometry(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& pVB, int count, float* data);
void init_light(LPDIRECT3DDEVICE9 pDevice);