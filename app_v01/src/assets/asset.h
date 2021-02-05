#pragma once

#include <string>
#include <any>
#include <map>
#include <sstream>
#include <vector>

#include <spdlog/spdlog.h>

#include "asset_macros.h"
#include "text_asset.h"

#include "util/strings/strings.h"
#include "util/vectors/vectors.h"

#include "asset_type.h"

inline static std::map<AssetType, std::vector<std::string>> formats =
{
    define_asset_type(AssetType::Model, "fbx", "obj"),
    define_asset_type(AssetType::Image, "png", "jpg"),
    define_asset_type(AssetType::Text, "glsl", "txt", "json"),
    define_asset_type(AssetType::Font, "ttf")
};

inline static AssetType extract_asset_type(const std::string& format)
{
    for (const auto& x : formats)
    {
        const std::vector<std::string> y = x.second;
        
        spdlog::info(format);

        if (util::vec::contains(y, format))
        {
            return x.first;
        }
    }

    return AssetType::Undefined;
}

inline static std::string extract_asset_format(const std::string& path)
{
    const std::vector<std::string> parts = util::str::split(path, '.');

    if (parts.size() < 2)
    {
        return "";
    }

    return parts[1];
}

template <typename T>
inline static void load_asset(T* res, const std::string& path)
{
    std::string str_format = extract_asset_format(path);
    AssetType asset_type = extract_asset_type(str_format);
    
    switch (asset_type)
    {
        case AssetType::Text:
            load_text_asset(res, path);
            break;
    }
}
