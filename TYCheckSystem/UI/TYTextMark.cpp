//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYTextMark.cpp
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
#include "TYTextMark.hpp"
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYTextMark::theSession) = NULL;
UI *(TYTextMark::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYTextMark *theTYTextMark;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYTextMark::TYTextMark()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYTextMark::theSession = NXOpen::Session::GetSession();
		TYTextMark::theUI = UI::GetUI();
		theDialogName = "TYTextMark.dlx";
		theDialog = TYTextMark::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYTextMark::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYTextMark::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYTextMark::update_cb));
		theDialog->AddCancelHandler(make_callback(this, &TYTextMark::cancel_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYTextMark::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYTextMark::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYTextMark::dialogShown_cb));
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
TYTextMark::~TYTextMark()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}



int TYTextMark::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYTextMark::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}


//------------------------------------------------------------------------------
//Method name: Show_TYTextMark
//------------------------------------------------------------------------------
void TYTextMark::Show_TYTextMark()
{
	try
	{
		theTYTextMark = new TYTextMark();
		// The following method shows the dialog immediately
		theTYTextMark->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYTextMark::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYTextMark;
}

//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYTextMark::initialize_cb()
{
	try
	{
		groupText = theDialog->TopBlock()->FindBlock("groupText");
		enumPrinter = theDialog->TopBlock()->FindBlock("enumPrinter");
		toggleOnlyCurrent = theDialog->TopBlock()->FindBlock("toggleOnlyCurrent");
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYTextMark::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYTextMark::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYTextMark::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYTextMark::apply_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYTextMark::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYTextMark::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
	try
	{
		if(block == enumPrinter)
		{
			//---------Enter your code here-----------
		}
		else if(block == toggleOnlyCurrent)
		{
			//---------Enter your code here-----------
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYTextMark::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYTextMark::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYTextMark::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: cancel_Cb
//------------------------------------------------------------------------------
int TYTextMark::cancel_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYTextMark::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYTextMark::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}
