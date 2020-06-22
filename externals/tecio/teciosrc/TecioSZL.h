 #pragma once
 #if defined _WIN32
 #if !defined MSWIN
 #define MSWIN 
 #endif
 #endif 
#include "ThirdPartyHeadersBegin.h"
#include <string>
#include "ThirdPartyHeadersEnd.h"
 #if defined TECIOMPI
#include "mpi.h"
 #endif
#include "StandardIntegralTypes.h"
namespace tecplot { namespace tecioszl { std::string const HEADER_FILE_SUFFIX        = ".szhdr"; std::string const ZONE_DATA_FILE_SUFFIX     = ".szdat"; std::string const TEXT_FILE_SUFFIX          = ".sztxt"; std::string const GEOMETRY_FILE_SUFFIX      = ".szgeo"; std::string const AUX_DATA_FILE_SUFFIX      = ".szaux"; std::string const CUSTOM_LABELS_FILE_SUFFIX = ".szlab"; int32_t tecFileWriterOpen_SZL( char const* ___1394, char const* dataSetTitle, char const* variableList, int32_t     ___1407, int32_t     defaultVarType, void*       gridFileHandle, void**      fileHandle); int32_t tecFileSetDiagnosticsLevel_SZL( void*   fileHandle, int32_t level);
 #if defined TECIOMPI
int32_t tecMPIInitialize_SZL( void*    fileHandle, MPI_Comm communicator, int32_t  mainRank);
 #endif
int32_t tecZoneCreateIJK_SZL( void*          fileHandle, char const*    ___4690, int64_t        imax, int64_t        jmax, int64_t        kmax, int32_t const* varTypes, int32_t const* ___3551, int32_t const* valueLocations, int32_t const* ___2982, int32_t        shareFaceNeighborsFromZone, int64_t        ___2802, int32_t        ___1284, int32_t*       zone); int32_t tecZoneCreateFE_SZL( void*          fileHandle, char const*    ___4690, int32_t        ___4692, int64_t        ___2821, int64_t        ___2781, int32_t const* varTypes, int32_t const* ___3551, int32_t const* valueLocations, int32_t const* ___2982, int32_t        ___3549, int64_t        ___2802, int32_t        ___1284, int32_t*       zone); int32_t tecZoneCreatePoly_SZL( void*          fileHandle, char const*    ___4690, int32_t        ___4692, int64_t        ___2821, int64_t        numFaces, int64_t        ___2781, int64_t        ___4192, int32_t const* varTypes, int32_t const* ___3551, int32_t const* valueLocations, int32_t const* ___2982, int32_t        ___3549, int64_t        ___2786, int64_t        ___4188, int32_t*       zone); int32_t tecZoneSetUnsteadyOptions_SZL( void*   fileHandle, int32_t zone, double  ___3640, int32_t ___3785); int32_t tecZoneSetParentZone_SZL( void*   fileHandle, int32_t zone, int32_t ___2974);
 #if defined TECIOMPI
int32_t tecZoneMapPartitionsToMPIRanks_SZL( void*          fileHandle, int32_t&       zone, int32_t        numPartitions, int32_t const* mpiRanksForPartitions);
 #endif
int32_t tecFEPartitionCreate32_SZL( void*          fileHandle, int32_t        zone, int32_t        ___2977, int64_t        ___2821, int64_t        ___2781, int64_t        numGhostNodes, int32_t const* ghostNodes, int32_t const* neighborPartitions, int32_t const* neighborPartitionNodes, int64_t        numGhostCells, int32_t const* ghostCells); int32_t tecFEPartitionCreate64_SZL( void*          fileHandle, int32_t        zone, int32_t        ___2977, int64_t        ___2821, int64_t        ___2781, int64_t        numGhostNodes, int64_t const* ghostNodes, int32_t const* neighborPartitions, int64_t const* neighborPartitionNodes, int64_t        numGhostCells, int64_t const* ghostCells); int32_t tecIJKPartitionCreate_SZL( void*   fileHandle, int32_t zone, int32_t ___2977, int64_t imin, int64_t jmin, int64_t kmin, int64_t imax, int64_t jmax, int64_t kmax); int32_t tecZoneVarWriteDoubleValues_SZL( void*         fileHandle, int32_t       zone, int32_t       ___4336, int32_t       ___2977, int64_t       count, double const* values); int32_t tecZoneVarWriteFloatValues_SZL( void*        fileHandle, int32_t      zone, int32_t      ___4336, int32_t      ___2977, int64_t      count, float const* values); int32_t tecZoneVarWriteInt32Values_SZL( void*          fileHandle, int32_t        zone, int32_t        ___4336, int32_t        ___2977, int64_t        count, int32_t const* values); int32_t tecZoneVarWriteInt16Values_SZL( void*          fileHandle, int32_t        zone, int32_t        ___4336, int32_t        ___2977, int64_t        count, int16_t const* values); int32_t tecZoneVarWriteUInt8Values_SZL( void*          fileHandle, int32_t        zone, int32_t        ___4336, int32_t        ___2977, int64_t        count, uint8_t const* values); int32_t tecZoneNodeMapWrite32_SZL( void*          fileHandle, int32_t        zone, int32_t        ___2977, int32_t        nodesAreOneBased, int64_t        count, int32_t const* nodes); int32_t tecZoneNodeMapWrite64_SZL( void*          fileHandle, int32_t        zone, int32_t        ___2977, int32_t        nodesAreOneBased, int64_t        count, int64_t const* nodes); int32_t tecZoneFaceNbrWriteConnections32_SZL( void*          fileHandle, int32_t        zone, int32_t const* faceNeighbors); int32_t tecZoneFaceNbrWriteConnections64_SZL( void*          fileHandle, int32_t        zone, int64_t const* faceNeighbors); int32_t tecZoneWritePolyFaces32_SZL( void*          fileHandle, int32_t        zone, int32_t        ___2977, int32_t        numFaces, int32_t const* faceNodeCounts, int32_t const* ___1296, int32_t const* faceLeftElems, int32_t const* faceRightElems, int32_t        isOneBased); int32_t tecZoneWritePolyFaces64_SZL( void*          fileHandle, int32_t        zone, int32_t        ___2977, int64_t        numFaces, int32_t const* faceNodeCounts, int64_t const* ___1296, int64_t const* faceLeftElems, int64_t const* faceRightElems, int32_t        isOneBased); int32_t tecZoneWritePolyBoundaryConnections32_SZL( void*          fileHandle, int32_t        zone, int32_t        ___2977, int32_t        numBoundaryFaces, int32_t const* faceBoundaryConnectionCounts, int32_t const* faceBoundaryConnectionElems, int32_t const* faceBoundaryConnectionZones, int32_t        isOneBased); int32_t tecZoneWritePolyBoundaryConnections64_SZL( void*          fileHandle, int32_t        zone, int32_t        ___2977, int64_t        numBoundaryFaces, int32_t const* faceBoundaryConnectionCounts, int64_t const* faceBoundaryConnectionElems, int32_t const* faceBoundaryConnectionZones, int32_t        isOneBased); int32_t tecDataSetAddAuxData_SZL( void*       fileHandle, char const* ___2685, char const* ___4314); int32_t tecVarAddAuxData_SZL( void*       fileHandle, int32_t     ___4336, char const* ___2685, char const* ___4314); int32_t tecZoneAddAuxData_SZL( void*       fileHandle, int32_t     zone, char const* ___2685, char const* ___4314); int32_t tecGeom2DLineSegmentsBegin_SZL( void*          fileHandle, double         xOrigin, double         yOrigin, int32_t        numPoints, double const*  relativeX, double const*  relativeY, int32_t        ___3159); int32_t tecGeom2DMultiLineSegmentsBegin_SZL( void*          fileHandle, double         xOrigin, double         yOrigin, int32_t        ___2835, int32_t const* numSegmentPoints, double const*  relativeX, double const*  relativeY, int32_t        ___3159); int32_t tecGeom3DLineSegmentsBegin_SZL( void*          fileHandle, double         xOrigin, double         yOrigin, double         zOrigin, int32_t        numPoints, double const*  relativeX, double const*  relativeY, double const*  relativeZ); int32_t tecGeom3DMultiLineSegmentsBegin_SZL( void*          fileHandle, double         xOrigin, double         yOrigin, double         zOrigin, int32_t        ___2835, int32_t const* numSegmentPoints, double const*  relativeX, double const*  relativeY, double const*  relativeZ); int32_t tecGeomCircleBegin_SZL( void*   fileHandle, double  xCenter, double  yCenter, double  radius,
int32_t ___3159); int32_t tecGeomEllipseBegin_SZL( void*   fileHandle, double  xCenter, double  yCenter, double  ___4458, double  ___1826, int32_t ___3159); int32_t tecGeomRectangleBegin_SZL( void*   fileHandle, double  xMin, double  yMin, double  xMax, double  yMax, int32_t ___3159); int32_t tecGeomSquareBegin_SZL( void*   fileHandle, double  xMin, double  yMin, double  size, int32_t ___3159); int32_t tecGeomArrowheadSetInfo_SZL( void*   fileHandle, double  ___56, int32_t attachment, double  size, int32_t style); int32_t tecGeomEllipseSetNumPoints_SZL( void*   fileHandle, int32_t numEllipsePoints); int32_t tecGeomSetClipping_SZL( void*   fileHandle, int32_t ___495); int32_t tecGeomSetLineInfo_SZL( void*   fileHandle, int32_t ___2263, double  ___2986, double  thickness, int32_t color); int32_t tecGeomSetMacroFunctionCmd_SZL( void*       fileHandle, char const* macroFunctionCmd); int32_t tecGeomSetScope_SZL( void*   fileHandle, int32_t ___3442); int32_t tecGeomAttachToZone_SZL( void*   fileHandle, int32_t zone); int32_t tecGeomFill_SZL( void*   fileHandle, int32_t ___1411); int32_t tecGeomEnd_SZL( void* fileHandle); int32_t tecCustomLabelsAddSet_SZL( void*       fileHandle, char const* ___2173); int32_t tecText2DBegin_SZL( void*       fileHandle, char const* string, double      x, double      ___4583, int32_t     ___3159, double      ___1826, int32_t     sizeUnits); int32_t tecText3DBegin_SZL( void*       fileHandle, char const* string, double      x, double      ___4583, double      z, double      ___1826, int32_t     sizeUnits); int32_t tecTextAttachToZone_SZL( void*   fileHandle, int32_t zone); int32_t tecTextBoxSetInfo_SZL( void*   fileHandle, int32_t ___410, int32_t lineColor, int32_t ___1411, double  ___2289, double  margin); int32_t tecTextSetAnchor_SZL( void*   fileHandle, int32_t ___38); int32_t tecTextSetAngle_SZL( void*  fileHandle, double ___56); int32_t tecTextSetClipping_SZL( void*   fileHandle, int32_t ___495); int32_t tecTextSetColor_SZL( void*   fileHandle, int32_t color); int32_t tecTextSetTypeface_SZL( void*       fileHandle, char const* family, int32_t     isBold, int32_t     isItalic); int32_t tecTextSetLineSpacing_SZL( void*  fileHandle, double ___2287); int32_t tecTextSetMacroFunctionCmd_SZL( void*       fileHandle, char const* macroFunctionCmd); int32_t tecTextSetScope_SZL( void*   fileHandle, int32_t ___3442); int32_t tecTextEnd_SZL( void* fileHandle); int32_t tecUserRecAdd_SZL( void*       fileHandle, char const* userRec); int32_t tecFileWriterFlush_SZL( void*          fileHandle, int32_t        numZonesToRetain, int32_t const* zonesToRetain); int32_t tecFileWriterClose_SZL( void** fileHandle); int32_t ___4004(int32_t  ___1397); int32_t ___4003(int32_t  ___1397); int32_t ___3999( int32_t          ___1397, char const*      ___4177, char const*      ___4350, char const*      ___1394, char const*      ___3447, int32_t  const*, int32_t  const*  ___941, int32_t  const*  ___2013); int32_t ___4014( int32_t         ___1397, char const*     ___4691, int32_t  const* ___4693, int32_t  const* ___1910, int32_t  const* ___2117, int32_t  const* ___2162, int32_t  const* ___1836, int32_t  const* ___2109, int32_t  const* ___2138, double const*   ___3641, int32_t  const* ___3786, int32_t  const* ___2975, int32_t  const* ___2006, int32_t  const* ___2803, int32_t  const* ___1285, int32_t  const* ___4193, int32_t  const* ___2787, int32_t  const* ___4189, int32_t  const* ___2983, int32_t  const* ___4327, int32_t  const* ___3552, int32_t  const* ___3550); int32_t ___3994( int32_t         ___1397, int32_t  const* N, void const*     ___1352, int32_t  const* ___2014); int32_t ___4001( int32_t         ___1397, int32_t  const* ___2689); int32_t ___4002( int32_t         ___1397, int32_t  const* N, int32_t  const* ___2689); int32_t TECIOSZL_FLUSH( int32_t        fileNum, int32_t const* numZonesToRetain, int32_t const* zonesToRetain); int32_t ___3995(int32_t  ___1397); int32_t ___4000( int32_t     ___1397, char const* S); int32_t ___4011( int32_t     ___1397, char const* S); int32_t ___3998( int32_t         ___1397, double const*   ___4576, double const*   ___4593, double const*   ___4716, int32_t  const* ___3160, int32_t  const* ___227, int32_t  const* ___4600, int32_t  const* Color, int32_t  const* ___1412, int32_t  const* ___2023, int32_t  const* ___1652, int32_t  const* ___2264, double const*   ___2987, double const*   ___2290, int32_t  const* ___2794, int32_t  const* ___188, int32_t  const* ___176, double const*   ___187, double const*   ___171, int32_t  const* ___3443, int32_t  const* ___496, int32_t  const* ___2836, int32_t  const* ___2838, float const*    ___4570, float const*    ___4588, float const*    ___4597,
char const*     mfc); int32_t ___4010( int32_t         ___1397, double const*   ___4575, double const*   ___4592, double const*   ___4714, int32_t  const* ___3160, int32_t  const* ___227, int32_t  const* ___4600, int32_t  const* ___353, int32_t  const* ___1453, double const*   ___1451, int32_t  const* ___411, double const*   ___409, double const*   ___407, int32_t  const* ___403, int32_t  const* ___405, double const*   ___57, int32_t  const* ___39, double const*   ___2288, int32_t  const* ___4081, int32_t  const* ___3443, int32_t  const* ___496, char const*     ___3813, char const*     mfc); void ___3997( int32_t         ___1397, int32_t  const* ___2891); int32_t ___3993( int32_t     ___1397, char const* ___2686, char const* ___4315); int32_t ___4013( int32_t     ___1397, char const* ___2686, char const* ___4315); int32_t ___4012( int32_t         ___1397, int32_t  const* ___4337, char const*     ___2686, char const*     ___4315); int32_t ___3996( int32_t         ___1397, int32_t  const* ___1258); int32_t ___4008(int32_t  ___1397); int32_t ___4009(int32_t  ___1397); int32_t ___4005( int32_t         ___1397, int32_t  const* ___1294, int32_t  const* ___1297, int32_t  const* ___1259, int32_t  const* ___1303, int32_t  const* ___1253, int32_t  const* ___1254, int32_t  const* ___1256); int32_t ___4007( int32_t         ___1397, int32_t  const* ___2806, int32_t  const* ___1294, int32_t  const* ___1297, int32_t  const* ___1259, int32_t  const* ___1303); int32_t ___4006( int32_t         ___1397, int32_t  const* ___2778, int32_t  const* ___1253, int32_t  const* ___1254, int32_t  const* ___1256);
 #if defined TECIOMPI
int32_t TECIOSZL_MPIINIT( int32_t *       fileNum, void*           communicator, int32_t  const* mainrank); int32_t TECIOSZL_ZNEMAP( int32_t         fileNum, int32_t  const* npartitions, int32_t  const* ptnworkers);
 #endif
int32_t TECIOSZL_FEPTN( int32_t         fileNum, int32_t  const* ___2977, int32_t  const* numnodes, int32_t  const* numcells, int32_t  const* ngnodes, int32_t  const* gnodes, int32_t  const* gnpartitions, int32_t  const* gnpnodes, int32_t  const* ngcells, int32_t  const* gcells); int32_t TECIOSZL_IJKPTN( int32_t         fileNum, int32_t  const* ___2977, int32_t  const* imin, int32_t  const* jmin, int32_t  const* kmin, int32_t  const* imax, int32_t  const* jmax, int32_t  const* kmax); int32_t tecioszl_convertrawdata(char const* ___1394); int32_t convertIntermediateFilesToSZLFile( void*              fileHandle, std::string const& intermediateFileBaseName, bool               cleanup, std::string const& szpltFileName, char const*        routineName); enum TecioSZLFileOpenResult_e { TecioSZLFileOpenResult_OK = 0, TecioSZLFileOpenResult_ErrorOpeningFile, TecioSZLFileOpenResult_BadFormat, TecioSZLFileOpenResult_OutOfMemory, END_TecioSZLFileOpenResult_e, TecioSZLFileOpenResult_INVALID }; int32_t tecioSZL_CustomLabelsGetNumSets(void* fileHandle, int32_t * numSets); int32_t tecioSZL_CustomLabelsGetSet(void* fileHandle, int32_t  ___4453, char** labelSet); int32_t tecioSZL_DataSetAuxDataGetItem(void* fileHandle, int32_t  whichItem, char** ___2685, char** ___4314); int32_t tecioSZL_DataSetAuxDataGetNumItems(void* fileHandle, int32_t * ___2812); int32_t tecioSZL_DataSetGetNumVars(void* fileHandle, int32_t * ___2843); int32_t tecioSZL_DataSetGetNumZones(void* fileHandle, int32_t * ___2846); int32_t tecioSZL_DataSetGetTitle(void* fileHandle, char** ___4177); int32_t tecioSZL_FileGetType(void* fileHandle, int32_t * ___1407); int32_t tecioSZL_FileReaderClose(void** fileHandle); TecioSZLFileOpenResult_e tecioSZL_FileReaderOpen(char const* ___1394, void** fileHandle); int32_t tecioSZL_GeomArrowheadGetAngle(void* fileHandle, int32_t  ___1555, double* ___56); int32_t tecioSZL_GeomArrowheadGetAttach(void* fileHandle, int32_t  ___1555, int32_t * attachment); int32_t tecioSZL_GeomArrowheadGetSize(void* fileHandle, int32_t  ___1555, double* arrowheadSize); int32_t tecioSZL_GeomArrowheadGetStyle(void* fileHandle, int32_t  ___1555, int32_t * arrowheadStyle); int32_t tecioSZL_GeomCircleGetRadius(void* fileHandle, int32_t  ___1555, double* radius); int32_t tecioSZL_GeomEllipseGetNumPoints(void* fileHandle, int32_t  ___1555, int32_t * numEllipsePoints); int32_t tecioSZL_GeomEllipseGetSize(void* fileHandle, int32_t  ___1555, double* horizontalAxis, double* verticalAxis); int32_t tecioSZL_GeomGetAnchorPos(void* fileHandle, int32_t  ___1555, double* x, double* ___4583, double* z); int32_t tecioSZL_GeomGetClipping(void* fileHandle, int32_t  ___1555, int32_t * ___495); int32_t tecioSZL_GeomGetColor(void* fileHandle, int32_t  ___1555, int32_t * color); int32_t tecioSZL_GeomGetCoordMode(void* fileHandle, int32_t  ___1555, int32_t * coordMode); int32_t tecioSZL_GeomGetFillColor(void* fileHandle, int32_t  ___1555, int32_t * ___1411); int32_t tecioSZL_GeomGetLinePattern(void* fileHandle, int32_t  ___1555, int32_t * ___2263); int32_t tecioSZL_GeomGetLineThickness(void* fileHandle, int32_t  ___1555, double* ___2289); int32_t tecioSZL_GeomGetMacroFunctionCmd(void* fileHandle, int32_t  ___1555, char** macroFunctionCmd); int32_t tecioSZL_GeomGetNumGeoms(void* fileHandle, int32_t * numGeoms); int32_t tecioSZL_GeomGetPatternLength(void* fileHandle, int32_t  ___1555, double* ___2986); int32_t tecioSZL_GeomGetScope(void* fileHandle, int32_t  ___1555, int32_t * ___3442); int32_t tecioSZL_GeomGetType(void* fileHandle, int32_t  ___1555, int32_t * type); int32_t tecioSZL_GeomGetZone(void* fileHandle, int32_t  ___1555, int32_t * zone); int32_t tecioSZL_GeomIsAttached(void* fileHandle, int32_t  ___1555, int32_t * ___2004); int32_t tecioSZL_GeomIsFilled(void* fileHandle, int32_t  ___1555, int32_t * ___2022); int32_t tecioSZL_GeomLineGetPoint(void* fileHandle, int32_t  ___1555, int32_t  segment, int32_t  index, double* x, double* ___4583, double* z); int32_t tecioSZL_GeomLineGetSegmentCount(void* fileHandle, int32_t  ___1555, int32_t * segmentCount); int32_t tecioSZL_GeomLineSegmentGetPointCount(void* fileHandle, int32_t  ___1555, int32_t  segment, int32_t * pointCount); int32_t tecioSZL_GeomRectangleGetSize(void* fileHandle, int32_t  ___1555, double* ___4458, double* ___1826); int32_t tecioSZL_GeomSquareGetSize(void* fileHandle, int32_t  ___1555, double* size); int32_t tecioSZL_TextBoxGetColor(void* fileHandle, int32_t  ___4042, int32_t * ___402); int32_t tecioSZL_TextBoxGetFillColor(void* fileHandle, int32_t  ___4042, int32_t * ___404); int32_t tecioSZL_TextBoxGetLineThickness(void* fileHandle, int32_t  ___4042, double* ___406); int32_t tecioSZL_TextBoxGetMargin(void* fileHandle, int32_t  ___4042, double* ___408); int32_t tecioSZL_TextBoxGetType(void* fileHandle, int32_t  ___4042, int32_t * ___410); int32_t tecioSZL_TextGetAnchor(void* fileHandle, int32_t  ___4042, int32_t * ___38); int32_t tecioSZL_TextGetAnchorPos(void* fileHandle, int32_t  ___4042, double* x, double* ___4583, double* z); int32_t tecioSZL_TextGetAngle(void* fileHandle, int32_t  ___4042, double* ___56);
int32_t tecioSZL_TextGetClipping(void* fileHandle, int32_t  ___4042, int32_t * ___495); int32_t tecioSZL_TextGetColor(void* fileHandle, int32_t  ___4042, int32_t * color); int32_t tecioSZL_TextGetCoordMode(void* fileHandle, int32_t  ___4042, int32_t * coordMode); int32_t tecioSZL_TextGetHeight(void* fileHandle, int32_t  ___4042, double* ___1826); int32_t tecioSZL_TextGetLineSpacing(void* fileHandle, int32_t  ___4042, double* ___2287); int32_t tecioSZL_TextGetMacroFunctionCmd(void* fileHandle, int32_t  ___4042, char** macroFunctionCmd); int32_t tecioSZL_TextGetNumTexts(void* fileHandle, int32_t * numTexts); int32_t tecioSZL_TextGetScope(void* fileHandle, int32_t  ___4042, int32_t * ___3442); int32_t tecioSZL_TextGetSizeUnits(void* fileHandle, int32_t  ___4042, int32_t * sizeUnits); int32_t tecioSZL_TextGetString(void* fileHandle, int32_t  ___4042, char** string); int32_t tecioSZL_TextGetTypeface(void* fileHandle, int32_t  ___4042, char** typeface); int32_t tecioSZL_TextGetZone(void* fileHandle, int32_t  ___4042, int32_t * zone); int32_t tecioSZL_TextIsAttached(void* fileHandle, int32_t  ___4042, int32_t * ___2004); int32_t tecioSZL_TextIsBold(void* fileHandle, int32_t  ___4042, int32_t * isBold); int32_t tecioSZL_TextIsItalic(void* fileHandle, int32_t  ___4042, int32_t * isItalic); int32_t tecioSZL_VarAuxDataGetItem(void* fileHandle, int32_t  ___4336, int32_t  whichItem, char** ___2685, char** ___4314); int32_t tecioSZL_VarAuxDataGetNumItems(void* fileHandle, int32_t  ___4336, int32_t * ___2812); int32_t tecioSZL_VarGetName(void* fileHandle, int32_t  ___4336, char** ___2685); int32_t tecioSZL_VarIsEnabled(void* fileHandle, int32_t  ___4336, int32_t * isEnabled); int32_t tecioSZL_ZoneAuxDataGetItem(void* fileHandle, int32_t  zone, int32_t  whichItem, char** ___2685, char** ___4314); int32_t tecioSZL_ZoneAuxDataGetNumItems(void* fileHandle, int32_t  zone, int32_t * ___2812); int32_t tecioSZL_ZoneConnectivityGetSharedZone(void* fileHandle, int32_t  zone, int32_t * sharedZone); int32_t tecioSZL_ZoneFaceNbrGetConnections(void* fileHandle, int32_t  zone, int32_t * connections); int32_t tecioSZL_ZoneFaceNbrGetConnections64(void* fileHandle, int32_t  zone, int64_t* connections); int32_t tecioSZL_ZoneFaceNbrGetMode(void* fileHandle, int32_t  zone, int32_t * ___2504); int32_t tecioSZL_ZoneFaceNbrGetNumConnections(void* fileHandle, int32_t  zone, int64_t* numConnections); int32_t tecioSZL_ZoneFaceNbrGetNumValues(void* fileHandle, int32_t  zone, int64_t* numValues); int32_t tecioSZL_ZoneFaceNbrsAre64Bit(void* fileHandle, int32_t  zone, int32_t * are64Bit); int32_t tecioSZL_ZoneGetIJK(void* fileHandle, int32_t  zone, int64_t* iMax, int64_t* jMax, int64_t* kMax); int32_t tecioSZL_ZoneGetParentZone(void* fileHandle, int32_t  zone, int32_t * ___2974); int32_t tecioSZL_ZoneGetSolutionTime(void* fileHandle, int32_t  zone, double* ___3640); int32_t tecioSZL_ZoneGetStrandID(void* fileHandle, int32_t  zone, int32_t * ___3785); int32_t tecioSZL_ZoneGetTitle(void* fileHandle, int32_t  zone, char** ___4177); int32_t tecioSZL_ZoneGetType(void* fileHandle, int32_t  zone, int32_t * type); int32_t tecioSZL_ZoneIsEnabled(void* fileHandle, int32_t  zone, int32_t * isEnabled); int32_t tecioSZL_ZoneNodeMapGet(void* fileHandle, int32_t  zone, int64_t startCell, int64_t ___2781, int32_t * ___2723); int32_t tecioSZL_ZoneNodeMapGet64(void* fileHandle, int32_t  zone, int64_t startCell, int64_t ___2781, int64_t* ___2723); int32_t tecioSZL_ZoneNodeMapIs64Bit(void* fileHandle, int32_t  zone, int32_t * is64Bit); int32_t tecioSZL_ZoneVarGetDoubleValues(void* fileHandle, int32_t  zone, int32_t  ___4336, int64_t startIndex, int64_t numValues, double* values); int32_t tecioSZL_ZoneVarGetFloatValues(void* fileHandle, int32_t  zone, int32_t  ___4336, int64_t startIndex, int64_t numValues, float* values); int32_t tecioSZL_ZoneVarGetInt16Values(void* fileHandle, int32_t  zone, int32_t  ___4336, int64_t startIndex, int64_t numValues, int16_t* values); int32_t tecioSZL_ZoneVarGetInt32Values(void* fileHandle, int32_t  zone, int32_t  ___4336, int64_t startIndex, int64_t numValues, int32_t * values); int32_t tecioSZL_ZoneVarGetSharedZone(void* fileHandle, int32_t  zone, int32_t  ___4336, int32_t * sharedZone); int32_t tecioSZL_ZoneVarGetType(void* fileHandle, int32_t  zone, int32_t  ___4336, int32_t * type); int32_t tecioSZL_ZoneVarGetUInt8Values(void* fileHandle, int32_t  zone, int32_t  ___4336, int64_t startIndex, int64_t numValues, uint8_t* values); int32_t tecioSZL_ZoneVarGetValueLocation(void* fileHandle, int32_t  zone, int32_t  ___4336, int32_t * location); int32_t tecioSZL_ZoneVarIsPassive(void* fileHandle, int32_t  zone, int32_t  ___4336, int32_t * isPassive); }}