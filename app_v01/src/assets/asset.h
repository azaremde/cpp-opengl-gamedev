#pragma once

#include <string>
#include <vector>
#include <map>

#include <spdlog/spdlog.h>

#include "asset_macros.h"
#include "asset_type.h"
#include "text_asset.h"

#include "util/strings/strings.h"
#include "util/vectors/vectors.h"

namespace assets {

inline std::map<AssetType, std::vector<std::string>> formats =
{
    define_asset_type(AssetType::Model, "fbx", "obj"),
    define_asset_type(AssetType::Image, "png", "jpg"),
    define_asset_type(AssetType::Text, "glsl", "txt", "json"),
    define_asset_type(AssetType::Font, "ttf")
};

inline AssetType extract_asset_type(const std::string& format)
{
    for (const auto& x : formats)
    {
        const std::vector<std::string> y = x.second;

        if (util::vec::contains(y, format))
        {
            return x.first;
        }
    }

    return AssetType::Undefined;
}

inline std::string extract_asset_format(const std::string& path)
{
    const std::vector<std::string> parts = util::str::split(path, '.');

    if (parts.size() < 2)
    {
        return "";
    }

    return parts[1];
}

template <typename T>
inline void load(T* res, const std::string& path)
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

}