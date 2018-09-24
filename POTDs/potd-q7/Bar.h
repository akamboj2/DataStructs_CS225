// your code here
#ifndef BAR_H
#define BAR_H
#include <string>
#include "Foo.h"
namespace potd{

class Bar{
private:
  Foo * f_;
public:
  Bar(string name);
  Bar(const Bar & other);
  ~Bar();
  Bar & operator=(const Bar &other);
  std::string get_name() const;
};
}


#endif
