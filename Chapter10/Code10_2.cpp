const char
  *expr = cimg_option("-z",
                      "sinc(sqrt(x^2+y^2)/4)*abs(sin(x/2)*cos(y/2))",
                      "Expression de f(x,y)"),
  *xyrange = cimg_option("-xy",
                         "-30,-30,30,30",
                         "Domaine de définition");
int
  resolution = cimg_option("-r",256,"Résolution du tracé 3D");
float
  sigma = cimg_option("-s",0.0f,"Régularité de la fonction f"),
  factor = cimg_option("-f",150.0f,"Facteur d'échelle");

// Initialisation du domaine d'évaluation de la fonction.
float x0, y0, x1, y1;
if (std::sscanf(xyrange,"%g,%g,%g,%g",&x0,&y0,&x1,&y1)!=4)
throw CImgArgumentException("3D Plotter: "
                            "Le domaine '%s' est invalide.",
                            xyrange);
if (x0>x1) cimg::swap(x0,x1); // On s'assure que x0<x1...
if (y0>y1) cimg::swap(y0,y1); // ... et que y0<y1
if (resolution<8) resolution = 8; // Assure une résolution minimale
