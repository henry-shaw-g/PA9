#include <SFML/Window.hpp>

int main(void) {
	sf::Window window(sf::VideoMode(500, 500), "WINDOW");
	sf::Event event;
	
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.display();
	}
}