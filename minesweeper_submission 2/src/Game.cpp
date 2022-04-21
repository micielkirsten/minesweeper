#include "Game.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Game::Game(const std::string config_path){
    std::ifstream file(config_path.c_str());
    std::string str; 

    std::getline(file, str);
    _tiles_width = std::stoi(str);

    std::getline(file, str);
    _tiles_height = std::stoi(str);
    
    std::getline(file, str);
    _mines_count = std::stoi(str);

    _window_width = _tiles_width * 32;
    _window_height = _tiles_height * 32 + 88;
    _tiles_count = _tiles_width * _tiles_height;

    _window.create(sf::VideoMode(_window_width, _window_height), "MineSweep");

    for (int i=0; i<_tiles_width; i++)
    for (int j=0; j<_tiles_height; j++){
        _tiles.push_back(new Tile(i, j));
    }

    _test3.setTexture(Configuration::textures.get(Configuration::Textures::Test3));
    _test3.setPosition(_window_width-64*1, 32*_tiles_height);

    _test2.setTexture(Configuration::textures.get(Configuration::Textures::Test2));
    _test2.setPosition(_window_width-64*2, 32*_tiles_height);

    _test1.setTexture(Configuration::textures.get(Configuration::Textures::Test1));
    _test1.setPosition(_window_width-64*3, 32*_tiles_height);

    _debug.setTexture(Configuration::textures.get(Configuration::Textures::Debug));
    _debug.setPosition(_window_width-64*4, 32*_tiles_height);

    _face.setTexture(Configuration::textures.get(Configuration::Textures::HappyFace));
    _face.setPosition(_window_width-64*6, 32*_tiles_height);

    _dig1.setTexture(Configuration::textures.get(Configuration::Textures::Digits_m));
    _dig1.setPosition(0, 32*_tiles_height);
    _dig2.setTexture(Configuration::textures.get(Configuration::Textures::Digits0));
    _dig2.setPosition(21, 32*_tiles_height);
    _dig3.setTexture(Configuration::textures.get(Configuration::Textures::Digits0));
    _dig3.setPosition(21*2, 32*_tiles_height);
    _dig4.setTexture(Configuration::textures.get(Configuration::Textures::Digits0));
    _dig4.setPosition(21*3, 32*_tiles_height);
    
    random_board();
}

void Game::load_board(const std::string board_path){
    clear();

    for (int i=0; i<_tiles_width; i++)
    for (int j=0; j<_tiles_height; j++){
        _tiles.push_back(new Tile(i, j));
    }
    
    std::ifstream file(board_path.c_str());
    char chr;

    _remaining_mines = 0;
    for (int j = 0; j < _tiles_height; j++) {
        for (int i = 0; i < _tiles_width; i++) {
            file >> chr;
            if(chr == '0')
                _tiles[i * _tiles_height + j]->set_mine(false);
            else if(chr == '1'){
                _remaining_mines++;
                _tiles[i * _tiles_height + j]->set_mine(true);
            }
        }
    }

    _ended = false;

    _flags_count = 0;
}

void Game::run(){
    while (_window.isOpen()){
        handle_events();
        update();
        render();
    }
}

void Game::clear(){
    for(Tile* t : _tiles)
        delete t;
    _tiles.clear();
}

void Game::handle_events(){
    sf::Event event;

    while (_window.pollEvent(event)){
        if (event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape))
            _window.close();
        else if(event.type == sf::Event::MouseButtonPressed){
            sf::Vector2i pos = sf::Mouse::getPosition(_window);

            if(pos.y < _tiles_height * 32){
                if (_ended)
                    continue;

                int x = pos.x / 32;
                int y = pos.y / 32;
                Tile* tile = _tiles[x * _tiles_height + y]; 

                if (tile->is_hidden()){
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        if (tile->is_flagged())
                            continue;

                        if(tile->has_mine()){
                            tile->set_sprite(Configuration::Textures::ShownTile, Configuration::Textures::Mine);
                            _ended = true;
                            _won = false;
                        } 
                        else{
                            reveal_tile(tile);
                        }
                    }
                        
                    if(event.mouseButton.button == sf::Mouse::Right){
                        if(tile->is_flagged()){ 
                            tile->set_sprite(Configuration::Textures::HiddenTile);
                            _flags_count--;
                        }
                        else {
                            tile->set_sprite(Configuration::Textures::HiddenTile, Configuration::Textures::Flag);
                            _flags_count++;
                        }
                    }
                        
                }
            }
            else if(pos.x > _window_width-64*4 and pos.x < _window_width-64*3){
                _debugging = !_debugging;
            }
            else if(pos.x > _window_width-64*3 and pos.x < _window_width-64*2){
                load_board("../boards/testboard1.brd");
            }
            else if(pos.x > _window_width-64*2 and pos.x < _window_width-64*1){
                load_board("../boards/testboard2.brd");
            }
            else if(pos.x > _window_width-64*1 and pos.x < _window_width){
                load_board("../boards/testboard3.brd");
            }
            else if(pos.x > _window_width-64*6 and pos.x < _window_width-64*5){
                random_board();
            }
        }
    }
}

void Game::reveal_tile(Tile* tile){
    int c = calculate_adjacent_mines(tile);
    set_number(tile, c);
    tile->set_played(true);
    
    if(c == 0){
    std::vector<Tile*> adj = get_adjacent_tiles(tile);
    for(Tile* t : adj){
        reveal_tile(t);
    }
    }
}

void Game::set_number(Tile* tile, int c){
    if(c==0) tile->set_sprite(Configuration::Textures::ShownTile);
    else tile->set_sprite(Configuration::Textures::ShownTile, (Configuration::Textures) ((int) Configuration::Textures::Number1 + (c-1)));
}

int Game::calculate_adjacent_mines(Tile* tile){
    std::vector<Tile*> adjacents = get_adjacent_tiles(tile);

    int c = 0;
    for(Tile* t : adjacents)
        if(t->has_mine()) 
            c++;
    return c;
}

std::vector<Tile*> Game::get_adjacent_tiles(Tile* tile){
    std::vector<Tile*> adjacents;

    for(int i = tile->x-1; i<=tile->x+1; i++)
    for(int j = tile->y-1; j<=tile->y+1; j++)
    if(i >= 0 and i<_tiles_width and j>=0 and j<_tiles_height and not (i == tile->x and j == tile->y)){
        Tile* tile_a = _tiles[i*_tiles_height+j];
        if(not tile_a->is_played())
            adjacents.push_back(tile_a);
    }

    return adjacents;
}

void Game::random_board(){
    clear();

    for (int i=0; i<_tiles_width; i++)
    for (int j=0; j<_tiles_height; j++){
        _tiles.push_back(new Tile(i, j));
    }
    
    std::vector<sf::Vector2i> pos;
    for (int j = 0; j < _tiles_height; j++) {
        for (int i = 0; i < _tiles_width; i++) {
            pos.push_back(sf::Vector2i(i, j));
        }
    }
    
    std::random_shuffle(std::begin(pos), std::end(pos));
    for(int i=0; i<_mines_count; i++)
        _tiles[pos.at(i).x*_tiles_height + pos.at(i).y]->set_mine(true);
    for(int i=_mines_count; i<pos.size(); i++)
        _tiles[pos.at(i).x*_tiles_height + pos.at(i).y]->set_mine(false);

    _ended = false;
    _remaining_mines = _mines_count;
    _flags_count = 0;
}

void Game::update(){
    for (int j = 0; j < _tiles_height; j++) {
        for (int i = 0; i < _tiles_width; i++) {
            Tile* tile = _tiles[i * _tiles_height + j];
            
            if(tile->is_hidden() and tile->has_mine() and not tile->is_flagged()){
                if(_debugging) tile->set_sprite(Configuration::Textures::HiddenTile, Configuration::Textures::Mine);
                else tile->set_sprite(Configuration::Textures::HiddenTile);
            } 
        }
    }

    bool won_flag = true; 
    for (int j = 0; j < _tiles_height; j++) {
        for (int i = 0; i < _tiles_width; i++) {
            Tile* tile = _tiles[i * _tiles_height + j];
            
            if(tile->is_hidden() and not tile->has_mine()){
                won_flag = false;
            } 
        }
    }
    if(won_flag){
        _ended = true;
        _won = true;
    }

    if(_ended){
        if(_won)  _face.setTexture(Configuration::textures.get(Configuration::Textures::WinFace));
        else  _face.setTexture(Configuration::textures.get(Configuration::Textures::LoseFace));
    }
    else _face.setTexture(Configuration::textures.get(Configuration::Textures::HappyFace));

    int count = _remaining_mines - _flags_count;
    if(count<0) _counter_neg = true;
    else _counter_neg = false;
    int dig2 = std::abs(count / 100);
    int dig3 = std::abs((count % 100) / 10);
    int dig4 = std::abs(count % 10);
    _dig2.setTexture(Configuration::textures.get((int)Configuration::Textures::Digits0+dig2));
    _dig3.setTexture(Configuration::textures.get((int)Configuration::Textures::Digits0+dig3));
    _dig4.setTexture(Configuration::textures.get((int)Configuration::Textures::Digits0+dig4));
}

void Game::render(){
    _window.clear();
    for (int i=0; i<_tiles_width; i++)
    for (int j=0; j<_tiles_height; j++){
        _window.draw(*_tiles.at(i * _tiles_height + j));
    } 

    _window.draw(_test1);
    _window.draw(_test2);
    _window.draw(_test3);
    _window.draw(_debug);

    _window.draw(_face);

    if(_counter_neg)
        _window.draw(_dig1);
    _window.draw(_dig2);
    _window.draw(_dig3);
    _window.draw(_dig4);

    _window.display();
}
