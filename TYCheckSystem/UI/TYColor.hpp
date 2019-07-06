//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYColor.hpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 18:56
//
//==============================================================================

#ifndef TYCOLOR_H_INCLUDED
#define TYCOLOR_H_INCLUDED

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
//------------------------------------------------------------------------------
//Bit Option for Property: EntityType
//------------------------------------------------------------------------------
#define                          EntityType_AllowFaces (1 << 4);
#define                         EntityType_AllowDatums (1 << 5);
//------------------------------------------------------------------------------
//Bit Option for Property: FaceRules
//------------------------------------------------------------------------------
#define                           FaceRules_SingleFace (1 << 0);
#define                          FaceRules_RegionFaces (1 << 1);
#define                         FaceRules_TangentFaces (1 << 2);
#define                   FaceRules_TangentRegionFaces (1 << 3);
#define                            FaceRules_BodyFaces (1 << 4);
#define                         FaceRules_FeatureFaces (1 << 5);
#define                        FaceRules_AdjacentFaces (1 << 6);
#define                  FaceRules_ConnectedBlendFaces (1 << 7);
#define                        FaceRules_AllBlendFaces (1 << 8);
#define                             FaceRules_RibFaces (1 << 9);
#define                            FaceRules_SlotFaces (1 <<10);
#define                   FaceRules_BossandPocketfaces (1 <<11);
#define                       FaceRules_MergedRibFaces (1 <<12);
#define                  FaceRules_RegionBoundaryFaces (1 <<13);
#define                 FaceRules_FaceAndAdjacentFaces (1 <<14);
#define                             FaceRules_AnyFaces (1 <<15);
//------------------------------------------------------------------------------
// Namespaces needed for following template
//------------------------------------------------------------------------------
using namespace std;
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Forward declaration for Class
//------------------------------------------------------------------------------
class TYColor;
//
//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
extern TYColor *theTYColor;

class TYColor
{
    // class members
public:
    static Session *theSession;
    static UI *theUI;
    TYColor();
    static void Show_TYColor();
    ~TYColor();
    int Show();
    
    //----------------------- BlockStyler Callback Prototypes ---------------------
    // The following member function prototypes define the callbacks 
    // specified in your BlockStyler dialog.  The empty implementaiton
    // of these prototypes is provided in the TYColor.cpp file. 
    // You are REQUIRED to write the implementation for these funtions.
    //------------------------------------------------------------------------------
    void initialize_cb();
    void dialogShown_cb();
    int apply_cb();
    int ok_cb();
    int cancel_cb();
    int update_cb(NXOpen::BlockStyler::UIBlock* block);
    int filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject);
	void InitShow();
	int ClearOldProperty(tag_t face);
    
private:
    std::string theDialogName;
    NXOpen::BlockStyler::BlockDialog* theDialog;
    NXOpen::BlockStyler::UIBlock* group;// Block type: Group
    NXOpen::BlockStyler::UIBlock* enumColor;// Block type: Enumeration
    NXOpen::BlockStyler::UIBlock* colorPicker;// Block type: Color Picker
    NXOpen::BlockStyler::UIBlock* groupSelect;// Block type: Group
    NXOpen::BlockStyler::UIBlock* faceSelection;// Block type: Face Collector
    NXOpen::BlockStyler::UIBlock* firstFace;// Block type: Face Collector
    NXOpen::BlockStyler::UIBlock* secondFace;// Block type: Face Collector

	int m_curSel;
    
};
#endif //TYCOLOR_H_INCLUDED
