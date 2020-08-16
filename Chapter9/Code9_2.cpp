/*
  Calcul d'un gradient d'image couleur.

  imgIn	: Image d'entrée
  E 	: Image du contraste local
  Phi	: Image de l'orientation du gradient
*/
void ColorGradient(CImg<>& imgIn, CImg<>& E, CImg<>& Phi)
{
  CImgList<> eig;

  // Calcul des gradients canal par canal.
  CImgList<> grad = imgIn.get_gradient();

  cimg_forXY(imgIn,x,y)
  {
    CImg<>
      Ix = grad[0].get_vector_at(x,y),
      Iy = grad[1].get_vector_at(x,y),
      M(2,2);
    M(0,0) = Ix.dot(Ix);
    M(1,1) = Iy.dot(Iy);
    M(0,1) = M(1,0) = Iy.dot(Ix);
    eig = M.get_symmetric_eigen();
    E(x,y) = std::sqrt(eig[0](0));
    Phi(x,y) = std::atan2(M(0,0) - M(1,1),2*M(0,1));
  }
}
