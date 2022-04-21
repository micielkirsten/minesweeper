#include "Configuration.h"

ResourceManager<sf::Texture, int> Configuration::textures;
void Configuration::initialize(){
    textures.load(Textures::Mine, "../images/mine.png");

    textures.load(Textures::HiddenTile, "../images/tile_hidden.png");
    textures.load(Textures::ShownTile, "../images/tile_revealed.png");

    textures.load(Textures::Number1, "../images/number_1.png");
    textures.load(Textures::Number2, "../images/number_2.png");
    textures.load(Textures::Number3, "../images/number_3.png");
    textures.load(Textures::Number4, "../images/number_4.png");
    textures.load(Textures::Number5, "../images/number_5.png");
    textures.load(Textures::Number6, "../images/number_6.png");
    textures.load(Textures::Number7, "../images/number_7.png");
    textures.load(Textures::Number8, "../images/number_8.png");

    textures.load(Textures::Flag, "../images/flag.png");

    textures.load(Textures::HappyFace, "../images/face_happy.png");
    textures.load(Textures::WinFace, "../images/face_win.png");
    textures.load(Textures::LoseFace, "../images/face_lose.png");

    textures.load(Textures::Digits0, "../images/digits.png", sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits1, "../images/digits.png", sf::IntRect(sf::Vector2i(21, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits2, "../images/digits.png", sf::IntRect(sf::Vector2i(21*2, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits3, "../images/digits.png", sf::IntRect(sf::Vector2i(21*3, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits4, "../images/digits.png", sf::IntRect(sf::Vector2i(21*4, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits5, "../images/digits.png", sf::IntRect(sf::Vector2i(21*5, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits6, "../images/digits.png", sf::IntRect(sf::Vector2i(21*6, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits7, "../images/digits.png", sf::IntRect(sf::Vector2i(21*7, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits8, "../images/digits.png", sf::IntRect(sf::Vector2i(21*8, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits9, "../images/digits.png", sf::IntRect(sf::Vector2i(21*9, 0), sf::Vector2i(21, 32)));
    textures.load(Textures::Digits_m, "../images/digits.png", sf::IntRect(sf::Vector2i(21*10, 0), sf::Vector2i(21, 32)));

    textures.load(Textures::Debug, "../images/debug.png");

    textures.load(Textures::Test1, "../images/test_1.png");
    textures.load(Textures::Test2, "../images/test_2.png");
    textures.load(Textures::Test3, "../images/test_3.png");
}
