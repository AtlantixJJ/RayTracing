#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <json/value.h>

struct Config
{
    static double snapshot_interval;
    static int dof;
    static bool enable_fresnel;
    static bool enable_texture_filter;
    static int hightlight_exponent;
    static int newton_iters;
    static bool photon_map_only;
    static int photo_number;
    static int photo_sample;
    static int phtrace_max_depth;
    static double ppm_dec;
    static double ppm_search_rad;
    static int ppm_iteration_depth;
    static int ppm_photo_number;
    static int raytracing_max_depth;
    static double raytracing_min_weight;
    static int soft_shadow_samples;
    static int thread_max_number;

    static Json::Value toJson();
    static void load(const Json::Value& config);
    static void save2Json(const std::string& file);
    static void loadFile(const std::string& file);

private:
    Config();
};

#endif // CONFIG_H
