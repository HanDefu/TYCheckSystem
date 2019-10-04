#include "StandardPartData.h"
#include "../Tool/Excel/BasicExcel.hpp"
#include <uf_clone.h>
#include "../Common/Com_UG.h"
#include <uf_assem.h>
#include <uf_so.h>
#include <uf_wave.h>

static int isInit = false;

using namespace YExcel;
StandardPartData::StandardPartData()
{
	currentclass1idx = -1;
	currentclass2idx = -1;
	currentclass3idx = -1;
	specialParamIndex = 0;
	isInit = false;
}

StandardPartData::~StandardPartData()
{
}
StlNXStringVector StandardPartData::GetStandardSearchDataName()
{
    StlNXStringVector names;
    for(int idx = 0;idx < standardSearchData.size(); ++idx )
    {
        names.push_back(standardSearchData[idx].StdName);
    }
    return names;
}
void StandardPartData::GetStandardSearchDataIndex( int idx, int* idx1,int* idx2, int* idx3 )
{
    *idx1 = standardSearchData[idx].idx1;
    *idx2 = standardSearchData[idx].idx2;
    *idx3 = standardSearchData[idx].idx3;
}
void StandardPartData::InitalData( const char* rootDir, const char *mainRegFile )
{
	BasicExcel excel;
	standardRoot = NXString(rootDir);
	char file_name[TY_STR_LEN] = "";
	strcpy(file_name, rootDir);
	strcat(file_name,mainRegFile);
	specialParamIndex = 0;
	isInit = true;
    standardSearchData.clear();
	Load_Level_1_Data(file_name);
    int num = m1_1_firstClassTypes.size();
    for( int idx = 0; idx < num; ++idx )
    {
        Load_Level_2_Data(idx);
        for(int jdx = 0; jdx < m2_1_secondClassTypes.size(); ++jdx )
        {
            for( int kdx = 0; kdx < m2_2_thirdClassNames[jdx].size(); ++kdx )
            {
                standardName temp;
                temp.idx1 = idx;
                temp.idx2 = jdx;
                temp.idx3 = kdx;
                temp.StdName = m1_1_firstClassTypes[idx]+"-"+m2_1_secondClassTypes[jdx]+"-"+m2_2_thirdClassNames[jdx].at(kdx);
                standardSearchData.push_back(temp);
            }
        }
    }
	Load_Level_2_Data(0);
	Load_Level_3_Data(0,0);
	m_lastUIExpressions.clear();
}

void StandardPartData::RefreshData(int class1idx,int class2idx, int class3idx)
{
	if( class1idx!= currentclass1idx || class2idx!= currentclass2idx || class3idx!= currentclass3idx)
	{
		Load_Level_2_Data(class1idx);
		Load_Level_3_Data(class2idx,class3idx);
	}
	if( m_lastUIExpressions.size() > 0 )
		m_lastUIExpressions.clear();
}

int StandardPartData::Load_Level_1_Data( const char* regFileFullName )
{
	int irc = 1;
	BasicExcel excel;
	bool isOk = excel.Load(regFileFullName);
	if( isOk )
	{
		BasicExcelWorksheet* sheet1 = excel.GetWorksheet(L"标准件分类");
		if (sheet1)
		{
			m1_1_firstClassTypes.clear();
			m1_2_firstClassRegFiles.clear();
			size_t maxRows = sheet1->GetTotalRows();
			for(int i = 1; i < maxRows; i++)
			{
				BasicExcelCell *cel = sheet1->Cell(i,0);
				NXString name = cel->Get();
				if (strlen(name.GetLocaleText()) == 0)
					break;

				m1_1_firstClassTypes.push_back(name);
				BasicExcelCell *cel2 = sheet1->Cell(i,1);
				NXString regpath(cel2->Get().c_str());
				m1_2_firstClassRegFiles.push_back(standardRoot+regpath);
			}
			irc = 0;
		}
	}
	return irc;
}

// 
int StandardPartData::Load_Level_2_Data( int idx )
{
	int irc = 1;
	BasicExcel excel;
	if( currentclass1idx == idx )
		return 0;
	m2_1_secondClassTypes.clear();   
	m2_2_thirdClassNames.clear(); 
	m2_3_thirdClassDataFiles.clear(); 
	m2_4_thirdClassModelFiles.clear();     
	m2_5_thirdClassBitmapFiles.clear();    
	m2_6_thirdClassIsParameterized.clear();
	m2_7_thirdClassIsToPocket.clear();     

	if(idx >= m1_2_firstClassRegFiles.size() )
		idx = 0;
	currentclass1idx = idx;
	currentclass2idx = -1; //force to refresh level 3 data
	currentclass3idx = -1;
	bool isOk = excel.Load(m1_2_firstClassRegFiles[idx].GetText());	
	char cFilePath[256] = "";
	char cFileName[64] = "";
	uc4576(m1_2_firstClassRegFiles[idx].GetText(), 2, cFilePath, cFileName);

	if( isOk )
	{
		int numSheet = excel.GetTotalWorkSheets();
		for( int idx = 0; idx < numSheet; ++idx )
		{
			const wchar_t* sheetName = excel.GetUnicodeSheetName(idx);
			m2_1_secondClassTypes.push_back(WCHARTOCHAR(sheetName));
			BasicExcelWorksheet* sheet1 = excel.GetWorksheet(sheetName);
			StlNXStringVector sheetclassNames;
			StlNXStringVector sheetclassDatas;
			StlNXStringVector sheetclassModels;
			StlNXStringVector sheetclassBitmaps;
			StlLogicalVector  sheetclassIsPram;
			StlLogicalVector  sheetclassIsPock;
			if (sheet1)
			{
				irc = 0;
				size_t maxRows = sheet1->GetTotalRows();
				for(int i = 1; i < maxRows; i++)
				{
					BasicExcelCell *cel = sheet1->Cell(i,0);
					std::string name = cel->Get();
					if (name.length() == 0)
						break;

					sheetclassNames.push_back(name);

					BasicExcelCell *cel2 = sheet1->Cell(i,1);
					std::string regpath = cel2->Get();

					BasicExcelCell *celFolder = sheet1->Cell(i,6);
					std::string folderName = celFolder->Get();

					
					sheetclassDatas.push_back(NXString(cFilePath) + NXString("\\") + NXString(folderName.c_str())+ NXString("\\") + NXString(regpath.c_str()));

					BasicExcelCell *cel3 = sheet1->Cell(i,2);
					std::string modelpath = cel3->Get();
					sheetclassModels.push_back(NXString(cFilePath) + NXString("\\") + NXString(folderName.c_str())+ NXString("\\") +NXString(modelpath.c_str()));

					BasicExcelCell *cel4 = sheet1->Cell(i,3);
					std::string bitmappath = cel4->Get();
					sheetclassBitmaps.push_back(NXString(cFilePath) + NXString("\\") + NXString(folderName.c_str())+ NXString("\\")+NXString(bitmappath.c_str()));

					BasicExcelCell *cel5 = sheet1->Cell(i,4);
					std::string isParam = cel5->Get();
					if( 0 == isParam.compare("是") || 0 == isParam.compare("Yes") )
						sheetclassIsPram.push_back(true);
					else
						sheetclassIsPram.push_back(false);

					BasicExcelCell *cel6 = sheet1->Cell(i,5);
					std::string isPock = cel6->Get();
					if( 0 == isPock.compare("是") || 0 == isPock.compare("Yes"))
						sheetclassIsPock.push_back(true);
					else
						sheetclassIsPock.push_back(false);
				}
			}
			m2_2_thirdClassNames.push_back(sheetclassNames);
			m2_3_thirdClassDataFiles.push_back(sheetclassDatas);
			m2_4_thirdClassModelFiles.push_back(sheetclassModels);
			m2_5_thirdClassBitmapFiles.push_back(sheetclassBitmaps);
			m2_6_thirdClassIsParameterized.push_back(sheetclassIsPram);
			m2_7_thirdClassIsToPocket.push_back(sheetclassIsPock);
		}
	}
	return irc;
}

int StandardPartData::Load_Level_3_Data( int idx2, int idx3  )
{
	int irc = 0;
	if( currentclass2idx == idx2 && currentclass3idx == idx3 )
		return 0;
	m3_1_currentExpName.clear();
	m3_2_currentExpValues.clear();
	m3_3_currentExpCanInput.clear();
	m3_4_currentExpBitmaps.clear();
	m3_5_currentAssoAttrName.clear();
	m3_6_currentAssoAttrValue.clear();
	m3_7_currentExpRename.clear();
	if( idx2 >= m2_3_thirdClassDataFiles.size() )
		idx2 = 0;
	if( idx3 >= m2_3_thirdClassDataFiles[idx2].size() )
		idx3 = 0;
	currentclass2idx = idx2;
	currentclass3idx = idx3;
	NXString expDataFile = m2_3_thirdClassDataFiles[idx2].at(idx3);
	BasicExcel excel;
	bool isOk = excel.Load(expDataFile.GetText());	

	char cFilePath[256] = "";
	char cFileName[64] = "";
	uc4576(expDataFile.GetText(), 2, cFilePath, cFileName);

	if( isOk )
	{
		BasicExcelWorksheet* sheet1 = excel.GetWorksheet(L"参数");
		if (sheet1)
		{
			size_t maxRows = sheet1->GetTotalRows();
			size_t maxCols = sheet1->GetTotalCols();
			BasicExcelCell *celflag = sheet1->Cell(1,0);
			std::string isPock = celflag->Get();
			if( 0 == isPock.compare("数值"))
			{
				isSpecialParamsTable = true;
				for(int i = 1; i < maxCols; i++)
				{
					BasicExcelCell *cel = sheet1->Cell(0,i);
					std::string expName = cel->Get();
					m3_1_currentExpName.push_back(expName);
				}
				for( int j = 1; j < maxCols; j++ )
				{
					StlNXStringVector valuevec;
					for(int i = 1; i < maxRows-SPECPARAMETER_OTHER_LINES; i++)
					{
						BasicExcelCell *cel = sheet1->Cell(i,j);
						std::string celValue = cel->Get();
						valuevec.push_back(celValue);
					}
					m3_2_currentExpValues.push_back(valuevec);
				}
				for(int i = 1; i < maxCols; i++)
				{
					BasicExcelCell *cel = sheet1->Cell(maxRows-SPECPARAMETER_OTHER_LINES,i);
					std::string isPock = cel->Get();
					if( 0 == isPock.compare("是") || 0 == isPock.compare("Yes"))
						m3_3_currentExpCanInput.push_back(true);
					else
						m3_3_currentExpCanInput.push_back(false);
				}
				for(int i = 1; i < maxCols; i++)
				{
					BasicExcelCell *cel = sheet1->Cell(maxRows-SPECPARAMETER_OTHER_LINES+1,i);
					std::string bmpPath = cel->Get();
					if( 0 != bmpPath.compare("无") && 0 != bmpPath.compare(""))
						m3_4_currentExpBitmaps.push_back(NXString(cFilePath) + NXString("\\") + NXString(bmpPath));
					else
						m3_4_currentExpBitmaps.push_back("");
				}
				for(int i = 1; i < maxCols; i++)
				{
					BasicExcelCell *cel = sheet1->Cell(maxRows-SPECPARAMETER_OTHER_LINES+2,i);
					std::string isRename = cel->Get();
					if( 0 == isRename.compare("是") || 0 == isRename.compare("Yes"))
						m3_7_currentExpRename.push_back(true);
					else
						m3_7_currentExpRename.push_back(false);
				}
			}
			else
			{
				isSpecialParamsTable = false;
				for(int i = 1; i < maxRows; i++)
				{
					BasicExcelCell *cel = sheet1->Cell(i,0);
					std::string expName = cel->Get();
					m3_1_currentExpName.push_back(expName);
					BasicExcelCell *cel2 = sheet1->Cell(i,1);
					std::string values = cel2->Get();
					char *pstring=NULL;
					StlNXStringVector valuevec;
					pstring=strtok((char*)values.c_str(),",");
					while(pstring)
					{
						valuevec.push_back(pstring);
						pstring=strtok(NULL,",");
					}
					m3_2_currentExpValues.push_back(valuevec);

					BasicExcelCell *cel6 = sheet1->Cell(i,2);
					std::string isPock = cel6->Get();
					if( 0 == isPock.compare("是") || 0 == isPock.compare("Yes"))
						m3_3_currentExpCanInput.push_back(true);
					else
						m3_3_currentExpCanInput.push_back(false);
					BasicExcelCell *cel3 = sheet1->Cell(i,3);
					std::string bmpPath = cel3->Get();
					m3_4_currentExpBitmaps.push_back(NXString(cFilePath) + NXString("\\") +NXString(bmpPath));
				}
			}


			BasicExcelWorksheet* sheet2 = excel.GetWorksheet("属性");
			if (sheet2)
			{
				size_t maxRows = sheet2->GetTotalRows();
				for(int i = 1; i < maxRows; i++)
				{
					BasicExcelCell *cel = sheet2->Cell(i,0);
					std::string expName = cel->Get();
					m3_5_currentAssoAttrName.push_back(expName.c_str());
					BasicExcelCell *cel2 = sheet2->Cell(i,1);
					std::string values = cel2->Get();
					m3_6_currentAssoAttrValue.push_back(NXString(values.c_str()));
				}
			}	
		}
	}
	return 0;
}

StlNXStringVectorVector StandardPartData::GetCurrentExpValues(  )
{
	//RefreshData(class1idx,class2idx,class3idx);
	int num = m3_2_currentExpValues.size();
	if(isSpecialParamsTable && num > 0 )
	{
		StlNXStringVectorVector currentSpecialExpValues;
		currentSpecialExpValues.push_back(m3_2_currentExpValues[0]);
		StlNXStringVector selValues;
		for( int idx = 1; idx < num; ++idx )
		{
			NXString temp = m3_2_currentExpValues[idx].at(specialParamIndex);
			selValues.push_back(temp);
		}
		for( int idx = 0; idx < selValues.size(); ++idx )
		{
			char *pstring=NULL;
			StlNXStringVector valuevec;
			pstring=strtok((char*)selValues[idx].GetText(),",");
			while(pstring)
			{
				valuevec.push_back(pstring);
				pstring=strtok(NULL,",");
			}
			currentSpecialExpValues.push_back(valuevec);
		}
		return currentSpecialExpValues;
	}
	else
		return m3_2_currentExpValues;
}


StlNXStringVector StandardPartData::GetFirstClassNames( )
{
	return m1_1_firstClassTypes;
}
StlNXStringVector StandardPartData::GetSecondClassNames( )
{
	return m2_1_secondClassTypes;
}
StlNXStringVector StandardPartData::GetThirdClassNames( )
{
	return m2_2_thirdClassNames[currentclass2idx];
}

NXString StandardPartData::GetCurrentStdPartModel( )
{
	return m2_4_thirdClassModelFiles[currentclass2idx].at(currentclass3idx);
}

NXString StandardPartData::GetCurrentStdPartBitmap( )
{
	return m2_5_thirdClassBitmapFiles[currentclass2idx].at(currentclass3idx);
}

logical StandardPartData::GetCurrentStdPartIsPara(  )
{
	return m2_6_thirdClassIsParameterized[currentclass2idx].at(currentclass3idx);
}

logical StandardPartData::GetCurrentStdPartIsPock( )
{
	return m2_7_thirdClassIsToPocket[currentclass2idx].at(currentclass3idx);
}

StlNXStringVector StandardPartData::GetCurrentExpNames(  )
{
	return m3_1_currentExpName;
}

StlLogicalVector StandardPartData::GetCurrentExpCanInput(  )
{
	return m3_3_currentExpCanInput;
}

StlLogicalVector StandardPartData::GetCurrentExpRename(  )
{
	return m3_7_currentExpRename;
}

logical StandardPartData::GetIsSpecialParamsTable()
{
	return isSpecialParamsTable;
}
void StandardPartData::SetSpecialParamIndex( int idx )
{
	specialParamIndex = idx;
}
int StandardPartData::GetSpecialParamIndex( )
{
	return specialParamIndex;
}

logical StandardPartData::GetIsInit()
{
	return isInit;
}
int StandardPartData::GetClass1Index()
{
	return currentclass1idx;
}
int StandardPartData::GetClass2Index()
{
	return currentclass2idx;
}
int StandardPartData::GetClass3Index()
{
	return currentclass3idx;
}
void StandardPartData::SetLastUIExpressions(StlNXStringVector& exps)
{
	m_lastUIExpressions = exps;
}
StlNXStringVector StandardPartData::GetLastUIExpressions()
{
	return m_lastUIExpressions;
}
StlNXStringVector StandardPartData::GetAssoAttrNames()
{
	return m3_5_currentAssoAttrName;
}
StlNXStringVector StandardPartData::GetAssoAttrValues()
{
	return m3_6_currentAssoAttrValue;
}
NXString StandardPartData::GetCurrentStdClassName()
{
	return m1_1_firstClassTypes[currentclass1idx]+"-"+m2_1_secondClassTypes[currentclass2idx]+"-"+m2_2_thirdClassNames[currentclass2idx].at(currentclass3idx);
}

////////////---------------------------------------//

extern int XINGTAI_ASSY_clone(char templateName[MAX_FSPEC_SIZE], char nameRule[MAX_FSPEC_SIZE],char path_str[MAX_FSPEC_SIZE], char new_part_name[MAX_FSPEC_SIZE])
{
    int err;
    UF_CLONE_operation_class_t operation_class=UF_CLONE_clone_operation ; 
    UF_CLONE_action_t default_action=UF_CLONE_clone;  
    UF_PART_load_status_t load_status; 
    UF_CLONE_name_rule_def_t namerule; 
    UF_CLONE_naming_failures_t naming_failures; 
    UF_CLONE_naming_technique_t naming_technique;
    err = UF_CLONE_initialise(operation_class); 
    err = UF_CLONE_init_naming_failures(&naming_failures); 
    if(UF_CLONE_add_assembly ( templateName, & load_status )) 
		return 1;
    UF_free_string_array(load_status.n_parts,load_status.file_names);
    UF_free(load_status.statuses);

    err = UF_CLONE_set_def_action(default_action); 
    err = UF_CLONE_set_def_directory(path_str);  
    naming_technique= UF_CLONE_naming_rule;
    err = UF_CLONE_set_def_naming(naming_technique);
    namerule.type=UF_CLONE_prepend_string; 
    namerule.new_string=nameRule; 

	/*uc4576(templateName, 2, path_str, new_part_name);

	namerule.type = UF_CLONE_replace_string;
    namerule.base_string = new_part_name;
    namerule.new_string  = nameRule;*/

    err = UF_CLONE_set_name_rule(&namerule,&naming_failures); 
	NXFUN_ASSY_clone_set_no_log();
    err = UF_CLONE_perform_clone(&naming_failures); 
    if(naming_failures.n_failures >0) 
    {
        UF_free_string_array(naming_failures.n_failures,naming_failures.input_names);
        UF_free_string_array(naming_failures.n_failures,naming_failures.output_names);
        UF_free(naming_failures.statuses);
    }
    //else
    //{
    //    PrintErrorMessage(err);
    //}
    UF_CLONE_terminate();   

    //UF_PART_load_status_t   error_status;
    strcpy(new_part_name,path_str);
    strcat(new_part_name,"\\");    
    strcat(new_part_name, nameRule);
    /*UF_PART_open_quiet( new_part_name, newPart, &error_status );
    UF_free_string_array( error_status.n_parts, error_status.file_names );
    UF_free( error_status.statuses );*/
    return 0;
}
void build_temp_filespec(char *fspec, int ftype, char *new_spec)
{
    char *tmp_dir;

    UF_translate_variable("UGII_TMP_DIR", &tmp_dir);
	uc4575(tmp_dir, ftype, fspec, new_spec);
}

int StandardPartClonePart(const char *source_part, char *output_part)
{
	int irc = 0;
    /*UF_CLONE_naming_failures_t  name_failures;
    char output_path[UF_CFI_MAX_PATH_NAME_SIZE], output_name[UF_CFI_MAX_FILE_NAME_SIZE];

    irc = uc4576(output_part, 2, output_path, output_name);

    irc = UF_CLONE_initialise(UF_CLONE_clone_operation);

    int err = UF_CLONE_add_part(source_part);
	err = UF_CLONE_init_naming_failures(&name_failures);
    if ( err != 0)
    {
        char msg[133];
        UF_get_fail_message( err, msg );
        return -1;
    }

    err = UF_CLONE_set_def_action(UF_CLONE_clone);
    if (UF_CLONE_set_def_directory(output_path) != 0)
        return -2;
	char clone_log[MAX_FSPEC_SIZE+1]="";
	build_temp_filespec("Clone_Existing_Import", 47, clone_log);
	UF_CLONE_set_logfile(clone_log);

    err = UF_CLONE_set_naming(source_part, UF_CLONE_user_name, output_part);
	err = UF_CLONE_set_dryrun(false);

    NXFUN_ASSY_clone_set_no_log();
    err = UF_CLONE_perform_clone(&name_failures);
    if (name_failures.n_failures > 0)
    {
        UF_free(name_failures.statuses);
        UF_free_string_array(name_failures.n_failures, name_failures.input_names);
        UF_free_string_array(name_failures.n_failures, name_failures.output_names);
        return -3;
    }
    err = UF_CLONE_terminate();*/
    uc4567( source_part,output_part,UF_CFI_COPY_NEVER_REPLACE,0,2);
    UF_CFI_ask_file_exist(output_part,&irc);
    return irc;
}

//int GetRegFileData( char* fileFullName, StlNXStringVector& className2, StlNXStringVectorVector& regData )
//{
//	BasicExcel excel;
//	className2.clear();
//	regData.clear();
//	bool isOk = excel.Load(fileFullName);	
//	if( isOk )
//	{
//		int numSheet = excel.GetTotalWorkSheets();
//		for( int idx = 0; idx < numSheet; ++idx )
//		{
//			const wchar_t* sheetName = excel.GetUnicodeSheetName(idx);
//			className2.push_back(WCHARTOCHAR(sheetName));
//			BasicExcelWorksheet* sheet1 = excel.GetWorksheet(sheetName);
//			StlNXStringVector sheetclassNames;
//			if (sheet1)
//			{
//				size_t maxRows = sheet1->GetTotalRows();
//				for(int i = 1; i < maxRows; i++)
//				{
//					BasicExcelCell *cel = sheet1->Cell(i,0);
//					const wchar_t* name = cel->GetWString();
//					sheetclassNames.push_back(NXString(WCHARTOCHAR(name)));
//				}
//			}
//			regData.push_back(sheetclassNames);
//		}
//	}
//	return regData.size();
//}

int ConvertStr(char *pstr)
{
    int len = strlen(pstr);
    for(int i = 0; i < len; i++)
    {
        if( pstr[i] >= 'a' && pstr[i] <= 'z')
             pstr[i] = pstr[i] - 32;
    }
    return 0;
}


logical IsContainStr( const char* strlib, const char* substr )
{
    char *p = NULL;
    StlNXStringVector strv;
    logical result = true;
    char* strp = (char *)malloc(strlen(substr) + 1) ;
    char* str = (char *)malloc(strlen(strlib) + 1) ;
    strcpy(strp,substr);
    strcpy(str,strlib);
    ConvertStr(strp);
    ConvertStr(str);
    p=strtok(strp,"*");
    while(p!=NULL)
    {
        strv.push_back(p);
        p=strtok(NULL,"*");
    }
    for( int idx = 0; idx < strv.size(); ++idx )
    {
        char* p1 = strstr(str,strv[idx].GetText());
        if( p1 == NULL )
        {
            result = false;
            break;
        }
    }
    free(strp);
    return result;
}


int pock_with_select_tool_and_target2(tag_t tool_occ,tag_t sel_target)
{
	//tag_t tool_occ;
	tag_t tool_pro,target_pro;
	tag_t from_part_occ,to_part_occ;
	tag_t ref_tag=NULL_TAG;
	tag_p_t mebers;
	int  num_mebers,i;
	char refset_name[MAX_ENTITY_NAME_SIZE+1] ;
	double origin[3] ;
	double csys_matrix[9] ;
	tag_t feat_waved=NULL_TAG,body_waved=NULL_TAG;
	tag_t workpart;
	tag_t tem_workpart;

	workpart=UF_ASSEM_ask_work_part();

	if (UF_ASSEM_is_occurrence(sel_target))
	{
		to_part_occ=UF_ASSEM_ask_part_occurrence(sel_target);
		target_pro=UF_ASSEM_ask_prototype_of_occ(sel_target);
		tem_workpart=UF_ASSEM_ask_prototype_of_occ(to_part_occ);
	}
	else
	{
		target_pro=sel_target;
		to_part_occ=NULL_TAG;
		tem_workpart=workpart;
	}

	if (UF_ASSEM_is_occurrence(tool_occ))
	{
		//tool_occ=UF_ASSEM_ask_part_occurrence(sel_tool);
		tool_pro=UF_ASSEM_ask_prototype_of_occ(tool_occ);
		from_part_occ=tool_occ;
	}


	UF_CALL(UF_OBJ_cycle_by_name_and_type(tool_pro,"FALSE",UF_reference_set_type, TRUE, &ref_tag));

	UF_CALL(UF_ASSEM_ask_ref_set_data(ref_tag,refset_name,origin,csys_matrix,&num_mebers,&mebers));

	if( workpart != tem_workpart )
		UF_CALL(UF_ASSEM_set_work_part(tem_workpart));
	for (i=0;i<num_mebers;i++)
	{
		int type,subtype,err;
		tag_t xform=NULL_TAG;
		int num_results;
		tag_t *resultbodies;
		int   result[1];

		if (UF_OBJ_ask_type_and_subtype(mebers[i],&type,&subtype)==0
			&&type==UF_solid_type&&subtype==UF_solid_body_subtype)
		{
			//UF_CALL(UF_ASSEM_set_work_part(tem_workpart));

			UF_CALL(UF_SO_create_xform_assy_ctxt(target_pro,from_part_occ,to_part_occ,&xform));

			UF_CALL(UF_WAVE_create_linked_body(mebers[i],xform,target_pro,TRUE,&feat_waved));

			UF_CALL(UF_MODL_ask_feat_body(feat_waved,&body_waved));

			//UF_CALL(UF_ASSEM_set_work_part(tem_workpart));
			UF_MODL_check_interference(target_pro,1,&body_waved,result);
			if( result[0]==1 )
			{
				err=UF_MODL_subtract_bodies(target_pro,body_waved,&num_results,&resultbodies);
				if (err)
				{
					UF_CALL(UF_OBJ_delete_object(body_waved));
				}
				UF_free(resultbodies);
			}
			else
			{
				UF_CALL(UF_OBJ_delete_object(body_waved));
			}
		}
	}
	UF_free(mebers);
	if( workpart != tem_workpart )
		UF_CALL(UF_ASSEM_set_work_part(workpart));
	return 0;
}

int Royal_ask_refset_objs( char *ref_set_name , 
								 tag_t part_occ , 
								 StlTagVector& objlist )
{
	int i = 0 ,
		j = 0 ,
		err = 0 ,
		type = 0 ,
		subtype = 0 ,
		num_occ = 0 ,
		n_members = 0 ;
	tag_t ref_set = NULL_TAG , 
		part_tag = NULL_TAG ,
		* members = NULL ,
		* body_occ = NULL ;

	if( UF_ASSEM_is_occurrence( part_occ ) )
	{
		part_tag = UF_ASSEM_ask_prototype_of_occ( part_occ ) ;
	}

	err = UF_OBJ_cycle_by_name_and_type( part_tag , ref_set_name , UF_reference_set_type , true , & ref_set ) ;
	if ( err || ref_set == NULL_TAG )
		return -1;

	UF_ASSEM_ask_ref_set_members( ref_set , & n_members , & members ) ;
	for( i = 0 ; i < n_members ; i ++ )
	{
		err = UF_OBJ_ask_type_and_subtype( members[ i ] , & type , & subtype ) ;
		if ( err == 0 && type == UF_solid_type && subtype == UF_solid_body_subtype &&
			UF_OBJ_ALIVE == UF_OBJ_ask_status( members[ i ] ) )
		{
			num_occ = UF_ASSEM_ask_occs_of_entity( members[ i ] , & body_occ ) ;
			for( j = 0 ; j < num_occ ; j ++ )
			{
				if( part_occ == UF_ASSEM_ask_part_occurrence( body_occ[ j ] ) )
				{
					objlist.push_back(body_occ[ j ]);
				}
			}
			if( body_occ != NULL )
			{
				UF_free( body_occ ) ;
				body_occ = NULL ;
			}           
		}
	}
	UF_free( members ) ;
	return objlist.size() ;
}

int Royal_standard_pocket(tag_t tool_occ, StlTagVector target_list,StlTagVector target_force)
{
	tag_t  target = NULL_TAG;
	int   result[1];
	StlTagVector  true_objs;
	int num_true = Royal_ask_refset_objs("TRUE",tool_occ,true_objs);
	for (int i=0;i<target_list.size();i++)
	{
		int idx = -1;
		logical intersect = false;
		target = target_list[i];
		if(target_force.size()>0)
		{
			idx = vFind(target_force,target);
		}
		if( idx > -1 )
		{
			intersect = true;
		}
		else
		{
			for (int j=0;j<num_true;j++)
			{
				UF_MODL_check_interference(target,1,&true_objs[j],result);
				if (result[0]==1&&target != true_objs[j])
				{
					intersect = true;
					break;
				}
			}
		}
		if( intersect )
			UF_CALL(pock_with_select_tool_and_target2(tool_occ,target));
	}
	return 0;
}

//void Royal_set_obj_attr( tag_t obj_tag, const char* title, const char *name_str )
//{
//	int err;
//	UF_ATTR_value_t value;
//	if( UF_ASSEM_is_occurrence( obj_tag ))
//	{
//		obj_tag = UF_ASSEM_ask_prototype_of_occ ( obj_tag ) ;
//    }
//	value.type = UF_ATTR_string;
//	value.value.string = (char*)name_str;
//	err = UF_ATTR_assign( obj_tag, (char*)title, value );
//}

