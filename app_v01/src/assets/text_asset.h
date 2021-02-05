#pragma once

#include <string>
#include <fstream>
#include <spdlog/spdlog.h>

namespace assets
{
    struct Text
    {
        std::string content;
    };

    inline void load_text_asset(Text* asset, const std::string& path)
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
            spdlog::error("[DEBUG][text_asset.h]: Could not read file {0}. File doesn't exist.", path);
        }

        fileStream.close();
    }
}