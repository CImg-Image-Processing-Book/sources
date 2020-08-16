/*
  InitLevelSet: Initialisation du LevelSet (psi) à l'aide de la
  distance euclidienne signée. Le contour initial est un cercle de
  centre (x0,y0) et de rayon r.

  imgIn : Fonction level-set à initialiser
  x0,y0,r : Paramètres du cercle pour initialiser
*/
void InitLevelSet(CImg<>& imgIn, int x0, int y0, int r)
{
  cimg_forXY(imgIn,x,y)
    imgIn(x,y) = std::sqrt(cimg::sqr(x - x0) + cimg::sqr(y - y0)) - r;
}
