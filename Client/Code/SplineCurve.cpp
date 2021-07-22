#include "stdafx.h"
#include "..\Header\SplineCurve.h"


CSplineCurve::CSplineCurve()
{
}


CSplineCurve::~CSplineCurve()
{
}

void CSplineCurve::CreateCurve(Desc* pDesc)
{
	memcpy(&m_desc, pDesc, sizeof(Desc));

	int index = 0;
	m_curve.clear();

	// first curve -> first_p, p0, p1, p2
	for (_uint i = 0; i < m_desc.detail; ++i)
	{
		_float3 out;
		D3DXVec3CatmullRom(&out, &m_points[0], &m_points[0], &m_points[1], &m_points[2], (_float)i / (_float)m_desc.detail);
		m_curve.emplace_back(out);
	}

	// middle curves
	for (; index < m_points.size() - 3; ++index)
	{
		for (_uint i = 0; i < m_desc.detail; ++i)
		{
			_float3 out;
			D3DXVec3CatmullRom(&out, &m_points[index], &m_points[index + 1], &m_points[index + 2], &m_points[index + 3], (_float)i / (_float)m_desc.detail);
			m_curve.emplace_back(out);
		}
	}

	// last curve pn-2, pn-1, pn, lastp

	for (_uint i = 0; i < m_desc.detail + 1; ++i)
	{
		_float3 out;
		D3DXVec3CatmullRom(&out, &m_points[index], &m_points[index + 1], &m_points[index + 2], &m_points[index + 2], (_float)i / (_float)m_desc.detail);
		m_curve.emplace_back(out);
	}


	//CalcDistanceRatio();
}

vector<_float3>* CSplineCurve::GetCurve()
{
	return &m_curve;
}

void CSplineCurve::AddPoint(_float3 _point)
{
	m_points.emplace_back(_point);
}

void CSplineCurve::SubPoint(int _index)
{
	if (_index >= m_points.size())
		return;

	m_points.erase(m_points.begin() + _index);
}

void CSplineCurve::DeletePoints()
{
	m_points.clear();
}


_float3 CSplineCurve::GetPoint(float ratio)
{
	_float curveFrameCount = _float(m_curve.size() - 1);
	curveFrameCount *= ratio;
	
	_uint curveIndex = (_uint)curveFrameCount;

	return m_curve[curveIndex];


// 	_ratio = GET_MATH->MinMax(_ratio, 0.f, 1.f);
// 
// 	int index = 0;
// 	_float3 point;
// 	for (int i = 0; i < m_distanceRatio.size(); ++i)
// 	{
// 		if (_ratio <= m_distanceRatio[i])
// 		{
// 			float total;
// 			float patial;
// 			if (i == 0)
// 			{
// 				total = m_distanceRatio[i];
// 				patial = _ratio;
// 
// 			}
// 			else
// 			{
// 				total = m_distanceRatio[i] - m_distanceRatio[i - 1];
// 				patial = _ratio - m_distanceRatio[i - 1];
// 
// 			}
// 
// 			point = GetPoint(i + 2, patial / total);
// 			break;
// 
// 		}
// 	}
// 	return point;
}

_float3 CSplineCurve::GetPoint(int _index, float _ratio)
{
	_float3 point;

	if(_index == 0)
		D3DXVec3CatmullRom(&point, &m_points[0], &m_points[0], &m_points[1], &m_points[2], _ratio);
	else if (0 < _index && _index < m_points.size() - 1)
	{
		D3DXVec3CatmullRom(&point, &m_points[_index - 1], &m_points[_index], &m_points[_index + 1], &m_points[_index + 2], _ratio);
	}
	else if(_index == m_points.size() - 1)
		D3DXVec3CatmullRom(&point, &m_points[_index - 2], &m_points[_index - 1], &m_points[_index], &m_points[_index], _ratio);

	return point;
}


void CSplineCurve::CalcDistanceRatio()
{
	float totalDistance = 0;
	vector<float> distantList;

	m_distanceRatio.clear();

	for (int i = 1; i < m_points.size() - 2; ++i)
	{
		_float distance = D3DXVec3Length(&(m_points[i + 1] - m_points[i]));
		totalDistance += distance;
		distantList.emplace_back(totalDistance);
	}

	for (auto& distance : distantList)
	{
		m_distanceRatio.emplace_back(distance / totalDistance);
	}
}
