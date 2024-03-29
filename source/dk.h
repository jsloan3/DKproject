/* GIMP RGBA C-Source image dump (dk.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[32 * 32 * 4 + 1];
} dk = {
  32, 32, 4,
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\270\000\000\001\270\000\000h\270\000\000\377\270\000\000\377\270\000"
  "\000\377\270\000\000\377\270\000\000\377\270\000\000\066\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\270\000\000P\306((\377\306((\377\270\000\000\377\270\000\000\377\306"
  "((\377\306((\377\270\000\000\377\270\000\000\035\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\270"
  "\000\000*\306((\377\377\270U\377\377\270U\377\377f\000\377\306((\377\377\270U\377"
  "\377\270U\377\377f\000\377\270\000\000\326\270\000\000\037\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\270U\012\377\270U\062\377"
  "f\000\062\270\000\000\326\377f\000\377\377\270U\377\000\000\000\377\377\270U\377\377\270"
  "U\377\377\270U\377\000\000\000\377\377\270U\377\306((\377\306((\255\377\270U\062"
  "\377\270U\012\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377"
  "\270Um\377\270U\377\377f\000\377\270\000\000\377\377\270U\377\377\270U\377\377"
  "\353\356\377\000\000\000\377\377\270U\377\000\000\000\377\377\353\356\377\377\270U\377"
  "\377\270U\377\377f\000\377\377\270U\377\377\270Um\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\270U\377\377\270U\377\377f\000\377\270\000"
  "\000\377\306((\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377"
  "\270U\377\377\270U\377\377\270U\377\270\000\000\377\377f\000\377\377\270U\377\377"
  "\270U\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377f\000=\306((e\377\270U"
  "\377\377\270U\377\377\270U\377\377f\000\377\377\270U\377\377\270U\377\377\270"
  "U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377"
  "f\000\377\377\270U\377\377\270U\377\377\270U\377\306((e\377f\000=\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377"
  "f\000\026\377f\000n\377f\000\305\270\000\000\377\306((\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\377\377f\000\377\377f\000\377\377f\000\377"
  "\377f\000\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U"
  "\377\306((\377\270\000\000\377\377f\000\305\377f\000n\377f\000\026\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377f\000\247\377f\000\377\306"
  "((\377\270\000\000\377\306((\377\377\270U\377\377\270U\377\377\270U\377\377f"
  "\000\377\377f\000\377\377f\000\377\377f\000\377\377f\000\377\377f\000\377\377f\000\377"
  "\377f\000\377\377\270U\377\377\270U\377\377\270U\377\306((\377\270\000\000\377"
  "\306((\377\377f\000\377\377f\000\247\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\377f\000\\\377f\000\232\306((\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\306((\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270"
  "U\377\377\270U\377\377\270U\377\377\270U\377\306((\377\270\000\000\377\270\000"
  "\000\377\270\000\000\377\306((\377\377f\000\232\377f\000\\\000\000\000\000\000\000\000\000\000\000\000\000"
  "\377f\000>\377f\000\327\306((\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000"
  "\377\306((\377\377f\000\377\377f\000\377\377\270U\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270"
  "U\377\377\270U\377\377\270U\377\377f\000\377\306((\377\270\000\000\377\270\000\000"
  "\377\270\000\000\377\270\000\000\377\306((\377\377f\000\327\377f\000>\000\000\000\000\270\000\000"
  "$\270\000\000\323\270\000\000\377\270\000\000\377\270\000\000\377\377f\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270"
  "U\377\377\270U\377\377\270U\377\377\270U\377\270\000\000\377\270\000\000\377\270"
  "\000\000\377\270\000\000\377\377f\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000"
  "\000\323\270\000\000$\270\000\000\063\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\377f\000\377\377f\000\377\306((\377\270\000\000\377\270\000\000\377\270\000\000\377\306"
  "((\377\377f\000\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377"
  "\270U\377\377\270U\377\377\270U\377\306((\377\306((\377\270\000\000\377\270\000"
  "\000\377\306((\377\377f\000\377\377f\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\063\270\000\000\063\270\000\000\377\270\000\000\377\270\000\000\377\270"
  "\000\000\377\270\000\000\377\377f\000\377\377f\000\377\377f\000\377\270\000\000\377\270\000\000"
  "\377\270\000\000\377\306((\377\306((\377\306((\377\306((\377\306((\377\306(("
  "\377\306((\377\306((\377\270\000\000\377\270\000\000\377\270\000\000\377\377f\000\377\377"
  "f\000\377\377f\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000"
  "\000\377\270\000\000\063\270\000\000\063\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000"
  "\377\270\000\000\377\270\000\000\377\377f\000\377\377f\000\377\377f\000\377\306((\377\377"
  "\270U\377\377\270U\377\377\270U\377\270\000\000\377\270\000\000\377\270\000\000\377\270"
  "\000\000\377\377\270U\377\377\270U\377\377\270U\377\306((\377\377f\000\377\377"
  "f\000\377\377f\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000"
  "\000\377\270\000\000\377\270\000\000\063\270\000\000\001\270\000\000h\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\306((\377"
  "\306((\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000h\270\000\000\001\000\000\000\000\270\000\000\000\270\000\000\227"
  "\270\000\000\376\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\377\270U\377\377\270U\377\377\270U\377"
  "\377f\000\377\377f\000\377\377\270U\377\377\270U\377\377\270U\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\376\270\000\000\227\270\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\270\000\000\257\270\000\000\332\270\000\000\351\270\000\000\377\270\000\000\377\270\000"
  "\000\377\270\000\000\377\270\000\000\377\270\000\000\377\306((\377\377\270U\377\377\270"
  "U\377\377f\000\377\377f\000\377\377\270U\377\377\270U\377\306((\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\351"
  "\270\000\000\332\270\000\000\257\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\306((f\270\000\000\377\270\000\000\377\306((\377\270\000\000\377\306"
  "((\377\306((\377\377\270U\377\377f\000\377\377\270U\377\377\270U\377\377\270"
  "U\377\377\270U\377\377f\000\377\377\270U\377\306((\377\306((\377\270\000\000\377"
  "\306((\377\270\000\000\377\270\000\000\377\306((f\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377f\000\012\377f\000\204\306((\377\270"
  "\000\000\377\377f\000\377\377f\000\377\377f\000\377\377f\000\377\377f\000\377\377f\000\377"
  "\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377f\000\377\377f\000\377"
  "\377f\000\377\377f\000\377\377f\000\377\377f\000\377\270\000\000\377\306((\377\377f\000"
  "\204\377f\000\012\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\377f\000m\377f\000\377\270\000\000\377\270\000\000\377\270\000\000\377\377f\000\377"
  "\270\000\000\377\377f\000\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377f\000\377\270\000\000\377"
  "\377f\000\377\270\000\000\377\270\000\000\377\270\000\000\377\377f\000\377\377f\000m\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377f\000Q\377f\000\377\270"
  "\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\377"
  "f\000\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\377\377f\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\377f\000\377\377f\000Q\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377f\000=\377f\000\340\270\000\000\377\270\000\000"
  "\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\306((\377"
  "\377f\000\377\377f\000\377\377f\000\377\377f\000\377\306((\377\377f\000\377\377f\000"
  "\377\377f\000\377\306((\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\377f\000\340\377f\000=\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\377f\000\231\306((\377\270\000\000\377\270\000\000\377\270\000\000\377\270"
  "\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\377f\000\377\270\000\000\377\306("
  "(\377\306((\377\377f\000\377\270\000\000\377\306((\377\306((\377\270\000\000\377\377"
  "f\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000"
  "\000\377\270\000\000\377\306((\377\377f\000\231\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377"
  "f\000\231\306((\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000"
  "\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\342\270\000\000n\270\000\000n\270"
  "\000\000n\270\000\000n\270\000\000n\270\000\000n\270\000\000n\270\000\000\377\270\000\000\377\270\000\000"
  "\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\306((\377"
  "\377f\000\231\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\306((\231\270\000\000\377\270\000\000"
  "\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000"
  "\377\270\000\000\377\270\000\000Q\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\270\000\000\204\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270"
  "\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\306((\231\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\270\000\000\231\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\204\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\270\000\000\024\270\000\000\243"
  "\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\377\270\000\000\231\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\270\000\000\231\270"
  "\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270"
  "\000\000\377\270\000\000\222\270\000\000\017\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\270\000\000\035\270\000\000\266\270\000\000\377\270\000\000"
  "\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\231\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\270\000\000\036\270\000\000\326\270\000\000\377\270\000\000\377\270"
  "\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\341\270\000\000)\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\270\000\000"
  "R\270\000\000\353\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377\270\000\000\377"
  "\270\000\000\326\270\000\000\036\000\000\000\000\000\000\000\000\000\000\000\000\377\270UQ\377\270U\313\377"
  "\270U\365\377\270U\377\377\270U\377\270\000\000\377\270\000\000\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\063\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\270Uf\377f\000\377\377\270U\377"
  "\377\270U\377\270\000\000\377\270\000\000\377\377\270U\377\377\270U\365\377\270U"
  "\313\377\270UQ\000\000\000\000\377\270U,\377\270U\351\377\270U\377\377\270U\377\377"
  "\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\063\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\377\270Uf\377\270U\377\377f\000\377\377\270U\377\377"
  "\270U\377\377\270U\377\377f\000\377\377\270U\377\377\270U\377\377\270U\351"
  "\377\270U,\377\270U\374\377\270U\377\377\270U\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270"
  "Uh\377\270U\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\377\270U\001\377\270U\232\377\270U\377\377\270U\377\377\270U\377"
  "\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270U\377\377\270"
  "U\374",
};

