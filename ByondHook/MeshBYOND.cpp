#include <d3d9.h>
#include <vector>
#include <d3dx9.h>
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "MeshBYOND.h"

Mesh::Mesh() { vCount = 0; }

Mesh::Mesh(LPDIRECT3DDEVICE9 _pDevice)
{
	position = D3DXVECTOR3(0, 0, 0);
	vBuffer = NULL;
	pDevice = _pDevice;
	vCount = 0;
}

void Mesh::Draw()
{
	D3DXMATRIX matRotateTranslate;
	D3DXMatrixTranslation(&matRotateTranslate, position.x, position.y, position.z);

	finalMatrix = (matRotateY * matRotateX * matRotateZ) * matRotateScale * matRotateTranslate;
	pDevice->SetTransform(D3DTS_WORLD, &(finalMatrix));    // set the world transform

	pDevice->SetStreamSource(0, vBuffer, 0, sizeof(CUSTOMVERTEX));

	UINT offset = 0;
	for (size_t m = 0; m < materials.size(); m++) {

		int current_material_id = shapes[m].mesh.material_ids[0];

		if (m < tex.size())
		{
			if ((current_material_id < 0) || (current_material_id >= static_cast<int>(materials.size()))) {
				// Invaid material ID. Use default material.
				current_material_id = materials.size() - 1; // Default material is added to the last item in `materials`.
			}

			pDevice->SetTexture(0, tex[current_material_id]);
			//std::cout << materials[tex.size() - m - 1].diffuse_texname << std::endl;
		}

		//std::cout << shapes[shapes.size() - 1 - m].name << std::endl;
		//std::cout << materials[m].name << std::endl << std::endl;


		/*
		if (m % 2 == 0)
			pDevice->SetTexture(0, tex[0]);
		else
			pDevice->SetTexture(0, t2);
		*/

		pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, offset, shapes[m].mesh.indices.size() / 3);

		offset += shapes[m].mesh.indices.size();
	}
}

void Mesh::SetTexture(std::string texName)
{
	//OBJStruct t = GetFileInResources(texName);
	//D3DXCreateTextureFromFileInMemory(pDevice, t.fileBuf, t.size, &tex[0]);
}

void Mesh::SetRotation(float x, float y, float z)
{
	D3DXMatrixRotationX(&matRotateX, x);
	D3DXMatrixRotationY(&matRotateY, y);
	D3DXMatrixRotationZ(&matRotateZ, z);
}

void Mesh::SetScale(float x, float y, float z)
{
	D3DXMatrixScaling(&matRotateScale, x, y, z);
}

void Mesh::SetPosition(float x, float y, float z)
{
	position = D3DXVECTOR3(x, y, z);
}

void Mesh::LoadObj(OBJStruct* objStruct, OBJStruct* matStruct)
{
	std::string err;

	OneShotReadBuf osrb(objStruct->fileBuf, objStruct->size);
	std::istream istr(&osrb);

	istr.clear();

	OneShotReadBuf matosrb(matStruct->fileBuf, matStruct->size);
	std::istream matistr(&matosrb);

	matistr.clear();

	tinyobj::MaterialStreamReader materialStreamReader(matistr);
	tinyobj::MaterialStreamReader* materialReader = (matStruct != nullptr)
		? &materialStreamReader
		: NULL;


	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, &istr, materialReader, true);

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	if (!ret) {
		std::cout << "Couldn't load obj" << std::endl;
		return;
	}

	std::vector<float> buffer;
	for (size_t s = 0; s < shapes.size(); s++)
	{
		tinyobj::mesh_t& mesh = shapes[s].mesh;
		//std::cout << shapes[s].mesh.num_face_vertices.size() << std::endl;

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
				vCount++;
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
		//vertexCount += shapes[s].mesh.num_face_vertices.size();
	}
	CreateMeshGeometry(pDevice, vBuffer, vCount, &buffer.at(0));

	for (size_t m = 0; m < materials.size(); m++) {
		tinyobj::material_t* mp = &materials[m];

		if (mp->diffuse_texname.length() > 0) {
			// Only load the texture if it is not already loaded
			if (true) {
				UINT texture_id = m;
				int w, h;
				int comp;

				std::string texture_filename = mp->diffuse_texname;

				std::string base_filename = texture_filename.substr(texture_filename.find_last_of("/\\") + 1);

				//std::cout << texture_filename << std::endl;

				LPDIRECT3DTEXTURE9 tx;

				OBJStruct t = GetFileInResources(base_filename);
				if (t.size != 0)
				{
					D3DXCreateTextureFromFileInMemory(pDevice, t.fileBuf, t.size, &tx);
					tex.push_back(tx);


					textures.insert(std::make_pair(mp->diffuse_texname, texture_id));
				}
			}
		}
		else
		{
			std::cout << "No textures in file." << std::endl;
		}
	}
}

void Mesh::LoadObj(const char* name)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, name);

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	if (!ret) {
		std::cout << "Couldn't load obj" << std::endl;
		return;
	}

	std::vector<float> buffer;
	for (size_t s = 0; s < shapes.size(); s++)
	{
		tinyobj::mesh_t& mesh = shapes[s].mesh;

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
				vCount++;
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
		//vertexCount += shapes[s].mesh.num_face_vertices.size();
	}
	CreateMeshGeometry(pDevice, vBuffer, vCount, &buffer.at(0));
}