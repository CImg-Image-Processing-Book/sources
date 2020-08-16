/*
  Détection de coins par la méthode d'Harris et Stephens.

  imgIn	: Image d'entrée
  k   	: Paramètre de sensibilité du détecteur
  n     : Nombre de points à détecter
  sigma : Variance du fenêtreage gaussien
*/
CImg<> HarrisDetector(CImg<>& imgIn, float k, int n, float sigma)
{
  CImg<> harris(imgIn);
  CImgList<> gradXY = imgIn.get_gradient();
  const float eps = 1e-5f;

  // Fenêtrage.
  CImg<> G = W(7,sigma);

  // Tenseur de structure.
  CImg<>
    Ixx = gradXY[0].get_mul(gradXY[0]).get_convolve(G),
    Iyy = gradXY[1].get_mul(gradXY[1]).get_convolve(G),
    Ixy = gradXY[0].get_mul(gradXY[1]).get_convolve(G);

  // Calcul de la fonction R.
  CImg<>
    det = Ixx.get_mul(Iyy) - Ixy.get_sqr(),
    trace = Ixx + Iyy,
    R = det - k*trace.get_sqr();

  // Calcul des maxima locaux de R.
  CImgList<> imgGradR = R.get_gradient();
  CImg_3x3(I,float);
  CImg<> harrisValues(imgIn.width()*imgIn.height(),1,1,1,0);
  CImg<int>
    harrisXY(imgIn.width()*imgIn.height(),2,1,1,0),
    perm(imgIn.width()*imgIn.height(),1,1,1,0);

  int nbHarris = 0;
  cimg_for3x3(R,x,y,0,0,I,float)
  {
    if (imgGradR[0](x,y)<eps && imgGradR[1](x,y)<eps)
    {
      float
        befx = Ipc - Icc,
        befy = Icp - Icc,
        afty = Icn - Icc,
        aftx = Inc - Icc;
      if (befx<0 && befy<0 && aftx<0 && afty<0)
      {
        harrisValues(nbHarris) = R(x,y);
        harrisXY(nbHarris,0) = x;
        harrisXY(nbHarris++,1) = y;
      }
    }
  }

  // Tri des valeurs de R.
  harrisValues.sort(perm,false);

  // Affichage des points d'intérêt.
  unsigned char red[3] = { 255,0,0 };
  for (int i = 0; i<n; ++i)
  {
    int
      pos = perm(i),
      posx = harrisXY(pos,0),
      posy = harrisXY(pos,1);
    harris.draw_line(posx-1,posy,posx,posy,red);
    harris.draw_line(posx,posy,posx+1,posy,red);
    harris.draw_line(posx,posy-1,posx,posy,red);
    harris.draw_line(posx,posy,posx,posy+1,red);
  }
  return harris;
}
