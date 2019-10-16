#include "Com_Draft2.h"
#include <NXOpen/NXString.hxx>
#include <NXOpen/Section.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <uf_cfi.h>
#include <NXOpen/DxfdwgCreator.hxx>
#include <NXOpen/DexManager.hxx>
#include <uf_part.h>
#include <uf_assem.h>
#include <uf_obj.h>
#include <uf.h>
#include "../Common/TY_Def.h"
#include "../Common/Com_Attribute.h"
#include <uf_modl.h>
#include <uf_vec.h>
#include <NXOpen/Drawings_BaseView.hxx>
#include <NXOpen/Drawings_BaseViewBuilder.hxx>
#include <NXOpen/Drawings_DraftingViewCollection.hxx>
#include <NXOpen/NXObjectManager.hxx>
#include <NXOpen/ModelingViewCollection.hxx>
#include <NXOpen/ModelingView.hxx>
#include <NXOpen/DirectionCollection.hxx>
#include <NXOpen/Drawings_SelectDraftingView.hxx>
#include <NXOpen/ViewCollection.hxx>
#include <uf_view.h>
#include <NXOpen/Drawings_ProjectedView.hxx>
#include <uf_draw.h>
#include <NXOpen/Drawings_DrawingSheetCollection.hxx>
#include <NXOpen/Drawings_DrawingSheetBuilder.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Point.hxx>
#include "Com_UG.h"
#include <NXOpen/Annotations_Dimension.hxx>
#include <NXOpen/Annotations_RadialStyleBuilder.hxx>
#include <uf_csys.h>
#include <uf_view.h>
#include <NXOpen/Annotations_Note.hxx>
#include <NXOpen/Annotations_DraftingNoteBuilder.hxx>
#include <NXOpen/Annotations_AnnotationManager.hxx>
#include "Com_UG.h"
#include<uf_group.h>
#include <algorithm>

using namespace NXOpen;

static void export_sheet_to_acad_dwg2d2( char* inputfile, char* outputfile, NXString& drawingName )
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Part *displayPart(theSession->Parts()->Display());

	int status = 0;
	UF_CFI_ask_file_exist(outputfile,&status);
	if( 0 == status )
	{
		uc4561(outputfile,0);
	}
	char *p_env;
	char dwgdef[MAX_FSPEC_SIZE];
	p_env = getenv("UGII_USER_DIR");
	strcpy(dwgdef,p_env);
	strcat(dwgdef,"\\application\\dxfdwg.def");

    ///////////////////////////////////////////////
	NXTo2dCreator *nXTo2dCreator1;
	nXTo2dCreator1 = theSession->DexManager()->CreateNxto2dCreator();

	nXTo2dCreator1->SetMaxSystem3DModelSpace(true);

	nXTo2dCreator1->SetMaxSystemPointRes(true);

	nXTo2dCreator1->SetSpCurveTolerance(0.0508);

	nXTo2dCreator1->SetMaxUser3DModelSpace(10000.0);

	nXTo2dCreator1->SetMaxUserPointRes(0.001);

	nXTo2dCreator1->SetOutputFileType(NXTo2dCreator::OutputAsOptionDWGFile);

	nXTo2dCreator1->SetOutputFile(outputfile);

	//nXTo2dCreator1->SetNxto2dSettingsFile("C:\\Program Files (x86)\\UGS\\NX 7.0\\ugto2d\\ugto2d.def");

	nXTo2dCreator1->SetDxfSettingsFile(dwgdef);

	nXTo2dCreator1->SetExportData(NXTo2dCreator::ExportDataOptionDrawing);

	nXTo2dCreator1->SetFacetBodies(true);

	nXTo2dCreator1->SetAutoCADRevision(NXTo2dCreator::AutoCADRevisionOptionR2004);

	nXTo2dCreator1->SetInputFile(inputfile);

	nXTo2dCreator1->SetDrawingName("Sheet 1");

	nXTo2dCreator1->SetViewName("TOP");

	nXTo2dCreator1->SetUserCredential("", "", "");

	NXObject *nXObject1;
	nXObject1 = nXTo2dCreator1->Commit();

	nXTo2dCreator1->Destroy();

	int count = 0;
	UF_CFI_ask_file_exist(outputfile,&status);
	while( count < 300 && 1 == status)
	{
		_sleep(500);
		count++;
		UF_CFI_ask_file_exist(outputfile,&status);
	}
}


static void export_sheet_to_acad_dwg2d( char* inputfile, char* outputfile, NXString& drawingName )
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    NXOpen::Part *displayPart(theSession->Parts()->Display());

	int status = 0;
	UF_CFI_ask_file_exist(outputfile,&status);
	if( 0 == status )
	{
		uc4561(outputfile,0);
	}
	char *p_env;
    char dwgdef[MAX_FSPEC_SIZE];
    p_env = getenv("UGII_USER_DIR");
    strcpy(dwgdef,p_env);
    strcat(dwgdef,"\\application\\dxfdwg.def");
  
    NXOpen::DxfdwgCreator *dxfdwgCreator1;
    dxfdwgCreator1 = theSession->DexManager()->CreateDxfdwgCreator();
    
    //dxfdwgCreator1->SetExportData(NXOpen::DxfdwgCreator::ExportDataOptionDrawing);
    
    dxfdwgCreator1->SetAutoCADRevision(NXOpen::DxfdwgCreator::AutoCADRevisionOptionsR2004);
    
    dxfdwgCreator1->SetViewEditMode(true);
    
    dxfdwgCreator1->SetFlattenAssembly(true);
    
    dxfdwgCreator1->ObjectTypes()->SetCurves(true);
    
    dxfdwgCreator1->ObjectTypes()->SetAnnotations(true);
    
    dxfdwgCreator1->ObjectTypes()->SetStructures(true);
    
    dxfdwgCreator1->SetFlattenAssembly(false);
    
    dxfdwgCreator1->SetSettingsFile(dwgdef);
    
    dxfdwgCreator1->SetOutputFileType(NXOpen::DxfdwgCreator::OutputFileTypeOptionDwg);
    
    dxfdwgCreator1->SetInputFile(inputfile);
    
    dxfdwgCreator1->SetOutputFile(outputfile);
    
    //dxfdwgCreator1->SetExportSplinesAs(NXOpen::DxfdwgCreator::ExportSplinesAsOptionsPolyline2D);
    
    //dxfdwgCreator1->SetTextFontMappingFile("C:\\Users\\ADMINI~1\\AppData\\Local\\Temp\\Admi0A188E06nlb3.txt");
    
   // dxfdwgCreator1->SetWidthFactorMode(NXOpen::DxfdwgCreator::WidthfactorMethodOptionsAutomaticCalculation);
    
    //dxfdwgCreator1->SetCrossHatchMappingFile("C:\\Users\\ADMINI~1\\AppData\\Local\\Temp\\Admi0A188E06nlb4.txt");
    
    //dxfdwgCreator1->SetLineFontMappingFile("C:\\Users\\ADMINI~1\\AppData\\Local\\Temp\\Admi0A188E06nlb5.txt");
    
    dxfdwgCreator1->SetLayerMask("1-256");
    
    dxfdwgCreator1->SetDrawingList( drawingName );
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = dxfdwgCreator1->Commit();
    
    dxfdwgCreator1->Destroy();
	int count = 0;
    UF_CFI_ask_file_exist(outputfile,&status);
    while( count < 300 && 1 == status)
    {
        _sleep(500);
        count++;
        UF_CFI_ask_file_exist(outputfile,&status);
    }
}

static tag_t  CreateDWGPart( )
{
	tag_t partTag = NULL_TAG;
	char sFilePath[UF_CFI_MAX_PATH_NAME_SIZE]="";
	char file_name[UF_CFI_MAX_PATH_NAME_SIZE]="";
	char fname[_MAX_FNAME];

	NXOpen::Session *theSession = NXOpen::Session::GetSession();

	tag_t disPart = UF_PART_ask_display_part();
	tag_t rootocc = UF_ASSEM_ask_root_part_occ(disPart);
	UF_PART_ask_part_name (disPart, file_name );
	char *p = strstr(file_name,".prt");
	if( p != NULL )
	{
		*p='\0';
	}
	char *p_env = getenv("UGII_USER_DIR");
	char srcspc[MAX_FSPEC_SIZE]="";
	char desspc[MAX_FSPEC_SIZE]="";
	sprintf(srcspc,"%s\\templates\\gz_dwg.prt",p_env);
	sprintf(desspc,"%s_dwg.prt",file_name);
	int status = uc4567( srcspc,desspc,UF_CFI_COPY_ALWAYS_REPLACE,0,2);
	UF_CFI_ask_file_exist(desspc,&status);
	if(0  == status )
	{
		UF_PART_load_status_t error_status;
		tag_t new_drawing_tag = NULL_TAG;
		UF_PART_open(desspc,&partTag, &error_status);
		//UF_ASSEM_set_work_part_quietly(partTag,&disPart);
		UF_PART_free_load_status(&error_status);
		if(partTag != NULL_TAG)
		{
			//theSession->ApplicationSwitchImmediate("UG_APP_DRAFTING");
		}
	}
	return partTag;
}

static tag_t GetReferencesetBody(tag_t part,NXString& refsetName)
{
	tag_t body = NULL_TAG;
	tag_t refset = NULL_TAG;
  	UF_OBJ_cycle_by_name_and_type(part, refsetName.GetLocaleText(),UF_reference_set_type, FALSE, &refset);
	if( refset != NULL_TAG )
	{
		int n_members = 0;
		tag_t * members = NULL;
		UF_ASSEM_ask_ref_set_members( refset , & n_members , & members ) ;
		for( int i = 0 ; i < n_members ; i ++ )
		{
			int type = 0, subtype = 0;
			UF_OBJ_ask_type_and_subtype( members[ i ] , & type , & subtype ) ;
			if (type == UF_solid_type && subtype == UF_solid_body_subtype &&
				UF_OBJ_ALIVE == UF_OBJ_ask_status( members[ i ] ) )
			{
				body = members[i];
			}
		}
		UF_free( members ) ;
	}
	return body;
}

static int GetTopViewProjectDirection( tag_t partTag, NXString& refset,double dir[3][3] )
{
	tag_t part = partTag;
	dir[0][0] = 1;
	dir[0][1] = 0;
	dir[0][2] = 0;
	dir[1][0] = 0;
	dir[1][1] = 1;
	dir[1][2] = 0;
	dir[2][0] = 0;
	dir[2][1] = 0;
	dir[2][2] = 1;
	if(UF_ASSEM_is_occurrence(partTag))
	{
		part = UF_ASSEM_ask_prototype_of_occ(partTag);
	}
	tag_t body = GetReferencesetBody(part,refset);
	if( NULL_TAG != body )
	{
		char VZx[133]="",VZy[133]="",VZz[133]="";
		char VXx[133]="",VXy[133]="",VXz[133]="";
		int irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_X_X,VZx);
		if( 1 == irc )
		{
			irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_X_Y,VZy);
		}
		if( 1 == irc )
		{
			irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_X_Z,VZz);
		}
		if( 1 == irc )
		{
			irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_Y_X,VXx);
		}
		if( 1 == irc )
		{
			irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_Y_Y,VXy);
		}
		if( 1 == irc )
		{
			irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_Y_Z,VXz);
		}
		if( 1 == irc )
		{
			dir[0][0] = atof(VZx);
			dir[0][1] = atof(VZy);
			dir[0][2] = atof(VZz);

			dir[1][0] = atof(VXx);
			dir[1][1] = atof(VXy);
			dir[1][2] = atof(VXz);
			double tol = 0;
			UF_MODL_ask_distance_tolerance(&tol);
			UF_VEC3_cross(dir[0], dir[1], dir[2]);
			/*UF_CALL(UF_VEC3_unitize(dir[0], tol, &mag, &csys[0]));
			UF_CALL(UF_VEC3_unitize(dir[1], tol, &mag, &csys[3]));
			UF_CALL(UF_VEC3_unitize(dir[2], tol, &mag, &csys[6]));*/
			return 0;
		}
	}
	return -1;
}

static tag_t CreateBaseView(tag_t partTag, NXString viewType, NXString& refset,Point3d& viewRefPoint, double stdscale,double sheetlen,double sheethei  )
{
	tag_t viewTag = NULL_TAG;

	NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    NXOpen::Drawings::BaseView *nullNXOpen_Drawings_BaseView(NULL);
    NXOpen::Drawings::BaseViewBuilder *baseViewBuilder1;
    baseViewBuilder1 = workPart->DraftingViews()->CreateBaseViewBuilder(nullNXOpen_Drawings_BaseView);
    
    //baseViewBuilder1->Placement()->SetAssociative(true);
    
    char part_fspec[MAX_FSPEC_SIZE+1] = "";
	tag_t part = partTag;
	if(UF_ASSEM_is_occurrence(partTag))
	{
		part = UF_ASSEM_ask_prototype_of_occ(partTag);
	}
    UF_PART_ask_part_name(part,part_fspec);

	Part *part1(dynamic_cast<Part *>(NXOpen::NXObjectManager::Get(part)));
    bool loadStatus1;
    loadStatus1 = part1->IsFullyLoaded();
	if( !loadStatus1 )
		part1->LoadFully();
    

	/*NXOpen::ModelingViewCollection * views = part1->ModelingViews();
	NXOpen::ModelingViewCollection::iterator it = views->begin();
	char name[133] = "";
    NXOpen::ModelingView * topView = 0;
	while (it!= views->end())
	{
		NXOpen::ModelingView * thisdata = *it;
		UF_OBJ_ask_name(thisdata->Tag(),name);
		if (strcmp(name,viewType.GetLocaleText()) == 0)
		{
			topView = *it;
			break;
		}

		it++;
	}*/

    NXOpen::ModelingView *modelingView2(dynamic_cast<NXOpen::ModelingView *>(part1->ModelingViews()->FindObject(viewType)));
    baseViewBuilder1->SelectModelView()->SetSelectedView(modelingView2);

	//baseViewBuilder1->SelectModelView()->SetSelectedView(modelingView2);
    
    NXOpen::Assemblies::Arrangement *nullNXOpen_Assemblies_Arrangement(NULL);
    baseViewBuilder1->Style()->ViewStyleBase()->Arrangement()->SetSelectedArrangement(nullNXOpen_Assemblies_Arrangement);
    
    baseViewBuilder1->Style()->ViewStyleBase()->SetPart(part1);
    
    baseViewBuilder1->Style()->ViewStyleBase()->SetPartName(NXString(part_fspec));
    
	NXOpen::NXObject *nXObject2;
	//logical adjust = false;
	//NXOpen::Vector3d vec1(0.0, 0.0, 1.0);
	//NXOpen::Vector3d vec2(1.0, 0.0, 0.0);
	if( 0 == strcmp("TOP",viewType.GetText()) )
	{
		/*workPart->DrawingSheets()->CurrentDrawingSheet();
		Drawings::DrawingSheet *drawingSheet1= workPart->DrawingSheets()->CurrentDrawingSheet();
		Drawings::DrawingSheetBuilder *drawingSheetBuilder1;
		drawingSheetBuilder1 = workPart->DrawingSheets()->DrawingSheetBuilder(drawingSheet1);
		double sheetlen = drawingSheetBuilder1->Length();
		double sheethei = drawingSheetBuilder1->Height();
		drawingSheetBuilder1->Destroy();*/

		
		NXOpen::Point3d origin1(0.0, 0.0, 0.0);
		NXOpen::Vector3d vector1(0.0, 0.0, 1.0);
		NXOpen::Vector3d vector2(1.0, 0.0, 0.0);
		double dir[3][3]={0};
		int ret = GetTopViewProjectDirection(partTag,refset,dir);
		if(ret == 0)
		{
			vector1.X = dir[0][0];
			vector1.Y = dir[0][1];
			vector1.Z = dir[0][2];

			double cross[3] ;
			UF_VEC3_cross(dir[0],dir[1],cross);
			UF_VEC3_cross(cross,dir[0],dir[1]);

			vector2.X = -dir[1][0];
			vector2.Y = -dir[1][1];
			vector2.Z = -dir[1][2];
		}

		

		
		//注意这里定的是投影方向---是最重要的因素
		NXOpen::Direction *direction1;
		direction1 = workPart->Directions()->CreateDirection(origin1, vector1, NXOpen::SmartObject::UpdateOptionAfterModeling);
		baseViewBuilder1->Style()->ViewStyleOrientation()->Ovt()->SetNormalDirection(direction1);

		//注意：这里定的是投影图投出来以后，x方向（这个时候只有xy方向），x方向对应的三维空间的方向，其实就是定投影视图的旋转方向的
		//这个很重要：他决定了了 右视图 和 下面的视图的 投影方向！！！！！！ 因为右边视图和下面视图我们是不能指定方向的,这个旋转方向直接决定了右侧和下侧看什么东西
		NXOpen::Direction *direction2;
		direction2 = workPart->Directions()->CreateDirection(origin1, vector2, NXOpen::SmartObject::UpdateOptionAfterModeling);
		baseViewBuilder1->Style()->ViewStyleOrientation()->Ovt()->SetXDirection(direction2);

		

        viewRefPoint.X = sheetlen/2;
		viewRefPoint.Y = sheethei/2;
		viewRefPoint.Z = 0;
	}
	else
	{
		//baseViewBuilder1->Scale()->SetDenominator(1.0);
	}
	baseViewBuilder1->Scale()->SetDenominator(stdscale);
    baseViewBuilder1->Placement()->Placement()->SetValue(NULL, workPart->Views()->WorkView(), viewRefPoint);
	
	nXObject2 = baseViewBuilder1->Commit();
    viewTag = nXObject2->Tag();

	baseViewBuilder1->Destroy();

	/*if(adjust)
		AdjustViewDirection(viewTag,vec1,vec2);*/
    return viewTag;
}

static int ROY_UF_VIEW_ask_xy_clip(tag_t view_tag ,double scale, double xy_clip_bounds[4] )
{
	double xy_boud[4] = {0,0,0,0};
	int irc = UF_VIEW_ask_xy_clip(view_tag,xy_boud);
	for( int idx = 0; idx < 4; idx++ )
	{
		xy_clip_bounds[idx] = xy_boud[idx]/scale;
	}
	return irc;
}

static tag_t CreateProjectView( tag_t topView, const double x, const double y)
{
    Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Part *displayPart(theSession->Parts()->Display());
    Drawings::ProjectedView *nullDrawings_ProjectedView(NULL);
    Drawings::ProjectedViewBuilder *projectedViewBuilder1;
    projectedViewBuilder1 = workPart->DraftingViews()->CreateProjectedViewBuilder(nullDrawings_ProjectedView);
    
    //Drawings::BaseView *baseView1(dynamic_cast<Drawings::BaseView *>(workPart->DraftingViews()->FindObject("TOP@1")));
	Drawings::BaseView *baseView1(dynamic_cast<Drawings::BaseView *>(NXOpen::NXObjectManager::Get(topView)));

    projectedViewBuilder1->Parent()->View()->SetValue(baseView1);
    
    projectedViewBuilder1->Style()->ViewStyleDetail()->SetViewBoundaryWidth(Preferences::WidthOriginal);
    
    //projectedViewBuilder1->Style()->ViewStyleBase()->SetPartName("E:\\xingtai\\RYF140628-UG\\RYF140628-UG\\RYF140628-GAUGE\\RYF-test_dwg.prt");
    
    projectedViewBuilder1->Style()->ViewStyleDetail()->SetViewBoundaryWidth(Preferences::WidthNormal);
    
    projectedViewBuilder1->Style()->ViewStyleGeneral()->SetToleranceValue(0.213614);    
    
    projectedViewBuilder1->Placement()->AlignmentView()->SetValue(baseView1);
    
    Point3d point2(x, y, 0.0);
    projectedViewBuilder1->Placement()->Placement()->SetValue(NULL, workPart->Views()->WorkView(), point2);
    
    projectedViewBuilder1->Placement()->AlignmentView()->SetValue(baseView1);
    
    NXObject *nXObject3;
    nXObject3 = projectedViewBuilder1->Commit();
	tag_t viewTag = nXObject3->Tag();

    projectedViewBuilder1->Destroy();
	return viewTag;
}

static void MoveBaseView( tag_t viewTag ,double x, double y)
{
	Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());

    NXOpen::Drawings::BaseViewBuilder *baseViewBuilder1;
    Drawings::BaseView *baseView1(dynamic_cast<Drawings::BaseView *>(NXOpen::NXObjectManager::Get(viewTag)));
    baseViewBuilder1 = workPart->DraftingViews()->CreateBaseViewBuilder(baseView1);

    Point3d point2(x, y, 0.0);
    baseViewBuilder1->Placement()->Placement()->SetValue(NULL, workPart->Views()->WorkView(), point2);
    
    NXObject *nXObject3;
    nXObject3 = baseViewBuilder1->Commit();
    baseViewBuilder1->Destroy();
}

static void MoveProjectView( tag_t projectview ,double x, double y)
{
	Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Drawings::ProjectedView *nullDrawings_ProjectedView(NULL);
    Drawings::ProjectedViewBuilder *projectedViewBuilder1;
    
	//Drawings::BaseView *baseView1(dynamic_cast<Drawings::BaseView *>(NXOpen::NXObjectManager::Get(topView)));
	Drawings::ProjectedView *projectView1(dynamic_cast<Drawings::ProjectedView *>(NXOpen::NXObjectManager::Get(projectview)));

	projectedViewBuilder1 = workPart->DraftingViews()->CreateProjectedViewBuilder(projectView1);

   /* projectedViewBuilder1->Parent()->View()->SetValue(baseView1);

	projectedViewBuilder1->Placement()->AlignmentView()->SetValue(baseView1);*/
    
    Point3d point2(x, y, 0.0);
    projectedViewBuilder1->Placement()->Placement()->SetValue(NULL, workPart->Views()->WorkView(), point2);
    
    //projectedViewBuilder1->Placement()->AlignmentView()->SetValue(baseView1);
    
    NXObject *nXObject3;
    nXObject3 = projectedViewBuilder1->Commit();
	//tag_t viewTag = nXObject3->Tag();

    projectedViewBuilder1->Destroy();
}

static int CreateBaseAndProjectViews( tag_t partTag, NXString& refset, double stdscale, tag_t &symbolView, tag_t &projectViewl,tag_t &projectViewr, double viewxbound[4],double& sug,double sheetlen,double sheethei)//6,75, x-6, y-36 v // 6,75, x-59, y-6 h
{
	Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
	NXOpen::Point3d point1(0, 0, 0.0);

	//注意NX7.0 是TOP NX12.0是 Top--这一句话看似多余，其实是为了让ug自动把model图纸挂到当前装配下
	tag_t baseView = CreateBaseView(partTag,"TOP",refset, point1,stdscale,sheetlen,sheethei);

    tag_t proto = partTag;
    tag_t currentDrawing = NULL_TAG;
    tag_t *comps = NULL;
    tag_t disp = UF_PART_ask_display_part();
    if(UF_ASSEM_is_occurrence(partTag))
        proto = UF_ASSEM_ask_prototype_of_occ(partTag);
    tag_t rootocc = UF_ASSEM_ask_root_part_occ(disp);
    int n = UF_ASSEM_ask_part_occ_children(rootocc, &comps);
    for( int idx = 0; idx < n; ++idx )
    {
        tag_t compPro = UF_ASSEM_ask_prototype_of_occ(comps[idx]);
        if( compPro == proto )
        {
            int err = 0;
            err = UF_ASSEM_replace_refset(1,&comps[idx],refset.GetLocaleText());
            tag_t baseView2 = CreateBaseView(partTag,"TOP",refset, point1,stdscale,sheetlen,sheethei);
            UF_VIEW_delete(baseView,&err);
            baseView = baseView2;
        }
    }
    UF_DRAW_ask_current_drawing(&currentDrawing);
    UF_DRAW_upd_out_of_date_views(currentDrawing);
    UF_free(comps);
    //UF_DRAW_set_suppress_view_updat
             //UF_DRAW_update_one_view
    double sheetLen = point1.X*2;
    double sheetHei = point1.Y*2;
	projectViewr = CreateProjectView(baseView,point1.X+50, point1.Y);
	projectViewl = CreateProjectView(baseView,point1.X, point1.Y-50);
    

	//nx7.0 TFR-ISO nx12.0 Isometric
    tag_t IsometricView = CreateBaseView(partTag,"TFR-ISO", refset,point1,stdscale,sheetlen,sheethei);
	double xy_boud1[4] = {0,0,0,0};
	double xy_boud2[4] = {0,0,0,0};
	double xy_boud3[4] = {0,0,0,0};
	double xy_boud4[4] = {0,0,0,0};
	ROY_UF_VIEW_ask_xy_clip(baseView,stdscale,xy_boud1);
	ROY_UF_VIEW_ask_xy_clip(projectViewl,stdscale,xy_boud2);
    ROY_UF_VIEW_ask_xy_clip(projectViewr,stdscale,xy_boud3);
    ROY_UF_VIEW_ask_xy_clip(IsometricView,stdscale,xy_boud4);
    double viewHei = xy_boud1[3]-xy_boud1[2] + xy_boud2[3]-xy_boud2[2];
    double viewLen = xy_boud1[1]-xy_boud1[0] + xy_boud3[1]-xy_boud3[0];
    double drawingareaHei = 0;
    double drawingareaLen = 0;
    double vlen2 = xy_boud1[1]-xy_boud1[0] + xy_boud4[1]-xy_boud4[0];
    double vhei2 = xy_boud3[3]-xy_boud3[2] + xy_boud4[3]-xy_boud4[2];
    if(sheetLen > sheetHei) //h
    {
        drawingareaLen = sheetLen-20-20;
        drawingareaHei = sheetHei-40-20;
    }
    else //v 
    {
        drawingareaLen = sheetLen-20-20;
        drawingareaHei = sheetHei-40-20;
    }
	if( vhei2 > viewHei )
		viewHei = vhei2;
	if( vlen2 > viewLen )
		viewLen = vlen2;
	/*if( viewHei >= drawingareaHei || viewLen >= drawingareaLen ) //adjust scale &&  stdscale < 19.9 || vhei2 >= drawingareaHei || vlen2 >= drawingareaLen 
    {
		int err = 0;//-->A3 UF_DRAW_set_drawing_info
        double sug1 = (viewLen-25.4)/(drawingareaLen-25.4);
        double sug2 = (viewHei-25.4)/(drawingareaHei-25.4);
        if( sug1 > sug2 )
            sug = sug1;
        else
            sug = sug2;
		UF_VIEW_delete(projectViewl,&err);
		UF_VIEW_delete(projectViewr,&err);
		UF_VIEW_delete(baseView,&err);
		UF_VIEW_delete(IsometricView,&err);
        return 1;
    }
    else
    {*/
        int err = 0;
        UF_VIEW_delete(IsometricView,&err);
        Drawings::DrawingSheet *drawingSheet1= workPart->DrawingSheets()->CurrentDrawingSheet();
        Drawings::DrawingSheetBuilder *drawingSheetBuilder1;
        drawingSheetBuilder1 = workPart->DrawingSheets()->DrawingSheetBuilder(drawingSheet1);
        drawingSheetBuilder1->SetStandardMetricScale(NXOpen::Drawings::DrawingSheetBuilder::SheetStandardMetricScaleCustom);
        drawingSheetBuilder1->SetScaleNumerator(1.0);
        drawingSheetBuilder1->SetScaleDenominator(stdscale);
        NXOpen::NXObject *nXObject1;
        nXObject1 = drawingSheetBuilder1->Commit();
        drawingSheetBuilder1->Destroy();
    //}
	
	if( drawingareaHei > viewHei && drawingareaLen > viewLen )
	{
		double gaph = (drawingareaHei - viewHei)/3;
		double gapl = (drawingareaLen - viewLen)/3;
		double baseview_x = 20+gapl+(xy_boud1[1]-xy_boud1[0])/2;
		double baseview_y = 40+gaph*2+(xy_boud1[3]-xy_boud1[2])/2+xy_boud2[3]-xy_boud2[2];
		double baseview_y2 = 40+gaph*2+(xy_boud1[3]-xy_boud1[2])/2+xy_boud4[3]-xy_boud4[2];
		if( baseview_y2 > baseview_y )
			baseview_y = baseview_y2;
		double projeclview_x = baseview_x;
		double projeclview_y = 40+gaph+(xy_boud2[3]-xy_boud2[2])/2;
		double projeclview_y2 = 40+gaph+(xy_boud4[3]-xy_boud4[2])/2;
		if( projeclview_y2 > projeclview_y )
			projeclview_y = projeclview_y2;
		double projecRview_x = 20+gapl*2+xy_boud1[1]-xy_boud1[0]+(xy_boud3[1]-xy_boud3[0])/2;
		double projecRview_x2 = 20+gapl*2+xy_boud1[1]-xy_boud1[0]+(xy_boud4[1]-xy_boud4[0])/2;
		if( projecRview_x2 > projecRview_x )
			projecRview_x = projecRview_x2;
		double projecRview_y = baseview_y;
		MoveBaseView(baseView,baseview_x,baseview_y );
        viewxbound[0] = baseview_x-(xy_boud1[1]-xy_boud1[0])/2;
        viewxbound[2] = baseview_y-(xy_boud1[3]-xy_boud1[2])/2;
		viewxbound[1] = baseview_x+(xy_boud1[1]-xy_boud1[0])/2;
        viewxbound[3] = baseview_y+(xy_boud1[3]-xy_boud1[2])/2;
		MoveProjectView(projectViewl,projeclview_x,projeclview_y);
		MoveProjectView(projectViewr,projecRview_x,projecRview_y);

		NXOpen::Point3d point2(projecRview_x, projeclview_y, 0.0);
		tag_t IsometricView = CreateBaseView(partTag,"TFR-ISO", refset,point2,stdscale,sheetlen,sheethei);
		NXOpen::Session *theSession = NXOpen::Session::GetSession();
		NXOpen::Part *workPart(theSession->Parts()->Work());
		std::vector<NXOpen::Drawings::DraftingView *> views1(2);
		NXOpen::Drawings::ProjectedView *projectedView1(dynamic_cast<NXOpen::Drawings::ProjectedView *>(NXOpen::NXObjectManager::Get(projectViewl)));
		NXOpen::Drawings::ProjectedView *projectedView2(dynamic_cast<NXOpen::Drawings::ProjectedView *>(NXOpen::NXObjectManager::Get(projectViewr)));
		views1[0] = projectedView1;
		views1[1] = projectedView2;
		workPart->DraftingViews()->UpdateViews(views1);
		//ROY_UF_VIEW_ask_xy_clip(IsometricView,stdscale,xy_boud4);
		//if(stdscale<20)
        //if(projecRview_x+xy_boud4[1]>sheetLen || projecRview_x-xy_boud4[1] <  projeclview_x+(xy_boud2[1]-xy_boud2[0])/2)
        //double vlen2 = xy_boud1[1]-xy_boud1[0] + xy_boud4[1]-xy_boud4[0];
        //double vhei2 = xy_boud3[3]-xy_boud3[2] + xy_boud4[3]-xy_boud4[2];
        //if(vhei2 >= drawingareaHei || vlen2 >= drawingareaLen  ) //|| projecRview_x+xy_boud4[1]>sheetLen || projecRview_x-xy_boud4[1] <  projeclview_x+(xy_boud2[1]-xy_boud2[0])/2
        //{
        //    int err = 0;
        //    double sug1 = (vlen2-25.4)/(drawingareaLen-25.4);
        //    double sug2 = (vhei2-25.4)/(drawingareaHei-25.4);
        //    double tempsug = 0;
        //    if( sug1 > sug2 )
        //        tempsug = sug1;
        //    else
        //        tempsug = sug2;
        //    if( tempsug > sug )
        //        sug = tempsug;
        //    UF_VIEW_delete(projectViewl,&err);
        //    UF_VIEW_delete(projectViewr,&err);
        //    UF_VIEW_delete(baseView,&err);
        //    UF_VIEW_delete(IsometricView,&err);
        //    return 1;
        //}
	}
    symbolView = baseView;
	return 0;
}

static void CreateDrawingSheet(NXString& name, double len, double hei )
{
	UF_DRAW_info_t drawing_info;
	drawing_info.drawing_scale = 1.0;
	drawing_info.units = UF_PART_METRIC;
	drawing_info.projection_angle = UF_DRAW_FIRST_ANGLE_PROJECTION;
	drawing_info.size_state = UF_DRAW_METRIC_SIZE;
	tag_t new_drawing_tag = NULL_TAG;
    drawing_info.size_state = UF_DRAW_CUSTOM_SIZE;
    drawing_info.size.custom_size[0]=hei;
    drawing_info.size.custom_size[1]=len;
	UF_DRAW_create_drawing( name.GetLocaleText(), &drawing_info,&new_drawing_tag);
	UF_DRAW_open_drawing( new_drawing_tag );
}

//frame: "A3横","A3竖","A4横","A4竖"
static tag_t CreateDrawingViewDWG(tag_t part, 
								  tag_t body, 
								  tag_t& view, 
								  tag_t &projectViewl,
								  tag_t &projectViewr,
								  NXString& name,
								  NXString& frame,
								  NXString& typeStr,
								  double viewbound[4],
								  double &stdscale )
{
	UF_import_part_modes_t modes;
	tag_t group = NULL_TAG;
	tag_t new_drawing_tag = NULL_TAG;
	char titleblock[MAX_FSPEC_SIZE] = "";
	double dest_csys[6]={1,0,0,0,1,0};
	double dest_point[3]={0,0,0};
	modes.layer_mode=1;
	modes.group_mode=1;
	modes.csys_mode=0;
	modes.plist_mode=0;
	modes.view_mode=0;
	modes.cam_mode=false;
	modes.use_search_dirs=false;
	char *p_env = getenv("UGII_USER_DIR");
    double gap = 20;
    double xlengh = 0;
    double sheetlen = 0, sheethei = 0;
	if( 0 == strcmp("A3横",frame.GetLocaleText()))
	{
        sheetlen = 420;
        sheethei = 297;
		sprintf(titleblock,"%s\\templates\\A3.prt",p_env);
	}
	else if( 0 == strcmp("A3竖",frame.GetLocaleText()))
	{
        sheetlen = 297;
        sheethei = 420;
		sprintf(titleblock,"%s\\templates\\A3V.prt",p_env);
	}
	else if( 0 == strcmp("A4横",frame.GetLocaleText()))
	{
        sheetlen = 297;
        sheethei = 210;
		sprintf(titleblock,"%s\\templates\\A4.prt",p_env);
	}
	else if( 0 == strcmp("A4竖",frame.GetLocaleText()))
	{
        sheetlen = 297;
        sheethei = 210;
		sprintf(titleblock,"%s\\templates\\A4.prt",p_env);
	}
	else
		return NULL_TAG;

	double xyzLen[3] = {0};
	TY_GetBodyXYZLen_aligned(body, xyzLen[0],xyzLen[1],xyzLen[2]);
	double xAllLen = xyzLen[0] + xyzLen[1];
	double yAllLen = xyzLen[1] + xyzLen[2];
	double scale = TY_MAX(xAllLen/sheetlen, yAllLen/sheethei);
	scale *= 2.5;
	if (scale < 1)
	{
		scale = 1;
	}

    CreateDrawingSheet( name,sheetlen*scale,sheethei*scale );

    UF_PART_import(titleblock,&modes,dest_csys,dest_point,scale,&group);

    double sug = 0;

    int irc = CreateBaseAndProjectViews(part,name,stdscale,view,projectViewl,projectViewr,viewbound,sug,sheetlen*scale,sheethei*scale);
    return group;
}

static tag_t GetMinDistanceObject( double pt[3], vtag_t& objects )
{
	tag_t target = NULL_TAG;
	tag_t planeTag = NULL_TAG;
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
	if (objects.size() > 0 )
	{
		target = objects[0];
		NXOpen::Point *point1;
		NXOpen::Point3d coordinates1(pt[0], pt[1], pt[2]);
		//double dir[3]={0,1,0};
		point1 = workPart->Points()->CreatePoint(coordinates1);
		//UF_MODL_create_plane(pt,dir,&planeTag);
		double mindist = 0;
		 TYCOM_AskMinimumDist(point1->Tag(),target,mindist);
		for( int idx = 1; idx < objects.size(); ++idx )
		{
			double tempdis = 0;
			 TYCOM_AskMinimumDist(point1->Tag(),objects[idx],tempdis);
			if( MATH_is_less2(tempdis , mindist,DOUBLE_TOL))
			{
				mindist = tempdis;
				target = objects[idx];
			}
		}
		UF_OBJ_delete_object(point1->Tag());
	}
	return target;
}

static void CreateDemension2(tag_t partTag, tag_t viewTag, vtag_t& objects, int flag, double bound[4])
{
	/*NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Part *dispPart(theSession->Parts()->Display());
	double offset = 1000;
	tag_t firstTag = NULL_TAG, secondTag = NULL_TAG;
	double leftpt2d[2]={bound[0]-offset,(bound[2]+bound[3])/2};
	double rightpt2d[2]={bound[1]+offset,(bound[2]+bound[3])/2};
	double bottompt2d[2]={(bound[0]+bound[1])/2,bound[2]-offset};
	double toppt2d[2]={(bound[0]+bound[1])/2,bound[3]+offset};
	double firstPoint[3], secondPoint[3];
	//UF_ASSEM_set_work_part(partTag);
	//UF_PART_set_display_part(partTag);
	if( 0 == flag )
	{
		UF_VIEW_map_drawing_to_model(viewTag,toppt2d,firstPoint);
		UF_VIEW_map_drawing_to_model(viewTag,bottompt2d,secondPoint);
	}
	else
	{
		UF_VIEW_map_drawing_to_model(viewTag,rightpt2d,firstPoint);
		UF_VIEW_map_drawing_to_model(viewTag,leftpt2d,secondPoint);
	}
	firstTag = GetMinDistanceObject(firstPoint,objects);
	secondTag = GetMinDistanceObject(secondPoint,objects);
	//UF_ASSEM_set_work_part(workPart->Tag());
	//UF_PART_set_display_part(dispPart->Tag());

    NXOpen::Annotations::Dimension *nullNXOpen_Annotations_Dimension(NULL);
    NXOpen::Annotations::RapidDimensionBuilder *rapidDimensionBuilder1;
    rapidDimensionBuilder1 = workPart->Dimensions()->CreateRapidDimensionBuilder(nullNXOpen_Annotations_Dimension);
    
    rapidDimensionBuilder1->Origin()->SetInferRelativeToGeometry(true);
  
    rapidDimensionBuilder1->Origin()->Plane()->SetPlaneMethod(NXOpen::Annotations::PlaneBuilder::PlaneMethodTypeXyPlane);
    
    NXOpen::Direction *nullNXOpen_Direction(NULL);
    rapidDimensionBuilder1->Measurement()->SetDirection(nullNXOpen_Direction);
    
    NXOpen::View *nullNXOpen_View(NULL);
    rapidDimensionBuilder1->Measurement()->SetDirectionView(nullNXOpen_View);
    
    rapidDimensionBuilder1->Style()->DimensionStyle()->SetNarrowDisplayType(NXOpen::Annotations::NarrowDisplayOptionNone);

	NXOpen::Drawings::BaseView *baseView1(dynamic_cast<Drawings::BaseView *>(NXOpen::NXObjectManager::Get(viewTag)));
    NXOpen::Drawings::DraftingCurve *draftingCurve1(dynamic_cast<NXOpen::Drawings::DraftingCurve *>(NXOpen::NXObjectManager::Get(firstTag)));
	int type = 0, subtype = 0;
	int type2 = 0, subtype2 = 0;
	double ref[3]={0,0,0};
	double pt2d[2],pt3d[3];
	UF_OBJ_ask_type_and_subtype(firstTag, &type, &subtype);
	UF_OBJ_ask_type_and_subtype(secondTag, &type2, &subtype2);
    //NXOpen::Point3d point1_1(-0.490001264002843, 100, 0.0);
    //NXOpen::Point3d point1_1(boundbox1[3], boundbox1[4], boundbox1[5]);
    NXOpen::Point3d point1_1(firstPoint[0], firstPoint[1], firstPoint[2]);
    NXOpen::Point3d point2_1(0.0, 0.0, 0.0);
    //rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
    if(type == UF_circle_type|| type == UF_conic_type)
	{
		rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
	}
	else //if(type == UF_line_type)
	{
		rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeEnd, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
	}
    NXOpen::Drawings::DraftingCurve *draftingCurve2(dynamic_cast<NXOpen::Drawings::DraftingCurve *>(NXOpen::NXObjectManager::Get(secondTag)));
    //NXOpen::Point3d point1_2(-22.0000000000002, -26.9999999999995, -129.357884749828);
	
	//NXOpen::Point3d point1_2(-0.490001264002843, 100, 0.0);
    NXOpen::Point3d point2_2(0.0, 0.0, 0.0);
	

	NXOpen::Point3d point1_2(secondPoint[0], secondPoint[1], secondPoint[2]);
    //rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeEnd, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
    if(type2 == UF_circle_type|| type2 == UF_conic_type)
	{
		rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
	}
	else //if(type == UF_line_type)
	{
		rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeStart, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
	}

    NXOpen::Annotations::Annotation::AssociativeOriginData assocOrigin1;
    assocOrigin1.OriginType = NXOpen::Annotations::AssociativeOriginTypeDrag;
    assocOrigin1.View = nullNXOpen_View;
    assocOrigin1.ViewOfGeometry = nullNXOpen_View;
    NXOpen::Point *nullNXOpen_Point(NULL);
    assocOrigin1.PointOnGeometry = nullNXOpen_Point;
    NXOpen::Annotations::Annotation *nullNXOpen_Annotations_Annotation(NULL);
    assocOrigin1.VertAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.VertAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.HorizAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.HorizAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.AlignedAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.DimensionLine = 0;
    assocOrigin1.AssociatedView = nullNXOpen_View;
    assocOrigin1.AssociatedPoint = nullNXOpen_Point;
    assocOrigin1.OffsetAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.OffsetAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.XOffsetFactor = 0.0;
    assocOrigin1.YOffsetFactor = 0.0;
    assocOrigin1.StackAlignmentPosition = NXOpen::Annotations::StackAlignmentPositionAbove;
    rapidDimensionBuilder1->Origin()->SetAssociativeOrigin(assocOrigin1);
    
	NXOpen::Point3d point1(bound[0]-5, (bound[3]+bound[1])/2, 0.0);
	rapidDimensionBuilder1->Style()->LineArrowStyle()->SetLeaderOrientation(NXOpen::Annotations::LeaderSideLeft);
	if( 1 == flag )
	{
		point1.X = (bound[2]+bound[0])/2;
		point1.Y = bound[3]+5;
		rapidDimensionBuilder1->Style()->LineArrowStyle()->SetLeaderOrientation(NXOpen::Annotations::LeaderSideRight);
		rapidDimensionBuilder1->Measurement()->SetMethod(NXOpen::Annotations::DimensionMeasurementBuilder::MeasurementMethodHorizontal);
	}
	else
	{
		//rapidDimensionBuilder1->Measurement()->SetMethod(NXOpen::Annotations::DimensionMeasurementBuilder::MeasurementMethodVertical);
	}
    
    rapidDimensionBuilder1->Origin()->Origin()->SetValue(NULL, nullNXOpen_View, point1);
    
    rapidDimensionBuilder1->Origin()->SetInferRelativeToGeometry(true);

    NXOpen::NXObject *nXObject1;
    nXObject1 = rapidDimensionBuilder1->Commit();
    
    rapidDimensionBuilder1->Destroy(); */

}

static void CreateDemension3(tag_t partTag, tag_t viewTag, vtag_t& objects, int flag, double firstPoint[3], double secondPoint[3],double scale )
{
	/*NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Part *dispPart(theSession->Parts()->Display());
	double offset = 1000;
	tag_t firstTag = NULL_TAG, secondTag = NULL_TAG;

	firstTag = GetMinDistanceObject(firstPoint,objects);
	secondTag = GetMinDistanceObject(secondPoint,objects);
	//UF_ASSEM_set_work_part(workPart->Tag());
	//UF_PART_set_display_part(dispPart->Tag());
    NXOpen::Annotations::Dimension *nullNXOpen_Annotations_Dimension(NULL);
    NXOpen::Annotations::RapidDimensionBuilder *rapidDimensionBuilder1;
    rapidDimensionBuilder1 = workPart->Dimensions()->CreateRapidDimensionBuilder(nullNXOpen_Annotations_Dimension);
    
    rapidDimensionBuilder1->Origin()->SetInferRelativeToGeometry(true);
  
    rapidDimensionBuilder1->Origin()->Plane()->SetPlaneMethod(NXOpen::Annotations::PlaneBuilder::PlaneMethodTypeXyPlane);
    
    NXOpen::Direction *nullNXOpen_Direction(NULL);
    rapidDimensionBuilder1->Measurement()->SetDirection(nullNXOpen_Direction);
    
    NXOpen::View *nullNXOpen_View(NULL);
    rapidDimensionBuilder1->Measurement()->SetDirectionView(nullNXOpen_View);
    
    rapidDimensionBuilder1->Style()->DimensionStyle()->SetNarrowDisplayType(NXOpen::Annotations::NarrowDisplayOptionNone);

	//NXOpen::Drawings::BaseView *baseView1(dynamic_cast<Drawings::BaseView *>(NXOpen::NXObjectManager::Get(viewTag)));
	NXOpen::View *baseView1(dynamic_cast<NXOpen::View *>(NXOpen::NXObjectManager::Get(viewTag)));
	//NXOpen::Drawings::ProjectedView *projectedView1(dynamic_cast<NXOpen::Drawings::ProjectedView *>(workPart->DraftingViews()->FindObject("ORTHO@8")));
	
    NXOpen::Drawings::DraftingCurve *draftingCurve1(dynamic_cast<NXOpen::Drawings::DraftingCurve *>(NXOpen::NXObjectManager::Get(firstTag)));
	int type = 0, subtype = 0;
	int type2 = 0, subtype2 = 0;
	double ref[3]={0,0,0};
	double pt2d[2],pt3d[3];
	UF_OBJ_ask_type_and_subtype(firstTag, &type, &subtype);
	UF_OBJ_ask_type_and_subtype(secondTag, &type2, &subtype2);
    //NXOpen::Point3d point1_1(-0.490001264002843, 100, 0.0);
    //NXOpen::Point3d point1_1(boundbox1[3], boundbox1[4], boundbox1[5]);
    NXOpen::Point3d point1_1(firstPoint[0], firstPoint[1], firstPoint[2]);
    NXOpen::Point3d point2_1(0.0, 0.0, 0.0);
    //rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
    if(type == UF_circle_type|| type == UF_conic_type)
	{
		rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
	}
	else //if(type == UF_line_type)
	{
		rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeEnd, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
	}
    NXOpen::Drawings::DraftingCurve *draftingCurve2(dynamic_cast<NXOpen::Drawings::DraftingCurve *>(NXOpen::NXObjectManager::Get(secondTag)));
    //NXOpen::Point3d point1_2(-22.0000000000002, -26.9999999999995, -129.357884749828);
	
	//NXOpen::Point3d point1_2(-0.490001264002843, 100, 0.0);
    NXOpen::Point3d point2_2(0.0, 0.0, 0.0);
	

	NXOpen::Point3d point1_2(secondPoint[0], secondPoint[1], secondPoint[2]);
    //rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeEnd, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
    if(type2 == UF_circle_type|| type2 == UF_conic_type)
	{
		rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
	}
	else //if(type == UF_line_type)
	{
		rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeStart, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
	}

    NXOpen::Annotations::Annotation::AssociativeOriginData assocOrigin1;
    assocOrigin1.OriginType = NXOpen::Annotations::AssociativeOriginTypeDrag;
    assocOrigin1.View = nullNXOpen_View;
    assocOrigin1.ViewOfGeometry = nullNXOpen_View;
    NXOpen::Point *nullNXOpen_Point(NULL);
    assocOrigin1.PointOnGeometry = nullNXOpen_Point;
    NXOpen::Annotations::Annotation *nullNXOpen_Annotations_Annotation(NULL);
    assocOrigin1.VertAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.VertAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.HorizAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.HorizAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.AlignedAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.DimensionLine = 0;
    assocOrigin1.AssociatedView = nullNXOpen_View;
    assocOrigin1.AssociatedPoint = nullNXOpen_Point;
    assocOrigin1.OffsetAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.OffsetAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.XOffsetFactor = 0.0;
    assocOrigin1.YOffsetFactor = 0.0;
    assocOrigin1.StackAlignmentPosition = NXOpen::Annotations::StackAlignmentPositionAbove;
    rapidDimensionBuilder1->Origin()->SetAssociativeOrigin(assocOrigin1);
	double viewbound[4] = {0};
	double viewcenter[3] = {0};
	ROY_UF_VIEW_ask_xy_clip(viewTag,scale,viewbound);
	UF_VIEW_ask_center(viewTag,viewcenter);
	UF_VIEW_map_model_to_drawing(viewTag,viewcenter,pt2d);
	viewbound[0] += pt2d[0];
	viewbound[1] += pt2d[0];
	viewbound[2] += pt2d[1];
	viewbound[3] += pt2d[1];
	NXOpen::Point3d point1(viewbound[0]-5, (viewbound[3]+viewbound[2])/2, 0.0);
	rapidDimensionBuilder1->Style()->LineArrowStyle()->SetLeaderOrientation(NXOpen::Annotations::LeaderSideLeft);
	if( 1 == flag )
	{
		point1.X = (viewbound[1]+viewbound[0])/2;
		point1.Y = viewbound[3]+5;
		rapidDimensionBuilder1->Style()->LineArrowStyle()->SetLeaderOrientation(NXOpen::Annotations::LeaderSideRight);
		rapidDimensionBuilder1->Measurement()->SetMethod(NXOpen::Annotations::DimensionMeasurementBuilder::MeasurementMethodHorizontal);
	}
	else
	{
		//rapidDimensionBuilder1->Measurement()->SetMethod(NXOpen::Annotations::DimensionMeasurementBuilder::MeasurementMethodVertical);
	}
    
    rapidDimensionBuilder1->Origin()->Origin()->SetValue(NULL, nullNXOpen_View, point1);
    
    rapidDimensionBuilder1->Origin()->SetInferRelativeToGeometry(true);

    NXOpen::NXObject *nXObject1;
    nXObject1 = rapidDimensionBuilder1->Commit();
    
    rapidDimensionBuilder1->Destroy(); */

}
static void CreateDemension( tag_t viewTag, tag_t firstTag, tag_t secondTag, int flag, double bound[4])
{
	/*NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    
    NXOpen::Annotations::Dimension *nullNXOpen_Annotations_Dimension(NULL);
    NXOpen::Annotations::RapidDimensionBuilder *rapidDimensionBuilder1;
    rapidDimensionBuilder1 = workPart->Dimensions()->CreateRapidDimensionBuilder(nullNXOpen_Annotations_Dimension);
    
    rapidDimensionBuilder1->Origin()->SetInferRelativeToGeometry(true);
  
    rapidDimensionBuilder1->Origin()->Plane()->SetPlaneMethod(NXOpen::Annotations::PlaneBuilder::PlaneMethodTypeXyPlane);
    
    NXOpen::Direction *nullNXOpen_Direction(NULL);
    rapidDimensionBuilder1->Measurement()->SetDirection(nullNXOpen_Direction);
    
    NXOpen::View *nullNXOpen_View(NULL);
    rapidDimensionBuilder1->Measurement()->SetDirectionView(nullNXOpen_View);
    
    rapidDimensionBuilder1->Style()->DimensionStyle()->SetNarrowDisplayType(NXOpen::Annotations::NarrowDisplayOptionNone);

	NXOpen::Drawings::BaseView *baseView1(dynamic_cast<Drawings::BaseView *>(NXOpen::NXObjectManager::Get(viewTag)));
    NXOpen::Drawings::DraftingCurve *draftingCurve1(dynamic_cast<NXOpen::Drawings::DraftingCurve *>(NXOpen::NXObjectManager::Get(firstTag)));
	int type = 0, subtype = 0;
	int type2 = 0, subtype2 = 0;
	double ref[3]={0,0,0};
	double boundbox1[6]={0};
	double boundbox2[6]={0};
	double pt2d[2],pt3d[3];
	UF_OBJ_ask_type_and_subtype(firstTag, &type, &subtype);
	UF_OBJ_ask_type_and_subtype(secondTag, &type2, &subtype2);
	UF_MODL_ask_bounding_box(firstTag,boundbox1);
	UF_MODL_ask_bounding_box(secondTag,boundbox2);

	UF_VIEW_map_model_to_drawing(viewTag,boundbox1+3,pt2d);
	if( 0 == flag ) // top 
	{
		pt2d[1] += 999999;
	}
	else//right
	{
		pt2d[0] += 999999;
	}
	UF_VIEW_map_drawing_to_model(viewTag,pt2d,pt3d);
    //NXOpen::Point3d point1_1(-0.490001264002843, 100, 0.0);
    //NXOpen::Point3d point1_1(boundbox1[3], boundbox1[4], boundbox1[5]);
    NXOpen::Point3d point1_1(pt3d[0], pt3d[1], pt3d[2]);
    NXOpen::Point3d point2_1(0.0, 0.0, 0.0);
    //rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
    if(type == UF_circle_type|| type == UF_conic_type)
	{
		rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
	}
	else //if(type == UF_line_type)
	{
		rapidDimensionBuilder1->FirstAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeEnd, draftingCurve1, baseView1, point1_1, NULL, nullNXOpen_View, point2_1);
	}
    NXOpen::Drawings::DraftingCurve *draftingCurve2(dynamic_cast<NXOpen::Drawings::DraftingCurve *>(NXOpen::NXObjectManager::Get(secondTag)));
    //NXOpen::Point3d point1_2(-22.0000000000002, -26.9999999999995, -129.357884749828);
	
	//NXOpen::Point3d point1_2(-0.490001264002843, 100, 0.0);
    NXOpen::Point3d point2_2(0.0, 0.0, 0.0);
	
	UF_VIEW_map_model_to_drawing(viewTag,boundbox2,pt2d);
	if( 0 == flag ) // bottom
	{
		pt2d[1] -= 999999;
	}
	else //left
	{
		pt2d[0] -= 999999;
	}
	UF_VIEW_map_drawing_to_model(viewTag,pt2d,pt3d);
	NXOpen::Point3d point1_2(pt3d[0], pt3d[1], pt3d[2]);
    //rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeEnd, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
    if(type2 == UF_circle_type|| type2 == UF_conic_type)
	{
		rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeDrfTangent, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
	}
	else //if(type == UF_line_type)
	{
		int cnt = 0;
		double *pts, parm=0;
		double pt1[2]={0,0},pt2[2]={0,0};
		//UF_MODL_ask_curve_parm(secondTag,ref,&parm,pts);
		double end[3],start[3];
		tag_t edge = NULL_TAG;
		//UF_CALL(UF_MODL_create_curve_from_edge(secondTag, &edge));
		//UF_CALL(UF_MODL_ask_edge_verts(edge, start, end, &cnt));
		//UF_VIEW_map_model_to_drawing(viewTag,start,pt1);
		//UF_VIEW_map_model_to_drawing(viewTag,end,pt2);
		rapidDimensionBuilder1->SecondAssociativity()->SetValue(NXOpen::InferSnapType::SnapTypeStart, draftingCurve2, baseView1, point1_2, NULL, nullNXOpen_View, point2_2);
	}

    NXOpen::Annotations::Annotation::AssociativeOriginData assocOrigin1;
    assocOrigin1.OriginType = NXOpen::Annotations::AssociativeOriginTypeDrag;
    assocOrigin1.View = nullNXOpen_View;
    assocOrigin1.ViewOfGeometry = nullNXOpen_View;
    NXOpen::Point *nullNXOpen_Point(NULL);
    assocOrigin1.PointOnGeometry = nullNXOpen_Point;
    NXOpen::Annotations::Annotation *nullNXOpen_Annotations_Annotation(NULL);
    assocOrigin1.VertAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.VertAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.HorizAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.HorizAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.AlignedAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.DimensionLine = 0;
    assocOrigin1.AssociatedView = nullNXOpen_View;
    assocOrigin1.AssociatedPoint = nullNXOpen_Point;
    assocOrigin1.OffsetAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.OffsetAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.XOffsetFactor = 0.0;
    assocOrigin1.YOffsetFactor = 0.0;
    assocOrigin1.StackAlignmentPosition = NXOpen::Annotations::StackAlignmentPositionAbove;
    rapidDimensionBuilder1->Origin()->SetAssociativeOrigin(assocOrigin1);
    
	NXOpen::Point3d point1(bound[0]-5, (bound[3]+bound[1])/2, 0.0);
	rapidDimensionBuilder1->Style()->LineArrowStyle()->SetLeaderOrientation(NXOpen::Annotations::LeaderSideLeft);
	if( 1 == flag )
	{
		point1.X = (bound[2]+bound[0])/2;
		point1.Y = bound[3]+5;
		rapidDimensionBuilder1->Style()->LineArrowStyle()->SetLeaderOrientation(NXOpen::Annotations::LeaderSideRight);
		rapidDimensionBuilder1->Measurement()->SetMethod(NXOpen::Annotations::DimensionMeasurementBuilder::MeasurementMethodHorizontal);
	}
	else
	{
		//rapidDimensionBuilder1->Measurement()->SetMethod(NXOpen::Annotations::DimensionMeasurementBuilder::MeasurementMethodVertical);
	}
    
    rapidDimensionBuilder1->Origin()->Origin()->SetValue(NULL, nullNXOpen_View, point1);
    
    rapidDimensionBuilder1->Origin()->SetInferRelativeToGeometry(true);

    NXOpen::NXObject *nXObject1;
    nXObject1 = rapidDimensionBuilder1->Commit();
    
    rapidDimensionBuilder1->Destroy(); */

}

static tag_t Create_wcs_by_view(tag_t viewTag)
{
    tag_t mx = NULL_TAG, wcs = NULL_TAG;
    double csys[9]={1,0,0,0,1,0,0,0,1},
           tol = 0,
		   mag = 0, 
		   origin[3]={0,0,0},
		   x_dir[3],
           y_dir[3],
           z_dir[3];


    UF_MODL_ask_distance_tolerance(&tol);

    /*UF_CALL(UF_MODL_ask_face_parm(face, origin, parm, pnt));
    UF_CALL(UF_MODL_ask_face_props(face, parm, pnt, x_dir, 
        junk, junk, junk, z_dir, junk));*/
	if( viewTag != NULL_TAG )
	{
		/*NXOpen::Session *theSession = NXOpen::Session::GetSession();
		NXOpen::Part *workPart(theSession->Parts()->Work());

		NXOpen::Drawings::BaseViewBuilder *baseViewBuilder1;
		Drawings::BaseView *baseView1(dynamic_cast<Drawings::BaseView *>(NXOpen::NXObjectManager::Get(viewTag)));
		baseViewBuilder1 = workPart->DraftingViews()->CreateBaseViewBuilder(baseView1);

		NXOpen::Direction* xdir = baseViewBuilder1->Style()->ViewStyleOrientation()->Ovt()->XDirection();
		NXOpen::Direction* ndir = baseViewBuilder1->Style()->ViewStyleOrientation()->Ovt()->NormalDirection();

		x_dir[0]= xdir->Vector().X;
		x_dir[1]= xdir->Vector().Y;
		x_dir[2]= xdir->Vector().Z;
		z_dir[0]= ndir->Vector().X;
		z_dir[1]= ndir->Vector().Y;
		z_dir[2]= ndir->Vector().Z;
		UF_VEC3_cross(z_dir, x_dir, y_dir);
		UF_CALL(UF_VEC3_unitize(x_dir, tol, &mag, &csys[0]));
		UF_CALL(UF_VEC3_unitize(y_dir, tol, &mag, &csys[3]));
		UF_CALL(UF_VEC3_unitize(z_dir, tol, &mag, &csys[6]));
		baseViewBuilder1->Destroy();*/
	}
	x_dir[0]= 1;
	x_dir[1]= 0;
	x_dir[2]= 0;
	z_dir[0]= 0;
	z_dir[1]= 0;
	z_dir[2]= 1;
	UF_VEC3_cross(z_dir, x_dir, y_dir);
	UF_CALL(UF_VEC3_unitize(x_dir, tol, &mag, &csys[0]));
	UF_CALL(UF_VEC3_unitize(y_dir, tol, &mag, &csys[3]));
	UF_CALL(UF_VEC3_unitize(z_dir, tol, &mag, &csys[6]));
    //UF_MTX3_ortho_normalize(csys);

    UF_CALL(UF_CSYS_create_matrix(csys, &mx));
    UF_CALL(UF_CSYS_create_temp_csys(origin, mx, &wcs));

    return wcs;
}


static void RY_DWG_create_demention(tag_t partTag, tag_t viewTag ,double scale, double directions[3][3])
{
    int n_vis = 0, n_cli = 0;
    tag_t *visobj = NULL;
    tag_t *cliobj = NULL;
	double offset = 90000;
    double pt1[2]={0,0}, pt2[2]={0,0};
    UF_VIEW_ask_visible_objects(viewTag,&n_vis,&visobj,&n_cli,&cliobj);
    vtag_t objects;
    for( int idx = 0; idx < n_vis; ++idx )
    {
        int type = 0, subtype = 0;
        UF_OBJ_ask_type_and_subtype(visobj[idx], &type, &subtype);
        /*if(type == UF_line_type || type == UF_circle_type 
            || type == UF_conic_type || type == UF_spline_type
            || type == UF_solid_silhouette_type || type == UF_section_edge_type
            && UF_line_normal_subtype == subtype)*/
		if(type == UF_line_type || type == UF_circle_type 
            || type == UF_conic_type && UF_line_normal_subtype == subtype)
        {
            objects.push_back(visobj[idx]);
        }
    }
	//tag_t csysTag = Create_wcs_by_view(viewTag);
	//double min_corner[3]={0.0},max_corner[3]={0.0},directions[3][3]={0.0},distances[3] = {0.0};
	double leftPoint[3]={0.0},rightPoint[3]={0.0},topPoint[3]={0.0},bottomPoint[3]={0.0};
	/*UF_MODL_ask_bounding_box_exact( objects[0], csysTag, min_corner, directions, distances );
	for( int i = 0; i< 3; i++ )
	{
		for( int j = 0; j< 3; j++ )
		{
			max_corner[i] = min_corner[i]+directions[j][i] * distances[j];
		}
		center[i] = (min_corner[i]+max_corner[i])/2;
	}*/
	double center[3]={0.0};
	//UF_VIEW_ask_center(viewTag,center);
	for( int i = 0; i< 3; i++ )
	{
		leftPoint[i] = center[i]-directions[0][i] * offset;
		rightPoint[i] = center[i]+directions[0][i] * offset;
		topPoint[i] = center[i]+directions[1][i] * offset;
		bottomPoint[i] = center[i]-directions[1][i] * offset;
	}
	CreateDemension3(partTag,viewTag,objects,0,topPoint,bottomPoint,scale);
	CreateDemension3(partTag,viewTag,objects,1,leftPoint,rightPoint,scale);
	UF_free(visobj);
    UF_free(cliobj);
	return;
}
static void EditLableNote(  tag_t orgNote, vNXString text )
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	int type = 0;
	int subType = 0;
	NXString noteStr;
	UF_OBJ_ask_type_and_subtype( orgNote, &type, &subType );
	if( UF_draft_note_subtype == subType )
	{
		Annotations::Note *note1 = (NXOpen::Annotations::Note *)NXOpen::NXObjectManager::Get(orgNote);
		Annotations::DraftingNoteBuilder *draftingNoteBuilder1;
		draftingNoteBuilder1 = workPart->Annotations()->CreateDraftingNoteBuilder((Annotations::SimpleDraftingAid *)note1);
		draftingNoteBuilder1->Text()->TextBlock()->SetText(text);
		NXObject *nXObject1;
		nXObject1 = draftingNoteBuilder1->Commit();
		draftingNoteBuilder1->Destroy();
	}
}

static int GZ_SetDrawingNoteInformation( tag_t thisBody, tag_t group, double scale, NXString& DrawingNO, NXString &drawer )
{
	int n = 0;
	tag_t *members = NULL;

	UF_GROUP_ask_group_data(group, &members, &n);
	for( int idx = 0; idx < n; ++idx )
	{
		int type = 0;
		int subType = 0;
		UF_OBJ_ask_type_and_subtype( members[idx], &type, &subType );
		if( UF_draft_note_subtype == subType )//UF_tabular_note_type UF_draft_label_subtype == subType || 
		{
			char note_name[MAX_ENTITY_NAME_SIZE+1]="";
			UF_OBJ_ask_name(members[idx],note_name);
			if( 0 == strcmp("TECHREQ",note_name) )
			{
				StlNXStringVector techRequs;
				TYCOM_GetObjectAttributeLong(thisBody, ATTR_TYCOM_PROPERTY_TECH_REQUIREMENT, techRequs);
				//tech = multiline_string0->GetValue();
				if (techRequs.size() > 0)
				    EditLableNote(members[idx],techRequs);
			}
			else if( 0 == strcmp("PARTNAME",note_name) )
			{
				StlNXStringVector tech;

				char name1[256],name2[256];
				TYCOM_GetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_SOLID_NAME, name1);
				TYCOM_GetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_SOLID_NAME2, name2);

				tech.push_back(NXString(name1)+NXString(name2));
				//tech = multiline_string0->GetValue();
				EditLableNote(members[idx],tech);
			}
			else if( 0 == strcmp("DATE",note_name) )
			{
				StlNXStringVector tech;
				NXString date = GetDateStr();
				tech.push_back(date);
				EditLableNote(members[idx],tech);
			}
			else if( 0 == strcmp("MATERIAL",note_name) )
			{
				StlNXStringVector tech;
				char mat[256];
				TYCOM_GetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_MATERIAL, mat);
				tech.push_back(mat);
				EditLableNote(members[idx],tech);
			}
			else if( 0 == strcmp("DRAWNO",note_name) )
			{
				StlNXStringVector tech;
				tech.push_back("DRAWNO");
				EditLableNote(members[idx],tech);;
			}
			else if( 0 == strcmp("DRAWER",note_name) )
			{
				StlNXStringVector tech;
				tech.push_back(drawer);
				EditLableNote(members[idx],tech);;
			}
			else if( 0 == strcmp("HEATPROCESS",note_name) )
			{
				StlNXStringVector tech;
				char heat[256];
				TYCOM_GetObjectStringAttribute( thisBody, ATTR_TYCOM_PROPERTY_HEAT_PROCESS, heat);
				tech.push_back(heat);
				EditLableNote(members[idx],tech);
			}
			else if( 0 == strcmp("SCALE",note_name) )
			{
				StlNXStringVector tech;
				char str[32]="";
				sprintf(str,"1:%g",scale);
				tech.push_back(str);
				EditLableNote(members[idx],tech);
			}
			else if( 0 == strcmp("DWGNO",note_name) )
			{
				StlNXStringVector tech;
				char dwgno[256] = "";
				TYCOM_GetObjectStringAttribute( thisBody, TY_ATTR_DRAWING_NO, dwgno);
				if(strlen(dwgno) > 0)
				{
					tech.push_back(dwgno);
					EditLableNote(members[idx],tech);
				}
			}
		}
	}
	UF_free(members);
	return 0;
}

//按照用户出bom的顺序排号 TY_ATTR_DRAWING_NO出bom时候会设置上去
static  logical CompareBody(tag_t &body1, tag_t &body2)
{
	NXString dwgno1, dwgno2;
	TYCOM_GetObjectStringAttribute( body1 , TY_ATTR_DRAWING_NO , dwgno1);
	TYCOM_GetObjectStringAttribute( body2 , TY_ATTR_DRAWING_NO , dwgno2);

	if (dwgno1.getLocaleText() == 0 || dwgno2.getLocaleText() != 0)
		return false;

	if (dwgno1.getLocaleText() != 0 || dwgno2.getLocaleText() == 0)
		return true;

	if (dwgno1.getLocaleText() == 0 || dwgno2.getLocaleText() == 0)
		return false;
	
	if (strlen(dwgno1.getLocaleText()) >0 && strlen(dwgno2.getLocaleText()) > 0)
	{
		if (strcmp(dwgno1.getLocaleText(),dwgno2.getLocaleText()) >= 0)
		    return false;
		return true;
	}

	return true;
}

static int SortBomBodies(vtag_t &bomBodies)
{
	std::sort(bomBodies.begin(),bomBodies.end(),CompareBody);   
	return 0;
}

int TY_AutoDrafting2(vtag_t &allBodies, NXString drawer)
{
	int errorCode = 0;
    try
    {
		char inputfile[UF_CFI_MAX_PATH_NAME_SIZE]="";
		char outputfile[UF_CFI_MAX_PATH_NAME_SIZE]="";
		char filePath[MAX_FSPEC_SIZE] = "";
		char namestr[MAX_FSPEC_SIZE] = "";
		char part_fspec1[MAX_FSPEC_SIZE] = "";


		//第一步得到保存dwg文件的路径
		tag_t disp = UF_PART_ask_display_part();
		UF_PART_ask_part_name(disp,part_fspec1);
		uc4576(part_fspec1, 2, filePath, namestr);
        NXString savepath(filePath);

		
		//bodies排序
        SortBomBodies(allBodies);
     
	    vNXString refNames;
        for( int idx = 0; idx < allBodies.size(); ++idx )
        {
     
			vtag_t bodies;
			bodies.push_back(allBodies[idx]);
			char  crefName[32] = "";
			sprintf_s(crefName,"BODY_%d",idx);
			NXString refName(crefName);
			refNames.push_back(refName);
            CreateReferenceSet(bodies,refName);
        }

		//第三步:创建一个dwg模板的part，这里面带了很多预先的设置
        tag_t newpart = CreateDWGPart();
        if( NULL_TAG == newpart )
            return 1;
        UF_PART_ask_part_name(newpart,inputfile);
        for( int idx = 0; idx < allBodies.size(); ++idx )
        {
            tag_t view = NULL_TAG;
            tag_t viewl = NULL_TAG;
            tag_t viewr = NULL_TAG;
            double scale = 1;
			double direction[3][3]={0};
			double viewldir[3][3]={0};
			double viewrdir[3][3]={0};
            double viewbound[4] = {0};

			GetTopViewProjectDirection( disp, refNames[idx], direction );

            tag_t group = CreateDrawingViewDWG(disp,allBodies[idx],view,viewl,viewr,refNames[idx],NXString("A4横"),NXString("钢材"),viewbound,scale);
            GZ_SetDrawingNoteInformation(allBodies[idx],group,scale,refNames[idx],drawer);
            RY_DWG_create_demention(disp,view,scale,direction);
			for( int i = 0; i< 3; i++)
				viewldir[0][i] = direction[0][i];
			for( int i = 0; i< 3; i++)
				viewldir[1][i] = direction[2][i];
            RY_DWG_create_demention(disp,viewl,scale,viewldir);
			for( int i = 0; i< 3; i++)
				viewrdir[0][i] = direction[2][i];
			for( int i = 0; i< 3; i++)
				viewrdir[1][i] = direction[1][i];
            RY_DWG_create_demention(disp,viewr,scale,viewrdir);
            UF_PART_save();

			NXString dwgno;
			TYCOM_GetObjectStringAttribute( allBodies[idx] , TY_ATTR_DRAWING_NO , dwgno);
			if (dwgno.getLocaleText() != 0 && strlen(dwgno.getLocaleText()) > 0)
			    sprintf(outputfile,"%s\\%s.dwg",savepath.GetLocaleText(),dwgno.GetLocaleText());
			else
                sprintf(outputfile,"%s\\%s.dwg",savepath.GetLocaleText(),refNames[idx].GetLocaleText());
            export_sheet_to_acad_dwg2d2(inputfile,outputfile,refNames[idx]);
        }
        UF_PART_close(newpart,0,1);
        UF_PART_set_display_part(disp);
        //theSession->ApplicationSwitchImmediate("UG_APP_MODELING");
        char cmd[512]="";
        sprintf_s(cmd,"start %s",savepath.GetLocaleText());
        system(cmd);    
    }
    catch(exception& ex)
    {
		char str[256] = "";
		strcpy(str,ex.what());
		uc1601(str,1);
        errorCode = 1;
    }
    return errorCode;
}
