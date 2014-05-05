#include "qxjson.h"

#include <QVariant>
#include <QPixmapCache>
#include <QDir>

#include "cocos2d.h"
USING_NS_CC;

#define USING_QT5_JSON 1

#if USING_QT5_JSON == 1
#include <QJsonDocument>
QVariant QxTools::stringToVariant(QString string)
{
    QJsonDocument json = QJsonDocument::fromJson(string.toUtf8());
    return json.toVariant();
}

QString QxTools::variantToString(QVariant data)
{
    QJsonDocument json = QJsonDocument::fromVariant(data);
    return json.toJson();
}

#else
#include "3rd/qt-json/qt-json.h"

QVariant QxTools::stringToVariant(QString string)
{
    return QtJson::parse(string);
}

QString QxTools::variantToString(QVariant data)
{
    return QtJson::serializeStr(data);
}

#endif

static cocos2d::CCImage *createImageFromSprite(cocos2d::CCSprite *sprite)
{
      CCPoint p = sprite->getAnchorPoint();
      sprite->setAnchorPoint(ccp(0,0));
      CCRenderTexture *render = CCRenderTexture::create(sprite->getContentSize().width,sprite->getContentSize().height);
      render->begin();
      sprite->visit();
      render->end();
      sprite->setAnchorPoint(p);
      CCImage *pImage = render->newCCImage( true);
      return pImage;
}

QImage QxTools::createQImageWithSpriteFrameName(QString frameName)
{
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(frameName.toLocal8Bit().constData());
    CCImage *image = createImageFromSprite(sprite);

    return ccimageToQImage(image);
}

QPixmap QxTools::createPixmapWithSpriteFrameName(QString frameName)
{
    static QPixmapCache pixmapCache;

    QPixmap pixmap;
    if (pixmapCache.find(frameName, &pixmap))
    {
        return pixmap;
    }

    pixmap = QPixmap::fromImage(QxTools::createQImageWithSpriteFrameName(frameName));
    pixmapCache.insert(frameName, pixmap);

    return pixmap;
}

bool QxTools::saveScreenshot(QString path)
{
    cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();
    cocos2d::CCRenderTexture *screen = cocos2d::CCRenderTexture::create(size.width, size.height, cocos2d::kCCTexture2DPixelFormat_RGBA8888);

    cocos2d::CCScene* temp = cocos2d::CCDirector::sharedDirector()->getRunningScene();

    // draw
    screen->beginWithClear(0,0,0,255);  // black screen
    temp->visit();
    screen->end();

    // convert to qimage
    cocos2d::CCImage *ccimage = screen->newCCImage(true);

#ifdef Q_OS_WIN
    ccimage->saveToFile( path.toStdString().data(), true);
#else
    QImage retImage = QxTools::ccimageToQImage(ccimage);
    retImage.save(path);
#endif
    CC_SAFE_DELETE(ccimage);
    CC_SAFE_DELETE(screen);

    return true;
}

QString QxTools::getHomeDesktopPath()
{
    return QDir::homePath() + "/Desktop/";
}

QImage QxTools::ccimageToQImage(cocos2d::CCImage *img)
{
    QImage retImg;
    if (img)
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        retImg = QImage(img->getData(), img->getWidth(), img->getHeight(), QImage::Format_RGBA8888);
#else
        retImg = QImage(img->getData(), img->getWidth(), img->getHeight(), QImage::Format_RGB888);
        retImg.invertPixels(QImage::InvertRgba);
#endif
    }
    return retImg;
}

QxTools::QxTools()
{
}
