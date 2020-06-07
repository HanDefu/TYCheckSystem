#pragma once
#include "TY_Def.h"

//得到目前最大的属性编号
int TYCOM_GetMaxProperyIndex(vtag_t &bodies);
int TYCOM_SortBodiesByPropertyIndex(vtag_t &bomBodies);
int TYCOM_GetSameBodiesForOneBody(tag_t seedBody, vtag_t& allBodies, vtag_t &sameBodies);
bool TYCOM_isSameBody(tag_t body1, tag_t body2);