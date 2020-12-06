#include "Wrapper.h"
#include "Engine.h"
#include "Classes.h"


int f2(int a, int b)
{
  return a - b;
}

int main(void)
{
  
  Subject subj;

  /*Wrapper wrapper(&subj, &Subject::f3, { {"arg1", 0}, {"arg2", 0} });*/

  Wrapper wrapper(&f2, { {"arg1", 0}, {"arg2", 0} }); 

  Engine engine;

  engine.register_command(&wrapper, "command1");

  std::cout << engine.execute("command1", { {"arg1", 4}, {"arg2", 5} }) << std::endl;
}