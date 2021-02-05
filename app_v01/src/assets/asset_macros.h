#pragma once

#define define_asset_type(x, ...)   std::pair<AssetType, std::vector<std::string>> \
                                    {                                              \
                                        ##x, std::vector<std::string>              \
                                        {                                          \
                                           ##__VA_ARGS__                           \
                                        }                                          \
                                    }                                              