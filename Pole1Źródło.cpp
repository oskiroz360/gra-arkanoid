#include <ctime>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>


class pole {
private:
	Text* pt;
	Text* lt;
	Text* dt;
	Text* tt;
	sf::Font* czcionka;
	RectangleShape rozm;
public:
	void dalej1();
	pole(RenderWindow& okno_we) {
		rozm.setSize(Vector2f(szerokna, wysokna));
		rozm.setFillColor(Color::Blue);
		czcionka = new sf::Font;
		if (!czcionka->loadFromFile("arial.ttf"))
			return;
		lt->setFont(*czcionka);
		lt->setCharacterSize(30);
		lt->setPosition(szerokna / 2, wysokna / 5);
		lt->setFillColor(sf::Color::White);
		lt->setString("Wybierz poziom trudnosci:");
		okno_we.draw(*lt);

		pt->setFont(*czcionka);
		pt->setCharacterSize(30);
		pt->setPosition(szerokna / 2, 2 * wysokna / 5);
		pt->setFillColor(sf::Color::White);
		pt->setString("1 - Latwy  ");
		okno_we.draw(*pt);

		dt->setFont(*czcionka);
		dt->setCharacterSize(14);
		dt->setPosition(szerokna / 2, 3 * wysokna / 5);
		dt->setFillColor(sf::Color::White);
		dt->setString("2 - Sredni");
		okno_we.draw(*dt);

		tt->setFont(*czcionka);
		tt->setCharacterSize(14);
		tt->setPosition(szerokna / 2, 4 * wysokna / 5);
		tt->setFillColor(sf::Color::White);
		tt->setString("Center Bottom");
		okno_we.draw(*tt);
	}
};