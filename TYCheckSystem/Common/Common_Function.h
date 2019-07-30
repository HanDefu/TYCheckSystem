#ifndef COMMON_FUNCTION_H_INCLUDED
#define COMMON_FUNCTION_H_INCLUDED

#include <uf_defs.h>
#include <uf.h>
#include <vector>
#include <uf_undo.h>
#include <NXOpen/UGMath.hxx>
#include <NXOpen\TaggedObject.hxx>
#include "TY_Def.h"
//#include "Common.h"
//#include "Common_Function.h"

using namespace std;
using namespace NXOpen;

//�����ԭ��
#define ATTR_TYCOM_MIRROR_ORI_OBJ        "ATTR_TYCOM_MIRROR_ORI_OBJ"
//�����
#define ATTR_TYCOM_MIRROR_OBJ        "ATTR_TYCOM_MIRROR_OBJ"
//�����׼��
#define ATTR_TYCOM_MIRROR_STANDARD_PART        "ATTR_TYCOM_MIRROR_STANDARD_PART"

//����ר��
#define ATTR_TYCOM_TEXT_SPLINE_BODY_HANDLE "ATTR_TYCOM_TEXT_SPLINE_BODY_HANDLE"

//��ͬ��
#define ATTR_TYCOM_SAME_OBJ        "ATTR_TYCOM_SAME_OBJ"

//���Ӽ�
#define ATTR_TYCOM_WELD_OBJ        "ATTR_TYCOM_PROPERTY_WELD"
#define ATTR_TYCOM_PROPERTY_WELD      "ATTR_TYCOM_PROPERTY_WELD"
#define ATTR_TYCOM_WELD_OBJ_MIRROR   "ATTR_TYCOM_WELD_OBJ_MIRROR"
#define ATTR_TYCOM_WELD_PART   "ATTR_TYCOM_WELD_PART"
//����ԭʼ��� ATTR_TYCOM_WELD_OBJ = value 10001 
//�������� ATTR_TYCOM_WELD_OBJ_MIRROR = value 10001 ATTR_TYCOM_WELD_OBJ

//�ͻ�����
#define ATTR_TYCOM_PROPERTY_CUSTOMER          "ATTR_TYCOM_PROPERTY_CUSTOMER"

//��ҵ��
#define ATTR_TYCOM_PROPERTY_PARTMENT          "ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE"
#define ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE     "ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE"

//�����
#define ATTR_TYCOM_PROPERTY_GROUP_NUMBER      "ATTR_TYCOM_PROPERTY_GROUP_NUMBER"
//������
#define ATTR_TYCOM_PROPERTY_GROUP_SUBINDEX "ATTR_TYCOM_PROPERTY_GROUP_SUBINDEX"

//���������
#define ATTR_TYCOM_PROPERTY_SOLID_NAME      "ATTR_TYCOM_PROPERTY_SOLID_NAME"
//���������
#define ATTR_TYCOM_PROPERTY_SOLID_NAME2      "ATTR_TYCOM_PROPERTY_SOLID_NAME2"

//����Ҫ��
#define ATTR_TYCOM_PROPERTY_TECH_REQUIREMENT      "ATTR_TYCOM_PROPERTY_TECH_REQUIREMENT"
//�ȴ���
#define ATTR_TYCOM_PROPERTY_HEAT_PROCESS      "ATTR_TYCOM_PROPERTY_HEAT_PROCESS"
//���洦��
#define ATTR_TYCOM_PROPERTY_FACE_PROCESS      "ATTR_TYCOM_PROPERTY_FACE_PROCESS"

//����
#define ATTR_TYCOM_PROPERTY_MATERIAL     "ATTR_TYCOM_PROPERTY_MATERIAL"
#define ATTR_TYCOM_PROPERTY_PARTNAME     "ATTR_TYCOM_PROPERTY_PARTNAME"

#define ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE     "ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE"
//�Ƿ�������
#define  ATTR_TYCOM_PROPERTY_NEED_RENAME "ATTR_TYCOM_PROPERTY_NEED_RENAME"
#define ATTR_TYCOM_PROPERTY_PART_QUANTITY     "ATTR_TYCOM_PROPERTY_PART_QUANTITY"
#define ATTR_TYCOM_PROPERTY_PART_QUANTITY_NUM "ATTR_TYCOM_PROPERTY_PART_QUANTITY_NUM"
//#define ATTR_TYCOM_PROPERTY_DRAWING_SCALE     "ATTR_TYCOM_PROPERTY_DRAWING_SCALE"
#define ATTR_TYCOM_PROPERTY_SH_SHEET_NUMBER     "ATTR_TYCOM_PROPERTY_SH_SHEET_NUMBER"
#define ATTR_TYCOM_PROPERTY_SH_NUMBER_OF_SHEETS    "ATTR_TYCOM_PROPERTY_SH_NUMBER_OF_SHEETS"
#define ATTR_TYCOM_PROPERTY_ITEM_REVISION    "ATTR_TYCOM_PROPERTY_ITEM_REVISION"
#define ATTR_TYCOM_DRAWING_REFERENCE_SET     "DRAWING"

//�Ƿ��ͼ
#define ATTR_TYCOM_PROPERTY_NEED_DRAFTING "ATTR_TYCOM_PROPERTY_NEED_DRAFTING"
//��׼���Ƿ�����
#define ATTR_TYCOM_PROPERTY_STD_DIVIDE "������׼��"
#define ATTR_TYCOM_PROPERTY_STD_GROUP "ʵ�����"

//��ͼ����--��һ��׼��
#define ATTR_TYCOM_DRAFTING_NORMAL_DIR "ATTR_TYCOM_DRAFTING_NORMAL_DIR"
//��ͼx����--�ڶ���׼��
#define ATTR_TYCOM_DRAFTING_X_DIR "ATTR_TYCOM_DRAFTING_X_DIR"

//ͼֽ��С
//1-a3�� 2-a3�� 3-a4�� 4-a4-��
#define ATTR_TYCOM_PROPERTY_DRAWING_TYPE     "ATTR_TYCOM_PROPERTY_DRAWING_TYPE"

//ͼ������
#define ATTR_TYCOM_PROPERTY_Layer    "ATTR_TYCOM_PROPERTY_Layer"
//Ũ��
#define ATTR_TYCOM_PROPERTY_DENSITY     "ATTR_TYCOM_PROPERTY_DENSITY"

//����ר��
#define ATTR_TYCOM_KEZI_1     "ATTR_TYCOM_KEZI_1"
#define ATTR_TYCOM_KEZI_2     "ATTR_TYCOM_KEZI_2"
#define ATTR_TYCOM_KEZI_3     "ATTR_TYCOM_KEZI_3"
#define ATTR_TYCOM_KEZI_4     "ATTR_TYCOM_KEZI_4"
#define ATTR_TYCOM_KEZI_5     "ATTR_TYCOM_KEZI_5"
#define ATTR_TYCOM_KEZI_6     "ATTR_TYCOM_KEZI_6"
#define ATTR_TYCOM_KEZI_7     "ATTR_TYCOM_KEZI_7"
#define ATTR_TYCOM_KEZI_8     "ATTR_TYCOM_KEZI_8"

//��ģ������滻������������
#define ATTR_TYCOM_EXTRUDE_REPLACE     "ATTR_TYCOM_EXTRUDE_REPLACE"

//������ϼ��Ƿ�����������ͼ
#define ATTR_TYCOM_WEB_SUB_DRAFTING_FLAG     "ATTR_TYCOM_WEB_SUB_DRAFTING_FLAG"

//��ϼ������ ���Ĳ������ͼֽ
#define WELD_DRAFTING_NUMBER 1500

#define NX_VERSION_60

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
	NXOpen::Point3d m_center;//����ֱ���ཻʱ��m_pt�ǽ��㣬�����Բ�ĵ㣬ע�����������Բ��Ҳ��������ֱ���ཻ����
	//��Ҫ�Ǹ������ṩ���ݲο�

	NXOpen::Point3d m_arcStart;//�ṩ�ο�
	NXOpen::Point3d m_arcEnd;//�ṩ�ο�
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
	double m_y;//�����չ�ļ�ʱ�����twy
	double m_b;//�����չ�ļ�ʱ�����twbj
	double m_c;//�����չ�ļ�ʱ�����jwc
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


//���a�߶���ĽǶ�
double YuXuanDingLi(double a, double b, double c);//���Ҷ��� ����߳� ����A��, ͨ�����������abc,�õ������Ƕ�
bool isTwoSegmentIntersect(NXOpen::Point3d A, NXOpen::Point3d B, NXOpen::Point3d C, NXOpen::Point3d D);
std::wstring str2wstr(const std::string &str);
bool   ExistFile(char   *szName);
 char* newGUID();
extern int BYD_set_OBJ_string_attr( tag_t part_tag, char title[64], const char name_str[1024] );
extern int BYD_set_obj_integer_attr( tag_t part_tag, char title[64], int data );
extern int BYD_set_obj_real_attr( tag_t part_tag, char title[64], double data );
int EF_ask_obj_real_attr( tag_t obj , char *title , double *real_data );
int EF_ask_obj_integer_attr( tag_t obj , char *title , int *integer_data );
int EF_ask_obj_integer_attr_Ori( tag_t obj , char *title , int *integer_data );


int USER_ask_obj_string_attr( tag_t obj , char *title , char *string );
bool USER_ask_obj_has_attr( const tag_t obj , char *title );
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
#endif