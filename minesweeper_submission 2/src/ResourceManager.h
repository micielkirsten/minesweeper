#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>

template<typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager {
public:
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;

    ResourceManager() = default;

    template<typename ... Args>
    void load(const IDENTIFIER &id, Args &&... args){
        std::unique_ptr<RESOURCE> ptr(new RESOURCE);
        if (!ptr->loadFromFile(std::forward<Args>(args)...)){
            throw std::runtime_error("Couldn't load file");
        }
        _map.emplace(id, std::move(ptr));
    }

    RESOURCE &get(const IDENTIFIER &id) const{
        return *_map.at(id);
    }

private:
    std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> _map;
};
