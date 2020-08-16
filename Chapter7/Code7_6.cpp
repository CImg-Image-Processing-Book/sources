CImg<> CalculDescripteurs(CImg<>& imgIn)
{
  int p = 2;
  CImg<> descripteurs(imgIn.width(),imgIn.height(),p);

  // Calcul pour chaque pixel de la moyenne et de la
  // variance dans un voisinage 5x5.
  CImg<> N(5,5);
  cimg_for5x5(imgIn,x,y,0,0,N,float)
  {
    descripteurs(x,y,0) = N.mean();
    descripteurs(x,y,1) = N.variance();
  }
  descripteurs.get_shared_slice(0).normalize(0,255);
  descripteurs.get_shared_slice(1).normalize(0,255);
  return descripteurs;
}
