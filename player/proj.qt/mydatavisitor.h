#ifndef MYDATAVISITOR_H
#define MYDATAVISITOR_H

#include "cocos2d.h"

class MyDataVisitor : public cocos2d::CCDataVisitor
{
public:
    MyDataVisitor(int indentLevel = 0);
    ~MyDataVisitor();

    void visitObject(const cocos2d::CCObject *p);

    std::string getResult();

    void clear();

    cocos2d::CCDictionary *getDict();
private:
    cocos2d::CCDictionary *m_data;
};

#endif // MYDATAVISITOR_H
