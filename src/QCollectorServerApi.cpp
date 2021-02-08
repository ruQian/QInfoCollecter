#include "QCollectorServerApi.h"
#include "mirai/third-party/httplib.h"
QCollectorServerApi::QCollectorServerApi()
{
}
bool QCollectorServerApi::PostRawData(const char *path, const std::string &body)
{
    httplib::Client cli("http://cpp-httplib-server.yhirose.repl.co");

    return true;
}

bool QCollectorServerApi::PostQMessageData(const std::string &body)
{
    httplib::Client cli("8.131.255.126", 7001);
    
    auto res = cli.Post("/api/v1/rawcollector", body, "application/json");
    //return true;
    return true;
}



