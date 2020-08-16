CImg<> LBPHistogram(CImg<>& imgIn)
{
  int dx = imgIn.width(), dy = imgIn.height();

  // Nombre de patchs en x et en y.
  int nbX = 5, nbY = 5;

  // Paramètres des LBP et des histogrammes.
  float R = 2;
  int p = 20, nbins = 20;

  // Construction de l'histogramme concaténé des patchs.
  CImg<> hglobal(nbins*nbX*nbY);
  for (int i = 0; i<nbX; ++i)
  {
    for (int j = 0; j<nbY; ++j)
    {
      CImg<>
        patch = imgIn.get_crop(i*dx/nbX,j*dy/nbY,0,0,
                               (i + 1)*dx/nbX,(j + 1)*dy/nbY,0,0),
        lbp(patch.width(),patch.height(),1,1,0),
        C(lbp);

      CalculLBP(patch,R,p,lbp,C);
      CImg<> hlbp = lbp.get_histogram(nbins);
      cimg_forX(hlbp,x) hglobal((j + i*nbY)*nbins + x) = hlbp(x);
    }
  }
  return hglobal;
}
