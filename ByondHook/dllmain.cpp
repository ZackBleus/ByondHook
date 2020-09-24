// dllmain.cpp : Defines the entry point for the DLL application.
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
#include "core/core.h"

DWORD gameBaseAddress;
HANDLE processHandle = NULL;


IDirect3D9* ppD3D9;

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
LPDIRECT3DINDEXBUFFER9 i_buffer;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC oWndProc;

static HWND window = NULL;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

trvh TestHook(unsigned int argcount, Value* args, Value src);


LRESULT __stdcall WndProc(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	return true; // Yeah.

	return CallWindowProcA(oWndProc, hWnd, msg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}



int startThread()
{
	Core::initialize();
	Core::get_proc("/proc/yo").hook(TestHook); // Gets the proc as defined in Hack.dm

	init();
	return 1;
}

long __stdcall hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	std::cout << "Reset" << std::endl;

	//ZeroMemory(pPresentationParameters, sizeof(*pPresentationParameters));

	//ZeroMemory(pPresentationParameters, sizeof(D3DPRESENT_PARAMETERS));
	pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	pPresentationParameters->Windowed = TRUE;
	pPresentationParameters->SwapEffect = D3DSWAPEFFECT_DISCARD;
	pPresentationParameters->EnableAutoDepthStencil = TRUE;
	pPresentationParameters->AutoDepthStencilFormat = D3DFMT_D24S8;


	InitVolatileResources(pDevice);

	ImGui_ImplDX9_InvalidateDeviceObjects();
	//ReleaseVolatileResources(pDevice);
	long result = oReset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}

HRESULT __stdcall hkClear(LPDIRECT3DDEVICE9 pDevice, DWORD count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	//pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 1);
	//pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 1);
	return oClear(pDevice, count, pRects, Flags, Color, Z, Stencil);
}

bool initialized = false;
bool texturesLoaded = false;
RECT windowSize;

float playerX = 0.0f;
float playerY = 0.0f;
float playerZ = 0.0f;
float headingX = 0.0f;
float headingY = 0.0f;

static ImGuiContext* context;

Mesh bobombMesh;
long __stdcall hkPresent(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	if (!initialized)
	{
		//IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

		//if (!pD3D)
		//	return false;

		//dummyDeviceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		
		

		D3DDEVICE_CREATION_PARAMETERS params;
		pDevice->GetCreationParameters(&params);
		params.BehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;

		context = ImGui::CreateContext();	// Setting up some ImGui stuff.

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = NULL;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.Fonts->AddFontDefault();

		ImGui_ImplWin32_Init(params.hFocusWindow);
		ImGui_ImplDX9_Init(pDevice);

		std::cout << "Initializing Graphics" << std::endl;

		bobombMesh = Mesh(pDevice);

		OBJStruct bbb = GetFileInResources("Bob-omb Battlefield.obj");		// Load mesh from obj stored in .rsc file.
		OBJStruct bbbmat = GetFileInResources("Bob-omb Battlefield.mtl");	// Load material from the .rsc file.

		bobombMesh.LoadObj(&bbb, &bbbmat);

		InitVolatileResources(pDevice);										// Make sure stuff stays the same when the window loses focus.

		GetClientRect(params.hFocusWindow, &windowSize);

		IDirect3DSwapChain9* pSwap;
		D3DPRESENT_PARAMETERS pParams;

		pDevice->GetSwapChain(0, &pSwap);

		pSwap->GetPresentParameters(&pParams);

		oReset(pDevice, &pParams);

		//pDevice->CreateRenderTarget(windowSize.right, windowSize.bottom, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, 0, FALSE, ppSurface, NULL);
		initialized = true;
	}

	//pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 1);
	//pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 1);


	DWORD dwReturnAddress = 0;

	static DWORD dwAllowedReturn = 0;

	__asm	// This is so that we hook into the correct render instance.
	{
		push eax
		mov eax, [ebp + 4]
		mov dwReturnAddress, eax
		pop eax
	}

	pDevice->BeginScene();
	//->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 1);
	pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 1);

	ImGuiContext* tmpContext = ImGui::GetCurrentContext();
	ImGui::SetCurrentContext(context);

	// select which vertex format we are using


	D3DXMATRIX matView;										// the view transform matrix
	D3DXVECTOR3 normal = D3DXVECTOR3(headingX, 0.0f, headingY);
	D3DXVECTOR3 lookAt = D3DXVECTOR3(playerX, playerZ, playerY) + normal;

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(playerX, playerZ, playerY),			// the camera position
		&lookAt,											// the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));					// the up direction

	pDevice->SetTransform(D3DTS_VIEW, &matView);			// set the view transform to matView

	D3DXMATRIX matProjection;								// the projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(40),									// the horizontal field of view
		(FLOAT)windowSize.right / (FLOAT)windowSize.bottom, // aspect ratio
		0.01f,												// the near view-plane
		1000.0f);											// the far view-plane

	pDevice->SetTransform(D3DTS_PROJECTION, &matProjection);// set the projection

	static float index = 0.0f; index += 0.03f;				// an ever-increasing float value

	bobombMesh.SetScale(1.0f, 1.0f, 1.0f);
	bobombMesh.SetRotation(0.0f, 0.0f, 0.0f);
	bobombMesh.SetPosition(0, -3, 0);

	bobombMesh.Draw();

	if (dwAllowedReturn == 0 || dwAllowedReturn == dwReturnAddress)
	{
		// Yet more ImGui stuff.
		InputHandler();

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::SetWindowSize(ImVec2(300, 600));
		showExampleWindow("D3D9");

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		dwAllowedReturn = dwReturnAddress;

		ImGui::SetCurrentContext(tmpContext);
		

	}

	pDevice->EndScene(); // Call hooked EndScene function.

	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	long result = oPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

	//result = pDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

	//pRenderTarget->Release();
	return result;
	//return oPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

long __stdcall hkBeginScene(LPDIRECT3DDEVICE9 pDevice)
{
	//pDevice->SetFVF(CUSTOMFVF);
	/*
	pDevice->SetVertexShader(0);
	pDevice->SetPixelShader(0);
	pDevice->SetFVF(CUSTOMFVF); //pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
	*/
	
	InitVolatileResources(pDevice);
	return oBeginScene(pDevice);
}

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	//pDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(0, 128, 128, 128), 1.0f, 0);
	InitVolatileResources(pDevice);

	return oEndScene(pDevice);
}



void InputHandler()
{
	for (int i = 0; i < 5; i++) ImGui::GetIO().MouseDown[i] = false;

	int button = -1;
	if (GetAsyncKeyState(VK_LBUTTON)) button = 0;

	if (button != -1) ImGui::GetIO().MouseDown[button] = true;
}


// *NOTE* This only works if the client is running the server / in single-player.
trvh TestHook(unsigned int argcount, Value* args, Value src)
{
	// Receiving from values of vars from the BYOND process.

	trvh* valueHolder;

	valueHolder = &GetVariable(args[0].type, args[0].value, Core::GetStringId("realX"));
	playerX = valueHolder->valuef;

	valueHolder = &GetVariable(args[0].type, args[0].value, Core::GetStringId("realY"));
	playerY = valueHolder->valuef;

	valueHolder = &GetVariable(args[0].type, args[0].value, Core::GetStringId("realZ"));
	playerZ = valueHolder->valuef;

	valueHolder = &GetVariable(args[0].type, args[0].value, Core::GetStringId("headingX"));
	headingX = valueHolder->valuef;

	valueHolder = &GetVariable(args[0].type, args[0].value, Core::GetStringId("headingY"));
	headingY = valueHolder->valuef;

	return Value::Null();
}

void init()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout); // Sets cout to be used with our newly created console

	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());

	if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL) { // error handling
		std::cout << "Failed to open process" << std::endl;
		return;
	}

	char byondCoreName[] = "byondcore.dll";
	gameBaseAddress = GetModuleBaseAddress(_T(byondCoreName), GetCurrentProcessId());

	char processName[] = "dreamseeker.exe";
	DWORD processBaseAddress = GetModuleBaseAddress(_T(processName), GetCurrentProcessId());

	//dungClient = new DungClient((DungClient*)(processBaseAddress + 0x6C378));
	//reinterpret_cast<void*&>(dungClient->getCurrentLoginKey) = (GetCurrentLoginKey*)(gameBaseAddress + 0x69230);

	//dungClient.getCurrentLoginKey = (GetCurrentLoginKey)(gameBaseAddress + 0x69230);

	//std::cout << std::hex << gameBaseAddress + 0x69230 << std::endl;

	//std::cout << dungClient.GetCurrentLoginKey() << std::endl;



	HANDLE base = GetModuleHandle(_T(byondCoreName));

	if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success) // D3D9 binding stuff
	{
		kiero::bind(16, (void**)&oReset, hkReset);
		kiero::bind(17, (void**)&oPresent, hkPresent);

		kiero::bind(41, (void**)&oBeginScene, hkBeginScene);
		kiero::bind(42, (void**)&oEndScene, hkEndScene);
		kiero::bind(43, (void**)&oClear, hkClear);

		std::cout << *hkPresent << std::endl;
	}
	else
	{
		std::cout << "Kiero failed to initialize." << std::endl;
	}

	std::cout << std::hex << gameBaseAddress << std::endl;;

	// Initialize MinHook.
	if (MH_Initialize() != MH_OK) // Should be initialized already by Kiero, but if that somehow fails we'll know.
	{
		std::cout << "MH initialization failed." << std::endl;
	}

	// Ideally this would be done with an AoB scan rather than offsets but y'know.
	if (MH_CreateHook((LPVOID)(ReadIcon)(gameBaseAddress + 0x70EF0), hkReadIcon, reinterpret_cast<LPVOID*>(&oReadIcon)) != MH_OK) 
	{
		std::cout << "Read Icon hook failed." << std::endl;
	}

	if (MH_EnableHook((LPVOID)(ReadIcon)(gameBaseAddress + 0x70EF0)) != MH_OK)
	{
		std::cout << "Read Icon enable failed." << std::endl;
	}

	if (MH_CreateHook((LPVOID)(ReadIconPixels)(gameBaseAddress + 0x71130), hkReadIconPixels, reinterpret_cast<LPVOID*>(&oReadIconPixels)) != MH_OK)
	{
		std::cout << "Read Icon Pixels hook failed." << std::endl;
	}

	if (MH_EnableHook((LPVOID)(ReadIconPixels)(gameBaseAddress + 0x71130)) != MH_OK)
	{
		std::cout << "Read Icon Pixels enable failed." << std::endl;
	}

	/*
	if (MH_CreateHook((LPVOID)(CommandEvent)(gameBaseAddress + 0x68310), hkCommandEvent, reinterpret_cast<LPVOID*>(&oCommandEvent)) != MH_OK)
	{
		std::cout << "Command Event hook failed." << std::endl;
		return;
	}

	std::cout << "Command Event hooked!." << std::endl;
	*/

	//MH_STATUS mhError = MH_EnableHook((LPVOID)(CommandEvent)(gameBaseAddress + 0x68310));

	/*
	if (MH_CreateHook((LPVOID)(CommandEvent)(gameBaseAddress + 0x69140), hkInitClient, reinterpret_cast<LPVOID*>(&oInitClient)) != MH_OK)
	{
		std::cout << "Client hook failed." << std::endl;
		return;
	}

	//MH_STATUS mhError = MH_EnableHook((LPVOID)(CommandEvent)(gameBaseAddress + 0x68310));
	MH_STATUS mhError = MH_EnableHook((LPVOID)(CommandEvent)(gameBaseAddress + 0x69140));


	if (mhError != MH_OK)
	{
		std::cout << mhError << std::endl;
		return;
	}
	*/

	//(GetCurrentLoginKey)oGetCurrentLoginKey(dungClient);
	

	/*
	DWORD clientXOffset = 0x32B6A4;
	DWORD clientYOffset = 0x32B6A8;
	DWORD mouseXOffset = 0x32B6E0;
	DWORD mouseYOffset = 0x32B6E2;
	DWORD tileMapOffset = 0x32C6B4;

	bool NeedsToDraw = true;
	int YMaxScan = 21;
	int XMaxScan = 21;

	int MaxXIndex = 21;
	int MinXIndex = 0;
	int MaxYIndex = 21;
	int MinYIndex = 0;

	int MaxScreenX = 100;
	int MaxScreenY = 100;

	unsigned char DefaultViewSize = 5;

	int PosX = 0;
	int PosY = 0;
	*/

	//std::vector<int> tiles;


	//pAddVPrintf = (_AddVPrintf)DetourFunction((PBYTE)(_AddVPrintf)(base + 0x1F20D0), (PBYTE)AddVPrintf);
}

// ImGui code here.
void showExampleWindow(const char* comment)
{
	char buffer[128];
	::memset(buffer, 0, 128);
	::sprintf(buffer, "BYOND ImGui (%s)", comment);

	ImGui::Begin(buffer);

	ImGui::Text("ImGui implementation in BYOND.");

	ImGui::End();
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	DisableThreadLibraryCalls(hModule);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		do
			window = GetProcessWindow();
		while (window == NULL);

		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startThread, NULL, 0, NULL);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// This doesn't do anything, but it doesn't actually need to. If you're calling this function from call()() in DM, then it'll attach the .dll to the process anyway.
extern "C" __declspec(dllexport) char* Initialize(int n, char* v[])
{
	return *v;
}