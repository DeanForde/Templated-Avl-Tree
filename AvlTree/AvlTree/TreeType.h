
//
//  AvlClass.h
//  AvlTree
//
//  Created by Eski on 20/09/2018.
//  Copyright © 2018 Eski. All rights reserved.
//

#ifndef AvlClass_h
#define AvlClass_h
#include <iostream>
using namespace std;
typedef enum {LH,EH,RH} Balfactor;

template <class ItemType>
struct TreeNode
{
    ItemType info;
    TreeNode *left;
    TreeNode *right;
    Balfactor bf;
};

template <class ItemType>
class TreeType
{
public:
    void InsertItem(ItemType item);
    void Print();
private:
    TreeNode <ItemType> * root;
};

template <class ItemType>
void TreeType<ItemType> ::Print()
{
    PrintPostorder(root);
}

template <class ItemType>
void PrintPostorder(TreeNode<ItemType>*&  tree)
{
    if (tree == NULL)
        return;
    // first recur on left subtree
    PrintPostorder(tree->left);
    
    // then recur on right subtree
    PrintPostorder(tree->right);
    
    // now deal with the node
    cout << tree->info << "\n";
}


template <class ItemType>
void TreeType<ItemType> :: InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
    bool taller=false;
    Insert (root, item, taller);
}

template <class ItemType>
void Insert (TreeNode<ItemType>*& tree, ItemType item, bool & taller)
// Inserts item into tree.
// Post:item is in tree; search property is maintained.
{
    if (tree == NULL)
    {    // Insertion place found.
        tree = new TreeNode<ItemType>;
        tree->left = NULL;
        tree->right = NULL;
        tree->info = item;
        tree->bf = EH;
        taller = true;
    }
    else if ( item == tree->info)
        cerr << "Duplicate key is not allowed in AVL tree." << endl;
    else if (item < tree->info)
    {
        Insert (tree->left, item, taller);
        // Insert into left subtree
        if (taller)
            switch (tree->bf)
        {
            case LH: LeftBalance(tree,taller);
                break;
            case EH: tree->bf = LH;
                break;
            case RH: tree->bf = EH;
                taller = false;
                break;
        }
    }
    else
    {
        Insert (tree->right, item, taller);
        // Insert into right subtree
        if (taller)
            switch (tree->bf)
        {
            case RH: RightBalance (tree,taller);
                break;
            case EH: tree->bf = RH;
                break;
            case LH: tree->bf = EH;
                taller = false;
                break;
        }
        
    }
}

template <class ItemType>
void RotateLeft (TreeNode<ItemType> * & tree)
{
    TreeNode<ItemType> * rs;
    if (tree == NULL)
        cerr << "It is impossible to rotate an empty tree in RotateLeft" << endl;
    else if (tree->right == NULL)
        cerr << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
    else
    {
        rs = tree->right;
        tree->right = rs->left;
        rs->left = tree;
        tree = rs;
        
    }
}

template <class ItemType>
void RotateRight (TreeNode<ItemType> * & tree)
{
    TreeNode<ItemType> * ls;
    if (tree == NULL)
        cerr << "It is impossible to rotate an empty tree in RotateRight" << endl;
    else if (tree->left == NULL)
        cerr << "It is impossible to make an empty subtree the root in RotateRight" << std::endl;
    else
    {
        ls = tree->left;
        tree->left = ls->right;
        ls->right = tree;
        tree = ls;
        
    }
    
}

template <class ItemType>
void RightBalance (TreeNode<ItemType> *& tree, bool & taller)
{
    TreeNode<ItemType> * rs = tree->right;
    TreeNode<ItemType> * ls;
    switch (rs->bf)
    {
        case RH:
            tree->bf = rs->bf = EH;
            RotateLeft(tree);
            taller = false;
            break;
        case EH:
            std::cerr << "Tree already balanced " << std::endl;
            break;
        case LH:
            ls = rs->left;
            switch (ls->bf)
        {
            case RH:
                tree->bf = LH;
                rs->bf = EH;
                break;
            case EH:
                tree->bf = rs->bf = EH;
                break;
            case LH:
                tree->bf = EH;
                rs->bf = RH;
                break;
        }
            ls->bf = EH;
            RotateRight(tree->right);
            RotateLeft(tree);
            taller = false;
    }
}


template <class ItemType>
void LeftBalance (TreeNode<ItemType> *& tree, bool & taller)
{
    TreeNode<ItemType> * ls = tree->left;
    TreeNode<ItemType> * rs;
    switch (ls->bf)
    {
        case LH:
            tree->bf = ls->bf = EH;
            RotateRight(tree);
            taller = false;
            break;
        case EH:
            cerr << "Tree already balanced " << endl;
            break;
        case RH:
            rs = ls->right;
            switch (rs->bf)
        {
            case LH:
                tree->bf = RH;
                ls->bf = EH;
                break;
            case EH:
                tree->bf = ls->bf = EH;
                break;
            case RH:
                tree->bf = EH;
                ls->bf = LH;
                break;
                
        }
            rs->bf = EH;
            RotateLeft(tree->left);
            RotateRight(tree);
            taller = false;
    }
}
#endif /* AvlClass_h */
