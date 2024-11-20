/*
 *  phaseOne.cpp
 *  Elliot Friesen efries01
 *  11/9/2024
 *
 *  CS15 Project Zap
 *
 *  This file contains the class definitions for phaseOne.h
 *
 */

#include "phaseOne.h"
#include <map>
#include <iostream>
#include <sstream>
#include "HuffmanTreeNode.h"
#include "ZapUtil.h"

using namespace std;

/*
 * name:      count_freqs
 * purpose:   store frequencies of chars and print them out
 * arguments: address of an input stream
 * returns:   none
 * effects:   none
 */
void count_freqs(std::istream &text)
{
    map<char, int> mp;
    char c;
    text >> std::noskipws;
    text >> c;
    while (not text.eof()) {
        int value = mp[c];
        int nextVal = value + 1;
        mp[c] = nextVal;
        text >> c;
    }

    map<char, int>::iterator i = mp.begin();

    while(i != mp.end()){
        cout << i->first << ": " << i->second;
        if (i != prev(mp.end())) {
            cout << endl;
        }
        i++;
    }
}

/*
 * name:      serialize_tree
 * purpose:   convert a huffman tree into a string
 * arguments: pointer to root of a Huffman Tree
 * returns:   string
 * effects:   none
 */
std::string serialize_tree(HuffmanTreeNode *root)
{
    if(root == nullptr){ // check if no tree
        return "";
    }
    if(root->is_leaf()){ // if lead
        string returnString = "L";
        returnString += root->get_val();
        return returnString;
    }
    return "I" + serialize_tree(root->get_left()) + \
    serialize_tree(root->get_right());
}




/*
 * name:      deserialized_tree
 * purpose:   convert a string into a huffman tree
 * arguments: const &string
 * returns:   pointer to Huffman Tree
 * effects:   calls deserialized helper
 */
HuffmanTreeNode *deserialize_tree(const std::string &s)
{
    if(s.length() == 0){
        return nullptr;
    }
    int index = 0;
    return deserialize_tree_helper(s, index);
}

/*
 * name:      deserialized_tree_helper
 * purpose:   convert a string into a huffman tree recursively
 * arguments: const &string, &int
 * returns:   pointer to Huffman Tree
 * effects:   allocates space on heap
 */
HuffmanTreeNode *deserialize_tree_helper(const std::string &s, int &index)
{
    const char INTERNAL_NODE_VAL = '\0';
    HuffmanTreeNode* curr;
    if (s[index] == 'L') { // base case if leaf
        curr = new HuffmanTreeNode(s[index + 1]);
        index += 2;
    }
    else if(s[index] == 'I'){ // if internal node
        curr = new HuffmanTreeNode(INTERNAL_NODE_VAL);
        index += 1;
        curr->set_left(deserialize_tree_helper(s, index));
        curr->set_right(deserialize_tree_helper(s, index));
    }
    return curr;
}



