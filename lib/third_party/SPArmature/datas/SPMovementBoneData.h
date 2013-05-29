/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "SPFrameData.h"

#include "sigslot.h"

namespace sp{


class  MovementBoneData : public CCObject, public JsonData, public sigslot::has_slots<>
{
public:
    static MovementBoneData *createWithJson(const char *_pszDescription);
	static MovementBoneData *create();
public:
	MovementBoneData();
	~MovementBoneData(void);

	virtual bool init();

    virtual bool initWithJson(const char *_pszDescription);
    
    /*
     *  @brief   get data's json value
     *
     */
    Json::Value &getJsonValue();
    
    /*
     *  @brief   update data's json value
     *
     */
    void updateJson();
    
    //! Add a frame data
	FrameData *addFrameData(FrameData *_frameData);
    //! Add a frame data and use a json string to init this data
    FrameData *addFrameData(const char *_pszDescription);
    //! Add a frame data at a certain index 
    FrameData *insertFrameDataAtIndex(int _index, FrameData *_frameData);
    //! Add a frame data at a certain index and use a json string to init this data
    FrameData *insertFrameDataAtIndex(int _index, const char *_pszDescription);
    //! Remove frame data at a certain index
    FrameData *removeFrameData(int _index);
    //! exchange frame datas in two certain index
    void exchangeFrameData(int _index, int _index2);
    
    
    //! get a frame data in a certain index
	FrameData *getFrameData(int _index);
    //! get all the frame datas in this MovementBoneData
	CCArray *getFrameDatas();
    //! get the count of the frame datas in this MovementBoneData
    int getFrameCount();

private:
    void judgeColorChanged(FrameData *_data);
    
private:
	//! movement delay percent, this value can produce a delay effect
    CC_SYNTHESIZE_PASS_BY_REF(float, m_fDelay, Delay)

	//! scale this movement
    CC_SYNTHESIZE_PASS_BY_REF(float, m_fScale, Scale)

	//! this Bone in this movement will last m_iDuration frames
    CC_SYNTHESIZE_PASS_BY_REF(int, m_iDuration, Duration)

    //! bone name
    CC_SYNTHESIZE_PASS_BY_REF(std::string, m_strName, Name)
    
    CC_SYNTHESIZE(bool, m_bUseColorInfo, UseColorInfo)
    CC_SYNTHESIZE(bool, m_bUseScaleInfo, UseScaleInfo)
    CC_SYNTHESIZE(bool, m_bUsePositionInfo, UsePositionInfo)
    CC_SYNTHESIZE(bool, m_bUseRotationInfo, UseRotationInfo)
private:
	CCArray *m_pFrameList;
    
    
//! signal    
public:
    
    sigslot::signal0<> DurationChangedSignal;
    sigslot::signal1<std::string> NameChangedSignal;

//! slot
public:
    void connectFrameDataSignal(FrameData *_frameData);
    void disconnectFrameDataSignal(FrameData *_frameData);
    
    void frameDataDurationChanged(int _preDurantion, int _duration);
};

}