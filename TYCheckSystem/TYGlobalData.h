#pragma once

#include "TY_Def.h"

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

	void Run();

private:
	TYGlobalData();
	~TYGlobalData();

	//��excel����
	int GetPropertyExcelData();
public:

	vNXString m_nameTypes;//�������1 First
	vvNXString m_names;//�������2 Second

	vSNameMaterial m_nameMaterial;//���Ʋ��϶���

	vSNameTech m_nameTech;//���Ƽ���Ҫ����ձ�

	vSNameHeatProcess m_customerHeatProcess;//�ͻ��ȴ���
	vSNameSurfaceProcess m_customerFaceProcess;//�ͻ����洦��

	vSNameLayer m_nameLayer;
	vSMaterialDensity m_materialDensity;
	vNXString m_curlayers; 
};

#define TYGBDATA  (TYGlobalData::GetInstance())
