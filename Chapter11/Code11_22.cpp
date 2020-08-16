// Récupération des coordonnées de la souris et de l'état du bouton.
int xm = disp.mouse_x(), ym = disp.mouse_y(), bm = disp.button();

if (xm>=0 && bm) { // L'utilisateur a cliqué dans la fenêtre
  float // Coordonnées de la souris en pourcentage.
    xmp = xm*100.0f/(disp.width()-1),
    ymp = ym*100.0f/(disp.height()-1);

  // Détermine si un point clé existant est sélectionné
  // par l'utilisateur.
  if (selected<0) cimglist_for(keypoints,l) {
    int
      x = (int)cimg::round(keypoints(l,0)),
      y = (int)cimg::round(keypoints(l,1));
    if (cimg::hypot(x - xmp,y - ymp)<15) { selected = l; break; }
  }

  if (selected<0 && bm&1) {
    // Pas de sélection + bouton gauche -> Ajoute nouveau point-clé.
    int
      xw = (int)(xmp*(img.width()-1)/100),
      yw = (int)(ymp*(img.height()-1)/100);
    CImg<>::vector(xmp,ymp,
                   warp.atXY(xw,yw,0,0)*100/(img.width()-1),
                   warp.atXY(xw,yw,0,1)*100/(img.height()-1)).
                   move_to(keypoints);
    selected = (int)keypoints.size() - 1; // Garde le en sélection

  } else if (selected>=0 && bm&1) {
    // Sélection + bouton gauche -> Déplace point-clé.
    keypoints(selected,0) = xmp;
    keypoints(selected,1) = ymp;

  } else if (selected>=0 && bm&2) {
    // Sélection + bouton droit -> Supprime point-clé.
    keypoints.remove(selected);
    selected = -1;
    disp.set_button(); // Supprime l'évènement 'bouton appuyé'
  }
} else if (!bm) selected = -1; // Pas de bouton -> pas de sélection
