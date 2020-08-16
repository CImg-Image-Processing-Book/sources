/*
  Calcul de l'indice de coarseness de Tamura.

  Ekh,Ekv : Images des différences horizontale et verticale
            L'échelle k est codée en z
*/
float CalculS(CImg<>& Ekh, CImg<>& Ekv)
{
  float sum = 0;

  cimg_forXY(Ekh,x,y)
  {
    float maxE = 0;
    int maxk = 0;
    cimg_forZ(Ekh,k)
      if (std::max(Ekh(x,y,k),Ekv(x,y,k))>maxE)
      {
        maxE = std::max(Ekh(x,y,k),Ekv(x,y,k));
        maxk = k + 1;
      }
    sum += pow(2,maxk);
  }
  return sum/(Ekh.width()*Ekh.height());
}
