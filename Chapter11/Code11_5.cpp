/*
  distorsionRate : Calcul de l'écart quadratique.

  image      : Image originale
  comp_image : Image "compressée" (DCT + quantification)
  return     : Ecart quadratique
*/
float distorsionRate(CImg<>& image, CImg<>& comp_image)
{
  float rate = (image - comp_image).sqr().sum();
  return rate /= image.width()*image.height();
}
