#pragma once
#include <string>
#include <iostream>
#include "node.h"

using namespace std;

node::node()
{
	m_tType = NIL;
}

node::node(std::string s)
{
	m_tType = STRING;
	m_sStringContent = s;
}

node::node(double d)
{
	m_tType = NUMERIC;
	m_dNumericContent = d;
}

void node::addChild(node n)
{
	m_vnChildren.push_back(n);
}

void node::setStringContent(std::string s)
{
	if (m_tType != NIL)
	{
		cout << "setStringValue: Cannot set string val on NUMERIC node" << endl;
		return;
	}

	m_tType = STRING;
	m_sStringContent = s;
}

void node::setNumericContent(double d)
{
	if (m_tType != NIL)
	{
		cout << "setNumericContent: Cannot set numeric content on STRING node" << endl;
		return;
	}

	m_tType = NUMERIC;
	m_dNumericContent = d;
}

void node::setNil()
{
	m_tType = NIL;
}

void node::flagContainer()
{
	m_tType = CONTAINER;
}

NODE_TYPE node::type()
{
	return m_tType;
}

string node::representation()
{
	string r;

	if (m_tType == CONTAINER)
	{
		r += "[ ";
		for each (node child in m_vnChildren)
		{
			r += child.representation();
		}
		r += "] ";
	}
	else if (m_tType == NUMERIC)
	{
		r = to_string(m_dNumericContent) + " ";
	}
	else if (m_tType == STRING)
	{
		r = m_sStringContent + " ";
	}
	else if (m_tType == NIL)
	{
		r = "@";  // ?
	}

	return r;
}