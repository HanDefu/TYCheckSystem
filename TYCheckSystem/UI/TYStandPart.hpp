//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYStandPart.hpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 18:57
//
//==============================================================================

#ifndef TYSTANDPART_H_INCLUDED
#define TYSTANDPART_H_INCLUDED

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include <uf_defs.h>
#include <uf_ui_types.h>
#include <iostream>
#include <NXOpen/Session.hxx>
#include <NXOpen/UI.hxx>
#include <NXOpen/NXMessageBox.hxx>
#include <NXOpen/Callback.hxx>
#include <NXOpen/NXException.hxx>
#include <NXOpen/BlockStyler_UIBlock.hxx>
#include <NXOpen/BlockStyler_BlockDialog.hxx>
#include <NXOpen/BlockStyler_PropertyList.hxx>
#include <NXOpen/BlockStyler_ListBox.hxx>
#include "../Common/StandardPartData.h"
//------------------------------------------------------------------------------
// Namespaces needed for following template
//------------------------------------------------------------------------------
using namespace std;
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Forward declaration for Class
//------------------------------------------------------------------------------
class TYStandPart;
//
//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
extern TYStandPart *theTYStandPart;


//还需要做 预览  编辑功能
//定位功能需要进一步完善
//父节点功能
//标准件名称功能
//开孔自动选择还是手动选择？工具体
class TYStandPart
{
    // class members
public:
    static Session *theSession;
    static UI *theUI;
    TYStandPart();
    static void Show_TYStandPart();
    ~TYStandPart();
    int Show();
    
    //----------------------- BlockStyler Callback Prototypes ---------------------
    // The following member function prototypes define the callbacks 
    // specified in your BlockStyler dialog.  The empty implementaiton
    // of these prototypes is provided in the TYStandPart.cpp file. 
    // You are REQUIRED to write the implementation for these funtions.
    //------------------------------------------------------------------------------
    void initialize_cb();
    void dialogShown_cb();
    int apply_cb();
    int ok_cb();
    int cancel_cb();
    int update_cb(NXOpen::BlockStyler::UIBlock* block);
    int filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject);

	void UpdateExpUI();
	void SetStdDefaultName();
    
private:
    std::string theDialogName;
    NXOpen::BlockStyler::BlockDialog* theDialog;
    NXOpen::BlockStyler::UIBlock* groupSearch;// Block type: Group
    NXOpen::BlockStyler::UIBlock* stringKey;// Block type: String
    NXOpen::BlockStyler::UIBlock* buttonSearch;// Block type: Button
    NXOpen::BlockStyler::ListBox* listSearchResult;// Block type: List Box
    NXOpen::BlockStyler::UIBlock* groupClass;// Block type: Group
    NXOpen::BlockStyler::UIBlock* enumFirstName;// Block type: Enumeration
    NXOpen::BlockStyler::UIBlock* enumSecondName;// Block type: Enumeration
    NXOpen::BlockStyler::ListBox* listParts;// Block type: List Box
    NXOpen::BlockStyler::UIBlock* groupLegend;// Block type: Group
    NXOpen::BlockStyler::UIBlock* labelLegend;// Block type: Label
    NXOpen::BlockStyler::UIBlock* groupParameter;// Block type: Group
    NXOpen::BlockStyler::ListBox* listParmeters;// Block type: List Box
    NXOpen::BlockStyler::UIBlock* doublePara;// Block type: Double
    NXOpen::BlockStyler::UIBlock* enumNoKeyinPara;// Block type: Enumeration
    NXOpen::BlockStyler::UIBlock* groupPosition;// Block type: Group
    NXOpen::BlockStyler::UIBlock* csysPos;// Block type: Specify Csys
    NXOpen::BlockStyler::UIBlock* groupSetting;// Block type: Group
    NXOpen::BlockStyler::UIBlock* toggleSubtract;// Block type: Toggle
    NXOpen::BlockStyler::UIBlock* togglePreview;// Block type: Toggle


	tag_t stdPreviewInstance;
	logical newCopy;
	int first;

	StandardPartData RoyStdData;
    
};
#endif //TYSTANDPART_H_INCLUDED
