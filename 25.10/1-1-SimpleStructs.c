struct Point {
  int x;
  int y;
} CENTER;

struct {
  int r;
  int phi;
} ANOTHER_CENTER;

struct Unused {
  short value;
};

int main(void) {
  struct Point random_point;
  return CENTER.x - random_point.x;
  // return CENTER.x - ANOTHER_CENTER.r;
}
