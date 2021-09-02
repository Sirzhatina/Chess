#include "Traits.h"

namespace Traits
{
bool operator==(const Coordinates& c1, const Coordinates& c2) { return c1.x == c2.x && c1.y == c2.y; }
bool operator!=(const Coordinates& c1, const Coordinates& c2) { return !(c1 == c2); }
} // namespace Traits
