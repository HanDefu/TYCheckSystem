#include "Common_Function.h"
#include <math.h>
#include <float.h>
#include <uf_assem.h>
#include "Common_Function_UG.h"
#include <windows.h>
#include <uf_vec.h>
#include <sql.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <algorithm>
#include <uf_mtx.h>
#include <io.h>

using namespace NXOpen;
using namespace std;

bool big(double a, double b, double tol)
{
	if(a - b > tol) return true;
	return false;
}
bool sma(double a, double b, double tol)
{
	if(b - a > tol) return true;
	return false;
}
bool equ(double a, double b, double tol)
{
	if(!big(a,b,tol) && !sma(a,b,tol)) return true;
	return false;
}

//This function help to check whether a double[3] is {0,0,0}.
bool TYCOM_ISZero(double d[3])
{
    if(MATH_is_zero(d[0], DOUBLE_TOL) && 
	   MATH_is_zero(d[1], DOUBLE_TOL) && 
	   MATH_is_zero(d[2], DOUBLE_TOL))
	   return true;
	return false;
}

//This function help to check whether a Vector3d is {0,0,0}.
bool TYCOM_ISZero(Vector3d &d)
{
	if(MATH_is_zero(d.X, DOUBLE_TOL) && 
	   MATH_is_zero(d.Y, DOUBLE_TOL) && 
	   MATH_is_zero(d.Z, DOUBLE_TOL))
	   return true;
	return false;
}

//This function help to check whether a Point3d is {0,0,0}.
bool TYCOM_ISZero(Point3d &d)
{
	if(MATH_is_zero(d.X, DOUBLE_TOL) && 
	   MATH_is_zero(d.Y, DOUBLE_TOL) && 
	   MATH_is_zero(d.Z, DOUBLE_TOL))
	   return true;
	return false;
}

//This function help to check whether a Point3d is {0,0,0}, with input tolerance.
bool TYCOM_ISZero2(double d[3], double tol)
{
    if(MATH_is_zero(d[0], tol) && 
	   MATH_is_zero(d[1], tol) && 
	   MATH_is_zero(d[2], tol))
	   return true;
	return false;
}


int vFind(vtag_t tags, tag_t tag)
{
	int index = -1;
	for(int i = 0; i < (int)tags.size(); i++)
	{
		if(tag == tags[i])
		{
			index = i;
			break;
		}
	}
	return index;
}

int vFind(vstring strs, string str)
{
	int index = -1;
	for(int i = 0; i < (int)strs.size(); i++)
	{
		if(str == strs[i])
		{
			index = i;
			break;
		}
	}
	return index;
}

int vFind(vNXString strs, NXString str)
{
	int index = -1;
	for(int i = 0; i < (int)strs.size(); i++)
	{
		if(strcmp(str.GetText(), strs[i].GetText()) == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}

int vFind(vint vv, int v)
{
	int index = -1;
	for(int i = 0; i < (int)vv.size(); i++)
	{
		//20160516这个公差放的有点大了
		if(vv[i] == v)
		{
			index = i;
			return i;
		}
	}
	return index;
}

int vfind(vdouble vv, double v)
{
	int index = -1;
	for(int i = 0; i < (int)vv.size(); i++)
	{
		//20160516这个公差放的有点大了
		if(fabs(v - vv[i]) < 1)
		{
			index = i;
			break;
		}
	}
	return index;
}

int vFind(std::vector<NXOpen::TaggedObject *> &tags, NXOpen::TaggedObject * tag)
{
	int index = -1;
	for(int i = 0; i < (int)tags.size(); i++)
	{
		if(tag == tags[i])
		{
			index = i;
			break;
		}
	}
	return index;
}

int vfindTol(vdouble vv, double v, double tol)
{
	int index = -1;
	for(int i = 0; i < (int)vv.size(); i++)
	{
		if(fabs(v - vv[i]) < tol)
		{
			index = i;
			break;
		}
	}
	return index;
}

int vfinddouble2(vdouble vv, double v)
{
	int index = -1;
	for(int i = 0; i < (int)vv.size(); i++)
	{
		if(fabs(v - vv[i]) < 0.1)
		{
			index = i;
			break;
		}
	}
	return index;
}

bool findExist(vtag_t tags1, vtag_t tags2)
{
	for(int i = 0; i < (int)tags2.size(); i++)
	{
		if(vFind(tags1, tags2[i]) == -1)
			return false;
	}
	return true;
}


double TYCOM_GetPointDistance(Point3d start, Point3d end)
{
	return sqrt((start.X-end.X)*(start.X-end.X) + 
		        (start.Y-end.Y)*(start.Y-end.Y) +
				(start.Z-end.Z)*(start.Z-end.Z));
}

int GetFirstStr(char *data, char* key, char *first)
{
    char *p = strtok(data,key);//第一次调用,传要处理的串参数地址s 
	strcpy(first,p);
	return 0;
}

int GetSecondStr(char *data, char* key, char *second)
{
    char *p = strtok(data,key);//第一次调用,传要处理的串参数地址s 
	p = strtok(NULL,key);//第二次调用
	strcpy(second,p);
	/*while(p)
	{
        p = strtok(NULL,key);
	}*/
	return 0;
}

int TYCOM_GetArcFrom3Point(Point3d start, Point3d end, Point3d intersect, double &r, Point3d &center)
{
	Point3d midPoint;
	midPoint.X = (start.X + end.X)/2.0;
	midPoint.Y = (start.Y + end.Y)/2.0;
	midPoint.Z = (start.Z + end.Z)/2.0;

    double a = TYCOM_GetPointDistance(intersect, midPoint);
	double b = TYCOM_GetPointDistance(intersect, start);
	double c = b * b /a;
	if(a > 100000 || b > 1000000 || c>100000)
		r = 0;
	else
	{
		if(c*c - b * b <= 0)
			r = 0;
		else
	        r = sqrt(c*c - b * b);
	}



 ////20161021第二部分
	//求出圆心
    double d = TYCOM_GetPointDistance(midPoint, start);
	double e = sqrt(r*r - d*d);
	//x = x2+e/a * (x2-x1);
	center.X = midPoint.X + (e/a)*(midPoint.X - intersect.X);
	center.Y = midPoint.Y + (e/a)*(midPoint.Y - intersect.Y);
	center.Z = midPoint.Z + (e/a)*(midPoint.Z - intersect.Z);
	return 0;
}

//This function extend a input line by input value.
//You can choose to just extend start or end part of this line.
Point3d  TYCOM_CurveExtendCurve(Point3d start, Point3d end, double value)
{
    double a = TYCOM_GetPointDistance(start, end);
    Point3d pnt;

	pnt.X = value * (end.X - start.X)/a + end.X;
	pnt.Y = value * (end.Y - start.Y)/a + end.Y;
	pnt.Z = value * (end.Z - start.Z)/a + end.Z;

	return pnt;
}

int TYCOM_GetArcCenterFrom3Point(Point3d start, Point3d end, Point3d intersect, Point3d &center)
{
	Point3d midPoint;
	midPoint.X = (start.X + end.X)/2.0;
	midPoint.Y = (start.Y + end.Y)/2.0;
	midPoint.Z = (start.Z + end.Z)/2.0;

    double a = TYCOM_GetPointDistance(intersect, midPoint);
	double b = TYCOM_GetPointDistance(intersect, start);
	double c = b * b /a;
	double r = sqrt(c*c - b * b);

    double disLen = sqrt(r*r + b*b) - a;

    center = TYCOM_CurveExtendCurve(intersect, midPoint, disLen);
    
	return 0;
}

int TYCOM_GetArc2Point(Point3d start, Point3d end, Point3d intersect, Point3d &p1, Point3d &p2)
{
	Point3d midPoint;
	midPoint.X = (start.X + end.X)/2.0;
	midPoint.Y = (start.Y + end.Y)/2.0;
	midPoint.Z = (start.Z + end.Z)/2.0;

    double a = TYCOM_GetPointDistance(intersect, midPoint);
	double b = TYCOM_GetPointDistance(intersect, start);
	double c = b * b /a;
	double r = sqrt(c*c - b * b);

    double L = sqrt(r*r + b*b);
	double L2 = L + r;

	double L3 =  L * L2/b;

    
    p1 = TYCOM_CurveExtendCurve(intersect, start, L3 - b);
	p2 = TYCOM_CurveExtendCurve(intersect, end, L3 - b);
    
	return 0;
}

int TYCOM_GetArc2Point_2(Point3d start0,Point3d start1, Point3d end0, Point3d end1, double rad, Point3d &p1, Point3d &p2)
{

    p1 = TYCOM_CurveExtendCurve(start0, start1, rad);
	p2 = TYCOM_CurveExtendCurve(end1, end0, rad);
    
	return 0;
}

int TYCOM_SaveDoubleValueToFile(FILE *m_file, char *key, double value)
{
	if (m_file == NULL || key == NULL || strlen(key) < 1)
		return -1;

	char cvalue[32] = "";
	sprintf(cvalue, "%s=%.3f\n", key,value);
	fputs(cvalue, m_file);
	return 0;
}

int GetValueFromTxt(char *filename, char *key, char *rvalue)
{
	FILE *m_file = NULL;

	m_file = fopen(filename,"r");
	if (m_file == NULL)
		return -1;
	
	char data[256] = "";
	char value[256] = "";
	while (!feof(m_file))
	{
		fgets(data, 256, m_file);
		if (strstr(data,key) != 0)
		{
			GetSecondStr(data,"=", value);
			break;
		}
	}
	fclose(m_file);

	if (strlen(value) == 0) 
	{
        return -1;
	}
	strcpy(rvalue, value);
	return 0;
	//else
	//{
 //       rvalue = atoi(value);
	//	return 0;
	//}
}

int GetPO_GetNotePath(char *pathName)  
{  
	char *pathNameTemp = 0;
	UF_translate_variable("UGII_USER_DIR", &pathNameTemp);
	strcpy(pathName, pathNameTemp);
	strcat(pathName, "\\application\\GetPo.ini");
	return 0;  
}

int GetPO_GetParameterPath2018HanGuo(char *pathName)  
{  
	char *pathNameTemp = 0;
	UF_translate_variable("UGII_USER_DIR", &pathNameTemp);
	strcpy(pathName, pathNameTemp);
	strcat(pathName, "\\application\\DefaultParameter2018LineCycle.ini");
	return 0;  
}

int GetPO_GetNoteLanguage()  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;
	char value[256] = "";
	int re = GetValueFromTxt(pathName, "LANGUAGE", value);
	if(re != 0)
		return -2;
	return atoi(value);
}

int GetPO_GetUILanguage()  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;
	char value[256] = "";
	int re = GetValueFromTxt(pathName, "LANGUAGE_UI", value);
	if(re != 0)
		return -2;
	return atoi(value);
}

int GetPO_GetNoteRNumber()  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;

	char value[256] = "";
	int re = GetValueFromTxt(pathName, "RNUMBER", value);
	if(re != 0)
		return -2;
	return atoi(value);
}

int GetPO_GetNotePNumber()  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;

	char value[256] = "";
	int re = GetValueFromTxt(pathName, "PNUMBER", value);
	if(re != 0)
		return -2;
	return atoi(value);
}

int GetPO_GetNoteRadsNumber()  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;

	char value[256] = "";
	int re = GetValueFromTxt(pathName, "RADS_NUMBER", value);
	if(re != 0)
		return 10;
	if(atoi(value) == 0)
		return 10;
	return atoi(value);
}

int GetPO_GetNoteDefaultName(char *name)  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;
	int re = GetValueFromTxt(pathName, "DEFAULTNAME", name);
	if(re != 0)
		return -2;
	return 0;
}

int GetPO_GetNoteDefaultName_HanGuo(char *name)  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;
	int re = GetValueFromTxt(pathName, "DEFAULTNAME2018", name);
	if(re != 0)
		return -2;
	return 0;
}

int GetPO_GetNoteDefaultNameExt(char *name)  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;
	int re = GetValueFromTxt(pathName, "DEFAULTNAME_EXT", name);
	if(re != 0)
		return -2;
	return 0;
}

double GetPO_GetNoteBUCHANG()  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;

	char value[256]="";
	int re = GetValueFromTxt(pathName, "BUCHANG", value);
	if(re != 0)
		return 0;
	return atof(value);
}


double GetPO_GetFaZhi()  
{  
	char pathName[256] = "";
	GetPO_GetNotePath(pathName);
	if(strlen(pathName) == 0) 
		return -1;

	char value[256] = "";
	int re = GetValueFromTxt(pathName, "TUIWAN_FAZHI", value);
	if(re != 0)
		return -2;
	return atof(value);
}

int  TYCOM_TXT_RemoveTailFileEndSign(char * str)
{
	if (NULL == str)
		return 1;
	int len = (int)strlen(str);
	if (len == 0) return 0;
    if (str[len - 1] == 10 || str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
	}
	return 0;
}

double YuXuanDingLi(double a, double b, double c)//余弦定理 输入边长 返回A角, 通过调整输入的abc,得到三个角度
{
	//为什么会有负数值?需要确认 20160829
	double tt = (b*b + c*c - a*a)/(2*b*c);
	if(fabs(tt) > 1)
		return 0;
	return acos((b*b + c*c - a*a)/(2*b*c));
}


std::wstring str2wstr(const std::string &str)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = str.c_str();
	size_t _Dsize = str.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	wstring result = _Dest;
	delete []_Dest;

	setlocale(LC_ALL, "C");

	return result;
}

bool isTwoSegmentIntersect(Point3d A, Point3d B, Point3d C, Point3d D)
{
    double ac[3] = {C.X - A.X,C.Y - A.Y,C.Z - A.Z};//a->c
	double ab[3] = {B.X - A.X,B.Y - A.Y,B.Z - A.Z};//a->b
	double ad[3] = {D.X - A.X,D.Y - A.Y,D.Z - A.Z};//a->b


	double nor1[3] = {0,0,0},nor2[3] = {0,0,0};
	UF_VEC3_cross(ac, ab, nor1);
	UF_VEC3_cross(ad, ab, nor2);

	double dot_product = 0;
	UF_VEC3_dot(nor1,nor2,&dot_product);
	if(dot_product > 0)
		return false;
	else
		return true;
}


#include <windows.h>
#include <ShlObj.h>

//注册专用
bool   ExistFile(char   *szName)
{
	HANDLE   hFile;
	hFile   =   CreateFileA(szName,   0,   0,   0,   OPEN_EXISTING,   0,   NULL);
	if(GetLastError()   ==   ERROR_FILE_NOT_FOUND)
	{
		CloseHandle(hFile);
		return   FALSE;
	}
	CloseHandle(hFile);
	return   TRUE;
}

///UI COMMON
char* newGUID()
{
	static char buf[64] = {0};
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(buf, sizeof(buf)
			, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
		, guid.Data4[6], guid.Data4[7]
		);
	}
	return (char*)buf;
}

/*--------------------------------------------------------------------------
*   excel 表格操作函数
---------------------------------------------------------------------------*/
static void   USER_strinit ( char *str1, char *str2 );
static void   USER_stradd ( char *str1, char *str2 );
static void   Excel_ConfigDSN ( char *temp_filepath, char *FileName );
static void   USER_stradj ( char *str1, char *str2 );
static int    USER_strlen ( char * string );

static int USER_strlen(char * string)
{
	int i = 0;
	for(;;)
	{
		if (*(string + i) == '\0'&&*(string + i + 1) == '\0')
		{
			break;
		}
		i ++;
	}
	return i ;
}
static void USER_stradj(char *str1, char *str2)
{
	int i = 0;
	int j = 0;
	int h = 0;
	i = USER_strlen(str1) + 1;
	j = USER_strlen(str2);
	for(;;)
	{
		if(h >= j)break;
		*(str1 + i + h ) = *(str2 + h);
		
		h ++;
	}
}
static void USER_strinit(char *str1, char *str2)
{
	
	int i = 0;
	
	for(;;)
	{
		if (*(str2 + i) == '\0') 
		{
			break;
		}
		*(str1 + i) = *(str2 + i);
		i ++;
	}
	*(str1 + i)     = '\0';
	*(str1 + i + 1) = '\0';
}
static void USER_stradd(char *str1, char *str2)
{
	int i = 0;
	int j = 0;
	int h = 0;
	i = USER_strlen(str1) + 1;
	j = USER_strlen(str2);

	for(;;)
	{
		if(h >= j)break;
		*(str1 + i + h ) = *(str2 + h);
		
		h ++;
	}
	*(str1 + i + h) = '\0';
    *(str1 + i + h + 1) = '\0';
}
/* --------------------------------------------------------------------
* Function name: Excel_ConfigDSN      
* Description: configure DSN of EXCEL
* Input:  FilePath -- file path 
*         FileName -- file name 
* Return: 0 -- successful; 1 -- fail
* -------------------------------------------------------------------*/
static void Excel_ConfigDSN(char * FilePath, char * FileName)
{
	char DSNAttri[TY_STR_LEN];
	char temp[TY_STR_LEN]  = {"DefaultDir="};
	char temp1[TY_STR_LEN] = {"DBQ="};
	DSNAttri[0] = '\0';//初始化为空的办法  也可以直接定义时候DSNAttri[STR_LEN]="";

	
	strcat(temp, FilePath);
	USER_strinit(temp, temp);
	USER_strinit(DSNAttri, "DSN=MYEXCELDB01");
	USER_stradd(DSNAttri, temp);
	strcat(FilePath, "\\");
	strcat(FilePath, FileName);
	strcat(temp1, FilePath);
	USER_strinit(temp1, temp1);//这个函数把后边的复制到前边来 ,并且在前者的最后加上两个结束符
	USER_stradd(DSNAttri, temp1);///这个函数是把后者的字符串加到前者的后面,去掉一个\0,保留另外一个\0在最终结尾加上\0\0
	USER_stradd(DSNAttri, "ReadOnly=00\0Description=my data base\0FIL=excel 8.0\0DriverId=790");

	if(!SQLConfigDataSource(NULL,ODBC_ADD_DSN, L"Microsoft Excel Driver (*.xls)", CharToWchar(DSNAttri)))
	{
		//printf(L" Failed to add DSN\n");	
		uc1601("000",1);
	}
}
/*-----------------------------------------------------------------------------------------
 * Function name : EF_Read_excel_file
 * Description : 读取一个表格的内容，用一个二维字符串组保存
 * Input : 
 *   filepath : 表格的路径
 *   FileName : 表格的名字
 *   table_name : 表页的名字
 *   columnum : 读取的列数
 * Output
 *    list_data :输出的字符串组
 *    row_num : 读取的行数
 * Return : void
 *-----------------------------------------------------------------------------------------*/
/*extern void EF_Read_excel_file( char *filepath, char *FileName, 
							  char *table_name, char **list_data, 
							  int  columnum, int *row_num )
{
	int            rec = 0;
	int            row = 0;
	HANDLE         hEnv;
	HANDLE         hDBC;
	HANDLE         hSTMT;
	char           sSql[200];
	SQLLEN     Columnlen;
	int            i, j=0;
	
	Excel_ConfigDSN(filepath, FileName);

	if(SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv))
	{
		uc1601("failed to allocate enviroment handle",1);
	}
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if(SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDBC))
	{
		uc1601("failed to allocate connect handle",1);
	}
	rec = SQLConnect(hDBC, (SQLWCHAR*) L"MYEXCELDB01", SQL_NTS,(SQLWCHAR*)L"", SQL_NTS, (SQLWCHAR*)L"", SQL_NTS);	
	if(SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT,hDBC,&hSTMT))
	{
		uc1601("failed to allocate stmt handle",1);
	}

	sprintf(sSql, "SELECT* FROM ");
	strcat(sSql, "[");
	strcat(sSql, table_name);
	strcat(sSql, "$]");
	
	rec = SQLPrepare(hSTMT, CharToWchar(sSql), SQL_NTS);
    rec = SQLExecute(hSTMT);
    row = 1;
	j = 0;
	
	while(row < 1028)
	{   
		rec = SQLFetch(hSTMT);

		if(rec == SQL_NO_DATA){break;}			
		else if(rec == SQL_SUCCESS)
		{	//uc1601("01",1);	
			for (i=1;i<=columnum;i++)
			{
				rec = SQLGetData(hSTMT, (SQLSMALLINT)i, SQL_C_CHAR, list_data[j], STR_LEN, &Columnlen);
				
				j++;//要是这个方格没有数据,为空,那么我们的Columnlen==SQL_NULL_DATA  -1
			}	
		}
		row ++;	
	//	if (Columnlen ==SQL_NULL_DATA ) break;
		if (strstr(list_data[j-columnum],"ROW_END")!=NULL) break;
		
		
	}
	*row_num = row-1;
	
	SQLFreeHandle(SQL_HANDLE_STMT, hSTMT);
	if (hSTMT != NULL) 
	{
		hSTMT = NULL;
	}
	SQLDisconnect(hDBC);
	SQLFreeHandle(SQL_HANDLE_DBC, hDBC);
	if (hDBC != NULL) 
	{
		hDBC = NULL;
	}
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	if (hEnv != NULL) 
	{
		hEnv = NULL;
	}
		
	if(!SQLConfigDataSource(NULL,ODBC_REMOVE_DSN, L"Microsoft Excel Driver (*.xls)", 
		L"DSN=MYEXCELDB01\0\0"))
	{
		uc1601(" Failed to remove DSN",1);
	}
}*/

wchar_t* CharToWchar(const char * pchar)
{
	wchar_t *m_pWchar = NULL;

	int outlen = MultiByteToWideChar(CP_ACP,0,pchar,-1,NULL,0);
	m_pWchar = new wchar_t[outlen];
	MultiByteToWideChar(CP_ACP,0,pchar,-1,m_pWchar,outlen);

	return m_pWchar;
}

char* WCHARTOCHAR(const wchar_t * pchar)
{
	char *m_pchar = NULL;

	int iSize = WideCharToMultiByte(CP_ACP,0,pchar,-1,NULL,0,NULL,NULL);
	//m_pchar = new CHAR[outlen];
	m_pchar = (char*)malloc((iSize+1)/**sizeof(char)*/);
	WideCharToMultiByte(CP_ACP, 0, pchar, -1, m_pchar, iSize, NULL, NULL);

	return m_pchar;
}

static bool sort_as(NXString &a, NXString &b)
{
	int ia = atoi(a.GetLocaleText());
	int ib = atoi(b.GetLocaleText());

	if(ia >= ib)
	    return false;
	else
		return true;
}

void SortNXStrings(vNXString &strs)
{
	std::sort(strs.begin(), strs.end(), sort_as);
}

int TYCOM_set_obj_attr( tag_t obj_tag, const char* title, const char *name_str )
{
	int err;
	UF_ATTR_value_t value;
	if( UF_ASSEM_is_occurrence( obj_tag ))
	{
		obj_tag = UF_ASSEM_ask_prototype_of_occ ( obj_tag ) ;
    }
	value.type = UF_ATTR_string;
	value.value.string = (char*)name_str;
	err = UF_ATTR_assign( obj_tag, (char*)title, value );
	return err;
}

wchar_t * UTF8ToUnicode(const char* str)  
{  
    int textlen;  
    wchar_t * result;  
    textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);  
    result = (wchar_t *)malloc((textlen + 1)*sizeof(wchar_t));  
    memset(result, 0, (textlen + 1)*sizeof(wchar_t));  
    MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);  
    return result;  
}
char * UnicodeToANSI(const wchar_t* str)  
{  
    char* result;  
    int textlen;  
    textlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);  
    result = (char *)malloc((textlen + 1)*sizeof(char));  
    memset(result, 0, sizeof(char) * (textlen + 1));  
    WideCharToMultiByte(CP_ACP, 0, str, -1, result, textlen, NULL, NULL);  
    return result;  
}

char* UTF8ToANSI(const char* str)  
{  
    wchar_t * buf = UTF8ToUnicode(str);  
    char * ret = UnicodeToANSI(buf);  
    free(buf);  
    return ret;  
} 

int EF_eval_exp(const char *express_input , double *value ) 
{
	int error = 0 ;
	char *pp ;
	char left_side[133] ;
    char *express ;
	*value = 0 ;
	if( express_input == NULL || express_input[0] == 0  )
		return 0 ;

	express = (char *)malloc(strlen(express_input) + 1) ;
	strcpy( express , express_input) ;

	pp = strstr( express , "=" ) ;
	if( pp == NULL )
	{
		strcpy( left_side , express ) ;
	}
	else
	{
	    strcpy( left_side , pp+1 ) ;
    }
	/*  处理有说明的情况 //*/
	pp = strstr( left_side , "//") ;
	if( pp )
		*pp = 0 ;
	*value = atof( left_side ) ;
	free( express ) ;
	return 1 ;
}

int ROY_dissect_exp_string(const char *express_input , NXString &leftstr, NXString &rightstr)
{
	char *pp = NULL;
	char *express = (char *)malloc(strlen(express_input) + 1) ;
	strcpy( express , express_input) ;
	pp = strstr( express, "=" );
	if( pp != NULL )
	{
		rightstr = NXString(pp+1);
		*pp = '\0';
		leftstr= NXString(express);
	}
	free( express ) ;
	return 0;
}

void TYCOM_create_STD_attributes(tag_t std_tag, vNXString names, vNXString values)
{
	int nn = names.size();
	int nv = values.size();//UF_MODL_eval_exp(  ) ;
	if( nn != nv )
		return;
	for( int idx = 0; idx < nn; ++idx )
	{
		double exp_value = 0.0 ;
		char *pp1 = NULL , *pp2 = NULL;
		char specs_format[133]="", specs_before[133]="",specs_after[133]="",specs_exp[133]="";
		sprintf(specs_format,"%s",values[idx].GetText());
		for(;;)
		{
			strcpy( specs_before , specs_format ) ;
			pp1 = strstr( specs_before , "<" ) ;
			if( pp1 == NULL )
				break ;
			strcpy( specs_exp , pp1+1 ) ;
			*pp1 = 0 ;
			pp2 = strstr( specs_exp , ">" ) ;
			if( pp2 == NULL )
			{
				break ;
			}
			if( pp2+1 != 0 )
				strcpy( specs_after , pp2+1 ) ;
			else
				specs_after[0] = 0 ;
			*pp2 = 0;
			UF_MODL_eval_exp( specs_exp , &exp_value ) ;
			sprintf( specs_format , "%s%g%s",specs_before,exp_value,specs_after);
		}
		TYCOM_set_obj_attr(std_tag, names[idx].GetText(), specs_format);
	}
}
static int EF_SLIDE_isdigit( char *string )
{
   char *p;
   int flag = 0;
   for(p=string; *p != '\0'; p++)
   {
      if ( !isdigit(*p) && *p !=  '.')
         return 1;
      else if (*p == '.')
         flag++;
   }
   if (flag > 1)
      return 1;
   return 0;
}
static int EF_remove_space( char *string )
{
    char *p;
    int ilen;
    for( p=string;(*p);p++)
   {
       if ((*p) !=  ' ' )  break;
    }
    ilen = strlen( p );
    while( ilen > 0 )
   {
       if ((*(p+ilen-1)) == ' ' )
         ilen--;
       else
         break;
    }
    *(p+ilen)= '\0';
    strcpy( string , p );
    return TRUE;
}

static int EF_isnum_exp( char *string )
{
   char string1[255];
   char *pp;
   if (EF_SLIDE_isdigit(string))
      return 1;
    strcpy( string1 , string );
    pp = strstr(string1, "//");
   if (pp != NULL)
    {
      *pp = 0;
    }
   EF_remove_space( string1 );
   if ( EF_SLIDE_isdigit( string1) )
      return TRUE;
   
   return FALSE;
} 

static void print_error_msg(char msg[])
{
	logical open = FALSE;

	UF_UI_is_listing_window_open(&open);
	if (!open)
	{
		UF_UI_open_listing_window();
		UF_UI_write_listing_window("参数化驱动出错，以下输入表达式不能驱动模型：\n");
	}
	UF_UI_write_listing_window(msg);
	UF_UI_write_listing_window("\n");
}
int TYCOM_STD_parametrize_part(vNXString all_express, tag_t part_tag)
{
    int i;
	char exp_name[1024], exp_value[1024], *pp;
	logical update_flag = FALSE, have_exp, success = TRUE;
	double cur_value;
	UF_UNDO_mark_id_t mark_id;

	UF_UNDO_set_mark(UF_UNDO_invisible, NULL, &mark_id);
	int nitems = all_express.size();
	for( i = 0; i < nitems; i++)
	{
		exp_value[0] = 0;
		char* curexp = (char*)all_express[i].GetText();
		strcpy(exp_name, curexp);
		pp = strstr(exp_name, "=" );
		if(pp)
		{
			strcpy(exp_value, pp+1);
			*pp = '\0' ;
		}
		if(exp_value[0] == 0)// || !USER_isnum_exp(exp_value))
			continue;
		UF_MODL_is_exp_in_part(part_tag, exp_name, &have_exp);
		if(have_exp)
		{
			double right_value;

			UF_MODL_eval_exp(exp_name, &cur_value);
			if (EF_isnum_exp(exp_value))
			{
				EF_eval_exp(exp_value, &right_value);
				if(fabs(cur_value - right_value) >0.0001)
				{
					update_flag = TRUE;
					if(UF_MODL_edit_exp(curexp))
					{
						print_error_msg(curexp);
						success = FALSE;
					}
				}
			}
			else
			{
				update_flag = TRUE;
				if (UF_MODL_edit_exp(curexp))
				{
					print_error_msg(curexp);
					success = FALSE;
				}
			}
		}
	}
    try
    {
        UF_MODL_update();
    }
    catch(exception& ex)
    {
    }
	/*if(update_flag)
		UF_MODL_update();
	if (!success)
		UF_UNDO_undo_to_mark(mark_id, NULL);
	else
		UF_UNDO_delete_mark(mark_id, NULL);*/
	return TRUE;
}
extern void PrintErrorMessage( int errorCode )
{
	char message[133];
    if ( 0 != errorCode )
    {
        UF_get_fail_message( errorCode, message );
        UF_UI_set_status( message );
		uc1601 ( message, 1 );
    }
}

int TYCOM_GetVecFromTwoPnts(NXOpen::Point3d pnt0, NXOpen::Point3d pnt1, double vec[3])
{
	double dis = TYCOM_GetPointDistance(pnt0, pnt1);
	if(dis < 0.1)
		return -1;
	vec[0] = pnt1.X - pnt0.X;
	vec[1] = pnt1.Y - pnt0.Y;
	vec[2] = pnt1.Z - pnt0.Z;
	return 0;
}

int TYCOM_MirrorPoint_Plane(double pnt[3], double planeOri[3], double planeNormal[3], double outPnt[3])
{
	double mtx[16] = {0.0};
	UF_MTX4_mirror(planeOri,planeNormal,mtx );
	UF_MTX4_vec3_multiply(pnt,mtx,outPnt);
	return 0;
}

int TYCOM_MirrorPoint_Plane(NXOpen::Point3d pnt, NXOpen::Point3d planeOri, NXOpen::Vector3d planeNormal, NXOpen::Point3d &outPnt)
{
	double pnt1[3] = {pnt.X,pnt.Y,pnt.Z};
	double planeOri1[3] = {planeOri.X,planeOri.Y,planeOri.Z};
	double planeNormal1[3] = {planeNormal.X,planeNormal.Y,planeNormal.Z};

	double outPnt1[3] = {0};
	TYCOM_MirrorPoint_Plane(pnt1, planeOri1, planeNormal1, outPnt1);
	outPnt.X = outPnt1[0];
	outPnt.Y = outPnt1[1];
	outPnt.Z=  outPnt1[2];
	return 0;
}

int TYCOM_MirrorPoint_Point(double pnt[3], double Ori[3], double outPnt[3])
{
	outPnt[0] = Ori[0] + (Ori[0] - pnt[0]);
	outPnt[1] = Ori[1] + (Ori[1] - pnt[1]);
	outPnt[2] = Ori[2] + (Ori[2] - pnt[2]);
	return 0;
}

int TYCOM_MirrorPoint_Point(NXOpen::Point3d pnt, NXOpen::Point3d Ori, NXOpen::Point3d &outPnt)
{
	outPnt.X = Ori.X + (Ori.X - pnt.X);
	outPnt.Y = Ori.Y + (Ori.Y - pnt.Y);
	outPnt.Z = Ori.Z + (Ori.Z - pnt.Z);
	return 0;
}

int TYCOM_TXT_SplitToStrs(char *instr, char* key, char **strs, int &numStr)
{
	if (strlen(instr) == 0) return 0;
	numStr = 0;
	char *copyInStr = (char *)malloc(strlen(instr) + 1);
	strcpy(copyInStr,instr);
	char *p = strtok(copyInStr,key);//第一次调用,传要处理的串参数地址s 
	while(p != NULL)
	{
		strcpy(strs[numStr++],p);
		p = strtok(NULL,key);
	}
	free(copyInStr);
	return 0;
}

void TYCOM_getFilesInDirectory( string path, vector<string>& files )  
{  
    //文件句柄  
    long   hFile   =   0;  
    //文件信息  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
            //如果是目录,迭代之  
            //如果不是,加入列表  
            if((fileinfo.attrib &  _A_SUBDIR))  
            {  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                    TYCOM_getFilesInDirectory( p.assign(path).append("\\").append(fileinfo.name), files );  
            }  
            else  
            {  
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  
        _findclose(hFile);  
    }  
}

int TYCOM_GetNewFileName(char *orinalFileName, char newFileName[256])
{
    if (orinalFileName == NULL || strstr(orinalFileName, ".prt") == 0)
		return -1;

	char temp[256] = "";
	strcpy(temp,orinalFileName);
	int len = strlen(orinalFileName);
	temp[len-4] = '\0';


	int i = 0;
	while(++i)
	{
		sprintf(newFileName, "%s_%d.prt",temp,i);
		int status = 0;
		UF_CFI_ask_file_exist(newFileName,&status);
		if (status == 1)
		    break;
		//uc4567(file_name,dwgfile,UF_CFI_COPY_ALWAYS_REPLACE,-1,-1);
	}

	return 0;
}