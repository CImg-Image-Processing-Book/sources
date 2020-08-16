CImgList<> points; // Liste de sommets pour les vecteurs déplacements
int ind = g_points.width(); // Indice du prochain sommet à ajouter
cimg_forXYZ(motion,x,y,z) if (region(x,y,z))
{
  float
    u = motion(x,y,z,0),
    v = motion(x,y,z,1),
    w = motion(x,y,z,2),
    norm = cimg::hypot(u,v,w);
  if (norm>0.5) { // Le vecteur est suffisamment grand

    // Ajout d'une primitive de type 'segment'.
    CImg<>::vector(x,y,z).move_to(points);
    CImg<>::vector(x + u, y + v, z + w).move_to(points);
    CImg<unsigned int>::vector(ind,ind + 1).
      move_to(g_primitives);

    // Ajout d'une primitive de type 'sphere'.
    CImg<>::vector(x + u - 0.2, y + v, z + w).move_to(points);
    CImg<>::vector(x + u + 0.2, y + v, z + w).move_to(points);
    CImg<unsigned int>::vector(ind + 2,ind + 3,0,0,0).
      move_to(g_primitives);

    // Ajout de la même couleur/opacité pour les deux primitives.
    CImg<unsigned char> color = motion.get_vector_at(x,y,z).
      normalize(0,255);
    g_colors.insert(2,color);
    g_opacities.insert(2,CImg<>::vector(0.7f));

    ind += 4; // Mise à jour de l'indice du prochain sommet
  }
}

// Insertion des sommets des vecteurs déplacements dans la liste
// des sommets de l'objet global.
g_points.append(points.get_append('x'),'x');
