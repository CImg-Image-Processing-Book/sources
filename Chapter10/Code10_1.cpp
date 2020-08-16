// Structures de l'objet 3D global, que l'on va générer.
CImg<> g_points;
CImgList<unsigned int> g_primitives;

// Ajout des tores en chaine.
CImgList<unsigned int> primitives;
CImg<> points;
for (unsigned int k = 0; k<8; ++k) {
  points = CImg<>::torus3d(primitives,100,30);
  points.resize_object3d(240,160,60).shift_object3d(130.f*k,0.f,0.f);
  if (k%2) points.rotate_object3d(1,0,0,90);
  g_points.append_object3d(g_primitives,points,primitives);
}

// Ajout de la sphère en bout de chaine.
points = CImg<>::sphere3d(primitives,150).shift_object3d(1000,0,0);
g_points.append_object3d(g_primitives,points,primitives);

// Création d'une image de fond 800x600 en dégradé de couleurs.
CImg<unsigned char> background(1,2,1,3,
                               "y?[64,128,255]:[255,255,255]",false);
background.resize(800,600,1,3,3);

// Lancement du visualiseur 3D interactif.
background.display_object3d("3D Object",g_points,g_primitives);
