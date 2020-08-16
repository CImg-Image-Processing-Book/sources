/*
  Hough_Cercle: Calcul de l'accumulateur pour la detection de cercles.

  ImgIn : Image d'entrée
  Acc   : Accumulateur ( sortie )
  a     : Regularisation du gradient
  s     : Seuil sur la norme des gradients retenus
  Rmin  : Rayon minimum
*/
void Hough_Cercle(CImg<>& ImgIn, CImg<>& Acc, float a, float s, int Rmin)
{
  // Initialisation de la structure de l'accumulateur.
  Acc.fill(0);

  // Calcul du gradient de l'image et régularisation.
  CImgList<> imgGrad = ImgIn.get_gradient();
  imgGrad[0].blur(a);
  imgGrad[1].blur(a);

  cimg_forXY(ImgIn,x,y)
  {
    float
      gx = imgGrad(0,x,y),
      gy = imgGrad(1,x,y),
      norm = std::sqrt(gx*gx + gy*gy);

    if (norm>s)
    {
      cimg_forZ(Acc,r)
      {
        // Centre du cercle dans la direction du gradient.
        int
          xc = (int)(x + (r + Rmin)*gx/norm),
          yc = (int)(y + (r + Rmin)*gy/norm);

        // Vote si le centre est présent dans l'accumulateur.
        if (xc>=0 && xc<Acc.width() && yc>=0 && yc<Acc.height())
          Acc(xc, yc,r) += norm;

        // Centre du cercle dans la direction opposée du gradient.
        xc = (int)(x - (r + Rmin)*gx/norm);
        yc = (int)(y - (r + Rmin)*gy/norm);

        if (xc>=0 && xc<Acc.width() && yc>=0 && yc<Acc.height())
          Acc(xc,yc,r) += norm;
      }
    }
  }
}
