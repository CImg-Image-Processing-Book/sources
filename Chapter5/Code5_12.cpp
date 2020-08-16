CImg<> FiltrageGaussien(CImg<>& imgIn,
                        float sigma)
{
  // Calcul de la transformée de Fourier.
  CImgList<> fImg = imgIn.get_FFT();

  // Calcul de la réponse en fréquence du filtre.
  CImg<> gaussMask(imgIn.width(),imgIn.height());
  float sigma2 = cimg::sqr(sigma);
  cimg_forXY(gaussMask,x,y)
  {
    float
      fx = x/(float)imgIn.width() - 0.5f,
      fx2 = cimg::sqr(fx),
      fy = y/(float)imgIn.height() - 0.5f,
      fy2 = cimg::sqr(fy);
    gaussMask(x,y) = 2*cimg::PI*sigma2*
      std::exp(-2*cimg::sqr(cimg::PI)*sigma2*(fx2 + fy2));
  }

  // Positionnement du zéro au bon endroit (pas au centre).
  gaussMask.shift(-imgIn.width()/2,-imgIn.height()/2,0,0,2);

  // Filtrage (multiplication des représentations spectrales).
  cimglist_for(fImg,k)
    fImg[k].mul(gaussMask);

  // Transformée de Fourier inverse et récuperation de la partie réelle
  // (symétrie hermitienne).
  return fImg.get_FFT(true)[0].normalize(0,255);
}
