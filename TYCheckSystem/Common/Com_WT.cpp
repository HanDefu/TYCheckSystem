#include "Com_WT.h"
#include "Com_Attribute.h"
#include <algorithm>


int TYCOM_GetMaxProperyIndex(vtag_t &bodies)
{
	int maxIndex = 0;
	int ret = 0;
   for (int i = 0; i < bodies.size(); i++)
   {
	   int indexProperty = 0;
	   ret = EF_ask_obj_integer_attr( bodies[i] , ATTR_TYCOM_PROPERTY_INDEX , &indexProperty );
	   if (ret == 0 && indexProperty > maxIndex)
	   {
		   maxIndex = indexProperty;
	   }
   }
   return maxIndex;
}


static logical CompareBodyByPropertyIndex(tag_t &body1, tag_t &body2)
{
	int indexProperty1 = 0, indexProperty2 = 0;
	int ret1 = EF_ask_obj_integer_attr( body1 , ATTR_TYCOM_PROPERTY_INDEX , &indexProperty1 );
	int ret2 = EF_ask_obj_integer_attr( body2 , ATTR_TYCOM_PROPERTY_INDEX , &indexProperty2 );
	if (ret1 == 0 && ret2 == 0)
		return indexProperty1 < indexProperty2;

	if (ret1 == 0 && ret2 != 0)
		return true;

	if (ret1 != 0 && ret2 == 0)
		return false;

	return false;
}

int TYCOM_SortBodiesByPropertyIndex(vtag_t &bomBodies)
{
	std::sort(bomBodies.begin(),bomBodies.end(),CompareBodyByPropertyIndex);   
	return 0;
}

bool TYCOM_isSameBody(tag_t body1, tag_t body2)
{

	if(body1 == 0 || body2 == 0)
		return false;

	char attriValue1[128] = "";
	char attriValue2[128] = "";
	int has1 = TYCOM_GetObjectStringAttribute( body1 , ATTR_TY_SAME_BODY , attriValue1 );
	if(!has1)
		return false;

	int has2 = TYCOM_GetObjectStringAttribute( body2 , ATTR_TY_SAME_BODY , attriValue2 );
	if(!has2)
		return false;

	if(strcmp(attriValue1, attriValue2) == 0)
			return true;
	return false;
}

int TYCOM_GetSameBodiesForOneBody(tag_t seedBody, vtag_t& allBodies, vtag_t &sameBodies)
{
	if(seedBody == 0)
		return -1;

	char attriValue[128] = "";
	int has = TYCOM_GetObjectStringAttribute( seedBody , ATTR_TY_SAME_BODY , attriValue );
	if(!has)
		return -2;

	for(int i = 0; i < allBodies.size(); i++)
	{
		if(allBodies[i] == seedBody)
			continue;

		char attriValue2[128] = "";
		int has2 = TYCOM_GetObjectStringAttribute( allBodies[i] , ATTR_TY_SAME_BODY , attriValue2 );
		if(!has2)
			continue;

		if(strcmp(attriValue, attriValue2) == 0)
			sameBodies.push_back(allBodies[i]);
	}

	return 0;
}
