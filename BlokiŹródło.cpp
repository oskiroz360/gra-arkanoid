#include <ctime>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>

class bloki {
public:
	RenderWindow* oknop;
	sf::ConvexShape* convex;
	bloki(int szer, int wys, RenderWindow* oknop_we);
	void zbicie(pilka& pilka);
	void usun();
	bool czy_zbito;
	void draw();
};
bloki::bloki(int szer, int wys, RenderWindow* oknop_we) :oknop(oknop_we) {
	convex = new ConvexShape;
	convex->setPointCount(7);
	convex->setFillColor(Color::Black);
	int i = 3;
	float wartoscx, wartoscy;
	wartoscx = (rand() % 200) + 50;
	wartoscy = (rand() % (wys / 3)) + 50;
	convex->setPoint(0, Vector2f(wartoscx, wartoscy));
	convex->setPoint(1, Vector2f(wartoscx + i * 20.0f, wartoscy));
	convex->setPoint(2, Vector2f(wartoscx + i * 40.0f, wartoscy + i * 20.0f));
	convex->setPoint(3, Vector2f(wartoscx + i * 40.0f, wartoscy + i * 40.0f));
	convex->setPoint(4, Vector2f(wartoscx + i * 15.0f, wartoscy + i * 40.0f));
	convex->setPoint(5, Vector2f(wartoscx + i * 15.0f, wartoscy + i * 25.0f));
	convex->setPoint(6, Vector2f(wartoscx, wartoscy + i * 25.0f));
	convex->setPoint(7, Vector2f(wartoscx, wartoscy));
}
void bloki::zbicie(pilka& pilka) {
	if (pilka.dol() >= convex->getPoint(0).y && pilka.prawo() >= convex->getPoint(0).x && pilka.lewo() <= convex->getPoint(1).x + 20 && pilka.gora() <= convex->getPoint(1).y) {
		czy_zbito = true;
		printf("git");
	}
	else if (pilka.dol() >= convex->getPosition().y + 20 && pilka.lewo() <= convex->getPosition().x + 40 && pilka.gora() <= convex->getPosition().y + 40 && pilka.prawo() >= convex->getPosition().x + 40) {
		czy_zbito = true;
	}
	else {
		czy_zbito = false;
	}
}
void bloki::usun() {
	if (czy_zbito == true) {
		delete convex;
		convex = new ConvexShape;
	}
}
void bloki::draw() {
	oknop->draw(*convex);
}