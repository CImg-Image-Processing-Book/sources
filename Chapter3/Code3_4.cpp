/*
  Egalisation d'histogramme.

  imgIn : Image d'entrée
  nb    : Nombre de bins
*/
CImg<> equalizeHisto(CImg<>& imgIn, unsigned int nb)
{
  CImg<> imgOut(imgIn);
  float vmin, vmax = imgIn.max_min(vmin);
  int size = imgIn.size();

  if (vmin==vmax && vmin==0)
    vmin = imgIn.min_max(vmax);

  int vdiff = vmax - vmin;
  CImg<> hist = imgIn.get_histogram(nb,vmin,vmax);
  long int cumul = 0;

  // Calcul de l'histogramme cumulé.
  cimg_forX(hist,pos)
  {
    cumul += hist[pos];
    hist[pos] = cumul;
  }
  if (cumul==0) cumul = 1;

  // Image égalisée.
  cimg_for(imgIn,off)
  {
    int pos = (int)((imgIn[off] - vmin)*(nb - 1)/vdiff);
    if (pos>=0 && pos<(int)nb)
      imgOut[off] = vmin + vdiff*hist[pos]/size;
  }
  return imgOut;
}
