/*
  Seuillage des accumulateurs

  acc   : Grille des accumulateurs
  th    : Valeur de seuil
  wsize : Demi taille deu voisinage
  accXY : Positions des accumulateurs  seuillés
  accnb : Nombre d'accumulateurs seuillés
*/
void AccThreshold(CImg<>& acc, float th, int wsize,
                  CImg<int>& accXY, int& accnb)
{
  cimg_for_insideXY(acc,x,y,wsize)
  {
    float value = acc(x,y);
    if (value<th) continue;

    bool ismax = true;
    for (int ny = y - wsize; ny<=y + wsize; ++ny)
      for (int nx = x - wsize; nx<=x + wsize; ++nx)
        ismax = ismax && (acc(nx,ny)<=value);
    if (!ismax) continue;
    accXY(accnb,0) = x;
    accXY(accnb++,1) = y;
  }
}
