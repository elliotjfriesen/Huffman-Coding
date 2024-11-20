/*
 *  HuffmanCoder.cpp
 *  Elliot Friesen efries01
 *  11/14/2024
 *
 *  CS15 Project Zap
 *
 *  This file contains the implementation for HuffmanCoder.h
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "HuffmanCoder.h"
#include <queue>
#include <map>
#include <sstream>
#include "ZapUtil.h"

using namespace std;
template <typename val, typename freq>
void printMap(map<val, freq> mp);
/*
 * name:      Default constructor
 * purpose:   Allows for instantiation of HuffmanCoder class
 * arguments: none
 * returns:   none
 * effects:   none
 */
HuffmanCoder::HuffmanCoder(){}


/*
 * name:      encoder
 * purpose:   Handles encoding of input file
 * arguments: &string, &*string
 * returns:   none
 * effects:   writes into output file
 */
void HuffmanCoder::encoder(const std::string &inputFile, const std::string \
&outputFile)
{
    ifstream input_file;
    openStream(input_file, inputFile);

    map<char, int> char_map = count_freqs(input_file);
    input_file.clear();             
    input_file.seekg(0, ios::beg);
   
    priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, \
    NodeComparator> my_pq;
    my_pq = createPriorityQueue(char_map);
    HuffmanTreeNode *root = createHuffmanTree(my_pq);
    map<char, string> encoding;
    if(root->is_leaf()){
        encoding[root->get_val()] = "0";
    }
    else {
        createEncoding(&encoding, root, "");
    }
    const string encoded_string = encodeText(encoding, input_file);
    const string serialized = serialize_tree(root);
    writeZapFile(outputFile, serialized, encoded_string);
    input_file.close();
    cout << "Success! Encoded given text using " << encoded_string.length() \
    << " bits." << endl;
    deleteTree(root);
}

/*
 * name:      deleteTree
 * purpose:   clears heap space of Huffman Tree
 * arguments: HuffmanTreeNode*
 * returns:   HuffmanTreeNode*
 * effects:   clears heap
 */
void HuffmanCoder::deleteTree(HuffmanTreeNode *root){
    if (root != nullptr) {
        deleteTree(root->get_left());
        deleteTree(root->get_right());
        delete root;
    }
}

/*
 * name:      encodeText
 * purpose:   converts input into their encodings
 * arguments: map<char, string>, &istream
 * returns:   string
 * effects:   none
 */
string HuffmanCoder::encodeText(map<char, string> encoding, istream &text)
{
    
    string encoded_string;
    char c;
    text >> std::noskipws;
    text >> c;
    while (not text.eof()) {  
        encoded_string += encoding[c];
        text >> c;
    }
    return encoded_string;
}

/*
 * name:      decoder
 * purpose:   Handles decoding of input file
 * arguments: &string, &*string
 * returns:   none
 * effects:   writes into output file
 */
void HuffmanCoder::decoder(const std::string &inputFile, const std::string \
&outputFile)
{
    pair<string, string> response = readZapFile(inputFile);
    string tree = response.first;
    string text = response.second;
    
    HuffmanTreeNode* root = deserialize_tree(tree);
    int index = 0;
    string final_str = whileLoopDecoder(root, text);
    ofstream output;
    openStream(output, outputFile);
    writeFile(output, final_str);
    output.close();
    deleteTree(root);
}

/*
 * name:      writeFile
 * purpose:   Writes decoded string to the specified output file
 * arguments: &ofstream, string
 * returns:   none
 * effects:   writes into output file
 */
void HuffmanCoder::writeFile(ofstream &output, string text) {
    for(int i = 0; i < text.length(); i++){
        output << text[i];
    }
}


/*
 * name:      whileLoopDecoder
 * purpose:   decodes an encoded string using a Huffman Tree
 * arguments: HuffmanTreeNode*, &string
 * returns:   string
 * effects:   may throw std_error
 */
string HuffmanCoder::whileLoopDecoder(HuffmanTreeNode *node, string &encoding){
    string final_string = "";
    int index = 0;
    if(node->is_leaf()){
        string str(encoding.length(), node->get_val());
        return str;
    }
    while (index < encoding.length()){
        HuffmanTreeNode* currNode = node;
        while(not currNode->is_leaf()){
            if(encoding[index] == '0'){
                currNode = currNode->get_left();
                index++;
            }
            else if(encoding[index] == '1'){
                currNode = currNode->get_right();
                index++;
            }
            if(not currNode->is_leaf() and index == encoding.length()){
                throw runtime_error("Encoding did not match Huffman tree.");
            }
        }
        final_string+=currNode->get_val();
    }
    return final_string;
}


/*
 * name:      createHuffmanTree
 * purpose:   creates Huffman Tree from a given priority queue
 * arguments: priority_queue
 * returns:   HuffmanTreeNode*
 * effects:   removes elements from given queue 
 */
HuffmanTreeNode* HuffmanCoder::createHuffmanTree(priority_queue \
<HuffmanTreeNode *, vector<HuffmanTreeNode *>, NodeComparator> my_pq) {
    const char INTERNAL_NODE_VAL = '\0';
    while(my_pq.size() > 1){
        int totalFreq = 0;
        HuffmanTreeNode *firstChild = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *secondChild = my_pq.top();
        my_pq.pop();

        totalFreq += firstChild->get_freq() + secondChild->get_freq();
        
        HuffmanTreeNode *internalNode = new HuffmanTreeNode(INTERNAL_NODE_VAL,\
         totalFreq);
        internalNode->set_left(firstChild);
        internalNode->set_right(secondChild);
        my_pq.push(internalNode);
    }
    return my_pq.top();
}

/*
 * name:      createPriorityQueue
 * purpose:   creates priority queue based on character frequencies
 * arguments: map<char, int>
 * returns:   priority_queue
 * effects:   allocates space on heap for nodes
 */
priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, NodeComparator> \ 
HuffmanCoder::createPriorityQueue(map<char, int> mp)
{
    priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, \
    NodeComparator> my_pq;
    map<char, int>::iterator i = mp.begin();
    while(i != mp.end()){
        HuffmanTreeNode *node = new HuffmanTreeNode(i->first, i->second);
        my_pq.push(node);
        i++;
    }
    return my_pq;
}


/*
 * name:      count_freqs
 * purpose:   counts frequencies of characters in stream
 * arguments: stream address
 * returns:   map<char, int>
 * effects:   none
 */
map<char, int> HuffmanCoder::count_freqs(std::istream &text)
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
    return mp;
}

/*
 * name:      count_freqs
 * purpose:   counts frequencies of characters in stream
 * arguments: stream address
 * returns:   map<char, int>
 * effects:   none
 */
map<char, string>* HuffmanCoder::createEncoding(map<char, string> *mp, \
HuffmanTreeNode* node, string s)
{
    if (node == nullptr) {
        return mp; 
    }
    if(node->is_leaf()){
        (*mp)[node->get_val()] = s;
        return mp;
    }
    createEncoding(mp, node->get_left(), s + "0");
    createEncoding(mp, node->get_right(), s + "1");
    return mp;
}


/*
 * name:      openStream
 * purpose:   attempts to open the stream specified
 * arguments: streamtype pointer, string
 * returns:   none
 * effects:   may throw error, opens stream
 */
template<typename streamtype>
void HuffmanCoder::openStream(streamtype &stream, string file_name){
    stream.open(file_name);
    if (not stream.is_open()) {
        throwOpenError(file_name);
    }
}

/*
 * name:      throwOpenError
 * purpose:   throws runtime error if file cannot be opened correctly
 * arguments: string
 * returns:   none
 * effects:   throws error and exits program
 */
void HuffmanCoder::throwOpenError(string file_name){
    throw runtime_error("Unable to open file " + file_name);
    exit(EXIT_FAILURE);
}


/*
 * name:      printMap
 * purpose:   prints a given map of any types
 * arguments: map<type, type>
 * returns:   none
 * effects:   none
 */
template <typename val, typename freq>
void printMap(map<val, freq> mp){
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        std::cout << it->first << ": " << it->second;
        if (std::next(it) != mp.end()) { 
            std::cout << std::endl;
        }
    }
}


/*
 * name:      serialize_tree
 * purpose:   convert a huffman tree into a string
 * arguments: pointer to root of a Huffman Tree
 * returns:   string
 * effects:   none
 */
std::string HuffmanCoder::serialize_tree(HuffmanTreeNode *root)
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
HuffmanTreeNode* HuffmanCoder::deserialize_tree(const std::string &s)
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
HuffmanTreeNode* HuffmanCoder::deserialize_tree_helper(const \
std::string &s, int &index)
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