#include "Direction.hpp"
#include <string>

namespace ariel
{

	class Board
	{
	public:
		void post(unsigned int row, unsigned int column, ariel::Direction dir, std::string const &ad);
		static std::string read(unsigned int row, unsigned int column, ariel::Direction dir, unsigned int length);
		void show();
	};

}
