#include <drv/canvas.h>

canvas_t canvas;

void canvas_init(uint8_t* framebuffer, int width, int height, int bpp, int pitch) {
    canvas.framebuffer = framebuffer;
    canvas.width = width;
    canvas.height = height;
    canvas.bpp = bpp;
    canvas.pitch = pitch;

    psf_load();
}

void canvas_drawpixel(int x,int y, int color) {
	int pixelwidth = canvas.bpp / 8;

    unsigned where = x*pixelwidth + y*canvas.pitch;
    canvas.framebuffer[where] = color & 255;              // BLUE
    canvas.framebuffer[where + 1] = (color >> 8) & 255;   // GREEN
    canvas.framebuffer[where + 2] = (color >> 16) & 255;  // RED
}

void canvas_fillrect(unsigned char r, unsigned char g, unsigned char b, unsigned char w, unsigned char h) {
    unsigned char *where = canvas.framebuffer;
    int i, j;

    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            canvas_drawpixel(j, i, (r << 16) + (g << 8) + b);
            //where[j*pixelwidth] = r;
            //where[j*pixelwidth + 1] = g;
            //where[j*pixelwidth + 2] = b;
        }
        where += canvas.pitch;
    }
}

void canvas_drawchar(
	unsigned short int c, // WARN: It's not a char, it's unicode char
	int cx, int cy,
	uint32_t fg, uint32_t bg
) {
	PSF_font *font = (PSF_font*)&_binary_system_8x16_psf_start;

	int pixelsize = canvas.bpp / 8;
	int scanline = canvas.pitch;

	// We need to know how many bytes encode one row
	int bytesperline = (font->width+7) / 8;

	// Unicode translation
	if(unicode != NULL) {
        c = unicode[c];
    }

	// Get the glyph for the character. If there's no
    // glyph for a given character, we'll display the first glyph.
	unsigned char *glyph = (unsigned char*)&_binary_system_8x16_psf_start +
    	font->headersize +
     	(c > 0 && c < font->numglyph ? c : 0) * font->bytesperglyph;

	// Calculate the upper left corner on screen where we want to display.
	// we only do this once, and adjust the offset later. This is faster.
    int offs = (cy * font->height * scanline) +
        ((cx) * (font->width + 1) * pixelsize);

	// Finnaly, displaying pixels
	int x, y, line, mask;

	for(y = 0; y < font->height; y++) { 
		// Save the starting position of the line
        line = offs;
        mask = 1 << (font->width - 1);

		// Display a row
        for(x = 0; x < font->width; x++){
			if(glyph != 0)
            *((PIXEL*)(canvas.framebuffer + line)) = *((unsigned int*)glyph) & mask ? fg : bg;
            /* adjust to the next pixel */
            mask >>= 1;
            line += pixelsize;
        }

		// Adjust to the next line */
        glyph += bytesperline;
        offs  += scanline;
	}
}