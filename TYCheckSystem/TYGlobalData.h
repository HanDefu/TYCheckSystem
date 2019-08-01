#pragma once

#include "Common/TY_Def.h"

typedef struct SNameMaterial
{
	NXString m_nameFirst;
	NXString m_nameSecond;
	vNXString m_materials;
}SNameMaterial;
typedef std::vector<SNameMaterial> vSNameMaterial;


typedef struct SNameTech
{
	NXString m_nameFirst;
	NXString m_nameSecond;
	vNXString m_tech;
}SNameTech;
typedef std::vector<SNameTech> vSNameTech;


typedef struct SNameHeatProcess
{
	NXString m_nameFirst;
	NXString m_material;
	vNXString m_heatProcess;
}SNameHeatProcess;
typedef std::vector<SNameHeatProcess> vSNameHeatProcess;

typedef struct SNameSurfaceProcess
{
	NXString m_nameFirst;
	NXString m_material;
	vNXString m_surfaceProcess;
}SNameSurfaceProcess;
typedef std::vector<SNameSurfaceProcess> vSNameSurfaceProcess;

typedef struct SNameLayer
{
	NXString m_nameFirst;
	vNXString m_layer;
}SNameLayer;
typedef std::vector<SNameLayer> vSNameLayer;

typedef struct SMaterialDensity
{
	NXString m_material;
	NXString m_Density;
}SMaterialDensity;
typedef std::vector<SMaterialDensity> vSMaterialDensity;

class TYGlobalData 
{
public:
	static TYGlobalData *GetInstance()
	{
		static TYGlobalData instance;
		return &instance;
	}

	vNXString GetMaterial(int firstNameSel, int secondNameSel);
	vNXString GetMaterial(NXString firstName, NXString secondName);
	vNXString GetTechRequirement(int firstNameSel, int secondNameSel);
	vNXString GetTechRequirement(NXString firstName, NXString secondName);

	vNXString GetFaceProcess(int firstNameSel, int secondNameSel, int materialSel);
	vNXString GetFaceProcess(NXString firstName, NXString material);

	vNXString GetHeatProcess(int firstNameSel, int secondNameSel, int materialSel);
	vNXString GetHeatProcess(NXString firstName, NXString material);

	double GetDensity(NXString material);
	void GetDensity(NXString material, NXString &density);

	void Run();

	void ClearData();

private:
	TYGlobalData();
	~TYGlobalData();

	//读excel数据
	int GetPropertyExcelData();
public:

	vNXString m_nameFirst;//名称主类
	vvNXString m_nameSecond;//名称子类

	vSNameMaterial m_nameMaterial;//名称材料对照

	vSNameTech m_nameTech;//名称技术要求对照表

	vSNameHeatProcess m_nameHeatProcess;//客户热处理
	vSNameSurfaceProcess m_nameFaceProcess;//客户表面处理

	vSNameLayer m_nameLayer;
	vSMaterialDensity m_materialDensity;
	vNXString m_curlayers; 
};

#define TYGBDATA  (TYGlobalData::GetInstance())
