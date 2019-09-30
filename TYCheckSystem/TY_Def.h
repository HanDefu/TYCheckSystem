#pragma once

#include <vector>
#include <uf_defs.h>
#include <NXOpen\UGMath.hxx>

#define TYCOM_DEBUG

using namespace std;
using namespace NXOpen;

//definitions - help vectors
typedef std::vector<tag_t> vtag_t;
typedef std::vector<tag_t>::iterator itvtag_t;

typedef std::vector<vtag_t> vvtag_t;
typedef std::vector<vtag_t>::iterator itvvtag_t;

typedef std::vector<NXOpen::Point3d> vPoint3d;
typedef std::vector<NXOpen::Point3d>::iterator itvPoint3d;

typedef std::vector<NXOpen::Point3d> vPoint3d;
typedef std::vector<NXOpen::Point3d>::iterator itvPoint3d;


typedef std::vector<double> vdouble;
typedef std::vector<double>::iterator itvdouble;

typedef std::vector<vdouble> vvdouble;
typedef std::vector<vdouble>::iterator itvvdouble;

typedef std::vector<int> vint;
typedef std::vector<int>::iterator itvvint;


typedef std::vector<string> vstring;
typedef std::vector<string>::iterator itvstring;

typedef std::vector<NXString> vNXString;
typedef std::vector<NXString>::iterator itvNXString;
typedef std::vector<vNXString> vvNXString;

#define TY_STR_LEN 256
#define TY_GAP_DIS 0.1 //悬空检测

//浓度
#define TY_ATTR_DENSITY    "TY_ATTR_DENSITY"//密度 

//镜像件原件
#define ATTR_TYCOM_MIRROR_ORI_OBJ        "ATTR_TYCOM_MIRROR_ORI_OBJ"
//镜像件
#define ATTR_TYCOM_MIRROR_OBJ        "ATTR_TYCOM_MIRROR_OBJ"
//镜像标准件
#define ATTR_TYCOM_MIRROR_STANDARD_PART        "ATTR_TYCOM_MIRROR_STANDARD_PART"

//刻字专用
#define ATTR_TYCOM_TEXT_SPLINE_BODY_HANDLE "ATTR_TYCOM_TEXT_SPLINE_BODY_HANDLE"

//相同件
#define ATTR_TYCOM_SAME_OBJ        "ATTR_TYCOM_SAME_OBJ"

//焊接件
#define ATTR_TYCOM_WELD_OBJ        "ATTR_TYCOM_PROPERTY_WELD"
#define ATTR_TYCOM_PROPERTY_WELD      "ATTR_TYCOM_PROPERTY_WELD"
#define ATTR_TYCOM_WELD_OBJ_MIRROR   "ATTR_TYCOM_WELD_OBJ_MIRROR"
#define ATTR_TYCOM_WELD_PART   "ATTR_TYCOM_WELD_PART"
//三个原始零件 ATTR_TYCOM_WELD_OBJ = value 10001 
//三个镜像 ATTR_TYCOM_WELD_OBJ_MIRROR = value 10001 ATTR_TYCOM_WELD_OBJ

//客户属性
#define ATTR_TYCOM_PROPERTY_CUSTOMER          "ATTR_TYCOM_PROPERTY_CUSTOMER"

//事业部
#define ATTR_TYCOM_PROPERTY_PARTMENT          "ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE"
#define ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE     "ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE"

//组件号
#define ATTR_TYCOM_PROPERTY_GROUP_NUMBER      "ATTR_TYCOM_PROPERTY_GROUP_NUMBER"
//零件序号
#define ATTR_TYCOM_PROPERTY_GROUP_SUBINDEX "ATTR_TYCOM_PROPERTY_GROUP_SUBINDEX"

//零件主名称
#define ATTR_TYCOM_PROPERTY_SOLID_NAME      "ATTR_TYCOM_PROPERTY_SOLID_NAME"
//零件次名称
#define ATTR_TYCOM_PROPERTY_SOLID_NAME2      "ATTR_TYCOM_PROPERTY_SOLID_NAME2"

//技术要求
#define ATTR_TYCOM_PROPERTY_TECH_REQUIREMENT      "ATTR_TYCOM_PROPERTY_TECH_REQUIREMENT"
//热处理
#define ATTR_TYCOM_PROPERTY_HEAT_PROCESS      "ATTR_TYCOM_PROPERTY_HEAT_PROCESS"
//表面处理
#define ATTR_TYCOM_PROPERTY_FACE_PROCESS      "ATTR_TYCOM_PROPERTY_FACE_PROCESS"

//材料
#define ATTR_TYCOM_PROPERTY_MATERIAL     "ATTR_TYCOM_PROPERTY_MATERIAL"
#define ATTR_TYCOM_PROPERTY_PARTNAME     "ATTR_TYCOM_PROPERTY_PARTNAME"

#define ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE     "ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE"
//是否重命名
#define  ATTR_TYCOM_PROPERTY_NEED_RENAME "ATTR_TYCOM_PROPERTY_NEED_RENAME"
#define ATTR_TYCOM_PROPERTY_PART_QUANTITY     "ATTR_TYCOM_PROPERTY_PART_QUANTITY"
#define ATTR_TYCOM_PROPERTY_PART_QUANTITY_NUM "ATTR_TYCOM_PROPERTY_PART_QUANTITY_NUM"
//#define ATTR_TYCOM_PROPERTY_DRAWING_SCALE     "ATTR_TYCOM_PROPERTY_DRAWING_SCALE"
#define ATTR_TYCOM_PROPERTY_SH_SHEET_NUMBER     "ATTR_TYCOM_PROPERTY_SH_SHEET_NUMBER"
#define ATTR_TYCOM_PROPERTY_SH_NUMBER_OF_SHEETS    "ATTR_TYCOM_PROPERTY_SH_NUMBER_OF_SHEETS"
#define ATTR_TYCOM_PROPERTY_ITEM_REVISION    "ATTR_TYCOM_PROPERTY_ITEM_REVISION"
#define ATTR_TYCOM_DRAWING_REFERENCE_SET     "DRAWING"

//是否出图
#define ATTR_TYCOM_PROPERTY_NEED_DRAFTING "ATTR_TYCOM_PROPERTY_NEED_DRAFTING"
//标准件是否析出
#define ATTR_TYCOM_PROPERTY_STD_DIVIDE "析出标准件"
#define ATTR_TYCOM_PROPERTY_STD_GROUP "实体分组"

//出图方向--第一基准面
#define ATTR_TYCOM_DRAFTING_NORMAL_DIR "ATTR_TYCOM_DRAFTING_NORMAL_DIR"
//出图x方向--第二基准面
#define ATTR_TYCOM_DRAFTING_X_DIR "ATTR_TYCOM_DRAFTING_X_DIR"

//图纸大小
//1-a3横 2-a3竖 3-a4横 4-a4-竖
#define ATTR_TYCOM_PROPERTY_DRAWING_TYPE     "ATTR_TYCOM_PROPERTY_DRAWING_TYPE"

//图层属性
#define ATTR_TYCOM_PROPERTY_Layer    "ATTR_TYCOM_PROPERTY_Layer"
//浓度
#define ATTR_TYCOM_PROPERTY_DENSITY     "ATTR_TYCOM_PROPERTY_DENSITY"

//刻字专用
#define ATTR_TYCOM_KEZI_1     "ATTR_TYCOM_KEZI_1"
#define ATTR_TYCOM_KEZI_2     "ATTR_TYCOM_KEZI_2"
#define ATTR_TYCOM_KEZI_3     "ATTR_TYCOM_KEZI_3"
#define ATTR_TYCOM_KEZI_4     "ATTR_TYCOM_KEZI_4"
#define ATTR_TYCOM_KEZI_5     "ATTR_TYCOM_KEZI_5"
#define ATTR_TYCOM_KEZI_6     "ATTR_TYCOM_KEZI_6"
#define ATTR_TYCOM_KEZI_7     "ATTR_TYCOM_KEZI_7"
#define ATTR_TYCOM_KEZI_8     "ATTR_TYCOM_KEZI_8"

//主模型镶块替换拉伸特征属性
#define ATTR_TYCOM_EXTRUDE_REPLACE     "ATTR_TYCOM_EXTRUDE_REPLACE"

//定义组合件是否进行子零件出图
#define ATTR_TYCOM_WEB_SUB_DRAFTING_FLAG     "ATTR_TYCOM_WEB_SUB_DRAFTING_FLAG"

//组合件的情况 第四层出几个图纸
#define WELD_DRAFTING_NUMBER 1500

#define NX_VERSION_60


