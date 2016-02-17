#pragma once
#include <vector>
#include <string>

enum NODE_TYPE
{
	NIL,
	STRING,
	NUMERIC,
	CONTAINER
};

class node
{
public:
	node();  // the NIL node
	node(std::string s);
	node(double d);
	void addChild(node n);
	void setStringContent(std::string s);
	void setNumericContent(double d);
	void setNil();
	void flagContainer();
	std::string representation();
	NODE_TYPE type();

private:
	NODE_TYPE m_tType;
	std::vector<node> m_vnChildren;
	std::string m_sStringContent;  // can be identifier, string literal, function name etc.
	double m_dNumericContent;  // a number
};