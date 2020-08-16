/*
  Programme principal (algorithme ART)
*/
int main(int argc, const char * argv[])
{
  cimg_usage("Algorithme ART (reconstruction tomographique");
  char *file = cimg_option("-i","phantom.bmp","Image d'entrée");
  int
    size = cimg_option("-s",50,"Taille de l'image redimensionnée"),
    nbProj = cimg_option("-np",100,"Nombre d'orientations"),
    scaleIt = cimg_option("-n",2,"Facteur du nombre d'iteration");

  CImg<> img = CImg<>(file).get_resize(size,size).channel(0);

  // Simulation des mesures.
  CImg<> p = Projections(img,nbProj);

  // Calcul de la matrice de projections (paramètres de la machine).
  CImg<> A = MatriceProjection(size,nbProj);

  // Algorithme de reconstruction ART.
  CImg<> f = ART(A,p,scaleIt*nbProj*size);

  // Redimensionnement en forme d'une image et enregistrement.
  f.resize(size,size,1,1,-1);
  f.normalize(0,255).save_png("art.png");

  return 0;
}
