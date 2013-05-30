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

#include "CSDataReaderHelper.h"
#include "tinyxml.h"
#include "CSArmatureDataManager.h"
#include "CSTransformHelp.h"
#include "CSDatas.h"
#include "CSArmatureDefine.h"

using namespace cocos2d;

namespace cs {

	std::vector<std::string> DataReaderHelper::m_arrConfigFileList;
	float DataReaderHelper::m_fPositionReadScale = 1;
	static float s_FlashToolVersion = VERSION_2_0;

	void DataReaderHelper::setPositionReadScale(float scale)
	{
		m_fPositionReadScale = scale;
	}

	float DataReaderHelper::getPositionReadScale()
	{
		return m_fPositionReadScale;
	}
	
	void DataReaderHelper::clear()
	{
		m_arrConfigFileList.clear();
	}

	void DataReaderHelper::addDataFromFile(const char *filePath)
	{
		/*
		* Check if file is already added to ArmatureDataManager, if then return.
		*/
		for(unsigned int i = 0; i<m_arrConfigFileList.size(); i++)
		{
			if (m_arrConfigFileList[i].compare(filePath) == 0)
			{
				return;
			}
		}
		m_arrConfigFileList.push_back(filePath);


		std::string filePathStr = filePath;
		size_t startPos = filePathStr.find_last_of(".");
		std::string str = &filePathStr[startPos];

		if (str.compare(".xml") == 0)
		{

#if CS_TOOL_PLATFORM
			if(Game::sharedGame()->isUsePackage())
			{
				DataReaderHelper::addDataFromXMLPak(filePathStr.c_str());
			}
			else
			{
				DataReaderHelper::addDataFromXML(filePathStr.c_str());
			}
#else
			DataReaderHelper::addDataFromXML(filePathStr.c_str());
#endif
		}
		else if(str.compare(".json") == 0 || str.compare(".ExportJson") == 0)
		{
			DataReaderHelper::addDataFromJson(filePathStr.c_str());
		}
	}


#pragma region Decode Data From XML   

	void DataReaderHelper::addDataFromXML(const char* xmlPath)
	{

		/*
		*  Need to get the full path of the xml file, or the Tiny XML can't find the xml at IOS
		*/
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlPath);

		/*
		*  Need to read the tiny xml into memory first, or the Tiny XML can't find the xml at IOS
		*/
		unsigned long	_size;
		const char *_pFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &_size);

		if (_pFileContent)
		{
			addDataFromCache(_pFileContent);
		}
	}

	void DataReaderHelper::addDataFromXMLPak(const char *xmlPakPath)
	{
#if CS_TOOL_PLATFORM

		char *_pFileContent = NULL;
		JsonReader::getFileBuffer(xmlPakPath, &_pFileContent);

		if (_pFileContent)
		{
			addDataFromCache(_pFileContent);
		}
#endif
	}

	void DataReaderHelper::addDataFromCache(const char *_pFileContent)
	{
		TiXmlDocument document;
		document.Parse(_pFileContent, 0, TIXML_ENCODING_UTF8);

		TiXmlElement	*root = document.RootElement();
		CCAssert(root, "XML error  or  XML is empty.");

		root->QueryFloatAttribute(VERSION, &s_FlashToolVersion);

		/*
		* Begin decode armature data from xml
		*/
		TiXmlElement *armaturesXML = root->FirstChildElement(ARMATURES);
		TiXmlElement *armatureXML = armaturesXML->FirstChildElement(ARMATURE);
		while(armatureXML)
		{
			ArmatureData *armatureData = DataReaderHelper::decodeArmature(armatureXML);
			ArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData);

			armatureXML = armatureXML->NextSiblingElement(ARMATURE);
		}

		/*
		* Begin decode animation data from xml
		*/
		TiXmlElement *animationsXML = root->FirstChildElement(ANIMATIONS);
		TiXmlElement *animationXML = animationsXML->FirstChildElement(ANIMATION);
		while(animationXML)
		{
			AnimationData *animationData = DataReaderHelper::decodeAnimation(animationXML);
			ArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData);

			animationXML = animationXML->NextSiblingElement(ANIMATION);
		}

		/*
		* Begin decode texture data from xml
		*/
		TiXmlElement *texturesXML = root->FirstChildElement(TEXTURE_ATLAS);
		TiXmlElement *textureXML = texturesXML->FirstChildElement(SUB_TEXTURE);
		while(textureXML)
		{
			TextureData *textureData = DataReaderHelper::decodeTexture(textureXML);
			ArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData);

			textureXML = textureXML->NextSiblingElement(SUB_TEXTURE);
		}

		document.Clear();
	}

	ArmatureData *DataReaderHelper::decodeArmature(TiXmlElement *armatureXML)
	{
		const char*	name = armatureXML->Attribute(A_NAME);


		ArmatureData *armatureData = ArmatureData::create();
		armatureData->name = name;


		TiXmlElement* boneXML = armatureXML->FirstChildElement(BONE);

		while( boneXML )
		{
			/*
			*  If this bone have parent, then get the parent bone xml
			*/
			const char *parentName = boneXML->Attribute(A_PARENT);
			TiXmlElement *parentXML = NULL;
			if (parentName)
			{
				parentXML = armatureXML->FirstChildElement(BONE);
				std::string name = parentName;
				while (parentXML)
				{
					if (name.compare(parentXML->Attribute(A_NAME)) == 0)
					{
						break;
					}
					parentXML = parentXML->NextSiblingElement(BONE);
				}
			}

			BoneData *boneData = decodeBone(boneXML, parentXML);
			armatureData->addBoneData(boneData);

			boneXML = boneXML->NextSiblingElement(BONE);
		}

		return armatureData;
	}

	BoneData *DataReaderHelper::decodeBone(TiXmlElement *boneXML, TiXmlElement *parentXml)
	{

		std::string name = boneXML->Attribute(A_NAME);

		CCAssert(name.compare("") != 0, "");


		BoneData *boneData = BoneData::create();

		boneData->name = name;

		if( boneXML->Attribute(A_PARENT) != NULL )
		{
			boneData->parentName = boneXML->Attribute(A_PARENT);
		}

		//     boneXML->QueryFloatAttribute(A_X,		&(boneData->x));
		//     boneXML->QueryFloatAttribute(A_Y,		&(boneData->y));
		//     boneXML->QueryFloatAttribute(A_SKEW_X, &(boneData->skewX));
		//     boneXML->QueryFloatAttribute(A_SKEW_Y, &(boneData->skewY));
		//     boneXML->QueryFloatAttribute(A_SCALE_X,&(boneData->scaleX));
		//     boneXML->QueryFloatAttribute(A_SCALE_Y,&(boneData->scaleY));
		//     boneXML->QueryIntAttribute(A_Z,		&(boneData->m_iZOrder));
		//     
		//     boneXML->QueryIntAttribute(A_ALPHA,	&(boneData->alpha));
		//     boneXML->QueryIntAttribute(A_RED,		&(boneData->red));
		//     boneXML->QueryIntAttribute(A_GREEN,	&(boneData->green));
		//     boneXML->QueryIntAttribute(A_BLUE,		&(boneData->blue));
		//     
		//     // flash export data is a percent value, so wo change it
		//     boneData->alpha *= 2.55;
		//     boneData->red *= 2.55;
		//     boneData->green *= 2.55;
		//     boneData->blue *= 2.55;
		//     
		//     /*
		//      *  Note : Flash's Y value contrary to Cocos2dX's Y value
		//      */
		//     boneData->y = -boneData->y;
		//     
		//     /*
		//      *  Note : Flash export datas are DEGREE values, and our matrix use RADIAN values
		//      */
		//     boneData->skewX = CC_DEGREES_TO_RADIANS(boneData->skewX);
		//     boneData->skewY = CC_DEGREES_TO_RADIANS(-boneData->skewY);
		//     
		//     
		//     if(parentXml)
		//     {
		//         /*
		//          *  recalculate bone data from parent bone data, use for translate matrix
		//          */
		//         Node _helpNode;
		//         parentXml->QueryFloatAttribute(A_X, &_helpNode.x);
		//         parentXml->QueryFloatAttribute(A_Y, &_helpNode.y);
		//         parentXml->QueryFloatAttribute(A_SKEW_X, &_helpNode.skewX);
		//         parentXml->QueryFloatAttribute(A_SKEW_Y, &_helpNode.skewY);
		//         
		//         _helpNode.y = -_helpNode.y;
		//         _helpNode.skewX = CC_DEGREES_TO_RADIANS(_helpNode.skewX);
		//         _helpNode.skewY = CC_DEGREES_TO_RADIANS(-_helpNode.skewY);
		//         
		//         TransformHelp::transformFromParent(*boneData, _helpNode);
		//     }


		TiXmlElement *displayXML = boneXML->FirstChildElement(DISPLAY);
		while(displayXML)
		{
			DisplayData *displayData = decodeBoneDisplay(displayXML);
			boneData->addDisplayData(displayData);

			displayXML = displayXML->NextSiblingElement(DISPLAY);
		}


		return boneData;
	}

	DisplayData *DataReaderHelper::decodeBoneDisplay(TiXmlElement *displayXML)
	{
		int _isArmature = 0;

		DisplayData *displayData;


		if( displayXML->QueryIntAttribute(A_IS_ARMATURE, &(_isArmature)) == TIXML_SUCCESS )
		{
			if(!_isArmature)
			{
				displayData = SpriteDisplayData::create();
				displayData->displayType  = CS_DISPLAY_SPRITE;
			}
			else
			{
				displayData = ArmatureDisplayData::create();
				displayData->displayType  = CS_DISPLAY_ARMATURE;
			}

		}else{
			displayData = SpriteDisplayData::create();
			displayData->displayType  = CS_DISPLAY_SPRITE;
		}

		if(displayXML->Attribute(A_NAME) != NULL )
		{
			if(!_isArmature)
			{
				((SpriteDisplayData*)displayData)->displayName = displayXML->Attribute(A_NAME);
			}
			else
			{
				((ArmatureDisplayData*)displayData)->displayName = displayXML->Attribute(A_NAME);
			}

		}


		return displayData;
	}

	AnimationData *DataReaderHelper::decodeAnimation(TiXmlElement *animationXML)
	{
		const char*	name = animationXML->Attribute(A_NAME);


		AnimationData *aniData =  AnimationData::create();

		ArmatureData *armatureData = ArmatureDataManager::sharedArmatureDataManager()->getArmatureData(name);

		aniData->name = name;

		TiXmlElement* movementXML = animationXML->FirstChildElement(MOVEMENT);

		while( movementXML )
		{
			MovementData *movementData = decodeMovement(movementXML, armatureData);
			aniData->addMovement(movementData);

			movementXML = movementXML->NextSiblingElement(MOVEMENT);

		}

		return aniData;
	}

	MovementData *DataReaderHelper::decodeMovement(TiXmlElement *movementXML, ArmatureData *armatureData)
	{
		const char* _movName = movementXML->Attribute(A_NAME);

		MovementData *movementData = MovementData::create();

		movementData->name = _movName;


		int _duration, _durationTo, _durationTween, _loop, _tweenEasing = 0;

		if( movementXML->QueryIntAttribute(A_DURATION, &(_duration)) == TIXML_SUCCESS)
		{
			movementData->duration  = _duration;
		}
		if( movementXML->QueryIntAttribute(A_DURATION_TO, &(_durationTo)) == TIXML_SUCCESS)
		{
			movementData->durationTo = _durationTo;
		}
		if( movementXML->QueryIntAttribute(A_DURATION_TWEEN, &(_durationTween)) == TIXML_SUCCESS)
		{
			movementData->durationTween = _durationTween;
		}
		if( movementXML->QueryIntAttribute(A_LOOP, &(_loop)) == TIXML_SUCCESS)
		{
			movementData->loop = (bool)_loop;
		}

		const char * _easing= movementXML->Attribute(A_TWEEN_EASING);
		if(_easing != NULL)
		{
			std::string str = _easing;
			if(str.compare(FL_NAN) != 0)
			{
				if( movementXML->QueryIntAttribute(A_TWEEN_EASING, &(_tweenEasing)) == TIXML_SUCCESS)
				{
					movementData->tweenEasing = (TweenType)_tweenEasing;
				}
			}else{
				movementData->tweenEasing  = TWEEN_EASING_MAX;
			}
		}

		TiXmlElement *movBoneXml = movementXML->FirstChildElement(BONE);
		while(movBoneXml)
		{
			const char* _boneName = movBoneXml->Attribute(A_NAME);

			if (movementData->getMovementBoneData(_boneName))
			{
				movBoneXml = movBoneXml->NextSiblingElement();
				continue;
			}


			BoneData *boneData = (BoneData*)armatureData->getBoneData(_boneName);

			std::string _parentName = boneData->parentName;


			TiXmlElement *parentXml = NULL;
			if (_parentName.compare("") != 0)
			{
				parentXml = movementXML->FirstChildElement(BONE);

				while (parentXml)
				{
					if (_parentName.compare(parentXml->Attribute(A_NAME)) == 0)
					{
						break;
					}
					parentXml = parentXml->NextSiblingElement(BONE);
				}
			}

			MovementBoneData *_moveBoneData = decodeMovementBone(movBoneXml, parentXml, boneData);
			movementData->addMovementBoneData(_moveBoneData);

			movBoneXml = movBoneXml->NextSiblingElement(BONE);
		}

		return movementData;
	}


	MovementBoneData *DataReaderHelper::decodeMovementBone(TiXmlElement* movBoneXml, TiXmlElement* parentXml, BoneData *boneData)
	{
		MovementBoneData* movBoneData = MovementBoneData::create();
		float _scale, _delay;

		if( movBoneXml )
		{
			if( movBoneXml->QueryFloatAttribute(A_MOVEMENT_SCALE, &_scale) == TIXML_SUCCESS )
			{
				movBoneData->scale = _scale;
			}
			if( movBoneXml->QueryFloatAttribute(A_MOVEMENT_DELAY, &_delay) == TIXML_SUCCESS )
			{
				if(_delay > 0)
				{
					_delay -= 1;
				}
				movBoneData->delay = _delay;
			}
		}

		int _length = 0;
		int _i = 0;
		int _parentTotalDuration = 0;
		int _currentDuration = 0;

		TiXmlElement *parentFrameXML = NULL;

		std::vector<TiXmlElement*> parentXmlList;

		/*
		*  get the parent frame xml list, we need get the origin data
		*/
		if( parentXml != NULL )
		{
			parentFrameXML = parentXml->FirstChildElement(FRAME);
			while (parentFrameXML)
			{
				parentXmlList.push_back(parentFrameXML);
				parentFrameXML = parentFrameXML->NextSiblingElement(FRAME);
			}

			parentFrameXML = NULL;

			_length = parentXmlList.size();
		}


		int _totalDuration =0;

		std::string name = movBoneXml->Attribute(A_NAME);

		movBoneData->name = name;

		TiXmlElement *frameXML= movBoneXml->FirstChildElement(FRAME);

		while( frameXML )
		{
			if(parentXml)
			{
				/*
				*  in this loop we get the corresponding parent frame xml
				*/
				while(_i < _length && (parentFrameXML?(_totalDuration < _parentTotalDuration || _totalDuration >= _parentTotalDuration + _currentDuration):true))
				{
					parentFrameXML = parentXmlList[_i];
					_parentTotalDuration += _currentDuration;
					parentFrameXML->QueryIntAttribute(A_DURATION, &_currentDuration);
					_i++;

				}
			}

			FrameData * _frameData = decodeFrame( frameXML, parentFrameXML, boneData);
			movBoneData->addFrameData(_frameData);

			_totalDuration += _frameData->duration;

			frameXML = frameXML->NextSiblingElement(FRAME);
		}


		return movBoneData;
	}

	FrameData * DataReaderHelper::decodeFrame(TiXmlElement* frameXML,  TiXmlElement* parentFrameXml, BoneData *boneData)
	{
		float _x, _y, _scale_x, _scale_y, _skew_x, _skew_y = 0;
		int _duration, _displayIndex, _zOrder, _tweenEasing = 0;

		FrameData* frameData = FrameData::create();


		if(frameXML->Attribute(A_MOVEMENT) != NULL)
		{
			frameData->m_strMovement = frameXML->Attribute(A_MOVEMENT);
		}
		if(frameXML->Attribute(A_EVENT) != NULL)
		{
			frameData->m_strEvent = frameXML->Attribute(A_EVENT);
		}
		if(frameXML->Attribute(A_SOUND) != NULL)
		{
			frameData->m_strSound = frameXML->Attribute(A_SOUND);
		}
		if(frameXML->Attribute(A_SOUND_EFFECT) != NULL)
		{
			frameData->m_strSoundEffect = frameXML->Attribute(A_SOUND_EFFECT);
		}



		if (s_FlashToolVersion >= VERSION_2_0)
		{
			if(frameXML->QueryFloatAttribute(A_COCOS2DX_X, &_x) == TIXML_SUCCESS)
			{
				frameData->x = _x;
				frameData->x *= m_fPositionReadScale;
			}
			if(frameXML->QueryFloatAttribute(A_COCOS2DX_Y, &_y) == TIXML_SUCCESS)
			{
				frameData->y = -_y;
				frameData->y *= m_fPositionReadScale;
			}
		}
		else
		{
			if(frameXML->QueryFloatAttribute(A_X, &_x) == TIXML_SUCCESS)
			{
				frameData->x = _x;
				frameData->x *= m_fPositionReadScale;
			}
			if(frameXML->QueryFloatAttribute(A_Y, &_y) == TIXML_SUCCESS)
			{
				frameData->y = -_y;
				frameData->y *= m_fPositionReadScale;
			}
		}

		if( frameXML->QueryFloatAttribute(A_SCALE_X, &_scale_x) == TIXML_SUCCESS )
		{
			frameData->scaleX = _scale_x;
		}
		if( frameXML->QueryFloatAttribute(A_SCALE_Y, &_scale_y) == TIXML_SUCCESS )
		{
			frameData->scaleY = _scale_y;
		}
		if( frameXML->QueryFloatAttribute(A_SKEW_X, &_skew_x) == TIXML_SUCCESS )
		{
			frameData->skewX = CC_DEGREES_TO_RADIANS(_skew_x);
		}
		if( frameXML->QueryFloatAttribute(A_SKEW_Y, &_skew_y) == TIXML_SUCCESS )
		{
			frameData->skewY = CC_DEGREES_TO_RADIANS(-_skew_y);
		}
		if( frameXML->QueryIntAttribute(A_DURATION, &_duration) == TIXML_SUCCESS )
		{
			frameData->duration = _duration;
		}
		if(  frameXML->QueryIntAttribute(A_DISPLAY_INDEX, &_displayIndex) == TIXML_SUCCESS )
		{
			frameData->displayIndex = _displayIndex;
		}
		if(  frameXML->QueryIntAttribute(A_Z, &_zOrder) == TIXML_SUCCESS )
		{
			frameData->zOrder = _zOrder;
		}


		TiXmlElement *colorTransformXML = frameXML->FirstChildElement(A_COLOR_TRANSFORM);
		if (colorTransformXML)
		{
			int alpha, red, green, blue = 100;
			int alphaOffset, redOffset, greenOffset, blueOffset = 0;

			colorTransformXML->QueryIntAttribute(A_ALPHA, &alpha);
			colorTransformXML->QueryIntAttribute(A_RED, &red);
			colorTransformXML->QueryIntAttribute(A_GREEN, &green);
			colorTransformXML->QueryIntAttribute(A_BLUE, &blue) ;

			colorTransformXML->QueryIntAttribute(A_ALPHA_OFFSET, &alphaOffset);
			colorTransformXML->QueryIntAttribute(A_RED_OFFSET, &redOffset);
			colorTransformXML->QueryIntAttribute(A_GREEN_OFFSET, &greenOffset);
			colorTransformXML->QueryIntAttribute(A_BLUE_OFFSET, &blueOffset) ;

			frameData->a = 2.55 * alphaOffset +alpha;
			frameData->r = 2.55 * redOffset + red;
			frameData->g = 2.55 * greenOffset + green;
			frameData->b = 2.55 * blueOffset + blue;

			frameData->isUseColorInfo = true;
		}


		const char * _easing= frameXML->Attribute(A_TWEEN_EASING);
		if(_easing != NULL)
		{
			std::string str = _easing;
			if(str.compare(FL_NAN) != 0)
			{
				if( frameXML->QueryIntAttribute(A_TWEEN_EASING, &(_tweenEasing)) == TIXML_SUCCESS)
				{
					frameData->tweenEasing = (TweenType)_tweenEasing;
				}
			}else{
				frameData->tweenEasing  = TWEEN_EASING_MAX;
			}
		}

		if(parentFrameXml)
		{
			/*
			*  recalculate frame data from parent frame data, use for translate matrix
			*/
			Node _helpNode;
			if (s_FlashToolVersion >= VERSION_2_0)
			{
				parentFrameXml->QueryFloatAttribute(A_COCOS2DX_X, &_helpNode.x);
				parentFrameXml->QueryFloatAttribute(A_COCOS2DX_Y, &_helpNode.y);
			}
			else
			{
				parentFrameXml->QueryFloatAttribute(A_X, &_helpNode.x);
				parentFrameXml->QueryFloatAttribute(A_Y, &_helpNode.y);
			}
			

			parentFrameXml->QueryFloatAttribute(A_SKEW_X, &_helpNode.skewX);
			parentFrameXml->QueryFloatAttribute(A_SKEW_Y, &_helpNode.skewY);

			_helpNode.y = -_helpNode.y;
			_helpNode.skewX = CC_DEGREES_TO_RADIANS(_helpNode.skewX);
			_helpNode.skewY = CC_DEGREES_TO_RADIANS(-_helpNode.skewY);

			TransformHelp::transformFromParent(*frameData, _helpNode);
		}

		//    frameData->x -= boneData->x;
		//    frameData->y -= boneData->y;
		//    frameData->skewX -= boneData->skewX;
		//    frameData->skewY -= boneData->skewY;


		return frameData;
	}

	TextureData *DataReaderHelper::decodeTexture(TiXmlElement *textureXML)
	{
		TextureData *textureData = TextureData::create();

		if( textureXML->Attribute(A_NAME) != NULL)
		{
			textureData->name = textureXML->Attribute(A_NAME);
		}

		float px, py, width, height = 0;

		if(s_FlashToolVersion >= VERSION_2_0)
		{
			textureXML->QueryFloatAttribute(A_COCOS2D_PIVOT_X, &px);
			textureXML->QueryFloatAttribute(A_COCOS2D_PIVOT_Y, &py);
		}
		else
		{
			textureXML->QueryFloatAttribute(A_PIVOT_X, &px);
			textureXML->QueryFloatAttribute(A_PIVOT_Y, &py);
		}
		
		
		textureXML->QueryFloatAttribute(A_WIDTH, &width);
		textureXML->QueryFloatAttribute(A_HEIGHT, &height);

		float anchorPointX = px / width;
		float anchorPointY = (height - py) / height;

		textureData->pivotX = anchorPointX;
		textureData->pivotY = anchorPointY;

		TiXmlElement *contourXML = textureXML->FirstChildElement(CONTOUR);

		while (contourXML) {

			ContourData *contourData = decodeContour(contourXML);
			textureData->addContourData(contourData);

			contourXML = contourXML->NextSiblingElement(CONTOUR);
		}


		return textureData;
	}

	ContourData *DataReaderHelper::decodeContour(TiXmlElement *contourXML)
	{
		ContourData *contourData = ContourData::create();

		TiXmlElement *vertexDataXML = contourXML->FirstChildElement(CONTOUR_VERTEX);

		while (vertexDataXML) {

			ContourVertex2 *vertex = new ContourVertex2(0, 0);
			vertex->autorelease();

			vertexDataXML->QueryFloatAttribute(A_X, &vertex->x);
			vertexDataXML->QueryFloatAttribute(A_Y, &vertex->y);

			vertex->y = -vertex->y;
			contourData->vertexList.addObject(vertex);

			vertexDataXML = vertexDataXML->NextSiblingElement(CONTOUR_VERTEX);
		}


		return contourData;

	}
#pragma endregion


#pragma region Decode Data From JSON

	void DataReaderHelper::addDataFromJson(const char *filePath)
	{
		unsigned long size;
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filePath);
		const char *pFileContent = (char*)CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str() , "r", &size);

		addDataFromJsonCache(pFileContent);
	}


	void DataReaderHelper::addDataFromJsonCache(const char *fileContent)
	{
		CSJsonDictionary json;
		json.initWithDescription(fileContent);

		// Decode armatures
		int length = json.getArrayItemCount(ARMATURE_DATA);
		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *armatureDic = json.getSubItemFromArray(ARMATURE_DATA, i);
			ArmatureData *armatureData = decodeArmature(*armatureDic);
			ArmatureDataManager::sharedArmatureDataManager()->addArmatureData(armatureData->name.c_str(), armatureData);

			delete armatureDic;
		}

		// Decode animations
		length = json.getArrayItemCount(ANIMATION_DATA);
		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *animationDic = json.getSubItemFromArray(ANIMATION_DATA, i);
			AnimationData *animationData = decodeAnimation(*animationDic);
			ArmatureDataManager::sharedArmatureDataManager()->addAnimationData(animationData->name.c_str(), animationData);

			delete animationDic;
		}

		// Decode textures
		length = json.getArrayItemCount(TEXTURE_DATA);
		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *textureDic = json.getSubItemFromArray(TEXTURE_DATA, i);
			TextureData *textureData = decodeTexture(*textureDic);
			ArmatureDataManager::sharedArmatureDataManager()->addTextureData(textureData->name.c_str(), textureData);

			delete textureDic;
		}


	}

	ArmatureData *DataReaderHelper::decodeArmature(CSJsonDictionary &json)
	{
		ArmatureData *armatureData = ArmatureData::create();

		const char * name = json.getItemStringValue(A_NAME);
		if(name != NULL)
		{
			armatureData->name = name;
		}

		int length = json.getArrayItemCount(BONE_DATA);
		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *dic = json.getSubItemFromArray(BONE_DATA, i);
			armatureData->addBoneData(decodeBone(*dic));

			delete dic;
		}

		return armatureData;
	}

	BoneData *DataReaderHelper::decodeBone(CSJsonDictionary &json)
	{
		BoneData *boneData = BoneData::create();

		DecodeNode(boneData, json);

		const char * str = json.getItemStringValue(A_NAME);
		if(str != NULL)
		{
			boneData->name = str;
		}

		str = json.getItemStringValue(A_PARENT);
		if(str != NULL)
		{
			boneData->parentName = str;
		}

		int length = json.getArrayItemCount(DISPLAY_DATA);

		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *dic = json.getSubItemFromArray(DISPLAY_DATA, i);
			boneData->addDisplayData(decodeBoneDisplay(*dic));

			delete dic;
		}

		return boneData;
	}

	DisplayData *DataReaderHelper::decodeBoneDisplay(CSJsonDictionary &json)
	{
		DisplayType displayType = (DisplayType)json.getItemIntValue(A_DISPLAY_TYPE, CS_DISPLAY_SPRITE);

		DisplayData *displayData = NULL;

		switch (displayType) {
		case CS_DISPLAY_SPRITE:
			{
				displayData = SpriteDisplayData::create();
				const char *name = json.getItemStringValue(A_NAME);
				if(name != NULL)
				{
					((SpriteDisplayData*)displayData)->displayName = name;
				}
			}

			break;
		case CS_DISPLAY_ARMATURE:
			{
				displayData = ArmatureDisplayData::create();
				const char *name = json.getItemStringValue(A_NAME);
				if(name != NULL)
				{
					((ArmatureDisplayData*)displayData)->displayName = name;
				}
			}
			break;
		case CS_DISPLAY_PARTICLE:
			{
				displayData = ParticleDisplayData::create();
				const char *plist = json.getItemStringValue(A_PLIST);
				if(plist != NULL)
				{
					((ParticleDisplayData*)displayData)->plist = plist;
				}
			}
			break;
		case CS_DISPLAY_SHADER:
			{
				displayData = ShaderDisplayData::create();
				const char *vert = json.getItemStringValue(A_VERT);
				if(vert != NULL)
				{
					((ShaderDisplayData*)displayData)->vert = vert;
				}

				const char *frag = json.getItemStringValue(A_FRAG);
				if(frag != NULL)
				{
					((ShaderDisplayData*)displayData)->frag = vert;
				}

			}
			break;
		default:
			displayData = SpriteDisplayData::create();
			break;
		}

		displayData->displayType = displayType;

		return displayData;
	}

	AnimationData *DataReaderHelper::decodeAnimation(CSJsonDictionary &json)
	{
		AnimationData *aniData = AnimationData::create();

		const char * name = json.getItemStringValue(A_NAME);
		if(name != NULL)
		{
			aniData->name = name;
		}

		int length = json.getArrayItemCount(MOVEMENT_DATA);

		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *dic = json.getSubItemFromArray(MOVEMENT_DATA, i);
			aniData->addMovement(decodeMovement(*dic));

			delete dic;
		}

		return aniData;
	}

	MovementData *DataReaderHelper::decodeMovement(CSJsonDictionary &json)
	{
		MovementData *movementData = MovementData::create();

		movementData->loop = json.getItemBoolvalue(A_LOOP, true);
		movementData->durationTween = json.getItemIntValue(A_DURATION_TWEEN, 0);
		movementData->durationTo = json.getItemIntValue(A_DURATION_TO, 0);
		movementData->duration = json.getItemIntValue(A_DURATION, 0);
		movementData->tweenEasing = (TweenType)json.getItemIntValue(A_TWEEN_EASING, Linear);

		const char *name = json.getItemStringValue(A_NAME);
		if(name != NULL)
		{
			movementData->name = name;
		}

		int length = json.getArrayItemCount(MOVEMENT_BONE_DATA);
		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *dic = json.getSubItemFromArray(MOVEMENT_BONE_DATA, i);
			movementData->addMovementBoneData(decodeMovementBone(*dic));

			delete dic;
		}

		return movementData;
	}

	MovementBoneData *DataReaderHelper::decodeMovementBone(CSJsonDictionary &json)
	{
		MovementBoneData *movementBoneData = MovementBoneData::create();

		movementBoneData->delay = json.getItemFloatValue(A_MOVEMENT_DELAY, 0);
		movementBoneData->scale = json.getItemFloatValue(A_MOVEMENT_SCALE, 1);

		const char *name = json.getItemStringValue(A_NAME);
		if(name != NULL)
		{
			movementBoneData->name = name;
		}

		int length = json.getArrayItemCount(FRAME_DATA);
		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *dic = json.getSubItemFromArray(FRAME_DATA, i);
			FrameData *frameData = decodeFrame(*dic);
			movementBoneData->addFrameData(frameData);
			//movementBoneData->duration += frameData->duration;

			delete dic;
		}

		return movementBoneData;
	}

	FrameData *DataReaderHelper::decodeFrame(CSJsonDictionary &json)
	{
		FrameData *frameData = FrameData::create();

		DecodeNode(frameData, json);

		frameData->duration = json.getItemIntValue(A_DURATION, 1);
		frameData->tweenEasing = (TweenType)json.getItemIntValue(A_TWEEN_EASING, Linear);
		frameData->displayIndex = json.getItemIntValue(A_DISPLAY_INDEX, 0);

		const char *event= json.getItemStringValue(A_EVENT);
		if (event != NULL)
		{
			frameData->m_strEvent = event;
		}

		return frameData;
	}

	TextureData *DataReaderHelper::decodeTexture(CSJsonDictionary &json)
	{
		TextureData *textureData = TextureData::create();

		const char *name = json.getItemStringValue(A_NAME);
		if(name != NULL)
		{
			textureData->name = name;
		}

		textureData->width = json.getItemFloatValue(A_WIDTH, 0);
		textureData->height = json.getItemFloatValue(A_HEIGHT, 0);
		textureData->pivotX = json.getItemFloatValue(A_PIVOT_X, 0);
		textureData->pivotY = json.getItemFloatValue(A_PIVOT_Y, 0);

		int length = json.getArrayItemCount(CONTOUR_DATA);
		for (int i = 0; i<length; i++)
		{
			CSJsonDictionary *dic = json.getSubItemFromArray(CONTOUR_DATA, i);
			textureData->contourDataList.addObject(decodeContour(*dic));

			delete dic;
		}

		return textureData;
	}

	ContourData *DataReaderHelper::decodeContour(CSJsonDictionary &json)
	{
		ContourData *contourData = ContourData::create();

		int length = json.getArrayItemCount(VERTEX_POINT);
		for (int i = length - 1; i>=0; i--)
		{
			CSJsonDictionary *dic = json.getSubItemFromArray(VERTEX_POINT, i);

			ContourVertex2 *vertex = new ContourVertex2(0, 0);

			vertex->x = dic->getItemFloatValue(A_X, 0);
			vertex->y = dic->getItemFloatValue(A_Y, 0);

			contourData->vertexList.addObject(vertex);
			vertex->release();
		
			delete dic;
		}

		return contourData;
	}

	void DataReaderHelper::DecodeNode(Node *node, CSJsonDictionary &json)
	{
		node->x = json.getItemFloatValue(A_X, 0) * m_fPositionReadScale;
		node->y = json.getItemFloatValue(A_Y, 0) * m_fPositionReadScale;
		node->zOrder = json.getItemIntValue(A_Z, 0);

		node->skewX = json.getItemFloatValue(A_SKEW_X, 0);
		node->skewY = json.getItemFloatValue(A_SKEW_Y, 0);
		node->scaleX = json.getItemFloatValue(A_SCALE_X, 1);
		node->scaleY = json.getItemFloatValue(A_SCALE_Y, 1);


		CSJsonDictionary *colorDic = json.getSubItemFromArray(COLOR_INFO, 0);

		if (colorDic)
		{
			node->a = colorDic->getItemIntValue(A_ALPHA, 255);
			node->r = colorDic->getItemIntValue(A_RED, 255);
			node->g = colorDic->getItemIntValue(A_GREEN, 255);
			node->b = colorDic->getItemIntValue(A_BLUE, 255);

			node->isUseColorInfo = true;
			
			delete colorDic;
		}

	}
#pragma endregion

}