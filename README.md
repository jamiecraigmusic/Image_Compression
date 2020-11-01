# Image_Compression
Image compression and decompression 

This program is an implementation of a JPEG lossless encoder and
decoder comparing 7 prediction formulas. This program utilizes a Huffman table and applies
the lossless codec to a hard-coded 16 by 16 grayscale image. The program prints the
following for each prediction formula: \n
  --> The original image as pixels
  --> Coefficients of pixels after the prediction formula is applied
  --> The compressed image in the form of a binary sequence
  --> The compression ratio
  --> Bits/Pixel for the compressed image
  --> Image(pixels) after Huffman decoder
  --> Image(pixels) after decompression
