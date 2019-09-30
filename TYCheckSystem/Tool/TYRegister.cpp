//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\TYCheckSystem\install\application\TYRegister.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 19:21 (Format: hh-mm)
//
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "TYRegister.hpp"
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYRegister::theSession) = NULL;
UI *(TYRegister::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYRegister *theTYRegister;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYRegister::TYRegister()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYRegister::theSession = NXOpen::Session::GetSession();
		TYRegister::theUI = UI::GetUI();
		theDialogName = "TYRegister.dlx";
		theDialog = TYRegister::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYRegister::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYRegister::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYRegister::update_cb));
		theDialog->AddCancelHandler(make_callback(this, &TYRegister::cancel_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYRegister::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYRegister::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYRegister::dialogShown_cb));
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
TYRegister::~TYRegister()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}


void  TYRegister::Show_TYRegister()
{
	try
	{
		theTYRegister = new TYRegister();
		// The following method shows the dialog immediately
		theTYRegister->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYRegister::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYRegister;
}



int TYRegister::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYRegister::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

void TYRegister::initialize_cb()
{
	try
	{
		groupSelect = theDialog->TopBlock()->FindBlock("groupSelect");
		stringZhuCeMa = theDialog->TopBlock()->FindBlock("stringZhuCeMa");
		stringXuLieHao = theDialog->TopBlock()->FindBlock("stringXuLieHao");
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYRegister::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYRegister::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYRegister::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYRegister::apply_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYRegister::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYRegister::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
	try
	{
		if(block == stringZhuCeMa)
		{
			//---------Enter your code here-----------
		}
		else if(block == stringXuLieHao)
		{
			//---------Enter your code here-----------
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYRegister::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYRegister::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYRegister::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: cancel_Cb
//------------------------------------------------------------------------------
int TYRegister::cancel_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYRegister::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYRegister::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}