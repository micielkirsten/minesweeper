#pragma once

#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

class Configuration{
public:
    Configuration() = delete;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    enum Textures : int {
        None,
        Mine,
        HiddenTile, ShownTile,
        Number1, Number2, Number3, Number4, Number5, Number6, Number7, Number8,
        Flag,
        HappyFace, WinFace, LoseFace,
        Digits0, Digits1, Digits2, Digits3, Digits4, Digits5, Digits6, Digits7, Digits8, Digits9, Digits_m,
        Debug,
        Test1, Test2, Test3
    };
    static ResourceManager<sf::Texture, int> textures;

    static void initialize();
};


