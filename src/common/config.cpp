#include "common/config.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <json/reader.h>
#include <json/writer.h>

Config::Config()
{
    edge_threshold = 0.02;
    aliasing_samples = 5;
    enable_texture_filtering = true;
    hightlight_exponent = 50;
    photon_number = 1e7;
    photon_samples = 1e3;
    photon_tracing_max_depth = 20;
    raytracing_max_depth = 20;
    raytracing_min_weight = 0.05;
    soft_shadow_samples = 4;
}

void Config::load(const Json::Value& config)
{
    edge_threshold          = config["edge_threshold"].asDouble()       ;
    aliasing_samples        = config["aliasing_samples"].asInt()        ;
    enable_texture_filtering=config["enable_texture_filtering"].asBool();
    hightlight_exponent     = config["hightlight_exponent"].asInt()     ;
    photon_number           = config["photon_number"].asInt()           ;
    photon_samples          = config["photon_samples"].asInt()          ;
    photon_tracing_max_depth= config["photon_tracing_max_depth"].asInt();
    raytracing_max_depth    = config["raytracing_max_depth"].asInt()    ;
    raytracing_min_weight   = config["raytracing_min_weight"].asDouble();
    soft_shadow_samples     = config["soft_shadow_samples"].asInt()     ;
}

Json::Value Config::toJson()
{
    Json::Value config;
    config["edge_threshold"]           = edge_threshold          ;
    config["aliasing_samples"]         = aliasing_samples        ;
    config["enable_texture_filtering"] = enable_texture_filtering;
    config["hightlight_exponent"]      = hightlight_exponent     ;
    config["photon_number"]            = photon_number           ;
    config["photon_samples"]           = photon_samples          ;
    config["photon_tracing_max_depth"] = photon_tracing_max_depth;
    config["raytracing_max_depth"]     = raytracing_max_depth    ;
    config["raytracing_min_weight"]    = raytracing_min_weight   ;
    config["soft_shadow_samples"]      = soft_shadow_samples     ;
    return config;
}

void Config::save(const std::string& file)
{
    std::ofstream fout(file.c_str());
    fout << toJson() << std::endl;
    fout.close();
}

void Config::loadFrom(const std::string& file)
{
    Json::Value config;
    std::ifstream fin(file.c_str());
    if (!fin)
    {
        std::cerr << "ERROR: No such config file '" + file + "'" << std::endl;
        return;
    }
    fin >> config;
    fin.close();

    load(config);
}