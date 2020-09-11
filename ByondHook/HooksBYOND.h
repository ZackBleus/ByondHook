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

typedef long(__stdcall* Reset)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
static Reset oReset = NULL;

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
static EndScene oEndScene = NULL;

typedef long(__stdcall* BeginScene)(LPDIRECT3DDEVICE9);
static BeginScene oBeginScene = NULL;

typedef long(__stdcall* Present)(LPDIRECT3DDEVICE9, const RECT*, const RECT*, HWND, const RGNDATA*);
static Present oPresent = NULL;

typedef void(__thiscall* CommandEvent)(void*, unsigned char, unsigned short, unsigned char);
static CommandEvent oCommandEvent;

typedef void(__thiscall* InitClient)(void*, const char*, const char*, int);
static InitClient oInitClient;

typedef const char* (__thiscall* GetCurrentLoginKey)(void*);
static GetCurrentLoginKey oGetCurrentLoginKey;

typedef int(__cdecl* ReadIcon)(struct iobuf*, struct DMIcon*, int, unsigned long, struct IconContextCallback*, int);
static ReadIcon oReadIcon = NULL;

typedef int(__cdecl* ReadIconPixels)(struct iobuf*, struct DMIcon*, struct ColRGBA**, int*, int*, struct IconContextCallback**, int);
static ReadIconPixels oReadIconPixels = NULL;

void __fastcall hkInitClient(void* This, void* _EDX, const char* a, const char* b, int c);
int __cdecl hkReadIcon(struct iobuf* iobuf, struct DMIcon* icon, int a, unsigned long b, struct IconContextCallback* callback, int c);
int __cdecl hkReadIconPixels(struct iobuf* _iobuf, struct DMIcon* _icon, struct ColRGBA** _colArray, int* _height, int* _width, struct IconContextCallback** _callbackArray, int _c);
void __fastcall hkCommandEvent(void* This, void* _EDX, unsigned char a, unsigned short b, unsigned char c);