/*
  Calcul du contraste de Tamura.

  imgIn	: Image d'entrée
  n 	: Puissance du kursotis
  nbins	: Nombre de bins de l'histogramme
*/
float Contraste(CImg<>& imgIn, float n, int nbins)
{
  CImg<> h = imgIn.get_histogram(nbins);
  float
    mean = h.mean(),
    variance = h.variance(),
    kurtosis = 0;

  cimg_forX(h,x)
    kurtosis += cimg::sqr(cimg::sqr((h(x) - mean)));
  kurtosis /= (nbins*cimg::sqr(variance));

  return std::sqrt(variance)/std::pow(kurtosis,n);
}
