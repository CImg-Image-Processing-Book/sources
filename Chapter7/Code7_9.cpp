/*
  Calcul du critère d'arrêt des K-means.

  data      : Descripteurs
  g         : Centres de classe
  etiquette : Classe des points
*/
float W(CImg<>& data, CImgList<>& g, CImg<unsigned int>& etiquette)
{
  float d = 0;

  // Distances des attributs au centre de classe correspondant.
  cimg_forXY(data,x,y)
    d += d2(g[etiquette(x,y)],data,x,y);

  return d;
}
