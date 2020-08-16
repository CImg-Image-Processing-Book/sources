CImg<> region;
float value = 0;
(+frame1).draw_fill(55,55,7,&value,1,region,40,true);
g_points = region.blur(1.f,1.f,3.f).threshold(0.5f).
                  get_isosurface3d(g_primitives,0.5f);
g_colors.insert(g_primitives.size(),
                CImg<unsigned char>::vector(255,128,0));
g_opacities.insert(g_primitives.size(),
                   CImg<>::vector(1));
