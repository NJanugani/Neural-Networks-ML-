#include <stdio.h>
#include <pgm.h>
#include <bpnn.h>

extern void exit();

#define TARGET_HIGH 0.9
#define TARGET_LOW 0.1


load_target(img, net)
IMAGE *img;
BPNN *net;
{
  int scale;
  char userid[40], head[40], expression[40], eyes[40], photo[40];

  userid[0] = head[0] = expression[0] = eyes[0] = photo[0] = '\0';

  /*** scan in the image features ***/
  sscanf(NAME(img), "%[^_]_%[^_]_%[^_]_%[^_]_%d.%[^_]",
    userid, head, expression, eyes, &scale, photo);

  if (!strcmp(head, "left")) {
    net->target[1] = TARGET_HIGH;
  } else {
    net->target[1] = TARGET_LOW;
  }


   if (!strcmp(head, "right")) {
    net->target[2] = TARGET_HIGH;
  } else {
    net->target[2] = TARGET_LOW;
  }


   if (!strcmp(head, "up")) {
    net->target[3] = TARGET_HIGH;
  } else {
    net->target[3] = TARGET_LOW;
  }


   if (!strcmp(head, "straight")) {
    net->target[4] = TARGET_HIGH;
  } else {
    net->target[4] = TARGET_LOW;
  }

}

load_input_with_image(img, net)
IMAGE *img;
BPNN *net;
{
  double *units;
  int nr, nc, imgsize, i, j, k;

  nr = ROWS(img);
  nc = COLS(img);
  imgsize = nr * nc;;
  units = net->input_units;
  k = 1;
  for (i = 0; i < nr; i++) {
    for (j = 0; j < nc; j++) {
      units[k] = ((double) img_getpixel(img, i, j)) / 255.0;
      k++;
    }
  }
}
