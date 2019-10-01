#include "Common_Function_Attribute.h"
#include <uf_attr.h>
#include <uf.h>
#include <uf_assem.h>
#include <string.h>
#include <stdio.h>


extern int TYCOM_SetObjectStringAttribute( tag_t part_tag, char title[64], const char name_str[132] )
{
	int err;
	UF_ATTR_value_t value;
	char copy[1024] = "";
	strcpy(copy,name_str);
	value.type = UF_ATTR_string;
	value.value.string = copy;
	err = UF_ATTR_assign( part_tag, title, value );
	return err;
}

/*-----------------------------------------------------------------------------------------
 * Function name : USER_set_moldbase_integer_attr
 * Description : 设置一个部件的整形属性
 * Input : 
 *   part_tag : 需要设置属性的部件原型
 *   title : 属性标题
 *   data : 属性内容
 * Return : 0  OK
 *-----------------------------------------------------------------------------------------*/
extern int TYCOM_SetObjectIntAttribute( tag_t part_tag, char title[64], int data )
{
	int err;
	UF_ATTR_value_t value;
	
	value.type = UF_ATTR_integer;
	value.value.integer = data;
	err = UF_ATTR_assign( part_tag, title, value );
	return err;
}
/*-----------------------------------------------------------------------------------------
 * Function name : USER_set_moldbase_double_attr
 * Description : 设置一个部件的浮点属性
 * Input : 
 *   part_tag : 需要设置属性的部件原型
 *   title : 属性标题
 *   data : 属性内容
 * Return : 0  OK
 *-----------------------------------------------------------------------------------------*/
extern int TYCOM_SetObjectRealAttribute( tag_t part_tag, char title[64], double data )
{
	int err;
	UF_ATTR_value_t value;
	
	value.type = UF_ATTR_real;
	value.value.real = data;
	err = UF_ATTR_assign( part_tag, title, value );
	return err;
}

int TYCOM_GetObjectStringAttribute( tag_t obj , char *title , char *string )
{
	UF_ATTR_value_t  value ;
    int		ret;

	strcpy( string , "" ) ;
	if( obj == NULL_TAG ) return false ;
	//if( UF_ASSEM_is_occurrence( obj )) {
		//obj = UF_ASSEM_ask_prototype_of_occ ( obj ) ;
   // }

	ret = UF_ATTR_read_value( obj, title, UF_ATTR_any, &value );
	if( value.type == UF_ATTR_string ) 
	{
        strcpy( string , value.value.string ) ;
//		USER_remove_space( string ) ;//除掉字符串两端的空格
        UF_free(value.value.string) ;
	}
	else 
		return false ;
	return true ;
}  

bool TYCOM_GetObjectHasAttribute( const tag_t obj , char *title )
{
	UF_ATTR_value_t  value ;
    int		ret;
	if( obj == NULL_TAG ) 
        return false ;
    tag_t object = obj;
	if( UF_ASSEM_is_occurrence( obj )) 
    {
		object = UF_ASSEM_ask_prototype_of_occ ( obj ) ;
    }
	ret = UF_ATTR_read_value( object, title, UF_ATTR_any, &value );
	if( value.type == UF_ATTR_string ) 
	{
        UF_free(value.value.string) ;
        return true;
	}
    else 
        return false;
}

/***************************************************************************
   EF_ask_obj_integer_attr( tag_t obj , char *title , char *string 
   input:  obj,   object tag or part tag  
           title, attirbute title  
   output: integer_data,  integer data return 
***************************************************************************/
int EF_ask_obj_integer_attr( tag_t obj , char *title , int *integer_data )
{
	UF_ATTR_value_t  value ;
    
	if( obj == NULL_TAG ) return 1 ;

	if( UF_ASSEM_is_occurrence( obj )) 
	{
		obj = UF_ASSEM_ask_prototype_of_occ ( obj ) ;
    }
	
	UF_ATTR_read_value(obj, title, UF_ATTR_any, &value);
	if( value.type == UF_ATTR_integer )
	{
        *integer_data = value.value.integer ;
	}
	else 
		return 2 ;
	return 0 ;
} 

int EF_ask_obj_integer_attr_Ori( tag_t obj , char *title , int *integer_data )
{
	UF_ATTR_value_t  value ;
    
	if( obj == NULL_TAG ) return 1 ;
	
	UF_ATTR_read_value(obj, title, UF_ATTR_any, &value);
	if( value.type == UF_ATTR_integer )
	{
        *integer_data = value.value.integer ;
	}
	else 
		return 2 ;
	return 0 ;
} 
 
/***************************************************************************
   EF_ask_obj_real_attr( tag_t obj , char *title , char *string 
   input:  obj,   object tag or part tag  
           title, attirbute title  
   output: real_data,  real data return 
***************************************************************************/
int EF_ask_obj_real_attr( tag_t obj , char *title , double *real_data )
{
	UF_ATTR_value_t  value ;
    
	if( obj == NULL_TAG ) return false ;
	if( UF_ASSEM_is_occurrence( obj ) ){
		obj = UF_ASSEM_ask_prototype_of_occ ( obj ) ;
    }

	UF_ATTR_read_value(obj, title, UF_ATTR_any, &value);
	if( value.type == UF_ATTR_real ) {
        *real_data = value.value.real ;
	}
	else 
		return false ;
	return true ;
}  

int TYCOM_SetObjectAttributeLong(tag_t body, char *title, vNXString &values)
{
	/*int len = strlen(value);
	int  numSeg = len/(UF_ATTR_MAX_STRING_LEN-2);
	int curIndex = 0;
	for (int i = 0; i < numSeg; i++)
	{
		char thisStr[UF_ATTR_MAX_STRING_LEN-1] = "\0";
		for (int j = curIndex; j < curIndex+UF_ATTR_MAX_STRING_LEN-2 && j < len; j++)
		{
            thisStr[j-curIndex] = value[j];
			
		}
		curIndex+=UF_ATTR_MAX_STRING_LEN-2;
		thisStr[UF_ATTR_MAX_STRING_LEN-2] = '\0';

		char tempTitle[64] = "";
		sprintf_s(tempTitle, "%s_%d", title, i);
		TYCOM_SetObjectStringAttribute( body, tempTitle, thisStr );
	}*/

	for (int i = 0; i < values.size(); i++)
	{
		char tempTitle[64] = "";
		sprintf_s(tempTitle, "%s_%d", title, i);
		if (strlen(values[i].GetLocaleText()) < UF_ATTR_MAX_STRING_LEN)
		    TYCOM_SetObjectStringAttribute( body, tempTitle,  values[i].GetLocaleText());
		else
		{
			const char *tempValue = values[i].GetLocaleText();
			char thisStr[UF_ATTR_MAX_STRING_LEN-1] = "\0";
			for (int j = 0; j < UF_ATTR_MAX_STRING_LEN-2; j++)
			{
				thisStr[j] = tempValue[j];
			}
			thisStr[UF_ATTR_MAX_STRING_LEN-2] = '\0';
			 TYCOM_SetObjectStringAttribute( body, tempTitle,  thisStr);
		}
	}

	return 0;
}

int TYCOM_GetObjectAttributeLong(tag_t body, char *title, vNXString &values)
{
	char tempTitle[64] = "";

	int i = 0;
	while (1)
	{
		sprintf(tempTitle, "%s_%d", title, i++);
		if(TYCOM_GetObjectHasAttribute(body,tempTitle))
		{
			char str[UF_ATTR_MAX_STRING_LEN] = "";
			TYCOM_GetObjectStringAttribute(body, tempTitle,str);
			values.push_back(str);
		}
		else
			break;
	}

	return 0;
}

/*int TYCOM_set_obj_attr_Long2(tag_t obj, NXString title, NXString &value)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	tag_t obj_tag = obj;
	if( UF_ASSEM_is_occurrence( obj ))
	{
		obj_tag = UF_ASSEM_ask_prototype_of_occ ( obj ) ;
	}

	std::vector<NXOpen::NXObject *> objects1(1);

	NXObject* pobj = dynamic_cast<NXObject*> (NXObjectManager::Get(obj_tag));

	objects1[0] = pobj;

	NXOpen::AttributePropertiesBuilder *attributePropertiesBuilder1;
	attributePropertiesBuilder1 = theSession->AttributeManager()->CreateAttributePropertiesBuilder(workPart, objects1, NXOpen::AttributePropertiesBuilder::OperationTypeNone);

	attributePropertiesBuilder1->SetDataType(NXOpen::AttributePropertiesBaseBuilder::DataTypeOptionsString);

	attributePropertiesBuilder1->SetTitle(title);

	attributePropertiesBuilder1->SetStringValue(value);

	NXOpen::NXObject *nXObject1;
	nXObject1 = attributePropertiesBuilder1->Commit();

	NXOpen::Session::UndoMarkId id1;
	id1 = theSession->GetNewestUndoMark(NXOpen::Session::MarkVisibilityVisible);

	int nErrs1;
	nErrs1 = theSession->UpdateManager()->DoUpdate(id1);

	attributePropertiesBuilder1->Destroy();
	return 0;
}

int TYCOM_set_obj_attr_Long(tag_t obj, NXString title, NXString &value)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Part *displayPart(theSession->Parts()->Display());

	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(obj);
	NXObject* pbody = dynamic_cast<NXObject*> (tagobj);
	if(pbody == NULL)
		return -1;

	std::vector<NXOpen::NXObject *> objects1(1);
	objects1[0] = pbody;

	NXOpen::AttributePropertiesBuilder *attributePropertiesBuilder1;
	attributePropertiesBuilder1 = theSession->AttributeManager()->CreateAttributePropertiesBuilder(workPart, objects1, NXOpen::AttributePropertiesBuilder::OperationTypeNone);

	attributePropertiesBuilder1->SetArray(false);
	attributePropertiesBuilder1->SetDataType(NXOpen::AttributePropertiesBaseBuilder::DataTypeOptionsString);
	attributePropertiesBuilder1->SetUnits("MilliMeter");


	attributePropertiesBuilder1->SetTitle(title);
	attributePropertiesBuilder1->SetStringValue(value);

	attributePropertiesBuilder1->CreateAttribute();


	NXOpen::NXObject *nXObject1;
	nXObject1 = attributePropertiesBuilder1->Commit();
	//int nErrs1;
	//nErrs1 = theSession->UpdateManager()->DoUpdate(id1);

	attributePropertiesBuilder1->Destroy();

	return 0;
}*/
