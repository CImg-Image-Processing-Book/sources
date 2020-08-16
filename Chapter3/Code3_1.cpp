CImg<> imgIn("butterfly.bmp");
CImgList<> mathOps(imgIn,
                   imgIn.get_exp()/50,
                   10*imgIn.get_sqrt(),
                   (1 + imgIn.get_abs()).log(),
                   imgIn.get_pow(3));
mathOps.display();
