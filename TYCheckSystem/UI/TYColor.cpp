//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYColor.cpp
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
#include "TYColor.hpp"
#include "../Common/Com_UI.h"
#include "../Common/Com_Attribute.h"
#include "../Common/Com_UG.h"
#include <uf_vec.h>
#include <uf_assem.h>
#include <math.h>

using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYColor::theSession) = NULL;
UI *(TYColor::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYColor *theTYColor;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYColor::TYColor()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYColor::theSession = NXOpen::Session::GetSession();
		TYColor::theUI = UI::GetUI();
		theDialogName = "TYColor.dlx";
		theDialog = TYColor::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYColor::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYColor::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYColor::update_cb));
		theDialog->AddCancelHandler(make_callback(this, &TYColor::cancel_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYColor::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYColor::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYColor::dialogShown_cb));

		//注意我们在dlx文件中设置bmp时候 系统自动读取的是ugii_user_dir的路径作为相对路径
		//系统不会自动读取当前dlx文件所在路径作为相对路径的！！
		m_curSel = 0;
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
TYColor::~TYColor()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}

int TYColor::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//Method name: Show_TYColor
//------------------------------------------------------------------------------
void TYColor::Show_TYColor()
{
	try
	{
		theTYColor = new TYColor();
		// The following method shows the dialog immediately
		theTYColor->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYColor;
}

//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYColor::initialize_cb()
{
	try
	{
		group = theDialog->TopBlock()->FindBlock("group");
		enumColor = theDialog->TopBlock()->FindBlock("enumColor");
		colorPicker = theDialog->TopBlock()->FindBlock("colorPicker");
		groupSelect = theDialog->TopBlock()->FindBlock("groupSelect");
		faceSelection = theDialog->TopBlock()->FindBlock("faceSelection");
		firstFace = theDialog->TopBlock()->FindBlock("firstFace");
		secondFace = theDialog->TopBlock()->FindBlock("secondFace");

        UI_EnumSetCurrentSel(enumColor,m_curSel);
		InitShow();
		
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYColor::dialogShown_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYColor::apply_cb()
{
	try
	{
		NXOpen::BlockStyler::PropertyList *  pAttr = NULL;

		int colorIndex = 0;
		UI_EnumGetCurrentSel(enumColor, colorIndex);
		if(colorIndex == 0)
		{
			std::vector<tag_t> objsFaces1 = UI_GetSelectObjects2(firstFace);
			std::vector<tag_t> objsFaces2 = UI_GetSelectObjects2(secondFace);


			tag_t firstFace = TYCOM_Prototype(objsFaces1[0]);
			tag_t secondFace = TYCOM_Prototype(objsFaces2[0]);

			//第二步：检测
			double normal1[3],normal2[3];
			TYCOM_FaceAskMidPointNormal(firstFace,normal1);
			TYCOM_FaceAskMidPointNormal(secondFace,normal2);

			int isp = false;
			//公差的意义
			//0.01 ->0.57 度
			//0.02 ->1.14度
			//0.03-->1.71度
			//0.04--> 2.29度
			//https://www.pianshen.com/article/9101212216/
			UF_VEC3_is_perpendicular(normal1,normal2,0.001,&isp);
			if(isp == 0)
			{
				TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, "两个基准面必须垂直");
				return 0;
			}

			tag_t faceBody1 = 0;
			UF_MODL_ask_face_body(firstFace, &faceBody1);
			tag_t faceBody2 = 0;
			UF_MODL_ask_face_body(secondFace, &faceBody2);
			if (faceBody1 != faceBody2)
			{
				TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, "两个面不属于同一个实体");
				return 0;
			}

			//清除原有的属性和颜色
			ClearOldProperty(firstFace);
			ClearOldProperty(secondFace);

			//第三步：着色
			UF_OBJ_set_color(firstFace , 21);
			UF_OBJ_set_color(secondFace , 21);

			//UF_VEC3_negate(normal1,normal1);
			//UF_VEC3_negate(normal2,normal2);

			char str[133]="";

			/*sprintf(str,"%g", fabs(normal1[0]) < TOL ? 0 : normal1[0]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_X_X,str);
			sprintf(str,"%g",fabs(normal1[1]) < TOL ? 0 : normal1[1]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_X_Y,str);
			sprintf(str,"%g",fabs(normal1[2]) < TOL ? 0 : normal1[2]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_X_Z,str);

			sprintf(str,"%g",fabs(normal2[0]) < TOL ? 0 : normal2[0]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_Y_X,str);
			sprintf(str,"%g",fabs(normal2[1]) < TOL ? 0 : normal2[1]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_Y_Y,str);
			sprintf(str,"%g",fabs(normal2[2]) < TOL ? 0 : normal2[2]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_Y_Z,str);*/

			sprintf(str,"%g", normal1[0]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_X_X,str);
			sprintf(str,"%g",normal1[1]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_X_Y,str);
			sprintf(str,"%g",normal1[2]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_X_Z,str);

			sprintf(str,"%g",normal2[0]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_Y_X,str);
			sprintf(str,"%g",normal2[1]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_Y_Y,str);
			sprintf(str,"%g",normal2[2]);
			TYCOM_SetObjectStringAttribute(faceBody1,ATTR_NORMAL_DIR_Y_Z,str);

			

			
		}
		else
		{
			std::vector<tag_t> objsFaces1 = UI_GetSelectObjects2(faceSelection);

			for(int i = 0; i < objsFaces1.size(); i++)
			{
				tag_t oneFace = objsFaces1[i];
				if(UF_ASSEM_is_occurrence(oneFace))
				{
					oneFace = UF_ASSEM_ask_prototype_of_occ( oneFace) ;
				}

				int color = 1;
				if(colorIndex == 1)
					color = 36;
				else if(colorIndex == 2)
					color = 211;
				else if(colorIndex == 3)
					color = 6;
				else if(colorIndex == 4)
					color = 181;
				else if(colorIndex == 5)
					color = 31;
				else if(colorIndex == 6)
					color = 196;
				UF_OBJ_set_color(oneFace , color);
			}
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYColor::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
	try
	{
		if(block == enumColor)
		{
			//---------Enter your code here-----------
			UI_EnumGetCurrentSel(enumColor,m_curSel);
			InitShow();
		}
		else if(block == colorPicker)
		{
			//---------Enter your code here-----------
		}
		else if(block == faceSelection)
		{
			//---------Enter your code here-----------
		}
		else if(block == firstFace)
		{
			//---------Enter your code here-----------
		}
		else if(block == secondFace)
		{
			//---------Enter your code here-----------
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYColor::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: cancel_Cb
//------------------------------------------------------------------------------
int TYColor::cancel_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYColor::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYColor::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}

void TYColor::InitShow()
{
	if (m_curSel == 0)
	{
		UI_SetShow(firstFace,true);
		UI_SetShow(secondFace,true);
		UI_SetShow(faceSelection,false);
	}
	else
	{
		UI_SetShow(firstFace,false);
		UI_SetShow(secondFace,false);
		UI_SetShow(faceSelection,true);
	}
}

int TYColor::ClearOldProperty(tag_t face)
{
	tag_t faceBody = 0;
	UF_MODL_ask_face_body(face, &faceBody);
	uf_list_p_t faceList;
	UF_MODL_ask_body_faces(faceBody, &faceList);

	vtag_t faces;
	TYCOM_AskListItemsAndDelete(faceList, faces);

	UF_OBJ_disp_props_t disp_props;
	UF_OBJ_ask_display_properties(faceBody, &disp_props);

	for(int i = 0; i < faces.size(); i++)
	{
		UF_OBJ_disp_props_t disp_props1;
		UF_OBJ_ask_display_properties(faces[i], &disp_props1);
		if(disp_props1.color == 21)
		{
			UF_ATTR_delete_all( faces[i] , UF_ATTR_any );
			UF_OBJ_set_color(faces[i] , disp_props.color);
		}
	}
	return 0;
}
