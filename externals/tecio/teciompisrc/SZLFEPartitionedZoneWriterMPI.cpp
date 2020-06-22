#include "SZLFEPartitionedZoneWriterMPI.h"
#include "ThirdPartyHeadersBegin.h"
#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include "ThirdPartyHeadersEnd.h"
#include "FEZoneInfo.h"
#include "FieldData.h"
#include "FileWriterInterface.h"
#include "ItemSetIterator.h"
#include "MPICommunicationCache.h"
#include "MPICommunicator.h"
#include "MPIFileWriter.h"
#include "MPINonBlockingCommunicationCollection.h"
#include "MPIUtil.h"
#include "NodeMap.h"
#include "SZLFEPartitionWriter.h"
#include "TecioMPI.h"
#include "ZoneInfoCache.h"
using namespace tecplot::___3933; namespace tecplot { namespace teciompi { struct SZLFEPartitionedZoneWriterMPI::Impl { MPI_Comm m_comm; int m_mainProcess; int m_localProcess; bool m_useCollectiveRoutines; Impl(MPI_Comm comm, int mainProcess, ___37& ___36, ___4636 zone) : m_comm(comm) , m_mainProcess(mainProcess) , m_useCollectiveRoutines(everyRankOwnsOnePartition(comm, ___36, zone)) { MPI_Comm_rank(m_comm, &m_localProcess); } }; SZLFEPartitionedZoneWriterMPI::SZLFEPartitionedZoneWriterMPI( ItemSetIterator&              varIter, ___4636                   zone, ___4636                   ___341, std::vector<___372> const& ___4564, ___372                     ___4499, ___37&                   ___36, ZoneInfoCache&                zoneInfoCache, MPI_Comm                      comm, int                           mainProcess) : SZLFEPartitionedZoneWriter(varIter, zone, ___341, ___4564, ___4499, ___36, zoneInfoCache) , m_impl(new Impl(comm, mainProcess, ___36, zone)) { createPartitionWriters(); } SZLFEPartitionedZoneWriterMPI::~SZLFEPartitionedZoneWriterMPI() {} ___2479 SZLFEPartitionedZoneWriterMPI::varMinMax(___4352 datasetVar) { REQUIRE(m_varIter.baseItem() <= datasetVar && datasetVar < m_varIter.___2812()); ___2479 ___3358; ___4352 const baseVar = m_varIter.baseItem(); for(___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) ___3358.include(m_varPartitionMinMaxes[datasetVar - baseVar][___2977]); return ___3358; } void SZLFEPartitionedZoneWriterMPI::collateAndReturnResponses( MPINonBlockingCommunicationCollection& communicationCollection) { std::vector<std::vector<int> > referencingPartitions(___2337.zoneGetNumPartitions(___2677 + 1)); MPICommunicator communicator(m_impl->m_comm); for(___4636 i = 0; i < ___2337.zoneGetNumPartitions(___2677 + 1); ++i) { int ___3656 = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, i + 1); SimpleVector<___2090::___2980> neighbors; communicator.receiveVector(neighbors, ___3656, TecioMPI::REFERENCED_PARTITIONS_SIZE, TecioMPI::REFERENCED_PARTITIONS_VEC); BOOST_FOREACH(int neighbor, neighbors) referencingPartitions[neighbor].push_back(i); } for(___4636 i = 0; i < ___2337.zoneGetNumPartitions(___2677 + 1); ++i) communicationCollection.sendVectorCopy( SimpleVector<int32_t>(referencingPartitions[i].begin(), referencingPartitions[i].end()), ___2337.zonePartitionGetOwnerProcess(___2677 + 1, i + 1), TecioMPI::REFERENCING_PARTITIONS_SIZE, TecioMPI::REFERENCING_PARTITIONS_VEC); } void SZLFEPartitionedZoneWriterMPI::exchangeGhostInfo( std::map<int, boost::shared_ptr<___3933::___1350> >& partitionInfoMap) { PartitionTecUtilDecorator partitionTecUtilDecorator(___2337, ___2677 + 1); ___4352 const numVarsToWrite = m_varIter.___2812(); ___2090::___2980 numPartitions = static_cast<___2090::___2980>(___2337.zoneGetNumPartitions(___2677 + 1)); MPINonBlockingCommunicationCollection communicationCollection(m_impl->m_comm); std::map<int, NeighborCellSubzoneInfoMap> neighborCellSubzoneInfoMapMap; std::map<int, SimpleVector<int32_t> > referencingPartitionsMap; for(___2090::___2980 ___2977 = 0; ___2977 < numPartitions; ++___2977) { if (___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1) != m_impl->m_localProcess) continue; ___2724 ___2723(&partitionTecUtilDecorator, ___2977 + 1); std::vector<___1352> fieldDatas(numVarsToWrite); m_varIter.reset(); ___4352 const baseVar = m_varIter.baseItem(); while (m_varIter.hasNext()) { ___4352 const datasetVar = m_varIter.next(); ___4352 const fileVar = datasetVar - baseVar; if (___2337.___4353(datasetVar + 1) && !___2337.___926(___2677 + 1, datasetVar + 1)) { if (___2337.___910(___2677 + 1, datasetVar + 1) == ___4330) fieldDatas[fileVar] = ___1352(&partitionTecUtilDecorator, ___2977 + 1, datasetVar + 1, false, false); else fieldDatas[fileVar] = ___1352(&partitionTecUtilDecorator, ___2977 + 1, datasetVar + 1, false, true); } } gatherNeighborCellSubzoneInfo(neighborCellSubzoneInfoMapMap[___2977], ___2977, numVarsToWrite, ___2723, fieldDatas, *(partitionInfoMap[___2977])); std::set<___2090::___2980> referencedPartitions; BOOST_FOREACH(NeighborCellSubzoneInfoMap::value_type const& valuePair, neighborCellSubzoneInfoMapMap[___2977]) { ___2090::___2980 const neighbor = valuePair.first; referencedPartitions.insert(neighbor); } if (!referencedPartitions.empty()) partitionInfoMap[___2977]->addReferencedPartitions(referencedPartitions); SimpleVector<___2090::___2980> partitionVector(referencedPartitions.begin(), referencedPartitions.end()); communicationCollection.sendVectorCopy(partitionVector, m_impl->m_mainProcess, TecioMPI::REFERENCED_PARTITIONS_SIZE, TecioMPI::REFERENCED_PARTITIONS_VEC); communicationCollection.receiveVector(referencingPartitionsMap[___2977], m_impl->m_mainProcess, TecioMPI::REFERENCING_PARTITIONS_SIZE, TecioMPI::REFERENCING_PARTITIONS_VEC);
} if (m_impl->m_localProcess == m_impl->m_mainProcess) { collateAndReturnResponses(communicationCollection); } communicationCollection.___4446(); for(___2090::___2980 ___2977 = 0; ___2977 < numPartitions; ++___2977) { if (___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1) != m_impl->m_localProcess) continue; BOOST_FOREACH(NeighborCellSubzoneInfoMap::value_type const& valuePair, neighborCellSubzoneInfoMapMap[___2977]) { ___2090::___2980 const neighbor = valuePair.first; int32_t partitionOwner = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, neighbor + 1); NeighborCellSubzoneInfo const& neighborCellSubzoneInfo = valuePair.second; ___478(!neighborCellSubzoneInfo.m_nodes.empty()); SimpleVector<int64_t> nodes(neighborCellSubzoneInfo.m_neighborNodes.begin(), neighborCellSubzoneInfo.m_neighborNodes.end()); MPICommunicationCache cache; cache.addVector(nodes, TecioMPI::REFERENCED_NODES); for(size_t i = 0; i < neighborCellSubzoneInfo.m_nodes.size(); ++i) { SimpleVector<uint32_t> cellSubzones(neighborCellSubzoneInfo.m_cellSubzones[i].begin(), neighborCellSubzoneInfo.m_cellSubzones[i].end()); cache.addVector(cellSubzones, TecioMPI::REFERENCED_NODE_CELL_SUBZONES); SimpleVector<double> minMaxes(2 * static_cast<int>(neighborCellSubzoneInfo.m_varMinMaxes[i].size())); int ind = 0; BOOST_FOREACH(___2479 const& minMax, neighborCellSubzoneInfo.m_varMinMaxes[i]) { minMaxes[ind++] = minMax.minValue(); minMaxes[ind++] = minMax.maxValue(); } cache.addVector(minMaxes, TecioMPI::REFERENCED_NODE_MINMAXES); } communicationCollection.sendVectorCopy(cache.data(), partitionOwner, TecioMPI::REFERENCED_NODE_CACHED_INFO_SIZE, TecioMPI::REFERENCED_NODE_CACHED_INFO_VEC); } } typedef std::map<___2090::___2980, std::set<___2090::___2980> > PartitionNeighborMap; PartitionNeighborMap receiveOrder; for(___2090::___2980 i = 0; i < numPartitions; ++i) { if (___2337.zonePartitionGetOwnerProcess(___2677 + 1, i + 1) != m_impl->m_localProcess) continue; for(int ___2105 = 0; ___2105 < referencingPartitionsMap[i].size(); ++___2105) receiveOrder[referencingPartitionsMap[i][___2105]].insert(i); } MPICommunicator mpiCommunicator(m_impl->m_comm); BOOST_FOREACH(PartitionNeighborMap::value_type const& valuePair, receiveOrder) { ___2090::___2980 const referencingPartition = valuePair.first; BOOST_FOREACH(___2090::___2980 ___2977, valuePair.second) { ___478(___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1) == m_impl->m_localProcess); int32_t partitionOwner = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, referencingPartition + 1); SimpleVector<uint8_t> cachedData; mpiCommunicator.receiveVector(cachedData, partitionOwner, TecioMPI::REFERENCED_NODE_CACHED_INFO_SIZE, TecioMPI::REFERENCED_NODE_CACHED_INFO_VEC); MPICommunicationCache cache(cachedData); SimpleVector <int64_t>nodeVector; cache.retrieveVector(nodeVector, TecioMPI::REFERENCED_NODES); std::vector<___2718> nodes(nodeVector.begin(), nodeVector.end()); std::vector<boost::unordered_set<___2090::SubzoneOffset_t> > cellSubzones; std::vector<std::vector<___2479> > varMinMaxes; for(int ___2105 = 0; ___2105 < nodeVector.size(); ++___2105) { SimpleVector<___2090::SubzoneOffset_t> cellSubzonesVector; cache.retrieveVector(cellSubzonesVector, TecioMPI::REFERENCED_NODE_CELL_SUBZONES); cellSubzones.push_back(boost::unordered_set<___2090::SubzoneOffset_t>(cellSubzonesVector.begin(), cellSubzonesVector.end())); SimpleVector<double> minMaxesVector; cache.retrieveVector(minMaxesVector, TecioMPI::REFERENCED_NODE_MINMAXES); int ___2843 = minMaxesVector.size() / 2; std::vector<___2479> nodeMinMaxes(___2843); for(int ___4291 = 0; ___4291 < ___2843; ++___4291) { nodeMinMaxes[___4291].include(minMaxesVector[2 * ___4291]); nodeMinMaxes[___4291].include(minMaxesVector[2 * ___4291 + 1]); } varMinMaxes.push_back(nodeMinMaxes); } partitionInfoMap[___2977]->addNeighborCszInfo(referencingPartition, nodes, cellSubzones, varMinMaxes); SimpleVector<uint32_t> nodeSubzoneOffsets(nodeVector.size()); SimpleVector<uint16_t> nodeItemOffsets(nodeVector.size()); for(int ___2105 = 0; ___2105 < nodeVector.size(); ++___2105) { ___2090 const nodeAddress(partitionInfoMap[___2977]->___3924(nodeVector[___2105])); nodeSubzoneOffsets[___2105] = nodeAddress.subzoneOffset(); nodeItemOffsets[___2105] = nodeAddress.itemOffset(); } communicationCollection.sendVectorCopy(nodeSubzoneOffsets, partitionOwner, TecioMPI::REFERENCED_NODE_SUBZONES_SIZE, TecioMPI::REFERENCED_NODE_SUBZONES_VEC); communicationCollection.sendVectorCopy(nodeItemOffsets, partitionOwner, TecioMPI::REFERENCED_NODE_OFFSETS_SIZE, TecioMPI::REFERENCED_NODE_OFFSETS_VEC); } } for(___2090::___2980 ___2977 = 0; ___2977 < numPartitions; ++___2977) { if (___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1) != m_impl->m_localProcess) continue; BOOST_FOREACH(NeighborCellSubzoneInfoMap::value_type const& valuePair, neighborCellSubzoneInfoMapMap[___2977]) { ___2090::___2980 const neighbor = valuePair.first; int32_t partitionOwner = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, neighbor + 1);
NeighborCellSubzoneInfo const& neighborCellSubzoneInfo = valuePair.second; SimpleVector<uint32_t> nodeSubzoneOffsets; SimpleVector<uint16_t> nodeItemOffsets; mpiCommunicator.receiveVector(nodeSubzoneOffsets, partitionOwner, TecioMPI::REFERENCED_NODE_SUBZONES_SIZE, TecioMPI::REFERENCED_NODE_SUBZONES_VEC); mpiCommunicator.receiveVector(nodeItemOffsets, partitionOwner, TecioMPI::REFERENCED_NODE_OFFSETS_SIZE, TecioMPI::REFERENCED_NODE_OFFSETS_VEC); ___478(static_cast<size_t>(nodeSubzoneOffsets.size()) == neighborCellSubzoneInfo.m_nodes.size()); ___478(static_cast<size_t>(nodeItemOffsets.size()) == neighborCellSubzoneInfo.m_nodes.size()); for(int i = 0; i < static_cast<int>(neighborCellSubzoneInfo.m_nodes.size()); ++i) { ___2090 const nodeAddress(neighbor, nodeSubzoneOffsets[i], nodeItemOffsets[i]); partitionInfoMap[___2977]->addNeighborNodeCoordinate(neighborCellSubzoneInfo.m_nodes[i], nodeAddress); } } } if (!communicationCollection.isComplete()) communicationCollection.___4446(); } void SZLFEPartitionedZoneWriterMPI::createPartitionWriters() { std::map<int, boost::shared_ptr<___1350> > partitionInfoMap; for(___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) { if (___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1) != m_impl->m_localProcess) continue; partitionInfoMap[___2977] = ___2680.getFEZonePartitionInfo(___2677, ___2977, m_partitionTecUtil); m_partitionNumCells[___2977] = static_cast<uint32_t>(partitionInfoMap[___2977]->___1766() - partitionInfoMap[___2977]->getNumGhostCells()); m_partitionNumNodes[___2977] = static_cast<uint32_t>(partitionInfoMap[___2977]->___1768() - partitionInfoMap[___2977]->getNumGhostNodes()); } exchangeGhostInfo(partitionInfoMap); for(___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) { if (___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1) == m_impl->m_localProcess) m_partitionWriters[___2977] = boost::make_shared<SZLFEPartitionWriter> ( boost::ref(m_varIter), ___2677, m_baseZone, ___2977, boost::ref(m_writeVariables), m_writeConnectivity, boost::ref(m_partitionTecUtil), partitionInfoMap[___2977]); } } ___372 SZLFEPartitionedZoneWriterMPI::writeZoneHeader(___3933::FileWriterInterface& szpltFile) { if (m_impl->m_localProcess == m_impl->m_mainProcess) return SZLFEPartitionedZoneWriter::writeZoneHeader(szpltFile); else return ___4226; } uint64_t SZLFEPartitionedZoneWriterMPI::zoneHeaderFileSize(bool ___2002) { if (m_impl->m_localProcess == m_impl->m_mainProcess) return SZLFEPartitionedZoneWriter::zoneHeaderFileSize(___2002); else return 0; } ___372 SZLFEPartitionedZoneWriterMPI::writeZoneData(___3933::FileWriterInterface& szpltFile) { ___1393 fileLoc = szpltFile.fileLoc(); boost::unordered_map<___4636, ___1393> partitionFileLocMap; uint64_t localPartitionFileSize = 0; if (m_impl->m_useCollectiveRoutines) { ___478(m_partitionWriters.size() == 1); ___4636 localPartition = m_partitionWriters.begin()->first; localPartitionFileSize = m_partitionWriters[localPartition]->zoneFileSize(szpltFile.___2002() == ___4226); gatherScatterPartitionFileLocs(fileLoc, partitionFileLocMap[localPartition], ___2337, ___2677, m_impl->m_localProcess, localPartitionFileSize, m_impl->m_mainProcess, m_impl->m_comm); } else if (m_impl->m_localProcess == m_impl->m_mainProcess) { MPICommunicator communicator(m_impl->m_comm); for (___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) { uint64_t partitionFileSize; int32_t partitionOwner = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1); if (partitionOwner == m_impl->m_localProcess) { partitionFileLocMap[___2977] = fileLoc; partitionFileSize = m_partitionWriters[___2977]->zoneFileSize(szpltFile.___2002() == ___4226); } else { communicator.sendScalar(fileLoc, partitionOwner, TecioMPI::PARTITION_FILE_LOC); communicator.receiveScalar(partitionFileSize, partitionOwner, TecioMPI::PARTITION_FILE_SIZE); } fileLoc += partitionFileSize; } } else { MPINonBlockingCommunicationCollection communicationCollection(m_impl->m_comm); for (___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) { if (___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1) == m_impl->m_localProcess) { uint64_t partitionSize = m_partitionWriters[___2977]->zoneFileSize(szpltFile.___2002() == ___4226); communicationCollection.sendScalarCopy(partitionSize, m_impl->m_mainProcess, TecioMPI::PARTITION_FILE_SIZE); communicationCollection.receiveScalar(partitionFileLocMap[___2977], m_impl->m_mainProcess, TecioMPI::PARTITION_FILE_LOC); } } communicationCollection.___4446(); } if (m_impl->m_useCollectiveRoutines) { ___478(m_partitionWriters.size() == 1 && localPartitionFileSize > 0); ___4636 localPartition = m_partitionWriters.begin()->first; MPIFileWriter& fileWriter = dynamic_cast<MPIFileWriter&>(szpltFile);
boost::scoped_ptr<MPIFileWriter::ScopedCaching> scopedCaching; try { scopedCaching.reset(new MPIFileWriter::ScopedCaching(fileWriter, localPartitionFileSize)); } catch (...) { } m_partitionWriters[localPartition]->writeZone(szpltFile, partitionFileLocMap[localPartition]); m_partitionHeaderFilePositions[localPartition] = m_partitionWriters[localPartition]->getZoneHeaderFilePosition(); MPICommunicationCache cache; cache.addScalar(m_partitionHeaderFilePositions[localPartition], TecioMPI::PARTITION_HEADER_FILE_LOC); cache.addScalar(m_partitionNumCells[localPartition], TecioMPI::PARTITION_NUM_CELLS); cache.addScalar(m_partitionNumNodes[localPartition], TecioMPI::PARTITION_NUM_NODES); SimpleVector<___2479> minMaxValues(m_varIter.___2812()); m_varIter.reset(); int i = 0; while (m_varIter.hasNext()) { ___4352 const datasetVar = m_varIter.next(); minMaxValues[i++] = m_partitionWriters[localPartition]->varMinMax(datasetVar); } cache.addVector(minMaxValues, TecioMPI::PARTITION_VAR_MINMAX_VALUES); SimpleVector<uint8_t> cachedData = cache.data(); int bytesPerPartition = cachedData.size(); std::vector<uint8_t> serializedCaches(static_cast<size_t>(bytesPerPartition)* ___2337.zoneGetNumPartitions(___2677 + 1)); MPI_Gather(&cachedData[0], bytesPerPartition, MPI_UINT8_T, &serializedCaches[0], bytesPerPartition, MPI_UINT8_T, m_impl->m_mainProcess, m_impl->m_comm); if (m_impl->m_localProcess == m_impl->m_mainProcess) { for (___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) { MPICommunicationCache cache(&serializedCaches[___2977 * bytesPerPartition], bytesPerPartition); int32_t partitionOwner = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1); cache.retrieveScalar(m_partitionHeaderFilePositions[___2977], TecioMPI::PARTITION_HEADER_FILE_LOC); cache.retrieveScalar(m_partitionNumCells[___2977], TecioMPI::PARTITION_NUM_CELLS); cache.retrieveScalar(m_partitionNumNodes[___2977], TecioMPI::PARTITION_NUM_NODES); SimpleVector<___2479> minMaxValues; cache.retrieveVector(minMaxValues, TecioMPI::PARTITION_VAR_MINMAX_VALUES); ___478(minMaxValues.size() == m_varIter.___2812()); m_varIter.reset(); ___4352 const baseVar = m_varIter.baseItem(); while (m_varIter.hasNext()) { ___4352 const fileVar = m_varIter.next() - baseVar; m_varPartitionMinMaxes[fileVar][partitionOwner] = minMaxValues[fileVar]; } } } } else { for (___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) { int32_t partitionOwner = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1); if (partitionOwner == m_impl->m_localProcess) { m_partitionWriters[___2977]->writeZone(szpltFile, partitionFileLocMap[___2977]); m_partitionHeaderFilePositions[___2977] = m_partitionWriters[___2977]->getZoneHeaderFilePosition(); if (m_impl->m_localProcess == m_impl->m_mainProcess) { m_varIter.reset(); ___4352 const baseVar = m_varIter.baseItem(); while (m_varIter.hasNext()) { ___4352 const datasetVar = m_varIter.next(); m_varPartitionMinMaxes[datasetVar - baseVar][___2977] = m_partitionWriters[___2977]->varMinMax(datasetVar); } } else { MPICommunicationCache cache; cache.addScalar(m_partitionHeaderFilePositions[___2977], TecioMPI::PARTITION_HEADER_FILE_LOC); cache.addScalar(m_partitionNumCells[___2977], TecioMPI::PARTITION_NUM_CELLS); cache.addScalar(m_partitionNumNodes[___2977], TecioMPI::PARTITION_NUM_NODES); SimpleVector<___2479> minMaxValues(m_varIter.___2812()); m_varIter.reset(); int i = 0; while (m_varIter.hasNext()) { ___4352 const datasetVar = m_varIter.next(); minMaxValues[i++] = m_partitionWriters[___2977]->varMinMax(datasetVar); } cache.addVector(minMaxValues, TecioMPI::PARTITION_VAR_MINMAX_VALUES); MPICommunicator(m_impl->m_comm).sendVector(cache.data(), m_impl->m_mainProcess, TecioMPI::PARTITION_CACHED_INFO_SIZE, TecioMPI::PARTITION_CACHED_INFO_VEC); } } else if (m_impl->m_localProcess == m_impl->m_mainProcess) { MPICommunicator communicator(m_impl->m_comm); SimpleVector<uint8_t> cachedData; communicator.receiveVector(cachedData, partitionOwner, TecioMPI::PARTITION_CACHED_INFO_SIZE, TecioMPI::PARTITION_CACHED_INFO_VEC); MPICommunicationCache cache(cachedData); SimpleVector<___2479> minMaxValues; cache.retrieveScalar(m_partitionHeaderFilePositions[___2977], TecioMPI::PARTITION_HEADER_FILE_LOC); cache.retrieveScalar(m_partitionNumCells[___2977], TecioMPI::PARTITION_NUM_CELLS); cache.retrieveScalar(m_partitionNumNodes[___2977], TecioMPI::PARTITION_NUM_NODES); cache.retrieveVector(minMaxValues, TecioMPI::PARTITION_VAR_MINMAX_VALUES); ___478(minMaxValues.size() == m_varIter.___2812()); m_varIter.reset(); ___4352 const baseVar = m_varIter.baseItem(); while (m_varIter.hasNext()) { ___4352 const fileVar = m_varIter.next() - baseVar; m_varPartitionMinMaxes[fileVar][___2977] = minMaxValues[fileVar]; } } } } if (m_impl->m_localProcess == m_impl->m_mainProcess) szpltFile.___3459(fileLoc);
 #if !defined NO_ASSERTS
if (m_impl->m_localProcess != m_impl->m_mainProcess) szpltFile.___3459(0);
 #endif
return ___4226; } uint64_t SZLFEPartitionedZoneWriterMPI::zoneDataFileSize(bool ___2002) { uint64_t ___3358 = 0; MPICommunicator communicator(m_impl->m_comm); if (m_impl->m_localProcess == m_impl->m_mainProcess) { for(___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) { uint64_t partitionFileSize; int partitionOwner = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1); if (partitionOwner == m_impl->m_localProcess) partitionFileSize = m_partitionWriters[___2977]->zoneFileSize(___2002); else communicator.receiveScalar(partitionFileSize, partitionOwner, TecioMPI::PARTITION_FILE_SIZE); ___3358 += partitionFileSize; } } else { for(___4636 ___2977 = 0; ___2977 < ___2337.zoneGetNumPartitions(___2677 + 1); ++___2977) { int partitionOwner = ___2337.zonePartitionGetOwnerProcess(___2677 + 1, ___2977 + 1); if (partitionOwner == m_impl->m_localProcess) { uint64_t partitionFileSize = m_partitionWriters[___2977]->zoneFileSize(___2002); communicator.sendScalar(partitionFileSize, m_impl->m_mainProcess, TecioMPI::PARTITION_FILE_SIZE); } } } return ___3358; } }}