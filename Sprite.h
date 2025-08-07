class Sprite {
  public:
    int width, height, x, y;
    bool isDead;
    const uint8_t* bit_map; 

    Sprite(int width, int height, int x, int y, const uint8_t* bit_map) {
      this->width = width;
      this->height = height;
      this->x = x;
      this->y = y;
      this->isDead = false;
      this->bit_map = bit_map;
    }

    void move_x(int positions) {
      this->x += positions;
    }

    void move_y(int positions) {
      this->y += positions;
    }
};