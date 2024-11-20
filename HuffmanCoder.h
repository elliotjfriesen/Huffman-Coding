/*
 *  HuffmanCoder.h
 *  Elliot Friesen efries01
 *  11/14/2024
 *
 *  CS15 Project Zap
 *
 *  This file contains the class interface for HUffmanCoder.cpp
 *
 */
#ifndef _HUFFMAN_CODER
#define _HUFFMAN_CODER

#include <string>
#include <fstream>
#include <string>
#include "phaseOne.h"
#include <map>
#include <iostream>
#include <sstream>
#include <queue>
#include "HuffmanTreeNode.h"
using namespace std;

class HuffmanCoder {
    // Feel free to add additional private helper functions as well as a
    // constructor and destructor if necessary
   public:
    HuffmanCoder();
    void encoder(const std::string &inputFile, const std::string &outputFile);
    void decoder(const std::string &inputFile, const std::string &outputFile);
   private:
    template<typename streamtype>
     void openStream(streamtype &stream, string file_name);
    map<char, int> count_freqs(std::istream &text);
    void throwOpenError(string file_name);
    priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, \
    NodeComparator> createPriorityQueue(map<char, int> mp);
    HuffmanTreeNode* createHuffmanTree(priority_queue<HuffmanTreeNode *, \
     vector<HuffmanTreeNode *>, NodeComparator> my_pq);
    map<char, string>* createEncoding(map<char, string> *mp, HuffmanTreeNode* \
    node, string s);
    string encodeText(map<char, string> encoding, istream &text);
    string serialize_tree(HuffmanTreeNode *root);
    HuffmanTreeNode* deserialize_tree(const std::string &s);
    HuffmanTreeNode* deserialize_tree_helper(const std::string &s, int &index);
    string recursiveDecoder(HuffmanTreeNode *node, string &encoding, int \
     &index, string &final_str);
    string whileLoopDecoder(HuffmanTreeNode *node, string &encoding);
    void writeFile(ofstream &output, string text);
    void deleteTree(HuffmanTreeNode *root);
};

#endif