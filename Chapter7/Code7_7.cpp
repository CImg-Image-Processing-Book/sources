float d2(CImg<>& g_i, CImg<>& data, int x, int y)
{
  float d = 0;
  cimg_forX(g_i,dim)
    d += cimg::sqr(data(x,y,dim) - g_i(dim));
  return d;
}

/*
  Affectation des points aux classes.

  data       : Descripteurs
  g          : Centres de classe
  etiquette  : Classe des points
*/
void F(CImg<>& data, CImgList<>& g, CImg<unsigned int>& etiquette)
{
  float dist, min;
  unsigned int jmin;

  // Pour tous les vecteurs descripteurs.
  cimg_forXY(data,x,y)
  {
    // Recherche du centre le plus proche.
    min = d2(g[0],data,x,y);
    jmin = 0;

    for (int j = 1; j<g.size(); ++j)
    {
      dist = d2(g[j],data,x,y);
      if (dist<min)
      {
        min = dist;
        jmin = j;
      }
    }
    // Affectation de la classe au point.
    etiquette(x,y) = jmin;
  }
}
