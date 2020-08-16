CImg<> W(int size, float sigma)
{
  CImg<> res(size,size);

  int centre = size / 2 + 1;
  float sigma2 = cimg::sqr(sigma);

  cimg_forXY(res,i,j)
    res(i,j) = std::exp(-(cimg::sqr(centre - i) +
                          cimg::sqr(centre - j))/(2*sigma2));
  return res;
}
