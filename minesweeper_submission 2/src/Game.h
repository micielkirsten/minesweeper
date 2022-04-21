#pragma once

#include "Tile.h"

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Game{
private:
	std::vector<Tile*> _tiles;
	
	sf::Sprite _debug;
	sf::Sprite _test1, _test2, _test3;
	sf::Sprite _face;
	sf::Sprite _dig1, _dig2, _dig3, _dig4;

	bool _debugging;
	bool _ended;
	bool _won;

    int _window_width, _window_height;
	int _tiles_width, _tiles_height;
	int _tiles_count, _mines_count;
	bool _exposed_mine, _paused;

	int _remaining_mines;
	int _flags_count;
	bool _counter_neg;

	sf::RenderWindow _window;

	void handle_events();
    void update();
    void render();

    void reveal_tile(Tile* tile);
    int calculate_adjacent_mines(Tile* tile);
    std::vector<Tile*> get_adjacent_tiles(Tile* tile);
    void set_number(Tile* tile, int c);

	void clear();
public:
	Game(const std::string config_path = "../boards/config.cfg");

	void load_board(const std::string board_path);
	void random_board();
	void run();
};
