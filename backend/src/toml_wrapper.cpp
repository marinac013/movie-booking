#include "toml_wrapper.h"

namespace MovieBooking {

Config Config::LoadConfig(const std::string& path)
{
    Config cfg;

    try
    {
        const toml::table tbl = toml::parse_file(path);
        cfg.ip = tbl["server"]["ip"].value_or(cfg.ip);
        cfg.port = tbl["server"]["port"].value_or(cfg.port);
        cfg.threads = tbl["server"]["threads"].value_or(cfg.threads);
    }
    catch (const toml::parse_error& err)
    {
        std::cerr << err << '\n';
    }

    return cfg;
}

}