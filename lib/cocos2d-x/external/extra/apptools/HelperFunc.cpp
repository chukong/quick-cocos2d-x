#include "cocos2d.h"
extern "C" {
#include "lua.h"
#include "xxtea.h"
}
#include "CCLuaEngine.h"
#include "HelperFunc.h"


USING_NS_CC;

unsigned char* CZHelperFunc::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned long size;
    unsigned char* buf = CCFileUtils::sharedFileUtils()->getFileData(pszFileName, pszMode, &size);
    if (NULL==buf) {
        return NULL;
    } else if (size < 1) {
        delete []buf;
        return NULL;
    }
    
    CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
    
	unsigned char* buffer;
    if (stack && stack->m_xxteaEnabled && size > stack->m_xxteaSignLen && memcmp(buf, stack->m_xxteaSign, stack->m_xxteaSignLen) == 0) {
        // decrypt XXTEA
        xxtea_long len = 0;
        unsigned char * tbuff;
        tbuff = xxtea_decrypt(buf + stack->m_xxteaSignLen,
                               (xxtea_long)size - (xxtea_long)stack->m_xxteaSignLen,
                               (unsigned char*)stack->m_xxteaKey,
                               (xxtea_long)stack->m_xxteaKeyLen,
                               &len);
        delete []buf;
        buffer = new unsigned char[len];
        memcpy(buffer, tbuff, len);
        free(tbuff);
		size = len;
    } else {
		buffer = buf;
    }

	if (pSize) *pSize = size;
	return buffer;
}

int CZHelperFunc::getFileData(const char *pPathFile)
{
    unsigned long size;
    unsigned char* buf = CZHelperFunc::getFileData(pPathFile, "rb", &size);
    if (NULL==buf) return 0;
    
    CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
	stack->clean();
    stack->pushString((const char*)buf, size);
    delete []buf;
    return 1;
}
