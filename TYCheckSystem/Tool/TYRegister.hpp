//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  E:\Project\WetTang\Src\TYCheckSystem\install\application\TYRegister.hpp
//
//        This file was generated by the NX Block Styler
//        Created by: Administrator
//              Version: NX 7
//              Date: 07-28-2019  (Format: mm-dd-yyyy)
//              Time: 19:21
//
//==============================================================================

#ifndef TYREGISTER_H_INCLUDED
#define TYREGISTER_H_INCLUDED

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
// Namespaces needed for following template
//------------------------------------------------------------------------------
using namespace std;
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Forward declaration for Class
//------------------------------------------------------------------------------
class TYRegister;
//
//------------------------------------------------------------------------------
// Declaration of global variables
//------------------------------------------------------------------------------
extern TYRegister *theTYRegister;

class TYRegister
{
    // class members
public:
    static Session *theSession;
    static UI *theUI;
    TYRegister();
    static void Show_TYRegister();
    ~TYRegister();
    int Show();
    
    //----------------------- BlockStyler Callback Prototypes ---------------------
    // The following member function prototypes define the callbacks 
    // specified in your BlockStyler dialog.  The empty implementaiton
    // of these prototypes is provided in the TYRegister.cpp file. 
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
    NXOpen::BlockStyler::UIBlock* groupSelect;// Block type: Group
    NXOpen::BlockStyler::UIBlock* stringZhuCeMa;// Block type: String
    NXOpen::BlockStyler::UIBlock* stringXuLieHao;// Block type: String
    
};

#endif //TYREGISTER_H_INCLUDED
