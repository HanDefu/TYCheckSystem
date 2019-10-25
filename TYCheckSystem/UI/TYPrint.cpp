//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYPrint.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 18:56 (Format: hh-mm)
//
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "TYPrint.hpp"
#include <uf.h>
#include "../Common/Com_UI.h"
#include "../Common/Com_UG.h"
#include <math.h>
#include <uf_draw.h>
#include <uf_plot.h>
#include "../ConfigData/TYGlobalData.h"
#include <uf_part.h>
#include <uf_assem.h>
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYPrint::theSession) = NULL;
UI *(TYPrint::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYPrint *theTYPrint;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYPrint::TYPrint()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYPrint::theSession = NXOpen::Session::GetSession();
		TYPrint::theUI = UI::GetUI();
		theDialogName = "TYPrint.dlx";
		theDialog = TYPrint::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYPrint::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYPrint::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYPrint::update_cb));
		theDialog->AddCancelHandler(make_callback(this, &TYPrint::cancel_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYPrint::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYPrint::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYPrint::dialogShown_cb));
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
TYPrint::~TYPrint()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}

int TYPrint::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPrint::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

void TYPrint::Show_TYPrint()
{
	try
	{
		theTYPrint = new TYPrint();
		// The following method shows the dialog immediately
		theTYPrint->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPrint::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYPrint;
}


//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYPrint::initialize_cb()
{
	try
	{
		groupPrinter = theDialog->TopBlock()->FindBlock("groupPrinter");
		enumPrinter = theDialog->TopBlock()->FindBlock("enumPrinter");
		togglePrintAll = theDialog->TopBlock()->FindBlock("toggleOnlyCurrent");
		labelInfo = theDialog->TopBlock()->FindBlock("labelInfo");

		printers.clear();
		int num = 0;
		printers = TYGBDATA->m_printers;

		if(printers.size() > 0)
		{
			UI_EnumSetValues(enumPrinter,printers);
			UI_EnumSetCurrentSel(enumPrinter, 0);
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPrint::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYPrint::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
		UI_LogicalSetValue(togglePrintAll,true);
		UI_SetShow(labelInfo,true);

		tag_p_t drawing_tags;
		int num_drawings = 0;
		UF_DRAW_ask_drawings( &num_drawings, &drawing_tags);
		char info[128] = "";
		sprintf(info, "共有%d张图纸即将打印",num_drawings);
		UI_BlockSetLabel(labelInfo, NXString(info));
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPrint::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

NXOpen::PrintBuilder::PaperSize GetPaperSize(double hei, double wid)
{
	if(fabs(hei - 297) < 1 && fabs(wid - 420) < 1)
		return NXOpen::PrintBuilder::PaperSizeA3;

	if(fabs(hei - 297) < 1 && fabs(wid - 210) < 1)
		return NXOpen::PrintBuilder::PaperSizeA4Rotated;

	if(fabs(hei - 210) < 1 && fabs(wid - 297) < 1)
		return NXOpen::PrintBuilder::PaperSizeA4;

	return NXOpen::PrintBuilder::PaperSizeA4;
}

int ChangeReferenceSet(tag_t drawTag)
{
	char name[64] = "";
    UF_OBJ_ask_name(drawTag, name);

	tag_t *child_part_occs = 0;
	tag_t disp = UF_PART_ask_display_part();
	tag_t rootocc = UF_ASSEM_ask_root_part_occ(disp);
	int n = UF_ASSEM_ask_part_occ_children(rootocc, &child_part_occs);
	int ret = 0;
	if (n > 0)
	{
		ret = UF_ASSEM_replace_refset(1,&child_part_occs[0],name);
	}
	return 0;
}
//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYPrint::apply_cb()
{
	try
	{
		int sel = 0;
		UI_EnumGetCurrentSel(enumPrinter, sel);

		char printername[256] = "";
		strcpy(printername,printers[sel].getLocaleText());


		bool printAll = false;
		UI_LogicalGetValue(togglePrintAll, printAll);

		tag_p_t drawing_tags;
		tag_t currentDraw = 0;
		int num_drawings = 0;

		if(!printAll)
		{
			UF_DRAW_ask_current_drawing(&currentDraw);
			if(currentDraw != NULL_TAG)
			{
				drawing_tags = &currentDraw;
				num_drawings = 1;
			}
		}
		else
			UF_DRAW_ask_drawings( &num_drawings, &drawing_tags);

		bool showWid = TYCOM_DraftingPreferences_GetShowLineWidth();
		if(!showWid)
			TYCOM_DraftingPreferences_SetShowLineWidth(true);

		for(int i = 0; i < num_drawings; i++)
		{
			UF_DRAW_info_t info;
			UF_DRAW_ask_drawing_info(drawing_tags[i], &info);
			NXOpen::PrintBuilder::PaperSize ps = GetPaperSize(info.size.custom_size[0], info.size.custom_size[1]);

			NXOpen::PrintBuilder::OrientationOption orientation = NXOpen::PrintBuilder::OrientationOptionLandscape;
			if(ps == NXOpen::PrintBuilder::PaperSizeA4Rotated)
				orientation = NXOpen::PrintBuilder::OrientationOptionPortrait;

			//CF_SetPrintPDFName("test1");
			ChangeReferenceSet(drawing_tags[i]);

			TYCOM_Plot_Single(drawing_tags[i],
				ps,
				orientation,
				printername);
		}
		if(!showWid)
			TYCOM_DraftingPreferences_SetShowLineWidth(false);
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPrint::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYPrint::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
	try
	{
		if(block == enumPrinter)
		{
			//---------Enter your code here-----------
		}
		else if(block == togglePrintAll)
		{
			//---------Enter your code here-----------
			bool printAll = false;
			UI_LogicalGetValue(togglePrintAll,printAll);
			UI_SetShow(labelInfo,printAll);
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPrint::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYPrint::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPrint::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: cancel_Cb
//------------------------------------------------------------------------------
int TYPrint::cancel_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYPrint::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYPrint::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}
