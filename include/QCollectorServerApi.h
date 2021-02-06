#pragma once
#ifndef QCOLLECTOR_H
#define QCOLLECTOR_H
#include <string>
using namespace std;
class QCollectorServerApi
{
public:
    QCollectorServerApi();
public:
    string mUrl;
public:
    //上传原始信息
    bool PostRawData(const char *path, const std::string &body);


};

#endif










