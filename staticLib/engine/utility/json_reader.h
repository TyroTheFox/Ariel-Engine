#pragma once

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <iostream>

class JSONReader
{
private:
public:
    JSONReader();
    ~JSONReader();
    rapidjson::Document JSONReader::readJSON(std::string path);
};