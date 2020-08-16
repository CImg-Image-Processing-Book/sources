CImgList<unsigned int> c_primitives;
CImgList<unsigned char> c_colors;
frame1.normalize(0,255).resize(-100,-100,-100,3,1);

// Calcul d'une élévation 3D texturée avec carte constante.
CImg<> c_points = frame1.get_slice(2*frame1.depth()/3).
                         get_elevation3d(c_primitives,c_colors,
CImg<>(frame1.width(),frame1.height(),1,1,2*frame1.depth()/3));

// Ajout du plan texturé à l'objet 3D global.
g_points.append_object3d(g_primitives,c_points,c_primitives);
g_colors.insert(c_colors);
g_opacities.insert(c_primitives.size(),CImg<>::vector(1));
