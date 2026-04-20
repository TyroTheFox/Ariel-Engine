#pragma once

#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JSONHandler
{
private:
public:
    JSONHandler();
    ~JSONHandler();
    json readJSON(std::string path);
};

#endif