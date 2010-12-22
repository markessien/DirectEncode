/* mplex.h */

#define USER_DATA_START         0x000001b2
#define SEQUENCE_HEADER 	0x000001b3
#define SEQUENCE_END		0x000001b7
#define PICTURE_START		0x00000100
#define GROUP_START		0x000001b8
#define SYNCWORD_START		0x000001
#define IFRAME                  1
#define PFRAME                  2
#define BFRAME                  3
#define DFRAME                  4

#define SEQHDR_FLAG             1
#define GOPHDR_FLAG             2

#define AUDIO_SYNCWORD		0xfff
#define AC3_SYNCWORD            0x0b77

#define PACK_START		0x000001ba
#define SYS_HEADER_START	0x000001bb
#define PROGRAM_END		0x000001b9
#define PACKET_START		0x000001

#define MAX_FFFFFFFF		4294967295.0 	/* = 0xffffffff in hex.	*/
#define MSB_TIMECODE            4294967296.0    /* = 0x100000000 in hex */

#define CLOCKS			27000000.0	/* System Clock Hertz	*/

#define MPEG2_AFTER_PACKET_LENGTH    16         /* No of non-data-bytes	*/
#define MPEG1_AFTER_PACKET_LENGTH    12         /* following the packet	*/
						/* length field		*/
#define MPEG2_LAST_SCR_BYTE_IN_PACK  10		/* No of bytes in pack	*/
#define MPEG1_LAST_SCR_BYTE_IN_PACK   9         /* preceding, and 	*/
						/* including, the SCR	*/

/* The following values for sys_header_length & size are only valid for */
/* System streams consisting of three basic streams. When wrapping around */
/* the system layer on a single video or a single audio stream, those   */
/* values get decreased by 3 or 6.                                           */

#define SYS_HEADER_LENGTH	15		/* length of Sys Header	*/
						/* after start code and	*/
						/* length field		*/

#define SYS_HEADER_SIZE		21		/* incl. start code and	*/
						/* length field		*/
#define MPEG2_PACK_HEADER_SIZE	14
#define MPEG1_PACK_HEADER_SIZE  12

#define PACKET_HEADER_SIZE	6

#define MPEG2_MIN_PACKET_SIZE   255 + PACKET_HEADER_SIZE + MPEG2_AFTER_PACKET_LENGTH
#define MPEG1_MIN_PACKET_SIZE   255 + PACKET_HEADER_SIZE + MPEG1_AFTER_PACKET_LENGTH

#define VIDEOCD_SECTOR_SIZE	2324	        /* VideoCD sector size */
#define SVCD_SECTOR_SIZE        2324            /* Super VideoCD sector size */
#define DVD_SECTOR_SIZE         2048            /* DVD sector size     */
#define MAX_SECTOR_SIZE         4096

#define MPEG2_MIN_SECTOR_SIZE	MPEG2_MIN_PACKET_SIZE + MPEG2_PACK_HEADER_SIZE + SYS_HEADER_SIZE
#define MPEG1_MIN_SECTOR_SIZE	MPEG1_MIN_PACKET_SIZE + MPEG1_PACK_HEADER_SIZE + SYS_HEADER_SIZE

#define STREAMS_VIDEO           1
#define STREAMS_AUDIO           2
#define STREAMS_V_A             3
#define STREAMS_AUDIO1          4
#define STREAMS_V_A1            5
#define STREAMS_A_A1            6
#define STREAMS_V_A_A1          7

#define AUDIO_STREAMS		0xb8		/* Marker Audio Streams	*/
#define VIDEO_STREAMS		0xb9		/* Marker Video Streams	*/
#define AUDIO_STR_0		0xc0		/* Marker Audio Stream0	*/
#define AUDIO_STR_1             0xc1            /* Marker Audio Stream1 */
#define VIDEO_STR_0		0xe0		/* Marker Video Stream0	*/
//#define VIDEO_STR_0		0xe1		/* low res video still	*/
#define PADDING_STR		0xbe		/* Marker Padding Stream*/
#define PRIVATE_STREAM1         0xbd            /* private stream 1 */
#define PRIVATE_STREAM2         0xbf            /* private stream 2 */
#define AC3_STREAM1             0x80            /* AC3 substream id 1 */
#define AC3_STREAM2             0x81            /* AC3 substream id 2 */

#define ZERO_STUFFING_BYTE	  0
#define STUFFING_BYTE	          0xff
#define RESERVED_BYTE		  0xff
#define TIMESTAMPS_NO		  0		/* Flag NO timestamps	*/
#define MPEG2_TIMESTAMPS_PTS	  2		/* MPEG2 Flag PTS timestamp */
#define MPEG1_TIMESTAMPS_PTS      1             /* MPEG1 Flag PTS timestamp */
#define MPEG2_TIMESTAMPS_PTS_DTS  3		/* MPEG2 Flag BOTH timestamps */
#define MPEG1_TIMESTAMPS_PTS_DTS  2             /* MPEG1 Flag BOTH timestamps */

#define MPEG2_MARKER_SCR	1		/* MPEG2 Marker SCR	*/
#define MPEG1_MARKER_SCR	2		/* MPEG1 Marker SCR	*/
#define MARKER_JUST_PTS		2		/* Marker only PTS	*/
#define MARKER_PTS		3		/* Marker PTS		*/
#define MPEG2_MARKER_DTS	4		/* MPEG2 Marker DTS	*/
#define MPEG1_MARKER_DTS	1		/* MPEG1 Marker DTS	*/
#define MARKER_NO_TIMESTAMPS	0x0f		/* Marker NO timestamps	*/

#define STATUS_AUDIO_END	0		/* Statusmessage A end	*/
#define STATUS_VIDEO_END	1		/* Statusmessage V end	*/
#define STATUS_AUDIO_TIME_OUT	2		/* Statusmessage A out	*/
#define STATUS_VIDEO_TIME_OUT	3		/* Statusmessage V out	*/
#define STATUS_AUDIO1_END       4
#define STATUS_AUDIO1_TIME_OUT  5

/*************************************************************************
    Typ- und Strukturdefinitionen
*************************************************************************/

typedef struct timecode_struc	/* Time_code Struktur laut MPEG		*/
{   unsigned long msb;		/* fuer SCR, DTS, PTS			*/
    unsigned long lsb;
    unsigned long reference_ext;
    unsigned long negative;     /* for delays when doing multiple files */
} Timecode_struc;

typedef struct vaunit_struc	/* Informationen ueber Video AU's 	*/
{   unsigned int length;
    unsigned short int type;
    unsigned short int flags;
    unsigned short int svcd_offset;
    unsigned short int pict_hdr_offset;
    unsigned int first_frame_offset;
    Timecode_struc DTS;
    Timecode_struc PTS;
} Vaunit_struc;

typedef struct aaunit_struc	/* Informationen ueber Audio AU's 	*/
{   unsigned long length;
    Timecode_struc PTS;
} Aaunit_struc;

typedef struct video_struc	/* Informationen ueber Video Stream	*/
{
	double stream_length;
    unsigned int num_sequence;
    unsigned int num_seq_end;
    unsigned int num_pictures;
    unsigned int num_groups;
    unsigned int num_frames[4];
    unsigned int avg_frames[4];

    unsigned int horizontal_size;
    unsigned int vertical_size;
    unsigned int aspect_ratio;
    unsigned int picture_rate;
    unsigned int bit_rate;
    unsigned int comp_avg_bit_rate;
    unsigned int comp_max_bit_rate;
    unsigned int vbv_buffer_size;
    unsigned int CSPF;
    unsigned int pulldown;
    unsigned int sh_length;
    unsigned char seq_hdr[256];
    timecode_struc last_PTS;
} Video_struc;

typedef struct audio_struc	/* Informationen ueber Audio Stream	*/
{
	double stream_length  ;
    unsigned int num_syncword	;
    unsigned int num_frames [2]	;
    unsigned int size_frames[2] ;
    unsigned int layer		;
    unsigned int protection	;
    unsigned int bit_rate	;
    unsigned int frequency	;
    unsigned int mode		;
    unsigned int mode_extension ;
    unsigned int copyright      ;
    unsigned int original_copy  ;
    unsigned int emphasis	;
} Audio_struc;

typedef struct sector_struc	/* Ein Sektor, kann Pack, Sys Header	*/
				/* und Packet enthalten.		*/
{   unsigned char  buf [MAX_SECTOR_SIZE] ;
    unsigned int   length_of_sector  ;
    unsigned int   length_of_packet_data ;
    Timecode_struc TS                ;
} Sector_struc;

typedef struct pack_struc	/* Pack Info				*/
{   unsigned char  buf [MPEG2_PACK_HEADER_SIZE];
    Timecode_struc SCR;
} Pack_struc;

typedef struct sys_header_struc	/* System Header Info			*/
{   unsigned char  buf [SYS_HEADER_SIZE];
} Sys_header_struc;

typedef struct buffer_queue	/* FIFO-Queue fuer STD Buffer		*/
{   unsigned int size	;	/* als verkettete Liste implementiert	*/
    Timecode_struc DTS	;
    struct buffer_queue *next	;
} Buffer_queue;
    

typedef struct buffer_struc	/* Simuliert STD Decoder Buffer		*/
{   unsigned int max_size;	/* enthaelt Anker auf verkettete Liste	*/
    Buffer_queue *first;
} Buffer_struc;
    
    
/*************************************************************************
    Funktionsprototypen, keine Argumente, K&R Style
*************************************************************************/

int ml_domplex(int mplex_video, int mplex_audio);

				/* Ueberpruefen der Argumente		*/
int ml_check_files          (	/* Kontrolliert ob Files vorhanden und	*/
   double *audio_bytes,
   double *audio1_bytes,
   double *video_bytes,
   unsigned int which_streams);

				/* weist sie Audio/Video Pointern zu	*/
int  open_file            (	/* File vorhanden?			*/
   char *name,
   double *bytes);

int ml_get_info_video       (	/* Info Access Units Video Stream	*/
   char *video_file,
   char *video_units,
   Video_struc *video_info,
   double *startup_delay,
   unsigned int *video_total,
   double length);

void output_info_video    (	/* Ausgabe Information Access Units	*/
   Video_struc *video_info);

int ml_get_info_audio       (	/* Info Access Units Audio Stream	*/
   char *audio_file,
   char *audio_units,
   Audio_struc *audio_info,
   double *startup_delay,
   unsigned int *audio_total,
   double length);

void output_info_audio    (	/* Ausgabe Information Access Units	*/
   Audio_struc *audio_info);

int marker_bit           (	/* Checks for marker bit		*/
   unsigned int what);

void empty_video_struc    (	/* Initialisiert Struktur fuer SUN cc	*/
   Video_struc *pointer);

void empty_audio_struc    (	/* Initialisiert Struktur fuer SUN cc	*/
   Audio_struc *pointer);

void empty_vaunit_struc   (	/* Initialisiert Struktur fuer SUN cc	*/
   Vaunit_struc *pointer);

void empty_aaunit_struc   (	/* Initialisiert Struktur fuer SUN cc	*/
   Aaunit_struc *pointer);

void empty_sector_struc   (	/* Initialisiert Struktur fuer SUN cc	*/
   Sector_struc *pointer);

void empty_timecode_struc (	/* Initialisiert Struktur fuer SUN cc	*/
   Timecode_struc *timecode);

void init_buffer_struc    (	/* Initialisiert Struktur fuer SUN cc	*/
   Buffer_struc *pointer,
   unsigned int size);

void copy_timecode        (	/* setzt 2tes TimeC. dem 1ten gleich	*/
   Timecode_struc *time_original, Timecode_struc *time_copy);

void make_timecode        (
   double timestamp,
   Timecode_struc *pointer);

double get_timecode        (	/* rechnet aus double einen TimeC.	*/
   Timecode_struc *pointer);

				/* und schreibt ihn in Timecode_struc   */
void add_to_timecode      (	/* addiert 1tes TimeC. zum 2ten		*/
   Timecode_struc *add,
   Timecode_struc *to);

void buffer_timecode      (	/* schreibt Timecode in Bitstreamformat */
   Timecode_struc *pointer,
   unsigned char  marker,
   unsigned char **buffer);

int  comp_timecode        (	/* 1tes TimeC. <= 2tes TimeC. ?		*/
   Timecode_struc *TS1,
   Timecode_struc *TS2);

int create_sector	  (  /* erstellt einen Sector		*/
  Sector_struc 	 *sector,
  Pack_struc	 *pack,
  Sys_header_struc *sys_header,
  unsigned int 	 packet_size,
  unsigned int   partial_packet_size, /* used for svcd multiplexing */
  HANDLE		 inputstream,
  unsigned char 	 type,
  unsigned char          subtype,
  unsigned char 	 buffer_scale,
  unsigned int 	 buffer_size,
  unsigned char 	 buffers,
  Timecode_struc   *PTS,
  Timecode_struc   *DTS,
  unsigned char 	 timestamps,
  unsigned int     which_streams,
  unsigned int     sector_pad,
  unsigned int     svcd_offset,
  unsigned int     write_broken_link,
  unsigned int     write_seq_end,
  unsigned int     write_seq_hdr,
  unsigned int     sh_length,
  unsigned char    *seq_hdr);

void create_sys_header	  (	/* erstellt einen System Header		*/
   Sys_header_struc *sys_header,
   unsigned int	 rate_bound,
   unsigned char	 audio_bound,
   unsigned char	 fixed,
   unsigned char	 CSPS,
   unsigned char	 audio_lock,
   unsigned char	 video_lock,
   unsigned char	 video_bound,

   unsigned char 	 stream1,
   unsigned char 	 buffer1_scale,
   unsigned int 	 buffer1_size,
   unsigned char 	 stream2,
   unsigned char 	 buffer2_scale,
   unsigned int 	 buffer2_size,
   unsigned char 	 stream3,
   unsigned char 	 buffer3_scale,
   unsigned int 	 buffer3_size,
   unsigned int     which_streams);

void create_pack	  (	/* erstellt einen Pack Header		*/
  Pack_struc	 *pack,
  Timecode_struc   *SCR,
  unsigned int 	 mux_rate);


int output_video         (	/* erstellt und schreibt Video pack aus	*/
   Timecode_struc *SCR,
   Timecode_struc *SCR_delay,
   FILE *vunits_info,
   HANDLE istream_v,
   Pack_struc *pack,
   Sys_header_struc *sys_header,
   Buffer_struc *buffer,
   Vaunit_struc *video_au,
   unsigned char *picture_start,
   unsigned int mux_rate,
   unsigned long packet_data_size,
   unsigned char marker_pack,
   unsigned int which_streams,
   unsigned int sh_length,
   unsigned char *seq_hdr);

int output_audio         (   /* erstellt und schreibt Audio pack aus */
   Timecode_struc *SCR,
   Timecode_struc *SCR_delay,
   FILE *aunits_info,
   HANDLE istream_a,
   Pack_struc *pack,
   Sys_header_struc *sys_header,
   Buffer_struc *buffer,
   Aaunit_struc *audio_au,
   unsigned char *audio_frame_start,
   unsigned int *audio_counter,
   unsigned int *audio_underflows,
   unsigned char audio_PSTD,
   unsigned char aid,
   unsigned char audio_subid,
   unsigned char abuffer_scale,
   unsigned int abuffer_size,
   unsigned int mux_rate,
   unsigned long packet_data_size,
   unsigned char marker_pack,
   unsigned int which_streams,
   char *audio_start_new_file);

int output_padding       (	/* erstellt und schreibt Padding pack	*/
   Timecode_struc *SCR,
   Pack_struc *pack,
   Sys_header_struc *sys_header,
   unsigned int mux_rate,
   unsigned long packet_data_size,
   unsigned char marker_pack,
   unsigned int which_streams);

int output_private2       (	/* erstellt und schreibt Private 2 pack	*/
   Timecode_struc *SCR,
   unsigned int mux_rate);

int next_audio_access_unit (	/* holt naechste gueltige AU Info her	*/
   Buffer_struc *buffer,
   Aaunit_struc *audio_au,
   unsigned int *bytes_left,
   FILE *aunits_info,
   unsigned char *audio_frame_start,
   unsigned int *audio_counter,
   Timecode_struc *SCR_delay);

void buffer_empty(Buffer_struc *buffer);

void buffer_clean	  (	/* saeubert die Bufferschlange 		*/
   Buffer_struc  *buffer,
   Timecode_struc *SCR);

int  buffer_space         (	/* Anzahl freier Bytes in Buffer	*/
   Buffer_struc *buffer);

int queue_buffer         (	/* An Bufferliste anhaengen		*/
   Buffer_struc *buffer,
   unsigned int bytes,
   Timecode_struc *TS);

int ml_outputstream         (	/* Hauptschleife Multiplexroutinen	*/
   HANDLE        outputFile,
   char 		*video_units,
   Video_struc 	*video_info,
   char 		*audio_units,
   Audio_struc 	*audio_info,
   char 		*audio1_units,
   Audio_struc 	*audio1_info,
   unsigned int video_total,
   unsigned int audio_total,
   unsigned int audio1_total,
   unsigned int    which_streams);

void status_info          (	/* Statusmitteilung bei Erstellen	*/
   unsigned int nsectors_a,
   unsigned int nsectors_a1,
   unsigned int nsectors_v,
   unsigned int nsectors_p,
   double nbytes,
   unsigned int buf_v,
   unsigned int buf_a,
   unsigned int buf_a1);

				/* MPEG multiplex stream		*/
void status_header	  (char *filename);	/* Titelzeilen Statusblock		*/
void status_message	  (unsigned char what);	/* Event (end, time_out) mitteilen	*/
void status_footer	  ();	/* Endzeile				*/

