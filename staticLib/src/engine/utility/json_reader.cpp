#include "engine/utility/json_reader.h";

JSONReader::JSONReader()
{
}

JSONReader::~JSONReader()
{
}

rapidjson::Document JSONReader::readJSON(std::string path)
{
    // Open the file for reading
    FILE* fp = fopen(path.c_str(), "r");

    // Use a FileReadStream to
    // read the data from the file
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    // Parse the JSON data 
    // using a Document object
    rapidjson::Document d;
    d.ParseStream(is);

    // Close the file
    fclose(fp);

    return d;
}
