CImg<> CalculAk(CImg<>& imgIn)
{
  CImg<>
    imgIntegrale(imgIn.width(),imgIn.height(),1,1,0),
    Ak(imgIn.width(),imgIn.height(),5,1,0);

  // Initialisation : Utilisation des images intégrales.
  cimg_forXY(imgIntegrale,x,y)
  {
    float
      l1 = x==0 ? 0 : imgIntegrale(x - 1,y),
      l2 = y==0 ? 0 : imgIntegrale(x,y - 1),
      l3 = x==0 || y==0 ? 0: imgIntegrale(x - 1,y - 1);
    imgIntegrale(x,y) = imgIn(x,y) + l1 + l2 - l3;
  }

  // Calcul des Ak.
  int kp = 1;
  cimg_forZ(Ak,k)
  {
    kp *= 2;
    cimg_forXY(Ak,x,y)
      Ak(x,y,k) = IntegralLocalMean(imgIntegrale,x,y,kp);
  }
  return Ak;
}
