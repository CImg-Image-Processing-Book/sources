int main(int argc,char **argv)
{
  // Passage des paramètres par ligne de commande
  cimg_usage("Compression simplifiée JPEG ");
  const char
    *input_f = cimg_option("-i","lena.bmp","Image d'entrée"),
    *output_f = cimg_option("-o",(char*)0,"Image de sortie");
  float quality = cimg_option("-q",1.0,"Facteur de qualité");

  // Lecture de l'image d'entrée.
  CImg<> imgIn(input_f);
  imgIn.channel(0);

  // Pré-calcul des valeurs des cosinus.
  CImg<> cos_values = genCosValues();

  // Calcul de l'image par DCT + quantification.
  CImg<> dct_image = JPEGEncoder(imgIn,quality,cos_values);

  // Reconstruction de l'image.
  CImg<> comp_image = JPEGDecoder(dct_image,quality,cos_values);

  // Affichage de l'écart quadratique entre les images.
  float dist = distorsionRate(imgIn,comp_image);
  std::cout << "Distorsion Rate : " << dist << std::endl;

  // Affichage des images.
  (imgIn,dct_image,comp_image).display("Image d'entrée - "
                                       "Image des blocs DCT - "
                                       "Image decompressée");

  // Sauvegarde de l'image (si le nom existe).
  if (output_f)
    comp_image.save(output_f);
}
