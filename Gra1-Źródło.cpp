#include <ctime>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>


class gra {
protected:
	sf::CircleShape pilka;
	sf::RectangleShape paletka;
	sf::RectangleShape boxy;
	sf::Vector2f wsp_pilki;
	sf::Vector2f wsp_paletki;
	int scores;
	float diff = 1;
	float dx;
	float dy;

public:
	void pilkak(int granicax_we, int granicay_we);
};

void gra::pilkak(int granicax_we, int granicay_we) {
	wsp_pilki.x = granicax_we / 2;
	wsp_pilki.y = granicay_we / 2;
	dx = (granicax_we / granicay_we) * (5 + diff);
	dy = -(granicay_we / granicax_we) * (5 + diff);
	pilka.setRadius(15);
	pilka.setFillColor(sf::Color::Red);
	pilka.setPosition(wsp_pilki);
	pilka.setOutlineThickness(2);
	pilka.setOutlineColor(sf::Color::Yellow);
	while (true) {
		if (wsp_pilki.x < 0 || wsp_pilki.x>granicax_we) {
			dx = -dx;
		}
		if (wsp_pilki.y < 0 || wsp_pilki.y>granicay_we) {
			dy = -dy;
		}
		wsp_pilki.x += dx;
		wsp_pilki.y += dy;
		pilka.move(sf::Vector2f(dx, dy));
	}
};