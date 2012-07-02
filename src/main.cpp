#include "main_controller.h"

int main(int argc, char* argv[])
{
  Main_controller* mc = new Main_controller();
  mc->main_loop();
}
