#include "mydatapriter.h"

USING_NS_CC;
MyDataPriter::MyDataPriter(const std::string &flag/* = "\t"*/, int indentLevel/* = 0 */)
    : _indentStrFlag(flag)
{
    setIndentLevel(indentLevel);
}

void MyDataPriter::clear()
{
    _result.clear();
}

std::string MyDataPriter::getResult()
{
    return _result;
}

void MyDataPriter::visitObject(const CCObject *p)
{
    char buf[50] = {0};
    sprintf(buf, "%p", p);
    _result += buf;
}

void MyDataPriter::visit(const CCBool * p)
{
    char buf[50] = {0};
    sprintf(buf, "%s", p->getValue() ? "true" : "false");
   _result += buf;
}

void MyDataPriter::visit(const CCInteger *p)
{
    char buf[50] = {0};
    sprintf(buf, "%d", p->getValue());
    _result += buf;
}

void MyDataPriter::visit(const CCFloat *p)
{
    char buf[50] = {0};
    sprintf(buf, "%.2f", p->getValue());
    _result += buf;
}

void MyDataPriter::visit(const CCDouble *p)
{
    char buf[50] = {0};
    sprintf(buf, "%.2lf", p->getValue());
    _result += buf;
}

void MyDataPriter::visit(const CCString *p)
{
    _result += p->getCString();
}

void MyDataPriter::visit(const CCArray *p)
{
    _result += "\n";
    _result += _indentStr;
    _result += "<array>\n";

    setIndentLevel(_indentLevel+1);
    CCObject* obj;
    int i = 0;
    char buf[50] = {0};
    CCARRAY_FOREACH(p, obj)
    {
        if (i > 0) {
            _result += "\n";
        }
        sprintf(buf, "%s%02d: ", _indentStr.c_str(), i);
        _result += buf;
        MyDataPriter v(_indentStrFlag, _indentLevel);
        obj->acceptVisitor(v);
        _result += v.getResult();
        i++;
    }
    setIndentLevel(_indentLevel-1);

    _result += "\n";
    _result += _indentStr;
    _result += "</array>";
}

void MyDataPriter::visit(const CCDictionary *p)
{
    _result += "\n";
    _result += _indentStr;
    _result += "<dict>\n";

    setIndentLevel(_indentLevel+1);
    CCDictElement* element;
    bool bFirstElement = true;
    char buf[1000] = {0};
    CCDICT_FOREACH(p, element)
    {
        if (!bFirstElement) {
            _result += "\n";
        }
        sprintf(buf, "%s%s: ", _indentStr.c_str(),element->getStrKey());
        _result += buf;
        MyDataPriter v(_indentStrFlag, _indentLevel);
        element->getObject()->acceptVisitor(v);
        _result += v.getResult();
        bFirstElement = false;
    }
    setIndentLevel(_indentLevel-1);

    _result += "\n";
    _result += _indentStr;
    _result += "</dict>";
}

void MyDataPriter::visit(const CCSet *p)
{
    _result += "\n";
    _result += _indentStr;
    _result += "<set>\n";

    setIndentLevel(_indentLevel+1);

    int i = 0;
    CCSet* tmp = const_cast<CCSet*>(p);
    CCSetIterator it = tmp->begin();

    for (; it != tmp->end(); ++it, ++i) {
        if (i > 0) {
            _result += "\n";
        }
        _result += _indentStr.c_str();
        MyDataPriter v(_indentStrFlag, _indentLevel);
        (*it)->acceptVisitor(v);
        _result += v.getResult();
    }
    setIndentLevel(_indentLevel-1);

    _result += "\n";
    _result += _indentStr;
    _result += "</set>\n";
}

void MyDataPriter::setIndentLevel(int indentLevel)
{
    _indentLevel = indentLevel;
    _indentStr.clear();
    for (int i = 0; i < _indentLevel; ++i) {
        _indentStr += _indentStrFlag;
    }
}
