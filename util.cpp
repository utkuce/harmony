#include <iterator>
#include <vector>

// printing vectors to standard output
template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& container) {
   std::copy(container.cbegin(), container.cend(), std::ostream_iterator<T>(out, " " ));
   return out;
}