#include "pch.h"
#include "myutils.hpp"

#define WIDTH 1200
#define HEIGHT 720

void branch(sf::VertexArray& vertices, const int& length, const double& angle, const double& rotation) {
  static sf::Vector2f offset{WIDTH * 0.5f, HEIGHT};

  if (length > 3) {
    sf::Vector2f prevOffset{offset};
    sf::Vector2f nextOffset(offset.x + cos(angle) * length, offset.y - sin(angle) * length);

    vertices.append(offset);
    vertices.append(nextOffset);

    offset = nextOffset;
    branch(vertices, length * 0.67f, angle + rotation, rotation);

    nextOffset = sf::Vector2f(prevOffset.x + cos(angle) * length, prevOffset.y - sin(angle) * length);
    vertices.append(prevOffset);
    vertices.append(nextOffset);

    offset = nextOffset;
    branch(vertices, length * 0.67f, angle - rotation, rotation);
  } else
    offset = {WIDTH * 0.5f, HEIGHT};
}

int main() {
  sf::RenderWindow window;
  sf::Font font;
  sf::VertexArray lines{sf::Lines};
  float length = 200.f;
  double rotation = 0.7853981634;

  // Setup main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Template text", sf::Style::Close);
  window.setFramerateLimit(90);

  // Font for some test text
  font.loadFromFile("../../src/fonts/Minecraft rus.ttf");
  branch(lines, length, 3.141518 * 0.5, rotation);

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
          default:
            break;
        }

      if (event.type == sf::Event::MouseWheelScrolled) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
          length += 10.f * event.mouseWheelScroll.delta;
        else
          rotation += 0.1 * event.mouseWheelScroll.delta;

        lines.clear();
        branch(lines, length, 3.141518 * 0.5, rotation);
      }
    }

    window.clear();
    window.draw(lines);
    window.display();
  }

	return 0;
}

