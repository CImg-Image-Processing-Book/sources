/*
  Suivi d'objet par corrélation de phase.
*/
int main(int argc, const char **argv)
{
  cimg_usage("Suivi d'objet par recalage (corrélation de phase)");
  int
    roi_x0 = cimg_option("-x",102,"Abscisse de la  ROI"),
    roi_y0 = cimg_option("-y",151,"Ordonnée de la ROI"),
    roi_w  = cimg_option("-w",64,"Largeur de la ROI"),
    roi_h  = cimg_option("-h",64,"Hauteur de la ROI");
  bool save = cimg_option("-o",1,"Sauvegarde (0 ou 1)");

  // Lecture d'une séquence d'images.
  CImg<> img = CImg<>("frame_0000.bmp").channel(0);
  img.append(CImg<>("frame_0005.bmp").channel(0),'z');
  img.append(CImg<>("frame_0010.bmp").channel(0),'z');
  ...;
  img.append(CImg<>("frame_0135.bmp").channel(0),'z');
  img.append(CImg<>("frame_0140.bmp").channel(0),'z');

  int
    tx,ty,         // Translation
    x0 = roi_x0,   // Position de l'objet (abscisse)
    y0 = roi_y0;   // Position de l'objet (ordonnée)

  for (int f = 0; f<img.depth() - 1; ++f)
  {
    CImg<>
      IS = img.get_slice(f).
               crop(x0,y0,x0 + roi_w - 1,y0 + roi_h - 1),
      IC = img.get_slice(f + 1).
               crop(x0,y0,x0 + roi_w - 1,y0 + roi_h - 1);

    // Estimation de mouvement par corrélation de phase.
    PhaseCorrelation(IS,IC,tx,ty);

    // Mise à jour de la position de l'objet.
    x0 -= tx;
    y0 -= ty;

    // Enregistrement du suivi.
    if (save)
    {
      CImg<unsigned char> out(img.width(),img.height(),1,3,0);
      unsigned char mycolor[] = { 243,102,25 };

      out.draw_image(0,0,0,0,img.get_slice(f + 1),1).
        draw_image(0,0,0,1,img.get_slice(f + 1),1).
        draw_image(0,0,0,2,img.get_slice(f + 1),1).
        draw_rectangle(x0,y0,
                       x0 + roi_w - 1,y0 + roi_h - 1,mycolor,0.5f);

      std::string fileName = "Tracking_" + std::to_string(f + 1) + ".png";
      out.normalize(0,255).save_png(fileName.c_str());
    }
  }
  return 0;
}
