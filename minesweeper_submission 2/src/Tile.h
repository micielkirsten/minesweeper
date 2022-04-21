#pragma once

#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include <vector>

class Tile : public sf::Drawable {
private:
    sf::Sprite _primary_sprite;
    sf::Sprite _secondary_sprite;
    Configuration::Textures _primary_id;
    Configuration::Textures _secondary_id;

    int _pos_x, _pos_y;
    int _width, _height;

    bool _has_mine;
    bool _played;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    int x, y;
    Tile(int x, int y);

    void set_sprite(Configuration::Textures p_id, Configuration::Textures s_id = Configuration::Textures::None);

    inline bool is_hidden() { return _primary_id == Configuration::Textures::HiddenTile;}
    inline bool is_flagged(){ return _secondary_id == Configuration::Textures::Flag; }
    inline bool has_mine(){ return _has_mine; }
    inline bool is_played(){ return _played; }
    inline bool set_played(bool p){ _played = p; }
    inline void set_mine(bool mine){ _has_mine = mine;}
};
