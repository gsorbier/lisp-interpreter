#include <iostream>
#include <string>
#include <vector>
#include "ast.h"

using namespace std;
vector<string> lex(string);

int main()
{
	string line;
	int64_t line_num = 0;

	while (true)
	{
		line_num++;
		cout << "in [" << line_num << "] > ";
		getline(cin, line);

		cout << "lexer output: "; 
		vector<string> toks = lex(line);
		for each (string tok in toks)
		{
			cout << tok << ",";
		}

		cout << endl;

		ast tree(toks);

		if (tree.success())
		{
			cout << tree.representation() << endl;
		}
	}


	int x; 
	cin >> x;
}

// Returns a string of tokens resulting from lexing the input string
vector<string> lex(string line)
{
	vector<string> tokens;

	size_t len = line.length();
	size_t start = 0;
	size_t curPosn = 0;

	const char* data = line.c_str();

	// Loop invariant: contents of data from index "start" to index "curPosn" inclusive
	// contain a valid token (no delimiters, no special characters)
	// The number of characters contained within this token is curPosn - start + 1
	while (curPosn < len)
	{
		size_t nChars = curPosn - start + 1;
		if (data[curPosn] == ' ')
		{
			// Copy data from start to the current posision (inclusive) into a token if that
			// data consists of more than just the space
			if (nChars > 1)
			{
				tokens.push_back(string(data + start, nChars - 1));
			}

			start = curPosn + 1;
		}
		else if (data[curPosn] == '(' || data[curPosn] == ')' || data[curPosn] == '\'' || data[curPosn] == '+' || data[curPosn] == '-')
		{
			if (nChars > 1)
			{
				// Push back the previous token
				tokens.push_back(string(data + start, nChars - 1));
			}

			// Push back the special character
			tokens.push_back(string(data + curPosn, 1));

			start = curPosn + 1;
		}
		else if (data[curPosn] == '.' && curPosn > 0 && isdigit(data[curPosn - 1]))
		{
			// pass
		}
		else if (data[curPosn] == '\r' || data[curPosn] == '\n')
		{
			// Exit
			break;
		}
		else if (!isalnum(data[curPosn]))
		{
			cout << "lex: Invalid character at position " << curPosn << " of input [stopping]" << endl;
			tokens.clear();
			return tokens;
		}
		
		curPosn++;
	}

	// If there's anything left, push it into a token
	size_t nChars = curPosn - start;
	if (nChars > 0)
	{
		tokens.push_back(string(data + start, nChars));
	}

	return tokens;
}