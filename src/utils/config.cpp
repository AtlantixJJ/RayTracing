#include "utils/config.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <json/reader.h>
#include <json/writer.h>

int Config::dof = 8;

bool Config::enable_fresnel = true;

bool Config::enable_texture_filter = true;

int Config::hightlight_exponent = 50;

bool Config::photon_map_only = true;

int Config::photo_number = 1000000;

int Config::photo_sample = 1000;

int Config::phtrace_max_depth = 10;

double Config::ppm_dec = 0.7;

double Config::ppm_search_rad = 0.1;

int Config::ppm_iteration_depth = 20;

int Config::ppm_photo_number = 1000000;

int Config::newton_iters = 20;

double Config::snapshot_interval = 0.1;

int Config::raytracing_max_depth = 20;

double Config::raytracing_min_weight = 0.05;

int Config::soft_shadow_samples = 4;

int Config::thread_max_number = 4;

void Config::load(const Json::Value& config)
{
    dof = config["dof"].asInt();
    enable_fresnel = config["enable_fresnel"].asBool();
    enable_texture_filter = config["enable_texture_filter"].asBool();
    hightlight_exponent = config["hightlight_exponent"].asInt();
    newton_iters = config["newton_iters"].asInt();
    snapshot_interval = config["snapshot_interval"].asDouble();
    photon_map_only = config["photon_map_only"].asBool();
    photo_number = config["photo_number"].asInt();
    photo_sample = config["photo_sample"].asInt();
    phtrace_max_depth = config["phtrace_max_depth"].asInt();
    ppm_dec = config["ppm_dec"].asDouble();
    ppm_search_rad = config["ppm_search_rad"].asDouble();
    ppm_iteration_depth = config["ppm_iteration_depth"].asInt();
    ppm_photo_number = config["ppm_photo_number"].asInt();
    raytracing_max_depth = config["raytracing_max_depth"].asInt();
    raytracing_min_weight = config["raytracing_min_weight"].asDouble();
    soft_shadow_samples = config["soft_shadow_samples"].asInt();
    thread_max_number = config["thread_max_number"].asInt();
}

Json::Value Config::toJson()
{
    Json::Value config;
    config["enable_fresnel"] = enable_fresnel;
    config["enable_texture_filter"] = enable_texture_filter;
    config["hightlight_exponent"] = hightlight_exponent;
    config["newton_iters"] = newton_iters;
    config["snapshot_interval"] = snapshot_interval;
    config["photon_map_only"] = photon_map_only;
    config["photo_number"] = photo_number;
    config["photo_sample"] = photo_sample;
    config["phtrace_max_depth"] = phtrace_max_depth;
    config["ppm_dec"] = ppm_dec;
    config["ppm_search_rad"] = ppm_search_rad;
    config["ppm_iteration_depth"] = ppm_iteration_depth;
    config["ppm_photo_number"] = ppm_photo_number;
    config["raytracing_max_depth"] = raytracing_max_depth;
    config["raytracing_min_weight"] = raytracing_min_weight;
    config["soft_shadow_samples"] = soft_shadow_samples;
    config["thread_max_number"] = thread_max_number;
    return config;
}

void Config::save2Json(const std::string& file)
{
    std::ofstream fout(file.c_str());
    fout << toJson() << std::endl;
    fout.close();
}

void Config::loadFile(const std::string& file)
{
    Json::Value config;
    std::ifstream fin(file.c_str());
    fin >> config;
    fin.close();

    load(config);
}
