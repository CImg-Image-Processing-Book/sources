/*
  Algorithme des K-means.

  imgIn  : Image d'entrée
  ncl    : Nombre de classes
*/
CImg<unsigned int> Kmeans(CImg<>& imgIn, int ncl)
{
  // Calcul des descripteurs.
  CImg<> attributs = CalculDescripteurs(imgIn);

  // Structure de sortie.
  CImg<unsigned int> imgOut(attributs.width(),attributs.height());
  float w0, w;

  // Allocation des centres de classes.
  CImgList<> g(ncl,attributs.depth());

  // Initialisation de la position des centres.
  cimg_forX(g,i)
  {
    int
      x = (int)(rand()%attributs.width()),
      y = (int)(rand()%attributs.height());
    cimg_forX(g[i],dim)
      g[i](dim) = attributs(x,y,dim);
  }

  // Calcul de la partition initiale et du critère de distance.
  F(attributs,g,imgOut);
  w = W(attributs,g,imgOut);

  float epsilon = 1e-3f;
  do
  {
    w0 = w;
    // Calcul de la partition à partir de la position des centres.
    F(attributs,g,imgOut);
    // Calcul de la position des centres à partir de la partition.
    G(attributs,imgOut,g);
    // Calcul du critère de distance.
    w = W(attributs,g,imgOut);
  }
  while ((cimg::abs(w - w0)/w0)>epsilon);

  return imgOut;
}
