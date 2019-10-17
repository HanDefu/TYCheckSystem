#include "TYGlobalData.h"
#include "../Tool/Excel/BasicExcel.hpp"
#include "../Common/Com.h"
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
	char * env = getenv(env_name);
	strcpy(file_name, env);
	strcat(file_name, "\\Parameter\\TYProperty.xls");

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
					m_nameFirst.push_back(NXString(aa));
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
			m_nameSecond.push_back(strs);
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
			m_nameHeatProcess.push_back(vhp);
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
			m_nameFaceProcess.push_back(nsp);
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

vNXString TYGlobalData::GetMaterial(int firstNameSel, int secondNameSel)
{
	vNXString strs;

	if (firstNameSel > m_nameFirst.size())
		return strs;

	//处理材料表
	NXString first, second;
	first = m_nameFirst[firstNameSel];

	if (secondNameSel > m_nameSecond[firstNameSel].size())
		return strs;

	second = m_nameSecond[firstNameSel][secondNameSel];

	for(int i = 0; i < m_nameMaterial.size(); i++)
	{
		if(strcmp(m_nameMaterial[i].m_nameFirst.GetText(), first.GetText()) == 0 && 
			strcmp(m_nameMaterial[i].m_nameSecond.GetText(), second.GetText()) == 0)
		{
			return m_nameMaterial[i].m_materials;
		}
	}
	return strs;
}

vNXString TYGlobalData::GetMaterial(NXString firstName, NXString secondName)
{
	vNXString strs;

	for(int i = 0; i < m_nameMaterial.size(); i++)
	{
		if(strcmp(m_nameMaterial[i].m_nameFirst.GetText(), firstName.GetText()) == 0 && 
			strcmp(m_nameMaterial[i].m_nameSecond.GetText(), secondName.GetText()) == 0)
		{
			return m_nameMaterial[i].m_materials;
		}
	}
	return strs;
}


vNXString TYGlobalData::GetTechRequirement(int firstNameSel, int secondNameSel)
{
	vNXString strs;

	if (firstNameSel > m_nameFirst.size())
		return strs;

	//处理材料表
	NXString first, second;
	first = m_nameFirst[firstNameSel];

	if (secondNameSel > m_nameSecond[firstNameSel].size())
		return strs;

	second = m_nameSecond[firstNameSel][secondNameSel];

	for(int i = 0; i < m_nameTech.size(); i++)
	{
		if(strcmp(m_nameTech[i].m_nameFirst.GetLocaleText(), first.GetLocaleText()) == 0 && 
			strcmp(m_nameTech[i].m_nameSecond.GetLocaleText(), second.GetLocaleText()) == 0)
		{
			return m_nameTech[i].m_tech;
		}
	}
	return strs;
}

vNXString TYGlobalData::GetTechRequirement(NXString firstName, NXString secondName)
{
	vNXString strs;


	for(int i = 0; i < m_nameTech.size(); i++)
	{
		if(strcmp(m_nameTech[i].m_nameFirst.GetLocaleText(), firstName.GetLocaleText()) == 0 && 
			strcmp(m_nameTech[i].m_nameSecond.GetLocaleText(), secondName.GetLocaleText()) == 0)
		{
			return m_nameTech[i].m_tech;
		}
	}
	return strs;
}


vNXString TYGlobalData::GetHeatProcess(int firstNameSel, int secondNameSel, int materialSel)
{
	vNXString strs;

	if (firstNameSel > m_nameFirst.size())
		return strs;

	//处理材料表
	NXString firstName, material;
	firstName = m_nameFirst[firstNameSel];

	vNXString materials =  GetMaterial(firstNameSel, secondNameSel);

	if (materials.size() <= materialSel)
	{
		return strs;
	}

	material = materials[materialSel];

	for(int i = 0; i < m_nameHeatProcess.size(); i++)
	{
		if(strcmp(m_nameHeatProcess[i].m_nameFirst.GetLocaleText(), firstName.GetLocaleText()) == 0 && 
			strcmp(m_nameHeatProcess[i].m_material.GetLocaleText(), material.GetLocaleText()) == 0)
		{
			return m_nameHeatProcess[i].m_heatProcess;
		}
	}
	return strs;
}

vNXString TYGlobalData::GetHeatProcess(NXString firstName, NXString material)
{
	vNXString strs;

	for(int i = 0; i < m_nameHeatProcess.size(); i++)
	{
		if(strcmp(m_nameHeatProcess[i].m_nameFirst.GetLocaleText(), firstName.GetLocaleText()) == 0 && 
			strcmp(m_nameHeatProcess[i].m_material.GetLocaleText(), material.GetLocaleText()) == 0)
		{
			return m_nameHeatProcess[i].m_heatProcess;
		}
	}
	return strs;
}


vNXString TYGlobalData::GetFaceProcess(int firstNameSel, int secondNameSel, int materialSel)
{
	vNXString strs;

	if (firstNameSel > m_nameFirst.size())
		return strs;

	//处理材料表
	NXString firstName, material;
	firstName = m_nameFirst[firstNameSel];

	vNXString materials =  GetMaterial(firstNameSel, secondNameSel);

	if (materials.size() <= materialSel)
	{
		return strs;
	}

	material = materials[materialSel];

	for(int i = 0; i < m_nameFaceProcess.size(); i++)
	{
		if(strcmp(m_nameFaceProcess[i].m_nameFirst.GetLocaleText(), firstName.GetLocaleText()) == 0 && 
			strcmp(m_nameFaceProcess[i].m_material.GetLocaleText(), material.GetLocaleText()) == 0)
		{
			return m_nameFaceProcess[i].m_surfaceProcess;
		}
	}
	return strs;
}

vNXString TYGlobalData::GetFaceProcess(NXString firstName, NXString material)
{
	vNXString strs;

	for(int i = 0; i < m_nameFaceProcess.size(); i++)
	{
		if(strcmp(m_nameFaceProcess[i].m_nameFirst.GetLocaleText(), firstName.GetLocaleText()) == 0 && 
			strcmp(m_nameFaceProcess[i].m_material.GetLocaleText(), material.GetLocaleText()) == 0)
		{
			return m_nameFaceProcess[i].m_surfaceProcess;
		}
	}
	return strs;
}

double TYGlobalData::GetDensity(NXString material)
{
	//从材料读到密度
	NXString strDensi; 
	for(int i = 0; i < m_materialDensity.size(); i++)
	{
		if(strcmp(m_materialDensity[i].m_material.GetLocaleText(), material.GetLocaleText()) == 0)
		{
			strDensi = m_materialDensity[i].m_Density;
			return atof(strDensi.GetLocaleText());
		}
	}

	return 0;
}

void  TYGlobalData::GetDensity(NXString material, NXString &density)
{
	//从材料读到密度
	NXString strDensi; 
	for(int i = 0; i < m_materialDensity.size(); i++)
	{
		if(strcmp(m_materialDensity[i].m_material.GetLocaleText(), material.GetLocaleText()) == 0)
		{
			density = m_materialDensity[i].m_Density;
			return;
		}
	}
}

void TYGlobalData::ClearData()
{
	m_nameFirst.clear();
	m_nameSecond.clear();
	m_nameMaterial.clear();
	m_nameTech.clear();
	m_nameHeatProcess.clear();
	m_nameFaceProcess.clear();
}