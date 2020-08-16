CImgList<> grad = lab.get_gradient("xy");
CImg<> grad_norm = (grad>'c').norm(); // Norme du gradient
CImg<> centroids(cimg::round(img.width()/S),
cimg::round(img.height()/S),1,5);
int S1 = S/2, S2 = S - 1 - S1;

cimg_forXY(centroids,x,y) {
  int
    xc = x*S + S1,
    yc = y*S + S1,
    x0 = std::max(xc - S1,0),
    y0 = std::max(yc - S1,0),
    x1 = std::min(xc + S2,img.width() - 1),
    y1 = std::min(yc + S2,img.height() - 1);

  // Récupère la position du point de norme de gradient
  // minimum dans un voisinage SxS.
  CImg<> st = grad_norm.get_crop(x0,y0,x1,y1).get_stats();
  centroids(x,y,0) = x0 + st[4];
  centroids(x,y,1) = y0 + st[5];
  centroids(x,y,2) = lab(xc,yc,0);
  centroids(x,y,3) = lab(xc,yc,1);
  centroids(x,y,4) = lab(xc,yc,2);
}
// Déroule en une image de taille Nx1x1x5.
centroids.resize(centroids.width()*centroids.height(),1,1,5,-1);
