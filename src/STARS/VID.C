
//#include "ptc.h"


/* ptc objects */
PTC_FORMAT format = 0;
PTC_SURFACE surface = 0;
PTC_CONSOLE console = 0;
PTC_PALETTE pal = 0;


void cleanup()
{
    /* destroy objects */
    ptc_format_destroy(format);
    ptc_surface_destroy(surface);
    ptc_console_destroy(console);
}


void open_vid()
{
	ptc_int32 pal32[256];
	int i;


	console = ptc_console_create();
	format = ptc_format_create_indexed(8);
	ptc_console_open_resolution(console, "stars", 320, 200, format, 0);
	surface = ptc_surface_create(ptc_console_width(console),ptc_console_height(console),format);
	pal = ptc_palette_create();

//   for (int i=0; i<256; i++) set_col(i, i/12, i/8, i/4);
	for (i=0; i<256; i++)
	{
		pal32[i] = ((i/3) << 16) + ((i/2) << 8) + ((i) << 0);
	}

	ptc_palette_load(pal, pal32);
	ptc_console_palette_set(console, pal);
	ptc_surface_palette_set(surface, pal);
}



void show(char *m)
{
	ptc_char8 *pixels;

	pixels = (ptc_char8*) ptc_surface_lock(surface);

//	for (i=0; i<64000; i++)
//	pixels[i] = zinco6[i];
//	memcpy(m, pixels, 64000);
	memcpy(pixels, m, 64000);

            // draw color [r,g,b] at position [x,y]
//            pixels[x+y*width] = (r<<16) + (g<<8) + b;

        /* unlock surface */
        ptc_surface_unlock(surface);

        /* copy to console */
        ptc_surface_copy(surface,console);

        /* update console */
        ptc_console_update(console);
}


void close_vid()
{
    /* close console */
    ptc_console_close(console);

    /* cleanup */
    cleanup();

    /* exit */
 //   return 0;
}
