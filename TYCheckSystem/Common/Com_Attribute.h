#pragma once

#include <uf_defs.h>
#include "../TY_Def.h"

extern int TYCOM_SetObjectStringAttribute( tag_t part_tag, char title[64], const char name_str[132] );
extern int TYCOM_SetObjectIntAttribute( tag_t part_tag, char title[64], int data );
extern int TYCOM_SetObjectRealAttribute( tag_t part_tag, char title[64], double data );

bool TYCOM_GetObjectHasAttribute( const tag_t obj , char *title );
int TYCOM_GetObjectStringAttribute( tag_t obj , char *title , char *string );


int EF_ask_obj_real_attr( tag_t obj , char *title , double *real_data );
int EF_ask_obj_integer_attr( tag_t obj , char *title , int *integer_data );
int EF_ask_obj_integer_attr_Ori( tag_t obj , char *title , int *integer_data );



//长字符串属性设置和读取
int TYCOM_SetObjectAttributeLong(tag_t body, char *title, vNXString &values);
int TYCOM_GetObjectAttributeLong(tag_t body, char *title, vNXString &values);

