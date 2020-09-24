#include "GraphicsBYOND.h"
#include "main.h"

LPDIRECT3DTEXTURE9 tex;
void InitVolatileResources(LPDIRECT3DDEVICE9 pDevice)
{
	//init_light(pDevice);
	
	pDevice->SetFVF(CUSTOMFVF);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));    // ambient light
	pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);




	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);   //Ignored
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//pDevice->SetTexture(0, tex);

}

void ReleaseVolatileResources(LPDIRECT3DDEVICE9 pDevice)
{
	// I don't actually know what to put here.
}

bool CreateMeshGeometry(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DVERTEXBUFFER9& pVB, int count, float* data)
{
	// Create the vertex buffer.
	pDevice->CreateVertexBuffer(count * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &pVB, NULL);

	CUSTOMVERTEX* pVertices;
	if (FAILED(pVB->Lock(0, 0, (void**)&pVertices, 0)))
	{
		std::cout << "Couldn't lock verts" << std::endl;
		return false;
	}



	float* ptr = data;
	for (DWORD i = 0; i < count; i++)
	{
		if (i > count)
		{
			continue;
		}

		float z = *ptr++;
		float y = *ptr++;
		float x = *ptr++;

		pVertices[i].X = x;
		pVertices[i].Y = y;
		pVertices[i].Z = z;

		pVertices[i].NORMAL = D3DXVECTOR3(*ptr++, *ptr++, *ptr++);
		pVertices[i].tu = *ptr++;
		pVertices[i].tv = *ptr++;
	}
	pVB->Unlock();
	return true;
}

D3DMATERIAL9 material;    // create the material struct
D3DLIGHT9 light;    // create the light struct
// this is the function that sets up the lights and materials
void init_light(LPDIRECT3DDEVICE9 pDevice)
{


	ZeroMemory(&light, sizeof(light));    // clear out the light struct for use
	light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
	light.Direction = D3DXVECTOR3(0.5f, -0.5f, 0.0f);

	pDevice->SetLight(0, &light);    // send the light struct properties to light #0
	pDevice->LightEnable(0, TRUE);    // turn on light #0

	ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

	pDevice->SetMaterial(&material);    // set the globably-used material to &material
}