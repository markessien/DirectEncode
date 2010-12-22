
/* type definitions for variable length code table entries */

typedef struct
{
  unsigned char code; /* right justified */
  char len;
} VLCtable;

/* for codes longer than 8 bits (excluding leading zeroes) */
typedef struct
{
  unsigned short code; /* right justified */
  char len;
} sVLCtable;


extern unsigned char zig_zag_scan[64];
extern unsigned char alternate_scan[64];
extern unsigned char default_intra_quantizer_matrix[64];
extern unsigned char default_non_intra_quantizer_matrix[64];
extern unsigned char non_linear_mquant_table[32];
extern unsigned char map_non_linear_mquant[113];
extern VLCtable addrinctab[33];
extern VLCtable mbtypetab[3][32];
extern VLCtable cbptable[64];
extern VLCtable motionvectab[17];
extern sVLCtable DClumtab[12];
extern sVLCtable DCchromtab[12];
extern VLCtable dct_code_tab1[2][40];
extern VLCtable dct_code_tab2[30][5];
extern VLCtable dct_code_tab1a[2][40];
extern VLCtable dct_code_tab2a[30][5];
extern double picture_rates [9];
extern double ratio [16];
extern unsigned int bitrate_index [3][16];
extern unsigned int ac3_bitrate_index[32];
extern unsigned int ac3_frame_size[3][32];
extern double frequency [4];
extern double ac3_frequency[4];
extern unsigned int slots [4];
extern unsigned int samples [4];
extern char modetxt [4][15];
extern char copyrighttxt [2][20];
extern char originaltxt [2][10];
extern char emphasistxt [4][20];
extern char     *mux_mode_names[4];
extern char     *mux_layer_names[3];
extern double   s_freq[4];
extern int      bitrate[3][15];
extern double  mux_multiple[64];


