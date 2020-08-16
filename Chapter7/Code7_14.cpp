float E = 0; // Erreur résiduelle
do {
  // Affecte un centroïde à chaque pixel de l'image.
  CImg<> labels = get_labels(lab,centroids,S,m);

  // Recalcule les positions et les couleurs moyennes
  // de chaque centroïde.
  CImg<>
    next_centroids = centroids.get_fill(0),
    accu(centroids.width(),1,1,1,0);
  cimg_forXY(img,x,y)
  {
    int k = (int)labels(x,y);
    next_centroids(k,0) += x;
    next_centroids(k,1) += y;
    next_centroids(k,2) += lab(x,y,0);
    next_centroids(k,3) += lab(x,y,1);
    next_centroids(k,4) += lab(x,y,2);
    ++accu[k];
  }
  accu.max(1e-8f);
  next_centroids.div(accu);

  // Calcul de l'erreur résiduelle (en norme L1).
  E = (next_centroids - centroids).norm(1).sum()/centroids.width();
  centroids.swap(next_centroids);
} while (E>0.25);
