//main
//course: CS216-001
//Project: Lab12
//Date: 12/04/2015
//Purpose: to build a parse tree which shows the relationships
//         among operators and operands in an expression
//         display the tree structure visually
//Author: Graham Hough 

#include <string>
#include <sstream>
#include <iostream>
#include "parsetree.h"

using namespace std;

int main()
{
	ParseTree exprTree; 
	string infix;
	bool more = true;
					//Output to console screen instructions:
	do
	{
		cout << endl;
		cout << "Read an expression (type Q to quit):" << endl;
		getline(cin,infix);

		if(infix == "Q" || infix == "q")
		{
			more = false;
		}
		else
		{ 
                        exprTree.buildTree(infix);
                        exprTree.printTree();
		}
	}while (more);
} //end of program
