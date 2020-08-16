/*
  Suivi d'objet par cross correlation.

  I    : Séquence d'images
  pos  : Position initiale de l'objet
  size : Taille de la fenêtre template autour de p
  area : Taille de la fenêtre de recherche
*/
CImg<> SuiviCC(CImgList<>& I, CImg<int>& pos,
               CImg<int>& size, CImg<int>& area)
{
  CImg<int>
    prevPos(pos),
    currPos(1,2);

  // Template de réference normalisé.
  CImg<> T = I[0].get_crop(pos(0) - size(0),pos(1) - size(1),
                           pos(0) + size(0),pos(1) + size(1));
  int
    w = T.width(),
    h = T.height();
  T -= T.sum()/(w*h);
  float
    norm = T.magnitude(),
    correlation,
    corr = -1;

  // Calcul de la corrélation max dans une zone area.
  for (int x = prevPos(0) - area(0); x<=prevPos(0) + area(0); ++x)
  {
    for (int y = prevPos(1) - area(0); y<=prevPos(1) + area(1); ++y)
    {
      CImg<> u = I[1].get_crop(x - w/2,y - h/2,x + w/2,y + h/2);
      u -= u.sum()/(u.width()*u.height());
      correlation = u.dot(T)/(u.magnitude()*norm);
      if (correlation>corr)
      {
        corr = correlation;
        currPos(0,0) = x;
        currPos(0,1) = y;
      }
    }
  }

  // Région d'intérêt.
  unsigned char red [3] = {255,0,0};
  CImg<> imgOut(I[1]);
  imgOut.draw_line(currPos(0) - size(0),currPos(1) - size(1),
                   currPos(0) + size(0),currPos(1) - size(1),red).
    draw_line(currPos(0) + size(0),currPos(1) - size(1),
              currPos(0) + size(0),currPos(1) + size(1),red).
    draw_line(currPos(0) + size(0),currPos(1) + size(1),
              currPos(0) - size(0),currPos(1) + size(1),red).
    draw_line(currPos(0) - size(0),currPos(1) + size(1),
              currPos(0) - size(0),currPos(1) - size(1),red);
  return imgOut;
}
