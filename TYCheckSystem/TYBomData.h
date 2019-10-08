#pragma once
#include <uf_defs.h>
#include <NXOpen/NXString.hxx>
#include <vector>

using namespace NXOpen;

class TYBomData
{
public:
	TYBomData(tag_t body);
	~TYBomData();
	int FromBody(tag_t body);

	static void SetProjectNo(NXString no){m_projectNo = no;}

public:
	NXString m_index;
	NXString m_firstName;
	NXString m_secondName;
	NXString m_material;
	NXString m_size;
	NXString m_count;
	NXString m_description;
	NXString m_addDescription;
	NXString m_heatProcess;
	NXString m_faceProcess;
	NXString m_station;
	NXString m_level;
	NXString m_tyoe;


	static NXString m_projectNo;//DetailÒ»À¸µÄ×Ü±àºÅ
};

typedef std::vector<TYBomData> vTYBomData;