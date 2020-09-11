#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "kiero.h"
#include "MinHook.h"
#include <tchar.h>
#include <TlHelp32.h>
#include "byonddefs.h"
#include "HooksBYOND.h"
#include "GraphicsBYOND.h"
#include "MeshBYOND.h"
#include <fstream>

#pragma comment(lib, "user32.lib")

struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DXVECTOR3 NORMAL; FLOAT tu, tv; };

void init();
int startThread();
void showExampleWindow(const char* comment);
void InputHandler();
bool CreateMeshGeometry(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& pVB, int count, float* data);
void init_graphics(LPDIRECT3DDEVICE9);    // 3D declarations

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)



/*
// this is the function that puts the 3D models into video RAM
void init_graphics(LPDIRECT3DDEVICE9 pDevice)
{
	float length = 3.0f;
	float width = 3.0f;
	float height = 3.0f;

	/*
	D3DXVECTOR3 c[8];
	c[0] = D3DXVECTOR3(-length * .5f, -width * .5f, height * .5f);
	c[1] = D3DXVECTOR3(length * .5f, -width * .5f, height * .5f);
	c[2] = D3DXVECTOR3(length * .5f, -width * .5f, -height * .5f);
	c[3] = D3DXVECTOR3(-length * .5f, -width * .5f, -height * .5f);

	c[4] = D3DXVECTOR3(-length * .5f, width * .5f, height * .5f);
	c[5] = D3DXVECTOR3(length * .5f, width * .5f, height * .5f);
	c[6] = D3DXVECTOR3(length * .5f, width * .5f, -height * .5f);
	c[7] = D3DXVECTOR3(-length * .5f, width * .5f, -height * .5f);

	//6) Define each vertex's UV co-ordinates
	D3DXVECTOR2 uv00 = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 uv10 = D3DXVECTOR2(1.0f, 0.0f);
	D3DXVECTOR2 uv01 = D3DXVECTOR2(0.0f, 1.0f);
	D3DXVECTOR2 uv11 = D3DXVECTOR2(1.0f, 1.0f);

	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 down = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 back = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 left = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DVECTOR normals[] =
	{
		down, down, down, down,             // Bottom
		left, left, left, left,             // Left
		forward, forward, forward, forward,	// Front
		back, back, back, back,             // Back
		right, right, right, right,         // Right
		up, up, up, up	                    // Top
	};

	// create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX vertices[24] =
	{
		{ c[0].x, c[0].y, c[0].z, down, uv11.x, uv11.y, },
		{ c[1].x, c[1].y, c[1].z, down, uv01.x, uv01.y, },
		{ c[2].x, c[2].y, c[2].z, down, uv00.x, uv00.y,},
		{ c[3].x, c[3].y, c[3].z, down, uv10.x, uv10.y,},

		{ c[7].x, c[7].y, c[7].z, left, uv11.x, uv11.y,},
		{ c[4].x, c[4].y, c[4].z, left, uv01.x, uv01.y,},
		{ c[0].x, c[0].y, c[0].z, left, uv00.x, uv00.y,},
		{ c[3].x, c[3].y, c[3].z, left, uv10.x, uv10.y,},

		{ c[4].x, c[4].y, c[4].z, forward, uv11.x, uv11.y,},
		{ c[5].x, c[5].y, c[5].z, forward, uv01.x, uv01.y,},
		{ c[1].x, c[1].y, c[1].z, forward, uv00.x, uv00.y,},
		{ c[0].x, c[0].y, c[0].z, forward, uv10.x, uv10.y,},

		{ c[6].x, c[6].y, c[6].z, back, uv11.x, uv11.y,},
		{ c[7].x, c[7].y, c[7].z, back, uv01.x, uv01.y,},
		{ c[3].x, c[3].y, c[3].z, back, uv00.x, uv00.y,},
		{ c[2].x, c[2].y, c[2].z, back, uv10.x, uv10.y,},

		{ c[5].x, c[5].y, c[5].z, right, uv11.x, uv11.y, },
		{ c[6].x, c[6].y, c[6].z, right, uv01.x, uv01.y, },
		{ c[2].x, c[2].y, c[2].z, right, uv00.x, uv00.y, },
		{ c[1].x, c[1].y, c[1].z, right, uv10.x, uv10.y, },

		{ c[7].x, c[7].y, c[7].z, up, uv11.x, uv11.y, },
		{ c[6].x, c[6].y, c[6].z, up, uv01.x, uv01.y, },
		{ c[5].x, c[5].y, c[5].z, up, uv00.x, uv00.y, },
		{ c[4].x, c[4].y, c[4].z, up, uv10.x, uv10.y, },
	};

	int vert_count = sizeof(vertices) / sizeof(CUSTOMVERTEX);
	int byte_count = vert_count * sizeof(CUSTOMVERTEX);

	// create a vertex buffer interface called v_buffer
	pDevice->CreateVertexBuffer(byte_count,
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);

	VOID* pVoid;    // a void pointer

	// lock v_buffer and load the vertices into it
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	// create the indices using an int array
	short indices[] =
	{
			3, 1, 0,        3, 2, 1,        // Bottom
			7, 5, 4,        7, 6, 5,        // Left
			11, 9, 8,       11, 10, 9,      // Front
			15, 13, 12,     15, 14, 13,     // Back
			19, 17, 16,     19, 18, 17,	    // Right
			23, 21, 20,     23, 22, 21,	    // Top
	};

	// create an index buffer interface called i_buffer
	pDevice->CreateIndexBuffer(36 * sizeof(short),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&i_buffer,
		NULL);

	// lock i_buffer and load the indices into it
	i_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	i_buffer->Unlock();

bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, "Shrek.obj");

if (!err.empty()) {
	std::cerr << err << std::endl;
}

if (!ret) {
	std::cout << "Couldn't load obj" << std::endl;
	return;
}

//bmin.x = bmin.y = bmin.z = std::numeric_limits<float>::max();
//bmax.x = bmax.y = bmax.z = -std::numeric_limits<float>::max();

std::vector<float> buffer;
for (size_t s = 0; s < shapes.size(); s++)
{
	// pos(3float), normal(3float), color(3float)
	tinyobj::mesh_t& mesh = shapes[s].mesh;

	// Check for smoothing group and compute smoothing normals
	//std::map<int, easymath::vector3> smoothVertexNormals;
	//computeSmoothingNormals(attrib, mesh, smoothVertexNormals);

	size_t index_offset = 0;
	for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
		int fv = shapes[s].mesh.num_face_vertices[f];

		// Loop over vertices in the face.
		for (size_t v = 0; v < fv; v++) {
			// access to vertex
			tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
			tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
			tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
			tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
			tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
			tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
			tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
			tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
			tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];

			buffer.push_back((vx * 0.5 + 0.5));
			buffer.push_back((vy * 0.5 + 0.5));
			buffer.push_back((vz * 0.5 + 0.5));
			buffer.push_back(nx);
			buffer.push_back(ny);
			buffer.push_back(nz);
			buffer.push_back(tx);
			buffer.push_back(1.f - ty);
			// Optional: vertex colors
			// tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
			// tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
			// tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
			vertexCount++;
		}
		index_offset += fv;

		// per-face material
		shapes[s].mesh.material_ids[f];
	}
	//vertexCount += shapes[s].mesh.num_face_vertices.size();
}
CreateMeshGeometry(pDevice, v_buffer, vertexCount, &buffer.at(0));
}*/