#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <iostream>
#include <json/value.h>

class Config{
public:
    Config(); ///< default configuration
    ~Config(){}

     // 保存为 JSON 格式
    Json::Value toJson();

    // 从 JSON 导入场景
    void load(const Json::Value& config);

    // 保存 JSON 到文件
    void save(const std::string& file);

    // 从文件导入场景
    void loadFrom(const std::string& file);   

public: // to be modified
    ////  Options that can be configured
    //// anti aliasing
    double edge_threshold;
    int aliasing_samples;

    //// Photon Map
    int photon_number;
    int photon_samples;
    int photon_tracing_max_depth;

    //// RayTracing
    int raytracing_max_depth;
    double raytracing_min_weight;
    int soft_shadow_samples;

    //// I/O Config
    double output_refresh_interval;

    //// Math
    int newton_iters;

    //// Misc
    bool enable_texture_filtering;
    int hightlight_exponent;
};

#endif