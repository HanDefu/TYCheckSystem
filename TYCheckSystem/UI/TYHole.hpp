//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\WeiTang\install\application\TYHole.hpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 18:56
//
//==============================================================================

#ifndef TYHOLE_H_INCLUDED
#define TYHOLE_H_INCLUDED

#define  HOLE_TYPE_GeneralCounterbore //如果定义了这个表示沉头孔 威唐模式 否则若宇模式 简单孔

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
//Bit Option for Property: SnapPointTypesEnabled
//------------------------------------------------------------------------------
#define              SnapPointTypesEnabled_UserDefined (1 << 0);
#define                 SnapPointTypesEnabled_Inferred (1 << 1);
#define           SnapPointTypesEnabled_ScreenPosition (1 << 2);
#define                 SnapPointTypesEnabled_EndPoint (1 << 3);
#define                 SnapPointTypesEnabled_MidPoint (1 << 4);
#define             SnapPointTypesEnabled_ControlPoint (1 << 5);
#define             SnapPointTypesEnabled_Intersection (1 << 6);
#define                SnapPointTypesEnabled_ArcCenter (1 << 7);
#define            SnapPointTypesEnabled_QuadrantPoint (1 << 8);
#define            SnapPointTypesEnabled_ExistingPoint (1 << 9);
#define             SnapPointTypesEnabled_PointonCurve (1 <<10);
#define           SnapPointTypesEnabled_PointonSurface (1 <<11);
#define         SnapPointTypesEnabled_PointConstructor (1 <<12);
#define     SnapPointTypesEnabled_TwocurveIntersection (1 <<13);
#define             SnapPointTypesEnabled_TangentPoint (1 <<14);
#define                    SnapPointTypesEnabled_Poles (1 <<15);
//------------------------------------------------------------------------------
//Bit Option for Property: SnapPointTypesOnByDefault
//------------------------------------------------------------------------------
#define             SnapPointTypesOnByDefault_EndPoint (1 << 3);
#define             SnapPointTypesOnByDefault_MidPoint (1 << 4);
#define         SnapPointTypesOnByDefault_ControlPoint (1 << 5);
#define         SnapPointTypesOnByDefault_Intersection (1 << 6);
#define            SnapPointTypesOnByDefault_ArcCenter (1 << 7);
#define        SnapPointTypesOnByDefault_QuadrantPoint (1 << 8);
#define        SnapPointTypesOnByDefault_ExistingPoint (1 << 9);
#define         SnapPointTypesOnByDefault_PointonCurve (1 <<10);
#define       SnapPointTypesOnByDefault_PointonSurface (1 <<11);
#define     SnapPointTypesOnByDefault_PointConstructor (1 <<12);
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
class TYHole;
//
//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
extern TYHole *theTYHole;

class TYHole
{
    // class members
public:
    static Session *theSession;
    static UI *theUI;
    TYHole();
    static void Show_TYHole();
    ~TYHole();
    int Show();
    
    //----------------------- BlockStyler Callback Prototypes ---------------------
    // The following member function prototypes define the callbacks 
    // specified in your BlockStyler dialog.  The empty implementaiton
    // of these prototypes is provided in the TYHole.cpp file. 
    // You are REQUIRED to write the implementation for these funtions.
    //------------------------------------------------------------------------------
    void initialize_cb();
    void dialogShown_cb();
    int apply_cb();
    int ok_cb();
    int cancel_cb();
    int update_cb(NXOpen::BlockStyler::UIBlock* block);
    int filter_cb(NXOpen::BlockStyler::UIBlock*  block, NXOpen::TaggedObject* selectObject);
    
private:
    std::string theDialogName;
    NXOpen::BlockStyler::BlockDialog* theDialog;
	NXOpen::BlockStyler::UIBlock* group;// Block type: Group
	NXOpen::BlockStyler::UIBlock* enumHoleType;// Block type: Enumeration 孔类型选择
    NXOpen::BlockStyler::UIBlock* groupSelect;// Block type: Group
    NXOpen::BlockStyler::UIBlock* selectionBody;// Block type: Selection
    NXOpen::BlockStyler::UIBlock* selectFace;// Block type: Face Collector
    NXOpen::BlockStyler::UIBlock* groupSetting;// Block type: Group
    NXOpen::BlockStyler::UIBlock* groupHoleDepth;// Block type: Group
    NXOpen::BlockStyler::UIBlock* enumAuto;// Block type: Enumeration
    NXOpen::BlockStyler::UIBlock* doubleHoleDepth;// Block type: Double 通孔深度
	NXOpen::BlockStyler::UIBlock* doubleChenTouDepth;// Block type: Double
    
};
#endif //TYHOLE_H_INCLUDED
