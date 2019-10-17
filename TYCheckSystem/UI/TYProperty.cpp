//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYProperty.cpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 18:57 (Format: hh-mm)
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
#include "TYProperty.hpp"
#include "../ConfigData/TYGlobalData.h"
#include "../Common/Com_UI.h"
#include <uf_assem.h>
#include "../Common/Com_Attribute.h"
#include "../Common/Com_WT.h"
#include "../Common/Com_UG.h"
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(TYProperty::theSession) = NULL;
UI *(TYProperty::theUI) = NULL;

//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
TYProperty *theTYProperty;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
TYProperty::TYProperty()
{
	try
	{
		// Initialize the NX Open C++ API environment
		TYProperty::theSession = NXOpen::Session::GetSession();
		TYProperty::theUI = UI::GetUI();
		theDialogName = "TYProperty.dlx";
		theDialog = TYProperty::theUI->CreateDialog(theDialogName.c_str());
		// Registration of callback functions
		theDialog->AddApplyHandler(make_callback(this, &TYProperty::apply_cb));
		theDialog->AddOkHandler(make_callback(this, &TYProperty::ok_cb));
		theDialog->AddUpdateHandler(make_callback(this, &TYProperty::update_cb));
		theDialog->AddCancelHandler(make_callback(this, &TYProperty::cancel_cb));
		theDialog->AddFilterHandler(make_callback(this, &TYProperty::filter_cb));
		theDialog->AddInitializeHandler(make_callback(this, &TYProperty::initialize_cb));
		theDialog->AddDialogShownHandler(make_callback(this, &TYProperty::dialogShown_cb));

		m_customerSel = 0;
		m_firstNameSel = 0;
		m_secondNameSel = 0;
		m_materialSel = 0;
		m_workType = 0;//默认自绘模式
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
TYProperty::~TYProperty()
{
	if (theDialog != NULL)
	{
		delete theDialog;
		theDialog = NULL;
	}
}

int TYProperty::Show()
{
	try
	{
		theDialog->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYProperty::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Method name: Show_TYProperty
//------------------------------------------------------------------------------
void TYProperty::Show_TYProperty(int workType)
{
	try
	{
		theTYProperty = new TYProperty();
		// The following method shows the dialog immediately
		theTYProperty->m_workType = workType;
		theTYProperty->Show();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYProperty::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	delete theTYProperty;
}

//------------------------------------------------------------------------------
//---------------------Block Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void TYProperty::initialize_cb()
{
	try
	{
		groupSelect = theDialog->TopBlock()->FindBlock("groupSelect");
		selectionBodies = theDialog->TopBlock()->FindBlock("selectionBodies");
		groupProperty = theDialog->TopBlock()->FindBlock("groupProperty");
		enumFirstName = theDialog->TopBlock()->FindBlock("enumMainClass");
		enumSecondName = theDialog->TopBlock()->FindBlock("enumSubClass");
		enumMaterial = theDialog->TopBlock()->FindBlock("enumMaterial");
		enumHeatProcess = theDialog->TopBlock()->FindBlock("enumHeatProcess");
		enumFaceProcess = theDialog->TopBlock()->FindBlock("enumFaceProcess");
		stringTechReq = theDialog->TopBlock()->FindBlock("stringTechReq");
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYProperty::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void TYProperty::dialogShown_cb()
{
	try
	{
		UI_EnumSetValues(enumFirstName, TYGBDATA->m_nameFirst);


		if (TYGBDATA->m_nameFirst.size() > 0)
		{
			UI_EnumSetValues(enumFirstName, TYGBDATA->m_nameFirst);
			if (m_firstNameSel < TYGBDATA->m_nameFirst.size())
			    UI_EnumSetCurrentSel(enumFirstName,m_firstNameSel);
		}
		
		if(TYGBDATA->m_nameSecond.size() > m_firstNameSel)
		{
			UI_EnumSetValues(enumSecondName, TYGBDATA->m_nameSecond[m_firstNameSel]);
			if (m_secondNameSel <  TYGBDATA->m_nameSecond[m_firstNameSel].size())
			    UI_EnumSetCurrentSel(enumSecondName, m_secondNameSel);
		}

		
		UpdateMaterial();
		UI_EnumSetCurrentSel(enumMaterial, m_materialSel);
		UpdateHeatAndFace();
		UpdateTech();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYProperty::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int TYProperty::apply_cb()
{
	try
	{
		NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
		//bodies
		pAttr = selectionBodies->GetProperties();
		std::vector<NXOpen::TaggedObject *> objsBodies = pAttr->GetTaggedObjectVector("SelectedObjects");
		delete pAttr;
		pAttr = NULL;

		int cursel = 0;


		//名称
		NXString firstName, secondName;
		UI_EnumGetBlockString(enumFirstName, firstName);
		UI_EnumGetBlockString(enumSecondName, secondName);
		//name = first + second;

		//技术要求
		std::vector<NXString> requs;
		UI_StringsGetValues(stringTechReq,requs);

		//材料
		NXString material;
		UI_EnumGetBlockString(enumMaterial, material);

		//热处理
		NXString heatProcess;
		UI_EnumGetBlockString(enumHeatProcess, heatProcess);

		//表面处理
		NXString faceProcess;
		UI_EnumGetBlockString(enumFaceProcess, faceProcess);

		double density = TYGBDATA->GetDensity(material);
        int ret = 0;

		vtag_t partBodies;
		TYCOM_GetCurrentPartSolidBodies(partBodies);


		for(int i = 0; i < objsBodies.size(); i++)
		{
			if (m_workType == 1 && i > 0)//标准件只赋一个属性
				continue;

			char attriValue[128] = "";

			tag_t thisBody = 0;
			if( UF_ASSEM_is_occurrence( objsBodies[i]->Tag() ))
				thisBody = UF_ASSEM_ask_prototype_of_occ ( objsBodies[i]->Tag() ) ;
			else
				thisBody = objsBodies[i]->Tag();


			UF_OBJ_set_blank_status(objsBodies[i]->Tag(),UF_OBJ_BLANKED);
			TYCOM_SetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_SOLID_NAME, firstName.getLocaleText());
			TYCOM_SetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_SOLID_NAME2, secondName.getLocaleText());
			TYCOM_SetObjectAttributeLong(thisBody, ATTR_TYCOM_PROPERTY_TECH_REQUIREMENT, requs);
			TYCOM_SetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_MATERIAL, material.getLocaleText());
			TYCOM_SetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_HEAT_PROCESS, heatProcess.getLocaleText());
			TYCOM_SetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_FACE_PROCESS, faceProcess.getLocaleText());
			TYCOM_SetObjectRealAttribute( thisBody, TY_ATTR_DENSITY, density);

			int indexProperty = 0;
			ret = EF_ask_obj_integer_attr( thisBody , ATTR_TYCOM_PROPERTY_INDEX , &indexProperty );
			if(ret != 0) //仅仅处理不存在的情况
			{
                 int maxIndex = TYCOM_GetMaxProperyIndex(partBodies);
				 TYCOM_SetObjectIntAttribute( thisBody, ATTR_TYCOM_PROPERTY_INDEX, maxIndex+1 );
			}
		}

	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYProperty::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int TYProperty::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
	try
	{
		if(block == selectionBodies)
		{
			//---------Enter your code here-----------
		}
		else if(block == enumFirstName)
		{
			//---------Enter your code here-----------
			UI_EnumGetCurrentSel(enumFirstName, m_firstNameSel);
			UI_EnumSetValues(enumSecondName,TYGBDATA->m_nameSecond[m_firstNameSel]);

			UpdateMaterial();
			UpdateTech();
			UpdateHeatAndFace();
		}
		else if(block == enumSecondName)
		{
			UpdateMaterial();
			UpdateTech();
			UpdateHeatAndFace();
		}
		else if(block == enumMaterial)
		{
			UpdateHeatAndFace();
		}
		else if(block == enumHeatProcess)
		{
			//---------Enter your code here-----------
		}
		else if(block == enumFaceProcess)
		{
			//---------Enter your code here-----------
		}
		else if(block == stringTechReq)
		{
			//---------Enter your code here-----------
		}
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYProperty::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int TYProperty::ok_cb()
{
	try
	{
		apply_cb();
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYProperty::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: cancel_Cb
//------------------------------------------------------------------------------
int TYProperty::cancel_cb()
{
	try
	{
		//---- Enter your callback code here -----
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		TYProperty::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return 0;
}

//------------------------------------------------------------------------------
//Callback Name: filter_cb
//------------------------------------------------------------------------------
int TYProperty::filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject)
{
	return(UF_UI_SEL_ACCEPT);
}

void TYProperty::ClearData()
{
	
}

void TYProperty::UpdateHeatAndFace()
{
	NXString firstName,material;
	UI_EnumGetBlockString(enumFirstName, firstName);
	UI_EnumGetBlockString(enumMaterial, material);


	vNXString faceProcesses = TYGBDATA->GetFaceProcess(firstName,material);
	UI_EnumSetValues(enumFaceProcess,faceProcesses);


	vNXString heatProcesses = TYGBDATA->GetHeatProcess(firstName,material);
	UI_EnumSetValues(enumHeatProcess,heatProcesses);
}

void TYProperty::UpdateMaterial()
{
	int curselFirst = 0;
	int curselSecond = 0;

	UI_EnumGetCurrentSel(enumFirstName, curselFirst);
	UI_EnumGetCurrentSel(enumSecondName, curselSecond);


	vNXString materials = TYGBDATA->GetMaterial(curselFirst,curselSecond);
	
	UI_EnumSetValues(enumMaterial,materials);
}

void TYProperty::UpdateTech()
{
	int curselFirst = 0;
	int curselSecond = 0;

	UI_EnumGetCurrentSel(enumFirstName, curselFirst);
	UI_EnumGetCurrentSel(enumSecondName, curselSecond);

	vNXString techReqs = TYGBDATA->GetTechRequirement(curselFirst,curselSecond);

	UI_StringsSetValues(stringTechReq,techReqs);
}


