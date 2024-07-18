#pragma once

#include "..\header\triangle.hpp"

class Interface
{
private:
	Triangle **triangles_;
	int number_of_triangles_;

	// void ValidateStream();
	void DisplayCreationOptions(int) const;
	void DisplayUpdateOptions(int) const;
	Triangle *CreateTriangleWithSides();
	Triangle *CreateTriangleWithSideAndHeight();
	bool IsStreamValid();

public:
	Interface(int);
	~Interface();

	void CreateTriangles();
	void UpdateTriangles();
	void PrintTrianglesAreas();
	void PrintTrianglesDimensions();
	bool AskUserForRestart();
	int GetUserInput();
};