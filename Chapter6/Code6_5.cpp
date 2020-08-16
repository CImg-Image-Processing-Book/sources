/*
  Détection de ligne par transformée de Hough.

  imgIn : Image d'entrée
  thr   : Seuil des accumulateurs
*/
CImg<> Hough(CImg<>& imgIn, float thr)
{
  CImg<>
    acc(500,400,1,1,0),
    imgOut(imgIn);
  int
    wx = imgIn.width(),
    wy = imgIn.height();

  // Limite des paramètres.
  float
    rhomax = std::sqrt((float)(wx*wx + wy*wy))/2,
    thetamax = 2*cimg::PI;

  // Gradient et lissage.
  CImgList<> grad = imgIn.get_gradient();
  cimglist_for(grad,l)
    grad[l].blur(1.5f);

  // Espace de Hough et accumulateurs.
  cimg_forXY(imgIn,x,y)
  {
    float
      X = (float)x - wx/2,
      Y = (float)y - wy/2,
      gx = grad(0,x,y),
      gy = grad(1,x,y),
      theta = std::atan2(gy,gx),
      rho = std::sqrt(X*X + Y*Y)*std::cos(std::atan2(Y,X) - theta);
      if (rho<0)
      {
        rho *= -1;
        theta += cimg::PI;
      }
      theta = cimg::mod(theta,thetamax);
      acc((int)(theta*acc.width()/thetamax),
          (int)(rho*acc.height()/rhomax)) += (float)std::sqrt(gx*gx + gy*gy);
  }

  // Lissage des accumulateurs.
  acc.blur(0.5f);
  CImg<> acc2(acc);
  cimg_forXY(acc2,x,y)
    acc2(x,y) = (float)std::log(1 + acc(x,y));

  // Seuillage et filtrage des accumulateurs .
  int taille_max = acc2.get_threshold(thr*acc2.max()).get_label().max();
  CImg<int> coordinates(taille_max,2,1,1,0);
  int accNumber = 0;
  AccThreshold(acc2,thr*acc2.max(),4,coordinates,accNumber);

  // Dessine les lignes sur l'image.
  unsigned char col1[3] = { 255,255,0 };
  for (unsigned i = 0; i<accNumber; ++i)
  {
    float
      rho = coordinates(i,1)*rhomax/acc.height(),
      theta = coordinates(i,0)*thetamax/acc.width(),
      x = wx/2 + rho*std::cos(theta),
      y = wy/2 + rho*std::sin(theta);
    int
      x0 = (int)(x + 1000*std::sin(theta)),
      y0 = (int)(y - 1000*std::cos(theta)),
      x1 = (int)(x - 1000*std::sin(theta)),
      y1 = (int)(y + 1000*std::cos(theta));

    imgOut.
      draw_line(x0,y0,x1,y1,col1,1.0f).
      draw_line(x0+1,y0,x1+1,y1,col1,1.0f).
      draw_line(x0,y0+1,x1,y1+1,col1,1.0f);
  }
  return imgOut;
}
