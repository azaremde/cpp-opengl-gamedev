#pragma once

#include <string>
#include <vector>

namespace layers {

class Layer;

class LayerManager
{
private:
    std::vector<Layer*> layers;

    LayerManager()
    {
        
    }

public:
    inline static LayerManager& get_instance()
    {
        static LayerManager instance;
        return instance;
    }

    void init();
    void update();
    void add_layer(Layer* layer);
    void release();
    Layer* find_layer(const std::string& name);

};

inline LayerManager layer_manager = LayerManager::get_instance();

}