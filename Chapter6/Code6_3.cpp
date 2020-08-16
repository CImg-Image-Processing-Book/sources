/*
  Amélioration subpixellique de la position de points d'intérêt.

  imgIn : Image d'entrée
  p     : Point d'intérêt
  n     : Taille de la fenêtre autour de p
*/
CImg<> SubpixelCornerDetection(CImg<>& imgIn, CImg<int>& p, int n)
{
  int n2 = n/2, i = 0;

  // Calcul des gradients de l'image.
  CImgList<> grad = imgIn.get_gradient();

  // Seul le voisinage de taille n peut être pris en compte.
  CImg<>
    gx = grad(0).crop(p(0) - n2,p(1) - n2,
                      p(0) + n2,p(1) + n2),
    gy = grad(1).crop(p(0) - n2,p(1) - n2,
                      p(0) + n2,p(1) + n2),
    A,
    b(1,n*n);
  cimg_forXY(gx,x,y)
  {
    // Coordonnées de yi dans l'image originale.
    CImg<int> yi(1,2);
    yi[0] = p(0) - n2 + x;
    yi[1] = p(1) - n2 + y;
    CImg<> gradi(2,1);
    gradi[0] = gx(x,y);
    gradi[1] = gy(x,y);
    A.append(gradi,'y');
    b(i) = gradi.dot(yi);
    ++i;
  }

  // Résolution du système aux équations normales.
  return (A.get_transpose()*A).get_invert()*A.transpose()*b;
}
