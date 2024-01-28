#include "pch.h"
#include <cmath>

class Tree {
  sf::VertexArray& vertices;
  sf::Vector2f offset;
  sf::Color fullLengthColor = sf::Color::White;
  sf::Uint32 colorOffset = 0xff;
  float length = 200.f;
  double rotation = 0.7853981634; // radians (pi/4)
  float invLength = 1.f / length;

  void branch(const float& len, const double& angle) {
    static const sf::Vector2f initOffset{offset};

    if (len > 4) {
      // Left branch
      sf::Vector2f prevOffset{offset};
      sf::Vector2f nextOffset(offset.x + cos(angle) * len, offset.y - sin(angle) * len);
      sf::Color color(fullLengthColor.toInteger() * len * invLength * colorOffset);

      vertices.append({offset, color});
      vertices.append({nextOffset, color});

      offset = nextOffset;
      branch(len * 0.67f, angle + rotation);

      // Right branch
      nextOffset = sf::Vector2f(prevOffset.x + cos(angle) * len, prevOffset.y - sin(angle) * len);
      vertices.append({prevOffset, color});
      vertices.append({nextOffset, color});

      offset = nextOffset;
      branch(len * 0.67f, angle - rotation);
    } else
      offset = initOffset;
  }

public:
  Tree(sf::VertexArray& vertices, sf::Vector2f offset)
    : vertices(vertices), offset(offset) {}

  void build() {
    branch(length, 3.141518 * 0.5); // Vertical line (pi/2)
  }

  void randColorOffset() {
    colorOffset = rand();
    build();
  }

  // Increase/decrease the initial length
  void diffLength(float l) {
    length += l;
    invLength = 1.f / length;
  }

  // Increase/decrease the rotation value
  void diffRotation(double r) {
    rotation += r;
  }
};

