# Image_Compression
Image compression and decompression 

This program is an implementation of a JPEG lossless encoder and
decoder comparing 7 prediction formulas. This program utilizes a Huffman table and applies
the lossless codec to a hard-coded 16 by 16 grayscale image. The program prints the
following for each prediction formula: <br>
<ul>
  <li>The original image as pixels </li>
 <li>Coefficients of pixels after the prediction formula is applied </li>
 <li>The compressed image in the form of a binary sequence </li>
 <li>The compression ratio </li>
 <li>Bits/Pixel for the compressed image </li>
 <li>Image(pixels) after Huffman decoder </li>
 <li>Image(pixels) after decompression </li>
</ul>
