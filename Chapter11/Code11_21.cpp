do {
  // Récupération de l'image de la webcam
  img.load_camera(0,640,480,0,false);

  // Estimation du champ de déplacement RBF
  CImg<> warp = get_RBF(img,keypoints);

  // Affichage de l'image dans la fenêtre.
  if (!disp) disp.assign(img,"RBF-Based Deformation",0);
  CImg<unsigned char> visu = img.get_resize(disp,1);
  cimglist_for(keypoints,l) { // Affichage des points-clés
    int
      x = (int)cimg::round(keypoints(l,0)*(visu.width()-1)/100),
      y = (int)cimg::round(keypoints(l,1)*(visu.height()-1)/100);
    visu.draw_circle(x,y,8,black,0.75f).draw_circle(x,y,6,white,0.75f);
  }
  disp.display(visu).wait(40);
  if (disp.is_resized()) disp.resize();
} while (!disp.is_closed() && !disp.is_keyESC());
