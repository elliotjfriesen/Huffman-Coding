/*
 *  unit_tests.h
 *  Elliot Friesen efries01
 *  11/9/2024
 *
 *  CS 15 Project Zap
 *
 *  This file tests the various functions implemented in the 
 *  phaseOne.cpp file
 *
 */

#include "phaseOne.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include "HuffmanTreeNode.h"
#include "ZapUtil.h"

using namespace std;

//for the following tests I am looking at it visually

//tests count_freqs for string of length 
void count_freqs_empty() {
    stringstream s("");
    count_freqs(s);
    assert(true);
}

//tests count_freqs for string of length 
void count_freqs_length_one() {
    stringstream s("a");
    count_freqs(s);
    assert(true);
}

//tests count_freqs for banaNa
void count_freqs_normal_test0() {
    stringstream s("banaNa");
    count_freqs(s);
    assert(true);
}

//tests count_freqs for many repeats
void count_freqs_normal_test1() {
    stringstream s("banaNaNanaNa");
    count_freqs(s);
    assert(true);
}

//tests count_freqs for one space
void count_freqs_space_test0() {
    stringstream s("banaNa NanaNa");
    count_freqs(s);
    assert(true);
}

//tests count_freqs for many consecutive space
void count_freqs_space_test1() {
    stringstream s("banaNa NanaNa");
    count_freqs(s);
    assert(true);
}

//tests count_freqs for many consecutive and other spaces
void count_freqs_space_test2() {
    stringstream s("banaNa NanaNa hgb  nan");
    count_freqs(s);
    assert(true);
}

//tests count_freqs for new lines
void count_freqs_new_line_test0() {
    stringstream s("banaNa \n NanaNa hgb  nan");
    count_freqs(s);
    assert(true);
}

//tests count_freqs for new lines
void count_freqs_new_line_test1() {
    stringstream s("hi hi\nhi");
    count_freqs(s);
    assert(true);
}

// tests below are for serialize

// tests serialize on empty tree
void test_serialize_empty() {
    string serialized = serialize_tree(nullptr);
    assert(serialized == "");
}

// tests serialize on tree of one node
void test_serialize_length_one() {
    HuffmanTreeNode *node = new HuffmanTreeNode('a');
    string serialized = serialize_tree(node);
    assert(serialized == "La");
}


// tests serialize on figure1
void test_serialize_figure1() {
    const char INTERNAL_NODE_VAL = '\0';
    HuffmanTreeNode *fig1Tree = makeFigure1Tree(INTERNAL_NODE_VAL);
    string serialized = serialize_tree(fig1Tree);
    assert(serialized == "IIILaLbILeLfILcLd");
}

// tests ensures that figure 1 is properly deserialized
 

// test deserialize on empty tree
void test_deserialize_empty() {
    const char INTERNAL_NODE_VAL = '\0';
    const string empty = "";
    HuffmanTreeNode* root = deserialize_tree(empty);
    string serialized = serialize_tree(root);
    assert(serialized == "");
}

// test deserialize on tree of length 1
void test_deserialize_length_one() {
    const char INTERNAL_NODE_VAL = '\0';
    const string figure1 = "La";
    HuffmanTreeNode* root = deserialize_tree(figure1);
    string serialized = serialize_tree(root);
    printTree(root, INTERNAL_NODE_VAL);
    assert(serialized == "La");
}

// tests deserialize on figure 1
void test_deserialize_figure1() {
    const char INTERNAL_NODE_VAL = '\0';
    const string figure1 = "IIILaLbILeLfILcLd";
    HuffmanTreeNode* root = deserialize_tree(figure1);
    string serialized = serialize_tree(root);
    printTree(root, INTERNAL_NODE_VAL);
    assert(serialized == "IIILaLbILeLfILcLd");
}