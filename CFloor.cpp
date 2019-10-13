#include "BaseInclude.h"
#include "CFloor.h"


CFloor::CFloor()
	: m_VertexBuffer(nullptr)
	, m_IndexBuffer(nullptr)
{
}


CFloor::~CFloor()
{
	SAFE_RELEASE(m_IndexBuffer);
	SAFE_RELEASE(m_VertexBuffer);
}

HRESULT CFloor::Initialize()
{
	D3DXMatrixIdentity(&m_matWorld);

	float width = 0.f;
	float height = 0.f;
	float start = -20.f;
	ST_PNT_VERTEX v1, v2, v3;
	width = 60.f;
	height = 60.f;
	D3DXVECTOR3	 model(start, 0.f, start);
	D3DXVECTOR3 vUp(0.f, 0.f, start + height);
	D3DXVECTOR3 vRight(start + width, 0.f, 0.f);
	D3DXVECTOR3 vUR = vUp + vRight;
	D3DXVECTOR3 vDir1, vDir2, normal;
	v1.p = model;			v1.t = D3DXVECTOR2(0.f, 1.f); m_vecVertex.push_back(v1);
	v2.p = model + vUp;		v2.t = D3DXVECTOR2(0.f, 0.f); m_vecVertex.push_back(v2);
	v3.p = model + vRight;	v3.t = D3DXVECTOR2(1.f, 1.f); m_vecVertex.push_back(v3);
	vDir1 = v1.p - v2.p; vDir2 = v1.p - v3.p;
	D3DXVec3Cross(&normal, &vDir1, &vDir2);
	m_vecVertex[0].n = m_vecVertex[1].n = m_vecVertex[2].n = normal;
	v1.p = model + vUR;		v1.t = D3DXVECTOR2(1.f, 0.f); m_vecVertex.push_back(v1);
	v2.p = model + vRight;	v2.t = D3DXVECTOR2(1.f, 1.f); m_vecVertex.push_back(v2);
	v3.p = model + vUp;		v3.t = D3DXVECTOR2(0.f, 0.f); m_vecVertex.push_back(v3);
	vDir1 = v1.p - v2.p; vDir2 = v1.p - v3.p;
	D3DXVec3Cross(&normal, &vDir1, &vDir2);
	m_vecVertex[3].n = m_vecVertex[4].n = m_vecVertex[5].n = normal;

	m_vecIndice.resize(m_vecVertex.size());
	fill(m_vecIndice.begin(), m_vecIndice.end(), 0);

	int sizeVertex = sizeof(ST_PNT_VERTEX);
	int sizeVtxByte = (int)(m_vecVertex.size()) * sizeVertex;
	GET_DEVICE->CreateVertexBuffer(sizeVtxByte, D3DUSAGE_WRITEONLY,
		ST_PNT_VERTEX::FVF, D3DPOOL_MANAGED, &m_VertexBuffer, NULL);
	void* pVer;
	if (FAILED(m_VertexBuffer->Lock(0, 0, &pVer, 0)))
		cout << "버텍스 버퍼 오류" << endl;
	memcpy_s(pVer, sizeVtxByte, &m_vecVertex[0], sizeVtxByte);
	m_VertexBuffer->Unlock();

	int sizeIndex = sizeof(WORD);
	int sizeIdxByte = (int)(m_vecIndice.size()) * sizeIndex;
	GET_DEVICE->CreateIndexBuffer(sizeIdxByte, 0,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, NULL);
	void* pIdx;
	if (FAILED(m_IndexBuffer->Lock(0, sizeIdxByte, &pIdx, 0)))
		cout << "인텍스 버퍼 오류" << endl;
	memcpy_s(pIdx, sizeIdxByte, &m_vecIndice[0], sizeIdxByte);
	m_IndexBuffer->Unlock();

	ZeroMemory(&m_material, sizeof(D3DMATERIAL9));
	m_material.Ambient.r = 0.9f;
	m_material.Ambient.g = 0.9f;
	m_material.Ambient.b = 0.9f;
	m_material.Ambient.a = 0.9f;
	m_material.Diffuse.r = 0.9f;
	m_material.Diffuse.g = 0.9f;
	m_material.Diffuse.b = 0.9f;
	m_material.Diffuse.a = 0.9f;

	D3DXCreateTextureFromFile(GET_DEVICE, L"Resource/floor.jpg", &m_texture);
	return S_OK;
}

void CFloor::Progress()
{
}

void CFloor::Render()
{
	GET_DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	GET_DEVICE->SetMaterial(&m_material);
	GET_DEVICE->SetTexture(0, m_texture);
	GET_DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);
	GET_DEVICE->SetStreamSource(0, m_VertexBuffer, 0, sizeof(ST_PNT_VERTEX));
	GET_DEVICE->SetFVF(ST_PNT_VERTEX::FVF);
	if (m_IndexBuffer) {
		GET_DEVICE->SetIndices(m_IndexBuffer);
		int cntVertex = (int)m_vecVertex.size();
		GET_DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0, 0, cntVertex, 0, cntVertex / 3);
	}
	else {
		int cntVertex = (int)(m_vecVertex.size());
		GET_DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, cntVertex);
	}
}

void CFloor::Release()
{
}

const D3DXVECTOR3 & CFloor::GetVertexPosition(IN int index, OUT int & vertexSize)
{
	vertexSize = m_vecVertex.size();

	if (index < (int)m_vecVertex.size())
		return m_vecVertex[index].p;
	else
		return *(new D3DXVECTOR3(0, 0, 0));
}

D3DXVECTOR3 CFloor::GetPickingPoint()
{
	D3DXVECTOR3 vec;
	for (int i = 0; i < (int)m_vecVertex.size(); i += 3)
	{
		if (CheckPickingOnTriangle(&m_vecVertex[i].p, &m_vecVertex[i + 1].p, &m_vecVertex[i + 2].p, &vec)) {
			return vec;
		}
	}
	return D3DXVECTOR3(0.f, 0.f, 0.f);
}
