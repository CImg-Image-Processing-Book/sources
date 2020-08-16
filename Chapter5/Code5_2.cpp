int Derivatif(CImg<>& imageIn)
{
  // Calcul du gradient de l'image par différences finies centrées.
  CImgList<> grad = imageIn.get_gradient();

  // Calcul de la norme et de la phase du gradient.
  CImg<>
    norme = (grad[0].get_sqr() + grad[1].get_sqr()).sqrt(),
    phi = grad[1].get_atan2(grad[0]);

  // Affichage des images.
  (grad[0],grad[1],norme,phi).display();

  return 1;
}
