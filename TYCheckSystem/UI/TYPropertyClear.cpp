//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYPropertyClear.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 18:57 (Format: hh-mm)
//
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "TYPropertyClear.hpp"
#include <uf_attr.h>
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYPropertyClear::theSession) = NULL;
UI *(TYPropertyClear::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYPropertyClear *theTYPropertyClear;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYPropertyClear::TYPropertyClear()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYPropertyClear::theSession = NXOpen::Session::GetSession();
		TYPropertyClear::theUI = UI::GetUI();
		theDialogName = "TYPropertyClear.dlx";
		theDialog = TYPropertyClear::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYPropertyClear::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYPropertyClear::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYPropertyClear::update_cb));
		theDialog->AddCancelHandler(make_callback(this, &TYPropertyClear::cancel_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYPropertyClear::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYPropertyClear::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYPropertyClear::dialogShown_cb));
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
TYPropertyClear::~TYPropertyClear()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}

int TYPropertyClear::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPropertyClear::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
void TYPropertyClear::Show_TYPropertyClear()
{
	try
	{
		theTYPropertyClear = new TYPropertyClear();
		// The following method shows the dialog immediately
		theTYPropertyClear->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPropertyClear::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYPropertyClear;
}

//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYPropertyClear::initialize_cb()
{
	try
	{
		groupSelect = theDialog->TopBlock()->FindBlock("groupSelect");
		selectionBodies = theDialog->TopBlock()->FindBlock("selectionBodies");
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPropertyClear::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYPropertyClear::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPropertyClear::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYPropertyClear::apply_cb()
{
	try
	{
		NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
		//bodies
		pAttr = selectionBodies->GetProperties();
		std::vector<NXOpen::TaggedObject *> objsBodies = pAttr->GetTaggedObjectVector("SelectedObjects");

		for(int i = 0; i < objsBodies.size(); i++)
		{
			UF_ATTR_delete_all( objsBodies[i]->Tag() , UF_ATTR_any );
		}
		delete pAttr;
		pAttr = 0;
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPropertyClear::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYPropertyClear::update_cb(NXOpen::BlockStyler::UIBlock* block)
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
		TYPropertyClear::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYPropertyClear::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPropertyClear::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: cancel_Cb
//------------------------------------------------------------------------------
int TYPropertyClear::cancel_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPropertyClear::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYPropertyClear::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}
