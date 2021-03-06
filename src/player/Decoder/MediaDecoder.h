/*
 * Copyright (c) 2020, Intel Corporation
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

 *
 */
//!
//! \file     MediaDecoder.h
//! \brief    Defines class for MediaDecoder for decoding.
//!

#ifndef _MEDIADEOCODER_H_
#define _MEDIADEOCODER_H_

#include "../Common.h"
#include "FrameHandler.h"

VCD_NS_BEGIN

class MediaDecoder
{
public:
    MediaDecoder()
    {
        mbEOS = false;
    };
    virtual ~MediaDecoder(){};

public:
     //!
     //! \brief initialize a video decoder based on input information
     //!
     virtual RenderStatus Initialize(int32_t id, Codec_Type codec, FrameHandler* handler) = 0;

     //!
     //! \brief destroy a video decoder
     //!
     virtual RenderStatus Destroy() = 0;

     //!
     //! \brief  reset the decoder when decoding information changes
     //!
     virtual RenderStatus Reset() = 0;

     //!
     //! \brief  udpate frame to destination with the callback class FrameHandler
     //!
     virtual RenderStatus UpdateFrame(uint64_t pts) = 0;

     //!
     //! \brief  send a coded packet to decoder
     //!
     virtual RenderStatus SendPacket(DashPacket* packet) = 0;

     //!
     //! \brief  pending a decoder
     //!
     virtual void Pending() = 0;

     //!
     //! \brief  status of a decoder
     //!
     virtual ThreadStatus GetDecoderStatus() = 0;

     bool GetEOS() { return mbEOS; };
     void SetEOS(bool eos) { mbEOS = eos; };

     virtual bool IsReady() = 0;
private:
    bool mbEOS;
};

VCD_NS_END

#endif /* _MEDIADEOCODER_H_ */
