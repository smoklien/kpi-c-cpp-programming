#include "..\header\interface.hpp"

int main()
{
	Interface interface(3);

	try
	{
		do
		{
			interface.CreateTriangles();
			interface.UpdateTriangles();
			interface.PrintTrianglesDimensions();
			interface.PrintTrianglesAreas();
		} while (interface.AskUserForRestart());
	}
	catch (std::bad_alloc)
	{
		std::cerr << colors::red << "Error: bad memory allocation" << colors::reset;
		return 1;
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << colors::red << "Runtime error occurred: " << e.what() << colors::reset << std::endl;
		return 1;
	}
	return 0;
}