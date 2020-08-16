CImg<unsigned char> A("A.bmp"), B("B.bmp");
CImgList<unsigned char> binOps(A | B,  // OR
                               A & B,  // AND
                               A ^ B); // XOR
binOps.display();
