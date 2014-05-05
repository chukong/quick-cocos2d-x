/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"
#include <QImage>

NS_CC_BEGIN

/**
@brief    A memory DC which uses to draw text on bitmap.
*/
class BitmapDC
{
public:
    BitmapDC() : m_pPainter(NULL)
      , m_pImage(NULL)
    {
    }

    ~BitmapDC()
    {
        CC_SAFE_DELETE(m_pPainter);
        CC_SAFE_DELETE(m_pImage);
    }

    bool drawText(const char * pszText, QSize& size, CCImage::ETextAlign alignment, const char * pFontName = NULL, int fontSize = 0)
    {
        bool nRet = false;
        do
        {
            CC_BREAK_IF(pszText == NULL || strlen(pszText) <= 0);

            // Set font
            std::string fontName = pFontName;

            if (fontName.c_str())
            {
                int nFindttf = fontName.find(".ttf");
                int nFindTTF = fontName.find(".TTF");
                if (nFindttf >= 0 || nFindTTF >= 0)
                {
                    QFontDatabase::addApplicationFont(fontName.c_str());

                    // delete .ttf suffix from fontName
                    int nFindPos = fontName.rfind("/");
                    fontName = &fontName[nFindPos+1];
                    nFindPos = fontName.rfind(".");
                    fontName = fontName.substr(0, nFindPos);
                }
            }

            int flags = 0;
            switch (alignment)
            {
            case CCImage::kAlignCenter:
                flags = Qt::AlignCenter;
                break;
            case CCImage::kAlignTop:
                flags = Qt::AlignTop;
                break;
            case CCImage::kAlignTopRight:
                flags = Qt::AlignTop | Qt::AlignRight;
                break;
            case CCImage::kAlignRight:
                flags = Qt::AlignRight;
                break;
            case CCImage::kAlignBottomRight:
                flags = Qt::AlignBottom | Qt::AlignRight;
                break;
            case CCImage::kAlignBottom:
                flags = Qt::AlignBottom;
                break;
            case CCImage::kAlignBottomLeft:
                flags = Qt::AlignBottom | Qt::AlignLeft;
                break;
            case CCImage::kAlignLeft:
                flags = Qt::AlignLeft;
                break;
            case CCImage::kAlignTopLeft:
                flags = Qt::AlignTop | Qt::AlignLeft;
                break;
            default:
                flags = Qt::AlignCenter;
                break;
            }

            QRect rect;
            QFont font(fontName.c_str(), fontSize);
            QImage* image = new QImage(100, 100, QImage::Format_ARGB32);
            QPainter painter(image);
            painter.setFont(font);
            rect = painter.boundingRect(rect, flags, pszText);

            // if content width is 0, use text size as content size
            if (size.width() <= 0)
            {
                size.setWidth(rect.width());
                size.setHeight(rect.height());
            }

            QRect drawRect(0, 0, 0, 0);
            drawRect.setRight(rect.width());
            drawRect.setBottom(rect.height());

            m_pImage = new QImage(size, QImage::Format_ARGB32);
            m_pPainter = new QPainter(m_pImage);

            m_pPainter->setCompositionMode(QPainter::CompositionMode_Source);
            m_pPainter->fillRect(drawRect, Qt::transparent);
            m_pPainter->setCompositionMode(QPainter::CompositionMode_SourceOver);

            m_pPainter->setPen(Qt::white);
            m_pPainter->setFont(font);
            m_pPainter->drawText(drawRect, flags, pszText);
            m_pPainter->end();

            nRet = true;
        } while (0);
        return nRet;
    }
private:
    friend class CCImage;

    QPainter* m_pPainter;
    QImage* m_pImage;
};

static BitmapDC& sharedBitmapDC()
{
    static BitmapDC s_BmpDC;
    return s_BmpDC;
}

bool CCImage::initWithString(
                               const char *    pText, 
                               int             nWidth/* = 0*/, 
                               int             nHeight/* = 0*/,
                               ETextAlign      eAlignMask/* = kAlignCenter*/,
                               const char *    pFontName/* = nil*/,
                               int             nSize/* = 0*/)
{
    bool bRet = false;

    do
    {
        int nLen = 0;
        CC_BREAK_IF(! pText);
        BitmapDC& dc = sharedBitmapDC();

        QSize size(nWidth, nHeight);
        bRet = dc.drawText(pText, size, eAlignMask, pFontName, nSize);
        CC_BREAK_IF(!bRet);

        // Qt 5.0
//        nLen = dc.m_pImage->numBytes();
        nLen = dc.m_pImage->byteCount();
        CC_SAFE_DELETE(m_pData);
        m_pData = new uchar [nLen];
        memset(m_pData, 0, nLen);
        CC_BREAK_IF(!m_pData);
        memcpy(m_pData, dc.m_pImage->bits(), nLen);

        m_nWidth = size.width();
        m_nHeight = size.height();
        m_bHasAlpha	= true;
        m_bPreMulti = false;
        m_nBitsPerComponent = 8;

        bRet = true;
    } while(0);

    return bRet;
}

NS_CC_END
