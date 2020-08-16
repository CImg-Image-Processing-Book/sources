/*
  Calcul des centres de classe.

  data       : Descripteurs
  etiquette  : Classe des points
  g          : Centres de classe
*/
void G(CImg<>& data, CImg<unsigned int>& etiquette, CImgList<>& g)
{
  // Allocation de la table du nombre de pixels par classe.
  CImg<int> npc(g.size());
  npc.fill(0);

  // Initialisation des centres.
  cimg_forX(g,i)
    g[i].fill(0);

  // Si le pixel (x,y) appartient à la classe k,
  // on modifie le centre correspondant.
  cimg_forXY(etiquette,x,y)
  {
    unsigned int icl = etiquette(x,y);
    cimg_forX(g[icl],dim)
      g[icl](dim) += data(x,y,dim);
    ++npc(icl);
  }

  // On divise par le nombre de pixels dans la classe.
  cimg_forX(g,i)
    g[i] /= npc(i);
}
