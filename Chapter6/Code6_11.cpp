/*
  Calcul des différences absolues entre moyennes

  Ak      : Image des moyennes locales
  Ekh,Ekv : Images des différences horizontale et verticale
            L'échelle k est codée en z
*/
void CalculE(CImg<>& Ak, CImg<>& Ekh, CImg<>& Ekv)
{
  int kp = 1;
  cimg_forZ(Ekh,k)
  {
    int k2 = kp;
    kp *= 2;
    cimg_forXY(Ekh,x,y)
    {
      int
        posx1 = x + k2,
        posx2 = x - k2,
        posy1 = y + k2,
        posy2 = y - k2;
      if (posx1<Ak.width() && posx2>=0)
        Ekh(x,y,k) = cimg::abs(Ak(posx1,y,k) - Ak(posx2,y,k));

      if (posy1<Ak.height() && posy2>=0)
        Ekv(x,y,k) = cimg::abs(Ak(x,posy1,k) - Ak(x,posy2,k));
    }
  }
}
