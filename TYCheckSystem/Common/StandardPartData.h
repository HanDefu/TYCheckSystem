#ifndef STANDARD_PART_DATA_H_INCLUDED
#define STANDARD_PART_DATA_H_INCLUDED

#include <uf_defs.h>
#include <vector>
#include <uf.h>
#include <NXOpen/NXString.hxx>
#include "Com.h"
#include "TY_Def.h"

using namespace std;
using namespace NXOpen;

#define SPECPARAMETER_OTHER_LINES 3


struct standardName
{
    int idx1;
    int idx2;
    int idx3;
    NXString StdName;
};

typedef std::vector <standardName> StandardSearchData;


class StandardPartData
{
public:
	StandardPartData();
	~StandardPartData();
	void InitalData( const char* rootDir, const char *mainRegFile );
	void RefreshData(int class1idx=0,int class2idx=0, int class3idx=0, bool forceRefresh = false);
	StlNXStringVectorVector GetCurrentExpValues( );

	StlNXStringVector GetFirstClassNames( );
	StlNXStringVector GetSecondClassNames( );
	StlNXStringVector GetThirdClassNames( );
	NXString GetCurrentStdPartModel( );
	NXString GetCurrentStdPartBitmap( );
	logical GetCurrentStdPartIsPara(  );
	logical GetCurrentStdPartIsPock( );
	StlNXStringVector GetCurrentExpNames(  );
	StlLogicalVector GetCurrentExpCanInput(  );
	StlLogicalVector GetCurrentExpRename(  );
	logical GetIsSpecialParamsTable();
	void SetSpecialParamIndex( int idx );
	int GetSpecialParamIndex( );
	logical GetIsInit();
	int GetClass1Index();
	int GetClass2Index();
	int GetClass3Index();
	void SetLastUIExpressions(StlNXStringVector& exps);
	StlNXStringVector GetLastUIExpressions();
	StlNXStringVector GetAssoAttrNames();
	StlNXStringVector GetAssoAttrValues();
	NXString GetCurrentStdClassName();
    StlNXStringVector GetStandardSearchDataName();
    void GetStandardSearchDataIndex( int idx, int* idx1,int* idx2, int* idx3 );
public:
    StandardSearchData standardSearchData;

private:

	int Load_Level_1_Data(const char* regFileFullName);
	int Load_Level_2_Data( int idx );
	int Load_Level_3_Data( int idx2, int idx3);
	
	NXString standardRoot;
	int currentclass1idx;
	int currentclass2idx;
	int currentclass3idx;
	logical isSpecialParamsTable;
	int specialParamIndex;
	//static int isInit;
	StlNXStringVector m_lastUIExpressions;

	// data from level 1 data file
	StlNXStringVector m1_1_firstClassTypes;    //class1 Names
	StlNXStringVector m1_2_firstClassRegFiles; //class1 register file
	// data from level 1 data file

	// data from level 2 data file
	StlNXStringVector m2_1_secondClassTypes;   //class2 Names (sheet Names)
	StlNXStringVectorVector m2_2_thirdClassNames; //class3 Names (standard part name)
	StlNXStringVectorVector m2_3_thirdClassDataFiles; // standard part expression files
	StlNXStringVectorVector m2_4_thirdClassModelFiles;     // standard part prt files
	StlNXStringVectorVector m2_5_thirdClassBitmapFiles;    // standard part main bmp files
	StlLogicalVectorVector  m2_6_thirdClassIsParameterized;// standard part parameterize flags
	StlLogicalVectorVector  m2_7_thirdClassIsToPocket;     // standard part pocket flags
	// data from level 2 data file
	
	// data from level 3 data file
	StlNXStringVector       m3_1_currentExpName;            // current standard part expression Names
	StlNXStringVectorVector m3_2_currentExpValues;          // current standard part expression Values
	StlLogicalVector        m3_3_currentExpCanInput;        // current standard part expression can input flags
	StlNXStringVector       m3_4_currentExpBitmaps;         // current standard part detail bmps related to expression

	StlLogicalVector        m3_7_currentExpRename;        // current standard part expression can input flags

	StlNXStringVector       m3_5_currentAssoAttrName;       // current standard part attribute Names
	StlNXStringVector       m3_6_currentAssoAttrValue;      // current standard part attribute Values
	// data from level 3 data file

};


extern int XINGTAI_ASSY_clone(char templateName[MAX_FSPEC_SIZE], char nameRule[MAX_FSPEC_SIZE],char path_str[MAX_FSPEC_SIZE], char new_part_name[MAX_FSPEC_SIZE]);
void build_temp_filespec(char *fspec, int ftype, char *new_spec);
int StandardPartClonePart(const char *source_part, char *output_part);
int ConvertStr(char *pstr);
logical IsContainStr( const char* strlib, const char* substr );
int Royal_standard_pocket(tag_t tool_occ, StlTagVector target_list,StlTagVector target_force);

//void Royal_set_obj_attr( tag_t obj_tag, const char* title, const char *name_str );
int Royal_ask_refset_objs( char *ref_set_name , 
						  tag_t part_occ , 
						  StlTagVector& objlist );
int pock_with_select_tool_and_target2(tag_t tool_occ,tag_t sel_target);

#endif //STANDARD_PART_DATA_H_INCLUDED