#include <SDL/SDL.h>
#include <string>

namespace PaulCG {
  extern int w;
  extern int h;

  struct ColorRGB
  {
    int r;
    int g;
    int b;

    ColorRGB(Uint8 r, Uint8 g, Uint8 b);
    ColorRGB();
  };

  // SCREEN
  void screen(int width = 640, int height = 400, bool fullscreen = 0, const std::string& text = " ");
  void lock();
  void unlock();
  void plot(int x, int y, const ColorRGB& color);
  void redraw();

  //THREAD
  void sleep();
  void end();
}
