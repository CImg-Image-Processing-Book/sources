CImg<> get_labels(CImg<>& lab, CImg<>& centroids, float S, float m) {
  CImg<> labels(lab.width(),lab.height(),1,2,1e20);

  // Teste les pixels voisins de chaque centroïde,
  // dans un voisinage de taille 2Sx2S.
  cimg_forX(centroids,k)
  {
    float
      xc = centroids(k,0), yc = centroids(k,1),
      Lc = centroids(k,2), ac = centroids(k,3), bc = centroids(k,4);
      int
      x0 = std::max((int)(xc - S),0),
      y0 = std::max((int)(yc - S),0),
      x1 = std::min((int)(xc + S - 1),lab.width() - 1),
      y1 = std::min((int)(yc + S - 1),lab.height() - 1);

    // Boucle sur le voisinage (x0,y0)-(x1,y1) de taille 2Sx2S.
    cimg_for_inXY(lab,x0,y0,x1,y1,x,y)
    {
      float dist = D(x,y,lab(x,y,0),lab(x,y,1),lab(x,y,2),
                     xc,yc,Lc,ac,bc,S,m);
      if (dist<labels(x,y,1))
      {
        labels(x,y,0) = k;
        labels(x,y,1) = dist;
      }
    }
  }

  // Labélise les pixels restants en les testant
  // vis à vis de tous les centroïdes.
  cimg_forXY(labels,x,y) if (labels(x,y)>=centroids.width())
  {
    // Le pixel (x,y) n'est pas encore labélisé.
    float
      L = lab(x,y,0),
      a = lab(x,y,1),
      b = lab(x,y,2);
      float distmin = 1e20;
      int kmin = 0;

    // Teste vis à vis de tous les centroïdes.
    cimg_forX(centroids,k)
    {
      float
        xc = centroids(k,0),
        yc = centroids(k,1),
        Lc = centroids(k,2),
        ac = centroids(k,3),
        bc = centroids(k,4),
        dist = D(x,y,lab(x,y,0),lab(x,y,1),lab(x,y,2),
                 xc,yc,Lc,ac,bc,S,m);
      if (dist<distmin)
      {
        distmin = dist;
        kmin = k;
      }
    }
    labels(x,y,0) = kmin;
    labels(x,y,1) = distmin;
  }

  return labels;
}
