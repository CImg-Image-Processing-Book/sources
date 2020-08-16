/*
  Fonction principale pour la reconstruction tomographique analytique

  sinog  : Sinogramme <=> données d'entrées
  return : Sinogramme filtré par le filtre rampe
*/

int main(int argc, const char * argv[])
{
  cimg_usage("Reconstruction Tomographique par "
             "retroprojection filtrée");
  const char *file = cimg_option("-i","phantom.bmp",
                                 "Entrée : Nom de l'image d'entrée 2D (image carrée)");
  int nbProj = cimg_option("-np",50,
                           "Nombre de projections pour le calcul "
                           "de la transfomée de Radon");
  CImg<>
    image(file),
    radon_img = RadonTransform(image,nbProj),
    fsin_img = SinogramFiltering(radon_img),
    fbp_img = BackProjTransform(fsin_img);

  (image,radon_img,fdb_img).display("Image originale - "
                                    "Sinogramme - "
                                    "Image reconstruite");
  return 0;
}
