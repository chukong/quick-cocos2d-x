#ifndef MYDATAPRITER_H
#define MYDATAPRITER_H

#include "cocos2d.h"
#include <string>

class MyDataPriter : public cocos2d::CCDataVisitor
{
public:
    MyDataPriter(const std::string &flag = "\t", int indentLevel = 0);

    virtual void clear();
    virtual std::string getResult();

    virtual void visitObject(const cocos2d::CCObject *p);
    virtual void visit(const cocos2d::CCBool * p);
    virtual void visit(const cocos2d::CCInteger *p);
    virtual void visit(const cocos2d::CCFloat *p);
    virtual void visit(const cocos2d::CCDouble *p);
    virtual void visit(const cocos2d::CCString *p);
    virtual void visit(const cocos2d::CCArray *p);
    virtual void visit(const cocos2d::CCDictionary *p);
    virtual void visit(const cocos2d::CCSet *p);
private:
    void setIndentLevel(int indentLevel);
    int _indentLevel;
    std::string _indentStrFlag;
    std::string _indentStr;
    std::string _result;
};

#endif // MYDATAPRITER_H
