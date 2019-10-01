#ifndef COMMON_FUNCTION_H_INCLUDED
#define COMMON_FUNCTION_H_INCLUDED

#include <uf_defs.h>
#include <uf.h>
#include <vector>
#include <uf_undo.h>
#include <NXOpen/UGMath.hxx>
#include <NXOpen\TaggedObject.hxx>
#include "../TY_Def.h"
//#include "Common.h"
//#include "Com.h"

using namespace std;
using namespace NXOpen;



typedef struct SOKPointInfo
{
	SOKPointInfo()
	{
		m_pt.X = 0; m_pt.Y = 0; m_pt.Z = 0; m_rad = 0;
		m_center.X = 0; m_center.Y = 0; m_center.Z = 0;
		m_arcStart.X = 0; m_arcStart.Y = 0; m_arcStart.Z = 0;
		m_arcEnd.X = 0; m_arcEnd.Y = 0; m_arcEnd.Z = 0;
	}

    NXOpen::Point3d m_pt;
	double m_rad;
	NXOpen::Point3d m_center;//两个直线相交时候，m_pt是交点，这个是圆心点，注意这个仅仅是圆弧也就是两个直线相交才有
	//主要是给后面提供数据参考

	NXOpen::Point3d m_arcStart;//提供参考
	NXOpen::Point3d m_arcEnd;//提供参考
} SOKPointInfo, *PSOKPointInfo;

typedef struct SYBCData
{
	SYBCData()
	{
		m_y = 0;
		m_b = 0;
		m_c = 0;
		m_rd = 0;
	}
	double m_y;//输出扩展文件时候代表twy
	double m_b;//输出扩展文件时候代表twbj
	double m_c;//输出扩展文件时候代表jwc
	double m_rd;
}SYBCData;


typedef std::vector<SOKPointInfo> vSOKPointInfo;
typedef vSOKPointInfo::iterator itvSOKPointInfo;


typedef std::vector<vSOKPointInfo> vvSOKPointInfo;
typedef vSOKPointInfo::iterator itvvSOKPointInfo;



//definitions - math
#define ANGTORAD(a) (PI*a/180.0)
#define RADTOANG(r) (r*180.0/PI)

#define TYCOM_CURVE_EXTEND_LENGTH 1000.0

#define DOUBLE_TOL 0.000001

#define MATH_is_zero(s, tol)      (fabs ((s)) <= (tol))
#define MATH_is_extreme(s)         (fabs ((s)) < EQ_MAX_DBL)
#define MATH_is_equal(s, t, tol)     (EQ_is_equal( s, t, tol ))
#define MATH_is_geater(s, t, tol)     ((s) > ((t) - (tol)))
#define MATH_is_greater2(s, t, tol)     ((s) > ((t) + (tol)))
#define MATH_is_less(s, t, tol)     ((s) < ((t) + (tol)))
#define MATH_is_less2(s, t, tol)     ((s) < ((t) - (tol)))

bool big(double a, double b, double tol);
bool sma(double a, double b, double tol);
bool equ(double a, double b, double tol);

//This function help to check whether a double[3] is {0,0,0}.
bool TYCOM_ISZero(double d[3]);

//This function help to check whether a Vector3d is {0,0,0}.
bool TYCOM_ISZero(NXOpen::Vector3d &d);

//This function help to check whether a Point3d is {0,0,0}.
bool TYCOM_ISZero(NXOpen::Point3d &d);

//This function help to check whether a Point3d is {0,0,0}, with input tolerance.
bool TYCOM_ISZero2(double d[3], double tol);

#define FIND_TOLERAANCE (10.0)
int vFind(vtag_t tags, tag_t tag);
int vFind(std::vector<NXOpen::TaggedObject *> &tags, NXOpen::TaggedObject * tag);
int vfind(vdouble vv, double v);
int vFind(vstring strs, string str);
int vFind(vNXString strs, NXString str);
int vfindTol(vdouble vv, double v, double tol = FIND_TOLERAANCE);
bool findExist(vtag_t tags1, vtag_t tags2);
int vFind(vint vv, int v);
int vfinddouble2(vdouble vv, double v);

double TYCOM_GetPointDistance(NXOpen::Point3d start, NXOpen::Point3d end);

int TYCOM_GetArcFrom3Point(NXOpen::Point3d start, NXOpen::Point3d end, NXOpen::Point3d intersect, double &r, NXOpen::Point3d &center);

//20151202
int TYCOM_GetArcCenterFrom3Point(NXOpen::Point3d start, NXOpen::Point3d end, NXOpen::Point3d intersect, NXOpen::Point3d &center);
int TYCOM_GetArc2Point(NXOpen::Point3d start, NXOpen::Point3d end, NXOpen::Point3d intersect, NXOpen::Point3d &p1, NXOpen::Point3d &p2);
int TYCOM_GetArc2Point_2(NXOpen::Point3d start0,NXOpen::Point3d start1, NXOpen::Point3d end0, NXOpen::Point3d end1, double rad, NXOpen::Point3d &p1, NXOpen::Point3d &p2);


int GetFirstStr(char *data, char* key, char *first);
int GetSecondStr(char *data, char* key, char *second);
int GetValueFromTxt(char *filename, char *key, char *rvalue);
int GetPO_GetNoteLanguage();
int GetPO_GetUILanguage();
int GetPO_GetNoteRNumber();
int GetPO_GetNotePNumber();
int GetPO_GetNotePath(char* pathName);
int GetPO_GetParameterPath2018HanGuo(char *pathName);
int GetPO_GetNoteDefaultName(char *name);
int GetPO_GetNoteDefaultNameExt(char *name);
int GetPO_GetNoteRadsNumber();

int TYCOM_SaveDoubleValueToFile(FILE *m_file, char *key, double value);
int GetPO_GetNoteDefaultName_HanGuo(char *name);

double GetPO_GetNoteBUCHANG();
double GetPO_GetFaZhi();
int  TYCOM_TXT_RemoveTailFileEndSign(char * str);


//求出a边对面的角度
double YuXuanDingLi(double a, double b, double c);//余弦定理 输入边长 返回A角, 通过调整输入的abc,得到三个角度
bool isTwoSegmentIntersect(NXOpen::Point3d A, NXOpen::Point3d B, NXOpen::Point3d C, NXOpen::Point3d D);
std::wstring str2wstr(const std::string &str);
bool   ExistFile(char   *szName);
 char* newGUID();

wchar_t* CharToWchar(const char * pchar);
char* WCHARTOCHAR(const wchar_t * pchar);
wchar_t * UTF8ToUnicode(const char* str);
char * UnicodeToANSI(const wchar_t* str);
char* UTF8ToANSI(const char* str);
void SortNXStrings(vNXString &strs);
int TYCOM_set_obj_attr( tag_t obj_tag, const char* title, const char *name_str );
/*extern void EF_Read_excel_file( char *filepath, char *FileName, 
							  char *table_name, char **list_data, 
							  int  columnum, int *row_num );*/
int EF_eval_exp(const char *express_input , double *value );
int ROY_dissect_exp_string(const char *express_input , NXString &leftstr, NXString &rightstr);
void TYCOM_create_STD_attributes(tag_t std_tag, vNXString names, vNXString values);
int TYCOM_STD_parametrize_part(vNXString all_express, tag_t part_tag);
extern void PrintErrorMessage( int errorCode );

int TYCOM_GetVecFromTwoPnts(NXOpen::Point3d pnt0, NXOpen::Point3d pnt1, double vec[3]);
int TYCOM_MirrorPoint_Plane(double pnt[3], double planeOri[3], double planeNormal[3], double outPnt[3]);
int TYCOM_MirrorPoint_Plane(NXOpen::Point3d pnt, NXOpen::Point3d planeOri, NXOpen::Vector3d planeNormal, NXOpen::Point3d &outPnt);

int TYCOM_MirrorPoint_Point(double pnt[3], double Ori[3], double outPnt[3]);
int TYCOM_MirrorPoint_Point(NXOpen::Point3d pnt, NXOpen::Point3d Ori, NXOpen::Point3d &outPnt);
int TYCOM_TXT_SplitToStrs(char *instr, char* key, char **strs, int &numStr);
int TYCOM_SetPrintPDFName( const char* fileName);

void TYCOM_getFilesInDirectory( string path, vector<string>& files );
int TYCOM_GetNewFileName(char *orinalFileName, char newFileName[256]);

void write_integer_to_listing_window(char *title, int n);
int report_error( char *file, int line, char *call, int irc);
#define UF_CALL(X) (report_error( __FILE__, __LINE__, #X, (X)))

NXString GetDateStr();


#endif