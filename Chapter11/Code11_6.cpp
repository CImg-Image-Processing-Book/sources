CImg<> genCosValues()
{
  CImg<> cosinusvalues(N,N);
  cimg_forXY(cosinusvalues,i,x)
    cosinusvalues(x,i) = std::cos(((2*x+1)*i*cimg::PI)/(2*N));
  return cosinusvalues;
}
