 /* 
 * File:   parsetree.cpp
 * Author: Graham Hough 
 *
 * Created on December 4th, 2015
 */
#include <sstream>
#include <queue>
#include <cmath>
#include <iomanip>
#include <string>
#include "parsetree.h"

using namespace std;

// default constructor
ParseTree::ParseTree()
{
	root = NULL;
}

// recursive function to delete(free) tree node
// starting from the node pointed by T
void ParseTree::destroy(TreeNode* T)
{
	if  (T != NULL)    
	{    
		destroy(T->left) ;
		destroy(T->right) ;

		delete  T ;
	}
}

// destructor
// by calling destory function to free each node of the tree
// starting from the root node
ParseTree::~ParseTree()
{
	destroy(root);
}

// calculate the height of tree (tree levels)
// an empty tree has zero height
// The height of the tree is the number of nodes at the longest path
// from the root node to the leaf node
int ParseTree::height(TreeNode* T) 
{
        int hh = 0;
        int lh, rh;
        if (T == NULL) return hh;
        if ((T->left == NULL) && (T->right == NULL)) return (hh++);
        lh = height(T->left);
        rh = height(T->right);
        if (lh >= rh)
            hh = lh + 1;
        else
            hh = rh + 1;
        return hh;
}

// return the height of the parse tree
int ParseTree::getHeight()
{
    if (root == NULL)
        return 0;
    else
        return (height(root));
}

void ParseTree::buildTree(string E) // call build below recursively
{
    root = build(E, 0, E.length()-1);
}

 
// to buildTree the parse tree from an infix expression
TreeNode* ParseTree::build(string E, int left, int right)
{
    if (left == right) //a single operand
    {
        string key = string(&E[left]); //set node to left
        TreeNode *T;
        T = new TreeNode(key);
        return (new TreeNode(key));
    }
    TreeNode *T;
    int loc = findPlusMinus(E, left, right) ;
    if(loc != -1) // if plus or minus in expression:
    {
        if(E[loc] == '+') T = new TreeNode("+"); //if +, add node "+"
        else T = new TreeNode("-"); //same for minus
        T->left = build(E, left, loc-1); //repeat to end of left leaf
        T->right = build(E, loc+1, right); //same for right leaf
        return T; //return node
    }

    loc = findMulDiv(E, left, right) ;
    if(loc != -1)
    {
        if(E[loc] == '*') T = new TreeNode("*");
        else T = new TreeNode("/");
        T->left = build(E, left, loc-1);
        T->right = build(E, loc+1, right);
        return T;
    }
    return build(E, left, right-1); //parentheses eliminated
}

int ParseTree::findPlusMinus(string E, int left, int right) //find position of +- from right
{   int parenCnt = 0, loc = right;
    while(loc >= left)
    {   if(E[loc] == ')')parenCnt++ ;
        else
            if(E[loc] == '(') parenCnt-- ;
            else
            if(E[loc] == '+' || E[loc] == '-')
                if (parenCnt == 0) return loc;
        loc--;
    }
    return -1 ;
}

int ParseTree::findMulDiv(string E, int left, int right) //finds potisiotn of */ from right
{   int parenCnt = 0, loc = right;
    while(loc >= left)
    {
        if(E[loc] == ')') parenCnt++ ;
        else
            if(E[loc] == '(') parenCnt-- ;
            else
            if(E[loc] == '*' || E[loc] == '/')
                if (parenCnt == 0) return loc;
        loc--;
    }
    return -1 ;
}


// display the parse tree strcture visually
void ParseTree::printTree() 
{
        queue<TreeNode*> nodes;
        queue<int> levelList;
        TreeNode* current = NULL;
        int printDepth = this->getHeight();
        int possibleNodes = static_cast<int>(pow(2.0, printDepth + 1));
        int countNodes = 0;
        
        nodes.push(root);
        int currentLevel = 0;
        int previousLevel = -1;
        levelList.push(currentLevel);
        
        while (countNodes < possibleNodes) 
        {
            countNodes = countNodes + 1;
            if (!nodes.empty())  
            {    
                current = nodes.front();
                nodes.pop();
            }
            if (!levelList.empty())
            {    
                currentLevel = levelList.front();
                levelList.pop();
            }
            if (currentLevel > previousLevel)
            {
                cout << endl << endl;
                previousLevel = currentLevel;
                for (int j = 0; j < int ((pow(2.0, (printDepth - currentLevel))) - 1); j++)
                cout << setw(FORMAT_WIDTH)<< " ";
            }
            else
            {
                for (int i = 0; i < int ((pow(2.0, (printDepth - currentLevel + 1 )) - 1)) ; i++) 
                {
                    cout << setw(FORMAT_WIDTH) <<" ";
                }
            }
            if (current != NULL)
            {
                cout << setw(FORMAT_WIDTH) << current->key;
                nodes.push(current->left);
                levelList.push(currentLevel + 1);
                nodes.push(current->right);
                levelList.push(currentLevel + 1);
            }
            else {
                nodes.push(NULL);
                levelList.push(currentLevel + 1);
                nodes.push(NULL);
                levelList.push(currentLevel + 1);
                cout << setw(FORMAT_WIDTH) << " ";
            }

        }
}

