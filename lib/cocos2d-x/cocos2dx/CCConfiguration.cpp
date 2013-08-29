/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCConfiguration.h"
#include "ccMacros.h"
#include "ccConfig.h"
#include <string.h>

using namespace std;

NS_CC_BEGIN

CCConfiguration* CCConfiguration::s_gSharedConfiguration = NULL;

CCConfiguration::CCConfiguration(void)
: m_nMaxTextureSize(0) 
, m_nMaxModelviewStackDepth(0)
, m_nMaxTextureUnits(0)
, m_bSupportsPVRTC(false)
, m_bSupportsNPOT(false)
, m_bSupportsBGRA8888(false)
, m_bSupportsShareableVAO(false)
, m_bSupportsDiscardFramebuffer(false)
, m_nMaxSamplesAllowed(0)
, m_pGlExtensions(NULL)
{
}

bool CCConfiguration::init(void)
{
    CCLOG("cocos2d: GL_VENDOR:     %s", glGetString(GL_VENDOR));
    CCLOG("cocos2d: GL_RENDERER:   %s", glGetString(GL_RENDERER));
    CCLOG("cocos2d: GL_VERSION:    %s", glGetString(GL_VERSION));

    m_pGlExtensions = (char *)glGetString(GL_EXTENSIONS);

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_nMaxTextureSize);
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_nMaxTextureUnits);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    glGetIntegerv(GL_MAX_SAMPLES_APPLE, &m_nMaxSamplesAllowed);
#endif

    m_bSupportsPVRTC = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
    m_bSupportsNPOT = true;
    m_bSupportsBGRA8888 = checkForGLExtension("GL_IMG_texture_format_BGRA888");
    m_bSupportsDiscardFramebuffer = checkForGLExtension("GL_EXT_discard_framebuffer");

    m_bSupportsShareableVAO = checkForGLExtension("vertex_array_object");

    CCLOG("cocos2d: GL_MAX_TEXTURE_SIZE: %d", m_nMaxTextureSize);
    CCLOG("cocos2d: GL_MAX_TEXTURE_UNITS: %d",m_nMaxTextureUnits);
    CCLOG("cocos2d: GL supports PVRTC: %s", (m_bSupportsPVRTC ? "YES" : "NO"));
    CCLOG("cocos2d: GL supports BGRA8888 textures: %s", (m_bSupportsBGRA8888 ? "YES" : "NO"));
    CCLOG("cocos2d: GL supports NPOT textures: %s", (m_bSupportsNPOT ? "YES" : "NO"));
    CCLOG("cocos2d: GL supports discard_framebuffer: %s", (m_bSupportsDiscardFramebuffer ? "YES" : "NO"));
    CCLOG("cocos2d: GL supports shareable VAO: %s", (m_bSupportsShareableVAO ? "YES" : "NO") );

    bool bEnableProfilers = false;

#if CC_ENABLE_PROFILERS
    bEnableProfilers = true;
#else
	bEnableProfilers = false;
#endif

    CCLOG("cocos2d: compiled with Profiling Support: %s",
        bEnableProfilers ? "YES - *** Disable it when you finish profiling ***" : "NO");
    
#if CC_ENABLE_GL_STATE_CACHE == 0
    CCLOG("");
    CCLOG("cocos2d: **** WARNING **** CC_ENABLE_GL_STATE_CACHE is disabled. To improve performance, enable it by editing ccConfig.h");
    printf("\n");
#endif
    
    CHECK_GL_ERROR_DEBUG();

    return true;
}

CCConfiguration* CCConfiguration::sharedConfiguration(void)
{
    if (! s_gSharedConfiguration)
    {
        s_gSharedConfiguration = new CCConfiguration();
        s_gSharedConfiguration->init();
    }
    
    return s_gSharedConfiguration;
}

void CCConfiguration::purgeConfiguration(void)
{
    CC_SAFE_RELEASE_NULL(s_gSharedConfiguration);
}

bool CCConfiguration::checkForGLExtension(const string &searchName)
{
    bool bRet = false;
    const char *kSearchName = searchName.c_str();
    
    if (m_pGlExtensions && 
        strstr(m_pGlExtensions, kSearchName))
    {
        bRet = true;
    }
    
    return bRet;
}

//
// getters for specific variables.
// Mantained for backward compatiblity reasons only.
//
int CCConfiguration::getMaxTextureSize(void) const
{
	return m_nMaxTextureSize;
}

int CCConfiguration::getMaxModelviewStackDepth(void) const
{
	return m_nMaxModelviewStackDepth;
}

int CCConfiguration::getMaxTextureUnits(void) const
{
	return m_nMaxTextureUnits;
}

bool CCConfiguration::supportsNPOT(void) const
{
	return m_bSupportsNPOT;
}

bool CCConfiguration::supportsPVRTC(void) const
{
	return m_bSupportsPVRTC;
}

bool CCConfiguration::supportsBGRA8888(void) const
{
	return m_bSupportsBGRA8888;
}

bool CCConfiguration::supportsDiscardFramebuffer(void) const
{
	return m_bSupportsDiscardFramebuffer;
}

bool CCConfiguration::supportsShareableVAO(void) const
{
	return m_bSupportsShareableVAO;
}

//
// generic getters for properties
//
const char *CCConfiguration::getCString( const char *key, const char *default_value ) const
{
	CCObject *ret = m_pValueDict->objectForKey(key);
	if( ret ) {
		if( CCString *str=dynamic_cast<CCString*>(ret) )
			return str->getCString();

		CCAssert(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

/** returns the value of a given key as a boolean */
bool CCConfiguration::getBool( const char *key, bool default_value ) const
{
	CCObject *ret = m_pValueDict->objectForKey(key);
	if( ret ) {
		if( CCBool *boolobj=dynamic_cast<CCBool*>(ret) )
			return boolobj->getValue();
		if( CCString *strobj=dynamic_cast<CCString*>(ret) )
			return strobj->boolValue();
		CCAssert(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

/** returns the value of a given key as a double */
double CCConfiguration::getNumber( const char *key, double default_value ) const
{
	CCObject *ret = m_pValueDict->objectForKey(key);
	if( ret ) {
		if( CCDouble *obj=dynamic_cast<CCDouble*>(ret) )
			return obj->getValue();

		if( CCInteger *obj=dynamic_cast<CCInteger*>(ret) )
			return obj->getValue();

		if( CCString *strobj=dynamic_cast<CCString*>(ret) )
			return strobj->doubleValue();

		CCAssert(false, "Key found, but from different type");
	}

	// XXX: Should it throw an exception ?
	return default_value;
}

CCObject * CCConfiguration::getObject( const char *key ) const
{
	return m_pValueDict->objectForKey(key);
}

void CCConfiguration::setObject( const char *key, CCObject *value )
{
	m_pValueDict->setObject(value, key);
}


//
// load file
//
void CCConfiguration::loadConfigFile( const char *filename )
{
	CCDictionary *dict = CCDictionary::createWithContentsOfFile(filename);
	CCAssert(dict, "cannot create dictionary");

	// search for metadata
	bool metadata_ok = false;
	CCObject *metadata = dict->objectForKey("metadata");
	if( metadata && dynamic_cast<CCDictionary*>(metadata) ) {
		CCObject *format_o = static_cast<CCDictionary*>(metadata)->objectForKey("format");

		// XXX: cocos2d-x returns CCStrings when importing from .plist. This bug will be addressed in cocos2d-x v3.x
		if( format_o && dynamic_cast<CCString*>(format_o) ) {
			int format = static_cast<CCString*>(format_o)->intValue();

			// Support format: 1
			if( format == 1 ) {
				metadata_ok = true;
			}
		}
	}

	if( ! metadata_ok ) {
		CCLOG("Invalid config format for file: %s", filename);
		return;
	}

	CCObject *data = dict->objectForKey("data");
	if( !data || !dynamic_cast<CCDictionary*>(data) ) {
		CCLOG("Expected 'data' dict, but not found. Config file: %s", filename);
		return;
	}

	// Add all keys in the existing dictionary
	CCDictionary *data_dict = static_cast<CCDictionary*>(data);
    CCDictElement* element;
    CCDICT_FOREACH(data_dict, element)
    {
		if( ! m_pValueDict->objectForKey( element->getStrKey() ) )
			m_pValueDict->setObject(element->getObject(), element->getStrKey() );
		else
			CCLOG("Key already present. Ignoring '%s'", element->getStrKey() );
    }
    
    CCDirector::sharedDirector()->setDefaultValues();
}

NS_CC_END
