#pragma once

#include <string>
#include <fstream>
#include <spdlog/spdlog.h>

struct TextAsset
{
    std::string content;
};

inline static void load_text_asset(TextAsset* asset, const std::string& path)
{
    std::ifstream fileStream(path, std::ios::in);

    if (fileStream.is_open())
    {
        std::string line = "";
        while (!fileStream.eof())
        {
            getline(fileStream, line);
            asset->content.append(line + "\n");
        }
    }
    else
    {
        spdlog::error("[{0}]: Could not read file {1}. File doesn't exist.", "text_asset.h", path);
    }

    fileStream.close();
}