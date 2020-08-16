CImg<char> s_expr(1024);
std::sprintf(s_expr,"x = lerp(%g,%g,x/(w-1));"
                    "y = lerp(%g,%g,y/(h-1));"
                    "%s",
                    x0,x1,y0,y1,expr);
CImg<> elevation(resolution,resolution,1,1,s_expr,true);
elevation.blur(sigma).normalize(0,factor);
