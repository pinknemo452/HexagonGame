#include "Hexagon.h"
#include <cmath>

Hexagon::Hexagon(Point point, int icart, int jcart):hex_(point),icart_(icart),jcart_(jcart)
{

}

void Hexagon::calcCenter()
{
	xc_ = round(1.5 * jcart_ + 1);
	yc_ = round((icart_ + 1) * sqrt(3) / 2);
}

std::ostream& operator<<(std::ostream& os, const Hexagon hex)
{
	return os << "/\\\n| |\n\\/";
}
