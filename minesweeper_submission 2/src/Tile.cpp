#include "Tile.h"

Tile::Tile(int x, int y) : x(x), y(y), _pos_x(x*32), _pos_y(y*32) {
    set_sprite(Configuration::Textures::HiddenTile);
    _played = 0;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(_primary_sprite, states);
    if(_secondary_id != Configuration::Textures::None)
        target.draw(_secondary_sprite, states);
}

void Tile::set_sprite(Configuration::Textures p_id, Configuration::Textures s_id){
    _primary_id = p_id;
    _secondary_id = s_id;

    _primary_sprite.setTexture(Configuration::textures.get(p_id));
    _primary_sprite.setPosition(_pos_x, _pos_y);
    
    if(s_id != Configuration::Textures::None){
        _secondary_sprite.setTexture(Configuration::textures.get(s_id));
        _secondary_sprite.setPosition(_pos_x, _pos_y);
    }
}