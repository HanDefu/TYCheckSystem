//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Projects\WeiTang\Src\TYCheckSystem\Install\application\TYSameBody.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 06-07-2020  (Format: mm-dd-yyyy)
//              Time: 15:31 (Format: hh-mm)
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
#include "TYSameBody.hpp"
#include "../Common/Com_UI.h"
#include "../Common/Com_UG.h"
#include "../Common/Com_Attribute.h"
#include <math.h>
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYSameBody::theSession) = NULL;
UI *(TYSameBody::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYSameBody *theTYSameBody;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYSameBody::TYSameBody()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYSameBody::theSession = NXOpen::Session::GetSession();
		TYSameBody::theUI = UI::GetUI();
		theDialogName = "TYSameBody.dlx";
		theDialog = TYSameBody::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYSameBody::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYSameBody::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYSameBody::update_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYSameBody::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYSameBody::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYSameBody::dialogShown_cb));
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
TYSameBody::~TYSameBody()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}


int TYSameBody::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYSameBody::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}


//------------------------------------------------------------------------------
//Method name: Show_TYSameBody
//------------------------------------------------------------------------------
void TYSameBody::Show_TYSameBody()
{
	try
	{
		theTYSameBody = new TYSameBody();
		// The following method shows the dialog immediately
		theTYSameBody->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYSameBody::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYSameBody;
}


//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYSameBody::initialize_cb()
{
	try
	{
		group0 = theDialog->TopBlock()->FindBlock("group0");
		selectionSameBody = theDialog->TopBlock()->FindBlock("selectionSameBody");
		toggleFroceSame = theDialog->TopBlock()->FindBlock("toggleFroceSame");

		UI_SetSeletSolidBody(selectionSameBody);
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYSameBody::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYSameBody::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYSameBody::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}


bool AreBodiesSameVolume(vtag_t &bodies)
{
	if(bodies.size() < 2)
		return true;

	double volume0 = TYCOM_GetBodyVolume(bodies[0]);
	for(int i = 1; i < bodies.size(); i++)
	{
		double volume = TYCOM_GetBodyVolume(bodies[i]);
		if(fabs(volume - volume0) > 0.000001)
			return false;
	}
	return true;
}

int ProcessSameBody(std::vector<tag_t> &sameBodies, bool checkVolume)
{
	char attriValue[128] = "";
	int has = 0;

	if( sameBodies.size() == 1)
	{
		uc1601("相同件只有一个零件",1);
		return 1;
	}


	if(checkVolume && !AreBodiesSameVolume(sameBodies))
	{
		uc1601("零件体积不一样，请检查",1);
		return 1;
	}



	//UF_MODL_ask_mass_props_3d();

	char* guid = newGUID();

	//首先查找是否有的零件已经有属性了
	for(int i = 0; i < sameBodies.size(); i++)
	{

		has = TYCOM_GetObjectStringAttribute( sameBodies[i] , ATTR_TY_SAME_BODY , attriValue );
		if(has)
		{
			break;
		}
	}

	for(int i = 0; i < sameBodies.size(); i++)
	{
		if(has)
		{
			TYCOM_SetObjectStringAttribute( sameBodies[i], ATTR_TY_SAME_BODY, attriValue );
		}
		else
		{
			TYCOM_SetObjectStringAttribute( sameBodies[i], ATTR_TY_SAME_BODY, guid );
		}
	}
}


//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYSameBody::apply_cb()
{
	try
	{
		std::vector<tag_t> sameBodies = UI_GetSelectObjects2(selectionSameBody);

		bool checkVolume = false;
		UI_LogicalGetValue(toggleFroceSame,checkVolume);
		ProcessSameBody(sameBodies,!checkVolume);
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYSameBody::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYSameBody::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
	try
	{
		if(block == selectionSameBody)
		{
			//---------Enter your code here-----------
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYSameBody::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYSameBody::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYSameBody::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYSameBody::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}
