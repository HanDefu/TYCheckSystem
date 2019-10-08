#include "TYBomData.h"
#include "common\TY_Def.h"
#include "Common\Com_UG.h"
#include "Common\Com_Attribute.h"

TYBomData::TYBomData(tag_t body)
{
    FromBody(body);
}

TYBomData::~TYBomData()
{

}

int TYBomData::FromBody(tag_t body)
{
	if (body == 0)
		return -1;
	
	TYCOM_GetObjectStringAttribute( body, ATTR_TYCOM_PROPERTY_SOLID_NAME, m_firstName);
	TYCOM_GetObjectStringAttribute( body, ATTR_TYCOM_PROPERTY_SOLID_NAME2, m_secondName);
	TYCOM_GetObjectStringAttribute( body, ATTR_TYCOM_PROPERTY_MATERIAL, m_material);
	TYCOM_GetObjectStringAttribute( body, ATTR_TYCOM_PROPERTY_HEAT_PROCESS, m_heatProcess);
	TYCOM_GetObjectStringAttribute( body, ATTR_TYCOM_PROPERTY_FACE_PROCESS, m_faceProcess);



	double xLen = 0,yLen = 0,zLen = 0;
	int ret = TY_GetBodyXYZLen_aligned(body,  xLen, yLen, zLen);
	char str[128] = "";
	sprintf(str, "%dX%dX%d", (int)xLen + 1, (int)yLen + 1, (int)zLen + 1);
    m_size = str;

	m_count = "1";

    return 0;
}