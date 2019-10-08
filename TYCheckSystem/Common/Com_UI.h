#ifndef COMMON_UI_H_INCLUDED
#define COMMON_UI_H_INCLUDED

#include <uf_defs.h>
#include <uf_ui_types.h>
#include <uf.h>
#include <uf_obj.h>
#include <uf_ui.h>
#include <uf_ui_types.h>
#include <NXOpen/BlockStyler_UIBlock.hxx>
#include <NXOpen/ugmath.hxx>
#include "TY_Def.h"

using namespace NXOpen;

//UI Common
//----------------------UI Common Functions--------------------------------------//

//This function set the show status of input block.
void UI_BlockSetShowStatus(NXOpen::BlockStyler::UIBlock* block, bool show);
void UI_SetShow(NXOpen::BlockStyler::UIBlock* block, bool show);

void UI_BlockSetSensitivity(NXOpen::BlockStyler::UIBlock* block, bool sensitivity);

//This function set the label of a input block.
void UI_BlockSetLabel(NXOpen::BlockStyler::UIBlock* block, const NXString &label);
void UI_BlockSetBitmap(NXOpen::BlockStyler::UIBlock* block, const NXString &bitmap);

//This function set the max and min value of input double block.
void UI_DoubleSetMaxMinValue(NXOpen::BlockStyler::UIBlock* block, double max, double min);
void UI_StringSetOptions(NXOpen::BlockStyler::UIBlock* block, vNXString &options);

//This function set the enum current selection.
void UI_EnumSetCurrentSel(NXOpen::BlockStyler::UIBlock* block, int cursel);
//This function get the enum current selection.---需要改造为返回值类型的
void UI_EnumGetCurrentSel(NXOpen::BlockStyler::UIBlock* block, int &cursel);

//This function set the value of a double block.
void UI_DoubleSetValue(NXOpen::BlockStyler::UIBlock* block, double value);
//This function get the value of a double block.
void UI_DoubleGetValue(NXOpen::BlockStyler::UIBlock* block, double &value);


//This function set the value of a int block.
void UI_IntSetValue(NXOpen::BlockStyler::UIBlock* block, int value);
//This function get the value of a int block.
void UI_IntGetValue(NXOpen::BlockStyler::UIBlock* block, int &value);

//This function set the value of a string block.
void UI_StringSetValue(NXOpen::BlockStyler::UIBlock* block, NXString value);
//This function get the value of a string block.
void UI_StringGetValue(NXOpen::BlockStyler::UIBlock* block, NXString &value);

//This function set the value of a int block.
void UI_LogicalSetValue(NXOpen::BlockStyler::UIBlock* block, bool value);
//This function get the value of a int block.
void UI_LogicalGetValue(NXOpen::BlockStyler::UIBlock* block, bool &value);

void UI_PointGetPoint(NXOpen::BlockStyler::UIBlock* block, NXOpen::Point3d &point);
void UI_PointGetPoint_Tag(NXOpen::BlockStyler::UIBlock* block, std::vector<NXOpen::TaggedObject *> &obj);
void UI_PointSetPoint_Tag(NXOpen::BlockStyler::UIBlock* block, std::vector<NXOpen::TaggedObject *> &obj);

void UI_ListBox_SetItems(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & stringArray);
void UI_ListBox_GetItems(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & stringArray);
int UI_ListBox_GetSelectItem(NXOpen::BlockStyler::UIBlock* block);

//设置多个选择项
void UI_ListBox_GetSelectItems(NXOpen::BlockStyler::UIBlock* block, std::vector<int> &sels);
//NX7有问题
void UI_ListBox_SetSelectItem(NXOpen::BlockStyler::UIBlock* block, int sel);


std::vector<NXOpen::TaggedObject *> UI_GetSelectObjects(NXOpen::BlockStyler::UIBlock* block);
std::vector<tag_t> UI_GetSelectObjects2(NXOpen::BlockStyler::UIBlock* block);

tag_t UI_GetPlaneTag(NXOpen::BlockStyler::UIBlock* block);


//old ui
extern int KONKA_STYLER_set_item_value_string( int dialog_id, char *item, char * value );
extern int KONKA_STYLER_ask_item_value_string( int dialog_id, char *item, char *value );

void UI_SetSeletSolidBody(NXOpen::BlockStyler::UIBlock* block);



//-----------------NX7---------------//
void UI_EnumSetValues(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & values);
void UI_EnumGetValues(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & values);

void UI_EnumGetBlockString(NXOpen::BlockStyler::UIBlock* block, NXString & value);

void UI_StringsSetValues(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & values);
void UI_StringsGetValues(NXOpen::BlockStyler::UIBlock* block, std::vector<NXString> & values);

void UI_CSYS_GetSelected(NXOpen::BlockStyler::UIBlock* block, std::vector<NXOpen::TaggedObject *> &obj);
void UI_CSYS_SetSelected(NXOpen::BlockStyler::UIBlock* block, std::vector<NXOpen::TaggedObject *> &obj);

void UI_FilePathGetValue(NXOpen::BlockStyler::UIBlock* block, NXString &value);
void UI_FilePathSetValue(NXOpen::BlockStyler::UIBlock* block, NXString value);
#endif