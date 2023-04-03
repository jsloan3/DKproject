/* GIMP RGBA C-Source image dump (key.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[32 * 32 * 4 + 1];
} key = {
  32, 32, 4,
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\216rO\377\260\235\207\377\272\254\216"
  "\377\273\245\203\377\252\214b\377\177P\016\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\264\243\222\377\351\337\322"
  "\377\355\341\316\377\347\317\254\377\345\313\234\377\342\307\222\377\354"
  "\321\242\377\355\332\250\377\323\277\210\377\227r:\377n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\212kU\377\345\336\326\377\354\326\271\377"
  "\346\301R\377\357\323\065\377\370\333\063\377\365\330/\377\360\316\061\377\347"
  "\307\063\377\342\266\060\377\332\262[\377\350\312\211\377\274\232^\377n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\210mP\377\361\347\332\377\343\305\204\377"
  "\365\340@\377\372\343:\377\372\343:\377\370\333\063\377\365\322*\377\360\316"
  "\061\377\335\267\"\377\303\233\030\377\320\246'\377\326\246)\377\335\266l\377"
  "\307\242Y\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\351\337\322\377\343\305\204\377"
  "\372\351?\377\377\350?\377\372\343:\377\370\333\063\377\365\330/\377\365\322"
  "*\377\277\235#\377n=\000\000n=\000\000n=\000\000\253{\030\377\326\246)\377\332\262[\377"
  "\270\216A\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\300\256\235\377\354\326\271\377\365\340@\377"
  "\372\351?\377\374\344\060\377\376\340\071\377\370\333\063\377\365\322*\377\344"
  "\303#\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\313\234\035\377\326\246)\377\342\271"
  "[\377\215a\026\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n"
  "=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\361\347\332\377\344\306L\377\376\355\067\377"
  "\377\350\065\377\374\344\060\377\375\337,\377\370\332$\377\365\322*\377\326"
  "\260\030\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\276\220\031\377\342\266\060\377\333"
  "\261E\377\276\227\062\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\240\211]\377\355\341\316\377\365\340@\377"
  "\377\350\065\377\374\344\060\377\375\337,\377\370\332$\377\367\323\036\377\363"
  "\312#\377\344\275\035\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\327\255\070\377\346"
  "\300B\377\333\261E\377\336\262\065\377o>\005\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\276\256\212\377\347\317\254"
  "\377\377\350?\377\377\350\065\377\374\344\060\377\375\337,\377\375\331&\377"
  "\367\323\036\377\363\312#\377\355\305\032\377\303\233\030\377n=\000\000n=\000\000n="
  "\000\000\276\227\062\377\353\305F\377\356\310Q\377\346\301R\377\343\267:\377\225"
  "h\010\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000\312\274\236\377\344\307\214\377\374\344\060\377\374\344\060\377\375"
  "\337,\377\370\332$\377\367\323\036\377\370\316\031\377\363\312#\377\362\312"
  "/\377\354\276/\377\342\266\060\377\320\254\065\377\344\277H\377\361\313L\377"
  "\357\320V\377\361\322`\377\350\312`\377\346\272F\377\242s\013\377n=\000\000n="
  "\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\312\271"
  "\216\377\343\305\204\377\374\344\060\377\375\337,\377\375\336\032\377\375\331"
  "&\377\367\323\036\377\367\316(\377\362\312/\377\360\310\070\377\360\310\070"
  "\377\362\313D\377\361\313L\377\357\320V\377\361\322`\377\366\327e\377\364"
  "\334o\377\351\314i\377\346\272F\377\245u\000\377n=\000\000n=\000\000n=\000\000n=\000\000n="
  "\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\274\247l\377\345\313\234\377"
  "\375\337,\377\375\337,\377\375\337,\377\375\331&\377\371\326/\377\367\325"
  "\071\377\366\324B\377\362\313D\377\362\322P\377\357\320V\377\364\324Z\377"
  "\366\327e\377\364\334o\377\366\337x\377\372\344\203\377\344\320x\377\353"
  "\277B\377\230j\000\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000\242~\025\377\355\332\250\377\367\325\071\377\375\337,"
  "\377\375\337,\377\376\332\065\377\367\325\071\377\366\324B\377\365\324J\377"
  "\362\322P\377\366\326]\377\366\327e\377\364\334o\377\366\337x\377\372\344"
  "\203\377\375\347\207\377\371\353\217\377\345\315\203\377\355\270\012\377n"
  "=\000\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000\351\330\223\377\344\277H\377\376\340\071\377\376\340\071\377\373"
  "\336A\377\375\332I\377\373\331P\377\371\330W\377\367\336i\377\364\334o\377"
  "\366\337x\377\373\344}\377\375\347\207\377\371\353\217\377\373\357\231\377"
  "\360\336\221\377\347\314v\377\320\237\000\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\337\313\232\377\353"
  "\323\220\377\366\333P\377\377\343O\377\375\342V\377\372\337\\\377\372\341"
  "e\377\367\336i\377\371\341t\377\373\344}\377\375\347\207\377\371\353\217"
  "\377\373\357\231\377\374\361\241\377\370\356\245\377\351\330\223\377\361"
  "\303\064\377\230j\000\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n="
  "\000\000n=\000\000n=\000\000n=\000\000n=\000\000\266\243\215\377\376\357\317\377\373\335q\377"
  "\352\307m\377\372\337\\\377\375\343_\377\372\341e\377\376\346x\377\373\344"
  "}\377\375\347\207\377\371\353\217\377\373\357\231\377\374\361\241\377\376"
  "\364\253\377\373\362\257\377\350\332\240\377\364\317g\377\307\230\004\377n"
  "=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n"
  "=\000\000\226|d\377\366\362\334\377\367\335\214\377\251\220|\377\321\270i\377"
  "\351\314i\377\371\341t\377\376\346x\377\372\352\210\377\371\353\217\377\373"
  "\357\231\377\374\361\241\377\376\364\253\377\373\362\257\377\360\350\245"
  "\377\354\336\244\377\364\320o\377\327\245\015\377n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000~W\064\377\361\347\332"
  "\377\366\334\213\377\302\257\230\377\217oS\377\371\332\230\377\375\324;\377"
  "\362\314]\377\364\330\201\377\371\354\226\377\366\353\234\377\364\352\241"
  "\377\360\350\245\377\356\347\253\377\356\347\253\377\360\337\231\377\364"
  "\307K\377\307\230\004\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n"
  "=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\332\321\304\377\366\336\232\377\333\306"
  "\251\377\177R&\377\345\323\250\377\374\313\000\377\377\317-\377\342\307\222"
  "\377\336\262\065\377\362\313D\377\361\323h\377\366\332|\377\364\330\201\377"
  "\364\317g\377\361\303\064\377\331\247\000\377\242s\013\377n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\300\256"
  "\235\377\367\347\301\377\345\323\250\377\210[:\377\324\276\242\377\371\312"
  "=\377\374\313\000\377\354\321\242\377\203V/\377\333\304\241\377\320\237\000\377"
  "\256\203\000\377\271\214\000\377\271\214\000\377\247}\007\377\203S\000\377n=\000\000n="
  "\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n="
  "\000\000n=\000\000\241\210u\377\370\355\331\377\355\327\231\377\236}g\377\266\243"
  "\215\377\364\320o\377\366\306\014\377\366\327\225\377\235|`\377\275\251\223"
  "\377\342\271[\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n"
  "=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\204dI\377"
  "\361\347\332\377\356\325\213\377\270\236\212\377\235~l\377\361\321\211\377"
  "\361\302\000\377\371\317v\377\267\234\202\377\241\210u\377\361\320\202\377"
  "\213_\000\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n"
  "=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\342\331\313\377"
  "\353\323\220\377\316\272\244\377\204^@\377\351\320\247\377\354\275\020\377"
  "\355\270\012\377\264\224d\377\200L\015\377\344\307\214\377\247}\000\377n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\304\273\256\377\356\333\260\377"
  "\341\313\257\377\177R&\377\333\306\251\377\354\276/\377\355\270\012\377\245"
  "u\000\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "\250\227\207\377\364\347\315\377\345\323\250\377\223lM\377\300\256\235\377"
  "\347\275W\377\352\266\033\377\271\214\000\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\220qZ\377\361\347\332\377\344\317\230"
  "\377\251\216u\377\246\217\201\377\332\275|\377\276\220\031\377\256\203\000\377"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000vJ$\377"
  "\345\336\326\377\346\320\223\377\302\257\230\377\215o^\377\340\306\227\377"
  "\213`\010\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000\317\306\271\377\350\325\243\377\333\306\251\377\203V/"
  "\377\333\306\251\377\277\222&\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000\226|d\377\360\341\302\377\341\320"
  "\253\377\212\\\065\377\312\270\250\377\331\252G\377\253{\030\377n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000q@\017"
  "\377\337\313\232\377\235|`\377\264\243\222\377\331\264p\377\326\246)\377"
  "\225h\010\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000\234yR\377\226w`\377\315\265\215\377\254|\"\377\222"
  "e\021\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000"
  "\000n=\000\000n=\000\000n=\000\000n=\000\000o>\005\377o>\005\377n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000"
  "n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000n=\000\000",
};

