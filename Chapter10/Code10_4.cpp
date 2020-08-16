CImg<unsigned char>
  lut(4,1,1,3,"!x?[255,79,106]:"     // Rouge
              "x==1?[196,115,149]:"  // Orange
              "x==2?[231,250,90]:"   // Jaune
              "[255,255,255]",true); // Blanc
lut.resize(256,1,1,3,3);

// Création d'une représentation couleur de 'elevation'.
CImg<unsigned char>
  c_elevation = elevation.get_normalize(0,255).map(lut);
