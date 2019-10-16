#pragma once
//ENUM형 사용파일

enum TEXTYPE
{
	TEXTYPE_NORMAL,
	TEXTYPE_CUBE,
};

enum BUFFERTYPE
{
	BUFFERTYPE_TRICOL,
	BUFFERTYPE_RCCOL,
	BUFFERTYPE_RCTEX,
	BUFFERTYPE_CUBE,
	BUFFERTYPE_TERRAIN
};
enum BOUNDTYPE
{
	BOUNDTYPE_SPHERE,
	BOUNDTYPE_CUBE,
};
enum MESHTYPE
{
	MESHTYPE_STATIC,
	MESHTYPE_DYNAMIC,
	MESHTYPE_END

};
enum WINMODE { WINMODE_FULL, WINMODE_WIN };
enum ANGLE { ANGLE_X, ANGLE_Y, ANGLE_Z, ANGLE_END };
enum CAMMODE { CAMMODE_DYNAMIC, CAMMODE_STATIC, CAMMODE_GAME, CAMMODE_END };
enum SORTID { SORTID_FIRST, SORTID_NORMAL, SORTID_LAST, SORTID_END };
enum TERRIAN_INSERTTYPE
{
	INSERTTYPE_NUMBER,
	INSERTTYPE_ENGLISH,
};
enum THREADMENU{THREAD_MOUSE, THREAD_END};
enum PARTICLETYPE { PARTICLETYPE_LINELAZER };