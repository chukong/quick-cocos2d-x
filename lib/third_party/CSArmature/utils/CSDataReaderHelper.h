/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.cocostudio.com
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

#ifndef COCOSTUDIO_CSDATAREADERHELPER_H
#define COCOSTUDIO_CSDATAREADERHELPER_H

#include "cocos2d.h"
#include "CSDatas.h"
#include "CSConstValue.h"
#include "CSArmature.h"
#include "CSContentJsonDictionary.h"

class TiXmlElement;

namespace cs {


class CS_EXTERN DataReaderHelper
{
    
public:
    /**
	 * Scale the position data, used for multiresolution adapter
     * It won't effect the data already read.         
     */
    static void setPositionReadScale(float scale);
    static float getPositionReadScale();

    static void addDataFromFile(const char *filePath);

	static void clear();
public:
   
#pragma region Decode Data From XML
	/**
	 * Translate XML export from Dragon Bone flash tool to datas, and save them.
	 * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath Path of xml file
     */
    static void addDataFromXML(const char *xmlPath);
    
    /**
	 * Translate XML export from Dragon Bone flash tool to datas, and save them.
	 * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath Path of pak file
     */
    static void addDataFromXMLPak(const char *xmlPakPath);
    
    /**
	 * Translate XML export from Dragon Bone flash tool to datas, and save them.
	 * When you add a new xml, the data already saved will be keeped.
     *
     * @param xmlPath The cache of the xml
     */
    static void addDataFromCache(const char *pFileContent);
    
    
    
    /**
	 * Decode Armature Datas from xml export from Dragon Bone flash tool
     */
	static ArmatureData *decodeArmature(TiXmlElement *armatureXML);
	static BoneData *decodeBone(TiXmlElement *boneXML, TiXmlElement *parentXML);
	static DisplayData *decodeBoneDisplay(TiXmlElement *displayXML);
    
    
	/**
	 * Decode Animation Datas from xml export from Dragon Bone flash tool
     */
	static AnimationData *decodeAnimation(TiXmlElement *animationXML);
	static MovementData *decodeMovement(TiXmlElement *movementXML, ArmatureData *armatureData);
	static MovementBoneData *decodeMovementBone(TiXmlElement* movBoneXml, TiXmlElement* parentXml, BoneData *boneData);
	static FrameData *decodeFrame(TiXmlElement* frameXML, TiXmlElement* parentFrameXml, BoneData *boneData);
    
	
    /**
	 * Decode Texture Datas from xml export from Dragon Bone flash tool
     */
	static TextureData *decodeTexture(TiXmlElement *textureXML);
    
    /**
	 * Decode Contour Datas from xml export from Dragon Bone flash tool
     */
    static ContourData *decodeContour(TiXmlElement *contourXML);
#pragma endregion

#pragma region Decode Data From JSON
    
    static void addDataFromJson(const char *filePath);
	static void addDataFromJsonCache(const char *fileContent);

	static ArmatureData *decodeArmature(CSJsonDictionary &json);
	static BoneData *decodeBone(CSJsonDictionary &json);
	static DisplayData *decodeBoneDisplay(CSJsonDictionary &json);
    
	static AnimationData *decodeAnimation(CSJsonDictionary &json);
	static MovementData *decodeMovement(CSJsonDictionary &json);
	static MovementBoneData *decodeMovementBone(CSJsonDictionary &json);
	static FrameData *decodeFrame(CSJsonDictionary &json);
    
	static TextureData *decodeTexture(CSJsonDictionary &json);
    
    static ContourData *decodeContour(CSJsonDictionary &json);

	static void DecodeNode(Node *node, CSJsonDictionary &json);
	//static std::string convertFlashToSP(const char *fileName);

#pragma endregion

private:
    
    //! a std::vector save the xml file already added
    static std::vector<std::string> m_arrConfigFileList;
    
    static float m_fPositionReadScale;
};

}

#endif