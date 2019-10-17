#pragma once
#include <uf_defs.h>
#include <NXOpen/NXString.hxx>
#include <vector>

using namespace NXOpen;

typedef struct HoleRecord
{
	HoleRecord(): m_oriDia(0),m_newDia(0),m_depth(0){}
	double m_oriDia;
	double m_newDia;
	double m_depth;
}SHoleRecord;

typedef std::vector<SHoleRecord> vSHoleRecord;

class TYHoleData
{
public:

	static TYHoleData *GetInstance()
	{
		static TYHoleData instance;
		return &instance;
	}

private:
	TYHoleData();
	~TYHoleData();
public:
	bool GetHole(double oriDia, double &newDia, double& depth);
	int Read();
public:
    vSHoleRecord m_holdRecords;
};

typedef std::vector<TYHoleData> vTYHoleData;

#define TYHOLEDATA  (TYHoleData::GetInstance())