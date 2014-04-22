#ifndef QXJSON_H
#define QXJSON_H

#include <QImage>

namespace cocos2d {
class CCImage;
}

class QxTools
{
public:
    /* json */
    static QVariant  stringToVariant(QString string);
    static QString   variantToString(QVariant data);

    /* image */
    static QImage    createQImageWithSpriteFrameName(QString frameName);
    static QImage    ccimageToQImage(cocos2d::CCImage *img);
    static QPixmap   createPixmapWithSpriteFrameName(QString frameName);

protected:
    QxTools();
};

#endif // QXJSON_H
