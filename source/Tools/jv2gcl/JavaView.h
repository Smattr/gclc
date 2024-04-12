// JavaView.h: Schnittstelle f�r die Klasse CJavaView.
//
//////////////////////////////////////////////////////////////////////

#if !defined(JAVAVIEW_H)
#define JAVAVIEW_H


#include "gcompiler.h"
#include "GCLCInput.h"
#include "FileInput.h"
#include <string>

#include "ListOfFaces.h"


#define MAX_TOKEN_LEN 1024
#define MAX_POINTS 10000

class CGCLCInput;


struct javaviewpoint
{
	double x,y;
	char r,g,b;
	int thickness;
	bool visible;
};



enum JavaViewcommands
{
	_jv_jvx_model,
	_jv_meta,
	_jv_title, 
	_jv_version, 
	_jv_authors, 
	_jv_description, 
	_jv_geometries, 
	_jv_geometry, 
	_jv_pointset, 
	_jv_points, 
	_jv_p, 
	_jv_thickness, 
	_jv_colors, 
	_jv_color, 
	_jv_c, 
	_jv_vectorfield, 
	_jv_vectors, 
	_jv_v, 
	_jv_lineset, 
	_jv_lines, 
	_jv_l, 
	_jv_faceset, 
	_jv_faces, 
	_jv_f, 
	_jv_unsupportedcommand,
	_jv_number_of_commands
};




class CJavaView  
{
public:
	CJavaView();
	virtual ~CJavaView();
	
	GReturnValue Import(CGCLCInput *pInput, FILE *hOutput);

private:

	FILE *m_hOutput;
	
	char *JVTagName[100][2];

	CGCLCInput *m_pInput;
	char m_sToken[MAX_TOKEN_LEN];
	char m_sParams[MAX_TOKEN_LEN];
	GReturnValue GetToken(char **psToken);

	JavaViewcommands choose_command(char* word,char* params);
	GReturnValue  skip(const std::string &commandname);
	void AttachNames();

	
	GReturnValue ReadModel();
	GReturnValue ReadGeometries();
	GReturnValue ReadGeometry();
	GReturnValue ReadPointSet();
	GReturnValue ReadPoints();
	GReturnValue ReadP();

	GReturnValue ReadFaceSet();
	GReturnValue ReadFaces();
	GReturnValue ReadF();

	GReturnValue ReadLineSet();
	GReturnValue ReadLines();
	GReturnValue ReadL();

	GReturnValue ReadVectorField();
	GReturnValue ReadVectors();
	GReturnValue ReadV();

	GReturnValue ReadColors();
	GReturnValue ReadC();

	GReturnValue ReadThickness();
	
	GReturnValue ReadNumber(double *dNumber);
	GReturnValue convert(char *word, double *number);

	int m_iLineBeforeLastToken;
	int m_iPositionBeforeLastToken;

	int m_iGeometryIndex;

	GReturnValue Output(char *s);

	GReturnValue ReadFaceColors();
	GReturnValue ReadFaceC();
	
	CListOfFaces m_ListOfFaces;
	int m_iNumberOfFaces;

	CListOfPoints m_ListOfPoints;
	int m_iNumberOfPoints, m_iCurrentPoint; 

	char m_sOutput[MAX_TOKEN_LEN];

	char m_cUnreadChar;

};

#endif // !defined(JAVAVIEW_H)





	
