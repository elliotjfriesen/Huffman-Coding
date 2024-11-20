/*
 *  phaseOne.cpp
 *  Elliot Friesen efries01
 *  11/9/2024
 *
 *  CS15 Project Zap
 *
 *  This file contains the class declarations for phaseOne.cpp
 *
 */
#ifndef __PHASEONE_H
#define __PHASEONE_H

#include <istream>
#include <string>

#include "HuffmanTreeNode.h"

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(const std::string &s);
HuffmanTreeNode *deserialize_tree_helper(const std::string &s, int &index);
#endif