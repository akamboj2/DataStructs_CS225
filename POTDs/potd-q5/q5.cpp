// your code here
#include "q5.h"
void increase_quantity(Food * s){
  int q=s->get_quantity();
  s->set_quantity(++q);
}
