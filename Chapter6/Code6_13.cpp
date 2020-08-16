float Directionnalite(CImg<>& imgIn)
{
  CImgList<> g = imgIn.get_gradient();
  CImg<>
    phi = g(1).get_atan2(g(0)),
    norm = (g[0].get_sqr() + g[1].get_sqr()).sqrt();

  float tau = 0.01f;
  cimg_forXY(phi,x,y)
    phi(x,y) = norm(x,y)>tau ? phi(x,y) : 0;

  CImg<> h = phi.get_histogram(100);
  h /= (imgIn.width()*imgIn.height());

  // Recherche des maximum : On seuille l'histogramme à 70%.
  h.threshold(0.7*h.max());
  int nb_pics = h.sum();

  // Recherche de la position des maximum : On trie l'histogramme.
  CImg<int> perm;
  h.get_sort(perm,false);

  float D = 0;
  for (int p = 0; p<nb_pics; ++p)
    cimg_forX(h,x) D -= h(x)*(cimg::sqr(x - perm(p)));

  float r = 1;
  D *= r*nb_pics;

  return D + 1;
}
