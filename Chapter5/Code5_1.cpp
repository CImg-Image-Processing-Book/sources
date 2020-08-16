void MaskConv(CImg<>& imgIn)
{
  CImg<> W(3,3,1,1,0);
  W(1,1) = -4;
  W(0,1) = W(1,0) = W(1,2) = W(2,1) = 1;
  CImg<> imgOut = imgIn.get_convolve(W);
  imgOut.display();
}
