#include <iostream>
#include "paulcg.h"

using namespace PaulCG;

int main(){
  screen(400, 400, 0, "test");
  plot(10,10,ColorRGB(255,255,255));
  redraw();
  sleep();
  return 0;
}
