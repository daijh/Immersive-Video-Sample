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
//! \file:   ExtractorTrackGenerator.h
//! \brief:  Extractor track generator class definition
//! \detail: Define the operation of extractor track generator for various
//!          input video streams scenarios
//!
//! Created on April 30, 2019, 6:04 AM
//!

#ifndef _EXTRACTORTRACKGENERATOR_H_
#define _EXTRACTORTRACKGENERATOR_H_

#include "VROmafPacking_data.h"
#include "definitions.h"
#include "MediaStream.h"
#include "ExtractorTrack.h"
#include "RegionWisePackingGenerator.h"
#include "../utils/OmafStructure.h"

VCD_NS_BEGIN

//!
//! \class ExtractorTrackGenerator
//! \brief Define the operation of extractor track generator
//!        for various input video streams scenarios
//!

class ExtractorTrackGenerator
{
public:
    //!
    //! \brief  Constructor
    //!
    ExtractorTrackGenerator()
    {
        m_initInfo = NULL;
        m_streams  = NULL;
        m_viewportNum = 0;
        m_rwpkGen     = NULL;
        m_newSPSNalu  = NULL;
        m_newPPSNalu  = NULL;
        m_videoIdxInMedia = NULL;
        m_360scvpParam    = NULL;
        m_360scvpHandle   = NULL;
        m_tilesInViewport = NULL;
        m_viewInfo        = NULL;
        m_tilesNumInViewport  = 0;
        m_finalViewportWidth  = 0;
        m_finalViewportHeight = 0;
        m_origResWidth    = 0;
        m_origResHeight   = 0;
        m_origTileInRow     = 0;
        m_origTileInCol     = 0;
        m_origTileWidth     = 0;
        m_origTileHeight    = 0;
        m_tilesInfo       = NULL;
        m_projType        = VCD::OMAF::ProjectionFormat::PF_ERP;
        m_packedPicWidth  = 0;
        m_packedPicHeight = 0;
        m_origVPSNalu     = NULL;
        m_origSPSNalu     = NULL;
        m_origPPSNalu     = NULL;
    };

    //!
    //! \brief  Copy Constructor
    //!
    //! \param  [in] initInfo
    //!         initial information input by the library interface
    //! \param  [in] streams
    //!         pointer to the media streams map set up in OmafPackage
    //!
    ExtractorTrackGenerator(InitialInfo *initInfo, std::map<uint8_t, MediaStream*> *streams)
    {
        m_initInfo = initInfo;
        m_streams  = streams;
        m_viewportNum = 0;
        m_rwpkGen     = NULL;
        m_newSPSNalu  = NULL;
        m_newPPSNalu  = NULL;
        m_videoIdxInMedia = NULL;
        m_360scvpParam    = NULL;
        m_360scvpHandle   = NULL;
        m_tilesInViewport = NULL;
        m_viewInfo        = NULL;
        m_tilesNumInViewport  = 0;
        m_finalViewportWidth  = 0;
        m_finalViewportHeight = 0;
        m_origResWidth    = 0;
        m_origResHeight   = 0;
        m_origTileInRow     = 0;
        m_origTileInCol     = 0;
        m_origTileWidth     = 0;
        m_origTileHeight    = 0;
        m_tilesInfo       = NULL;
        m_projType        = VCD::OMAF::ProjectionFormat::PF_ERP;
        m_packedPicWidth  = 0;
        m_packedPicHeight = 0;
        m_origVPSNalu     = NULL;
        m_origSPSNalu     = NULL;
        m_origPPSNalu     = NULL;
    };

    ExtractorTrackGenerator(const ExtractorTrackGenerator& src)
    {
        m_initInfo = src.m_initInfo;
        m_streams  = src.m_streams;
        m_viewportNum = src.m_viewportNum;
        m_rwpkGen     = std::move(src.m_rwpkGen);
        m_newSPSNalu  = std::move(src.m_newSPSNalu);
        m_newPPSNalu  = std::move(src.m_newPPSNalu);
        m_videoIdxInMedia = std::move(src.m_videoIdxInMedia);
        m_360scvpParam    = std::move(src.m_360scvpParam);
        m_360scvpHandle   = std::move(src.m_360scvpHandle);
        m_tilesInViewport = std::move(src.m_tilesInViewport);
        m_viewInfo        = std::move(src.m_viewInfo);
        m_tilesNumInViewport  = src.m_tilesNumInViewport;
        m_finalViewportWidth  = src.m_finalViewportWidth;
        m_finalViewportHeight = src.m_finalViewportHeight;
        m_origResWidth    = src.m_origResWidth;
        m_origResHeight   = src.m_origResHeight;
        m_origTileInRow     = src.m_origTileInRow;
        m_origTileInCol     = src.m_origTileInCol;
        m_origTileWidth     = src.m_origTileWidth;
        m_origTileHeight    = src.m_origTileHeight;
        m_tilesInfo       = std::move(src.m_tilesInfo);
        m_projType        = src.m_projType;
        m_packedPicWidth  = src.m_packedPicWidth;
        m_packedPicHeight = src.m_packedPicHeight;
        m_origVPSNalu     = std::move(src.m_origVPSNalu);
        m_origSPSNalu     = std::move(src.m_origSPSNalu);
        m_origPPSNalu     = std::move(src.m_origPPSNalu);
    };

    ExtractorTrackGenerator& operator=(ExtractorTrackGenerator&& other)
    {
        m_initInfo = other.m_initInfo;
        m_streams  = other.m_streams;
        m_viewportNum = other.m_viewportNum;
        m_rwpkGen     = NULL;
        m_newSPSNalu  = NULL;
        m_newPPSNalu  = NULL;
        m_videoIdxInMedia = NULL;
        m_360scvpParam    = NULL;
        m_360scvpHandle   = NULL;
        m_tilesInViewport = NULL;
        m_viewInfo        = NULL;
        m_tilesNumInViewport  = other.m_tilesNumInViewport;
        m_finalViewportWidth  = other.m_finalViewportWidth;
        m_finalViewportHeight = other.m_finalViewportHeight;
        m_origResWidth    = other.m_origResWidth;
        m_origResHeight   = other.m_origResHeight;
        m_origTileInRow     = other.m_origTileInRow;
        m_origTileInCol     = other.m_origTileInCol;
        m_origTileWidth     = other.m_origTileWidth;
        m_origTileHeight    = other.m_origTileHeight;
        m_tilesInfo       = NULL;
        m_projType        = other.m_projType;
        m_packedPicWidth  = other.m_packedPicWidth;
        m_packedPicHeight = other.m_packedPicHeight;
        m_origVPSNalu     = NULL;
        m_origSPSNalu     = NULL;
        m_origPPSNalu     = NULL;

        return *this;
    };

    //!
    //! \brief  Destructor
    //!
    ~ExtractorTrackGenerator();

    //!
    //! \brief  Initialize the extractor track generator
    //!         for various input video streams scenarios
    //!
    //! \return int32_t
    //!         ERROR_NONE if success, else failed reason
    //!
    int32_t Initialize();

    //!
    //! \brief  Generate all extractor tracks
    //!
    //! \param  [in] extractorTrackMap
    //!         pointer to extractor tracks map which holds
    //!         all extractor tracks
    //! \param  [in] streams
    //!         pointer to the media streams map set up in OmafPackage
    //!
    //! \return int32_t
    //!         ERROR_NONE if success, else failed reason
    //!
    int32_t GenerateExtractorTracks(
        std::map<uint8_t, ExtractorTrack*>& extractorTrackMap,
        std::map<uint8_t, MediaStream*> *streams);

    //!
    //! \brief  Get the new SPS nalu for tiles merged bitstream
    //!
    //! \return Nalu*
    //!         the pointer to the new SPS nalu
    //!
    Nalu* GetNewSPS() { return m_newSPSNalu; };

    //!
    //! \brief  Get the new PPS nalu for tiles merged bitstream
    //!
    //! \return Nalu*
    //!         the pointer to the new PPS nalu
    //!
    Nalu* GetNewPPS() { return m_newPPSNalu; };

private:
    //!
    //! \brief  Calculate the total viewport number
    //!         according to the initial information
    //!
    //! \return uint16_t
    //!         the total viewport number
    //!
    uint16_t CalculateViewportNum();

    //!
    //! \brief  Fill the region wise packing information
    //!         for the specified viewport
    //!
    //! \param  [in] viewportIdx
    //!         the index of the specified viewport
    //! \param  [in] dstRwpk
    //!         pointer to the region wise packing information for the
    //!         specified viewport generated according to srcRwpk and
    //!         tiles merging strategy
    //!
    //! \return int32_t
    //!         ERROR_NONE if success, else failed reason
    //!
    int32_t FillDstRegionWisePacking(uint8_t viewportIdx, RegionWisePacking *dstRwpk);

    //!
    //! \brief  Fill the tiles merging direction information
    //!         for the specified viewport
    //!
    //! \param  [in] viewportIdx
    //!         the index of the specified viewport
    //! \param  [in] tilesMergeDir
    //!         pointer to the tiles merging direction information
    //!         for the specified viewport generated according to
    //!         tiles merging strategy
    //!
    //! \return int32_t
    //!         ERROR_NONE if success, else failed reason
    //!
    int32_t FillTilesMergeDirection(
        uint8_t viewportIdx,
        TilesMergeDirectionInCol *tilesMergeDir);

    //!
    //! \brief  Fill the content coverage information
    //!         for the specified viewport
    //!
    //! \param  [in] viewportIdx
    //!         the index of the specified viewport
    //! \param  [in] dstCovi
    //!         pointer to the content coverage information for the
    //!         specified viewport generated according to srcCovi and
    //!         tiles merging strategy
    //!
    //! \return int32_t
    //!         ERROR_NONE if success, else failed reason
    //!
    int32_t FillDstContentCoverage(uint8_t viewportIdx, ContentCoverage *dstCovi);

    //!
    //! \brief  Check the validation of initial information
    //!         input by library interface, meanwhile fill the lacked
    //!         information according to actual streams information
    //!
    //! \return int32_t
    //!         ERROR_NONE if success, else failed reason
    //!
    int32_t CheckAndFillInitInfo();

    //!
    //! \brief  Generate the new SPS for tiles merged bitstream
    //!
    //! \return int32_t
    //!         ERROR_NONE if success, else failed reason
    //!
    int32_t GenerateNewSPS();

    //!
    //! \brief  Generate the new PPS for tiles merged bitstream
    //!
    //! \return int32_t
    //!         ERROR_NONE if success, else failed reason
    //!
    int32_t GenerateNewPPS();

private:
    InitialInfo                     *m_initInfo;   //!< initial information input by library interface
    std::map<uint8_t, MediaStream*> *m_streams;    //!< media streams map set up in OmafPackage
    uint16_t                        m_viewportNum; //!< viewport number calculated according to initial information
    RegionWisePackingGenerator      *m_rwpkGen;    //!< pointer to region wise packing generator
    Nalu                            *m_newSPSNalu; //!< pointer to the new SPS nalu
    Nalu                            *m_newPPSNalu; //!< pointer to the new PPS nalu
    uint8_t                         *m_videoIdxInMedia;   //!< pointer to index of video streams in media streams
    param_360SCVP                   *m_360scvpParam;      //!< 360SCVP library initial parameter
    void                            *m_360scvpHandle;     //!< 360SCVP library handle
    TileDef                         *m_tilesInViewport;   //!< the list of tiles inside the viewport
    Param_ViewPortInfo              *m_viewInfo;          //!< pointer to the viewport information for 360SCVP library
    int32_t                         m_tilesNumInViewport; //!< tiles number in viewport
    int32_t                         m_finalViewportWidth;  //!< the final viewport width calculated by 360SCVP library
    int32_t                         m_finalViewportHeight; //!< the final viewport height calculated by 360SCVP library

    uint16_t                        m_origResWidth;       //!< frame width of high resolution video stream
    uint16_t                        m_origResHeight;      //!< frame height of high resolution video stream
    uint8_t                         m_origTileInRow;        //!< the number of high resolution tiles in one row in original picture
    uint8_t                         m_origTileInCol;        //!< the number of high resolution tiles in one column in original picture
    uint16_t                        m_origTileWidth;        //!< the width of high resolution tile
    uint16_t                        m_origTileHeight;       //!< the height of high resolution tile
    TileInfo                        *m_tilesInfo;         //!< pointer to tile information of all tiles in high resolution video stream
    VCD::OMAF::ProjectionFormat     m_projType;           //!< the projection type
    uint32_t                        m_packedPicWidth;     //!< the width of tiles merged picture
    uint32_t                        m_packedPicHeight;    //!< the height of tiles merged picture
    Nalu                            *m_origVPSNalu;       //!< the pointer to original VPS nalu of high resolution video stream
    Nalu                            *m_origSPSNalu;       //!< the pointer to original SPS nalu of high resolution video stream
    Nalu                            *m_origPPSNalu;       //!< the pointer to original PPS nalu of high resolution video stream
};

VCD_NS_END;
#endif /* _EXTRACTORTRACKGENERATOR_H_ */
