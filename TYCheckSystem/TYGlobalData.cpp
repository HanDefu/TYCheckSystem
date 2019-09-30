#include "TYGlobalData.h"
#include "Tool/Excel/BasicExcel.hpp"
#include "Common/Common_Function.h"
#include <uf_ui.h>

using namespace YExcel;

TYGlobalData::TYGlobalData()
{

}

TYGlobalData::~TYGlobalData()
{

}

void TYGlobalData::Run()
{
    GetPropertyExcelData();
}

int TYGlobalData::GetPropertyExcelData()
{
	//客户处理
	BasicExcel excel;
	// Load a workbook with one sheet, display its contents and save into another file.
	const char *env_name = "TY_DATA_DIR";
	char file_name[TY_STR_LEN] = "";
	strcpy(file_name, getenv(env_name));
	strcat(file_name,"\\Parameter\\TY中文Property.xls");

	bool isOk = excel.Load(file_name);	
	if (!isOk)
	{
		uc1601("加载数据文件失败，请检测",1);
		return -1;
	}
	/*BasicExcelWorksheet* sheet1 = excel.GetWorksheet(L"客户表");
	if (sheet1)
	{
		size_t maxRows = sheet1->GetTotalRows();
		for(int i = 1; i < maxRows; i++)
		{
			BasicExcelCell *cel = sheet1->Cell(i,1);
			const wchar_t* aa = cel->GetWString();
			m_customers.push_back(NXString(WCHARTOCHAR(aa)));
		}
	}*/

	//名称处理
	BasicExcelWorksheet* sheet2 = excel.GetWorksheet(L"名称分类表");
	if (sheet2)
	{
		size_t maxCols = sheet2->GetTotalCols();
		for(int i = 0; i < maxCols; i++)
		{
			vNXString strs;
			bool finish = false;
			for(int j = 0; j < 65535; j++)
			{
				if(j == 0)
				{
					BasicExcelCell *cel = sheet2->Cell(j,i);
					std::string stt = cel->Get();
				    const char* aa = stt.c_str();
					if(strlen(aa) == 0)
					{
						finish = true;
						break;
					}
					m_nameTypes.push_back(NXString(aa));
				}
				else
				{
					BasicExcelCell *cel = sheet2->Cell(j,i);
					const wchar_t* aa = cel->GetWString();
					if(aa == 0)
						break;
					strs.push_back(NXString(WCHARTOCHAR(aa)));
				}
			}
			if(finish)
				break;
			m_names.push_back(strs);
		}
	}


	//材料表
	BasicExcelWorksheet* sheet3 = excel.GetWorksheet(L"名称材料对照表");
	if (sheet3)
	{
		size_t maxRows = sheet3->GetTotalRows();
		for(int i = 0; i < maxRows; i++)
		{
			SNameMaterial nm;
			bool finish = false;
			for(int j = 0; j < 65535; j++)
			{
				BasicExcelCell *cel = sheet3->Cell(i,j);
				std::string stt = cel->Get();
				const char* aa = stt.c_str();
				if(strlen(aa) == 0)
				{
					if(j == 0)
						finish = true;
					break;
				}

				if(aa != 0)
				{
					if(j == 0)
					{
						nm.m_nameFirst = NXString(aa);
					}
					else if(j == 1)
					{
						nm.m_nameSecond = NXString(aa);
					}
					else
					{
						nm.m_materials.push_back(NXString(aa));
					}
					continue;
				}
			}

			if(finish)
				break;
			m_nameMaterial.push_back(nm);
		}
	}

	//技术要求表
	BasicExcelWorksheet* sheet4 = excel.GetWorksheet(L"名称技术要求对照表");
	if (sheet4)
	{
		size_t maxRows = sheet4->GetTotalRows();
		for(int i = 0; i < maxRows; i++)
		{
			SNameTech nt;
			bool finish = false;
			for(int j = 0; j < 65535; j++)
			{
				BasicExcelCell *cel = sheet4->Cell(i,j);
				std::string stt = cel->Get();
				const char* aa = stt.c_str();
				if(strlen(aa) == 0)
				{
					if(j == 0)
						finish = true;
					break;
				}
				if(aa != 0)
				{
					if(j == 0)
					{
						nt.m_nameFirst = NXString(aa);
					}
					else if(j == 1)
					{
						nt.m_nameSecond = NXString(aa);
					}
					else
					{
						nt.m_tech.push_back(NXString(aa));
					}
					continue;
				}
				break;
			}
			if(finish)
				break;
			m_nameTech.push_back(nt);
		}
	}
	//热处理表
	BasicExcelWorksheet* sheet5 = excel.GetWorksheet(L"名称材料热处理对照表");
	if (sheet5)
	{
		size_t maxRows = sheet5->GetTotalRows();
		for(int i = 0; i < maxRows; i++)
		{
			SNameHeatProcess vhp;
			bool finish = false;
			for(int j = 0; j < 65535; j++)
			{
				BasicExcelCell *cel = sheet5->Cell(i,j);
				std::string stt = cel->Get();
				const char* aa = stt.c_str();
				if(strlen(aa) == 0)
				{
					if(j == 0)
						finish = true;
					break;
				}

				if(aa != 0)
				{
					if(j == 0)
					{
						vhp.m_nameFirst = NXString(aa);
					}
					else if(j == 1)
					{
						vhp.m_material = NXString(aa);
					}
					else
					{
						vhp.m_heatProcess.push_back(NXString(aa));
					}
					continue;
				}
			}
			if(finish)
				break;
			m_customerHeatProcess.push_back(vhp);
		}
	}
	//表面处理表
	BasicExcelWorksheet* sheet6 = excel.GetWorksheet(L"名称材料表面处理对照表");
	if (sheet6)
	{
		size_t maxRows = sheet6->GetTotalRows();
		for(int i = 0; i < maxRows; i++)
		{
			SNameSurfaceProcess nsp;
			bool finish = false;
			for(int j = 0; j < 65535; j++)
			{
				BasicExcelCell *cel = sheet6->Cell(i,j);
				std::string stt = cel->Get();
				const char* aa = stt.c_str();
				if(strlen(aa) == 0)
				{
					if(j == 0)
						finish = true;
					break;
				}
				if(aa != 0)
				{
					if(j == 0)
					{
						nsp.m_nameFirst = NXString(aa);
					}
					else if(j == 1)
					{
						nsp.m_material = NXString(aa);
					}
					else
					{
						nsp.m_surfaceProcess.push_back(NXString(aa));
					}
					continue;
				}
			}
			if(finish)
				break;
			m_customerFaceProcess.push_back(nsp);
		}
	}

	//图层表
	BasicExcelWorksheet* sheet7 = excel.GetWorksheet(L"图层表");
	if (sheet7)
	{
		size_t maxRows = sheet7->GetTotalRows();
		for(int i = 0; i < maxRows; i++)
		{
			SNameLayer nl;
			BasicExcelCell *cel1 = sheet7->Cell(i,0);
			BasicExcelCell *cel2 = sheet7->Cell(i,1);
			std::string stt = cel1->Get();
			const char* aa = stt.c_str();
			if(strlen(aa) == 0)
			{
				break;
			}


			nl.m_nameFirst = NXString(aa);
			std::string stt2 = cel2->Get();

			int numStr = 0;
			char *strs[32] = {0};
			for(int j = 0; j < 32; j++)
				strs[j] = new char[8];
			char inputstr[128] = "";
			strcpy(inputstr,stt2.c_str());
			TYCOM_TXT_SplitToStrs(inputstr, ",", strs, numStr);
			

			for(int j = 0; j < numStr; j++)
			    nl.m_layer.push_back(NXString(strs[j]));

			for(int j = 0; j < 32; j++)
				delete strs[j];

			m_nameLayer.push_back(nl);
		}
	}

	//密度表
	BasicExcelWorksheet* sheet8 = excel.GetWorksheet(L"密度表");
	if (sheet8)
	{
		size_t maxRows = sheet8->GetTotalRows();
		for(int i = 0; i < maxRows; i++)
		{
			SMaterialDensity md;
			BasicExcelCell *cel1 = sheet8->Cell(i,0);
			BasicExcelCell *cel2 = sheet8->Cell(i,1);
			std::string stt = cel1->Get();
			const char* aa = stt.c_str();
			if(strlen(aa) == 0)
			{
				break;
			}

			md.m_material = NXString(aa);
			std::string stt2 = cel2->Get();
			md.m_Density = NXString(stt2.c_str());
			m_materialDensity.push_back(md);
		}
	}
	return 0;
}