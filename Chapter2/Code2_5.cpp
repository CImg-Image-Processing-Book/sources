unsigned char white[] = { 255,255,255 }, black[] = { 0,0,0 };
(+res).
draw_text(10,3,"X, Y = %d, %d",white,0,1,24,x,y).
draw_rectangle(x0,y0,x1,y1,black,0.25f).
draw_line(74,109,xc,yc,white,0.75,0xCCCCCCCC).
draw_line(74,264,xc,yc,white,0.75,0xCCCCCCCC).
draw_rectangle(7,32,140,165,white).
draw_rectangle(7,197,140,330,white).
draw_image(10,35,pImg).
draw_image(10,200,pGrad).
display(disp);
