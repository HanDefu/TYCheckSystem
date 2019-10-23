//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  D:\study\Mystudy\Pipe2015_NXopen\Src\V20150818\GetPoint.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: hand
//              Version: NX 6
//              Date: 08-18-2015  (Format: mm-dd-yyyy)
//              Time: 14:56 (Format: hh-mm)
//
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "Entry.hpp"
#include <uf.h>
#include <exception>
#include "Tool\TYRegister.hpp"
#include <NXOpen\Session.hxx>
#include "Tool\Excel\BasicExcel.hpp"
#include "UI\TYBaiWeiXian.hpp"
#include "UI\TYCheckGap.hpp"
#include "UI\TYCheckInterference.hpp"
#include "UI\TYColor.hpp"
#include "UI\TYHeavy.hpp"
#include "UI\TYHole.hpp"
#include "UI\TYMirrorText.hpp"
#include "UI\TYPrint.hpp"
#include "UI\TYProperty.hpp"
#include "UI\TYPropertyClear.hpp"
#include "UI\TYStandPart.hpp"
#include "UI\TYTextMark.hpp"
#include "Tool\TYRegister.hpp"
#include "Command.h"
#include <uf_ui.h>
#include "ConfigData/TYGlobalData.h"
#include "UI\TYBom.hpp"
#include "UI\TYAutoDraft.hpp"
#include "Common/Com_Draft2.h"
#include "UI\TYExport.hpp"

using namespace NXOpen;

static bool s_regOK = false;
static bool s_isFirst = true;

static bool InitCheck();
static int InitData();

extern "C" DllExport void  ufusr(char *param, int *retcod, int param_len)
{
	try
	{
#ifndef TY_DEBUG

		TYRegister::Show_TYRegister();//注册机相关

		if(g_regOK == 0)
		{
			UF_terminate();
			return;
		}

#endif  // TYCOM_DEBUG

		if(InitCheck() == false)
			return;

		UF_initialize();

		if (s_isFirst)
		{
			InitData();
			s_isFirst = false;
		}

		if(strcmp(param, "CUSTOM_TY_ADD_PROPERTY") == 0)//添加属性
		{
			 TYProperty::Show_TYProperty();
		}

		if(strcmp(param, "CUSTOM_TY_CLEAR_PROPERTY") == 0)//清空属性
		{
			TYPropertyClear::Show_TYPropertyClear();
		}

		if(strcmp(param, "CUSTOM_TY_COLOR_TOOL") == 0)//着色
		{
			TYColor::Show_TYColor();
		}

		if(strcmp(param, "CUSTOM_TY_STAND_PART") == 0)//标准件
		{
			//TYStandPart::Show_TYStandPart();
		}

		if(strcmp(param, "CUSTOM_TY_AUTO_DRAFTING") == 0)//自动出图
		{
			//TY_CMD_AutoDrafting();
			//TYAutoDraft::Show_TYAutoDraft();
			NXString drawer;
			vtag_t allBodies;
			TY_UI_AutoDraft(allBodies,drawer);
			if (allBodies.size() > 0)
		    	TY_AutoDrafting2(allBodies,drawer);
		}

		if(strcmp(param, "CUSTOM_TY_BOM") == 0)//BOM
		{
			TYBom::Show_TYBom();
		}

		if(strcmp(param, "CUSTOM_TY_BAIKEXIAN") == 0)//百刻线
		{
			TYBaiWeiXian::Show_TYBaiWeiXian();
		}

		if(strcmp(param, "CUSTOM_TY_CHECK_XUANKONG") == 0)//悬空检测
		{
			TYCheckGap::Show_TYCheckGap();
		}

		if(strcmp(param, "CUSTOM_TY_CHECK_INTERSECT") == 0)//干涉检测
		{
			TYCheckInterference::Show_TYCheckInterference();
		}

		if(strcmp(param, "CUSTOM_TY_CREATE_HOLE") == 0)//自动引孔
		{
			TYHole::Show_TYHole();
		}

		if(strcmp(param, "CUSTOM_TY_GET_HEAVY") == 0)//称重
		{
			TYHeavy::Show_TYHeavy();
		}

		if(strcmp(param, "CUSTOM_TY_TEXT_MARK") == 0)//刻字和镜像刻字
		{
			TYTextMark::Show_TYTextMark();
		}
		if(strcmp(param, "CUSTOM_TY_PRINT") == 0)//批量打印
		{
			TYPrint::Show_TYPrint();
		}

		if(strcmp(param, "CUSTOM_TY_EXPORT_DWG") == 0)//导出dwg
		{
			TY_CMD_ExportDwg();
		}


		if(strcmp(param, "CUSTOM_TY_CREATE_STANDARDPART_PROPERTY") == 0)//标准件属性
		{
			TYProperty::Show_TYProperty(1);
		}

		if(strcmp(param, "CUSTOM_TY_EXPORT3D") == 0)//标准件属性
		{
			TYExport_Main();
		}
		 
		
	}
	catch(std::exception& ex)
	{
		//if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
		//{
		//throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
		//}

		//RYMirror::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
		//throw NXException::Create("生成失败.");
	}

}


extern "C" DllExport int ufusr_ask_unload()
{
	UF_terminate();
	//return (int)Session::LibraryUnloadOptionExplicitly;
	//return (int)NXOpen::Session::LibraryUnloadOptionImmediately;
	return (int)Session::LibraryUnloadOptionAtTermination;
}


extern "C" DllExport void ufusr_cleanup(void)
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(std::exception& ex)
	{
		//---- Enter your exception handling code here -----
	}
}

bool InitCheck()
{
	char * env = getenv("TY_DATA_DIR");
	if (env == 0)
	{
		uc1601("没有环境变量TY_DATA_DIR",1);
		return false;
	}

	env = getenv("UGII_USER_DIR");
	if (env == 0)
	{
		uc1601("没有环境变量TY_DATA_DIR",1);
		return false;
	}
	return true;
}

int InitData()
{
	TYGBDATA->Run();
	return 0;
}