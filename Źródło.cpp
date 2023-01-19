#include <ctime>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
using namespace std;
using namespace sf;

const float szerokna = 800.f;
const float wysokna = 600.f;
int diff = 0;
int wynik = 0;
bool koniec = false;
bool wygrana = false;

class pilka{
public:
	sf::CircleShape ksztalt;
	Vector2f d = { 2.5f + diff,2.5f + diff};
	Vector2f temp = d;
	bool cooldown = false;
	pilka(float x, float y) {
		float promien = 10.0;
		ksztalt.setPosition(x / 6, y / 3);
		ksztalt.setRadius(promien);
		ksztalt.setFillColor(Color::Red);
	}
	float dol() { return ksztalt.getPosition().y + 2*ksztalt.getRadius(); }
	float prawo() { return ksztalt.getPosition().x + 2*ksztalt.getRadius(); }
	float gora() { return ksztalt.getPosition().y ; }
	float lewo() { return ksztalt.getPosition().x; }
	void ruch();
};

void pilka::ruch() {
	ksztalt.move(d);
	if (lewo() <= 0.f) {
		d.x = -d.x;
	}
	if (prawo() >= szerokna -3.0f) {
		d.x = -d.x;
	}
	if (gora() <= 0.f) {
		d.y = -d.y;
	}
}
class paletka {
public:
	RectangleShape ksztp;
	paletka(float x, float y) {
		ksztp.setPosition(x / 2, y * (0.85));
		ksztp.setSize(Vector2f(x / 8, x / 80));
		ksztp.setFillColor(Color::Yellow);
	}
	float dol() { return ksztp.getPosition().y + (ksztp.getSize().y); }
	float gora() { return ksztp.getPosition().y; }
	float prawo() { return ksztp.getPosition().x + (ksztp.getSize().x); }
	float lewo() { return ksztp.getPosition().x; }
	void ruch();
};
void paletka::ruch() {
	Vector2f przesuniecie_p;
	przesuniecie_p.x = 15;
	przesuniecie_p.y = 0;
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)
		&& prawo() < szerokna) {
		ksztp.move(przesuniecie_p);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Left)
		&& lewo() > 0.f) {
		ksztp.move(-przesuniecie_p);
	}
}

void kolizja(pilka& b, paletka& p) {
	float odlegloscx = (b.ksztalt.getPosition().x + b.ksztalt.getRadius()) - (p.ksztp.getPosition().x + 0.5 * p.ksztp.getSize().x);
	if ((p.dol() >= b.gora() && b.dol() >= p.gora()) && (fabs(odlegloscx) < p.ksztp.getSize().x / 2)) {
		b.d.y = -fabs((b.temp.y * (1.8 - (fabs(odlegloscx)/40))));
		if (odlegloscx > 0) {
			b.d.x = fabs(b.temp.x * (0.8 + (fabs(odlegloscx) / 40)));
		}
		else {
			b.d.x = -fabs(b.temp.x * (0.8 + (fabs(odlegloscx) / 40)));
		}

	}
}
class stop {
protected:
	sf::Text* tekst2;
	sf::Text* tekst1;
	sf::Text* tekst3;
	Text* tekst4;
	sf::RenderWindow* oknop;
	sf::Font* czcionka;


public:
	stop(sf::RenderWindow* oknop_we);
	stop() : oknop(NULL) {}
	void draw();


};

void stop::draw() {
	if (tekst2 != NULL) {
		oknop->draw(*tekst2);
	}
	if (tekst1 != NULL) {
		oknop->draw(*tekst1);
	}
	if (tekst3 != NULL) {
		oknop->draw(*tekst3);
	}
	if (tekst4 != NULL) {
		oknop->draw(*tekst4);
	}
}

stop::stop(sf::RenderWindow* oknop_we) :oknop(oknop_we) {
	czcionka = new sf::Font;
	if (!czcionka->loadFromFile("arial.ttf"))
		return;
	tekst1 = new Text;
	tekst2 = new Text;
	tekst3 = new Text;
	tekst4 = new Text;

	tekst1->setFont(*czcionka);
	tekst1->setCharacterSize(43);
	tekst1->setPosition(20, 10);
	tekst1->setFillColor(sf::Color::White);
	tekst1->setString("Sterujemy za pomoca\n bocznych strzalek");
	tekst1->setOutlineThickness(4);
	tekst1->setOutlineColor(Color::Black);

	tekst2->setFont(*czcionka);
	tekst2->setCharacterSize(43);
	tekst2->setPosition(20,  2*wysokna / 9);
	tekst2->setFillColor(sf::Color::White);
	tekst2->setString("Celem gry jest zniszczenie\nwszystkich cegiel");
	tekst2->setOutlineThickness(4);
	tekst2->setOutlineColor(Color::Black);

	tekst3->setFont(*czcionka);
	tekst3->setCharacterSize(43);
	tekst3->setPosition(20, 4 * wysokna / 9);
	tekst3->setFillColor(sf::Color::White);
	tekst3->setString("Jesli pilka spadnie\nna dol, tracisz zycie");
	tekst3->setOutlineThickness(4);
	tekst3->setOutlineColor(Color::Black);

	tekst4->setFont(*czcionka);
	tekst4->setCharacterSize(43);
	tekst4->setPosition(20, 6 * wysokna / 9);
	tekst4->setFillColor(sf::Color::White);
	tekst4->setString("Nacisnij ENTER aby\npowrocic do gry");
	tekst4->setOutlineThickness(4);
	tekst4->setOutlineColor(Color::Black);
}

class brick {
public:
	RectangleShape* cegla;
	float dol() { return cegla->getPosition().y + (cegla->getSize().y/2); }
	float gora() { return cegla->getPosition().y - (cegla->getSize().y / 2); }
	float prawo() { return cegla->getPosition().x + (cegla->getSize().x/2); }
	float lewo() { return cegla->getPosition().x - (cegla->getSize().x / 2); }
	bool czy_zbito = false;
	void zbicie(pilka& pilka);
	brick(float xp,float yp) {
		cegla = new RectangleShape;
		cegla->setPosition(xp, yp);
		cegla->setSize({ 60, 20 });
		cegla->setFillColor(Color::Green);
		cegla->setOrigin(60 / 2.f, 20 / 2.f);
	}
};
void brick::zbicie(pilka& pilka) {
	if (pilka.dol() >= gora() && pilka.prawo() >= lewo() && pilka.lewo() <= prawo() && pilka.gora() <= dol()) {
		czy_zbito = true;
		wynik += 1;
		float overlap_lewo{ pilka.prawo() - lewo() };
		float overlap_prawo{ prawo() - pilka.lewo() };
		float overlap_gora{ pilka.dol() - gora() };
		float overlap_dol{ dol() - pilka.gora() };

		bool z_lewej(fabs(overlap_lewo) < fabs(overlap_prawo));
		bool z_gory(fabs(overlap_gora) < fabs(overlap_dol));
		float mniejszy_overlapx{ z_lewej ? overlap_lewo : overlap_prawo };
		float mniejszy_overlapy{ z_gory ? overlap_gora : overlap_dol };
		if (fabs(mniejszy_overlapx) < fabs(mniejszy_overlapy)) {
			pilka.d.x *= -1;

		}
		else {
			pilka.d.y *= -1;
		}
		if (wynik == (11 * (3 + diff))) {
			wygrana = true;
			koniec = true;
		}
	}
}

class wyjscie {
protected:
	sf::Text* tekst2;
	sf::Text* tekst1;
	sf::Text* tekst3;
	Text* tekst4;
	sf::RenderWindow* oknop;
	sf::Font* czcionka;

public:
	wyjscie(sf::RenderWindow* oknop_we);
	wyjscie() : oknop(NULL) {}
	void draw();


};

void wyjscie::draw() {
	if (tekst2 != NULL) {
		oknop->draw(*tekst2);
	}
	if (tekst1 != NULL) {
		oknop->draw(*tekst1);
	}
	if (tekst3 != NULL) {
		oknop->draw(*tekst3);
	}
	if (tekst4 != NULL) {
		oknop->draw(*tekst4);
	}
}

wyjscie::wyjscie(sf::RenderWindow* oknop_we) :oknop(oknop_we) {
	czcionka = new sf::Font;
	if (!czcionka->loadFromFile("arial.ttf"))
		return;
	tekst1 = new Text;
	tekst2 = new Text;
	tekst3 = new Text;
	tekst4 = new Text;


	tekst1->setFont(*czcionka);
	tekst1->setCharacterSize(50);
	tekst1->setPosition(szerokna / 8, wysokna / 7);
	tekst1->setFillColor(sf::Color::White);
	tekst1->setString("Czy napewno chcesz wyjsc?");
	tekst1->setOutlineThickness(5);
	tekst1->setOutlineColor(Color::Black);

	tekst2->setFont(*czcionka);
	tekst2->setCharacterSize(50);
	tekst2->setPosition(szerokna / 8, 3 * wysokna / 7);
	tekst2->setFillColor(sf::Color::White);
	tekst2->setString("Q - tak, wychodze");
	tekst2->setOutlineThickness(5);
	tekst2->setOutlineColor(Color::Black);

	tekst3->setFont(*czcionka);
	tekst3->setCharacterSize(50);
	tekst3->setPosition(szerokna / 8, 4 * wysokna / 7);
	tekst3->setFillColor(sf::Color::White);
	tekst3->setString("Enter - nie, zostaje");
	tekst3->setOutlineThickness(5);
	tekst3->setOutlineColor(Color::Black);

	tekst4->setFont(*czcionka);
	tekst4->setCharacterSize(50);
	tekst4->setPosition(szerokna / 8, 5 * wysokna / 7);
	tekst4->setFillColor(sf::Color::White);
	tekst4->setString("3 - Trudny");
	tekst4->setOutlineThickness(5);
	tekst4->setOutlineColor(Color::Black);

}
class zycie {
public:
	RenderWindow* oknop;
	zycie(RenderWindow* oknop_we);
	sf::Font* czcionka;
	Text* zycia;
	int z = 5 - diff;
	void draw();
};

zycie::zycie(RenderWindow* oknop_we) :oknop(oknop_we) {
	czcionka = new Font;
	if (!czcionka->loadFromFile("arial.ttf"))
		return;
	zycia = new Text;
	zycia->setFont(*czcionka);
	zycia->setCharacterSize(30);
	zycia->setPosition(20.0f, 550.0f);
	zycia->setFillColor(sf::Color::White);
	zycia->setOutlineThickness(3);
	zycia->setOutlineColor(Color::Black);

}
void zycie::draw() {
	zycia->setString("Zostalo Ci " + to_string(z) + " Zyc"+"                                                  Punkty: "+to_string(wynik));
	oknop->draw(*zycia);
}
void health(pilka& pilka, zycie& zycie){
	if (pilka.dol() >= wysokna) {
		pilka.ksztalt.setPosition(Vector2f(szerokna / 6, wysokna / 3));
		pilka.d = pilka.temp;
		zycie.z += -1;
		if (zycie.z == 0) {
			koniec = true;
		}
	}
}
class wejscie {
protected:
	sf::Text* tekst2;
	sf::Text* tekst1;
	sf::Text* tekst3;
	Text* tekst4;
	Text* tekst5;
	sf::RenderWindow* oknop;
	sf::Font* czcionka;
public:
	wejscie(sf::RenderWindow* oknop_we);
	wejscie() : oknop(NULL) {}
	void draw();


};

void wejscie::draw() {
	if (tekst2 != NULL) {
		oknop->draw(*tekst2);
	}
	if (tekst1 != NULL) {
		oknop->draw(*tekst1);
	}
	if (tekst3 != NULL) {
		oknop->draw(*tekst3);
	}
	if (tekst4 != NULL) {
		oknop->draw(*tekst4);
	}
	if (tekst5 != NULL) {
		oknop->draw(*tekst5);
	}
}

wejscie::wejscie(sf::RenderWindow* oknop_we) :oknop(oknop_we) {
	czcionka = new sf::Font;
	if (!czcionka->loadFromFile("arial.ttf"))
		return;
	tekst1 = new Text;
	tekst2 = new Text;
	tekst3 = new Text;
	tekst4 = new Text;
	tekst5 = new Text;

	tekst1->setFont(*czcionka);
	tekst1->setCharacterSize(50);
	tekst1->setPosition(szerokna / 7, wysokna / 7);
	tekst1->setFillColor(sf::Color::White);
	tekst1->setString("Wybierz poziom trudnosci:");
	tekst1->setOutlineThickness(5);
	tekst1->setOutlineColor(Color::Black);

	tekst2->setFont(*czcionka);
	tekst2->setCharacterSize(50);
	tekst2->setPosition(szerokna / 3, 2 * wysokna / 7);
	tekst2->setFillColor(sf::Color::White);
	tekst2->setString("1 - Latwy  ");
	tekst2->setOutlineThickness(5);
	tekst2->setOutlineColor(Color::Black);

	tekst3->setFont(*czcionka);
	tekst3->setCharacterSize(50);
	tekst3->setPosition(szerokna / 3, 3 * wysokna / 7);
	tekst3->setFillColor(sf::Color::White);
	tekst3->setString("2 - Sredni");
	tekst3->setOutlineThickness(5);
	tekst3->setOutlineColor(Color::Black);

	tekst4->setFont(*czcionka);
	tekst4->setCharacterSize(50);
	tekst4->setPosition(szerokna / 3, 4 * wysokna / 7);
	tekst4->setFillColor(sf::Color::White);
	tekst4->setString("3 - Trudny");
	tekst4->setOutlineThickness(5);
	tekst4->setOutlineColor(Color::Black);

	tekst5->setFont(*czcionka);
	tekst5->setCharacterSize(50);
	tekst5->setPosition(szerokna / 3, 5 * wysokna / 7);
	tekst5->setFillColor(sf::Color::White);
	tekst5->setString("4 - Szaleniec ");
	tekst5->setOutlineThickness(5);
	tekst5->setOutlineColor(Color::Black);
}
class gameover {
protected:
	Text* tekst2;
	Text* tekst1;
	Text* tekst3;
	Text* tekst4;
	RenderWindow* oknop;
	Font* czcionka;

public:
	gameover(sf::RenderWindow* oknop_we);
	gameover() : oknop(NULL) {}
	void draw(int wyn, bool wygrana1);


};

void gameover::draw(int wyn, bool wygrana1) {
	if (wygrana1 == true) {
		tekst2->setString("Wygrales :)");
	}
	else {
		tekst2->setString("Przegrales :(");
	}
	if (tekst2 != NULL) {
		oknop->draw(*tekst2);
	}
	if (tekst1 != NULL) {
		oknop->draw(*tekst1);
	}
	tekst3->setString("Uzyskales " + to_string(wyn) + " punktow");
	if (tekst3 != NULL) {
		oknop->draw(*tekst3);
	}
	if (tekst4 != NULL) {
		oknop->draw(*tekst4);
	}
}

gameover::gameover(sf::RenderWindow* oknop_we) :oknop(oknop_we) {
	czcionka = new sf::Font;
	if (!czcionka->loadFromFile("arial.ttf"))
		return;
	tekst1 = new Text;
	tekst2 = new Text;
	tekst3 = new Text;
	tekst4 = new Text;

	tekst1->setFont(*czcionka);
	tekst1->setCharacterSize(60);
	tekst1->setPosition((szerokna +80)/ 4, wysokna / 6);
	tekst1->setFillColor(sf::Color::White);
	tekst1->setString("Koniec Gry");
	tekst1->setOutlineThickness(6);
	tekst1->setOutlineColor(Color::Black);

	tekst2->setFont(*czcionka);
	tekst2->setCharacterSize(60);
	tekst2->setPosition(szerokna / 4, 2 * wysokna / 6);
	tekst2->setFillColor(sf::Color::White);
	tekst2->setOutlineThickness(6);
	tekst2->setOutlineColor(Color::Black);

	tekst3->setFont(*czcionka);
	tekst3->setCharacterSize(60);
	tekst3->setPosition(szerokna / 8, 3 * wysokna / 6);
	tekst3->setFillColor(sf::Color::White);
	tekst3->setOutlineThickness(6);
	tekst3->setOutlineColor(Color::Black);

	tekst4->setFont(*czcionka);
	tekst4->setCharacterSize(60);
	tekst4->setPosition(15, 4 * wysokna / 6);
	tekst4->setString("Wcisnij ESC, aby wyjsc z gry");
	tekst4->setFillColor(sf::Color::White);
	tekst4->setOutlineThickness(6);
	tekst4->setOutlineColor(Color::Black);


}

int main() {
	bool pauza = false;
	bool exit = false;
	Texture tekstura;
	tekstura.loadFromFile("r5-.jpg");
	Sprite tlo(tekstura,IntRect( 0,0,szerokna,wysokna));
	Texture tekstura1;
	tekstura1.loadFromFile("r4-.jpg");
	Sprite tlo1(tekstura1, IntRect(0, 0, szerokna, wysokna));
	Texture tekstura2;
	tekstura2.loadFromFile("r7.jpg");
	Sprite tlo2(tekstura2, IntRect(0, 0, szerokna, wysokna));
	bool wlacz = true;

		int szer = 800.0;
		int wys = 600.0;
		int wyni;
		bool wygrana1;
		srand(time(NULL));
		RenderWindow window(VideoMode(szer, wys), "Arkanoid_1!");
		wejscie* oknogl = new wejscie(&window);
		wyjscie* oknowyj = new wyjscie(&window);
		gameover* gg = new gameover(&window);
		stop* oknostop = new stop(&window);
		window.setFramerateLimit(60);
		window.clear(Color::Blue);
		vector<brick> bricks;
	
		while (window.isOpen()) {
			window.draw(tlo);
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

			}
			oknogl->draw();
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::Key::Num1)) {
				diff = 1;
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Num2)) {
				diff = 2;
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Num3)) {
				diff = 3;
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Num4)) {
				diff = 4;
				break;
			}

		}
		for (int i = 0; i < 11; ++i)
			for (int j{ 0 }; j < (3 + diff); ++j)
				bricks.emplace_back((i + 1) * (60 + 3) + 22, (j + 2) * (20 + 3));
		zycie* z = new zycie(&window);
		pilka p1(szer, wys);
		paletka pal(szer, wys);
		while (window.isOpen())
		{
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::F1)) {
				pauza = true;
				oknostop->draw();
				window.display();
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
				exit = true;
				oknowyj->draw();
				window.display();
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
				pauza = false;
				exit = false;
			}
			if (pauza == false && exit == false) {
				window.clear();
				window.draw(tlo1);
				window.draw(p1.ksztalt);
				window.draw(pal.ksztp);
				z->draw();
				p1.ruch();
				pal.ruch();
				health(p1, *z);
				for (auto& brick : bricks) brick.zbicie(p1);
				bricks.erase(remove_if(begin(bricks), end(bricks),
					[](brick& brick)
					{
						return brick.czy_zbito;
					}),
					end(bricks));

				kolizja(p1, pal);
				for (auto& brick : bricks) window.draw(*brick.cegla);
				window.display();
			}
			if (exit == true && Keyboard::isKeyPressed(Keyboard::Key::Q)) {
				window.close();
			}
			if (koniec == true) {
				wygrana1 = wygrana;
				break;
			}
			wyni = wynik;
		}
		while (window.isOpen()) {
			sf::Event event;
			window.draw(tlo2);

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

			}
			gg->draw(wyni, wygrana1);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
				break;
			}
		}
	
}