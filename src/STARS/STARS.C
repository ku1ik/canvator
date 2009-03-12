
#include <stdio.h>
//#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
//#include <math.h>
#include <time.h>
#include "ptc.h"

unsigned char old_screen[320*200];
unsigned char screen[320*200];
#include "back.c"
#include "sincos.c"
#include "vid.c"

/*
#ifndef M_PI
#define M_PI 3.14159265358979324
#endif
#ifndef M_1_PI
#define M_1_PI 0.318309886183790672
#endif
*/
#define M_PI_1800 0.00174532925199433


//================= part from hebe ====================

#define X v->rotloc_x
#define Y v->rotloc_y
#define Z v->rotloc_z


typedef struct
{
   long x, y, z;

} ANGLE;

typedef struct _ve
{
   float x, y, z;
   float rotloc_x, rotloc_y, rotloc_z;
   long drawx, drawy;
   char color;
   int visible;
   struct _ve *next;

} VERTEX;

typedef struct _ob
{
   VERTEX *vertex_list;
   VERTEX origin;
   ANGLE angle;
   struct _ob *next;

} OBJECT;


//========================================================================

OBJECT *stars;


void rotate_object(OBJECT *o, float x, float y, float z)
{
 if (o)
 {
   o->angle.x += (long)x;
   o->angle.y += (long)y;
   o->angle.z += (long)z;

   if (o->angle.x >= 3600) o->angle.x -= 3600;
   if (o->angle.y >= 3600) o->angle.y -= 3600;
   if (o->angle.z >= 3600) o->angle.z -= 3600;

   if (o->angle.x < 0) o->angle.x += 3600;
   if (o->angle.y < 0) o->angle.y += 3600;
   if (o->angle.z < 0) o->angle.z += 3600;
 }
}

void rotate_vertex_local(VERTEX *v, ANGLE angle)
{
   float Xt, Yt, Zt;

   X = v->x;
   Y = v->y;
   Z = v->z;

   Yt = Y * cosin[angle.x] - Z * sinus[angle.x];
   Zt = Y * sinus[angle.x] + Z * cosin[angle.x];
   Y = Yt;
   Z = Zt;

   Xt = X * cosin[angle.y] - Z * sinus[angle.y];
   Zt = X * sinus[angle.y] + Z * cosin[angle.y];
   X = Xt;
   Z = Zt;

   Xt = X * cosin[angle.z] - Y * sinus[angle.z];
   Yt = X * sinus[angle.z] + Y * cosin[angle.z];
   X = Xt;
   Y = Yt;

}


void rotate_object_local(OBJECT *o)
{
   VERTEX *v;

   v = o->vertex_list;
   while (v)
   {
      rotate_vertex_local(v, o->angle);
      v = v->next;
   }
}

void cast_object(OBJECT *o)
{
   VERTEX *v;
   float z;

   v = o->vertex_list;
   while (v)
   {
      z = v->rotloc_z + o->origin.z;
      v->drawx = 160 + (long)((v->rotloc_x + o->origin.x) / z * 320.0);
      v->drawy = 100 + (long)((v->rotloc_y + o->origin.y) / z * 200.0);
      v = v->next;
   }
}


void vis_object(OBJECT *o)
{
   VERTEX *v;

   v = o->vertex_list;
   while (v)
   {
      if (((v->rotloc_z + o->origin.z > 0.0) || (v->rotloc_z + o->origin.z < 0.0 && !screen[v->drawx+v->drawy*320])) && v->drawx >= 0 && v->drawx < 320 && v->drawy >= 0 && v->drawy < 200)
      if (v->drawx >= 0 && v->drawx < 320 && v->drawy >= 0 && v->drawy < 200)
         v->visible = 1;
      else
         v->visible = 0;
      v = v->next;
   }
}



VERTEX * alloc_vertex()
{
   VERTEX *v;

   v = (VERTEX *)malloc(sizeof(VERTEX));
   memset(v, 0, sizeof(VERTEX));
//   memset(v, 0, sizeof(VERTEX));
   return v;
}

OBJECT * alloc_object()
{
   OBJECT *o;

   o = (OBJECT *)malloc(sizeof(OBJECT));
   memset(o, 0, sizeof(OBJECT));
//   memset(o, 0, sizeof(OBJECT));
   return o;
}



float deg_to_rad(long deg)
{
   return (float)((float)deg * M_PI_1800);  // 1800.0 = * 0.000556
}



void translate_object(OBJECT *o, float x, float y, float z)
{
   o->origin.x += x;
   o->origin.y += y;
   o->origin.z += z;
}

OBJECT *add_stars()
{
   VERTEX *v;

   if (!(stars = alloc_object())) return 0;
   for (int i=0; i<32; i++)
   {
      if (!(v = alloc_vertex())) return 0;
      v->x = -1.0 + 2.0 * ((float)rand() / 32767.0);
      v->y = -1.0 + 2.0 * ((float)rand() / 32767.0);
      v->z = -1.0 + 2.0 * ((float)rand() / 32767.0);
      v->next = stars->vertex_list;
      stars->vertex_list = v;
   }
   return stars;
}

void pix(long x, long y, unsigned char col)
{
   long c,i;

   i = x + (y << 8) + (y << 6);
   c = old_screen[i];
   c += col;
   c = ((c << 3) + (c << 2) + c + c) >> 4;
   if (c > 255) c = 255;
   old_screen[i] = c;
}


void render_star(VERTEX *v)
{
//   ((char *)screen)[v->drawx+v->drawy*320] = 255;
   float size;
   long x, y, half, dx, dy;
   unsigned char c;

//	if (v->rotloc_z > 0.0) return;

   size = 1.0 / (v->rotloc_z + stars->origin.z);
   c = size * 48.0;
   if (c > 255) c = 255;
   half = size * 10;
   for (y=-half; y<=half; y++)
   {
      if (y + v->drawy < 0 || y + v->drawy > 199) continue;
      for (x=-half; x<=half; x++)
      {
         dx = v->drawx + x;
         if (dx < 0 || dx > 319) continue;
         dy = v->drawy + y;
         ((unsigned char *)screen)[dx+dy*320] = c;
//         pix(dx, dy, c);
      }
   }
}

void render_object(OBJECT *o)
{
   VERTEX *v;

   v = o->vertex_list;
   while (v)
   {
      if (v->visible) render_star(v);
      v = v->next;
   }
}


void alfa()
{
   long c;
   for (int i=0; i<64000; i++)
   {
      c = screen[i];
      c += old_screen[i];
//      c = c * 0.9;
      c = ((c << 3) + (c << 2) + c + c ) >> 4;
      if (c > 255) c = 255;
      old_screen[i] = c;
   }
}


int main()
{
   clock_t t;
   long fr;

   for (int k=0; k<64000; k++) back[k] = back[k] / 7;

   srand(666);
   if (!add_stars()) { printf("err\n"); exit(1); }

	open_vid();
//   set_mode(0x13);
//   for (int i=0; i<256; i++) set_col(i, i/12, i/8, i/4);

   translate_object(stars, 0.0, 0.0, 2.0);

   fr = 0;
   t = clock();
	while (!ptc_console_key(console))
   {
//      memfill_d((long)screen, 16000, 0);
//      memcopy_d((long)back, (long)screen, 16000);
	memcpy(screen, back, 64000);
//      memset(screen, 0, 64000);
      rotate_object_local(stars);
      cast_object(stars);
      vis_object(stars);
      render_object(stars);
      alfa();
//      memcpy((char *)0xA0000, old_screen, 64000);
//      memcopy_d((long)old_screen, 0xA0000, 16000);
	show(old_screen);

      rotate_object(stars, 9, 9, 9);
      fr++;
   }
   t = clock() - t;
//   getch();

	close_vid();
//   set_mode(3);
   printf("f/s = %f\n", ((float)fr * CLOCKS_PER_SEC / (float)t));
   return 0;
}


