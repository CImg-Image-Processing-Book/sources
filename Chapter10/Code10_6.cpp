CImg<unsigned char> background(1,2,1,3,
                               "y?[64,128,255]:[255,255,255]",false);
background.resize(800,600,1,3,3);
const unsigned char black[] = { 0,0,0 };
background.draw_text(2,2,"f(x,y) = %s",black,
                     (unsigned char*)0,1.0f,24U,expression);

// Lancement du visualiseur interactif d'objet 3D.
background.display_object3d("3D Plotter",points,primitives,colors);
