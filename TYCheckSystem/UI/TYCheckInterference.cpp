//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYCheckInterference.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 18:55 (Format: hh-mm)
//
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "TYCheckInterference.hpp"
#include "../Common/Com_UI.h"
#include "../Common/TY_Def.h"
#include <uf_disp.h>
#include <uf_modl.h>
#include "../Common/Com.h"
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYCheckInterference::theSession) = NULL;
UI *(TYCheckInterference::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYCheckInterference *theTYCheckInterference;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYCheckInterference::TYCheckInterference()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYCheckInterference::theSession = NXOpen::Session::GetSession();
		TYCheckInterference::theUI = UI::GetUI();
		theDialogName = "TYCheckInterference.dlx";
		theDialog = TYCheckInterference::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYCheckInterference::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYCheckInterference::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYCheckInterference::update_cb));
		theDialog->AddCancelHandler(make_callback(this, &TYCheckInterference::cancel_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYCheckInterference::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYCheckInterference::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYCheckInterference::dialogShown_cb));
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
TYCheckInterference::~TYCheckInterference()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}

int TYCheckInterference::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYCheckInterference::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

void TYCheckInterference::Show_TYCheckInterference()
{
	try
	{
		theTYCheckInterference = new TYCheckInterference();
		// The following method shows the dialog immediately
		theTYCheckInterference->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYCheckInterference::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYCheckInterference;
}


//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYCheckInterference::initialize_cb()
{
	try
	{
		groupSelectBodies = theDialog->TopBlock()->FindBlock("groupSelectBodies");
		selectionBodies = theDialog->TopBlock()->FindBlock("selectionBodies");

		UI_SetSeletSolidBody(selectionBodies);

		for(int i = 0; i < m_intsectBodies.size(); i++)
		{
			UF_DISP_set_highlight(m_intsectBodies[i],1);
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYCheckInterference::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYCheckInterference::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
		
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYCheckInterference::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYCheckInterference::apply_cb()
{
	try
	{
		m_intsectBodies.clear();

		std::vector<NXOpen::TaggedObject *> pbodies = UI_GetSelectObjects(selectionBodies);
		vtag_t bodies;
		for(int i = 0; i < pbodies.size(); i++)
			bodies.push_back(pbodies[i]->Tag()); 

		int ret = 0;
		for(int i = 0; i < bodies.size(); i++)
		{
			for(int j = i+1; j < bodies.size(); j++)
            {
                ret = vFind(m_intsectBodies,bodies[i]);
				if (ret < 0)
				{
					m_intsectBodies.push_back(bodies[i]);
				}

				ret = vFind(m_intsectBodies,bodies[j]);
				if (ret < 0)
				{
					m_intsectBodies.push_back(bodies[j]);
				}
            }

		}

        logical response = 0;
		UF_UI_is_listing_window_open(&response);
		if(!response)
		    UF_UI_open_listing_window();
		
		char str[1024]="";
        if( m_intsectBodies.size() > 0 )
		    sprintf(str, "共选择%d个检测实体\n其中%d处存在干涉,系统已经高亮显示\n",bodies.size(),m_intsectBodies.size());
        else
            sprintf(str, "共选择%d个检测实体\n没有发现干涉\n",bodies.size());
		UF_UI_write_listing_window(str);

        cancel_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYCheckInterference::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYCheckInterference::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
	try
	{
		if(block == selectionBodies)
		{
			//---------Enter your code here-----------
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYCheckInterference::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYCheckInterference::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYCheckInterference::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: cancel_Cb
//------------------------------------------------------------------------------
int TYCheckInterference::cancel_cb()
{
	try
	{
		
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYCheckInterference::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYCheckInterference::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}
