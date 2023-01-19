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
	void paletkak(int granicax_we, int granicay_we);
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
void gra::paletkak(int granicax_we, int granicay_we) {
	wsp_paletki.x = granicax_we / 2;
	wsp_paletki.y = granicay_we / 10;
	paletka.setSize(sf::Vector2f(100, 10));
	paletka.setFillColor(sf::Color::Magenta);
	paletka.setPosition(wsp_paletki);
	sf::Vector2f przesuniecie_p;
	sf::Vector2f przesuniecie_l;
	przesuniecie_p.x = 15;
	przesuniecie_p.y = 0;
	przesuniecie_l.x = -15;
	przesuniecie_l.y = 0;

	unsigned char znak = getchar();
	switch (znak) {
	case 0: //klawisze specjalne 
	case 224: 
		znak = getchar();
		switch (znak) {
		case 75: //strza³ka w lewo
			paletka.move(przesuniecie_l);
			wsp_paletki.x += -15;
			break;
		case 77: //strza³ka w prawo
			paletka.move(przesuniecie_p);
			wsp_paletki.x += 15;
			break;
		}
		znak = 0;
		break;

	}
}
void gra::kolizja() {
	float odlegloscy = wsp_pilki.y - wsp_paletki.y;
	float odlegloscx = wsp_pilki.x - wsp_paletki.x;
	if ((odlegloscy == 12.5) && (fabs(odlegloscx) <= 50)) {
		dy = -(dy * 25 / fabs(odlegloscx));
		dx = (dx * fabs(odlegloscx) / 25);
		if (dy < 0.15 * fabs(dx)) {
			dy = 0.15 * fabs(dx);
		}
		if (dx < 0.15 * fabs(dy)) {
			dx = 0.15 * fabs(dy);
		}


	}
}
int main() {
	int szer = 800;
	int wys = 600;
	sf::RenderWindow window(sf::VideoMode(szer, wys), "SFML works!");
	gra g1;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		g1.pilkak(szer, wys);
		g1.paletkak(szer, wys);
	}
}