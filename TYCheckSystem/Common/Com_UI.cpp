#include "Com_UI.h"

#include <NXOpen/BlockStyler_PropertyList.hxx>
#include <uf_styler.h>
//#include <NXOpen/BlockStyler_BodyCollector.hxx>
//#include <NXOpen/BlockStyler_FaceCollector.hxx>
//#include <NXOpen/BlockStyler_CurveCollector.hxx>
//This function set the max and min value of input double block.
void UI_DoubleSetMaxMinValue(NXOpen::BlockStyler::UIBlock* block, double max, double min)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetDouble("MinimumValue", min);
	pAttr->SetDouble("MaximumValue", max);
	delete pAttr;
	pAttr = NULL;
}

void UI_StringSetOptions(NXOpen::BlockStyler::UIBlock* block, vNXString &options)
{

	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	//std::vector<NXString> pnames = pAttr->GetPropertyNames();
	pAttr->SetStrings("ListItems", options);
	delete pAttr;
	pAttr = NULL;
}

//This function set the show status of input block.
void UI_BlockSetShowStatus(NXOpen::BlockStyler::UIBlock* block, bool show)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetLogical("Show", show);
	delete pAttr;
	pAttr = NULL;
}

//This function set the sensitivity status of input block.
void UI_BlockSetSensitivity(NXOpen::BlockStyler::UIBlock* block, bool sensitivity)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetLogical("Enable", sensitivity);
	delete pAttr;
	pAttr = NULL;
}

//This function set the enum current selection.
void UI_EnumSetCurrentSel(NXOpen::BlockStyler::UIBlock* block, int cursel)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetEnum("Value", cursel);
	delete pAttr;
	pAttr = NULL;
}

//This function get the enum current selection.
void UI_EnumGetCurrentSel(NXOpen::BlockStyler::UIBlock* block, int &cursel)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	cursel = pAttr->GetEnum("Value");
	delete pAttr;
	pAttr = NULL;
}

//This function set the label of a input block.
void UI_BlockSetLabel(NXOpen::BlockStyler::UIBlock* block, const NXString &label)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetString("Label", label);
	delete pAttr;
	pAttr = NULL;
}

//This function set the bitmap of a input block.
void UI_BlockSetBitmap(NXOpen::BlockStyler::UIBlock* block, const NXString &bitmap)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetString("Bitmap", bitmap);
	delete pAttr;
	pAttr = NULL;
}

//This function set the value of a double block.
void UI_DoubleSetValue(NXOpen::BlockStyler::UIBlock* block, double value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetDouble("Value", value);
	delete pAttr;
	pAttr = NULL;
}

//This function get the value of a double block.
void UI_DoubleGetValue(NXOpen::BlockStyler::UIBlock* block, double &value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	value = pAttr->GetDouble("Value");
	delete pAttr;
	pAttr = NULL;
}

//This function set the value of a double block.
void UI_IntSetValue(NXOpen::BlockStyler::UIBlock* block, int value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetInteger("Value", value);
	delete pAttr;
	pAttr = NULL;
}

//This function get the value of a double block.
void UI_IntGetValue(NXOpen::BlockStyler::UIBlock* block, int &value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	value = pAttr->GetInteger("Value");
	delete pAttr;
	pAttr = NULL;
}

//This function set the value of a double block.
void UI_StringSetValue(NXOpen::BlockStyler::UIBlock* block, NXString value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetString("Value", value);
	delete pAttr;
	pAttr = NULL;
}

//This function get the value of a double block.
void UI_StringGetValue(NXOpen::BlockStyler::UIBlock* block, NXString &value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	value = pAttr->GetString("Value");
	delete pAttr;
	pAttr = NULL;
}

//This function set the value of a double block.
void UI_LogicalSetValue(NXOpen::BlockStyler::UIBlock* block, bool value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetLogical("Value", value);
	delete pAttr;
	pAttr = NULL;
}

//This function get the value of a double block.
void UI_LogicalGetValue(NXOpen::BlockStyler::UIBlock* block, bool &value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	value = pAttr->GetLogical("Value");
	delete pAttr;
	pAttr = NULL;
}



//This function get the point position from the block.
void UI_PointGetPoint(NXOpen::BlockStyler::UIBlock* block, NXOpen::Point3d &point)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	point = pAttr->GetPoint("Point");
	delete pAttr;
	pAttr = NULL;
}

//This function get the point tag from the block.
void UI_PointGetPoint_Tag(NXOpen::BlockStyler::UIBlock* block, std::vector<NXOpen::TaggedObject *> &obj)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	obj = pAttr->GetTaggedObjectVector("SelectedObjects");
	delete pAttr;
	pAttr = NULL;
}

//This function get the point tag from the block.
void UI_PointSetPoint_Tag(NXOpen::BlockStyler::UIBlock* block, std::vector<NXOpen::TaggedObject *> &obj)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetTaggedObjectVector("SelectedObjects", obj);
	delete pAttr;
	pAttr = NULL;
}

//This function set the listbox strings.
void UI_ListBox_SetItems(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & stringArray)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetStrings("ListItems", stringArray);
	delete pAttr;
	pAttr = NULL;
}

//This function get the listbox strings.
void UI_ListBox_GetItems(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & stringArray)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	stringArray = pAttr->GetStrings("ListItems");
	delete pAttr;
	pAttr = NULL;
}

//This function get the listbox select item.
void UI_ListBox_GetSelectItems(NXOpen::BlockStyler::UIBlock* block, std::vector<int> &sels)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	sels = pAttr->GetIntegerVector("SelectedItems");
	delete pAttr;
	pAttr = NULL;
}

//This function get the listbox select item.
void UI_ListBox_SetSelectItem(NXOpen::BlockStyler::UIBlock* block, int sel)
{
	vint sels;
	sels.push_back(sel);
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	 pAttr->SetIntegerVector("SelectedItems",sels);
	delete pAttr;
	pAttr = NULL;
}

int UI_ListBox_GetSelectItem(NXOpen::BlockStyler::UIBlock* block)
{
	vint sel;
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	//NXOpen::BlockStyler::PropertyList::PropertyType type =pAttr->GetPropertyType("SelectedItems");
	//int len = pAttr->Length();
	sel = pAttr->GetIntegerVector("SelectedItems");

	delete pAttr;
	pAttr = NULL;
	return sel[0];
}


//This function set the value of a double block.
void UI_SetShow(NXOpen::BlockStyler::UIBlock* block, bool show)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetLogical("Show", show);
	delete pAttr;
	pAttr = NULL;
}

extern int KONKA_STYLER_set_item_value_string( int dialog_id, char *item, char * value )
{
	int iErr;
	UF_STYLER_item_value_type_t value_data;

	value_data.item_id = item;
	value_data.item_attr = UF_STYLER_VALUE;
	value_data.value.string = value;
	iErr = UF_STYLER_set_value( dialog_id, &value_data );
	if ( iErr )
	{
		//PrintErrorMessage( iErr );
		return 1;
	}

	return 0;
}

extern int KONKA_STYLER_ask_item_value_string( int dialog_id, char *item, char *value )
{
	int iErr;
	UF_STYLER_item_value_type_t value_data;

	value_data.item_id = item;
	value_data.item_attr = UF_STYLER_VALUE;
	iErr = UF_STYLER_ask_value( dialog_id, &value_data );
	if ( iErr )
	{
		//PrintErrorMessage( iErr );
		return 1;
	}

	if(value != 0)
        strcpy_s(value, strlen(value_data.value.string), value_data.value.string);
	
	return 0;
}

std::vector<NXOpen::TaggedObject *> UI_GetSelectObjects(NXOpen::BlockStyler::UIBlock* block)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	std::vector<NXOpen::TaggedObject *> objs;
	//bodies
	pAttr = block->GetProperties();
	objs = pAttr->GetTaggedObjectVector("SelectedObjects");

	delete pAttr;
	pAttr = 0;
	return objs;
}

std::vector<tag_t> UI_GetSelectObjects2(NXOpen::BlockStyler::UIBlock* block)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	std::vector<NXOpen::TaggedObject *> objs;
	//bodies
	pAttr = block->GetProperties();
	objs = pAttr->GetTaggedObjectVector("SelectedObjects");

	delete pAttr;
	pAttr = 0;
	vtag_t tobjs;
	for (int i = 0; i < objs.size(); i++)
	{
		tobjs.push_back(objs[i]->Tag());
	}
	return tobjs;
}

tag_t UI_GetPlaneTag(NXOpen::BlockStyler::UIBlock* block)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	//---- Enter your callback code here -----
	pAttr = block->GetProperties();
	std::vector<NXOpen::TaggedObject *> objsBasePlane = pAttr->GetTaggedObjectVector("SelectedObjects");
	delete pAttr;

	if(objsBasePlane.size() == 0)
		return 0;
	//tag_t plane = objsBasePlane[0]->GetTag();
	tag_t plane = objsBasePlane[0]->Tag();
	
	pAttr = NULL;
	return plane;
}


void UI_SetSeletSolidBody(NXOpen::BlockStyler::UIBlock* block)
{
	NXOpen::Selection::MaskTriple mt1;
	mt1.Type = UF_solid_type;
	mt1.Subtype = UF_all_subtype;
	mt1.SolidBodySubtype = UF_UI_SEL_FEATURE_SOLID_BODY;
	std::vector<NXOpen::Selection::MaskTriple>  maskTriples;
	maskTriples.push_back(mt1);

	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetSelectionFilter("SelectionFilter", NXOpen::Selection::SelectionActionClearAndEnableSpecific,
		maskTriples);
	//pAttr->SetEnum("StepStatus", 1);
	delete pAttr;
	pAttr = NULL;

}

void UI_EnumSetValues(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & values)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();

	pAttr->SetEnumMembers("Value",values);

	delete pAttr;
	pAttr = NULL;

}

void UI_EnumGetValues(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & values)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();

	values = pAttr->GetEnumMembers("Value");

	delete pAttr;
	pAttr = NULL;
}

void UI_StringsSetValues(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & values)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();

	pAttr->SetStrings("Value",values);

	delete pAttr;
	pAttr = NULL;

}

void UI_StringsGetValues(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & values)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();

	values = pAttr->GetStrings("Value");

	delete pAttr;
	pAttr = NULL;
}

void UI_EnumGetBlockString(NXOpen::BlockStyler::UIBlock* block, NXString & value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();

	value = pAttr->GetEnumAsString("Value");

	delete pAttr;
	pAttr = NULL;
}


//This function get the point tag from the block.
void UI_CSYS_GetSelected(NXOpen::BlockStyler::UIBlock* block, std::vector<NXOpen::TaggedObject *> &obj)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	obj = pAttr->GetTaggedObjectVector("SelectedObjects");
	delete pAttr;
	pAttr = NULL;
}

//This function get the point tag from the block.
void UI_CSYS_SetSelected(NXOpen::BlockStyler::UIBlock* block, std::vector<NXOpen::TaggedObject *> &obj)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetTaggedObjectVector("SelectedObjects", obj);
	delete pAttr;
	pAttr = NULL;
}
//This function set the value of a double block.
void UI_FilePathSetValue(NXOpen::BlockStyler::UIBlock* block, NXString value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	pAttr->SetString("Path", value);
	delete pAttr;
	pAttr = NULL;
}

//This function get the value of a double block.
void UI_FilePathGetValue(NXOpen::BlockStyler::UIBlock* block, NXString &value)
{
	NXOpen::BlockStyler::PropertyList *  pAttr = NULL;
	pAttr = block->GetProperties();
	value = pAttr->GetString("Path");
	delete pAttr;
	pAttr = NULL;
}





