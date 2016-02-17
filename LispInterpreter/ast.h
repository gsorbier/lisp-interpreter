#pragma once
#include <vector>
#include "node.h"

class ast
{
public:
	ast(std::vector<std::string> tokens);
	std::string representation();
	bool success();
	

	// Hm, this looks like a prime candidate for an evaluate() or some such method!

private:
	node m_nRoot;
	bool m_bCreationSuccess;
};