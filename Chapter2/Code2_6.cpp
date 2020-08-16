/*
  File: decompose_blocs.cpp
  Description: Exemple de décomposition d’image en blocs rectangulaires
*/
#include "CImg.h"
using namespace cimg_library;

int main(int argc, char **argv) {

  // Lecture des paramètres à partir de la ligne de commande.
  cimg_usage("Décomposition par blocs d’une image couleur");
  const char *filename = cimg_option("-i","image.bmp","Image couleur");
  float
    threshold = cimg_option("-t",25.0f,"Seuil du gradient"),
    sigma = cimg_option("-s",0.7f,"Régularité du gradient");

  // Initialisation des images et de la liste des blocs.
  CImg<unsigned char> img(filename);
  while (img.width()>=CImgDisplay::screen_width() ||
         img.height()>=CImgDisplay::screen_height())
    img.resize(-50,-50,1,-100,2);

  CImg<> lum = img.get_norm().blur(sigma).normalize(0,255);
  CImgList<> grad = lum.get_gradient("xy");
  CImg<> normGrad = (grad[0].get_sqr() += grad[1].get_sqr()).sqrt();

  CImgList<int> blocs;
  CImg<int>::vector(0,0,img.width() - 1,img.height() - 1).
    move_to(blocs);

  // Calcul de la décomposition de l’image en blocs.
  for (unsigned int l = 0; l<blocs.size(); ) {
    CImg<int>& bloc = blocs[l];
    int
      x0 = bloc[0], y0 = bloc[1],
      x1 = bloc[2], y1 = bloc[3];
    if (normGrad.get_crop(x0,y0,x1,y1).max()>threshold &&
        std::min(x1 - x0,y1 - y0)>8) {
      int xc = (x0 + x1)/2, yc = (y0 + y1)/2;
      CImg<int>::vector(x0,y0,xc - 1,yc - 1).move_to(blocs);
      CImg<int>::vector(xc,y0,x1,yc - 1).move_to(blocs);
      CImg<int>::vector(x0,yc,xc - 1,y1).move_to(blocs);
      CImg<int>::vector(xc,yc,x1,y1).move_to(blocs);
      blocs.remove(l);
    } else ++l;
  }

  // Calcul du rendu de la décomposition.
  CImg<unsigned char> res(img.width(),img.height(),1,3,0);
  CImg<int> coords(img.width(),img.height(),1,4,0);
  cimglist_for(blocs,l) {
    CImg<int>& bloc = blocs[l];
    int
      x0 = bloc[0], y0 = bloc[1],
      x1 = bloc[2], y1 = bloc[3];
    CImg<unsigned char> color = img.get_crop(x0,y0,x1,y1).
      resize(1,1,1,3,2);
    res.draw_rectangle(x0,y0,x1,y1,color.data(),1);
    coords.draw_rectangle(x0,y0,x1,y1,bloc.data());
  }

  // Ajout des bordures noires.
  res.mul(1 - (res.get_shift(1,1,0,0,0) - res).norm().cut(0,1));

  // Démarrage du visualiseur interactif.
  CImgDisplay disp(res,"Tutoriel CImg : Decomposition en blocs",0);
  unsigned char white[] = { 255,255,255 }, black[] = { 0,0,0 };
  while (!disp.is_closed() && !disp.is_keyESC()) {
    int
      x = disp.mouse_x(),
      y = disp.mouse_y();
    if (x>=0 && y>=0) {
      int
        x0 = coords(x,y,0), y0 = coords(x,y,1),
        x1 = coords(x,y,2), y1 = coords(x,y,3),
        xc = (x0 + x1)/2, yc = (y0 + y1)/2;
      CImg<unsigned char>
        pImg = img.get_crop(x0,y0,x1,y1).resize(128,128,1,3,1),
        pGrad = normGrad.get_crop(x0,y0,x1,y1).resize(128,128,1,3,1).
        normalize(0,255).
        map(CImg<unsigned char>::hot_LUT256());
      (+res).
        draw_text(10,3,"X, Y = %d, %d",white,0,1,24,x,y).
        draw_rectangle(x0,y0,x1,y1,black,0.25f).
        draw_line(74,109,xc,yc,white,0.75,0xCCCCCCCC).
        draw_line(74,264,xc,yc,white,0.75,0xCCCCCCCC).
        draw_rectangle(7,32,140,165,white).
        draw_rectangle(7,197,140,330,white).
        draw_image(10,35,pImg).
        draw_image(10,200,pGrad).
        display(disp);
    }
    disp.wait(); // Attend un évènement utilisateur
    if (disp.is_resized()) disp.resize(disp);
  }
  return 0;
}
