#include "Tree.hpp"

#define WIDTH 1200
#define HEIGHT 720

int main() {
  sf::RenderWindow window;
  sf::VertexArray lines{sf::Lines};

  // Setup main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "The fractal tree", sf::Style::Close);
  window.setFramerateLimit(90);

  Tree tree(lines, {WIDTH * 0.5f, HEIGHT});
  tree.build();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyReleased)
        switch (event.key.code) {
          case sf::Keyboard::Q:
            window.close();
            break;
          case sf::Keyboard::R:
            tree.randColorOffset();
            break;
          default:
            break;
        }

      if (event.type == sf::Event::MouseWheelScrolled) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
          tree.diffLength(10.f * event.mouseWheelScroll.delta);
        else
          tree.diffRotation(0.1 * event.mouseWheelScroll.delta);

        lines.clear();
        tree.build();
      }
    }

    window.clear();
    window.draw(lines);
    window.display();
  }

	return 0;
}

