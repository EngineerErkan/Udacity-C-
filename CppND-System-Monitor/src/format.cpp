#include <string>

#include "format.h"

using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  long HH{seconds/3600};
  long H_re{seconds%3600};
  long MM{H_re/60};
  long SS{H_re%60};
  string str_HH{to_string(HH)};
  string str_MM{to_string(MM)};
  string str_SS{to_string(SS)};
  string time{str_HH+':'+str_MM+':'+str_SS};
  return time;
   }