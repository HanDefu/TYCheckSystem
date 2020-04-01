#include "TYHoleData.h"
#include "../common\TY_Def.h"
#include "../Common\Com_UG.h"
#include "../Common\Com_Attribute.h"
#include "../Tool/Excel/BasicExcel.hpp"

using namespace YExcel;


TYHoleData::TYHoleData()
{
   Read();
}

TYHoleData::~TYHoleData()
{

}

bool TYHoleData::GetHole(double oriDia, double &newDia, double& depth, double &chenTouDia)
{
	double ndia = 0;
	logical found = false;

	for( int i = 0; i < m_holdRecords.size(); i++)
	{
		if( abs(m_holdRecords[i].m_oriDia - oriDia)< TOL0254  )
		{
			found = true;
			newDia = m_holdRecords[i].m_newDia;
			depth = m_holdRecords[i].m_depth;
			chenTouDia =  m_holdRecords[i].m_chenTouDia;
			break;
		}
	}
	
	return found;
}

bool TYHoleData::GetTHole(double oriDia, double &newDia, double& depth)
{
	double ndia = 0;
	logical found = false;

	for( int i = 0; i < m_holdTRecords.size(); i++)
	{
		if( abs(m_holdTRecords[i].m_oriDia - oriDia)< TOL0254  )
		{
			found = true;
			newDia = m_holdTRecords[i].m_newDia;
			depth = m_holdTRecords[i].m_depth;
			break;
		}
	}

	return found;
}

int TYHoleData::Read()
{
	char *p_env = getenv("TY_DATA_DIR");
	char filePathName[MAX_FSPEC_SIZE]="";
	sprintf(filePathName,"%s\\Parameter\\TYHole.xls",p_env);

	double ndia = 0;
	logical found = false;
	YExcel::BasicExcel excel;
	bool isOk = excel.Load(filePathName);
	if( !isOk )
		return -1;

	YExcel::BasicExcelWorksheet* sheet1 = excel.GetWorksheet(L"³ÁÍ·¿×");
	if (sheet1 == 0)
		return -1;

	SHoleRecord oneRecord;
	size_t maxRows = sheet1->GetTotalRows();
	for( int i = 1; i < maxRows; i++)
	{
		
		YExcel::BasicExcelCell *cel = sheet1->Cell(i,0);
		oneRecord.m_oriDia = cel->GetDouble();
		cel = sheet1->Cell(i,1);
		oneRecord.m_newDia = cel->GetDouble();
		cel = sheet1->Cell(i,2);
		oneRecord.m_depth = cel->GetDouble();
		cel = sheet1->Cell(i,3);
		oneRecord.m_chenTouDia = cel->GetDouble();
		m_holdRecords.push_back(oneRecord);
	}


	YExcel::BasicExcelWorksheet* sheet2 = excel.GetWorksheet(L"Í¨¿×");
	if (sheet2 == 0)
		return -1;

	maxRows = sheet2->GetTotalRows();
	for( int i = 1; i < maxRows; i++)
	{

		YExcel::BasicExcelCell *cel = sheet2->Cell(i,0);
		oneRecord.m_oriDia = cel->GetDouble();
		cel = sheet2->Cell(i,1);
		oneRecord.m_newDia = cel->GetDouble();
		cel = sheet2->Cell(i,2);
		oneRecord.m_depth = cel->GetDouble();
		m_holdTRecords.push_back(oneRecord);
	}

    return 0;
}