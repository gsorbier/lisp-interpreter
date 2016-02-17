#include <iostream>
#include "ast.h"
#include <sstream>


using namespace std;

bool can_string_to_double(const string&);
double string_to_double(const string&);
node create_hierarchy(vector<string>& tokens);

ast::ast(vector<string> tokens)
{
	try
	{
		m_nRoot = create_hierarchy(tokens);
		m_bCreationSuccess = true;

		if (tokens.size() > 0)
		{
			string msg("unexpected chars after end-of-input");
			throw msg;
		}
	}
	catch (const string& e)
	{
		cerr << "ast creation failure: " << e << endl;
		m_bCreationSuccess = false;
	}
}

string ast::representation()
{
	string ret = m_nRoot.representation();
	return ret;
}

node create_hierarchy(vector<string>& tokens)
{
	node n;

	if (tokens.size() == 0)
	{
		string msg("create_hierarchy: unexpected end-of-input");
		throw msg;
	}

	string token = tokens.front();
	tokens.erase(tokens.begin());

	if (token == "(")
	{
		// Flag the node as a container
		n.flagContainer();

		while (tokens.size() > 0 && tokens.front() != ")")
		{
			n.addChild(create_hierarchy(tokens));
		}

		if (tokens.size() == 0)
		{
			string msg("create_hierarchy: unexpected end-of-input (unmatched lparen)");
			throw msg;
		}

		tokens.erase(tokens.begin());
	}
	else if (token == ")")
	{
		string msg("create_hierarchy: unexpected rparen");
		throw msg;
	}
	else
	{
		if (can_string_to_double(token))
		{
			n.setNumericContent(string_to_double(token));
		}
		else
		{
			n.setStringContent(token);
		}
	}

	return n;
}

bool ast::success()
{
	return m_bCreationSuccess;
}

// Helper functions for parsing node content
bool can_string_to_double(const std::string& s)
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
		return false;
	return true;
}

double string_to_double(const std::string& s)
{
	std::istringstream i(s);
	double x;
	i >> x;
	return x;
}