#include "Com_Export.h"
#include <uf_obj.h>
#include <NXOpen/Session.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Step203Creator.hxx>
#include <NXOpen/Step203Importer.hxx>
#include <NXOpen/Step214Creator.hxx>
#include <NXOpen/Step214Importer.hxx>
#include <NXOpen/IgesCreator.hxx>
#include <NXOpen/IgesImporter.hxx>
#include <NXOpen/STLImporter.hxx>
#include <NXOpen/STLImporter.hxx>
#include <NXOpen/DexManager.hxx>
#include <NXOpen/NXObjectManager.hxx>
#include <NXOpen/Body.hxx>
#include <NXOpen/SelectNXObjectList.hxx>
#include <uf_part.h>

using namespace NXOpen;

//导出当前workpart的一个实体
int TYCOM_Export_step203(vtag_t &bodies, NXString fileName)
{
	if (bodies.size() == 0)
		return -1;

	if (fileName.getLocaleText() == 0 || strlen(fileName.getLocaleText()) == 0)
		return -1;

	std::vector<NXOpen::NXObject *> pbodies;
	for (int i = 0; i < bodies.size(); i++)
	{
		TaggedObject * tagobj = NXOpen::NXObjectManager::Get(bodies[i]);
		Body * temp =  dynamic_cast<Body*> (tagobj);
		if(temp != NULL)
		{
            pbodies.push_back(temp);
		}
	}

	if (pbodies.size() == 0)
		return -1;

	Session *theSession = Session::GetSession();

	char file_name[_MAX_FNAME] = "";
	UF_PART_ask_part_name (UF_PART_ask_display_part(), file_name );


	Step203Creator *step203Creator1;
	step203Creator1 = theSession->DexManager()->CreateStep203Creator();

	step203Creator1->SetOutputFile(fileName);

	//step203Creator1->SetSettingsFile("C:\\Program Files\\UGS\\NX 7.0\\step203ug\\ugstep203.def");

	step203Creator1->ExportSelectionBlock()->SetSelectionScope(ObjectSelector::ScopeSelectedObjects);

	step203Creator1->ObjectTypes()->SetSolids(true);

	step203Creator1->ExportSelectionBlock()->SetSelectionScope(ObjectSelector::ScopeEntirePart);

	step203Creator1->SetInputFile(file_name);


	bool added1 = step203Creator1->ExportSelectionBlock()->SelectionComp()->Add(pbodies);

	step203Creator1->SetColorAndLayers(true);
	step203Creator1->SetFileSaveFlag(false);
	step203Creator1->SetLayerMask("1-256");

	step203Creator1->SetUserCredential("", "", "");

	NXObject *nXObject1;
	nXObject1 = step203Creator1->Commit();

	step203Creator1->Destroy();
	return 0;
}

int TYCOM_Export_step203(vtag_t &bodys, vNXString &filenames)
{
	if (bodys.size() != filenames.size())
		return false;
	
	for (int i = 0; i < bodys.size(); i++)
	{
		vtag_t tempBodies;
		tempBodies.push_back(bodys[i]);
        TYCOM_Export_step203(tempBodies, filenames[i]);
	}
	return 0;
}
