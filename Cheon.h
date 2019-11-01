#pragma once
#include<string>

enum UI_CHAMPTYPE
{
	UI_CHAMPTYPE_STATIC,
	UI_CHAMPTYPE_DYNAMIC
};

enum UI_SPELLTYPE
{
	SPELLTYPE_End,
	cleanse,
	Exhaust,
	Flash,
	Ghost,
	Heal,
	Smite,
	Teleport,
	Ignite,
	Barrier
};

typedef struct ST_PT_VERTEX
{
	D3DXVECTOR3 p; //position
	D3DXVECTOR2 t; //uv position
	enum {FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_NORMAL};
};