#include "qxjson.h"

#include <QVariant>

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
