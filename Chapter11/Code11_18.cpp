/*
  Calcul de la carte de disparité par somme de différences carrées.

  I1,I2   : Images stéréo
  h       : Taille du voisinage
  dbound  : Borne de l'intervalle de disparité.
*/
CImg<> computeSSDDisparityMap(CImg<>& I1, CImg<>& I2,
                              int h, int dbound)
{
  CImg<int> disparityMap(I1.width(),I1.height(),1,1,0);
  int arg, h2 = h/2;
  CImg<> patch1, patch2, val;

  cimg_forXY(I1,x,y)
  {
    patch1 = I1.get_crop(x - h2, y - h2,x + h2, y + h2);
    float min = 1e8f;
    for (int dx = -dbound; dx<=dbound; ++dx)
    {
      patch2 = I2.get_crop(x + dx - h2,y - h2,x + dx + h2,y + h2);
      float ssd = (patch1 - patch2).get_sqr().sum();
      if (ssd<min)
      {
        min = ssd;
        arg = dx;
      }
    }
    disparityMap(x,y) = arg;
  }
  return disparityMap;
}
