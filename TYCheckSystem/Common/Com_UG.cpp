#include "Com_UG.h"
#include <NXOpen/Session.hxx>
#include <NXOpen/NXMessageBox.hxx>
#include <NXOpen/NXException.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Features_ExtrudeBuilder.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/SectionCollection.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/DirectionCollection.hxx>
#include <NXOpen/GeometricUtilities_BooleanOperation.hxx>
#include <NXOpen/GeometricUtilities_Extend.hxx>
#include <NXOpen/GeometricUtilities_FeatureOffset.hxx>
#include <NXOpen/GeometricUtilities_FeatureOptions.hxx>
#include <NXOpen/GeometricUtilities_Limits.hxx>
#include <NXOpen/GeometricUtilities_MultiDraft.hxx>
#include <NXOpen/GeometricUtilities_SimpleDraft.hxx>
#include <NXOpen/Curve.hxx>
#include <NXOpen/Arc.hxx>
#include <NXOpen/CurveDumbRule.hxx>
#include <NXOpen/Spline.hxx>
#include <NXOpen/SplineCollection.hxx>
#include <NXOpen/NXObjectManager.hxx>
#include <NXOpen/ScRuleFactory.hxx>
#include <NXOpen/SelectionIntentRule.hxx>
#include <Windows.h>
#include <winbase.h>
#include <uf_vec.h>
#include <NXOpen/Features_RuledBuilder.hxx>
#include <NXOpen/GeometricUtilities_AlignmentMethodBuilder.hxx>
#include <NXOpen/EdgeDumbRule.hxx>
#include <algorithm>
#include <iostream>
#include <NXOpen/Features_NSidedSurfaceBuilder.hxx>
#include <NXOpen/BlockStyler_PropertyList.hxx>
#include <uf_part.h>
#include <NXOpen/Part.hxx>
#include <NXOpen/BasePart.hxx>
#include <math.h>
#include <float.h>
#include <uf_assem.h>
#include <NXOpen/ScCollectorCollection.hxx>
#include <NXOpen/Features_SplitBodyBuilder.hxx>
#include <NXOpen/Plane.hxx>
#include <uf_csys.h>
//#include <NXOpen/BodyDumbRule.hxx>
#include <NXOpen/Features_SplitBody.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_SplitBodyBuilder.hxx>
#include <NXOpen/Features_BooleanBuilder.hxx>
#include <NXOpen/SelectBodyList.hxx>
#include <NXOpen/Features_Geomcopy.hxx>
#include <NXOpen/PlaneCollection.hxx>
#include <NXOpen/Features_GeomcopyBuilder.hxx>
#include <NXOpen/BodyCollection.hxx>
//#include <NXOpen\Features_IContainerFeature.hxx>
//#include <NXOpen/AttributeManager.hxx>
//#include <NXOpen/AttributePropertiesBaseBuilder.hxx>
//#include <NXOpen/AttributePropertiesBuilder.hxx>
#include <NXOpen/Features_ProjectCurveBuilder.hxx>
#include <NXOpen/Line.hxx>
#include <NXOpen/FaceDumbRule.hxx>
#include <NXOpen/Features_ChamferBuilder.hxx>
#include <NXOpen/EdgeTangentRule.hxx>
#include <NXOpen/XformCollection.hxx>
#include <NXOpen/CoordinateSystemCollection.hxx>
#include <NXOpen/ImportManager.hxx>
#include <NXOpen/PartImporter.hxx>
//#include <NXOpen/Features_Text.hxx>
//#include <NXOpen/Features_TextBuilder.hxx>
#include <NXOpen/XformCollection.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/ModelingViewCollection.hxx>
#include <NXOpen/ModelingView.hxx>
//#include <NXOpen/Features_ToolingBox.hxx>
//#include <NXOpen/Features_ToolingBoxBuilder.hxx>
//#include <NXOpen/Features_ToolingFeatureCollection.hxx>
#include <NXOpen/SelectCoordinateSystem.hxx>
#include <uf_defs.h>
#include <NXOpen/Features_MoveObject.hxx>
#include <NXOpen/Features_MoveObjectBuilder.hxx>
#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/SelectNXObjectList.hxx>
#include <uf_obj_types.h>
#include <NXOpen/Features_WaveLinkBuilder.hxx>
#include <NXOpen/Assemblies_Component.hxx>
//#include <NXOpen/GeometricUtilities_WaveLinkRepository.hxx>
#include <NXOpen/Features_ExtractFace.hxx>
#include <NXOpen/Assemblies_ComponentAssembly.hxx>
#include <uf_so.h>
#include <uf_wave.h>
#include <NXOpen/Features_Extrude.hxx>
#include <NXOpen/Ellipse.hxx>
#include <NXOpen/Features_CompositeCurve.hxx>
#include <NXOpen/CurveFeatureRule.hxx>
#include <NXOpen/Drawings_DrawingSheet.hxx>
#include <NXOpen/Drawings_DrawingSheetCollection.hxx>
#include <atlstr.h>
#include <NXOpen/ReferenceSet.hxx>
#include <NXOpen/Features_DatumPlaneFeature.hxx>
#include <NXOpen/Features_DatumPlaneBuilder.hxx>
#include <NXOpen/DatumPlane.hxx>
#include <NXOpen/Preferences_PartVisualizationLine.hxx>
#include <NXOpen/Features_OffsetFaceBuilder.hxx>
#include "Com_Attribute.h"
#include "../Common/TY_Def.h"
#include <uf_mtx.h>
#include <uf_drf.h>
#include <NXOpen/Annotations_DraftingNoteBuilder.hxx>
#include <NXOpen/ViewCollection.hxx>
#include <NXOpen/View.hxx>
#include <NXOpen/WCS.hxx>
#include <NXOpen/Annotations_SimpleDraftingAid.hxx>
#include <NXOpen/Annotations_AnnotationManager.hxx>
#include <NXOpen/FontCollection.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/ModelingViewCollection.hxx>
#include <NXOpen/ModelingView.hxx>
#include <NXOpen/SelectDisplayableObject.hxx>
#include <NXOpen/NXTo2dCreator.hxx>
#include <NXOpen/DexManager.hxx>
#include <uf_trns.h>

using namespace NXOpen;
using namespace std;

extern Session *theSession;
extern UI *theUI;


//This function get the length of input curve.
int TYCOM_CurveGetLength(tag_t curve, double &len)
{
	if(curve == NULL_TAG)
		return 1;

	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(curve);
	Curve *pcurve =  dynamic_cast<Curve*> (tagobj);
	if(pcurve != NULL)
	{
		len = pcurve->GetLength();
		return 0;
	}

	Edge *pedge =  dynamic_cast<Edge*> (tagobj);
	if(pedge != NULL)
	{
		len = pedge->GetLength();
		return 0;
	}
	return 1;
}

//This function get the length of input curve between two input parms.
int TYCOM_CurveGetLengthAccordParms(tag_t curve, double startParm, double endParm, double &len)
{
	if (curve == NULL_TAG)
		return 1;
	double lenAll = 0;
    TYCOM_CurveGetLength(curve, lenAll);

	UF_EVAL_p_t evaluator = NULL;
	double limits[2] = {0.0, 0.0};
	UF_EVAL_initialize(curve, &evaluator);
	UF_EVAL_ask_limits(evaluator, limits);
	UF_EVAL_free(evaluator);
	len = lenAll * (fabs(endParm - startParm)/fabs(limits[1] - limits[0]));
	return 0;
}

//This function get the start and end points of input curve.
int TYCOM_CurveGetStartEndPoints(tag_t curve, double start[3], double end[3])
{
	UF_EVAL_p_t evaluator = NULL;
	double limits[2] = {0.0, 0.0};
	UF_EVAL_initialize(curve, &evaluator);
	UF_EVAL_ask_limits(evaluator, limits);
	UF_EVAL_evaluate(evaluator, 0, limits[0], start, NULL);
	UF_EVAL_evaluate(evaluator, 0, limits[1], end, NULL);
	UF_EVAL_free(evaluator);
	return 0;
}

//This funcion check whether the input point is on the curve.
bool TYCOM_CurveCheckPointOnCurve(tag_t curve, double pnt[3])
{
	UF_EVAL_p_t evaluator = NULL;
	double limits[2] = {0.0, 0.0};
	UF_EVAL_initialize(curve, &evaluator);
	double parm = 0, closest_point[3];
	UF_EVAL_evaluate_closest_point(evaluator, pnt, &parm, closest_point );
	UF_EVAL_free(evaluator);
	double tol = 0.0;
	UF_MODL_ask_distance_tolerance(&tol);
	double dis = 0;
	UF_VEC3_distance(closest_point, pnt, &dis);
	return MATH_is_zero(dis, tol);
}

//This function check whether the input edge is the edge of input face.
bool TYCOM_EdgeCheckOnFace(tag_t edgeToCheck, tag_t face)
{
	uf_list_p_t edge_list;
	UF_MODL_ask_face_edges(face, &edge_list);
	int count = 0;
	UF_MODL_ask_list_count(edge_list, &count);
	for(int i = 0; i < count; ++i )
	{
		tag_t edge = NULL_TAG;
		UF_MODL_ask_list_item(edge_list, i, &edge);
		if(edge == edgeToCheck)
		{
			UF_MODL_delete_list(&edge_list);
			return true;
		}
	}
	UF_MODL_delete_list(&edge_list);
	return false;
}

//This function get the minimum distance of two input objects. And outpur two points.
int TYCOM_AskMinimumDist(tag_t obj1, tag_t obj2, double &dis, double *pnt1, double *pnt2)
{
	double pt_on_obj1 [3] = {0.0, 0.0, 0.0}, pt_on_obj2 [3] = {0.0, 0.0, 0.0};
	double guess1[3] = {0.0, 0.0, 0.0}, guess2[3] = {0.0, 0.0, 0.0};
	int ret = 0;
	ret = UF_MODL_ask_minimum_dist(obj1, obj2, 
		0, guess1, 
		0, guess2,
        &dis, pt_on_obj1, pt_on_obj2);

	if(pnt1 != NULL)
	{
		memcpy(pnt1, pt_on_obj1, sizeof(double) * 3);
	}
	if(pnt2 != NULL)
	{
		memcpy(pnt2, pt_on_obj2, sizeof(double) * 3);
	}
	return ret;
}

//This function get the minimum distance of input object and input guess point. 
//And return the result point on the input object.
int TYCOM_AskMinimumDist(tag_t obj1, double inutpnt[3], double &dis, double *pnt1)
{
	double pt_on_obj1 [3] = {0.0, 0.0, 0.0}, pt_on_obj2 [3] = {0.0, 0.0, 0.0};
	double guess1[3] = {0.0, 0.0, 0.0};
	int ret = 0;
	UF_MODL_ask_minimum_dist(obj1, NULL_TAG, 
		0, guess1, 
		1, inutpnt,
        &dis, pt_on_obj1, pt_on_obj2);
	if(pnt1 != NULL)
	{
		memcpy(pnt1, pt_on_obj1, sizeof(double) * 3);
	}
	return ret;
}

typedef int (* AskMaximumDist)(unsigned int obj1, double guess1[3], double mtx1[16],
	                                    unsigned int obj2, double guess2[3], double mtx2[16],
										bool isexact, double pt1[3], double pt2[3]);
//This function get the max distance of two input objects. And return the two result points.
int TYCOM_AskMaxDist(tag_t obj1, tag_t obj2, double &dis, double *pnt1, double *pnt2 )
{
	static HINSTANCE hInst = NULL;
	AskMaximumDist GetMaxDist = NULL;
	if(hInst == NULL)
	{
	    hInst=LoadLibraryA("libmodlgeom.dll");
	    GetMaxDist =(AskMaximumDist)GetProcAddress(hInst,"?JAUTL_SINGLE_MEASURE_ask_maximum_dist@@YAHIQEANPEAUTransformMatrix@Math@UGS@@I01_N00@Z");
	}
	else
		GetMaxDist =(AskMaximumDist)GetProcAddress(hInst,"?JAUTL_SINGLE_MEASURE_ask_maximum_dist@@YAHIQEANPEAUTransformMatrix@Math@UGS@@I01_N00@Z");
	if(GetMaxDist == NULL)
		return 1;

	double pt1[3] = {0.0}, pt2[3] = {0.0}, 
           guess1[3] = {0.0}, guess2[3] = {0.0}, distance = -DBL_MAX;

	GetMaxDist( obj1, guess1, NULL, obj2, guess2, NULL, false, pt1, pt2);
    UF_VEC3_distance(pt1, pt2, &dis);
	if(pnt1 != NULL)
		memcpy(pnt1, pt1, sizeof(double) * 3);
	if(pnt2 != NULL)
		memcpy(pnt2, pt2, sizeof(double) * 3);
	//::FreeLibrary(hInst);//No need to free this library.
	return 0;
}

typedef int (* NX_EXPORT_AskFaceArea)(int nfaces, unsigned int *faces, double accuracy, double props[2], double *error);
//This function get the max distance of two input objects. And return the two result points.
int UF_AskFaceArea(tag_t face, double *area )
{
	if(area == NULL || face == NULL_TAG)
		return -1;
	static HINSTANCE hInst = NULL;
	NX_EXPORT_AskFaceArea AskFaceArea = NULL;
	if(hInst == NULL)
	{
	    hInst=LoadLibraryA("libgeom.dll");
	    AskFaceArea =(NX_EXPORT_AskFaceArea)GetProcAddress(hInst,"?MEASURE_calculate_area_property@@YAHHPAINQANPAN@Z");
	}
	else
		AskFaceArea =(NX_EXPORT_AskFaceArea)GetProcAddress(hInst,"?MEASURE_calculate_area_property@@YAHHPAINQANPAN@Z");
	if(AskFaceArea == NULL)
		return -2;
	double props[2] = {0.0, 0.0};
	double error = 0;
	AskFaceArea(1, &face, 1.0,  props, &error);
	*area = props[0];
	//::FreeLibrary(hInst);
	return 0;
}

//This function get the tags from list and put then in a vector.
int TYCOM_AskListItems(uf_list_p_t  &list, vtag_t & listTags)
{
	int count = 0;
	UF_MODL_ask_list_count(list, &count);
	for(int i = 0; i < count; ++i)
	{
		tag_t obj = NULL_TAG;
		UF_MODL_ask_list_item(list, i, &obj);
		listTags.push_back(obj);
	}
	return 0;
}

//This function get the tags from list and put then in a vector.
//Then delete the input list.
int TYCOM_AskListItemsAndDelete(uf_list_p_t  &list, vtag_t & listTags)
{
	int count = 0;
	UF_MODL_ask_list_count(list, &count);
	if(count == 0)
		return 0;
	for(int i = 0; i < count; ++i)
	{
		tag_t obj = NULL_TAG;
		UF_MODL_ask_list_item(list, i, &obj);
		listTags.push_back(obj);
	}
	UF_MODL_delete_list(&list);
	return 0;
}

//This function get the common edge of two faces.
int TYCOM_AskFaceFaceEdges(tag_t face1, tag_t face2, vtag_t &edges)
{
	int ret = 0;
	if(face1 == NULL_TAG || face2 == NULL_TAG)
		return 1;
	uf_list_p_t edge_list1, edge_list2; 
	ret = UF_MODL_ask_face_edges(face1, &edge_list1);
	if(ret != 0)
		return 1;
	ret = UF_MODL_ask_face_edges(face2, &edge_list2);
	if(ret != 0)
		return 1;
	int count1 = 0, count2 = 0;
	UF_MODL_ask_list_count(edge_list1, &count1);
	UF_MODL_ask_list_count(edge_list2, &count2);
	vtag_t edges1;
	for(int i = 0; i < count1; ++i)
	{
		tag_t edge = NULL_TAG;
		UF_MODL_ask_list_item(edge_list1, i, &edge);
		edges1.push_back(edge);
	}
	UF_MODL_delete_list(&edge_list1);

	for(int i = 0; i < count2; ++i)
	{
		tag_t edge = NULL_TAG;
		UF_MODL_ask_list_item(edge_list2, i, &edge);
		if(std::find(edges1.begin(), edges1.end(), edge) != edges1.end())
		{
			edges.push_back(edge);
		}
	}
	UF_MODL_delete_list(&edge_list2);
	return 0;
}

int TYCOM_AskEdgeEdgeFace(tag_t edge1, tag_t edge2, tag_t &face)
{
    int ret = 1;
    logical found = false;
	if(edge1 == NULL_TAG || edge2 == NULL_TAG)
		return 1;
    uf_list_p_t face_list1, face_list2; 
	ret = UF_MODL_ask_edge_faces(edge1, &face_list1);
	if(ret != 0)
		return 1;
	ret = UF_MODL_ask_edge_faces(edge2, &face_list2);
	if(ret != 0)
		return 1;
    int count1 = 0, count2 = 0;
	UF_MODL_ask_list_count(face_list1, &count1);
	UF_MODL_ask_list_count(face_list2, &count2);
	for(int i = 0; i < count1; ++i)
	{
		tag_t face1 = NULL_TAG;
		UF_MODL_ask_list_item(face_list1, i, &face1);
        for(int j = 0; j < count2; ++j)
        {
            tag_t face2 = NULL_TAG;
            UF_MODL_ask_list_item(face_list2, j, &face2);
            if( face1 == face2)
            {
                face = face1;
                found = true;
                break;
            }
        }
        if(found)
            break;
	}
	UF_MODL_delete_list(&face_list1);
	UF_MODL_delete_list(&face_list2);
    return ret;
}

//This function trim a solid body, and keep the result body which is near to the input reference object.
int TYCOM_BodyTrimAndReferenceObj(tag_t body, tag_t tool,tag_t &frec, tag_t reference )
{
	if(body == NULL_TAG || tool == NULL_TAG)
		return 1;

	double tol = 0.0;
	UF_MODL_ask_distance_tolerance(&tol);

	if(reference == NULL_TAG)
	{
		UF_MODL_trim_body(body, tool, 0, &frec);
		return 0;
	}

	double dis1 = 0, dis2 = 0;
	TYCOM_AskMinimumDist(body, reference, dis1);
	UF_MODL_trim_body(body, tool, 0, &frec);
	TYCOM_AskMinimumDist(body, reference, dis2);
	if(MATH_is_less2(dis2, dis1, tol))
	{
		vtag_t tags;
		tags.push_back(frec);
		TYCOM_DeleteFrecs(tags);
		UF_MODL_trim_body(body, tool, 1, &frec);
	}
	return 0;
}

//This function extend a input line by input value.
//You can choose to just extend start or end part of this line.
int TYCOM_CurveExtendCurve(tag_t line, bool extendStart, bool extendEnd, double value)
{
	double tol = 0.0;
	UF_MODL_ask_distance_tolerance(&tol);
	if(line == NULL_TAG || MATH_is_zero(value, tol))
		return 1;
	
	UF_CURVE_line_t data;
	TYCOM_CurveGetStartEndPoints(line, data.start_point, data.end_point);
	double dis = 0, scale = 1;
	UF_VEC3_distance(data.start_point, data.end_point, &dis);
	scale  = value/dis;
	if(extendStart)
	{
		//double pt[3] = {end[0] - start[0], end[1] - start[1], end[2] - start[2]};
		double pt[3] = {data.start_point[0] - data.end_point[0], 
			            data.start_point[1] - data.end_point[1], 
						data.start_point[2] - data.end_point[2]};
		
		double vec_comb [3];
		UF_VEC3_affine_comb(pt, scale, pt, vec_comb);
		data.start_point[0] = vec_comb[0] + data.end_point[0];
		data.start_point[1] = vec_comb[1] + data.end_point[1];
		data.start_point[2] = vec_comb[2] + data.end_point[2];
	}

	if(extendEnd)
	{
		double pt[3] = { data.end_point[0] - data.start_point[0],  
			             data.end_point[1] - data.start_point[1], 
						 data.end_point[2] - data.start_point[2]};
		double vec_comb [3];
		UF_VEC3_affine_comb(pt, scale, pt, vec_comb);
		data.end_point[0] = vec_comb[0] + data.start_point[0];
		data.end_point[1] = vec_comb[1] + data.start_point[1];
		data.end_point[2] = vec_comb[2] + data.start_point[2];
	}

	UF_CURVE_edit_line_data(line, &data);
	return 0;
}


//This function get the intersection point of input curve and another object.
//If there are more than one points, the input ref point is help to output the closeest intersection to this point.
int TYCOM_CurveGetObjectIntersectPoint(tag_t curve, tag_t object, double pnt[3], double *ref)
{
	if(curve == NULL_TAG || object == NULL_TAG)
		return -1;
	double ref_point[3] = {0,0,0};
	if(ref != NULL)
		memcpy(ref_point,ref, sizeof(double)*3);
	UF_CURVE_intersect_info_t out_info;
	UF_CURVE_intersect(curve, object, ref_point, &out_info);
	if(out_info.type_of_intersection != 0)
	{
		memcpy(pnt, out_info.curve_point, sizeof(double) * 3);
	    return 0;
	}
	else
		return 1;
}

//This function get the normal of mid point of input face.
int TYCOM_FaceAskMidPointNormal(tag_t face, double normal[3])
{
	if(face == NULL_TAG)
		return -1;
	double uv_min_max[4] = {0,0,0,0};
	int ret = 0;
	ret = UF_MODL_ask_face_uv_minmax(face, uv_min_max);
	double param[2] = {(uv_min_max[0] + uv_min_max[1])/2.0,
		               (uv_min_max[2] + uv_min_max[3])/2.0}, 
	       point[3] = {0,0,0}, 
		   u1[3] = {0,0,0}, v1[3] = {0,0,0},
		   u2[3] = {0,0,0}, v2[3] = {0,0,0}, 
		   radii[2] = {0,0};

	ret = UF_MODL_ask_face_props(face, param, point, u1, v1, u2, v2, normal, radii);
	return ret;
}

//This function get the normal of mid point of input face.
int TYCOM_FaceAskMidPointNormal(tag_t face, double normal[3], double point[3])
{
	if(face == NULL_TAG)
		return -1;
	double uv_min_max[4] = {0,0,0,0};
	int ret = 0;
	ret = UF_MODL_ask_face_uv_minmax(face, uv_min_max);
	double param[2] = {(uv_min_max[0] + uv_min_max[1])/2.0,
		               (uv_min_max[2] + uv_min_max[3])/2.0}, 
		   u1[3] = {0,0,0}, v1[3] = {0,0,0},
		   u2[3] = {0,0,0}, v2[3] = {0,0,0}, 
		   radii[2] = {0,0};

	ret = UF_MODL_ask_face_props(face, param, point, u1, v1, u2, v2, normal, radii);
	return ret;
}

//This function get the limits of input curve.
int TYCOM_CurveGetLimits(tag_t curve, double limit[2])
{
	UF_EVAL_p_t evaluator = NULL;
	double limits[2] = {0.0, 0.0};
	UF_EVAL_initialize(curve, &evaluator);
	UF_EVAL_ask_limits(evaluator, limit);
	UF_EVAL_free(evaluator);
	return 0;
}

//This function get the parm from a input point.
int TYCOM_CurveGetParmFromPoint(tag_t curve, double pnt[3], double &parm)
{
	UF_EVAL_p_t evaluator = NULL;
	double limits[2] = {0.0, 0.0};
	UF_EVAL_initialize(curve, &evaluator);
	double closest_point[3];
	UF_EVAL_evaluate_closest_point(evaluator, pnt, &parm, closest_point );
	UF_EVAL_free(evaluator);
	return 0;
}

//This function get the point from input curve and related parm.
int TYCOM_CurveGetPointFromParm(tag_t curve, double parm, double pnt[3])
{
	UF_EVAL_p_t evaluator = NULL;
	double limits[2] = {0.0, 0.0};
	UF_EVAL_initialize(curve, &evaluator);
	double derivatives[3];
	UF_EVAL_evaluate(evaluator, 0, parm, pnt, derivatives);
	UF_EVAL_free(evaluator);
	return 0;
}

//small cycle --- 1, else -1
//This function help to check input checkParm is between parm1 and parm2.
bool TYCOM_CurveIsInParm(double parm1, double parm2, double checkParm)
{
	double value = (checkParm - parm1) * (checkParm - parm2);
	if(value  > 0 ) 
		return 0;
	else
		return 1;
}

//This function help the check whether checkParm1 and checkParm2 are contain the zero point of input a closed curve.
bool TYCOM_CurveIsKuaiYue(double parm1, double parm2, double checkParm1, double checkParm2, int isSmall)
{
	double value = fabs(checkParm1 - checkParm2);
	double value1 = fabs(parm1 - parm2);
	if(isSmall)
	{
		if(value * 2 > value1)
			return true;
		else
			return false;
	}
	else
	{
		if(value * 2 > value1)
			return false;
		else
			return true;
	}
}

//This function help to check whether the input curve is closed.
bool TYCOM_CurveIsClosed(tag_t curve)
{
	double tol = 0.0;
	UF_MODL_ask_distance_tolerance(&tol);
	double start[3] = {0,0,0},end[3] = {0,0,0};
	TYCOM_CurveGetStartEndPoints(curve, start, end);
	double dis = 0;
	UF_VEC3_distance(start, end, &dis);
	int closed = UF_MODL_ask_curve_closed(curve);
	if(MATH_is_zero(dis, tol) || closed)
		return true;
	else 
		return false;
}

//This function transform a point along a direction with input distance.
int TYCOM_TransPnt(Point3d &pnt, double dir[3], double dis)
{
	//UF_VEC3_add
	double magnitude = 0;
	UF_VEC3_mag(dir, &magnitude);
	if (MATH_is_zero(magnitude,DOUBLE_TOL))
		return 1;
	double scale = dis/magnitude;
	double vec[3] = {pnt.X, pnt.Y, pnt.Z};
	double vec_comb[3] = {0,0,0};
	UF_VEC3_affine_comb(vec, scale, dir, vec_comb);
	pnt.X = vec_comb[0];
	pnt.Y = vec_comb[1];
	pnt.Z = vec_comb[2];
	return 0;
}

//This function create a plane at the related parm of a curve.
//The plane normal is the tangent of curve.
int TYCOM_CreatePlaneAccordingToParm(tag_t curve,  double parm, tag_t &planeTag)
{
	UF_EVAL_p_t evaluator = NULL;
	double normal[3] = {0.0, 0.0, 0.0},
		binormal[3] = {0.0, 0.0, 0.0},
		point[3] = {0.0, 0.0, 0.0},
		tangent[3] = {0.0, 0.0, 0.0};
	UF_EVAL_initialize(curve, &evaluator);
	UF_EVAL_evaluate_unit_vectors(evaluator, parm, point, tangent, normal, binormal);
	UF_EVAL_free(evaluator);

	UF_MODL_create_plane(point, tangent, &planeTag);
	return 0;
}

int TYCOM_GetDisplayPartFeatures(vtag_t &feats)
{
	tag_t part = UF_PART_ask_display_part();
	if(part == NULL_TAG)
		return 0;
	tag_t feature = NULL_TAG;
	UF_OBJ_cycle_objs_in_part( part, UF_feature_type, &feature );
    while ( feature != NULL_TAG )
    {
		feats.push_back(feature);
        UF_OBJ_cycle_objs_in_part( part, UF_feature_type, &feature );
    }
	return 0;
}

int TYCOM_GetWorkPartFeatures(vtag_t &feats)
{
	tag_t part = UF_ASSEM_ask_work_part();
	if(part == NULL_TAG)
		return 0;
	tag_t feature = NULL_TAG;
	UF_OBJ_cycle_objs_in_part( part, UF_feature_type, &feature );
    while ( feature != NULL_TAG )
    {
		feats.push_back(feature);
        UF_OBJ_cycle_objs_in_part( part, UF_feature_type, &feature );
    }
	return 0;
}

int TYCOM_ask_line_endpt( tag_t line_id,  double *start_p, double *end_p )
{
	int irc = 0;
	double start_parm = 0.0, end_parm = 0.0, torsion = 0.0, rad_of_cur = 0.0,
		tangent[3] = {0.0, 0.0, 0.0}, p_norm[3] = {0.0, 0.0, 0.0},
		b_norm[3] = {0.0, 0.0, 0.0};

	start_parm = 0.0;
	end_parm = 1.0;

	if( (irc = UF_MODL_ask_curve_props( line_id, start_parm, start_p, tangent, p_norm,
		b_norm, &torsion, &rad_of_cur )) ) return( irc );

	irc = UF_MODL_ask_curve_props( line_id, end_parm, end_p, tangent, p_norm,
		b_norm, &torsion, &rad_of_cur );

	return( irc );
}

int TYCOM_is_curve_adjacent( tag_t edge1, tag_t edge2,  int *is_adj , int *start)
{
	if (edge1 == edge2)
	{
		*is_adj = 0;
	    return(0);
	}
	
	int irc = 0;
	double pt1[3] = {0.0, 0.0, 0.0}, pt2[3] = {0.0, 0.0, 0.0}, 
		pt3[3] = {0.0, 0.0, 0.0}, pt4[3] = {0.0, 0.0, 0.0},
		dis1 = 0.0, dis2 = 0.0, dis3 = 0.0, dis4 = 0.0;

	*is_adj = 0;

	if( (irc = TYCOM_ask_line_endpt( edge1, pt1, pt2 )) ) return( irc );
	if( (irc = TYCOM_ask_line_endpt( edge2, pt3, pt4 )) ) return( irc );

	UF_VEC3_distance( pt1, pt3, &dis1 );
	UF_VEC3_distance( pt1, pt4, &dis2 );
	UF_VEC3_distance( pt2, pt3, &dis3 );
	UF_VEC3_distance( pt2, pt4, &dis4 );

	double tol = 0;
	UF_MODL_ask_distance_tolerance(&tol);
	if( dis1 < tol || dis2 < tol || dis3 < tol || dis4 < tol )
		*is_adj = 1;
	else *is_adj = 0;

	if (start != NULL && (*is_adj == 1))
	{
		if (dis1 < tol)
			*start = 1;
		else if(dis2 < tol)
			*start = 2;
		else if(dis3 < tol)
			*start = 3;
		else if (dis4 < tol)
			*start = 4;
	}
	
	return(0);
}

//This function delete all input features in vector.
int TYCOM_DeleteFrecs(vtag_t &tags)
{
	uf_list_p_t frecList = NULL;
	UF_MODL_create_list(&frecList);
	for(int i = 0; i < (int)tags.size(); ++i)
	    UF_MODL_put_list_item(frecList, tags[i]);
	UF_MODL_delete_feature (frecList);
	UF_MODL_delete_list(&frecList);
	return 0;
}

int TYCOM_GetCurrentPartSolidBodies(vtag_t &bodies)
{
	int type = 0, subtype = 0;
	tag_t part = UF_PART_ask_display_part();
	if(part == NULL_TAG)
		return 0;
	tag_t feature = NULL_TAG;
	UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    while ( feature != NULL_TAG )
    {
		UF_OBJ_ask_type_and_subtype(feature, &type, &subtype);
		if(type == UF_solid_type && subtype == UF_solid_body_subtype )
		    bodies.push_back(feature);
        UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    }
	return 0;
}

int TYCOM_GetCurrentPartSolidBodies2(vtag_t &bodies)
{
	int type = 0, subtype = 0;
	tag_t part = UF_ASSEM_ask_work_part();
	if(part == NULL_TAG)
		return 0;
	tag_t feature = NULL_TAG;
	UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    while ( feature != NULL_TAG )
    {
		UF_OBJ_ask_type_and_subtype(feature, &type, &subtype);
		if(type == UF_solid_type && subtype == UF_solid_body_subtype )
		    bodies.push_back(feature);
        UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    }
	return 0;
}

int TYCOM_GetPartSolidBodies(tag_t part, vtag_t &bodies)
{
	int type = 0, subtype = 0;
	if(part == NULL_TAG)
		return 0;
	tag_t feature = NULL_TAG;
	
	UF_OBJ_cycle_objs_in_part( TYCOM_Prototype(part), UF_solid_type, &feature );
    while ( feature != NULL_TAG )
    {
		UF_OBJ_ask_type_and_subtype(feature, &type, &subtype);
		if(type == UF_solid_type && subtype == UF_solid_body_subtype )
		    bodies.push_back(feature);
        UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    }
	return 0;
}

int TYCOM_GetCurrentPartFaces(vtag_t &faces)
{
	int type = 0, subtype = 0;
	tag_t part = UF_PART_ask_display_part();
	if(part == NULL_TAG)
		return 0;
	tag_t feature = NULL_TAG;
	UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    while ( feature != NULL_TAG )
    {
		UF_OBJ_ask_type_and_subtype(feature, &type, &subtype);
		if(type == UF_solid_type && subtype == UF_solid_face_subtype )
		    faces.push_back(feature);
        UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    }
	return 0;
}

int TYCOM_GetCurrentPartEdges(vtag_t &edges)
{
	int type = 0, subtype = 0;
	tag_t part = UF_PART_ask_display_part();
	if(part == NULL_TAG)
		return 0;
	tag_t feature = NULL_TAG;
	UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    while ( feature != NULL_TAG )
    {
		UF_OBJ_ask_type_and_subtype(feature, &type, &subtype);
		if(type == UF_solid_type && subtype == UF_solid_edge_subtype )
		    edges.push_back(feature);
        UF_OBJ_cycle_objs_in_part( part, UF_solid_type, &feature );
    }
	return 0;
}

int TYCOM_GetCurrentPartArcs(vtag_t &arcs)
{
	tag_t part = UF_PART_ask_display_part();
	if(part == NULL_TAG)
		return 0;
	tag_t arc = NULL_TAG;
	UF_OBJ_cycle_objs_in_part( part, UF_circle_type, &arc );
    while ( arc != NULL_TAG )
    {
		arcs.push_back(arc);
        UF_OBJ_cycle_objs_in_part( part, UF_circle_type, &arc );
    }
	return 0;
}

//ͨ����ɫ���ֵ���ʽ ��ɫΪ��ʼ ��ɫΪ����
int TYCOM_GetPlanarFaces(vtag_t &faces, vtag_t &planarFaces, tag_t &planar, tag_t &planarend)
{
	int type = 0;
	UF_OBJ_disp_props_t disp_props;
	for(int i = 0; i < (int)faces.size(); i++)
	{
        UF_MODL_ask_face_type(faces[i], &type);
		if(type == UF_MODL_PLANAR_FACE)
		{
			planarFaces.push_back(faces[i]);
		}
	}


	//��ʱ������ ֱ�Ӳ��������ļ�����
	/*for(int i = 0; i < (int)planarFaces.size(); i++)
	{
		UF_OBJ_ask_display_properties(planarFaces[i], &disp_props);
		if(disp_props.color == 186)
		{
			planar = planarFaces[i];
			break;
		}
	}

	for(int i = 0; i < (int)planarFaces.size(); i++)
	{
		UF_OBJ_ask_display_properties(planarFaces[i], &disp_props);
		if(disp_props.color == 36)
		{
			planarend = planarFaces[i];
			break;
		}
	}*/

	return 0;
}

int TYCOM_GetPlanarFaces(vtag_t &faces, vtag_t &planarFaces)
{
	int type = 0;
	UF_OBJ_disp_props_t disp_props;
	for(int i = 0; i < (int)faces.size(); i++)
	{
        UF_MODL_ask_face_type(faces[i], &type);
		if(type == UF_MODL_PLANAR_FACE)
		{
			planarFaces.push_back(faces[i]);
		}
	}
	return 0;
}

int TYCOM_RemovePlanarFaces(vtag_t &faces)
{
	int type = 0;
	UF_OBJ_disp_props_t disp_props;
	for(int i = 0; i < (int)faces.size(); i++)
	{
        UF_MODL_ask_face_type(faces[i], &type);
		if(type == UF_MODL_PLANAR_FACE)
		{
			faces.erase(faces.begin() + i);
			i--;
		}
	}
	return 0;
}

int TYCOM_GetAdjFaces(tag_t seedFace, vtag_t & faces)
{
	uf_list_p_t adjacent_faces = NULL;
	UF_MODL_ask_adjac_faces(seedFace, &adjacent_faces);
	TYCOM_AskListItemsAndDelete(adjacent_faces, faces);
	return 0;
}

/*
 type UF_MODL_PLANAR_FACE
      UF_MODL_CYLINDRICAL_FACE
	  UF_MODL_TOROIDAL_FACE
*/
int TYCOM_GetAdjFacesWithType(tag_t seedFace, int facetype, tag_t & face, vtag_t &allfaces)
{
	vtag_t allAdjFaces;
	TYCOM_GetAdjFaces(seedFace, allAdjFaces);
	int type = 0;
	for(int i = 0; i < (int)allAdjFaces.size(); i++)
	{
		UF_MODL_ask_face_type(allAdjFaces[i], &type);
		if(type == facetype)
		{
			if(vFind(allfaces, allAdjFaces[i]) == -1)
			{
			    face = allAdjFaces[i];
				break;
			}
		}
	}
	if(face == NULL_TAG)
		return -1;
	for(int i = 0; i < (int)allAdjFaces.size(); i++)
	{
		if(vFind(allfaces, allAdjFaces[i]) == -1)
		    allfaces.push_back(allAdjFaces[i]);
	}
	return 0;
}

int TYCOM_GetArcEdge(vtag_t &edges, tag_t &edge)
{
	int edge_type = 0;
    for(int i = 0; i < (int)edges.size(); i++)
	{
		UF_MODL_ask_edge_type(edges[i], &edge_type);
		if(edge_type == UF_MODL_CIRCULAR_EDGE)
		{
			edge = edges[i];
			return 1;
		}
	}
	return 0;
}

int GetCurveCenter(tag_t curve, Point3d &centerpnt)
{
    if(curve == 0)
		return -1;

	int edge_type = 0;
	UF_MODL_ask_edge_type(curve, &edge_type);

	UF_CURVE_arc_t arc_coords;
	int ret = 0;
	if(edge_type == UF_MODL_CIRCULAR_EDGE)
	{
		//method1
	    /*ret = UF_CURVE_ask_arc_data(curve, &arc_coords);  //��������õ��� ���ĵ���Ҫ ���Ͼ��� ���������
		centerpnt.X = arc_coords.arc_center[0];
		centerpnt.Y = arc_coords.arc_center[1];
		centerpnt.Z = arc_coords.arc_center[2];
		*/

		/*TaggedObject * tagobj = NXOpen::NXObjectManager::Get(curve);
		NXOpen::Edge  *pedge =  dynamic_cast<NXOpen::Edge*> (tagobj);
		NXOpen::ICurve *pcurve = dynamic_cast<NXOpen::ICurve*> (pedge);
		NXOpen::Conic  *parc =  dynamic_cast<NXOpen::Conic*> (pcurve);
		centerpnt = parc->CenterPoint();*/

		UF_EVAL_p_t evaluator = 0;
		UF_EVAL_initialize(curve, &evaluator);
		UF_EVAL_arc_t arc;
		UF_EVAL_ask_arc(evaluator, &arc);
		centerpnt.X = arc.center[0];
		centerpnt.Y = arc.center[1];
		centerpnt.Z = arc.center[2];
		UF_EVAL_free(evaluator);
	}
	else
	{
		UF_EVAL_p_t evaluator = 0;
		UF_EVAL_initialize(curve, &evaluator);
		double      limits[2] = {0,0};
		UF_EVAL_ask_limits(evaluator, limits);
		double parm1 = limits[0], 
			   parm2 = limits[0] + (limits[1] - limits[0])/3.0,
			   parm3 = limits[0] + 2.0 * (limits[1] - limits[0])/3.0;

		double point1[3],  point2[3],  point3[3];
		double  tangent[3], normal[3], binormal[3];
		UF_EVAL_evaluate_unit_vectors(evaluator, parm1, point1, tangent, normal, binormal);
		UF_EVAL_evaluate_unit_vectors(evaluator, parm2, point2, tangent, normal, binormal);
		UF_EVAL_evaluate_unit_vectors(evaluator, parm3, point3, tangent, normal, binormal);

		tag_t arctag = 0;
        UF_CURVE_create_arc_thru_3pts(2,  point1, point2 ,point3, &arctag);
		UF_EVAL_free(evaluator);
		evaluator = 0;

		if(arctag != NULL_TAG)
		{
			UF_EVAL_initialize(arctag, &evaluator);
			UF_EVAL_arc_t arc;
			UF_EVAL_ask_arc(evaluator, &arc);
			centerpnt.X = arc.center[0];
			centerpnt.Y = arc.center[1];
			centerpnt.Z = arc.center[2];
			UF_EVAL_free(evaluator);
			UF_OBJ_delete_object(arctag);
		}
	}

	return 0;
}

int GetCurveRad(tag_t curve, double &rad)
{
    if(curve == 0)
		return -1;

	int edge_type = 0;
	UF_MODL_ask_edge_type(curve, &edge_type);

	UF_CURVE_arc_t arc_coords;
	int ret = 0;
	if(edge_type == UF_MODL_CIRCULAR_EDGE)
	{
		UF_EVAL_p_t evaluator = 0;
		UF_EVAL_initialize(curve, &evaluator);
		UF_EVAL_arc_t arc;
		UF_EVAL_ask_arc(evaluator, &arc);
		rad = arc.radius;
		UF_EVAL_free(evaluator);
	}
	else
	{
        UF_EVAL_p_t evaluator = 0;
		UF_EVAL_initialize(curve, &evaluator);
		double      limits[2] = {0,0};
		UF_EVAL_ask_limits(evaluator, limits);
		double parm1 = limits[0], 
			   parm2 = limits[0] + (limits[1] - limits[0])/3.0,
			   parm3 = limits[0] + 2.0 * (limits[1] - limits[0])/3.0;

		double point1[3],  point2[3],  point3[3];
		double  tangent[3], normal[3], binormal[3];
		UF_EVAL_evaluate_unit_vectors(evaluator, parm1, point1, tangent, normal, binormal);
		UF_EVAL_evaluate_unit_vectors(evaluator, parm2, point2, tangent, normal, binormal);
		UF_EVAL_evaluate_unit_vectors(evaluator, parm3, point3, tangent, normal, binormal);

		tag_t arctag = 0;
        UF_CURVE_create_arc_thru_3pts(2,  point1, point2 ,point3, &arctag);
		UF_EVAL_free(evaluator);
		evaluator = 0;


		if(arctag != NULL_TAG)
		{
			UF_EVAL_initialize(arctag, &evaluator);
			UF_EVAL_arc_t arc;
			UF_EVAL_ask_arc(evaluator, &arc);
			rad = arc.radius;
			UF_EVAL_free(evaluator);
			UF_OBJ_delete_object(arctag);
		}

		
	}

	return 0;
}

int GetArcRad(tag_t curve, double &rad)
{
	if(curve == 0)
		return -1;


	UF_EVAL_p_t evaluator = 0;
	UF_EVAL_initialize(curve, &evaluator);
	UF_EVAL_arc_t arc;
	UF_EVAL_ask_arc(evaluator, &arc);
	rad = arc.radius;
	UF_EVAL_free(evaluator);

	return 0;
}

int TYCOM_CreateLineWithExtendTwoSide(Point3d start, Point3d end, tag_t &line)
{
	UF_CURVE_line_t line_coords;
	memcpy(line_coords.start_point,&start, sizeof(double)*3);
	memcpy(line_coords.end_point,&end, sizeof(double)*3);
	UF_CURVE_create_line(&line_coords, &line);
	TYCOM_CurveExtendCurve(line, true, true);
	return 0;
}

int TYCOM_GetLineLineClosestPoint(tag_t line1, tag_t line2, double pnt[3])
{
    if(line1 == 0 || line2 == 0)
		return -1;

	double dis = 0;
	double pnt1[3] ={0,0,0}, pnt2[3] = {0,0,0};
	//��һ�ַ��� ���������߶ν����ཻ ���㲻׼
	/*if(TYCOM_CurveGetObjectIntersectPoint(line1, line2, pnt) == 0)
	{
        return 1;
	}
	else
	{*/
        TYCOM_AskMinimumDist(line1, line2, dis, pnt1, pnt2);
		pnt[0] = (pnt1[0] + pnt2[0])/2.0;
		pnt[1] = (pnt1[1] + pnt2[1])/2.0;
		pnt[2] = (pnt1[2] + pnt2[2])/2.0;
		return 2;
	//}
	return -1;
}

bool isPointEqual(Point3d a, Point3d b, double tol)
{
	double dist = sqrt((a.X - b.X)*(a.X - b.X) + (a.Y - b.Y)*(a.Y - b.Y) + (a.Z - b.Z)*(a.Z - b.Z));
	if (dist < tol)
		return true;
	//if(equ(a.x, b.x, tol) && equ(a.y, b.y, tol) && equ(a.z, b.z, tol))
	//return true;
	return false;
}

int TYCOM_SortArcsByName(vtag_t m_arcs)
{

	char namei[UF_OBJ_NAME_LEN+1] = "", namej[UF_OBJ_NAME_LEN+1] = "";

	for (int i = 0; i < (int)m_arcs.size(); i++)
	{
		for (int j = i +1; j < (int)m_arcs.size(); j++)
		{
			UF_OBJ_ask_name(m_arcs[i], namei);
			UF_OBJ_ask_name(m_arcs[j], namej);

			int cmp = strcmp(namei, namej);
			if (cmp)
			{
				tag_t vv = m_arcs[i];
				m_arcs[i] = m_arcs[j];
				m_arcs[j] = vv;
			}
		}
	} 
return 0;
}

bool TYCOM_IsTwoEdgeParall(tag_t edge1, tag_t edge2)
{
	UF_EVAL_p_t evaluator = 0;
	UF_EVAL_initialize(edge1, &evaluator);
	double      limits[2] = {0,0};
	UF_EVAL_ask_limits(evaluator, limits);
	double parm1 = limits[0], 
		   parm2 = limits[0] + (limits[1] - limits[0])/3.0,
		   parm3 = limits[0] + 2.0 * (limits[1] - limits[0])/3.0;

	double point1[3],  point2[3],  point3[3];
	double  tangent[3], normal[3], binormal[3];
	UF_EVAL_evaluate_unit_vectors(evaluator, parm1, point1, tangent, normal, binormal);
	UF_EVAL_evaluate_unit_vectors(evaluator, parm2, point2, tangent, normal, binormal);
	UF_EVAL_evaluate_unit_vectors(evaluator, parm3, point3, tangent, normal, binormal);

	UF_EVAL_free(evaluator);
	evaluator = 0;

	double vec1[3] = {point2[0] - point1[0],point2[1] - point1[1],point2[2] - point1[2] },
	       vec2[3] = {point3[0] - point2[0],point3[1] - point2[1],point3[2] - point2[2] },
		   normal1[3] = {0,0,0};
    UF_VEC3_cross(vec1, vec2, normal1);
  

	UF_EVAL_initialize(edge2, &evaluator);
	UF_EVAL_ask_limits(evaluator, limits);
	parm1 = limits[0];
    parm2 = limits[0] + (limits[1] - limits[0])/3.0;
    parm3 = limits[0] + 2.0 * (limits[1] - limits[0])/3.0;

	double point4[3],  point5[3],  point6[3];
	UF_EVAL_evaluate_unit_vectors(evaluator, parm1, point4, tangent, normal, binormal);
	UF_EVAL_evaluate_unit_vectors(evaluator, parm2, point5, tangent, normal, binormal);
	UF_EVAL_evaluate_unit_vectors(evaluator, parm3, point6, tangent, normal, binormal);

	UF_EVAL_free(evaluator);
	evaluator = 0;

	
    double vec3[3] = {point5[0] - point4[0],point5[1] - point4[1],point5[2] - point4[2] },
	       vec4[3] = {point6[0] - point5[0],point6[1] - point5[1],point6[2] - point5[2] },
		   normal2[3] = {0,0,0};
	UF_VEC3_cross(vec3, vec4, normal2);

	//����1 ��Ƕ�
	/*double angle = 0;
	UF_VEC3_angle_between(normal1,normal2,tangent,&angle);
	angle = angle * 180/PI;
	if(fabs(180-angle) < PARALLEL_ANGLE || fabs(360-angle) < PARALLEL_ANGLE || fabs(angle) < PARALLEL_ANGLE)
		return true;
	else
		return false;*/

	//����2 ��ƽ��
	int is_parallel = false;
	UF_VEC3_is_parallel(normal1, normal2, 0.0254, &is_parallel);
	return is_parallel;
}


bool TYCOM_IsTwoEdgePerpendicular(tag_t edge1, tag_t edge2)
{
	UF_EVAL_p_t evaluator = 0;
	
	double      limits[2] = {0,0};

	UF_EVAL_initialize(edge1, &evaluator);
	UF_EVAL_ask_limits(evaluator, limits);
	double parm1 = limits[0], 
		   parm2 = limits[1];

	double point1[3],  point2[3];
	double  tangent[3], normal[3], binormal[3];
	UF_EVAL_evaluate_unit_vectors(evaluator, parm1, point1, tangent, normal, binormal);
	UF_EVAL_evaluate_unit_vectors(evaluator, parm2, point2, tangent, normal, binormal);
	UF_EVAL_free(evaluator);
	evaluator = 0;

	double vec1[3] = {point2[0] - point1[0],point2[1] - point1[1],point2[2] - point1[2] };
  

	UF_EVAL_initialize(edge2, &evaluator);
	UF_EVAL_ask_limits(evaluator, limits);
	parm1 = limits[0], 
    parm2 = limits[1];

	double point4[3],  point5[3];
	UF_EVAL_evaluate_unit_vectors(evaluator, parm1, point4, tangent, normal, binormal);
	UF_EVAL_evaluate_unit_vectors(evaluator, parm2, point5, tangent, normal, binormal);

	UF_EVAL_free(evaluator);
	evaluator = 0;

    double vec2[3] = {point5[0] - point4[0],point5[1] - point4[1],point5[2] - point4[2] };

	//����1 ��Ƕ�
	/*double angle = 0;
	UF_VEC3_angle_between(normal1,normal2,tangent,&angle);
	angle = angle * 180/PI;
	if(fabs(180-angle) < PARALLEL_ANGLE || fabs(360-angle) < PARALLEL_ANGLE || fabs(angle) < PARALLEL_ANGLE)
		return true;
	else
		return false;*/

	//����2 ��ƽ��
	//int is_parallel = false;
	//UF_VEC3_is_parallel(normal1, normal2, 0.0254, &is_parallel);
	//return is_parallel;

	int is_perpendicular = false;
	UF_VEC3_is_perpendicular(vec1, vec2, 0.0001, &is_perpendicular);
	return is_perpendicular;
}

extern void UF_map_wcs2abs    /* Map point from Absolute coordinates to */
                /* Work coordinate system coordinates     */
(
    double *point        /* IO  I:point in WCS  O:point in ACS */
)

{
    double abs_point[3];

    /*                Work-Coordinates             to Absolute (of work-part)*/
/*  UF_CSYS_map_point (UF_CSYS_ROOT_WCS_COORDS, point, UF_CSYS_WORK_COORDS, abs_point); */
    UF_CSYS_map_point (UF_CSYS_ROOT_WCS_COORDS, point, UF_CSYS_ROOT_COORDS, abs_point);
    point[0] = abs_point[0];
    point[1] = abs_point[1];
    point[2] = abs_point[2];
}


/*===========================================================================*/


extern void UF_map_abs2wcs    /* Map point from Work coordinate system  */
                /* to Absolute coordinates                */
(
    double *point        /* IO  I:point in ACS  O:point in WCS */
)

{
    double wcs_point[3];

    /*                Absolute (of work-part)  to  Work-Coordinates */
/*  UF_CSYS_map_point (UF_CSYS_WORK_COORDS, point, UF_CSYS_ROOT_WCS_COORDS, wcs_point); */
    UF_CSYS_map_point (UF_CSYS_ROOT_COORDS, point, UF_CSYS_ROOT_WCS_COORDS, wcs_point);
    point[0] = wcs_point[0];
    point[1] = wcs_point[1];
    point[2] = wcs_point[2];
}





void AddTagToVector( tag_t objTag,vtag_t &vecList )
{
    vtag_t::iterator itr = find(vecList.begin(),vecList.end(),objTag);
    if( itr == vecList.end() )
    {
        vecList.push_back(objTag);
    }
}



typedef int (* NXEXPORT_ASSY_clone_set_log_cb)(void *pCallBack, void *data);
//This function get the max distance of two input objects. And return the two result points.
int NXFUN_ASSY_clone_set_no_log()
{
	static HINSTANCE hInst = NULL;
	NXEXPORT_ASSY_clone_set_log_cb ASSYclonesetlogcb = NULL;
	if(hInst == NULL)
	{
		hInst=LoadLibraryA("libassy.dll");
		ASSYclonesetlogcb =(NXEXPORT_ASSY_clone_set_log_cb)GetProcAddress(hInst,"?ASSY_clone_set_log_cb@@YAHP6AHPEAXPEBDPEAD@Z0@Z");
	}
	else
		ASSYclonesetlogcb =(NXEXPORT_ASSY_clone_set_log_cb)GetProcAddress(hInst,"?ASSY_clone_set_log_cb@@YAHP6AHPEAXPEBDPEAD@Z0@Z");
	if(ASSYclonesetlogcb == NULL)
		return -2;


	int error = ASSYclonesetlogcb(NULL,NULL);
	return 0;
}

NXOpen::Xform * TYCOM_CreateXForm(NXOpen::Point3d origin1,  NXOpen::Vector3d xDirection1, NXOpen::Vector3d yDirection1)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
    NXOpen::Xform *xform1 = 0;
    xform1 = workPart->Xforms()->CreateXform(origin1, xDirection1, yDirection1, NXOpen::SmartObject::UpdateOptionAfterModeling, 1.0);
    return xform1;
}

NXOpen::CartesianCoordinateSystem * TYCOM_CreateCoordinateSystem(NXOpen::Xform *xform)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
    NXOpen::CartesianCoordinateSystem *cartesianCoordinateSystem1 = 0;
    cartesianCoordinateSystem1 = workPart->CoordinateSystems()->CreateCoordinateSystem(xform, NXOpen::SmartObject::UpdateOptionAfterModeling);
	return cartesianCoordinateSystem1;
}



double TYCOM_GetBodyVolume(tag_t solbody)
{
	double volume = 0.0;
	double area1 = 0.0, area2 = 0.0, area3 = 0.0;

	int  response = 2, type = 1, unit = 3, accuracy =  1, count = 0, zero = 0, i = 0;
	double  acc_val[11] = {.000001,0,0,0,0,0,0,0,0,0,0};
	double  density = 1.0, massprop[47], massprop_stat[13];

	int err = UF_MODL_ask_mass_props_3d(&solbody, 1, type, unit, density, accuracy, acc_val,
		massprop, massprop_stat);
	volume = massprop[1];
	//area1 = massprop[0]*100;
	return volume;
}

NXOpen::Xform * TYCOM_CreateXFormWithThreePoint(NXOpen::Point3d pnt0, NXOpen::Point3d pnt1, NXOpen::Point3d pnt2)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());

	NXOpen::Point *point1, *point2, *point3;
    point1 = workPart->Points()->CreatePoint(pnt0);
	point2 = workPart->Points()->CreatePoint(pnt1);
	point3 = workPart->Points()->CreatePoint(pnt2);

	
	NXOpen::Xform *xform4;
	xform4 = workPart->Xforms()->CreateXform(point1, point2, point3, NXOpen::SmartObject::UpdateOptionAfterModeling, 1.0);

	return xform4;
}

NXOpen::Xform * TYCOM_CreateXFormWithOriuginXYDirection(NXOpen::Point3d origin10, NXOpen::Vector3d xDirection9, NXOpen::Vector3d yDirection9)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());

	NXOpen::Xform *xform9;
	xform9 = workPart->Xforms()->CreateXform(origin10, xDirection9, yDirection9, NXOpen::SmartObject::UpdateOptionWithinModeling, 1.0);
	return xform9;
}

NXOpen::CartesianCoordinateSystem * TYCOM_CreateCSYCAccordingToXform(NXOpen::Xform *xform)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::CartesianCoordinateSystem *cartesianCoordinateSystem1;
    cartesianCoordinateSystem1 = workPart->CoordinateSystems()->CreateCoordinateSystem(xform, NXOpen::SmartObject::UpdateOptionAfterModeling);

	return cartesianCoordinateSystem1;
}

NXOpen::Matrix3x3 TYCOM_MatrixConvert(double matrix[9])
{
	NXOpen::Matrix3x3 matrix1;

	matrix1.Xx = matrix[0];
    matrix1.Xy = matrix[1];
    matrix1.Xz = matrix[2];
    matrix1.Yx = matrix[3];
    matrix1.Yy = matrix[4];
    matrix1.Yz = matrix[5];
    matrix1.Zx = matrix[6];
    matrix1.Zy = matrix[7];
    matrix1.Zz = matrix[8];

	return matrix1;
}

int TYCOM_GetCSYSMatrix(tag_t csys, double matrix_values[9])
{
	tag_t  matrix_id = 0;
	double csys_origin[3] = {0};
	int ret = UF_CSYS_ask_csys_info(csys, &matrix_id, csys_origin);
	ret = UF_CSYS_ask_matrix_values(matrix_id, matrix_values);
	return ret;
}

int TYCOM_GetCSYSOri(tag_t csys, double csys_origin[3])
{
	tag_t  matrix_id = 0;
	int ret = UF_CSYS_ask_csys_info(csys, &matrix_id, csys_origin);
	return ret;
}

int TYCOM_SetViewToCsys(NXOpen::CartesianCoordinateSystem * csys)
{
	if(csys == 0)
		return -1;

	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());

	double matrix_values[9] = {0};
	TYCOM_GetCSYSMatrix(csys->Tag(), matrix_values);

	NXOpen::Matrix3x3 mx1 = TYCOM_MatrixConvert(matrix_values);
	workPart->ModelingViews()->WorkView()->Orient(mx1);
	return 0;
}


int TYCOM_MoveObject_CSYS_CSYS(tag_t body, tag_t fromCsys,  tag_t toCsys)
{
	if(body == 0 || fromCsys == 0 || toCsys == 0)
		return -1;

    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
    NXOpen::Features::MoveObject *nullNXOpen_Features_MoveObject(NULL);
    
    NXOpen::Features::MoveObjectBuilder *moveObjectBuilder1;
    moveObjectBuilder1 = workPart->BaseFeatures()->CreateMoveObjectBuilder(nullNXOpen_Features_MoveObject);

	moveObjectBuilder1->SetMoveObjectResult(Features::MoveObjectBuilder::MoveObjectResultOptionsMoveOriginal);
    moveObjectBuilder1->TransformMotion()->SetOption(NXOpen::GeometricUtilities::ModlMotion::OptionsCsysToCsys);
    
	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(body);
	if(NULL == (dynamic_cast<Body*> (tagobj)))
		return 1;

    bool added1;
    added1 = moveObjectBuilder1->ObjectToMoveObject()->Add((Body *)tagobj);

    moveObjectBuilder1->SetLayerOption(NXOpen::Features::MoveObjectBuilder::LayerOptionTypeOriginal);
    
    
    
	TaggedObject * pcsys1 = NXOpen::NXObjectManager::Get(fromCsys);
	NXOpen::CartesianCoordinateSystem * ppcsys1 = dynamic_cast<NXOpen::CartesianCoordinateSystem *>(pcsys1);
	if(ppcsys1 == 0)
		return -1;
    
    moveObjectBuilder1->TransformMotion()->SetFromCsys(ppcsys1);
    

	TaggedObject * pcsys2 = NXOpen::NXObjectManager::Get(toCsys);
	NXOpen::CartesianCoordinateSystem * ppcsys2 = dynamic_cast<NXOpen::CartesianCoordinateSystem *>(pcsys2);
	if(ppcsys2 == 0)
		return -1;
    
    moveObjectBuilder1->TransformMotion()->SetToCsys(ppcsys2);
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = moveObjectBuilder1->Commit();
    
    std::vector<NXOpen::NXObject *> objects1;
    objects1 = moveObjectBuilder1->GetCommittedObjects();
    
    moveObjectBuilder1->Destroy();
	return 0;
 }

int TYCOM_askFaceArea(tag_t face, double &area)
{
	if(face == 0)
		return -1;
	int err = 0;

	int  response = 2, unit = 3, accuracy =  1, count = 0;
	double  acc_val[11] = {.01,0,0,0,0,0,0,0,0,0,0};
	double  density = 1.0, massprop[47], massprop_stat[13];

	tag_t sheet =  NULL_TAG;
	UF_MODL_extract_face(face, 0, &sheet);
	if(sheet != NULL_TAG)
	{
		err = UF_MODL_ask_mass_props_3d(&sheet, 1, 2, unit, density, accuracy, acc_val,
			massprop, massprop_stat);
		area += massprop[0]*100;
	}
	UF_OBJ_delete_object(sheet);
	return 0;
}

int TYCOM_GetFalseBodysFromTrueBody(tag_t bodyTag, vtag_t &objlist)
{
	tag_t partocc = UF_ASSEM_ask_part_occurrence(bodyTag);
	tag_t partPro = 0;
	if(partocc != 0)
		partPro = UF_ASSEM_ask_prototype_of_occ( partocc ) ;
	//UF_ASSEM_set_work_part(partPro);

	tag_t ref_set = NULL_TAG ;
	int n_members = 0;
	tag_t * members = NULL;

  	UF_OBJ_cycle_by_name_and_type(partPro,"FALSE",UF_reference_set_type, TRUE, &ref_set);
 	
    UF_ASSEM_ask_ref_set_members( ref_set , & n_members , & members ) ;

	tag_t *body_occ = 0;
	int num_occ = 0;
	for( int i = 0 ; i < n_members ; i ++ )
    {
		int type = 0, subtype = 0;
        UF_OBJ_ask_type_and_subtype( members[ i ] , & type , & subtype ) ;
        if (type == UF_solid_type && subtype == UF_solid_body_subtype &&
 		     UF_OBJ_ALIVE == UF_OBJ_ask_status( members[ i ] ) )
		{
			objlist.push_back(members[i]);
		}
	}
	UF_free( members ) ;
	return 0;
}

int TYCOM_GetFalseBodysAndWaveLink(tag_t linkbodyTag, tag_t tobodyTag, vtag_t &objlist)
{
	tag_t to_part_occ,target_pro;

	tag_t from_part_occ = UF_ASSEM_ask_part_occurrence(linkbodyTag);

	tag_t partPro = 0;
	if(from_part_occ != 0)
		partPro = UF_ASSEM_ask_prototype_of_occ( from_part_occ );

	if (UF_ASSEM_is_occurrence(tobodyTag))
	{
		to_part_occ=UF_ASSEM_ask_part_occurrence(tobodyTag);
 		target_pro=UF_ASSEM_ask_prototype_of_occ(tobodyTag);
	}
	else
	{
		target_pro=tobodyTag;
		to_part_occ=NULL_TAG;
	}

	tag_t ref_set = NULL_TAG ;
	int num_mebers = 0;
	tag_t * mebers = NULL;
	char refset_name[MAX_ENTITY_NAME_SIZE+1] ;
	double origin[3] ;
	double csys_matrix[9] ;

  	UF_OBJ_cycle_by_name_and_type(partPro,"FALSE",UF_reference_set_type, TRUE, &ref_set);
    UF_ASSEM_ask_ref_set_data(ref_set,refset_name,origin,csys_matrix,&num_mebers,&mebers);

	for (int i=0;i<num_mebers;i++)
 	{
		int type,subtype,err;
		tag_t xform=NULL_TAG;
		int num_results;
		tag_t *resultbodies;
		int   result[1];
		tag_t feat_waved = 0;
		tag_t body_waved = 0;

 		if (UF_OBJ_ask_type_and_subtype(mebers[i],&type,&subtype)==0
 			&&type==UF_solid_type&&subtype==UF_solid_body_subtype)
 		{
			//UF_CALL(UF_ASSEM_set_work_part(tem_workpart));
			
 			UF_SO_create_xform_assy_ctxt(target_pro,from_part_occ,to_part_occ,&xform);

 			UF_WAVE_create_linked_body(mebers[i],xform,target_pro,TRUE, &feat_waved);
			
			UF_MODL_ask_feat_body(feat_waved,&body_waved);
			objlist.push_back(body_waved);
			
			//UF_CALL(UF_ASSEM_set_work_part(tem_workpart));
			/*UF_MODL_check_interference(target_pro,1,&body_waved,result);
			if( result[0]==1 )
			{
				err=UF_MODL_subtract_bodies(target_pro,body_waved,&num_results,&resultbodies);
				if (err)
				{
					UF_OBJ_delete_object(body_waved);
				}
				UF_free(resultbodies);
			}
			else
			{
				UF_OBJ_delete_object(body_waved);
			}*/
 		}
	}
	UF_free(mebers);
	return 0;
}

int TYCOM_GetFalseBodys(tag_t linkbodyTag, tag_t tobodyTag)
{
	tag_t to_part_occ,target_pro;

	tag_t from_part_occ = UF_ASSEM_ask_part_occurrence(linkbodyTag);

	tag_t partPro = 0;
	if(from_part_occ != 0)
		partPro = UF_ASSEM_ask_prototype_of_occ( from_part_occ ) ;

	if (UF_ASSEM_is_occurrence(tobodyTag))
	{
		target_pro=UF_ASSEM_ask_part_occurrence(tobodyTag);
	}
	else
	{
		target_pro=tobodyTag;
		to_part_occ=NULL_TAG;
	}

	tag_t ref_set = NULL_TAG ;
	int num_mebers = 0;
	tag_t * mebers = NULL;
	char refset_name[MAX_ENTITY_NAME_SIZE+1] ;
	double origin[3] ;
	double csys_matrix[9] ;

  	UF_OBJ_cycle_by_name_and_type(partPro,"FALSE",UF_reference_set_type, TRUE, &ref_set);
    UF_ASSEM_ask_ref_set_data(ref_set,refset_name,origin,csys_matrix,&num_mebers,&mebers);

	for (int i=0;i<num_mebers;i++)
 	{
		int type,subtype,err;
		tag_t xform=NULL_TAG;
		int num_results;
		tag_t *resultbodies;
		int   result[1];
		tag_t feat_waved = 0;
		tag_t body_waved = 0;

 		if (UF_OBJ_ask_type_and_subtype(mebers[i],&type,&subtype)==0
 			&&type==UF_solid_type&&subtype==UF_solid_body_subtype)
 		{
			//UF_CALL(UF_ASSEM_set_work_part(tem_workpart));
			
 			UF_SO_create_xform_assy_ctxt(target_pro,from_part_occ,to_part_occ,&xform);

 			UF_WAVE_create_linked_body(mebers[i],xform,target_pro,TRUE, &feat_waved);
			
			UF_MODL_ask_feat_body(feat_waved,&body_waved);
			
			//UF_CALL(UF_ASSEM_set_work_part(tem_workpart));
			UF_MODL_check_interference(target_pro,1,&body_waved,result);
			if( result[0]==1 )
			{
				err=UF_MODL_subtract_bodies(target_pro,body_waved,&num_results,&resultbodies);
				if (err)
				{
					UF_OBJ_delete_object(body_waved);
				}
				UF_free(resultbodies);
			}
			else
			{
				UF_OBJ_delete_object(body_waved);
			}
 		}
	}
	UF_free(mebers);
	return 0;
}


int TYCOM_WaveLinkBody(tag_t bodyToLink, tag_t targetPartBody, tag_t &body_waved)
{
	tag_t to_part_occ,target_pro;

	tag_t from_part_occ = UF_ASSEM_ask_part_occurrence(bodyToLink);

	tag_t partPro = 0;
	if(from_part_occ != 0)
		partPro = UF_ASSEM_ask_prototype_of_occ( from_part_occ );

	if (UF_ASSEM_is_occurrence(targetPartBody))
	{
		to_part_occ=UF_ASSEM_ask_part_occurrence(targetPartBody);
 		target_pro=UF_ASSEM_ask_prototype_of_occ(targetPartBody);
	}
	else
	{
		target_pro=targetPartBody;
		to_part_occ=NULL_TAG;
	}

	tag_t xform=NULL_TAG;
	int   result[1];
	tag_t feat_waved = 0;

	if (UF_ASSEM_is_occurrence(bodyToLink))
	{
		bodyToLink=UF_ASSEM_ask_prototype_of_occ(bodyToLink);
	}

	UF_SO_create_xform_assy_ctxt(target_pro,from_part_occ,to_part_occ,&xform);
	UF_WAVE_create_linked_body(bodyToLink,xform,target_pro,TRUE, &feat_waved);
	UF_MODL_ask_feat_body(feat_waved,&body_waved);

	return 0;
}

int TYCOM_WaveLinkCurve(tag_t curveToLink, tag_t targetPartObject, tag_t &Curve_waved)
{
	tag_t to_part_occ,target_pro;

	tag_t from_part_occ = UF_ASSEM_ask_part_occurrence(curveToLink);

	tag_t partPro = 0;
	if(from_part_occ != 0)
		partPro = UF_ASSEM_ask_prototype_of_occ( from_part_occ );

	if (UF_ASSEM_is_occurrence(targetPartObject))
	{
		to_part_occ=UF_ASSEM_ask_part_occurrence(targetPartObject);
 		target_pro=UF_ASSEM_ask_prototype_of_occ(targetPartObject);
	}
	else
	{
		target_pro=targetPartObject;
		to_part_occ=NULL_TAG;
	}

	tag_t xform=NULL_TAG;
	int   result[1];
	tag_t feat_waved = 0;

	if (UF_ASSEM_is_occurrence(curveToLink))
	{
		curveToLink=UF_ASSEM_ask_prototype_of_occ(curveToLink);
	}

	UF_SO_create_xform_assy_ctxt(target_pro,from_part_occ,to_part_occ,&xform);
	UF_WAVE_create_linked_curve(curveToLink,xform,target_pro,TRUE, &feat_waved);
	UF_MODL_ask_feat_body(feat_waved,&Curve_waved);

	return 0;
}

int TYCOM_WaveLinkDatum(tag_t datumplanetolink, tag_t targetPartObject, tag_t &plane_waved)
{
	tag_t to_part_occ,target_pro;

	tag_t from_part_occ = UF_ASSEM_ask_part_occurrence(datumplanetolink);

	tag_t partPro = 0;
	if(from_part_occ != 0)
		partPro = UF_ASSEM_ask_prototype_of_occ( from_part_occ );

	if (UF_ASSEM_is_occurrence(targetPartObject))
	{
		to_part_occ=UF_ASSEM_ask_part_occurrence(targetPartObject);
 		target_pro=UF_ASSEM_ask_prototype_of_occ(targetPartObject);
	}
	else
	{
		target_pro=targetPartObject;
		to_part_occ=NULL_TAG;
	}

	tag_t xform=NULL_TAG;
	int   result[1];
	tag_t feat_waved = 0;

	if (UF_ASSEM_is_occurrence(datumplanetolink))
	{
		datumplanetolink=UF_ASSEM_ask_prototype_of_occ(datumplanetolink);
	}

	UF_SO_create_xform_assy_ctxt(target_pro,from_part_occ,to_part_occ,&xform);
	UF_WAVE_create_linked_datum(datumplanetolink,xform,target_pro, &feat_waved);
	UF_WAVE_ask_linked_feature_geom(feat_waved,&plane_waved);

	return 0;
}

tag_t TYCOM_CreateLine( double startpoint[3],double endpoint[3] )
{
	tag_t lineTag = NULL_TAG;
	UF_CURVE_line_t line_coords;
	line_coords.start_point[0] = startpoint[0];
	line_coords.start_point[1] = startpoint[1];
	line_coords.start_point[2] = startpoint[2];
	line_coords.end_point[0] = endpoint[0];
	line_coords.end_point[1] = endpoint[1];
	line_coords.end_point[2] = endpoint[2];
	UF_CURVE_create_line(&line_coords, &lineTag);
	return lineTag;
}
typedef int (* NXEXPORT_PRINT_WIN_get_printers)(char***printers);
//This function get the max distance of two input objects. And return the two result points.
int NXFUN_PRINT_WIN_get_printers(char***printers)
{
	static HINSTANCE hInst = NULL;
	NXEXPORT_PRINT_WIN_get_printers getPrinters = NULL;
	if(hInst == NULL)
	{
		hInst=LoadLibraryA("libpartdisp.dll");
		getPrinters =(NXEXPORT_PRINT_WIN_get_printers)GetProcAddress(hInst,"?PRINT_WIN_get_printers@@YAHPEAPEAPEAD@Z");
	}
	else
		getPrinters =(NXEXPORT_PRINT_WIN_get_printers)GetProcAddress(hInst,"?PRINT_WIN_get_printers@@YAHPEAPEAPEAD@Z");
	if(getPrinters == NULL)
		return -2;


	int num = getPrinters(printers);
	return num;
}

tag_t TYCOM_GetPartForOccurenceBody(tag_t solidBody)
{
	if(UF_ASSEM_is_occurrence(solidBody))
	{
		tag_t part_tag = NULL_TAG;
		//tag_t partocc = UF_ASSEM_ask_part_occurrence(solidBody);
		tag_t solidBody1 = UF_ASSEM_ask_prototype_of_occ( solidBody ) ;
		UF_OBJ_ask_owning_part(solidBody1,&part_tag);
		return part_tag;
	}

	return solidBody;
}

tag_t TYCOM_Prototype(tag_t intag)
{
	if(intag == 0)
		return 0;
	if(UF_ASSEM_is_occurrence(intag))
		return UF_ASSEM_ask_prototype_of_occ( intag ) ;
	return intag;
}

tag_t TYCOM_ask_occ_of_entity( tag_t entity )
{
	int num = 0;
	tag_t *occs = NULL;
	tag_t occ = NULL_TAG;
	num = UF_ASSEM_ask_occs_of_entity(entity,&occs);
	if( num > 0 )
	{
		occ = occs[0];
	}
	UF_free(occs);
	return occ;
}


int TYCOM_ImportParasolid(NXString fileName)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Part *displayPart(theSession->Parts()->Display());

	NXOpen::Importer *importer1;
	importer1 = workPart->ImportManager()->CreateParasolidImporter();

	importer1->SetFileName(fileName);

	NXOpen::NXObject *nXObject1;
	nXObject1 = importer1->Commit();

	importer1->Destroy();

	return 0;
}

#define PRINTDefaultSettingPath "Software\\FinePrint Software\\pdfFactory5\\FinePrinters\\pdfFactory Pro\\DocInfo\\"
int TYCOM_SetPrintPDFName( const char* fileName)
{
	int irc = 0;
	HKEY hKEY;
	string SubKey = string(PRINTDefaultSettingPath);
	CString str(fileName);
	int wlen=wcslen(str)*2;
	char *pElementText = new char[wlen];
	WideCharToMultiByte(CP_ACP,NULL,str,-1,pElementText,wlen+2,NULL,NULL);

	if(ERROR_SUCCESS == RegOpenKeyExA(HKEY_CURRENT_USER, SubKey.c_str(), 0, KEY_SET_VALUE, &hKEY))
	{
		CString title("Title");
		irc =::RegSetValueExA(hKEY,"Title",0,REG_SZ,(unsigned char*)pElementText,wlen);
	}
	else
	{
		irc = ::RegCreateKeyA(HKEY_CURRENT_USER, SubKey.c_str(), &hKEY);
		CString title("Title");
		irc =::RegSetValueExA(hKEY,"Title",0,REG_SZ,(unsigned char*)pElementText,wlen);
	}
	::RegCloseKey(hKEY);

	return irc;
}

int TYCOM_GetAllSplinesInPart( const tag_t partTag, vtag_t & splines )
{
	splines.clear();
	tag_t parttagPRo = TYCOM_Prototype(partTag);
	tag_t tN = NULL_TAG;
	tag_t tN1 = NULL_TAG;
	tag_t holeTable = NULL_TAG;

	//UF_initialize();
	UF_OBJ_cycle_objs_in_part( parttagPRo, UF_spline_type, &tN);
	while( NULL_TAG != tN )
	{
		int type = 0;
		int subType = 0;
		UF_OBJ_ask_type_and_subtype( tN, &type, &subType );
		if(  UF_spline_type == subType || UF_spline_subtype == subType )//UF_tabular_note_type
		{
			splines.push_back(tN);
		}
		UF_OBJ_cycle_objs_in_part( parttagPRo, UF_spline_type, &tN);
	}
	UF_OBJ_cycle_objs_in_part( parttagPRo, UF_line_type, &tN1);
	while( NULL_TAG != tN1 )
	{
		splines.push_back(tN1);
		UF_OBJ_cycle_objs_in_part( parttagPRo, UF_spline_type, &tN1);
	}

	return 0;
}

void CreateReferenceSet(vtag_t bodies,NXString& refsetName)
{
	int ret = 0;
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
    tag_t refset = NULL_TAG;
    NXOpen::Session::UndoMarkId markId5;
	markId5 = theSession->SetUndoMark(NXOpen::Session::MarkVisibilityVisible, "Create Reference Set");
    std::vector<NXOpen::NXObject *> components1;
    NXOpen::ReferenceSet *referenceSet1;
	/*for( int idx = 0; idx < bodies.size(); ++idx )
	{
		if( 0 == type )
		{
			NXOpen::Body *body1(dynamic_cast<NXOpen::Body *>(NXOpen::NXObjectManager::Get(bodies[idx])));
			components1.push_back(body1);
		}
		else
		{
			NXOpen::Line *line1(dynamic_cast<NXOpen::Line *>(NXOpen::NXObjectManager::Get(bodies[idx])));
			components1.push_back(line1);
		}
			
	}*/
    try
    {
        UF_OBJ_cycle_by_name_and_type(workPart->Tag(), refsetName.GetText(),UF_reference_set_type, FALSE, &refset);
        if( refset != NULL_TAG )
        {
            referenceSet1 = (ReferenceSet *)NXObjectManager::Get(refset);

			int ret_count = 0;
			tag_p_t  members = 0;
			ret = UF_ASSEM_ask_ref_set_members(referenceSet1->Tag(), &ret_count, &members);
			ret = UF_ASSEM_remove_ref_set_members(referenceSet1->Tag(),ret_count,members);
        }
        else
        {
            referenceSet1 = workPart->CreateReferenceSet();
            referenceSet1->SetName(refsetName);
        }
        for( int idx = 0; idx < bodies.size(); ++idx )
        {
            ret = UF_ASSEM_add_ref_set_members(referenceSet1->Tag(),1,&bodies[idx]);
        }
        //referenceSet1->AddObjectsToReferenceSet(components1);
        int nErrs3;
        nErrs3 = theSession->UpdateManager()->DoUpdate(markId5);
		//theSession->DeleteUndoMark(markId5, "Create Reference Set");
    }
    catch(exception ex)
    {
    }
}

int TYCOM_DraftingPreferences_SetShowLineWidth(bool show)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Part *displayPart(theSession->Parts()->Display());
	// ----------------------------------------------
	//   Menu: ��ѡ��(P)->���ӻ�(V)...
	// ----------------------------------------------
	workPart->Preferences()->LineVisualization()->SetShowWidths(show);
	return 0;
}

bool TYCOM_DraftingPreferences_GetShowLineWidth()
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Part *displayPart(theSession->Parts()->Display());
	// ----------------------------------------------
	//   Menu: ��ѡ��(P)->���ӻ�(V)...
	// ----------------------------------------------
	return workPart->Preferences()->LineVisualization()->ShowWidths();
}

int TYCOM_OffsetFace(tag_t faceID, double dis)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());

	NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);

	NXOpen::Features::OffsetFaceBuilder *offsetFaceBuilder1;
	offsetFaceBuilder1 = workPart->Features()->CreateOffsetFaceBuilder(nullNXOpen_Features_Feature);

	char cdis[32] = "";
	sprintf(cdis, "%.3f", dis);
	offsetFaceBuilder1->Distance()->SetRightHandSide(cdis);

	std::vector<NXOpen::Face *> faces1(1);

	TaggedObject * pobj = NXOpen::NXObjectManager::Get(faceID);
	NXOpen::Face *face1 =  dynamic_cast<NXOpen::Face*> (pobj);


	faces1[0] = face1;
	NXOpen::FaceDumbRule *faceDumbRule1;
	faceDumbRule1 = workPart->ScRuleFactory()->CreateRuleFaceDumb(faces1);

	std::vector<NXOpen::SelectionIntentRule *> rules1(1);
	rules1[0] = faceDumbRule1;
	offsetFaceBuilder1->FaceCollector()->ReplaceRules(rules1, false);

	NXOpen::NXObject *nXObject1;
	nXObject1 = offsetFaceBuilder1->Commit();

	NXOpen::Expression *expression1(offsetFaceBuilder1->Distance());
	offsetFaceBuilder1->Destroy();
	return 0;
}

int Roy_ask_obj_string_attr( tag_t obj , const char *title , char *string )
{
	UF_ATTR_value_t  value ;
	strcpy( string , "" ) ;
	if( obj == NULL_TAG ) 
		return 1 ;
	if( UF_ASSEM_is_occurrence( obj ))
	{
		obj = UF_ASSEM_ask_prototype_of_occ ( obj ) ;
	}

	UF_ATTR_read_value( obj, (char*)title, UF_ATTR_any, &value );
	if( value.type == UF_ATTR_string ) 
	{
		strcpy( string , value.value.string ) ;
		UF_free(value.value.string) ;
	}
	else 
	{
		return -1 ;
	}
	return 0 ;
} 

int TYCOM_SetText(tag_t text, NXString str, double height)
{
	/*if (strlen(str.GetLocaleText()) == 0)
	{
		UF_OBJ_delete_object(text);
		return -1;
	}

	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());

	TaggedObject *object = NXOpen::NXObjectManager::Get(text);

	NXOpen::Features::Text *text1 = dynamic_cast<NXOpen::Features::Text *>(object);
	if(text1 == 0)
		return -1;
	NXOpen::Features::TextBuilder *textBuilder1;
	textBuilder1 = workPart->Features()->CreateTextBuilder(text1);
	textBuilder1->SetTextString(str);

	if(height > 0)
	{
		char chei[32] = "";
		sprintf(chei, "%.1f", height);
		textBuilder1->PlanarFrame()->Height()->SetRightHandSide(chei);
	}

	NXOpen::NXObject *nXObject1;
	nXObject1 = textBuilder1->Commit();
	textBuilder1->Destroy();

	//workPart->Features()->SetEditWithRollbackFeature(text1);
	//theSession->UpdateManager()->SetInterpartDelay(true);
	//text1->MakeCurrentFeature();
	//if ( !workPart->Preferences()->Modeling()->GetHistoryMode() )
	//{
	//throw NXException::Create("Create or edit of a Feature was recorded in History Mode but playback is in History-Free Mode.");
	// }*/
	return 0;
}

int TYCOM_Plot_Single
(
 tag_t sheet,
 NXOpen::PrintBuilder::PaperSize ps,//NXOpen::PrintBuilder::PaperSizeA4
 NXOpen::PrintBuilder::OrientationOption orientation,//NXOpen::PrintBuilder::OrientationOptionLandscape
 char * printer//"Canon MG7700 series Printer WS"
 )
{
	//UG��ӡ�����Ĵ�ϸ���������õ�
	//UG Ĭ����Plot Customer Width 1--9 9����ȱ�����������
	//�ֱ��Ӧ����0.13 0.18 0.25.2.00�Ÿ����
	//�⼸����ȿ���ͨ��Plot Customer Width������ͬ�������ȵı�����ϵ�õ� ���е������Ȳ���
	//���������õ�������0.35 ʵ�� 0.7 ��ô�ֱ��ӦPlot Customer Width  4 �� Plot Customer Width 6
	//Ϊ���������� ����ֻҪ��Plot Customer Width 4���ó�1 Plot Customer Width ���ó� 5���߸���
	//�ٴ�ӡЧ���ͳ����ˡ���Ϊ����0.35����0.35  0.7�Ѿ����0.7*5 = 3.5�� ��ʮ���Ŀ��
	//----�������Ҫ�� ���������һ��˵�ı����ǲ������õ�
	//�������ugͼ����ͼ�ռ���ʾ����������ǲ�����Ҫ����ʵ����Ҫ��ʾ����������ѡ��--�����ӻ�--��ֱ��
	//�������ʾ�߿�ʵ�֡�
	//
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());

	NXOpen::PrintBuilder *printBuilder1;
	printBuilder1 = workPart->PlotManager()->CreatePrintBuilder();

	printBuilder1->SetCopies(1);
	printBuilder1->SetThinWidth(1.0);
	printBuilder1->SetNormalWidth(5.0);
	printBuilder1->SetThickWidth(6.0);

	printBuilder1->SetOutput(NXOpen::PrintBuilder::OutputOptionWireframeBlackWhite);
	printBuilder1->SetRasterImages(true);

	std::vector<NXOpen::NXObject *> sheets1;
	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(sheet);
	Drawings::DrawingSheet *drawingSheet = dynamic_cast<NXOpen::Drawings::DrawingSheet *>(tagobj);
	sheets1.push_back(drawingSheet);

	printBuilder1->SourceBuilder()->SetSheets(sheets1);

	printBuilder1->SetPaper(ps);
	printBuilder1->SetOrientation(orientation);
	printBuilder1->SetPrinterText(printer);
	//NXOpen::PrintBuilder::PaperSize paper1;
	//paper1 = printBuilder1->Paper();

	NXOpen::NXObject *nXObject1;
	nXObject1 = printBuilder1->Commit();
	printBuilder1->Destroy();

	return 0;
}

void TYCOM_ExportSheetToAcadDwg( const char* inputfile, const char* outputfile, NXString& drawingName )
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

	//nXTo2dCreator1->SetDrawingName("Sheet 1");
	nXTo2dCreator1->SetDrawingName(drawingName);

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

/*
int TYCOM_ExtrudeReplaceCurve(tag_t extrudeFeature, tag_t newCurve)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    NXOpen::TaggedObject *object = NXOpen::NXObjectManager::Get(extrudeFeature);
    Features::Feature *extrude1 = dynamic_cast<Features::Feature *>(object);
    NXOpen::Features::ExtrudeBuilder *extrudeBuilder1;
    extrudeBuilder1 = workPart->Features()->CreateExtrudeBuilder(extrude1);
    NXOpen::Section *section1;
    section1 = extrudeBuilder1->Section();
    extrudeBuilder1->AllowSelfIntersectingSection(true);
  
    NXOpen::Unit *unit1;
    unit1 = extrudeBuilder1->Draft()->FrontDraftAngle()->Units();
    section1->SetDistanceTolerance(0.01);
    section1->SetChainingTolerance(0.0095);
    NXOpen::NXObject *nullNXOpen_NXObject(NULL);
	section1->Clear();
    std::vector<NXOpen::IBaseCurve *> curves1(1);
    
	NXOpen::TaggedObject *object1 = NXOpen::NXObjectManager::Get(newCurve);
	Curve *pCurve= dynamic_cast<Curve *>(object1);

    curves1[0] = pCurve;
    NXOpen::CurveDumbRule *curveDumbRule1;
    curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);
    section1->AllowSelfIntersection(true);
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = curveDumbRule1;
    NXOpen::Point3d helpPoint1(102.024472401989, 109.145404160179, 0.0);
    section1->AddToSection(rules1, pCurve, nullNXOpen_NXObject, nullNXOpen_NXObject, helpPoint1, NXOpen::Section::ModeCreate, false);
    
    NXOpen::Features::Feature *feature1;
    feature1 = extrudeBuilder1->CommitFeature();
    extrudeBuilder1->Destroy();
    return 0;

}

//�滻workpart�ڵ�����

int TYCOM_ExtrudeReplaceCurvesWorkPart(tag_t extrudeFeature, vtag_t newCurves)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    NXOpen::TaggedObject *object = NXOpen::NXObjectManager::Get(extrudeFeature);
    Features::Feature *extrude1 = dynamic_cast<Features::Feature *>(object);
    NXOpen::Features::ExtrudeBuilder *extrudeBuilder1;
    extrudeBuilder1 = workPart->Features()->CreateExtrudeBuilder(extrude1);
    NXOpen::Section *section1;
    section1 = extrudeBuilder1->Section();
    extrudeBuilder1->AllowSelfIntersectingSection(true);
  
    NXOpen::Unit *unit1;
    unit1 = extrudeBuilder1->Draft()->FrontDraftAngle()->Units();
    NXOpen::NXObject *nullNXOpen_NXObject(NULL);
	section1->Clear();


    std::vector<NXOpen::IBaseCurve *> curves1;
	Curve *firstcurve=0;
	for(int i = 0; i < newCurves.size(); i++)
	{
		NXOpen::TaggedObject *object1 = NXOpen::NXObjectManager::Get(newCurves[i]);
	    Curve *pCurve= dynamic_cast<Curve *>(object1);
		curves1.push_back(pCurve);
		if(i == 0)
			firstcurve = pCurve;
	}
	
    NXOpen::CurveDumbRule *curveDumbRule1;
    curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);
    section1->AllowSelfIntersection(true);
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = curveDumbRule1;
    NXOpen::Point3d helpPoint1(102.024472401989, 109.145404160179, 0.0);
    section1->AddToSection(rules1, firstcurve, nullNXOpen_NXObject, nullNXOpen_NXObject, helpPoint1, NXOpen::Section::ModeCreate, false);
    
    NXOpen::Features::Feature *feature1;
    feature1 = extrudeBuilder1->CommitFeature();
    extrudeBuilder1->Destroy();
    return 0;
}



//�滻װ��������part������

int TYCOM_ExtrudeReplaceCurvesOtherPart(tag_t extrudeFeature, vtag_t newCurves)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    NXOpen::TaggedObject *object = NXOpen::NXObjectManager::Get(extrudeFeature);
    Features::Feature *extrude1 = dynamic_cast<Features::Feature *>(object);
    NXOpen::Features::ExtrudeBuilder *extrudeBuilder1;
    extrudeBuilder1 = workPart->Features()->CreateExtrudeBuilder(extrude1);
    NXOpen::Section *section1;
    section1 = extrudeBuilder1->Section();
    extrudeBuilder1->AllowSelfIntersectingSection(true);
  
    NXOpen::Unit *unit1;
    unit1 = extrudeBuilder1->Draft()->FrontDraftAngle()->Units();
    NXOpen::NXObject *nullNXOpen_NXObject(NULL);
	section1->Clear();



	//����װ��curve
	NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
	NXOpen::Features::CompositeCurveBuilder *compositeCurveBuilder1;
    compositeCurveBuilder1 = workPart->Features()->CreateCompositeCurveBuilder(nullNXOpen_Features_Feature);
    
    NXOpen::Section *section2;
    section2 = compositeCurveBuilder1->Section();
    compositeCurveBuilder1->SetAssociative(true);
    compositeCurveBuilder1->SetParentPart(NXOpen::Features::CompositeCurveBuilder::PartTypeOtherPart);
    compositeCurveBuilder1->SetAllowSelfIntersection(true);
    section2->SetAllowedEntityTypes(NXOpen::Section::AllowTypesOnlyCurves);
    section2->SetAllowRefCrvs(false);
    compositeCurveBuilder1->SetFixAtCurrentTimestamp(true);
    
	std::vector<NXOpen::IBaseCurve *> curves1;
	Curve *firstcurve=0;
	for(int i = 0; i < newCurves.size(); i++)
	{
		NXOpen::TaggedObject *object1 = NXOpen::NXObjectManager::Get(newCurves[i]);
	    Curve *pCurve= dynamic_cast<Curve *>(object1);
		curves1.push_back(pCurve);
		if(i == 0)
			firstcurve = pCurve;
	}
    NXOpen::CurveDumbRule *curveDumbRule1;
    curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = curveDumbRule1;
    NXOpen::Point3d helpPoint1(0, 0, 0.0);
    section2->AddToSection(rules1, firstcurve, nullNXOpen_NXObject, nullNXOpen_NXObject, helpPoint1, NXOpen::Section::ModeEdit, false);
    
    NXOpen::Features::Feature *feature1;
    feature1 = compositeCurveBuilder1->CommitCreateOnTheFly();



	std::vector<NXOpen::Features::Feature *> features1(1);
    NXOpen::Features::CompositeCurve *compositeCurve2(dynamic_cast<NXOpen::Features::CompositeCurve *>(feature1));
    features1[0] = compositeCurve2;
    NXOpen::CurveFeatureRule *curveFeatureRule1;
    curveFeatureRule1 = workPart->ScRuleFactory()->CreateRuleCurveFeature(features1);
    
    section1->AllowSelfIntersection(true);
    
    std::vector<NXOpen::SelectionIntentRule *> rules2(1);
    rules2[0] = curveFeatureRule1;
    NXOpen::Point3d helpPoint2(0, 0, 0.0);
    section1->AddToSection(rules2, firstcurve, nullNXOpen_NXObject, nullNXOpen_NXObject, helpPoint2, NXOpen::Section::ModeCreate, false);
   
	
    NXOpen::Features::Feature *feature2;
    feature2 = extrudeBuilder1->CommitFeature();
    extrudeBuilder1->Destroy();
    return 0;
}
int TYCOM_ExtrudeReplaceCurves(tag_t extrudeFeature, vtag_t newCurves)
{
	if(extrudeFeature == 0 || newCurves.size() == 0)
		return -1;

	tag_t workPart = UF_ASSEM_ask_work_part();//������extrudeFeature
	tag_t partTag2 = UF_ASSEM_ask_part_occurrence(newCurves[0]);
	if(partTag2 != 0)
		partTag2 = UF_ASSEM_ask_prototype_of_occ ( partTag2 ) ;
	else
		partTag2 = UF_PART_ask_display_part();

	int errorCode = 0;
	try
	{
		if(workPart == partTag2)
			errorCode = TYCOM_ExtrudeReplaceCurvesWorkPart(extrudeFeature, newCurves);
		else
			errorCode = TYCOM_ExtrudeReplaceCurvesOtherPart(extrudeFeature, newCurves);
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		const char * mesg = ex.what();
		errorCode = 1;
		
		//errorCode = 1;
		//CutSolid2018::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	return errorCode;
}
int TYCOM_ProjectCurveToPlane(tag_t curve, tag_t plane, tag_t &feat)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
    
    NXOpen::Features::ProjectCurveBuilder *projectCurveBuilder1;
    projectCurveBuilder1 = workPart->Features()->CreateProjectCurveBuilder(nullNXOpen_Features_Feature);
    

	double plane_point[3]= {0.0, 0.0, 0.0}, plane_normal[3]= {0.0, 0.0, 0.0};
	int ret = UF_MODL_ask_plane(plane, plane_point, plane_normal);
	Point3d origin1(plane_point[0], plane_point[1], plane_point[2]);
	Vector3d normal1(plane_normal[0], plane_normal[1], plane_normal[2]);
	Plane *plane1;
	plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);
    
    projectCurveBuilder1->CurveFitData()->SetTolerance(0.01);
    
    projectCurveBuilder1->CurveFitData()->SetAngleTolerance(0.5);
    
    projectCurveBuilder1->SectionToProject()->SetDistanceTolerance(0.01);
    projectCurveBuilder1->SectionToProject()->SetChainingTolerance(0.0095);
    
    projectCurveBuilder1->SectionToProject()->SetAngleTolerance(0.5);
    
    projectCurveBuilder1->SectionToProject()->SetAllowedEntityTypes(NXOpen::Section::AllowTypesCurvesAndPoints);

    
    std::vector<NXOpen::IBaseCurve *> curves1(1);
	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(curve);
	Line* line1 = dynamic_cast<Line*> (tagobj);
    curves1[0] = line1;
    NXOpen::CurveDumbRule *curveDumbRule1;
    curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);
    
    projectCurveBuilder1->SectionToProject()->AllowSelfIntersection(true);
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = curveDumbRule1;
    NXOpen::NXObject *nullNXOpen_NXObject(NULL);
    NXOpen::Point3d helpPoint1(0, 0, 0);
    projectCurveBuilder1->SectionToProject()->AddToSection(rules1, line1, nullNXOpen_NXObject, nullNXOpen_NXObject, helpPoint1, NXOpen::Section::ModeCreate, false);
    
   
    
    projectCurveBuilder1->SetPlaneToProjectTo(plane1);
    
    NXOpen::NXObject *nXObject1 = 0;
    nXObject1 = projectCurveBuilder1->Commit();
	if(nXObject1)
	feat = nXObject1->Tag();
    
    projectCurveBuilder1->Destroy();
    return 0;
}

int TYCOM_Plot
(
    vtag_t &sheets,
	NXOpen::PrintBuilder::PaperSize ps,//NXOpen::PrintBuilder::PaperSizeA4
	NXOpen::PrintBuilder::OrientationOption orientation,//NXOpen::PrintBuilder::OrientationOptionLandscape
	char * printer//"Canon MG7700 series Printer WS"
)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
    NXOpen::PrintBuilder *printBuilder1;
    printBuilder1 = workPart->PlotManager()->CreatePrintBuilder();
    
    printBuilder1->SetCopies(1);
    printBuilder1->SetThinWidth(1.0);
    printBuilder1->SetNormalWidth(2.0);
    printBuilder1->SetThickWidth(3.0);
    printBuilder1->SetWidth2ScaleFactor(1.0);
    printBuilder1->SetWidth3ScaleFactor(1.0);
    printBuilder1->SetWidth4ScaleFactor(1.0);
    printBuilder1->SetWidth5ScaleFactor(2.0);
    printBuilder1->SetWidth6ScaleFactor(2.0);
    printBuilder1->SetWidth7ScaleFactor(3.0);
    printBuilder1->SetWidth8ScaleFactor(3.0);
    printBuilder1->SetWidth9ScaleFactor(3.0);
    printBuilder1->SetOutput(NXOpen::PrintBuilder::OutputOptionWireframeBlackWhite);
    printBuilder1->SetRasterImages(true);
    
	std::vector<NXOpen::NXObject *> sheets1;
	for(int i = 0; i < sheets.size(); i++)
	{
		TaggedObject * tagobj = NXOpen::NXObjectManager::Get(sheets[i]);
		Drawings::DrawingSheet *drawingSheet = dynamic_cast<NXOpen::Drawings::DrawingSheet *>(tagobj);
		sheets1.push_back(drawingSheet);
	}
    printBuilder1->SourceBuilder()->SetSheets(sheets1);

	printBuilder1->SetPaper(ps);
	printBuilder1->SetOrientation(orientation);
    printBuilder1->SetPrinterText(printer);
    //NXOpen::PrintBuilder::PaperSize paper1;
    //paper1 = printBuilder1->Paper();
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = printBuilder1->Commit();
    printBuilder1->Destroy();
   
	return 0;
}


int TYCOM_AddObjectToReferenceSet(tag_t part, vtag_t objs, NXString refsetname)
{
	if(part == 0)
		return -1;
	if(objs.size()  == 0)
		return -1;

	part = TYCOM_Prototype(part);

	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(part);
	NXOpen::Part *ppart =  dynamic_cast<NXOpen::Part*> (tagobj);
	if(ppart == NULL)
		return -2;

	std::vector<NXOpen::NXObject *> components;
	for(int i = 0; i < objs.size(); i++)
	{
		TaggedObject * pobj = NXOpen::NXObjectManager::Get(objs[i]);
    	NXOpen::NXObject *nxobj =  dynamic_cast<NXOpen::NXObject*> (pobj);
		if(nxobj != NULL)
			components.push_back(nxobj);
	}

	std::vector<NXOpen::ReferenceSet *> refsets = ppart->GetAllReferenceSets();
	if(refsets.size() == 1)
		refsets[0]->AddObjectsToReferenceSet(components);
	else
	{
		//for(int i = 0; i < refsets.size(); i++)
		//{
		//	NXString name1 = refsets[i]->Name();
		//	const char * name2 = refsetname.GetLocaleText();
		//	if(strcmp(name1, name2) ==0 )
		//	{
		//		refsets[i]->AddObjectsToReferenceSet(components);
		//			return 0;
		//	}
		//}
	}
	

	return 1;


	//NXOpen::Session *theSession = NXOpen::Session::GetSession();
    //NXOpen::Part *workPart(theSession->Parts()->Work());
}
int TYCOM_CreateDatumPlane(NXOpen::Point3d origin, NXOpen::Vector3d & normal, tag_t &plane)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
   
    NXOpen::Features::DatumPlaneBuilder *datumPlaneBuilder1;
    datumPlaneBuilder1 = workPart->Features()->CreateDatumPlaneBuilder(0);
    
    NXOpen::Plane *plane1;
    plane1 = datumPlaneBuilder1->GetPlane();
    
    plane1->SetOrigin(origin);
	plane1->SetNormal(normal);
    
    plane1->Evaluate();
    plane1->SetFlip(false);
    plane1->SetReverseSide(false);

    datumPlaneBuilder1->SetResizeDuringUpdate(true);
    
    NXOpen::Features::Feature *feature1;
    feature1 = datumPlaneBuilder1->CommitFeature();
    
    NXOpen::Features::DatumPlaneFeature *datumPlaneFeature1(dynamic_cast<NXOpen::Features::DatumPlaneFeature *>(feature1));
    NXOpen::DatumPlane *datumPlane1;
    datumPlane1 = datumPlaneFeature1->DatumPlane();
    datumPlaneBuilder1->Destroy();
	plane = datumPlane1->Tag();
	return 0;
}
int TYCOM_SplitBody(tag_t &solid, Plane * plane1, vtag_t &splitBodies)
{
	int errorCode = 0;
	Session *theSession = Session::GetSession();
	Part * workPart = theSession->Parts()->Work();

	Features::SplitBody *nullFeatures_Feature(NULL);
	Features::SplitBodyBuilder *splitBodyBuilder = 0;
    splitBodyBuilder = workPart->Features()->CreateSplitBodyBuilder(nullFeatures_Feature);

	NXOpen::ScCollector * collector = workPart->ScCollectors()->CreateCollector();

	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(solid);
	if(NULL == (dynamic_cast<Body*> (tagobj)))
		return 1;

	std::vector<NXOpen::Body *>  bodies(1);
	bodies[0] = (Body *)tagobj;
	BodyDumbRule * bodyRule = workPart->ScRuleFactory()->CreateRuleBodyDumb(bodies);
	
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = bodyRule;
    collector->ReplaceRules(rules1, false);

	splitBodyBuilder->SetTargetBodyCollector(collector);

	//plane
	splitBodyBuilder->BooleanTool()->FacePlaneTool()->SetToolPlane(plane1);
	splitBodyBuilder->BooleanTool()->SetToolOption(NXOpen::GeometricUtilities::BooleanToolBuilder::BooleanToolTypeNewPlane);

	NXOpen::NXObject *nXObject2;
	try
	{
		vtag_t vfeats;
		uf_list_p_t solidfeatures = NULL;
	    errorCode = UF_MODL_ask_body_feats(solid, &solidfeatures);
	    TYCOM_AskListItemsAndDelete(solidfeatures, vfeats);
		char *featName = 0;

        nXObject2 = splitBodyBuilder->Commit();
		tag_t featureBody = 0;
		UF_MODL_ask_feat_body(nXObject2->Tag(), &featureBody);

		UF_MODL_ask_feat_name(nXObject2->Tag(), &featName);
		if(featureBody != solid)
		{
			double dis1 = 0, dis2 = 0;
			TYCOM_AskMaxDist(featureBody, plane1->Tag(), dis1);
			TYCOM_AskMaxDist(solid, plane1->Tag(), dis2);

			if(dis1 > dis2)
			{
				splitBodies.push_back(solid);
			    solid = featureBody;
			}
			else
			{
				splitBodies.push_back(featureBody);
			}
		}
		else
		{
			Features::SplitBody * pfrec = dynamic_cast<Features::SplitBody*> (nXObject2);

			std::vector<NXOpen::Body *> bodies = pfrec->GetBodies();
			if(bodies.size() == 2)
			{
				double dis1 = 0, dis2 = 0;
			    TYCOM_AskMaxDist(bodies[0]->Tag(), plane1->Tag(), dis1);
			    TYCOM_AskMaxDist(bodies[1]->Tag(), plane1->Tag(), dis2);
				if(dis1 > dis2)
				    splitBodies.push_back(bodies[1]->Tag());
				else
					splitBodies.push_back(bodies[0]->Tag());
			}
		}	
	}
	catch(exception& ex)
	{
		//---- Enter your exception handling code here -----
		const char * mesg = ex.what();
		errorCode = 1;
		//errorCode = 1;
		//CutSolid2018::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	splitBodyBuilder->Destroy();

	return errorCode;
}
int TYCOM_SolidIntersect(tag_t first, tag_t second, tag_t &resolid)
{
	Session *theSession = Session::GetSession();
	Part * workPart = theSession->Parts()->Work();

	TaggedObject * firstSolid = NXOpen::NXObjectManager::Get(first);
	if(NULL == (dynamic_cast<Body*> (firstSolid)))
		return 1;

	TaggedObject * secondSolid = NXOpen::NXObjectManager::Get(second);
	if(NULL == (dynamic_cast<Body*> (secondSolid)))
		return 1;

	NXOpen::Features::BooleanFeature *nullNXOpen_Features_BooleanFeature(NULL);
	NXOpen::Features::BooleanBuilder *booleanBuilder1;
    booleanBuilder1 = workPart->Features()->CreateBooleanBuilderUsingCollector(nullNXOpen_Features_BooleanFeature);
    
	booleanBuilder1->SetTolerance(0.01);
    booleanBuilder1->SetCopyTargets(true);
    booleanBuilder1->SetCopyTools(true);
    booleanBuilder1->SetOperation(NXOpen::Features::Feature::BooleanTypeIntersect);
    booleanBuilder1->Targets()->Add((Body*)firstSolid);


	NXOpen::ScCollector *scCollector2;
    scCollector2 = workPart->ScCollectors()->CreateCollector();
    
    std::vector<NXOpen::Body *> bodies1(1);
    bodies1[0] = (Body*) (secondSolid);
    NXOpen::BodyDumbRule *bodyDumbRule1;
    bodyDumbRule1 = workPart->ScRuleFactory()->CreateRuleBodyDumb(bodies1);
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = bodyDumbRule1;
    scCollector2->ReplaceRules(rules1, false);

	booleanBuilder1->SetToolBodyCollector(scCollector2);


	int errorCode = 0;
	try
	{
	    NXOpen::NXObject *nXObject1;
        nXObject1 = booleanBuilder1->Commit();
	    UF_MODL_ask_feat_body(nXObject1->Tag(), &resolid);
	}
	catch(exception& ex)
	{
		errorCode = 1;
	}

	booleanBuilder1->Destroy(); 

	return errorCode;
}

int TYCOM_SolidSubtruct(tag_t first, tag_t second)
{
	Session *theSession = Session::GetSession();
	Part * workPart = theSession->Parts()->Work();

	TaggedObject * firstSolid = NXOpen::NXObjectManager::Get(first);
	if(NULL == (dynamic_cast<Body*> (firstSolid)))
		return 1;

	TaggedObject * secondSolid = NXOpen::NXObjectManager::Get(second);
	if(NULL == (dynamic_cast<Body*> (secondSolid)))
		return 1;

	NXOpen::Features::BooleanFeature *nullNXOpen_Features_BooleanFeature(NULL);
	NXOpen::Features::BooleanBuilder *booleanBuilder1;
    booleanBuilder1 = workPart->Features()->CreateBooleanBuilderUsingCollector(nullNXOpen_Features_BooleanFeature);
    
    NXOpen::ScCollector *scCollector1;
    scCollector1 = booleanBuilder1->ToolBodyCollector();
    
    NXOpen::GeometricUtilities::BooleanRegionSelect *booleanRegionSelect1;
    booleanRegionSelect1 = booleanBuilder1->BooleanRegionSelect();
    
    booleanBuilder1->SetTolerance(0.01);
    
    booleanBuilder1->SetOperation(NXOpen::Features::Feature::BooleanTypeSubtract);
    
    booleanBuilder1->SetCopyTargets(false);
    booleanBuilder1->Targets()->Add((Body *)firstSolid);


	std::vector<NXOpen::Body *> bodies1(1);
    bodies1[0] = (Body *)secondSolid;
    NXOpen::BodyDumbRule *bodyDumbRule1;
    bodyDumbRule1 = workPart->ScRuleFactory()->CreateRuleBodyDumb(bodies1);
    
	NXOpen::ScCollector *scCollector2;
    scCollector2 = workPart->ScCollectors()->CreateCollector();
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = bodyDumbRule1;
    scCollector2->ReplaceRules(rules1, false);
    
    booleanBuilder1->SetToolBodyCollector(scCollector2);

	int errorCode = 0;
	try
	{
	    NXOpen::NXObject *nXObject1;
        nXObject1 = booleanBuilder1->Commit();
	}
	catch(exception& ex)
	{
		errorCode = 1;
	}
	booleanBuilder1->Destroy();
	return errorCode;
}

int TYCOM_InstanceGeometry(vtag_t &bodies, tag_t plane, bool associate)
{
	if(bodies.size() == 0)
		return -1;

	if(plane == 0)
		return -2;

	//�õ�������Ϣ
	int errorCode = 0;
	Session *theSession = Session::GetSession();
	Part * workPart = theSession->Parts()->Work();

	Features::GeomcopyBuilder *geomcopyBuilder1;
	Features::Feature *nullFeatures_Feature(NULL);
	geomcopyBuilder1 = workPart->Features()->CreateGeomcopyBuilder(nullFeatures_Feature);



	//plane����
	double plane_point[3]= {0.0, 0.0, 0.0}, plane_normal[3]= {0.0, 0.0, 0.0};
	int ret = UF_MODL_ask_plane(plane, plane_point, plane_normal);
	Point3d origin1(plane_point[0], plane_point[1], plane_point[2]);
	Vector3d normal1(plane_normal[0], plane_normal[1], plane_normal[2]);
	Plane *plane1;
	plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);
	
	//plane1->SetMethod(PlaneTypes::MethodTypeFixedY);

	geomcopyBuilder1->SetMirrorPlane(plane1);
	geomcopyBuilder1->SetType(Features::GeomcopyBuilder::TransformTypesMirror);
	geomcopyBuilder1->SetAssociative(associate);

	geomcopyBuilder1->SetCsysMirrorOption(Features::GeomcopyBuilder::CsysMirrorOptionsMirrorYAndZ);
	geomcopyBuilder1->SetCopyThreads(false);
	
	

	//std::vector<NXObject *> geom1(0);
	//plane1->SetGeometry(geom1);
	//Body *body1(dynamic_cast<Body *>(workPart->Bodies()->FindObject("BLOCK(1)")));

	for(int i = 0; i < bodies.size(); i++)
	{
	    TaggedObject * tagobj = NXOpen::NXObjectManager::Get(bodies[i]);
		bool added1;
	    added1 = geomcopyBuilder1->GeometryToInstance()->Add(tagobj);
	}


	vtag_t bodies1,bodies2;
	TYCOM_GetCurrentPartSolidBodies2(bodies1);
	Features::Feature *feature1;
	feature1 = geomcopyBuilder1->CommitFeature();
	TYCOM_GetCurrentPartSolidBodies2(bodies2);
	//std::vector<NXOpen::NXObject *> objs = feature1->GetEntities();
	//tag_t body = NULL_TAG;
	//tag_t feat = feature1->Tag();
	//ret = UF_MODL_ask_feat_body(feat, &body);

	//char msg[133];
	//UF_get_fail_message(ret,msg);
	//NXOpen::Features::IContainerFeature * cf = feature1->ContainerFeature();

	geomcopyBuilder1->Destroy();

	return 0;
}
int TYCOM_InstanceGeometry2(tag_t body, tag_t plane, bool associate, tag_t &outbody)
{
	if(body == 0)
		return -1;

	if(plane == 0)
		return -2;

	//�õ�������Ϣ
	int errorCode = 0;
	Session *theSession = Session::GetSession();
	Part * workPart = theSession->Parts()->Work();

	Features::GeomcopyBuilder *geomcopyBuilder1;
	Features::Feature *nullFeatures_Feature(NULL);
	geomcopyBuilder1 = workPart->Features()->CreateGeomcopyBuilder(nullFeatures_Feature);



	//plane����
	Plane *plane1;
	double plane_point[3]= {0.0, 0.0, 0.0}, plane_normal[3]= {0.0, 0.0, 0.0};
	TaggedObject * tagobj0 = NXOpen::NXObjectManager::Get(plane);
	NXOpen::DatumPlane *datumPlane1 = dynamic_cast<NXOpen::DatumPlane *>(tagobj0);
	if(datumPlane1 != 0)
	{
		plane1 = workPart->Planes()->CreatePlane(datumPlane1->Origin(), datumPlane1->Normal(), SmartObject::UpdateOptionWithinModeling);
	}
	else
	{
		int ret = UF_MODL_ask_plane(plane, plane_point, plane_normal);
		Point3d origin1(plane_point[0], plane_point[1], plane_point[2]);
		Vector3d normal1(plane_normal[0], plane_normal[1], plane_normal[2]);
		plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);
	}

	//plane1->SetMethod(PlaneTypes::MethodTypeFixedY);

	//TaggedObject * tagobjPlane = NXOpen::NXObjectManager::Get(plane);
	//Plane *plane1 = dynamic_cast<Plane *>(tagobjPlane);
	//if(plane1 == 0)
		//return -1;

	geomcopyBuilder1->SetMirrorPlane(plane1);
	geomcopyBuilder1->SetType(Features::GeomcopyBuilder::TransformTypesMirror);
	geomcopyBuilder1->SetAssociative(associate);

	geomcopyBuilder1->SetCsysMirrorOption(Features::GeomcopyBuilder::CsysMirrorOptionsMirrorYAndZ);
	geomcopyBuilder1->SetCopyThreads(false);
	

	//std::vector<NXObject *> geom1(0);
	//plane1->SetGeometry(geom1);
	//Body *body1(dynamic_cast<Body *>(workPart->Bodies()->FindObject("BLOCK(1)")));

	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(body);
	bool added1;
	added1 = geomcopyBuilder1->GeometryToInstance()->Add(tagobj);


	vtag_t bodies1,bodies2;
	TYCOM_GetCurrentPartSolidBodies2(bodies1);
	Features::Feature *feature1;
	feature1 = geomcopyBuilder1->CommitFeature();
	TYCOM_GetCurrentPartSolidBodies2(bodies2);

	for (int i = 0; i < bodies2.size(); i++)
	{
		if(vFind(bodies1, bodies2[i]) == -1)
		{
			outbody = bodies2[i];
		}
	}

	geomcopyBuilder1->Destroy();

	UF_OBJ_set_blank_status(plane1->Tag(),UF_OBJ_BLANKED);

	return 0;
}

logical TYCOM_get_obj_attr_Long2(tag_t obj, NXString title, NXString &value)
{
    logical has = false;
    if(obj == NULL_TAG)
        return has;
    tag_t obj_tag = obj;
    if( UF_ASSEM_is_occurrence( obj ))
    {
        obj_tag = UF_ASSEM_ask_prototype_of_occ ( obj ) ;
    }
    char* values = NULL;
    //const char* p = title.GetText();
    UF_ATTR_get_string_user_attribute(obj_tag,title.GetText(),UF_ATTR_NOT_ARRAY,&values,&has);
    if(has)
        value = values;
    UF_free(values);
    return has;
}
int TYCOM_get_obj_attr_Long(tag_t obj, NXString title, NXString &value)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(obj);
	NXObject* pbody = dynamic_cast<NXObject*> (tagobj);
	if(pbody == NULL)
		return -1;

	value = pbody->GetStringUserAttribute(title, -1);
	//const char * cstr1 = value.GetText();

	//int size  = pbody->GetUserAttributeSize(title, NXOpen::NXObject::AttributeTypeString);
	//NXOpen::NXObject::AttributeInformation info = pbody->GetUserAttribute(title, NXOpen::NXObject::AttributeTypeString, -1);
	//value = info.StringValue;
 //   const char * cstr2 = info.StringValue.GetText();
	////�������ַ����������õ�����
	return 0;
}
int TYCOM_ProjectCurveToFace(tag_t curve, tag_t face, tag_t &proFeature)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
    NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
    
    NXOpen::Features::ProjectCurveBuilder *projectCurveBuilder1;
    projectCurveBuilder1 = workPart->Features()->CreateProjectCurveBuilder(nullNXOpen_Features_Feature); 
    projectCurveBuilder1->CurveFitData()->SetTolerance(0.01);
    projectCurveBuilder1->CurveFitData()->SetAngleTolerance(0.5);
    projectCurveBuilder1->SectionToProject()->SetDistanceTolerance(0.01);
    projectCurveBuilder1->SectionToProject()->SetChainingTolerance(0.0095);
    projectCurveBuilder1->SectionToProject()->SetAngleTolerance(0.5);
    projectCurveBuilder1->SectionToProject()->SetAllowedEntityTypes(NXOpen::Section::AllowTypesCurvesAndPoints);
     
    std::vector<NXOpen::IBaseCurve *> curves1(1);
	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(curve);
	Line* line1 = dynamic_cast<Line*> (tagobj);
    curves1[0] = line1;
    NXOpen::CurveDumbRule *curveDumbRule1;
    curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);
    
    projectCurveBuilder1->SectionToProject()->AllowSelfIntersection(true);
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = curveDumbRule1;
    NXOpen::NXObject *nullNXOpen_NXObject(NULL);
    NXOpen::Point3d helpPoint1(0, 0, 0);
    projectCurveBuilder1->SectionToProject()->AddToSection(rules1, line1, nullNXOpen_NXObject, nullNXOpen_NXObject, helpPoint1, NXOpen::Section::ModeCreate, false);
    
    NXOpen::ScCollector *scCollector1;
    scCollector1 = workPart->ScCollectors()->CreateCollector();
    
    std::vector<NXOpen::Face *> faces1(1);
	TaggedObject * tagobj1 = NXOpen::NXObjectManager::Get(face);
    Face* face1 = dynamic_cast<Face*> (tagobj1);
    faces1[0] = face1;
    NXOpen::FaceDumbRule *faceDumbRule1;
    faceDumbRule1 = workPart->ScRuleFactory()->CreateRuleFaceDumb(faces1);
    
    std::vector<NXOpen::SelectionIntentRule *> rules2(1);

    rules2[0] = faceDumbRule1;
    scCollector1->ReplaceRules(rules2, false);
    bool added1;
    added1 = projectCurveBuilder1->FaceToProjectTo()->Add(scCollector1);
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = projectCurveBuilder1->Commit();
	proFeature = nXObject1->Tag();

    projectCurveBuilder1->SectionToProject()->CleanMappingData();
    projectCurveBuilder1->SectionToProject()->CleanMappingData();
    projectCurveBuilder1->Destroy();

	return 0;
}
int TYCOM_ExtrudeFromCurveWithOffset(tag_t curve, double height, double width, double normal[3],  tag_t &feat)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
    NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
   
    
    NXOpen::Features::ExtrudeBuilder *extrudeBuilder1;
    extrudeBuilder1 = workPart->Features()->CreateExtrudeBuilder(nullNXOpen_Features_Feature);
    
    NXOpen::Section *section1;
    section1 = workPart->Sections()->CreateSection(0.0095, 0.01, 0.5);
    extrudeBuilder1->SetSection(section1);
    extrudeBuilder1->AllowSelfIntersectingSection(true);
    
    NXOpen::Unit *unit1;
    unit1 = extrudeBuilder1->Draft()->FrontDraftAngle()->Units();
    extrudeBuilder1->SetDistanceTolerance(0.01);
    extrudeBuilder1->BooleanOperation()->SetType(NXOpen::GeometricUtilities::BooleanOperation::BooleanTypeCreate);
    
    std::vector<NXOpen::Body *> targetBodies1(1);
    NXOpen::Body *nullNXOpen_Body(NULL);
    targetBodies1[0] = nullNXOpen_Body;
    extrudeBuilder1->BooleanOperation()->SetTargetBodies(targetBodies1);

    
    extrudeBuilder1->Limits()->StartExtend()->Value()->SetRightHandSide("0");
	char cHeight[16] = "";
	sprintf(cHeight, "%.3f", height);
    extrudeBuilder1->Limits()->EndExtend()->Value()->SetRightHandSide(cHeight);
    
	char cWidth[16] = "";
	sprintf(cWidth, "%.3f", -width/2.0);
    extrudeBuilder1->Offset()->StartOffset()->SetRightHandSide(cWidth);
	sprintf(cWidth, "%.3f", width/2.0);
    extrudeBuilder1->Offset()->EndOffset()->SetRightHandSide(cWidth);
    
    section1->SetDistanceTolerance(0.01);
    section1->SetChainingTolerance(0.0095);
    section1->SetAllowedEntityTypes(NXOpen::Section::AllowTypesOnlyCurves);
  
    
    section1->AllowSelfIntersection(true);
    

	std::vector<NXOpen::IBaseCurve *> curves1(1);
    TaggedObject * tagobj = NXOpen::NXObjectManager::Get(curve);
    Line* line1 = dynamic_cast<Line*> (tagobj);
    curves1[0] = line1;
    NXOpen::CurveDumbRule *curveDumbRule1;
    curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);
    
    section1->AllowSelfIntersection(true);
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = curveDumbRule1;
    NXOpen::NXObject *nullNXOpen_NXObject(NULL);
    NXOpen::Point3d helpPoint1(0, 0, 0);
    section1->AddToSection(rules1, line1, nullNXOpen_NXObject, nullNXOpen_NXObject, helpPoint1, NXOpen::Section::ModeCreate, false);

    
    NXOpen::Point3d origin1(0, 0, 0);
    NXOpen::Vector3d vector1(normal[0], normal[1], normal[2]);
    NXOpen::Direction *direction1;
    direction1 = workPart->Directions()->CreateDirection(origin1, vector1, NXOpen::SmartObject::UpdateOptionWithinModeling);
    
    extrudeBuilder1->SetDirection(direction1);
    
    NXOpen::Unit *unit2;
    unit2 = extrudeBuilder1->Offset()->StartOffset()->Units();
    extrudeBuilder1->Offset()->SetOption(NXOpen::GeometricUtilities::TypeNonsymmetricOffset);
    
    extrudeBuilder1->SetParentFeatureInternal(false);
    
    NXOpen::Features::Feature *feature1;
    feature1 = extrudeBuilder1->CommitFeature();
    feat = feature1->Tag();
    
    NXOpen::Expression *expression5(extrudeBuilder1->Limits()->StartExtend()->Value());
    NXOpen::Expression *expression6(extrudeBuilder1->Limits()->EndExtend()->Value());
    extrudeBuilder1->Destroy();
    
	return 0;
}

int TYCOM_Champher(tag_t edge, double angle, double dist, tag_t &feat)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());

	NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
	NXOpen::Features::ChamferBuilder *chamferBuilder1;
	chamferBuilder1 = workPart->Features()->CreateChamferBuilder(nullNXOpen_Features_Feature);

	chamferBuilder1->SetOption(NXOpen::Features::ChamferBuilder::ChamferOptionOffsetAndAngle);
	chamferBuilder1->SetMethod(NXOpen::Features::ChamferBuilder::OffsetMethodEdgesAlongFaces);

	//chamferBuilder1->SetFirstOffset("20");
	//chamferBuilder1->SetSecondOffset("20");
	char cangle[32] = "";
	sprintf(cangle, "%.3f", angle);
	chamferBuilder1->SetAngle(cangle);

	char cdist[32] = "";
	sprintf(cdist, "%.3f", dist);
	chamferBuilder1->FirstOffsetExp()->SetRightHandSide(cdist);
	chamferBuilder1->SetTolerance(0.01);

	NXOpen::ScCollector *scCollector1;
	scCollector1 = workPart->ScCollectors()->CreateCollector();

	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(edge);
	Edge* edge1 = dynamic_cast<Edge*> (tagobj);

	NXOpen::Edge *nullNXOpen_Edge(NULL);
	NXOpen::EdgeTangentRule *edgeTangentRule1;
	edgeTangentRule1 = workPart->ScRuleFactory()->CreateRuleEdgeTangent(edge1, nullNXOpen_Edge, true, 0.5, true, false);

	std::vector<NXOpen::SelectionIntentRule *> rules1(1);
	rules1[0] = edgeTangentRule1;
	scCollector1->ReplaceRules(rules1, false);

	chamferBuilder1->SetSmartCollector(scCollector1);

	NXOpen::Features::Feature *feature1;
	feature1 = chamferBuilder1->CommitFeature();
	feat = feature1->Tag();
	chamferBuilder1->Destroy();

	return 0;
}
int TYCOM_ImportPart(NXOpen::CartesianCoordinateSystem *ccs, NXString fileName, NXOpen::Point3d destinationPoint1)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    NXOpen::PartImporter *partImporter1;
    partImporter1 = workPart->ImportManager()->CreatePartImporter();
    
    partImporter1->SetFileName(fileName);
    
    partImporter1->SetScale(1.0);
    
    partImporter1->SetCreateNamedGroup(true);
    
    partImporter1->SetImportViews(false);
    
    partImporter1->SetImportCamObjects(false);
    
    partImporter1->SetLayerOption(NXOpen::PartImporter::LayerOptionTypeWork);
    
    partImporter1->SetDestinationCoordinateSystemSpecification(NXOpen::PartImporter::DestinationCoordinateSystemSpecificationTypeSpecified);
    
    partImporter1->SetSpecifiedCoordinateSystem(ccs, false);
    
    partImporter1->SetDestinationPoint(destinationPoint1);
  
    NXOpen::NXObject *nXObject1;
    nXObject1 = partImporter1->Commit();
    
    partImporter1->Destroy();

	return 0;
}

int TYCOM_CreateBoxWithCSYS_ForBody(tag_t solidBody, tag_t csys, NXOpen::Point3d pnt0, tag_t &boxFeat)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
   
    NXOpen::Features::ToolingBox *nullNXOpen_Features_ToolingBox(NULL);
    
    NXOpen::Features::ToolingBoxBuilder *toolingBoxBuilder1;
    toolingBoxBuilder1 = workPart->Features()->ToolingFeatureCollection()->CreateToolingBoxBuilder(nullNXOpen_Features_ToolingBox);
    
    toolingBoxBuilder1->SetType(NXOpen::Features::ToolingBoxBuilder::TypesBoundedBlock);
    toolingBoxBuilder1->SetReferenceCsysType(NXOpen::Features::ToolingBoxBuilder::RefCsysTypeSelectedCsys);
    
    //toolingBoxBuilder1->XValue()->SetRightHandSide("10");
    //toolingBoxBuilder1->YValue()->SetRightHandSide("10");
    //toolingBoxBuilder1->ZValue()->SetRightHandSide("10");
    //toolingBoxBuilder1->OffsetPositiveX()->SetRightHandSide("1");
    //toolingBoxBuilder1->OffsetNegativeX()->SetRightHandSide("1");
    //toolingBoxBuilder1->OffsetPositiveY()->SetRightHandSide("1");
    //toolingBoxBuilder1->OffsetNegativeY()->SetRightHandSide("1");
    //toolingBoxBuilder1->OffsetPositiveZ()->SetRightHandSide("1");
    //toolingBoxBuilder1->OffsetNegativeZ()->SetRightHandSide("1");
    //toolingBoxBuilder1->RadialOffset()->SetRightHandSide("1");
    toolingBoxBuilder1->Clearance()->SetRightHandSide("1");
    
	TaggedObject * tagobj = NXOpen::NXObjectManager::Get(solidBody);
	if(NULL == (dynamic_cast<Body*> (tagobj)))
		return 1;

    std::vector<NXOpen::Body *> bodies1(1);
	bodies1[0] = (Body *)tagobj;
   
    NXOpen::BodyDumbRule *bodyDumbRule1;
    bodyDumbRule1 = workPart->ScRuleFactory()->CreateRuleBodyDumb(bodies1, true);
    
    NXOpen::ScCollector *scCollector1;
    scCollector1 = toolingBoxBuilder1->BoundedObject();
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = bodyDumbRule1;
    scCollector1->ReplaceRules(rules1, false);
    
    //std::vector<NXOpen::NXObject *> selections1(1);
    //selections1[0] = body1;
    //std::vector<NXOpen::NXObject *> deselections1(0);
   // toolingBoxBuilder1->SetSelectedOccurrences(selections1, deselections1);
    
    //NXOpen::SelectNXObjectList *selectNXObjectList1;
   // selectNXObjectList1 = toolingBoxBuilder1->FacetBodies();
    
    //std::vector<NXOpen::NXObject *> objects1(0);
    //bool added1;
    //added1 = selectNXObjectList1->Add(objects1);
    
    //NXOpen::Features::DatumCsys *datumCsys1(dynamic_cast<NXOpen::Features::DatumCsys *>(workPart->Features()->FindObject("DATUM_CSYS(7)")));
    //NXOpen::CartesianCoordinateSystem *cartesianCoordinateSystem1(dynamic_cast<NXOpen::CartesianCoordinateSystem *>(datumCsys1->FindObject("CSYSTEM 1")));
    
	TaggedObject * pcsys = NXOpen::NXObjectManager::Get(csys);
	NXOpen::CartesianCoordinateSystem * ppcsys = dynamic_cast<NXOpen::CartesianCoordinateSystem *>(pcsys);
	if(ppcsys == 0)
		return -1;

	toolingBoxBuilder1->CsysSelection()->SetValue(ppcsys);
    
	double matrix_values[9] = {0};
	TYCOM_GetCSYSMatrix(csys, matrix_values);

    NXOpen::Matrix3x3 matrix1  = TYCOM_MatrixConvert(matrix_values);

    //NXOpen::Point3d position1(11.9597518106377, -17.8300103442615, -148.707482295917);

	double pnt3[3] = {0};
	TYCOM_GetCSYSOri(csys, pnt3);
	NXOpen::Point3d position1(pnt3[0], pnt3[1], pnt3[2]);
    toolingBoxBuilder1->SetBoxMatrixAndPosition(matrix1, position1);
    
    toolingBoxBuilder1->CalculateBoxSize();
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = toolingBoxBuilder1->Commit();
   
    toolingBoxBuilder1->Destroy();
}
int GetSplineAttachedToBody(const tag_t body, const vtag_t& allSplines, vtag_t& curSplines)
{
	curSplines.clear();
	tag_t proBody = TYCOM_Prototype(body);
	for( int idx = 0; idx < allSplines.size(); ++idx )
	{
		char handle[UF_ATTR_MAX_STRING_BUFSIZE+1]="";
		tag_t proSpline = allSplines[idx];
		int irc = USER_ask_obj_string_attr(proSpline,ATTR_TYCOM_TEXT_SPLINE_BODY_HANDLE,handle);
		if( 1 == irc )
		{
			tag_t recTag = UF_TAG_ask_tag_of_handle(handle);
			if( recTag == proBody )
			{
				curSplines.push_back(allSplines[idx]);
			}
		}
	}
	return curSplines.size();
}

void TYCOM_WaveLinkSplinesToWorkPart(vtag_t& splines, logical Associative, logical Hideoriginal,logical addlineRef)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);

    NXOpen::Features::WaveLinkBuilder *waveLinkBuilder1;
    waveLinkBuilder1 = workPart->BaseFeatures()->CreateWaveLinkBuilder(nullNXOpen_Features_Feature);
    
    NXOpen::Features::WaveDatumBuilder *waveDatumBuilder1;
    waveDatumBuilder1 = waveLinkBuilder1->WaveDatumBuilder();
    
    NXOpen::Features::CompositeCurveBuilder *compositeCurveBuilder1;
    compositeCurveBuilder1 = waveLinkBuilder1->CompositeCurveBuilder();
    
    NXOpen::Features::WaveSketchBuilder *waveSketchBuilder1;
    waveSketchBuilder1 = waveLinkBuilder1->WaveSketchBuilder();
    
    NXOpen::Features::WaveRoutingBuilder *waveRoutingBuilder1;
    waveRoutingBuilder1 = waveLinkBuilder1->WaveRoutingBuilder();
    
    NXOpen::Features::WavePointBuilder *wavePointBuilder1;
    wavePointBuilder1 = waveLinkBuilder1->WavePointBuilder();
    
    NXOpen::Features::ExtractFaceBuilder *extractFaceBuilder1;
    extractFaceBuilder1 = waveLinkBuilder1->ExtractFaceBuilder();
    
    NXOpen::Features::MirrorBodyBuilder *mirrorBodyBuilder1;
    mirrorBodyBuilder1 = waveLinkBuilder1->MirrorBodyBuilder();
    
    extractFaceBuilder1->SetFaceOption(NXOpen::Features::ExtractFaceBuilder::FaceOptionTypeFaceChain);
    
    extractFaceBuilder1->SetFaceOption(NXOpen::Features::ExtractFaceBuilder::FaceOptionTypeFaceChain);
    
    extractFaceBuilder1->SetAngleTolerance(45.0);
    
    waveLinkBuilder1->SetAssociative(false);
    
    waveDatumBuilder1->SetDisplayScale(2.0);
    
    extractFaceBuilder1->SetParentPart(NXOpen::Features::ExtractFaceBuilder::ParentPartTypeOtherPart);
    
    mirrorBodyBuilder1->SetParentPartType(NXOpen::Features::MirrorBodyBuilder::ParentPartOtherPart);
    
    compositeCurveBuilder1->Section()->SetDistanceTolerance(0.0254);
    
    compositeCurveBuilder1->Section()->SetChainingTolerance(0.02413);
    
    compositeCurveBuilder1->SetAssociative(false);
    
    compositeCurveBuilder1->SetMakePositionIndependent(false);
    
    compositeCurveBuilder1->SetFixAtCurrentTimestamp(false);
    
    compositeCurveBuilder1->SetHideOriginal(true);
    
    compositeCurveBuilder1->SetInheritDisplayProperties(false);
    
    compositeCurveBuilder1->SetJoinOption(NXOpen::Features::CompositeCurveBuilder::JoinMethodNo);
    
    compositeCurveBuilder1->SetTolerance(0.0254);
    
    NXOpen::Section *section1;
    section1 = compositeCurveBuilder1->Section();
    
    section1->SetAllowedEntityTypes(NXOpen::Section::AllowTypesCurvesAndPoints);
    
    compositeCurveBuilder1->SetHideOriginal(false);
    
    std::vector<NXOpen::IBaseCurve *> curves1;

	for( int idx = 0; idx < splines.size(); ++idx )
	{
		NXOpen::IBaseCurve *icurve1(dynamic_cast<NXOpen::IBaseCurve *>(NXObjectManager::Get(splines[idx])));
		curves1.push_back(icurve1);
	}
    NXOpen::CurveDumbRule *curveDumbRule1;
    curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);
    
    section1->AllowSelfIntersection(false);
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = curveDumbRule1;
    NXOpen::NXObject *nullNXOpen_NXObject(NULL);
    NXOpen::Point3d helpPoint1(0.0, 0.0, 0.0);
    section1->AddToSection(rules1, nullNXOpen_NXObject, nullNXOpen_NXObject, nullNXOpen_NXObject, helpPoint1, NXOpen::Section::ModeCreate, false);
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = waveLinkBuilder1->Commit();
	tag_t linkCurvefeat= nXObject1->Tag();
	if( linkCurvefeat != NULL_TAG )
	{
		vtag_t curves;
		int n_eids = 0, n=0;
		tag_t *eids = NULL;
		tag_t *source = NULL;
		tag_t *linkgeos = NULL;
		tag_t geo = NULL_TAG;
		UF_MODL_ask_feat_object(linkCurvefeat, &n_eids, &eids);
		for( int idx =  0; idx < n_eids; ++idx )
		{
			curves.push_back(eids[idx]);
		}
		CreateReferenceSet(curves,NXString("MODEL"));
        if( addlineRef )
            CreateReferenceSet(curves,NXString(ATTR_TYCOM_DRAWING_REFERENCE_SET));
		UF_free(eids);
		UF_free(source);
		UF_free(linkgeos);
	}
    waveLinkBuilder1->Destroy();
}
tag_t TYCOM_WaveLinkBodyToWorkPart2( vtag_t& bodies, vtag_t& allSplines, logical Associative, logical Hideoriginal,logical addlineRef)
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    NXOpen::Part *displayPart(theSession->Parts()->Display());

    
    NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
    
    NXOpen::Features::WaveLinkBuilder *waveLinkBuilder1;
    waveLinkBuilder1 = workPart->BaseFeatures()->CreateWaveLinkBuilder(nullNXOpen_Features_Feature);
    
    NXOpen::Features::ExtractFaceBuilder *extractFaceBuilder1;
    extractFaceBuilder1 = waveLinkBuilder1->ExtractFaceBuilder();
    
    waveLinkBuilder1->SetType(NXOpen::Features::WaveLinkBuilder::TypesBodyLink);
    
    extractFaceBuilder1->SetFaceOption(NXOpen::Features::ExtractFaceBuilder::FaceOptionTypeFaceChain);
    
    extractFaceBuilder1->SetAngleTolerance(45.0);
    
    //waveDatumBuilder1->SetDisplayScale(2.0);
    
    extractFaceBuilder1->SetParentPart(NXOpen::Features::ExtractFaceBuilder::ParentPartTypeOtherPart);
    
    //compositeCurveBuilder1->Section()->SetDistanceTolerance(0.01);
    
    //compositeCurveBuilder1->Section()->SetChainingTolerance(0.0095);
    
    extractFaceBuilder1->SetAssociative(Associative);
    
    extractFaceBuilder1->SetMakePositionIndependent(false);
    
    extractFaceBuilder1->SetFixAtCurrentTimestamp(false);
    
    extractFaceBuilder1->SetHideOriginal(Hideoriginal);
    
    extractFaceBuilder1->SetInheritDisplayProperties(false);
    
    NXOpen::ScCollector *scCollector1;
    scCollector1 = extractFaceBuilder1->ExtractBodyCollector();
    
    extractFaceBuilder1->SetCopyThreads(true);

	std::vector<NXOpen::Body *> bodies1;
	for( int idx =  0; idx < bodies.size(); ++idx )
    {
        NXOpen::TaggedObject *object = NXOpen::NXObjectManager::Get(bodies[idx]);
        Body *body1 = dynamic_cast<Body *>(object);
		bodies1.push_back(body1);
    }
	NXOpen::BodyDumbRule *bodyDumbRule1;
    bodyDumbRule1 = workPart->ScRuleFactory()->CreateRuleBodyDumb(bodies1, true);
	std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = bodyDumbRule1;
    scCollector1->ReplaceRules(rules1, false);
    
    
    extractFaceBuilder1->SetFeatureOption(NXOpen::Features::ExtractFaceBuilder::FeatureOptionTypeSeparateFeatureForEachBody);
    
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = waveLinkBuilder1->Commit();
    
    waveLinkBuilder1->Destroy();

	if( allSplines.size() > 0 )
	{
		vtag_t cursplines;
		for( int idx =  0; idx < bodies.size(); ++idx )
		{
			vtag_t temsplines;
			GetSplineAttachedToBody(bodies[idx],allSplines,temsplines);
			for( int jdx =  0; jdx < temsplines.size(); ++jdx )
			{
				AddTagToVector(temsplines[jdx],cursplines);
			}
		}
		if(cursplines.size() > 0)
		{
			TYCOM_WaveLinkSplinesToWorkPart(cursplines,Associative,Hideoriginal,addlineRef);
		}
	}

    return nXObject1->Tag();

}

int TYCOM_SubtractInAssembly(tag_t targetBody, tag_t toolBody)
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
    NXOpen::Features::BooleanFeature *nullNXOpen_Features_BooleanFeature(NULL);
    
    NXOpen::Features::BooleanBuilder *booleanBuilder1;
    booleanBuilder1 = workPart->Features()->CreateBooleanBuilderUsingCollector(nullNXOpen_Features_BooleanFeature);
    
    NXOpen::ScCollector *scCollector1;
    scCollector1 = booleanBuilder1->ToolBodyCollector();
    
    NXOpen::GeometricUtilities::BooleanRegionSelect *booleanRegionSelect1;
    booleanRegionSelect1 = booleanBuilder1->BooleanRegionSelect();
    
    booleanBuilder1->SetTolerance(0.01);
    
    booleanBuilder1->SetOperation(NXOpen::Features::Feature::BooleanTypeSubtract);
    

	//Ŀ����
    NXOpen::Body *body1(dynamic_cast<NXOpen::Body *>(workPart->Bodies()->FindObject("BLOCK(1)")));
    bool added1;
    added1 = booleanBuilder1->Targets()->Add(body1);
    std::vector<NXOpen::TaggedObject *> targets1(1);
    targets1[0] = body1;
    booleanRegionSelect1->AssignTargets(targets1);
   
    
	//������
	NXOpen::TaggedObject *object = NXOpen::NXObjectManager::Get(toolBody);
    Body *body2 = dynamic_cast<Body *>(object);

    std::vector<NXOpen::Body *> bodies1(1);
    bodies1[0] = body2;
    NXOpen::BodyDumbRule *bodyDumbRule1;
    bodyDumbRule1 = workPart->ScRuleFactory()->CreateRuleBodyDumb(bodies1);
    

	NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
    NXOpen::Features::ExtractFaceBuilder *extractFaceBuilder1;
    extractFaceBuilder1 = workPart->Features()->CreateExtractFaceBuilder(nullNXOpen_Features_Feature);
    extractFaceBuilder1->SetType(NXOpen::Features::ExtractFaceBuilder::ExtractTypeBody);
    extractFaceBuilder1->SetParentPart(NXOpen::Features::ExtractFaceBuilder::ParentPartTypeOtherPart);
    extractFaceBuilder1->SetAssociative(true);
    
    NXOpen::ScCollector *scCollector2;
    scCollector2 = extractFaceBuilder1->ExtractBodyCollector();



    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = bodyDumbRule1;
    scCollector2->ReplaceRules(rules1, false);
    delete bodyDumbRule1;
    NXOpen::Features::Feature *feature1;
    feature1 = extractFaceBuilder1->CommitCreateOnTheFly();
     extractFaceBuilder1->Destroy();

    NXOpen::GeometricUtilities::WaveLinkRepository *waveLinkRepository1;
    waveLinkRepository1 = workPart->CreateWavelinkRepository();
    waveLinkRepository1->SetNonFeatureApplication(false);
    waveLinkRepository1->SetBuilder(booleanBuilder1);

    NXOpen::Features::ExtractFace *extractFace1(dynamic_cast<NXOpen::Features::ExtractFace *>(feature1));
    waveLinkRepository1->SetLink(extractFace1);

    NXOpen::Features::ExtractFaceBuilder *extractFaceBuilder2;
    extractFaceBuilder2 = workPart->Features()->CreateExtractFaceBuilder(extractFace1);
    extractFaceBuilder2->SetAssociative(false);
  
    NXOpen::Features::Feature *feature2;
    feature2 = extractFaceBuilder2->CommitCreateOnTheFly();
    extractFaceBuilder2->Destroy();


	tag_t featureBody = 0;
	char * featName = 0;
	UF_MODL_ask_feat_body(feature2->Tag(), &featureBody);
	UF_MODL_ask_feat_name(feature2->Tag(), &featName);
  

    NXOpen::ScCollector *scCollector3;
    scCollector3 = workPart->ScCollectors()->CreateCollector();
    
    std::vector<NXOpen::Body *> bodies2(1);
    //NXOpen::Body *body3(dynamic_cast<NXOpen::Body *>(workPart->Bodies()->FindObject("LINKED_BODY(5)")));

	object = NXOpen::NXObjectManager::Get(featureBody);
    Body *body3 = dynamic_cast<Body *>(object);

    std::vector<NXOpen::Body *> bodies3(1);
    bodies3[0] = body3;
    NXOpen::BodyDumbRule *bodyDumbRule3;
    bodyDumbRule3 = workPart->ScRuleFactory()->CreateRuleBodyDumb(bodies3, true);
    
    std::vector<NXOpen::SelectionIntentRule *> rules3(1);
    rules3[0] = bodyDumbRule3;
    scCollector3->ReplaceRules(rules3, false);
    
    booleanBuilder1->SetToolBodyCollector(scCollector3);
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = booleanBuilder1->Commit();

    booleanBuilder1->Destroy();
    waveLinkRepository1->Destroy();
	return 0;
}

int TYCOM_WaveLinkBodyToWorkPart(tag_t body)
{

	NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());
    
    NXOpen::Features::Feature *nullNXOpen_Features_Feature(NULL);
    NXOpen::Features::WaveLinkBuilder *waveLinkBuilder1;
    waveLinkBuilder1 = workPart->BaseFeatures()->CreateWaveLinkBuilder(nullNXOpen_Features_Feature);
    
    NXOpen::Features::ExtractFaceBuilder *extractFaceBuilder1;
    extractFaceBuilder1 = waveLinkBuilder1->ExtractFaceBuilder();
    
    extractFaceBuilder1->SetFaceOption(NXOpen::Features::ExtractFaceBuilder::FaceOptionTypeFaceChain);
    
    waveLinkBuilder1->SetType(NXOpen::Features::WaveLinkBuilder::TypesBodyLink);
    
    extractFaceBuilder1->SetFaceOption(NXOpen::Features::ExtractFaceBuilder::FaceOptionTypeFaceChain);
    
    extractFaceBuilder1->SetAngleTolerance(45.0);
    
    extractFaceBuilder1->SetParentPart(NXOpen::Features::ExtractFaceBuilder::ParentPartTypeOtherPart);
    
    extractFaceBuilder1->SetAssociative(true);
    
    extractFaceBuilder1->SetMakePositionIndependent(false);
    
    extractFaceBuilder1->SetFixAtCurrentTimestamp(false);
    
    extractFaceBuilder1->SetHideOriginal(false);
    
    extractFaceBuilder1->SetInheritDisplayProperties(false);
    
    NXOpen::ScCollector *scCollector1;
    scCollector1 = extractFaceBuilder1->ExtractBodyCollector();
    
    extractFaceBuilder1->SetCopyThreads(true);
    
    extractFaceBuilder1->SetFeatureOption(NXOpen::Features::ExtractFaceBuilder::FeatureOptionTypeOneFeatureForAllBodies);
    
    std::vector<NXOpen::Body *> bodies1(1);
    //NXOpen::Assemblies::Component *component1(dynamic_cast<NXOpen::Assemblies::Component *>(workPart->ComponentAssembly()->RootComponent()->FindObject("COMPONENT screw 1")));
    //NXOpen::Body *body1(dynamic_cast<NXOpen::Body *>(component1->FindObject("PROTO#.Bodies|EXTRUDE(30)")));
	NXOpen::TaggedObject *object = NXOpen::NXObjectManager::Get(body);
    Body *body1 = dynamic_cast<Body *>(object);
    bodies1[0] = body1;
    NXOpen::BodyDumbRule *bodyDumbRule1;
    bodyDumbRule1 = workPart->ScRuleFactory()->CreateRuleBodyDumb(bodies1, true);
    
    std::vector<NXOpen::SelectionIntentRule *> rules1(1);
    rules1[0] = bodyDumbRule1;
    scCollector1->ReplaceRules(rules1, false);
   
    NXOpen::NXObject *nXObject1;
    nXObject1 = waveLinkBuilder1->Commit();
    waveLinkBuilder1->Destroy();

	return 0;
}

/*
int TYCOM_GetMirrorBodiesForOneBody1(tag_t seedBody, vtag_t& allBodies, vtag_t &mirrorBodies)
{
	if(seedBody == 0)
		return -1;

	char attriValue[128] = "";
	int has = USER_ask_obj_string_attr( seedBody , ATTR_TYCOM_MIRROR_OBJ , attriValue );
	if(!has)
		return -2;

	for(int i = 0; i < allBodies.size(); i++)
	{
		if(allBodies[i] == seedBody)
			continue;

		char attriValue2[128] = "";
	    int has2 = USER_ask_obj_string_attr( allBodies[i] , ATTR_TYCOM_MIRROR_OBJ , attriValue2 );
		if(!has2)
			continue;

		if(strcmp(attriValue, attriValue2) == 0)
			mirrorBodies.push_back(allBodies[i]);
	}

	return 0;
}
int TYCOM_GetMirrorBodiesForOneBody(tag_t seedBody, vtag_t& allBodies, vtag_t &mirrorBodies)
{
int type = -1;
char attriValue[128] = "";
if(seedBody == 0)
return -1;

char attributes[][256]={ATTR_TYCOM_MIRROR_OBJ,ATTR_TYCOM_SAME_OBJ,ATTR_TYCOM_WELD_OBJ};
for( int idx = 0; idx < 3; ++idx )
{
int has = USER_ask_obj_string_attr( seedBody , attributes[idx] , attriValue );
{
if( has )
{
type = idx;
for(int i = 0; i < allBodies.size(); i++)
{
if(allBodies[i] == seedBody)
continue;

char attriValue2[128] = "";
int has2 = USER_ask_obj_string_attr( allBodies[i] , attributes[idx] , attriValue2 );
if(!has2)
continue;

if(strcmp(attriValue, attriValue2) == 0)
mirrorBodies.push_back(allBodies[i]);
}
break;
}
}
}
return type;
}

int TYCOM_GetSameBodiesForOneBody(tag_t seedBody, vtag_t &sameBodies)
{
if(seedBody == 0)
return -1;

vtag_t allBodies;
TYCOM_GetCurrentPartSolidBodies2(allBodies);


return TYCOM_GetSameBodiesForOneBody(seedBody,allBodies,sameBodies);
}

int TYCOM_GetSameBodiesForOneBody(tag_t seedBody, vtag_t& allBodies, vtag_t &sameBodies)
{
if(seedBody == 0)
return -1;

char attriValue[128] = "";
int has = USER_ask_obj_string_attr( seedBody , ATTR_TYCOM_SAME_OBJ , attriValue );
if(!has)
return -2;

for(int i = 0; i < allBodies.size(); i++)
{
if(allBodies[i] == seedBody)
continue;

char attriValue2[128] = "";
int has2 = USER_ask_obj_string_attr( allBodies[i] , ATTR_TYCOM_SAME_OBJ , attriValue2 );
if(!has2)
continue;

if(strcmp(attriValue, attriValue2) == 0)
sameBodies.push_back(allBodies[i]);
}

return 0;
}

int TYCOM_GetWeldBodiesForOneBody(tag_t seedBody, vtag_t &weldBodies)
{
if(seedBody == 0)
return -1;

vtag_t allBodies;
TYCOM_GetCurrentPartSolidBodies2(allBodies);


return TYCOM_GetWeldBodiesForOneBody(seedBody,allBodies,weldBodies);
}

int TYCOM_GetWeldBodiesForOneBody(tag_t seedBody, vtag_t& allBodies, vtag_t &weldBodies)
{
if(seedBody == 0)
return -1;

char attriValue[128] = "";
int has = USER_ask_obj_string_attr( seedBody , ATTR_TYCOM_WELD_OBJ , attriValue );
if(!has)
return -2;

for(int i = 0; i < allBodies.size(); i++)
{
if(allBodies[i] == seedBody)
continue;

char attriValue2[128] = "";
int has2 = USER_ask_obj_string_attr( allBodies[i] , ATTR_TYCOM_WELD_OBJ , attriValue2 );
if(!has2)
continue;

if(strcmp(attriValue, attriValue2) == 0)
weldBodies.push_back(allBodies[i]);
}

return 0;
}

int TYCOM_GetGroupSelIndexs(NXString gruopNumber, vint &selIndexs)
{
vtag_t bodies;
TYCOM_GetCurrentPartSolidBodies2(bodies);
for(int i = 0; i < bodies.size(); i++)
{
char value[128] = "";

int has = USER_ask_obj_string_attr(bodies[i], ATTR_TYCOM_PROPERTY_GROUP_NUMBER, value);
if(has)
{
NXString str(value);
if(strcmp(str.GetText(), gruopNumber.GetText()) ==0)
{
int selIndex = 0;
int has2 = EF_ask_obj_integer_attr_Ori(bodies[i], ATTR_TYCOM_PROPERTY_GROUP_SUBINDEX, &selIndex);

if(vFind(selIndexs,selIndex) == -1)
selIndexs.push_back(selIndex);
}
}
}
return 0;
}


int TYCOM_GetGoupBodiesForOneBody(tag_t seedBody, vtag_t& allBodies, vtag_t &groupBodies)
{
int type = 3;
vtag_t sameBodies;
vtag_t weldBodies;
TYCOM_GetWeldBodiesForOneBody(seedBody,allBodies,groupBodies);
if( groupBodies.size() > 0 )
type = 2;
TYCOM_GetSameBodiesForOneBody(seedBody,allBodies,sameBodies);
if( sameBodies.size() > 0 )
type = 1; //�����Ǻ��Ӻ���ͬ��
//sameBodies.push_back(seedBody);
AddTagToVector(seedBody,sameBodies);
for( int idx = 0; idx < sameBodies.size(); ++idx )
{
vtag_t mirrorBodies;
TYCOM_GetMirrorBodiesForOneBody1(sameBodies[idx],allBodies,mirrorBodies);
AddTagToVector(sameBodies[idx],groupBodies);
for( int jdx = 0; jdx < mirrorBodies.size(); ++jdx )
{
type = 0; //�����Ǻ��Ӻ����
AddTagToVector(mirrorBodies[jdx],groupBodies);
}
}
if( 2 == type )
{
AddTagToVector(seedBody,groupBodies);//�������Ӽ�
}
return type;
}

int TYCOM_GetMirrorBodiesForOneBody1(tag_t seedBody, vtag_t &mirrorBodies)
{
if(seedBody == 0)
return -1;

vtag_t allBodies;
TYCOM_GetCurrentPartSolidBodies2(allBodies);


return TYCOM_GetMirrorBodiesForOneBody1(seedBody,allBodies,mirrorBodies);
}

*/


vtag_t TYCOM_GetBodiesFromObjects(vtag_t &objs)
{
	vtag_t bodies;
	for( int idx = 0; idx < objs.size(); ++idx )
	{
		int type = 0,subType = 0;
		UF_OBJ_ask_type_and_subtype( objs[idx], &type, &subType );
		if(  UF_solid_type == type && UF_solid_body_subtype == subType )//UF_tabular_note_type
		{
			bodies.push_back(objs[idx]);
		}
	}
	return bodies;
}

int TYCOM_OptionDialog(NXString title, vNXString &options)
{
	char cp1[256] = "";
	strcpy(cp1,title.getLocaleText());
	char cp3[16][38];
	for (int i = 0; i < options.size(); i++)
	{
		strcpy(cp3[i],options[i].getLocaleText());
	}
	int ret = uc1603 ( cp1, 0, cp3, options.size());
	if (ret == 1 || ret == 2 || ret == 5)
		return 0;
	else
		return ret - 5;
}

int TY_GetBodyXDir(tag_t body, double vecx[3])
{
	vecx[0] = 1;
	vecx[1] = 0;
	vecx[2] = 0;

	char str[133]="";
	int irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_X_X,str);
	if(irc == 1)
	    vecx[0] = atof(str);
	
	
	irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_X_Y,str);
	if(irc == 1)
		vecx[1] = atof(str);

	irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_X_Z,str);
	if(irc == 1)
		vecx[2] = atof(str);

	return 0;
}

int TY_GetBodyYDir(tag_t body, double vecx[3])
{
	vecx[0] = 0;
	vecx[1] = 1;
	vecx[2] = 0;

	char str[133]="";
	int irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_Y_X,str);
	if(irc == 1)
		vecx[0] = atof(str);

	irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_Y_Y,str);
	if(irc == 1)
		vecx[1] = atof(str);

	irc = TYCOM_GetObjectStringAttribute(body,ATTR_NORMAL_DIR_Y_Z,str);
	if(irc == 1)
		vecx[2] = atof(str);

	return 0;
}

int TY_GetBodyMatrix(tag_t body, double mtx [ 9 ])
{
	double x[3] = {0};
	double y[3] = {0};
    int ret = TY_GetBodyXDir(body, x);
	if (ret != 0)
		return ret;

	ret = TY_GetBodyYDir(body, y);
	if (ret != 0)
		return ret;
	
	return UF_MTX3_initialize(x, y, mtx);
}

tag_t TY_GetBodyMatrix(tag_t body)
{
	double mtx[9] = {0};
	double x[3] = {0};
	double y[3] = {0};
	int ret = TY_GetBodyXDir(body, x);
	if (ret != 0)
		return ret;

	ret = TY_GetBodyYDir(body, y);
	if (ret != 0)
		return ret;

	ret = UF_MTX3_initialize(x, y, mtx);
	if (ret != 0)
		return 0;
	tag_t mxid = 0;
	UF_CSYS_create_matrix(mtx, &mxid);
	return mxid;
}

tag_t TY_GetBodyCSYS(tag_t body, const double csys_origin [ 3 ])
{
	tag_t mx = TY_GetBodyMatrix(body);
	if (mx == 0)
		return 0;

	tag_t csys = 0;
	UF_CSYS_create_csys(csys_origin, mx, &csys);
	return csys;
}

int TY_GetBodyXYZLen_aligned(tag_t body, double &xLen,double &yLen,double &zLen)
{

	double csys_origin [ 3 ] = {0,0,0};
	tag_t csys = TY_GetBodyCSYS(body, csys_origin);
	if (csys == 0)
		return -1;
	
	double min_corner[3] = {0};
	double  directions[3][3] = {0};
	double  distances[3] = {0};
	//int ret = UF_MODL_ask_bounding_box_aligned(body,csys,true, min_corner,  directions, distances);
	int ret = UF_MODL_ask_bounding_box_exact(body,csys, min_corner,  directions, distances);

	//double boundingbox[6] = {0};
	//UF_MODL_ask_bounding_box(body, boundingbox);
	if (ret)
		return ret;
	xLen = distances[0];
	yLen = distances[1];
	zLen = distances[2];
	return ret;
}

int TYCOM_GetObjectLayer(tag_t body)
{
	UF_OBJ_disp_props_t disp_props;
	int ret = UF_OBJ_ask_display_properties(body, &disp_props);
	if (ret != 0)
		return -1;

	return disp_props.layer;
}

int CreateKeDuMark( char* textHeight,double kedu,Point3d coordinates22 )
{
	char *textstring[1];
    char textStr[133]="";
    sprintf_s(textStr,132,"%g",kedu);
	textstring[0] = textStr;
	double Id_locate[3]={coordinates22.X,coordinates22.Y,coordinates22.Z};
	tag_t note_tag = NULL_TAG;
	tag_t point_tag = NULL_TAG;

	int irc = UF_DRF_create_note(1,textstring ,Id_locate,0,&note_tag);
    UF_DRF_associative_origin_t origin_data;
    origin_data.origin_type = UF_DRF_ORIGIN_AT_A_POINT;
    origin_data.associated_view = NULL_TAG;
    UF_CURVE_create_point(Id_locate,&origin_data.associated_point);
    /*origin_data.offset_annotation = origin_data.associated_point;UF_DRF_init_associativity_data
    origin_data.offset_alignment_position = UF_DRF_ALIGN_BOTTOM_LEFT;*/
    UF_DRF_set_associative_origin(note_tag,&origin_data,Id_locate);
	return note_tag;

    //UF_DRF_ask_associative_origin(assoTag,&origin_data,origin);
    /*origin_data->origin_type = UF_DRF_ORIGIN_RELATIVE_TO_VIEW;
    origin_data->view_eid = view;
    UF_DRF_set_associative_origin(note_tag,origin_data,Id_locate);
    UF_free(origin_data);*/
    return 0;
}

void setWcsToCurrentView()
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	Point3d origin1 = workPart->Views()->WorkView()->Origin();
	Matrix3x3 matrix1 = workPart->Views()->WorkView()->Matrix();
	workPart->WCS()->SetOriginAndMatrix(origin1, matrix1);
}
tag_t CreateNoteText(char* textStr,double textHei, Point3d coordinates22, int type, logical isX, int xyz )
{
    NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

	CartesianCoordinateSystem *oldWcs = workPart->WCS()->CoordinateSystem();
	

    NXOpen::Annotations::SimpleDraftingAid *nullNXOpen_Annotations_SimpleDraftingAid(NULL);
    NXOpen::Annotations::DraftingNoteBuilder *draftingNoteBuilder1;
    draftingNoteBuilder1 = workPart->Annotations()->CreateDraftingNoteBuilder(nullNXOpen_Annotations_SimpleDraftingAid);
    
    std::vector<NXString> text1;
    text1.push_back(textStr);
    draftingNoteBuilder1->Text()->TextBlock()->SetText(text1);
    draftingNoteBuilder1->Style()->LetteringStyle()->SetGeneralTextSize(textHei);
	double angle = 0;
	NXOpen::Point3d point2(coordinates22.X+5, coordinates22.Y+5, coordinates22.Z); 
	//NXOpen::Point3d point2(coordinates22.X, coordinates22.Y, coordinates22.Z);
	
    draftingNoteBuilder1->SetTextAlignment(NXOpen::Annotations::DraftingNoteBuilder::TextAlignBelowTopExtToMaxUnderline);
	/*if( 1 == xyz )
		draftingNoteBuilder1->Origin()->Plane()->SetPlaneMethod(NXOpen::Annotations::PlaneBuilder::PlaneMethodTypeXyPlane);
	if( 2 == xyz )
	{
		draftingNoteBuilder1->Origin()->Plane()->SetPlaneMethod(NXOpen::Annotations::PlaneBuilder::PlaneMethodTypeXzPlane);
		workPart->WCS()->Rotate(NXOpen::WCS::AxisYAxis, 90.0);
	}
	else if(3 == xyz)
	{
		draftingNoteBuilder1->Origin()->Plane()->SetPlaneMethod(NXOpen::Annotations::PlaneBuilder::PlaneMethodTypeYzPlane);
		workPart->WCS()->Rotate(NXOpen::WCS::AxisYAxis, 90.0);
	}*/
	draftingNoteBuilder1->Origin()->Plane()->SetPlaneMethod(NXOpen::Annotations::PlaneBuilder::PlaneMethodTypeXyPlane);
	draftingNoteBuilder1->Origin()->SetInferRelativeToGeometry(true);

	draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomLeft);
    
    NXOpen::Point *point1;

	if(isX)
	{
		if( type == 1 || type == 2 )
		{
			point2.Y = coordinates22.Y-5;
			angle = 270;
		}
		else
		{
			point2.X = coordinates22.X-5;
			angle = 90;
		}
	}
	else
	{
		if( type == 3 || type == 2 )
		{
			point2.X = coordinates22.X-5;
			draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomRight);
		}
	}
    if( xyz == 0 )
    {
        point2.X = coordinates22.X+5;
        point2.Y = coordinates22.Y+5;
        point2.Z = coordinates22.Z;
        if(isX)
        {
            if(1==type||2==type)
            {
                point2.X = coordinates22.X-5;
                point2.Y = coordinates22.Y-5;
            }
        }
        else
        {
            if( 1==type||0==type )
                draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomRight);
            else
            {
                point2.X = coordinates22.X-5;
                draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomLeft);
            }
        }
    }
	else if( xyz == 2 )
    {
        point2.X = coordinates22.X+5;
        point2.Y = coordinates22.Y;
        point2.Z = coordinates22.Z+5;
        if(isX) 
        {
            point2.X = coordinates22.X-5;
            point2.Z = coordinates22.Z+5;
            if( type == 1 || type == 2 )
            {
                point2.X = coordinates22.X+5;
                point2.Z = coordinates22.Z-5;
            }
        }
        else
        {
            if( type == 3 || type == 2 )
            {
                point2.X = coordinates22.X-5;
                //point2.Z = coordinates22.Z-5;
            }
        }
    }
    else if( xyz == 4 )
    {
        point2.X = coordinates22.X+5;
        point2.Y = coordinates22.Y;
        point2.Z = coordinates22.Z+5;
        if(isX)
        {
            if( 1 == type || 2 == type )
            {
                point2.X = coordinates22.X-5;
                point2.Z = coordinates22.Z-5;
            }
        }
        else
        {
            draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomRight);
            if( type == 2 || type == 3 )
            {
                point2.X = coordinates22.X-5;
                draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomLeft);
            }
        }
    }
    else if( xyz == 3  )
    {
        point2.X = coordinates22.X;
        point2.Y = coordinates22.Y+5;
        point2.Z = coordinates22.Z+5;
        if(isX) 
        {
            point2.Y = coordinates22.Y-5;
            point2.Z = coordinates22.Z+5;
            if( type == 1 || type == 2 )
            {
                point2.Y = coordinates22.Y+5;
                point2.Z = coordinates22.Z-5;
            }
        }
        else
        {
            if( type == 2 || type == 3  )
            {
                point2.Y = coordinates22.Y-5;
            }
        }
    }
    else if( 5 == xyz )
    {
        point2.X = coordinates22.X;
        point2.Y = coordinates22.Y+5;
        point2.Z = coordinates22.Z+5;
        if( isX )
        {
            if( 1 == type || 2 == type)
            {
                point2.Y = coordinates22.Y-5;
                point2.Z = coordinates22.Z-5;
            }
        }
        else
        {
            if( 0 == type || 1 == type )
                draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomRight);
            else
            {
                point2.Y = coordinates22.Y-5;
                draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomLeft);
            }
        }
    }
    
    /*if( type == 1)
    {
        point2.Y = coordinates22.Y-5;
        draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionTopLeft);
    }
    else if( type == 2 )
    {
        point2.Y = coordinates22.Y-5;
        point2.X = coordinates22.X-5;
        draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionTopRight);
    }
    else if( type == 3 )
    {
        point2.X = coordinates22.X-5;
        draftingNoteBuilder1->Origin()->SetAnchor(NXOpen::Annotations::OriginBuilder::AlignmentPositionBottomRight);
    }*/
	draftingNoteBuilder1->Style()->LetteringStyle()->SetAngle(angle);
    
    point1 = workPart->Points()->CreatePoint(point2);
    
    NXOpen::Annotations::Annotation::AssociativeOriginData assocOrigin1;
    assocOrigin1.OriginType = NXOpen::Annotations::AssociativeOriginTypeAtAPoint;
    NXOpen::View *nullNXOpen_View(NULL);
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
    assocOrigin1.AssociatedView = workPart->ModelingViews()->WorkView();
    assocOrigin1.AssociatedPoint = point1;
    assocOrigin1.OffsetAnnotation = nullNXOpen_Annotations_Annotation;
    assocOrigin1.OffsetAlignmentPosition = NXOpen::Annotations::AlignmentPositionTopLeft;
    assocOrigin1.XOffsetFactor = 0.0;
    assocOrigin1.YOffsetFactor = 0.0;
    assocOrigin1.StackAlignmentPosition = NXOpen::Annotations::StackAlignmentPositionAbove;
    draftingNoteBuilder1->Origin()->SetAssociativeOrigin(assocOrigin1);
    
    
    /*draftingNoteBuilder1->Origin()->Origin()->SetValue(NULL, nullNXOpen_View, point2);*/
    draftingNoteBuilder1->Origin()->Origin()->SetValue(NULL, nullNXOpen_View, point2);
    
    draftingNoteBuilder1->Origin()->SetInferRelativeToGeometry(true);
    
    NXOpen::NXObject *nXObject1;
    nXObject1 = draftingNoteBuilder1->Commit();
    tag_t text = nXObject1->Tag();
    UF_OBJ_set_color(text,186);
   
    draftingNoteBuilder1->Destroy();

	//workPart->WCS()->SetCoordinateSystem(oldWcs);

    return text;

}

/*
static tag_t CreateText( char* textHeight,double kedu,Point3d coordinates22,Vector3d xDirection1, Vector3d yDirection1, int assotype )
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
    NXOpen::Part *workPart(theSession->Parts()->Work());

    NXOpen::Features::Text *nullNXOpen_Features_Text(NULL);
    
	int worklayer = -1;
	int layerStatus = -1;
    char textStr[133]="";
    sprintf_s(textStr,132,"%g",kedu);
	//UF_LAYER_ask_work_layer(&worklayer);
	//UF_LAYER_ask_status(255,&layerStatus);
	//UF_LAYER_set_status(255, UF_LAYER_WORK_LAYER);
    
    NXOpen::Features::TextBuilder *textBuilder1;
    textBuilder1 = workPart->Features()->CreateTextBuilder(nullNXOpen_Features_Text);
    
    double mtx[9], vx[3]={xDirection1.X,xDirection1.Y,xDirection1.Z},vy[3]={yDirection1.X,yDirection1.Y,yDirection1.Z};
	UF_MTX3_initialize(vx,vy,mtx);
	Matrix3x3 element(mtx[0],mtx[1],mtx[2],mtx[3],mtx[4],mtx[5],mtx[6],mtx[7],mtx[8]);

    NXOpen::Point3d origin1(0.0, 0.0, 0.0);
    NXOpen::Vector3d normal1(mtx[6],mtx[7],mtx[8]);
    NXOpen::Plane *plane1;
    plane1 = workPart->Planes()->CreatePlane(origin1, normal1, NXOpen::SmartObject::UpdateOptionWithinModeling);
    
    textBuilder1->SetSectionPlane(plane1);
    
    textBuilder1->SetScript(NXOpen::Features::TextBuilder::ScriptOptionsWestern);
    
    textBuilder1->SetCanUseKerningSpaces(false);
    if( 0 == assotype )
        textBuilder1->PlanarFrame()->SetAnchorLocation(NXOpen::GeometricUtilities::RectangularFrameBuilder::AnchorLocationTypeBottomLeft);
    else if( 1 == assotype )
        textBuilder1->PlanarFrame()->SetAnchorLocation(NXOpen::GeometricUtilities::RectangularFrameBuilder::AnchorLocationTypeTopLeft);
    else if( 2 == assotype )
        textBuilder1->PlanarFrame()->SetAnchorLocation(NXOpen::GeometricUtilities::RectangularFrameBuilder::AnchorLocationTypeTopRight);
    else if( 3 == assotype )
        textBuilder1->PlanarFrame()->SetAnchorLocation(NXOpen::GeometricUtilities::RectangularFrameBuilder::AnchorLocationTypeBottomRight);

    textBuilder1->PlanarFrame()->Height()->SetRightHandSide(textHeight);
    
    textBuilder1->PlanarFrame()->SetWScale(100);
    textBuilder1->PlanarFrame()->Shear()->SetRightHandSide("0");
    
    textBuilder1->SetCanProjectCurves(true);
    
    textBuilder1->SelectFont("Modern", NXOpen::Features::TextBuilder::ScriptOptionsOem);//Arial
    
    textBuilder1->SetTextString(textStr);

	NXOpen::CoordinateSystem *coordinateSystem1;

	CoordinateSystemCollection *csysCollectionPtr = workPart->CoordinateSystems();
	NXMatrixCollection *matrixCollection = workPart->NXMatrices();
	
	NXOpen::NXMatrix * orientation = matrixCollection->Create(element);
	
	coordinateSystem1 = csysCollectionPtr->CreateCoordinateSystem(coordinates22,orientation,true);

	textBuilder1->PlanarFrame()->SetCoordinateSystem(coordinateSystem1);
    
    textBuilder1->PlanarFrame()->UpdateOnCoordinateSystem();

    NXOpen::Point *point2;
    point2 = workPart->Points()->CreatePoint(coordinates22);
    
    NXOpen::Point3d point3(coordinates22.X, coordinates22.Y, coordinates22.Z);
    textBuilder1->PlanarFrame()->AnchorLocator()->SetValue(point2, workPart->ModelingViews()->WorkView(), point3);

    NXOpen::NXObject *nXObject1;
    nXObject1 = textBuilder1->Commit();

	tag_t texttag = nXObject1->Tag();

    textBuilder1->Destroy();
    
    plane1->DestroyPlane();

	return texttag;
}*/


void SetWCSToABS()
{
	NXOpen::Session *theSession = NXOpen::Session::GetSession();
	NXOpen::Part *workPart(theSession->Parts()->Work());
	NXOpen::Point3d origin1(0.0, 0.0, 0.0);
	NXOpen::Matrix3x3 matrix1;
	matrix1.Xx = 1.0;
	matrix1.Xy = 0.0;
	matrix1.Xz = 0.0;
	matrix1.Yx = 0.0;
	matrix1.Yy = 1.0;
	matrix1.Yz = 0.0;
	matrix1.Zx = 0.0;
	matrix1.Zy = 0.0;
	matrix1.Zz = 1.0;
	workPart->WCS()->SetOriginAndMatrix(origin1, matrix1);
}


//------------------------------����ר��------------------------//
/************************************************************************/
/*funtion name: Calculate_face_point_cys                                */
/*Description:  ��һ���������õ�һ��Z���뷨��ƽ�е�����ϵ             */
/*Input:        normal ����                                             */
/*Output:       csys   ����ϵ                                           */
/*Return:       0��1                                                    */
/************************************************************************/
static int create_csys_two_vecs(double vec1[3],double vec2[3],double dest_csys[6] )
{
	dest_csys[0] = vec1[0];
	dest_csys[1] = vec1[1];
	dest_csys[2] = vec1[2];
	dest_csys[3] = vec2[0];
	dest_csys[4] = vec2[1];
	dest_csys[5] = vec2[2];
	return 0;
}

extern int Calculate_face_point_cys(double normal[3], double csys[6])
{
	double vec_x[3] = {1,0,0};
	double vec_y[3] = {0,1,0};
	double vec_z[3] = {0,0,1};
	double tolerance = 0.0001;
	double temp_vec[3];
	int    isparallel;
	UF_VEC3_is_parallel(normal,vec_x,tolerance,&isparallel);
	if (isparallel)
	{
		UF_VEC3_cross(normal,vec_y,temp_vec);
		create_csys_two_vecs(vec_y,temp_vec,csys);
		return 0;

	}
	UF_VEC3_is_parallel(normal,vec_y,tolerance,&isparallel);
	if (isparallel)
	{
		UF_VEC3_cross(normal,vec_x,temp_vec);
		create_csys_two_vecs(vec_x,temp_vec,csys);
		return 0;

	}
	UF_VEC3_is_parallel(normal,vec_z,tolerance,&isparallel);
	if (isparallel)
	{
		UF_VEC3_cross(normal,vec_x,temp_vec);
		create_csys_two_vecs(vec_x,temp_vec,csys);
		return 0;

	}
	if ( normal[0]*normal[1]*normal[2] !=0.0 )//��ʸ��Ԫ�ض���Ϊ0
	{
		double mag;
		vec_x[0] = 1;
		vec_x[1] = 0;
		vec_x[2] = (-1)*normal[0]/normal[2];
		UF_VEC3_cross(normal,vec_x,temp_vec);
		UF_VEC3_unitize(vec_x,tolerance/100,&mag,vec_x);
		UF_VEC3_unitize(temp_vec,tolerance/100,&mag,temp_vec);
		create_csys_two_vecs(vec_x,temp_vec,csys);
		return 0;
	}
	else                                    //��ʸ��Ԫ��ֻ��һ��Ϊ0
	{
		double mag;
		if (normal[0] == 0.0)
		{
			UF_VEC3_cross(normal,vec_x,temp_vec);
			UF_VEC3_unitize(temp_vec,tolerance/100,&mag,temp_vec);
			create_csys_two_vecs(vec_x,temp_vec,csys);
			return 0;
		}
		if (normal[1] == 0.0)
		{
			UF_VEC3_cross(normal,vec_y,temp_vec);
			UF_VEC3_unitize(temp_vec,tolerance/100,&mag,temp_vec);
			create_csys_two_vecs(vec_y,temp_vec,csys);
			return 0;
		}
		if (normal[2] == 0.0)
		{
			UF_VEC3_cross(normal,vec_z,temp_vec);
			UF_VEC3_unitize(temp_vec,tolerance/100,&mag,temp_vec);
			create_csys_two_vecs(vec_z,temp_vec,csys);
			return 0;
		}
	}
	return 0;
}


/****************************************************************************************************/
/****************************************************************************************************/
extern int USER_SPLIT_string_by_sign(char *string,char *sign,char **outstrings,int *num)
{
	char *pstring=NULL;
	int j=0;

	pstring=strtok(string,sign);
	while(pstring)
	{
		outstrings[j]=pstring;
		pstring=strtok(NULL,sign);
		j++;
	}
	*num=j;
	return 0;
}

/*******************************************************************************************************
*******************************************************************************************************/
void USER_ROTATE_CURUE_INXY(tag_t *curve, double *rotate_angle)
{
	double rotate_origin[3] ={0, 0, 0};
	double rotate_dir[3] = {0, 0, 1};
	double mtx[16];
	int status1;
	int status2;
	int obj_num = 1;
	int move_flag = 1;
	int dest_layer = -1;
	int curve_off = 2;
	/*char msg[133];*/
	FTN(uf5945)(rotate_origin, rotate_dir, rotate_angle, mtx, &status1);
	//	sprintf(msg,"status1 is %d", status1);
	//	uc1601(msg, 1);

	FTN(uf5947)(mtx, curve, &obj_num, &move_flag, &dest_layer, &curve_off, NULL_TAG, NULL_TAG, &status2);
	//	sprintf(msg,"status2 is %d", status2);
	//	uc1601(msg, 1);
}

/************************************************************************/
/* SINO�ļ�����ȡ���  by wgw 2008.3.29                                                                   */
/************************************************************************/
extern int GetStampLetters(char *FullPath,int Type,char *StampName)
{
	char modstr[MAX_FSPEC_SIZE+1],prtstr[MAX_FSPEC_SIZE+1];
	char PartName[MAX_FSPEC_SIZE+1];
	char *p1,*p2;
	strcpy(PartName,FullPath);
	p2 = p1 = strstr(PartName,"\\3D\\");
	if (!p1)
	{
		p2 = p1 = strstr(PartName,"\\3d\\");
	}
	if (p1)
	{
		strcpy(prtstr,p1+4);
		p1 = strstr(prtstr,"-");
		if (!p1)
		{
			p1 = strstr(prtstr,"_");
			if (!p1)
			{
				p1 = strstr(prtstr,".prt");
			}

		}
		*p1 = '\0';
		*p2 = '\0';
		while ((*p2)!='\\')
		{
			p2--;
		}
		strcpy(modstr,p2+1);
		if (Type == 0)
		{
			strcpy(StampName,prtstr);
			return 0;
		}
		else if (Type == 1)
		{
			strcpy(StampName,modstr);
			strcat(StampName,"-");
			strcat(StampName,prtstr);
			return 0;
		}
		else 
			return 0;
	}
	return 1;

}
/************************************************************************/
/*funtion name: CreateStampStr                                          */
/*Description:  ����������е��ַ�ʵ��                                  */
/*Input:        str ����ֵ��ַ�  depth �ַ����   scale�����С        */
/*              spacedist  �ַ����    angle  �ַ���X����Ƕ�           */
/*              taper_angle  �ַ������ģ��    type ���������          */
/*Output:                                                               */
/*Return:       0��1                                                    */
/************************************************************************/
int CreateStampStr(char *str,double depth, double scale, double spacedist,double angle, double taper_angle,int type, bool bExtrude)
{
	char *p_env;
	char txt_path[133],txt_name[133],str_tem[1000],scale_factor[255];
	char taper[32];
	FILE *fp;
	int  i,k=0,l=0,length,step,list_count;
	double dep,point[3];
	double direction[3]={0.0,0.0,-1.0};
	uf_list_p_t spline_line_list,features;
	char str_depth[32];
	char *limits[2];
	tag_t feature_eid,target_body = NULL_TAG;
	tag_t tmp_body, tmp_feat;
	double offsetx;

	p_env=getenv("UGII_USER_DIR");
	sprintf(txt_path,"%s\\data",p_env);
	length = strlen(str);
	if (type == 0 && length>2)
	{
		int i;
		for (i=0;i<length-2;i++)
		{
			scale/=1.25;
		}
	}
	offsetx = -(length-1)*spacedist/2;
	for (i=0;i<length;i++)
	{
		char tem[32]="";
		int num_line;
		int num_spline;
		tag_t line[1200];
		tag_t spline[1200]; 

		tem[0]=str[i];
		if(str[i] == '*')   //�����ַ�(*��/)�Ĵ���
		{
			tem[0]='#';
		}
		if(str[i] == '/')
		{
			tem[0]='&';
		}
		sprintf(txt_name,"%s\\%s.txt",txt_path,tem);
		fp=fopen(txt_name,"r"); 
		if (fp==NULL)
		{
			uc1601("�ַ�����ȱ����Ӧ���ַ�",1);
			return 1;
		}

		do 
		{
			fgets(str_tem,1000,fp);

			if (str_tem[0]=='3')
			{
				int num,j;
				char *p[3];
				int num1[15];
				char *p1[5][15];
				UF_CURVE_line_t line_coords;

				USER_SPLIT_string_by_sign(str_tem,"/",p,&num);

				for (j=1;j<num;j++) 
				{
					USER_SPLIT_string_by_sign(p[j],",",p1[j],&num1[j]);
				}
				line_coords.start_point[0]=atof(p1[1][0])+i*spacedist+offsetx;
				line_coords.start_point[1]=atof(p1[1][1])-5;
				line_coords.start_point[2]=atof(p1[1][2]);
				line_coords.end_point[0]=atof(p1[2][0])+i*spacedist+offsetx;
				line_coords.end_point[1]=atof(p1[2][1])-5;
				line_coords.end_point[2]=atof(p1[2][2]);

				UF_CALL(UF_CURVE_create_line(&line_coords,&line[k]));
				USER_ROTATE_CURUE_INXY(&line[k], &angle);
				UF_CALL(UF_OBJ_set_layer(line[k],251));
				k++;
			}
			else if(str_tem[0]=='9')
			{ 
				int num,j,m,n;
				char *p[4];
				int num2[15];
				char *p2[5][16];
				UF_CURVE_spline_t spline_data; 

				int num_states; 
				UF_CURVE_state_p_t states;
				double tem_knots[133];
				double tem_poles[32][4];

				USER_SPLIT_string_by_sign(str_tem,"/",p,&num);

				for (j=1;j<num;j++) 
				{
					USER_SPLIT_string_by_sign(p[j],",",p2[j],&num2[j]);
				}
				spline_data.num_poles=atoi(p2[1][0]);
				spline_data.order=atoi(p2[1][1]);
				spline_data.is_rational=atoi(p2[1][2]);
				spline_data.start_param=atof(p2[1][3]);
				spline_data.end_param=atof(p2[1][4]);
				for (m=0;m<num2[2];m++)
				{
					tem_knots[m]=atof(p2[2][m]);
				}
				spline_data.knots=tem_knots;

				for (n=0;n<(num2[3]/4);n++)
				{  
					int r;
					for (r=2;r<4;r++)
					{
						tem_poles[n][r]=atof(p2[3][n*4+r]);
					}
					tem_poles[n][0]=atof(p2[3][n*4])+i*spacedist+offsetx;
					tem_poles[n][1]=atof(p2[3][n*4+1])-5;
				}
				spline_data.poles=tem_poles;

				UF_CALL(UF_CURVE_create_spline(&spline_data,&spline[l],&num_states,&states));
				USER_ROTATE_CURUE_INXY(&spline[l], &angle);
				UF_CALL(UF_OBJ_set_layer(spline[l],251));
				l++;
			}

			str_tem[0]=0;

		} while(!feof(fp));

		UF_MODL_create_list(&spline_line_list);
		for (num_line=0;num_line<k;num_line++)
		{
			UF_MODL_put_list_item(spline_line_list,line[num_line]);
		}
		for (num_spline=0;num_spline<l;num_spline++)
		{
			UF_MODL_put_list_item(spline_line_list,spline[num_spline]);
		}
		sprintf(scale_factor,"%f",(scale*3/10));
		dep=(depth+0.5)/(scale*3/10);
		sprintf(str_depth,"%f",dep);
		sprintf(taper,"%f",taper_angle);

		limits[0]="0.0";
		limits[1]=str_depth;

		//�Ƿ����쿪��
		if (bExtrude)
		{
			UF_MODL_create_extruded1(spline_line_list,taper,limits,point,direction,UF_NULLSIGN,target_body,&features);

			UF_MODL_ask_list_item(features, 0, &tmp_feat);
			UF_MODL_ask_feat_body(tmp_feat,&tmp_body);

			UF_CALL(UF_MODL_create_uniform_scale(tmp_body,UF_CSYS_WORK_COORDS,scale_factor,&feature_eid)) ;
			UF_OBJ_set_name(tmp_body,"carve_char");

			UF_MODL_ask_list_count(spline_line_list,&list_count);
			for(step = 0; step < list_count; step++)
			{
				UF_MODL_ask_list_item(spline_line_list, step, &tmp_feat);
				UF_OBJ_set_blank_status(tmp_feat, UF_OBJ_BLANKED);
			}

			UF_MODL_delete_list(&spline_line_list);
		}
		
		k=0;
		l=0;

	}//end for
	return 0;
}

// str ��������
//scale �����С
//depth �������
//style_flag �ַ��۸�ʽ
int TYText_Main(tag_t sel_face, double base_pt[3], char str[133], double scale, double depth, int style_flag, bool bExtrude)
{
	int length;
	char *p_env;
	double X = 3,Y = 6;//�߾�A��B
	double direction[3]={0.0,0.0,1.0};
	double direction2[3]={0.0,0.0,-1.0};

	char new_part[133];
	tag_t new_part_tag,display_part;
	UF_import_part_modes_t modes;
	double dest_csys[6]={1,0,0,0,1,0};
	double dest_point[3]={0,0,0};
	tag_t group;

	tag_t lineA,lineB;
	int  face_type;
	double face_point[3]; 
	double dir[3];
	double box[6];
	double radius; 
	double rad_data;
	int  norm_dir;
	tag_t body_obj_id;
	int num_result;
	tag_t * resulting_bodies;
	tag_t tool_tag = NULL_TAG;
	int n;
	double intersectpoint[3];
	UF_UNDO_mark_id_t mark_id;
	tag_t loc_face;
	double size,spacedist=10;
	int ret;

	length = strlen(str);
	scale/=3.0;
	if (sel_face == NULL_TAG)
		return -1;
	else
	{
		UF_MODL_ask_face_body (sel_face, &body_obj_id );
		//uc1601("point",1);
		UF_MODL_ask_face_data (sel_face,&face_type,face_point,dir,box,&radius,&rad_data,&norm_dir );
		Calculate_face_point_cys(dir, dest_csys);
		for(n = 0; n < 3; n++)
		{
			intersectpoint[n] = base_pt[n];
		}
	}


	p_env=getenv("UGII_USER_DIR");
	display_part=UF_PART_ask_display_part();
	sprintf(new_part,"%s\\application\\tem.prt",p_env);
	UF_PART_new(new_part,1,&new_part_tag);
	UF_PART_set_display_part(new_part_tag);

	if (style_flag==0)
	{
		size = 6;
		spacedist = 8;
		if (length > 2)
		{
			spacedist = 7;
		}
	}
	else if (style_flag==1)
	{
		size = (length-2)*3+2;
	}
	UF_CALL(CreateStampStr(str,depth,scale,spacedist,0,0,style_flag,false));

	UF_PART_save();

	UF_PART_set_display_part(display_part);

	//	UF_CURVE_create_point(intersectpoint,&test);

	modes.layer_mode=1;
	modes.group_mode=0;
	modes.csys_mode=0;
	modes.plist_mode=0;
	modes.view_mode=0;
	modes.cam_mode=false;
	modes.use_search_dirs=false;
	UF_CALL( UF_PART_import(new_part,&modes,dest_csys,intersectpoint,1.0,&group));

	if(bExtrude)
	{
		UF_OBJ_cycle_by_name("carve_char", &tool_tag);
		while (tool_tag != NULL_TAG)
		{
			UF_MODL_subtract_bodies (body_obj_id, tool_tag, &num_result, &resulting_bodies ); 
			UF_OBJ_cycle_by_name("carve_char", &tool_tag);
		}
	}
	

	UF_PART_close(new_part_tag,0,1);
	uc4561(new_part,2);
	sel_face = NULL_TAG;

    return 0;
}





/*-----------------------------------------------�����-------------------------*/
/************************************************************************/
/*funtion name: CreateStampStr                                          */
/*Description:  ����������е��ַ�ʵ��                                  */
/*Input:        str ����ֵ��ַ�  depth �ַ����   scale�����С        */
/*              spacedist  �ַ����    angle  �ַ���X����Ƕ�           */
/*              taper_angle  �ַ������ģ��        */
/*Output:                                                               */
/*Return:       0��1                                                    */
/************************************************************************/
static int CreateStampStr2(char *str, double spacedist)
{
	double angle = 0;
	double taper_angle = 0;
	char *p_env = 0;
	char txt_path[133],txt_name[133],str_tem[1000],scale_factor[255];
	char taper[32];
	FILE *fp;
	int  i,k=0,l=0,length,step,list_count;
	double dep,point[3];
	double direction[3]={0.0,0.0,-1.0};
	uf_list_p_t spline_line_list,features;
	tag_t feature_eid,target_body = NULL_TAG;
	tag_t tmp_body, tmp_feat;
	double offsetx;

	p_env=getenv("UGII_USER_DIR");
	sprintf(txt_path,"%s\\data",p_env);
	length = strlen(str);

	offsetx = -(length-1)*spacedist/2;
	for (i=0;i<length;i++)
	{
		char tem[32]="";
		int num_line;
		int num_spline;
		tag_t line[1200];
		tag_t spline[1200]; 

		tem[0]=str[i];
		if(str[i] == '*')   //�����ַ�(*��/)�Ĵ���
		{
			tem[0]='#';
		}
		if(str[i] == '/')
		{
			tem[0]='&';
		}
		sprintf(txt_name,"%s\\%s.txt",txt_path,tem);
		fp=fopen(txt_name,"r"); 
		if (fp==NULL)
		{
			uc1601("�ַ�����ȱ����Ӧ���ַ�",1);
			return 1;
		}

		do 
		{
			fgets(str_tem,1000,fp);

			if (str_tem[0]=='3')
			{
				int num,j;
				char *p[3];
				int num1[15];
				char *p1[5][15];
				UF_CURVE_line_t line_coords;

				USER_SPLIT_string_by_sign(str_tem,"/",p,&num);

				for (j=1;j<num;j++) 
				{
					USER_SPLIT_string_by_sign(p[j],",",p1[j],&num1[j]);
				}
				line_coords.start_point[0]=atof(p1[1][0])+i*spacedist+offsetx;
				line_coords.start_point[1]=atof(p1[1][1])-5;
				line_coords.start_point[2]=atof(p1[1][2]);
				line_coords.end_point[0]=atof(p1[2][0])+i*spacedist+offsetx;
				line_coords.end_point[1]=atof(p1[2][1])-5;
				line_coords.end_point[2]=atof(p1[2][2]);

				UF_CALL(UF_CURVE_create_line(&line_coords,&line[k]));
				USER_ROTATE_CURUE_INXY(&line[k], &angle);
				UF_CALL(UF_OBJ_set_layer(line[k],251));
				k++;
			}
			else if(str_tem[0]=='9')
			{ 
				int num,j,m,n;
				char *p[4];
				int num2[15];
				char *p2[5][16];
				UF_CURVE_spline_t spline_data; 

				int num_states; 
				UF_CURVE_state_p_t states;
				double tem_knots[133];
				double tem_poles[32][4];

				USER_SPLIT_string_by_sign(str_tem,"/",p,&num);

				for (j=1;j<num;j++) 
				{
					USER_SPLIT_string_by_sign(p[j],",",p2[j],&num2[j]);
				}
				spline_data.num_poles=atoi(p2[1][0]);
				spline_data.order=atoi(p2[1][1]);
				spline_data.is_rational=atoi(p2[1][2]);
				spline_data.start_param=atof(p2[1][3]);
				spline_data.end_param=atof(p2[1][4]);
				for (m=0;m<num2[2];m++)
				{
					tem_knots[m]=atof(p2[2][m]);
				}
				spline_data.knots=tem_knots;

				for (n=0;n<(num2[3]/4);n++)
				{  
					int r;
					for (r=2;r<4;r++)
					{
						tem_poles[n][r]=atof(p2[3][n*4+r]);
					}
					tem_poles[n][0]=atof(p2[3][n*4])+i*spacedist+offsetx;
					tem_poles[n][1]=atof(p2[3][n*4+1])-5;
				}
				spline_data.poles=tem_poles;

				UF_CALL(UF_CURVE_create_spline(&spline_data,&spline[l],&num_states,&states));
				USER_ROTATE_CURUE_INXY(&spline[l], &angle);
				UF_CALL(UF_OBJ_set_layer(spline[l],251));
				l++;
			}

			str_tem[0]=0;

		} while(!feof(fp));

		UF_MODL_create_list(&spline_line_list);
		for (num_line=0;num_line<k;num_line++)
		{
			UF_MODL_put_list_item(spline_line_list,line[num_line]);
		}
		for (num_spline=0;num_spline<l;num_spline++)
		{
			UF_MODL_put_list_item(spline_line_list,spline[num_spline]);
		}

		k=0;
		l=0;

	}//end for
	return 0;
}

// str ��������
//scale �����С
//depth �������
//style_flag �ַ��۸�ʽ   TYText_Main(faces[0], base_pt, "ABC-123.6", 1, 1, 1,false);
int TYText_Main2_ForBaiKeXian(char str[133], double base_pt[3], double dest_csys[6],double height)
{
	char new_part_name[133] = "\0";
	tag_t new_part_tag = 0,display_part = 0;
	UF_import_part_modes_t modes;
	tag_t group;
	
	int ret = 0;
	double size,spacedist=10;
	int length = strlen(str);

	char *p_env=getenv("UGII_USER_DIR");
	display_part=UF_PART_ask_display_part();
	sprintf(new_part_name,"%s\\application\\tem.prt",p_env);
	UF_PART_new(new_part_name,1,&new_part_tag);
	UF_PART_set_display_part(new_part_tag);

	size = (length-2)*3+2;
	UF_CALL(CreateStampStr2(str,spacedist));

	UF_PART_save();

	UF_PART_set_display_part(display_part);

	modes.layer_mode=1;
	modes.group_mode=0;
	modes.csys_mode=0;
	modes.plist_mode=0;
	modes.view_mode=0;
	modes.cam_mode=false;
	modes.use_search_dirs=false;

	//Ĭ�ϸ߶���10.0 
	UF_CALL( UF_PART_import(new_part_name,&modes,dest_csys,base_pt,height/10.0,&group));


	UF_PART_close(new_part_tag,0,1);
	uc4561(new_part_name,2);

	return 0;
}