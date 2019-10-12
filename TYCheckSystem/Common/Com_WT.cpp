#include "Com_WT.h"
#include "Com_Attribute.h"


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