
#pragma once

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
	ST_PNT_VERTEX() {}
	explicit ST_PNT_VERTEX(float px, float py, float pz, float nx, float ny, float nz, float tu, float tv)
		: p(px, py, pz), n(nz, ny, nz), t(tu, tv) {}
};

typedef struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR c;
	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
}CUSTOMVERTEX;


typedef struct tagBoneMesh : public D3DXMESHCONTAINER
{
	// 움직이기 이전의 메쉬 정보.
	LPD3DXMESH					pOriMesh;
	
	std::vector<D3DMATERIAL9>		vecMtrl;
	std::vector<LPDIRECT3DTEXTURE9>	vecTexture;

	// 재질의 갯수
	DWORD						dwAttCnt;

	// 서브셋들을 배열형태로 담아두기위한 포인터
	D3DXATTRIBUTERANGE*			pAttTable;

	// 메쉬에 영향을 미치는 본들의 결합된 행렬을 가르키는 포인터.
	D3DXMATRIX**				ppBoneMatrix;

	// 메쉬에 영향을 미치는 여러개의 행렬들 중 가장 앞 행렬의 주소
	D3DXMATRIX*					pBoneoffSetMatrix;

	// 메쉬를 렌더링 해야할 최종행렬.
	D3DXMATRIX*					pCurrentBoneMatrix;
}BONEMESH;

typedef struct tagBone : public _D3DXFRAME
{
	D3DXMATRIX			matWorld;
}BONE;



// 텍스쳐의 정보
typedef struct  tagTextureInfo
{
	D3DXIMAGE_INFO	TexInfo;

	union
	{
		LPDIRECT3DTEXTURE9				pTexture;
		LPDIRECT3DCUBETEXTURE9			pCubeTexture;
	};
}TEXINFO;

// 삼각형하나를 그리기 위한 버텍스의 인덱스정보
typedef struct tagIndex
{
	DWORD			_1, _2, _3;
}INDEX;

typedef struct tagCubeVtxTex
{
	D3DXVECTOR3		vPosition;
	D3DXVECTOR3		vTexture;
}CUBEVTXTEX;

const DWORD VTXFVF_CUBETEX = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagVertexTexture
{
	D3DXVECTOR3		vPosition;

	D3DXVECTOR3		vNormal;

	// 현재 버텍스가 참조해야할 텍스쳐 상의 비율좌표
	D3DXVECTOR2		vTexture;
}VTXTEX;

const DWORD	VTXFVF_VTXTEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;


typedef struct tagVertexColor
{
	D3DXVECTOR3		vPosition;
	DWORD			dwDiffuse;
}VTXCOL;

const DWORD	VTXFVF_VTXCOL = D3DFVF_XYZ | D3DFVF_DIFFUSE;




typedef struct tagInfo
{
	D3DXVECTOR3		vPos;		// 위치
	D3DXVECTOR3		vLook;		// 캐릭터 기준 방향(matrix만들때 쓴다, 왠만하면 고치지말것)
	D3DXVECTOR3		vDir;		// 캐릭터 전방(Look이 정해준다)
	D3DXMATRIX		matWorld;	// 캐릭터 월드 매트릭스
}INFO;


typedef struct tagRay
{
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;
	tagRay(float x = 0.f, float y = 0.f, float z = 0.f)
		: origin(0, 0, 0), direction(x, y, z) {}
	tagRay(const D3DXVECTOR3& dir) : origin(0, 0, 0), direction(dir) {}
	tagRay(const tagRay& ray) : origin(ray.origin), direction(ray.direction) {}
}RAY;

typedef struct tagSphere
{
	float			fRadius;
	D3DXVECTOR3*	vpCenter;
	bool			isPicked = false;

	tagSphere() : fRadius(0.0f), vpCenter(nullptr) {}
	tagSphere(const float r, D3DXVECTOR3* v) : fRadius(r), vpCenter(v) {}
	tagSphere(const tagSphere& sph) : fRadius(sph.fRadius), vpCenter(sph.vpCenter) {}
}SPHERE;


typedef struct tagParticleVtx
{
	D3DXVECTOR3				vPosition;
	DWORD					dwColor;
}PARTICLEVTX;

const DWORD VTXFVF_PARTICLE = D3DFVF_XYZ | D3DFVF_DIFFUSE;
