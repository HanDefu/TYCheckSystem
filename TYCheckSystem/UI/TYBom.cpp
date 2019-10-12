//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Projects\WeiTang\Src\TYCheckSystem\install\application\TYBom.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 10-08-2019  (Format: mm-dd-yyyy)
//              Time: 15:19 (Format: hh-mm)
//
//==============================================================================

//==============================================================================
//  Purpose:  This TEMPLATE file contains C++ source to guide you in the
//  construction of your Block application dialog. The generation of your
//  dialog file (.dlx extension) is the first step towards dialog construction
//  within NX.  You must now create a NX Open application that
//  utilizes this file (.dlx).
//
//  The information in this file provides you with the following:
//
//  1.  Help on how to load and display your Block Styler dialog in NX
//      using APIs provided in NXOpen.BlockStyler namespace
//  2.  The empty callback methods (stubs) associated with your dialog items
//      have also been placed in this file. These empty methods have been
//      created simply to start you along with your coding requirements.
//      The method name, argument list and possible return values have already
//      been provided for you.
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "TYBom.hpp"
#include "../Common/TY_Def.h"
#include "../Common/Com_UI.h"
#include <uf_part.h>
#include "../Common/Com_UG.h"
#include "../Tool/Excel/BasicExcel.hpp"
#include "../Common/Com.h"
#include "../TYBomData.h"
#include "../Common/Com_Attribute.h"
#include "../Common/Com_WT.h"

using namespace YExcel;


using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYBom::theSession) = NULL;
UI *(TYBom::theUI) = NULL;

int TY_WT_Bom(vtag_t bodies, NXString srcName, NXString xlsFilePathName);

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYBom *theTYBom;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYBom::TYBom()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYBom::theSession = NXOpen::Session::GetSession();
		TYBom::theUI = UI::GetUI();
		theDialogName = "TYBom.dlx";
		theDialog = TYBom::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYBom::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYBom::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYBom::update_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYBom::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYBom::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYBom::dialogShown_cb));
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		throw;
	}
}

//------------------------------------------------------------------------------
// Destructor for NX Styler class
//------------------------------------------------------------------------------
TYBom::~TYBom()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}



int TYBom::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYBom::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}


//------------------------------------------------------------------------------
//Method name: Show_TYBom
//------------------------------------------------------------------------------
void TYBom::Show_TYBom()
{
	try
	{
		theTYBom = new TYBom();
		// The following method shows the dialog immediately
		theTYBom->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYBom::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYBom;
}


//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYBom::initialize_cb()
{
	try
	{
		group0 = theDialog->TopBlock()->FindBlock("group0");
		selectionBodies = theDialog->TopBlock()->FindBlock("selectionBodies");
		toggleAll = theDialog->TopBlock()->FindBlock("toggleAll");
		group = theDialog->TopBlock()->FindBlock("group");
		stringPathName = theDialog->TopBlock()->FindBlock("stringPathName");
		buttonSelect = theDialog->TopBlock()->FindBlock("buttonSelect");
		stringNO = theDialog->TopBlock()->FindBlock("stringNO");

		UI_LogicalSetValue(toggleAll, true);
		UI_SetShow(selectionBodies,false);

		char filePath[MAX_FSPEC_SIZE] = "";
		char namestr[MAX_FSPEC_SIZE] = "";
		char part_fspec1[MAX_FSPEC_SIZE] = "";
		tag_t disp = UF_PART_ask_display_part();
		UF_PART_ask_part_name(disp,part_fspec1);
		uc4578(part_fspec1, 2, filePath);
		strcat(filePath, "_BOM.xls");
		UI_StringSetValue(stringPathName,filePath);
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYBom::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYBom::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYBom::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}


int GetPartNameFirstType(NXString str)
{
	if (str.getLocaleText() == NULL || strlen(str.getLocaleText()) == 0)
		return 11;

    if (strcmp(str.getLocaleText(),"检测类") == 0)
		return 1;

	if (strcmp(str.getLocaleText(),"支架类") == 0)
		return 2;

	if (strcmp(str.getLocaleText(),"轴套类") == 0)
		return 3;

	if (strcmp(str.getLocaleText(),"定位类") == 0)
		return 4;

	if (strcmp(str.getLocaleText(),"夹紧类") == 0)
		return 5;

	if (strcmp(str.getLocaleText(),"标准件") == 0)
		return 101;

	return 11;
}


static logical CompareBody(tag_t &body1, tag_t &body2)
{
	NXString body1Type, body2Type;
    TYCOM_GetObjectStringAttribute( body1 , ATTR_TYCOM_PROPERTY_SOLID_NAME , body1Type);
	TYCOM_GetObjectStringAttribute( body2 , ATTR_TYCOM_PROPERTY_SOLID_NAME , body2Type);

    int itype1 = GetPartNameFirstType(body1Type);
	int itype2 = GetPartNameFirstType(body2Type);

    return itype1 < itype2;
}

static int SortBomBodiesByType(vtag_t &bomBodies)
{
	std::sort(bomBodies.begin(),bomBodies.end(),CompareBody);   
	return 0;
}


static logical CompareBodyByPropertyIndex(tag_t &body1, tag_t &body2)
{
	int indexProperty1 = 0, indexProperty2 = 0;
	int ret1 = EF_ask_obj_integer_attr( body1 , ATTR_TYCOM_PROPERTY_INDEX , &indexProperty1 );
	int ret2 = EF_ask_obj_integer_attr( body2 , ATTR_TYCOM_PROPERTY_INDEX , &indexProperty2 );
	if (ret1 == 0 && ret2 == 0)
		return indexProperty1 < indexProperty2;

	if (ret1 == 0 && ret2 != 0)
		return true;

	if (ret1 != 0 && ret2 == 0)
		return false;

	return false;
}

static int SortBodiesByPropertyIndex(vtag_t &bomBodies)
{
	std::sort(bomBodies.begin(),bomBodies.end(),CompareBodyByPropertyIndex);   
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYBom::apply_cb()
{
	try
	{
		//---- Enter your callback code here -----
		bool exportAll = false;
		UI_LogicalGetValue(toggleAll, exportAll);

		vtag_t bomBodies;
		if (exportAll)
			TYCOM_GetCurrentPartSolidBodies(bomBodies);
		else
			bomBodies = UI_GetSelectObjects2(selectionBodies);

		if(bomBodies.size() == 0)
		{
			uc1601("没有选择实体对象",1);
			return 0;
		}

		SortBodiesByPropertyIndex(bomBodies);
		//SortBomBodiesByType(bomBodies);


		NXString xlsFilePathName;
		UI_StringGetValue(stringPathName, xlsFilePathName);
		int exist = 0;
		UF_CFI_ask_file_exist(xlsFilePathName.getLocaleText(),&exist);
		if (exist == 0)
		{
			vNXString options;
			options.push_back("覆盖");
			options.push_back("不覆盖");
			int ret = TYCOM_OptionDialog("Excel文件已经存在，是否覆盖?", options);
			if (ret == 1)
				return 0;
		}

		//检查模板文件
		char *p_env = getenv("UGII_USER_DIR");
		char srcspc[MAX_FSPEC_SIZE]="";
		char desspc[MAX_FSPEC_SIZE]="";
		sprintf_s(srcspc,"%s\\templates\\BOMTemplate.xls",p_env);
		UF_CFI_ask_file_exist(srcspc,&exist);
		if( 0 != exist )
		{
			uc1601("没有找到BOM模板文件",1);
			return 0;
		}


		//拷贝文件
		/*uc4567( srcspc,xlsFilePathName.getLocaleText(),UF_CFI_COPY_ALWAYS_REPLACE,0,0);
		UF_CFI_ask_file_exist(xlsFilePathName.getLocaleText(),&exist);
		if (exist == 1)
		{
			uc1601("拷贝BOM模板文件失败",1);
			return 0;
		}*/

		NXString str;
		UI_StringGetValue(stringNO, str);
		TYBomData::SetProjectNo(str);
		TY_WT_Bom(bomBodies, srcspc, xlsFilePathName);


		char filePath[MAX_FSPEC_SIZE] = "";
		char namestr[MAX_FSPEC_SIZE] = "";
		uc4576(xlsFilePathName.GetLocaleText(), 2, filePath, namestr);
		char cmd[512]="";
		sprintf_s(cmd,"start %s",filePath);
		system(cmd);    
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYBom::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYBom::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
	try
	{
		if(block == selectionBodies)
		{
			//---------Enter your code here-----------
		}
		else if(block == toggleAll)
		{
			//---------Enter your code here-----------
			bool exportAll = false;
			UI_LogicalGetValue(toggleAll, exportAll);
			if (exportAll)
			    UI_SetShow(selectionBodies,false);
			else
                UI_SetShow(selectionBodies,true);
		}
		else if(block == buttonSelect)
		{

			tag_t work_part;
			char sPromptStr[]="Bom输出文件选择对话框";
			char sTitleStr[]="指定Bom输出文件存放位置";
			char sFilterStr[256]="*.xls";
			char sDefaultStr[256]="";
			char sFilePath[_MAX_PATH]="";
			int iResponse = 0;
			char file_name[256]="";
			char fname[_MAX_FNAME];
			//LPTSTR lpBuffer =  NULL;
			//LPTSTR lpFilePart;
			work_part = UF_PART_ask_display_part();
			UF_PART_ask_part_name (work_part, file_name );
			uc4576 (file_name, 2, sFilterStr, fname );
			uc4578(fname, 2, fname);
			strcpy(sDefaultStr, fname);
			strcat(sDefaultStr, "_BOM.xls");

			NXString str;
			UI_StringGetValue(stringPathName,str);
			strcpy(sDefaultStr,str.getLocaleText());
			

			strcat(sFilterStr,".xls");
			UF_UI_create_filebox (sPromptStr, sTitleStr, sFilterStr, 
				sDefaultStr,sFilePath, &iResponse );
			if(iResponse==UF_UI_OK)
			{
                UI_StringSetValue(stringPathName,sFilePath);
			}
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYBom::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYBom::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYBom::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYBom::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}

int TY_BOM_WriteOneBody(BasicExcelWorksheet* sheet, int rowIndex, int index, tag_t body)
{
	TYBomData bomData(body);

	BasicExcelCell *cel = 0;

	char str[128] = "";

	//第一列 NUM
	cel = sheet->Cell(rowIndex,0);
	sprintf(str, "%d", index);//第几个
	cel->Set(str);

	//第一列 DETAIL
	if (index < 10)
		sprintf(str, "00%d", index);//第几个
	else if(index < 100)
		sprintf(str, "0%d", index);//第几个
	else
		sprintf(str, "%d", index);//第几个

	cel = sheet->Cell(rowIndex,1);
	NXString nxstr = bomData.m_projectNo + NXString("-") + NXString(str);
	cel->Set(nxstr.getLocaleText());
	TYCOM_SetObjectStringAttribute( body, TY_ATTR_DRAWING_NO, nxstr.getLocaleText());


	//第三列:MAT_L
	cel = sheet->Cell(rowIndex,2);
	if (bomData.m_material.getLocaleText() != 0 && strlen(bomData.m_material.getLocaleText()) > 0)
	    cel->SetWString(CharToWchar(bomData.m_material.getLocaleText()));


	//第四列:DIA_THK
	cel = sheet->Cell(rowIndex,3);
	cel->Set(bomData.m_size.getLocaleText());


	//第五列:QTY
	cel = sheet->Cell(rowIndex,4);
	cel->Set("1");


	//第六列:DESCRIPTION
	cel = sheet->Cell(rowIndex,5);
	if (bomData.m_firstName.getLocaleText() != 0 && strlen(bomData.m_firstName.getLocaleText()) > 0)
	{
		nxstr = bomData.m_firstName + NXString("-") + bomData.m_secondName;
	    cel->SetWString(CharToWchar(nxstr.getLocaleText()));
	}


	//第七列:ADD_DESCRIP
	cel = sheet->Cell(rowIndex,6);
	cel->Set("prt");


	//第八列:HEAT TREAT
	cel = sheet->Cell(rowIndex,7);
	if (bomData.m_heatProcess.getLocaleText() != 0 && strlen(bomData.m_heatProcess.getLocaleText()) > 0)
	cel->SetWString(CharToWchar(bomData.m_heatProcess.getLocaleText()));

	return 0;
}

int TY_WT_Bom(vtag_t bodies, NXString srcName, NXString xlsFilePathName)
{
	int startRow = 3;

	//客户处理
	BasicExcel excel;
	bool isOk = excel.Load(srcName.getLocaleText(),BasicExcel::WRITE);	
	if (!isOk)
	{
		uc1601("加载数据文件失败，请检测",1);
		return -1;
	}

	BasicExcelWorksheet* sheet1 = excel.GetWorksheet(L"总表");
	if (sheet1)
	{
	
		for (int i = 0; i < bodies.size(); i++)
		{
			TY_BOM_WriteOneBody(sheet1, startRow + i, i+1, bodies[i]);
		}
	}

	excel.SaveAs(xlsFilePathName.getLocaleText());

	
    return 0;
}