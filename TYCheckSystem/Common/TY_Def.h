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
#define MAX_FSPEC_BUFSIZE 256
#define TY_GAP_DIS 0.1 //���ռ��
#define MAX_FILE_NAME_LENGTH 64

//�ͻ�����
#define ATTR_TYCOM_PROPERTY_CUSTOMER          "ATTR_TYCOM_PROPERTY_CUSTOMER"


//���������
#define ATTR_TYCOM_PROPERTY_SOLID_NAME      "ATTR_TYCOM_PROPERTY_SOLID_NAME"
//���������
#define ATTR_TYCOM_PROPERTY_SOLID_NAME2      "ATTR_TYCOM_PROPERTY_SOLID_NAME2"
//�ļ�����
#define ATTR_TYCOM_PROPERTY_PARTNAME     "ATTR_TYCOM_PROPERTY_PARTNAME"

//����
#define ATTR_TYCOM_PROPERTY_MATERIAL     "ATTR_TYCOM_PROPERTY_MATERIAL"

//����Ҫ��
#define ATTR_TYCOM_PROPERTY_TECH_REQUIREMENT      "ATTR_TYCOM_PROPERTY_TECH_REQUIREMENT"
//�ȴ���
#define ATTR_TYCOM_PROPERTY_HEAT_PROCESS      "ATTR_TYCOM_PROPERTY_HEAT_PROCESS"
//���洦��
#define ATTR_TYCOM_PROPERTY_FACE_PROCESS      "ATTR_TYCOM_PROPERTY_FACE_PROCESS"
//Ũ��
#define TY_ATTR_DENSITY    "TY_ATTR_DENSITY"//�ܶ� 


//����ר��
#define ATTR_TYCOM_TEXT_SPLINE_BODY_HANDLE "ATTR_TYCOM_TEXT_SPLINE_BODY_HANDLE"




#define ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE     "ATTR_TYCOM_PROPERTY_CUSTOMER_TYPE"
//�Ƿ�������
#define  ATTR_TYCOM_PROPERTY_NEED_RENAME "ATTR_TYCOM_PROPERTY_NEED_RENAME"
#define ATTR_TYCOM_PROPERTY_PART_QUANTITY     "ATTR_TYCOM_PROPERTY_PART_QUANTITY"
#define ATTR_TYCOM_PROPERTY_PART_QUANTITY_NUM "ATTR_TYCOM_PROPERTY_PART_QUANTITY_NUM"
//#define ATTR_TYCOM_PROPERTY_DRAWING_SCALE     "ATTR_TYCOM_PROPERTY_DRAWING_SCALE"
#define ATTR_TYCOM_PROPERTY_SH_SHEET_NUMBER     "ATTR_TYCOM_PROPERTY_SH_SHEET_NUMBER"
#define ATTR_TYCOM_PROPERTY_SH_NUMBER_OF_SHEETS    "ATTR_TYCOM_PROPERTY_SH_NUMBER_OF_SHEETS"
#define ATTR_TYCOM_PROPERTY_ITEM_REVISION    "ATTR_TYCOM_PROPERTY_ITEM_REVISION"
#define ATTR_TYCOM_DRAWING_REFERENCE_SET     "DRAWING"

//�Ƿ��ͼ
#define ATTR_TYCOM_PROPERTY_NEED_DRAFTING "ATTR_TYCOM_PROPERTY_NEED_DRAFTING"
//��׼���Ƿ�����
#define ATTR_TYCOM_PROPERTY_STD_DIVIDE "������׼��"
#define ATTR_TYCOM_PROPERTY_STD_GROUP "ʵ�����"

//��ͼ����--��һ��׼��
#define ATTR_TYCOM_DRAFTING_NORMAL_DIR "ATTR_TYCOM_DRAFTING_NORMAL_DIR"
//��ͼx����--�ڶ���׼��
#define ATTR_TYCOM_DRAFTING_X_DIR "ATTR_TYCOM_DRAFTING_X_DIR"

//ͼֽ��С
//1-a3�� 2-a3�� 3-a4�� 4-a4-��
#define ATTR_TYCOM_PROPERTY_DRAWING_TYPE     "ATTR_TYCOM_PROPERTY_DRAWING_TYPE"

//ͼ������
#define ATTR_TYCOM_PROPERTY_Layer    "ATTR_TYCOM_PROPERTY_Layer"
//Ũ��
#define ATTR_TYCOM_PROPERTY_DENSITY     "ATTR_TYCOM_PROPERTY_DENSITY"

//����ר��
#define ATTR_TYCOM_KEZI_1     "ATTR_TYCOM_KEZI_1"
#define ATTR_TYCOM_KEZI_2     "ATTR_TYCOM_KEZI_2"
#define ATTR_TYCOM_KEZI_3     "ATTR_TYCOM_KEZI_3"
#define ATTR_TYCOM_KEZI_4     "ATTR_TYCOM_KEZI_4"
#define ATTR_TYCOM_KEZI_5     "ATTR_TYCOM_KEZI_5"
#define ATTR_TYCOM_KEZI_6     "ATTR_TYCOM_KEZI_6"
#define ATTR_TYCOM_KEZI_7     "ATTR_TYCOM_KEZI_7"
#define ATTR_TYCOM_KEZI_8     "ATTR_TYCOM_KEZI_8"

//��ģ������滻������������
#define ATTR_TYCOM_EXTRUDE_REPLACE     "ATTR_TYCOM_EXTRUDE_REPLACE"

//������ϼ��Ƿ�����������ͼ
#define ATTR_TYCOM_WEB_SUB_DRAFTING_FLAG     "ATTR_TYCOM_WEB_SUB_DRAFTING_FLAG"

//��ϼ������ ���Ĳ������ͼֽ
#define WELD_DRAFTING_NUMBER 1500


#define ATTR_DRAFTING_NORMAL_DIR_X "ATTR_DRAFTING_NORMAL_DIR_X"
#define ATTR_DRAFTING_NORMAL_DIR_Y "ATTR_DRAFTING_NORMAL_DIR_Y"
#define ATTR_DRAFTING_NORMAL_DIR_Z "ATTR_DRAFTING_NORMAL_DIR_Z"

#define ATTR_DRAFTING_X_DIR_X "ATTR_DRAFTING_X_DIR_X"
#define ATTR_DRAFTING_X_DIR_Y "ATTR_DRAFTING_X_DIR_Y"
#define ATTR_DRAFTING_X_DIR_Z "ATTR_DRAFTING_X_DIR_Z"

#define NX_VERSION_60


