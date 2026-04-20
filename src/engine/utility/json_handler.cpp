#include <engine/utility/json_handler.h>

JSONHandler::JSONHandler() {}
JSONHandler::~JSONHandler() {}

json JSONHandler::readJSON(std::string path)
{
    std::ifstream f(path);
    json data = json::parse(f);
    f.close();
    return data;
};