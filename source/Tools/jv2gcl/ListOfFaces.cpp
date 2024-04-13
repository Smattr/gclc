// ListOfFaces.cpp: implementation of the CListOfFaces class.
//
//////////////////////////////////////////////////////////////////////

#include "ListOfFaces.h"
#include <malloc.h>
#include <string>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfFaces::CListOfFaces()
{
	m_pFirstFace = NULL;
	m_pLastFace = NULL;
}

CListOfFaces::~CListOfFaces()
{
	DeleteAll();
}


void CListOfFaces::DeleteAll()
{
	CFace *pFace, *pF;

	pFace=m_pFirstFace;

	while(pFace!=NULL)
	{
		pF = pFace->m_pNextFace;
		if(pFace->name!=NULL)
			free(pFace->name);
		delete pFace;
		pFace = pF;
	}
	m_pFirstFace = NULL;
	m_pLastFace = NULL;
}



void CListOfFaces::SetGeometryIndex(unsigned int uIndex)
{
	m_iGeometry = uIndex;
}


bool CListOfFaces::AddNewFace()
{
	CFace *pFace;

	pFace = new CFace;
	if (pFace == NULL) 
		return false;

	pFace->m_pNextFace = NULL;
	pFace->name=NULL;
	pFace->r=0;
	pFace->g=0;
	pFace->b=0;

	if(m_pFirstFace==NULL)
		m_pFirstFace=pFace;
	else
		m_pLastFace->m_pNextFace = pFace;
	
	m_pLastFace = pFace;

	return true;
}

		
bool CListOfFaces::AddNewVertex(unsigned int uIndex)
{
	return m_pLastFace->AddNewVertex(uIndex);
}


void CListOfFaces::AttachColorsToCurrentFace(unsigned char r,unsigned char g,unsigned char b)
{
	m_pCurrentFace->AttachColors(r,g,b);
}




CFace* CListOfFaces::GetFirstFace()
{
	m_pCurrentFace = m_pFirstFace;
	return m_pCurrentFace;
}


CFace* CListOfFaces::GetNextFace()
{
	if (m_pCurrentFace!=NULL)
	{
		m_pCurrentFace = m_pCurrentFace->m_pNextFace;
		return m_pCurrentFace;
	}
	else
		return NULL;
}


void CListOfFaces::SetLastFaceName(char* sName)
{
	m_pLastFace->name = sName;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CFace::CFace()
{
	m_pFirstVertex = NULL;
}


CFace::~CFace()
{
	struct vertex *pVertex, *pV;

	pVertex= m_pFirstVertex;

	while(pVertex!=NULL)
	{
		pV = pVertex->pnext;
		delete pVertex;
		pVertex = pV;
	}
}


bool CFace::AddNewVertex(unsigned int uIndex)
{
	struct vertex *pVertex;

	pVertex= new vertex;
	if (pVertex == NULL) 
		return false;

	pVertex->index = uIndex;
	pVertex->pnext = NULL;
	
	if(m_pFirstVertex==NULL)
		m_pFirstVertex = pVertex;
	else
		m_pLastVertex->pnext = pVertex;		

	m_pLastVertex=pVertex;
	
	return true;
}



struct vertex* CFace::GetFirstVertex()
{
	m_pCurrentVertex = m_pFirstVertex;
	return m_pCurrentVertex;
}


struct vertex* CFace::GetNextVertex()
{
	if (m_pCurrentVertex!=NULL)
	{
		m_pCurrentVertex = m_pCurrentVertex->pnext;
		return m_pCurrentVertex;
	}
	else
		return NULL;
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListOfPoints::CListOfPoints()
{
	m_iCurrentPoint = 0;
}

CListOfPoints::~CListOfPoints()
{
	DeleteAll();
}

void CListOfPoints::DeleteAll() {
	m_vPoints.clear();
}

void CListOfPoints::SetGeometryIndex(unsigned int uIndex)
{
	m_iGeometry = uIndex;
}

bool CListOfPoints::AddNewPoint(double x,double y,unsigned char r,unsigned char g,unsigned char b)
{
	struct point pPoint;

	pPoint.x = x;
	pPoint.y = y;
	pPoint.r = r;
	pPoint.g = g;
	pPoint.b = b;

	m_vPoints.push_back(pPoint);
	return true;
}

void CListOfPoints::AttachColorsToCurrentPoint(unsigned char r,unsigned char g,unsigned char b)
{
	m_vPoints[m_iCurrentPoint].r = r;
	m_vPoints[m_iCurrentPoint].g = g;
	m_vPoints[m_iCurrentPoint].b = b;
}

struct point* CListOfPoints::GetFirstPoint()
{
	m_iCurrentPoint = 0;
	return m_vPoints.empty() ? NULL : &m_vPoints.front();
}

struct point* CListOfPoints::GetNextPoint()
{
	if (m_iCurrentPoint + 1 < m_vPoints.size())
	{
		++m_iCurrentPoint;
		return &m_vPoints[m_iCurrentPoint];
	}
	else
		return NULL;
}

void CListOfPoints::GetCurrentPoint(double *x,double *y) 
{ 
	*x = m_vPoints[m_iCurrentPoint].x;
	*y = m_vPoints[m_iCurrentPoint].y;
}

void CListOfPoints::SetLastPointName(const std::string &sName)
{
	m_pLastPoint->name = sName;
}

