 /* ./.h 
 * File:   parsetree.h
 * Author: Graham Hough
 *
 * Created on December 4th, 2015
 */

#ifndef PARSETREE_H
#define	PARSETREE_H

#include <iostream>
#include <string>

using namespace std;

class TreeNode
{
private:
	string key;
	TreeNode *left, *right;
public:
	TreeNode(string k) {key = k; left = right = NULL;}
	friend class ParseTree;
};

const string PLUS = "+";
const string MINUS = "-";
const string MULTIPLY = "*";
const string DIVIDE = "/";
const string OPENBRACE = "(";
const string CLOSEBRACE = ")";
const int FORMAT_WIDTH = 3;  // It is for the display of a tree structure: the width of each operand

class ParseTree
{
private:
	TreeNode* root;				// points to the root of the tree
	
public:
	ParseTree();			//constructor
        ParseTree(string key);
	~ParseTree();			//destructor
        TreeNode* build(string E, int left, int right);
        int findMulDiv(string E, int left, int right);
        int findPlusMinus(string E, int left, int right);  
        void buildTree(string E);
        int getHeight();
        void printTree();               // show the tree in a figure

	// ------------------------------------------
        void destroy(TreeNode* T);
        int height(TreeNode* T);
};


#endif	/* PARSETREE_H */

