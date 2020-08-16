CImgList<unsigned int> primitives;
CImgList<unsigned char> colors;
CImg<> points = c_elevation.get_elevation3d(primitives,colors,elevation);

// Applique une rotation pour que l'axe z pointe vers le haut.
points.rotate_object3d(1,0,0,100);
