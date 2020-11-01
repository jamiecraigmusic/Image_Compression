/*
main.cpp
Program Description: This program is an implementation of a JPEG lossless encoder and
decoder comparing 7 prediction formulas. This program utilizes a Huffman table and applies
the lossless codec to a hard coded 16 by 16 grayscale image. The program prints the
following for each prediction formula:
  --> The original image as pixels
  --> Coefficients of pixels after the prediction formula is applied
  --> The compressed image in the form of a binary sequence
  --> The compression ratio
  --> Bits/Pixel for the compressed image
  --> Image(pixels) after Huffman decoder
  --> Image(pixels) after decompression
 
Created by Jamie Craig on 2/24/20.
Copyright © 2020 Jamie Craig. All rights reserved.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

struct node {
    int data;
    node* left_child;
    node* right_child;
};

class linked_list {
    public:
        linked_list();
        node* create_node();
    private:
        node* newnode;
        node* temp;
        node* root;
};

linked_list :: linked_list() {
    
    newnode = NULL;
    root = NULL;
    temp = NULL;
}

node* linked_list :: create_node() {
    
    newnode = new node;
    newnode->left_child = NULL;
    newnode->right_child = NULL;
    return newnode;
    
}

//---------------------------------------- Huffman ------------------------------------//

class huffman {
    public:
        huffman();
        void build_huff_tree(); // builds a tree based on the huffman table (for decoding)
        bool print_huff_tree(node* temp, bool flag); //prints the tree to test build_tree function
        vector<bool> huffman_search(int diffference); //searches the huffman table for the bit string that corresponds to the calculated difference.
        int decode_search(vector<bool> encoded_image); // searches the Huffman Tree for value and returns the corresponding bit string
   
    protected:
    
    private:
        struct huffman_ref {
        vector<bool> bit;
        int value;
        };
        huffman_ref ref [13];
        linked_list tree;
        node* root;
        node* temp_pointer;
        node* temp;
        node* search_pointer;
        bool found;
        int y; // tracks the bit sequence for decoding
    
    
};

huffman :: huffman() {
    root = tree.create_node();
    temp_pointer = root; // for building tree
    temp = root;
    search_pointer = root;
    found = false;
    y= 8;
    
    ref[0].bit.push_back(true);
    ref[0].value = 0;
    ref[1].bit.push_back(false);
    ref[1].bit.push_back(false);
    ref[1].value = 1;
    ref[2].bit.push_back(false);
    ref[2].bit.push_back(true);
    ref[2].bit.push_back(true);
    ref[2].value = -1;
    ref[3].bit.push_back(false);
    ref[3].bit.push_back(true);
    ref[3].bit.push_back(false);
    ref[3].bit.push_back(false);
    ref[3].value = 2;
    ref[4].bit.push_back(false);
    ref[4].bit.push_back(true);
    ref[4].bit.push_back(false);
    ref[4].bit.push_back(true);
    ref[4].bit.push_back(true);
    ref[4].value = -2;
    ref[5].bit.push_back(false);
    ref[5].bit.push_back(true);
    ref[5].bit.push_back(false);
    ref[5].bit.push_back(true);
    ref[5].bit.push_back(false);
    ref[5].bit.push_back(false);
    ref[5].value = 3;
    ref[6].bit.push_back(false);
    ref[6].bit.push_back(true);
    ref[6].bit.push_back(false);
    ref[6].bit.push_back(true);
    ref[6].bit.push_back(false);
    ref[6].bit.push_back(true);
    ref[6].bit.push_back(true);
    ref[6].value = -3;
    ref[7].bit.push_back(false);
    ref[7].bit.push_back(true);
    ref[7].bit.push_back(false);
    ref[7].bit.push_back(true);
    ref[7].bit.push_back(false);
    ref[7].bit.push_back(true);
    ref[7].bit.push_back(false);
    ref[7].bit.push_back(false);
    ref[7].value = 4;
    ref[8].bit.push_back(false);
    ref[8].bit.push_back(true);
    ref[8].bit.push_back(false);
    ref[8].bit.push_back(true);
    ref[8].bit.push_back(false);
    ref[8].bit.push_back(true);
    ref[8].bit.push_back(false);
    ref[8].bit.push_back(true);
    ref[8].bit.push_back(true);
    ref[8].value = -4;
    ref[9].bit.push_back(false);
    ref[9].bit.push_back(true);
    ref[9].bit.push_back(false);
    ref[9].bit.push_back(true);
    ref[9].bit.push_back(false);
    ref[9].bit.push_back(true);
    ref[9].bit.push_back(false);
    ref[9].bit.push_back(true);
    ref[9].bit.push_back(false);
    ref[9].bit.push_back(false);
    ref[9].value = 5;
    ref[10].bit.push_back(false);
    ref[10].bit.push_back(true);
    ref[10].bit.push_back(false);
    ref[10].bit.push_back(true);
    ref[10].bit.push_back(false);
    ref[10].bit.push_back(true);
    ref[10].bit.push_back(false);
    ref[10].bit.push_back(true);
    ref[10].bit.push_back(false);
    ref[10].bit.push_back(true);
    ref[10].bit.push_back(true);
    ref[10].value = -5;
    ref[11].bit.push_back(false);
    ref[11].bit.push_back(true);
    ref[11].bit.push_back(false);
    ref[11].bit.push_back(true);
    ref[11].bit.push_back(false);
    ref[11].bit.push_back(true);
    ref[11].bit.push_back(false);
    ref[11].bit.push_back(true);
    ref[11].bit.push_back(false);
    ref[11].bit.push_back(true);
    ref[11].bit.push_back(false);
    ref[11].bit.push_back(false);
    ref[11].value = 6;
    ref[12].bit.push_back(false);
    ref[12].bit.push_back(true);
    ref[12].bit.push_back(false);
    ref[12].bit.push_back(true);
    ref[12].bit.push_back(false);
    ref[12].bit.push_back(true);
    ref[12].bit.push_back(false);
    ref[12].bit.push_back(true);
    ref[12].bit.push_back(false);
    ref[12].bit.push_back(true);
    ref[12].bit.push_back(false);
    ref[12].bit.push_back(true);
    ref[12].bit.push_back(true);
    ref[12].value = -6;
    
    build_huff_tree();
    //print_huff_tree(temp, 0);
}

void huffman:: build_huff_tree() {
    
    for (int i=0; i<13; i++){
        node* temp_pointer = root;
        for (int j=0; j<ref[i].bit.size(); j++){
            if (ref[i].bit[j]==0 ){
                if(temp_pointer->left_child != NULL) {
                    temp_pointer = temp_pointer->left_child;
                }
                else {
                    node* n = tree.create_node();
                    temp_pointer->left_child = n;
                    temp_pointer = n;
                }
            }
            else {
                if (temp_pointer->right_child != NULL) {
                    temp_pointer = temp_pointer->right_child;
                }
                else {
                    node* n = tree.create_node();
                    temp_pointer->right_child = n;
                    temp_pointer = n;
                }
                
            }
            temp_pointer->data = ref[i].value;
        }
    }
}

bool huffman:: print_huff_tree(node* temp, bool flag){
    
    if (temp->left_child == NULL && temp->right_child == NULL && flag==false) {
        cout << temp->data << endl;
        return true;
    }
    if (temp->left_child == NULL && temp->right_child != NULL){
        print_huff_tree(temp->right_child,0);
    }
    else if (temp->left_child != NULL && temp->right_child == NULL) {
        print_huff_tree(temp->left_child,0);
    }
    else {
        print_huff_tree(temp->left_child,0);
        print_huff_tree(temp->right_child,0);
    }
    return true;
}

vector<bool> huffman :: huffman_search(int diffference){
    vector<bool> search_result;
    for (int i=0; i<13; i++){
        if (diffference == ref[i].value){
            search_result = ref[i].bit;
            return search_result;
        }
    }
    return search_result;
}

int huffman:: decode_search(vector<bool> encoded_image){
    search_pointer = root;
    while ( y < encoded_image.size() && found == false){
        if(search_pointer->left_child == NULL && search_pointer->right_child == NULL){
            found = true;
            break;
        }
        else {
            if (encoded_image[y] == 0) {
                search_pointer = search_pointer->left_child;
                y++;
            }
            else {
                search_pointer = search_pointer->right_child;
                y++;
            }
        }
    }
    found = false;
    if(y == encoded_image.size()){
        y = 8;
    }
    return search_pointer->data;
}


//------------------------------------- Converter ------------------------------------//

class converter: public huffman {
    public:
        converter();
        void decimalImage_to_binaryImage(); // converts each original pixel to a bitstring
        void print_original_image(); // prints the original pixels (given in assigment)
        void calculate_differences(const int formula); // calculates x- x_hat
        int four_conditions(const int formula, int i,int j); // checks the location of the pixel in the 2D array and sends predicitive formula to calculate x_hat
        int calculate_x_hat(const int formula, int a, int b, int c); // calculates x_hat
        void print_difference_array();
        void encode_differences(); // takes the returned bitstring from the huffman table and inserts it into the encoded bit string.
        void print_encoded_image(); // prints the encoded bit string
        void compression_ratio(); // calculates the compression ratio
        void insert_difference_array_decode(); // decodes the bitstring back to difference
        void print_decoded_difference(); // prints the decoded differences from bitstring
        void calculate_original_pixels(const int formula); // calculates orginal pixels from decoded differences
        void print_decoded_pixels(); // prints the decoded Image
        void calculate_RMS();
    
    protected:
        int differences_array[16][16];
        int difference_array_decode[16][16];
        vector<bool> encoded_image;
        int difference;
        int addition;
        int image_decoded[16][16];
           
    private:
        vector<bool> image_bits[256];
        int sequence;
        int x_hat;
        int x;
        int a;
        int b;
        int c;
        double CR;
        int image_source[16][16] = {
        {88,88,88,89,90,91,92,93,94,95,93,95,96,98,97,94},
        {93,91,91,90,92,93,94,94,95,95,92,93,95,95,95,96},
        {95,95,95,95,96,97,94,96,97,96,98,97,98,99,95,97},
        {97,96,98,97,98,94,95,97,99,100,99,101,100,100,98,98},
        {99,100,97,99,100,100,98,98,100,101,100,99,101,102,99,100},
        {100,101,100,99,101,102,99,100,103,102,103,101,101,100,102,101},
        {100,102,103,101,101,100,102,103,103,105,104,104,103,104,104,103},
        {103,105,103,105,105,104,104,104,102,101,100,100,100,101,102,103},
        {104,104,105,105,105,104,104,106,102,103,101,101,102,101,102,102},
        {102,105,105,105,106,104,106,104,103,101,100,100,101,102,102,103},
        {102,105,105,105,106,104,106,104,103,101,100,100,101,102,102,103},
        {102,105,105,105,106,104,105,104,103,101,102,100,102,102,102,103},
        {104,105,106,105,106,104,106,103,103,102,100,100,101,102,102,103},
        {103,105,107,107,106,104,106,104,103,101,100,100,101,102,102,103},
        {103,105,106,108,106,104,106,105,103,101,101,100,101,103,102,105},
        {102,105,105,105,106,104,106,107,104,103,102,100,101,104,102,104}};
    };

converter :: converter() {
    sequence = 0b10000000;
    decimalImage_to_binaryImage(); //converts each pixel number in source image to binary
    x_hat = NULL;
    x = NULL;
    a = NULL;
    b = NULL;
    c = NULL;
    difference = NULL;
    addition = NULL;
    CR = 0;

};

void converter :: decimalImage_to_binaryImage(){
    int l=0;
    for (int i=0; i<16; i++){
        for (int j=0; j<16; j++){
            for (int k=0; k<8; k++){
                image_bits[l].push_back(image_source[i][j]& (sequence>>k));
            }
            l++;
        }
    }
}

void converter:: print_original_image(){
    cout << "The Original Image \n";
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            cout << image_source[i][j] << "\t";
        }
        cout << endl;
    }
}

void converter :: calculate_differences(const int formula){
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            x = image_source[i][j];
            x_hat = four_conditions(formula, i, j);
            difference = x - x_hat;
            differences_array[i][j]=difference;
            
        }
    }
}

int converter :: four_conditions(const int formula, int i, int j) {
    a = image_source[i][j-1];
    b = image_source[i-1][j];
    c = image_source[i-1][j-1];
    
    if (i==0 && j==0) {
        return 0;
    }
    else if(j == 0 && i !=0 ){
        return calculate_x_hat(2, a,b,c);
    }
    else if ( i == 0 && j != 0) {
        return calculate_x_hat(1, a, b, c);
    }
    else {
        return calculate_x_hat(formula, a, b, c);
    }
    
}

int converter :: calculate_x_hat(const int formula, int a, int b, int c){
    switch (formula) {
        case 1:
            x_hat = a;
            break;
            
        case 2:
            x_hat = b;
            break;
        
        case 3:
            x_hat = c;
            break;
            
        case 4:
            x_hat = a + b - c;
            break;
            
        case 5:
            x_hat = a + (b-c)/2;
            break;
            
        case 6:
            x_hat = b + (a-c)/2;
            break;
            
        case 7:
            x_hat = (a+b)/2;
            break;
    }
    return x_hat;
}

void converter :: print_difference_array(){
    cout << "Coefficients After The Predictor: \n";
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            cout << differences_array[i][j] << "\t";
        }
        cout << endl;
    }
}

void converter :: encode_differences(){
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            if (i == 0 && j == 0){
                encoded_image = image_bits[0];
            }
            else {
                vector<bool> temp_vector = huffman_search(differences_array[i][j]);
                for (int m=0; m<temp_vector.size(); m++){
                    encoded_image.push_back(temp_vector[m]);
                }
            }
        }
    }
}

void converter :: print_encoded_image(){
    cout << "\n";
    cout << "The Compressed Image in the Form of a Binary Sequence: \n";
    cout << "The Number of Bits in the Compressed Image: " <<encoded_image.size() << "\n";
    for(int i= 0; i<encoded_image.size(); i++) {
        cout<< encoded_image[i];
    }
    cout << "\n";
    cout << "\n";
}

void converter :: compression_ratio() {
    double bits = encoded_image.size();
    CR = 2048 / bits ;
    double bitsperpixel= 8/CR;
    cout << "The Compression Ratio is: " << CR << endl;
    cout << "Bits/Pixel for the compressed image: " << bitsperpixel << endl << endl;
    
}

void converter :: insert_difference_array_decode(){
    for( int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            if (j==0 && i ==0){
                int temp =0;
                int sum = 0;
                int mask = 0b10000000;
                for (int k=0; k<8; k++){
                    temp = (mask >> k) * image_bits[0][k];
                    sum = temp + sum;
                    difference_array_decode[i][j] = sum;
                }
            }
            else {
                difference_array_decode[i][j] = decode_search(encoded_image);
            }
        }
    }
}

void converter :: print_decoded_difference() {
    cout << "Image After Huffman Decoder: \n";
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            cout << difference_array_decode[i][j] << "\t";
        }
        cout << endl;
    }
}

void converter :: calculate_original_pixels(const int formula){
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            if( i==0 && j==0){
                image_decoded[i][j] = difference_array_decode[i][j];
            }
            else {
                addition=0;
                x = difference_array_decode[i][j];
                x_hat = four_conditions(formula, i, j);
                addition = x + x_hat;
                image_decoded[i][j]=addition;
            }
            
        }
    }
}

void converter:: print_decoded_pixels() {
    cout << "Image After Decompression: \n";
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            cout << image_decoded[i][j] << "\t";
        }
        cout << endl;
    }
}

void converter :: calculate_RMS(){
    
    int rms_sum = 0;
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            int temp_sum = 0;
            temp_sum = pow(image_source[i][j] - image_decoded[i][j], 2);
            rms_sum = temp_sum + rms_sum;
        }
    }
    cout << "RMS = " << rms_sum <<  endl;
}

int main(int argc, const char * argv[]) {

    converter image1;
    for (int i=0; i<7; i++){
        cout << "Formula: " << i+1 << endl;
        image1.print_original_image();
        cout << endl;
        image1.calculate_differences(i+1);
        image1.print_difference_array();
        image1.encode_differences();
        image1.print_encoded_image();
        image1.compression_ratio();
        image1.insert_difference_array_decode();
        image1.print_decoded_difference();
        image1.calculate_original_pixels(i+1);
        image1.print_decoded_pixels();
        image1.calculate_RMS();
        cout << endl << endl;
    }

    
}


    
