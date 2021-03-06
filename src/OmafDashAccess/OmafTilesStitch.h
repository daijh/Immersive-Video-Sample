/*
 * Copyright (c) 2019, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.

 */

//!

//! \file:   OmafTilesStitch.h
//! \brief:  the class for tiles merge
//! \detail: define the operation and related data for tiles merge.
//!
//! Created on May 22, 2020, 1:18 PM
//!

#ifndef OMAFTILESSTITCH_H
#define OMAFTILESSTITCH_H

#include "MediaPacket.h"
#include "general.h"

#include <memory>

VCD_OMAF_BEGIN

#define LCU_SIZE 64
#define HEVC_STARTCODES_LEN 4
#define HEVC_NALUHEADER_LEN 2

// map of <qualityRanking, <trackID, MediaPacket*>>
typedef std::map<QualityRank, std::map<uint32_t, MediaPacket *>> PacketsMap;

//!
//! \sturct: TilesMergeArrangement
//! \brief:  tiles merge layout information, including merged resolution,
//!          tiles layout and so on
//!
typedef struct TilesMergeArrangement {
  uint32_t mergedWidth;
  uint32_t mergedHeight;
  int32_t mostTopPos;
  int32_t mostLeftPos;
  TileArrangement tilesLayout;
} TilesMergeArrangement;

//!
//! \class OmafTilesStitch
//! \brief The class for tiles stitching
//!

class OmafTilesStitch {
 public:
  //!
  //! \brief Constructor
  //!
  OmafTilesStitch();

  //!
  //! \brief Destructor
  //!
  virtual ~OmafTilesStitch();

 public:
  //!
  //! \brief  Initialize stitching class
  //!
  //! \param  [in] firstFramePackets
  //!         the first set of media packets for selected tiles
  //! \param  [in] needParams
  //!         denote whether VPS/SPS/PPS need to be added into merged packet
  //! \param  [in] projFmt
  //!         denote the projectin format of input source where tiles come
  //!         from
  //!
  //! \return int32_t
  //!         ERROR_NONE if success, else failed reason
  //!
  int32_t Initialize(std::map<uint32_t, MediaPacket *> &firstFramePackets, bool needParams,
                     VCD::OMAF::ProjectionFormat projFmt);

  //!
  //! \brief  Update the set of media packets of selected tiles for next frame
  //!
  //! \param  [in] currPackets
  //!         the input new set of media packets of selected tiles for
  //!         next frame
  //! \param  [in] needParams
  //!         denote whether VPS/SPS/PPS need to be added into merged packet
  //!
  //! \return int32_t
  //!         ERROR_NONE if success, else failed reason
  //!
  int32_t UpdateSelectedTiles(std::map<uint32_t, MediaPacket *> &currPackets, bool needParams);

  //!
  //! \brief  Get media packets for merged tiles for current frame
  //!
  //! \return std::list<MediaPacket*>
  //!         the list of media packets for merged tiles for current
  //!         frame
  //!
  std::list<MediaPacket *> GetTilesMergedPackets();

  //!
  //! \brief  Get whether stitch class instance has been initialized
  //!
  //! \return bool
  //!         whether stitch class instance has been initialized
  //!
  bool IsInitialized() { return m_isInitialized; };

 private:
  //!
  //! \brief  Parse the VPS/SPS/PPS information
  //!
  //! \param  [in] tilePacket
  //!         the media packet for one selected tile from highest
  //!         quality video frame which contains VPS/SPS/PPS
  //!
  //! \return int32_t
  //!         ERROR_NONE if success, else failed reason
  //!
  int32_t ParseVideoHeader(MediaPacket *tilePacket);

  //!
  //! \brief  Calculate tiles merge layout for selected tiles
  //!
  //! \return std::map<QualityRank, TilesMergeArrangement*>
  //!         the map of tiles merge layout information for different
  //!         tiles sets of different quality ranking
  //!
  std::map<QualityRank, TilesMergeArrangement *> CalculateTilesMergeArrangement();

  //!
  //! \brief  Calculate region wise packing information for
  //!         tiles set with specified quality ranking when
  //!         tiles come from ERP projection
  //!
  //! \param  [in] qualityRanking
  //!         the quality ranking information for the tiles
  //!         set needed to be calculate region wise packing
  //! \param  [in] hasPacketLost
  //!         denote whether media packet is lost in packets
  //!         set
  //! \param  [in] hasLayoutChanged
  //!         denote whether current tiles merge layout has
  //!         changed compared to previous layout
  //!
  //! \return RegionWisePacking*
  //!         the pointer to the calculated region wise packing
  //!         information
  //!
  std::unique_ptr<RegionWisePacking> CalculateMergedRwpkForERP(QualityRank qualityRanking, bool hasPacketLost,
                                                               bool hasLayoutChanged);

  //!
  //! \brief  Calculate region wise packing information for
  //!         tiles set with specified quality ranking when
  //!         tiles come from CubeMap projection
  //!
  //! \param  [in] qualityRanking
  //!         the quality ranking information for the tiles
  //!         set needed to be calculate region wise packing
  //! \param  [in] hasPacketLost
  //!         denote whether media packet is lost in packets
  //!         set
  //! \param  [in] hasLayoutChanged
  //!         denote whether current tiles merge layout has
  //!         changed compared to previous layout
  //!
  //! \return RegionWisePacking*
  //!         the pointer to the calculated region wise packing
  //!         information
  //!
  std::unique_ptr<RegionWisePacking> CalculateMergedRwpkForCubeMap(QualityRank qualityRanking, bool hasPacketLost,
                                                   bool hasLayoutChanged);
  //! \brief  Generate tiles merge layout information
  //!
  //! \return int32_t
  //!         ERROR_NONE if success, else failed reason
  //!
  int32_t GenerateTilesMergeArrangement();

  //!
  //! \brief  Generate the output media packet after tiles merge
  //!
  //! \return int32_t
  //!         ERROR_NONE if success, else failed reason
  //!
  int32_t GenerateOutputMergedPackets();

private:
    OmafTilesStitch& operator=(const OmafTilesStitch& other) { return *this; };
    OmafTilesStitch(const OmafTilesStitch& other) { /* do not create copies */ };

 private:
  bool m_isInitialized;  //<! whether the stitch class has been initialized

  VCD::OMAF::ProjectionFormat m_projFmt;  //<! the projection format of input source where tiles come from

  PacketsMap m_selectedTiles;  //<! map of <qualityRanking, <trackID, MediaPacket*>>

  std::set<QualityRank> m_allQualities;  //<! set of all quality ranking values

  param_360SCVP *m_360scvpParam;  //<! 360SCVP library input parameter

  void *m_360scvpHandle;  //<! 360SCVP library handle

  uint8_t *m_fullResVideoHeader;  //<! VPS/SPS/PPS bitstream data for the full resolution video stream

  uint32_t m_fullResVPSSize;  //<! VPS size of original video stream of highest quality

  uint32_t m_fullResSPSSize;  //<! SPS size of original video stream of highest quality

  uint32_t m_fullResPPSSize;  //<! PPS size of original video stream of highest quality

  std::map<QualityRank, TilesMergeArrangement *>
      m_initTilesMergeArr;  //<! initial tiles merge arrangement at the beginning

  std::map<QualityRank, TilesMergeArrangement *> m_updatedTilesMergeArr;  //<! updated tiles merge arrangement per frame

  std::map<QualityRank, std::map<uint32_t, uint8_t *>>
      m_mergedVideoHeaders;  //<! map of <qualityRanking, <mergedVideoHeadersSize, mergedVideoHeadersData*>>

  uint32_t m_fullWidth;  //<! the width of original video

  uint32_t m_fullHeight;  //<! the height of original height

  uint32_t m_mainMergedWidth;  //<! the width of main tiles merged video

  uint32_t m_mainMergedHeight;  //<! the height of main tiles merged video

  uint32_t m_mainMergedTileRows;  //<! the tile rows number of main merged video

  uint32_t m_mainMergedTileCols;  //<! the tile cols number of main merged video

  bool m_needHeaders;  //<! whether VPS/SPS/PPS are needed for output merged packet

  std::list<MediaPacket *>
      m_outMergedStream;  //<! the list of output tiles merged video stream, one stream one MediaPacket

  RectangularRegionWisePacking* m_tmpRegionrwpk;
};

VCD_OMAF_END;

#endif /* OMAFTILESSTITCH_H */
