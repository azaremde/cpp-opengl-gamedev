#include "layers/layer_manager.h"
#include "layers/layer.h"

namespace layers {

void LayerManager::init()
{
    for (int i = 0; i < layers.size(); i++)
    {
        layers[i]->init();
    }

    for (int i = 0; i < layers.size(); i++)
    {
        layers[i]->set_siblings();
    }
}

void LayerManager::update()
{
    for (int i = 0; i < layers.size(); i++)
    {
        layers[i]->update();
    }

    for (int i = 0; i < layers.size(); i++)
    {
        layers[i]->render(layers[i]->get_target());
    }
}

void LayerManager::add_layer(Layer* layer)
{
    layers.emplace_back(layer);
}

void LayerManager::release()
{
    for (int i = 0; i < layers.size(); i++)
    {
        delete layers[i];
    }

    layers.clear();
}

Layer* LayerManager::find_layer(const std::string& name)
{
    Layer* result = nullptr;
    for (int i = 0; i < layers.size(); i++)
    {
        if (layers[i]->name == name)
        {
            result = layers[i];
            break;
        }
    }

    return result;
}

}