//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\TYCheckSystem\install\application\TYAutoDraft.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 10-16-2019  (Format: mm-dd-yyyy)
//              Time: 16:33 (Format: hh-mm)
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
#include "TYAutoDraft.hpp"
#include "../Common/TY_Def.h"
#include "../Common/Com_UI.h"
#include <uf_part.h>
#include "../Common/Com_UG.h"
#include "../Common/Com.h"
#include "../Common/Com_Attribute.h"
#include "../Common/Com_WT.h"
#include "../Common/Com_Draft2.h"

using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYAutoDraft::theSession) = NULL;
UI *(TYAutoDraft::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYAutoDraft *theTYAutoDraft;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYAutoDraft::TYAutoDraft()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYAutoDraft::theSession = NXOpen::Session::GetSession();
		TYAutoDraft::theUI = UI::GetUI();
		theDialogName = "TYAutoDraft.dlx";
		theDialog = TYAutoDraft::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYAutoDraft::apply_cb));
		theDialog->AddCancelHandler(make_callback(this, &TYAutoDraft::cancel_cb));
		theDialog->AddOkHandler(make_callback(this, &TYAutoDraft::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYAutoDraft::update_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYAutoDraft::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYAutoDraft::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYAutoDraft::dialogShown_cb));
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
TYAutoDraft::~TYAutoDraft()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}



int TYAutoDraft::Show()
{
	try
	{
		//这个是如何将对话框只不显示apply的好办法
		theDialog->Show(BlockDialog::DialogModeEdit);
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYAutoDraft::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

void  TY_UI_AutoDraft(vtag_t &allBodies, NXString &drawer)
{
	try
	{
		theTYAutoDraft = new TYAutoDraft();
		// The following method shows the dialog immediately
		theTYAutoDraft->Show();

		allBodies = theTYAutoDraft->m_allBodies;
		drawer = theTYAutoDraft->m_drawer;
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYAutoDraft::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYAutoDraft;
}

//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYAutoDraft::initialize_cb()
{
	try
	{
		group0 = theDialog->TopBlock()->FindBlock("group0");
		selectionBodies = theDialog->TopBlock()->FindBlock("selectionBodies");
		toggleAll = theDialog->TopBlock()->FindBlock("toggleAll");
		stringDrawer = theDialog->TopBlock()->FindBlock("stringDrawer");

	

		 NXOpen::BlockStyler::CompositeBlock * comblocks = theDialog->TopBlock();
		NXOpen::BlockStyler::UIBlock *  aply = comblocks->FindBlock("Apply");
		aply = comblocks->FindBlock("apply");
		std::vector<NXOpen::BlockStyler::UIBlock *> allblks = comblocks->GetBlocks();


		UI_SetSeletSolidBody(selectionBodies);

	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYAutoDraft::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYAutoDraft::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
		UI_LogicalSetValue(toggleAll, true);
		UI_SetShow(selectionBodies,false);
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYAutoDraft::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYAutoDraft::apply_cb()
{
	try
	{
		bool exportAll = false;
		UI_LogicalGetValue(toggleAll, exportAll);


		vtag_t allBodies;
		if (exportAll)
		{
			//第二步得到所有的实体并创建引用集
			//注意威唐只要出小于150层的实体
			vtag_t partBodies;
			TYCOM_GetCurrentPartSolidBodies(partBodies);
			int layer = 0;
			for (int i = 0; i < partBodies.size(); i++)
			{
				layer = TYCOM_GetObjectLayer(partBodies[i]);
				if (layer < 150)
				{
					allBodies.push_back(partBodies[i]);
				}
			}
		}
		else
		{
            allBodies = UI_GetSelectObjects2(selectionBodies);
		}
			
		if(allBodies.size() == 0)
		{
			uc1601("没有选择实体对象",1);
			return 0;
		}
		TYCOM_SortBodiesByPropertyIndex(allBodies);

		m_allBodies = allBodies;
    

		//NXString drawer;
		UI_StringGetValue(stringDrawer,m_drawer);
		if (m_drawer.getLocaleText() == 0 || strlen(m_drawer.getLocaleText()) < 1)
		{
			uc1601("请输入绘图人员名称",1);
			return 0;
		}
		
		//theSession->DeleteAllUndoMarks();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYAutoDraft::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYAutoDraft::update_cb(NXOpen::BlockStyler::UIBlock* block)
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
		else if(block == stringDrawer)
		{
			//---------Enter your code here-----------
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYAutoDraft::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYAutoDraft::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYAutoDraft::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

int TYAutoDraft::cancel_cb()
{
	m_allBodies.clear();
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYAutoDraft::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}
