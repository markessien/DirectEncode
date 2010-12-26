/** This file is part of The Standard Mpeg Encoder.

The Standard Mpeg Encoder is free software: you can redistribute it 
and/or modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation, either version 3 of 
the License, or (at your option) any later version.

The Standard Mpeg Encoder is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with The Standard Mpeg Encoder.  
 
If not, see <http://www.gnu.org/licenses/>.
**/

// SequenceHeaders.cpp: implementation of the CSequenceHeaders class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SequenceHeaders.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSequenceHeaders::CSequenceHeaders()
{

}

CSequenceHeaders::~CSequenceHeaders()
{

}

/*
uint8_t* CSequenceHeaders::FindStartCode(const uint8_t * restrict p, const uint8_t *end, uint32_t * restrict state)
{
    int i;

    assert(p<=end);
    if(p>=end)
        return end;

    for(i=0; i<3; i++){
        uint32_t tmp= *state << 8;
        *state= tmp + *(p++);
        if(tmp == 0x100 || p==end)
            return p;
    }

    while(p<end){
        if     (p[-1] > 1      ) p+= 3;
        else if(p[-2]          ) p+= 2;
        else if(p[-3]|(p[-1]-1)) p++;
        else{
            p++;
            break;
        }
    }

    p= FFMIN(p, end)-4;
    *state=  be2me_32(unaligned32(p));

    return p+4;
}

void CSequenceHeaders::ExtractSequenceHeaders(char *pBuf, long nLen)
{
	// Reference = mpeg_decode_frame;

	char* buf_ptr = buf;
    char* buf_end = buf + buf_size;

	// you receive an mpeg frame here. Now get the sequence header
	int startcode = -1;
	for(;;) {
		// first, find the start code
		
		startcode = -1;
		buf_ptr = ff_find_start_code(buf_ptr,buf_end, &start_code);
		if (start_code < 0) {
			ASSERT(FALSE); // wierd stuff
		}


		input_size = buf_end - buf_ptr;

		       // prepare data for next start code
        switch(start_code) {
        case SEQ_START_CODE:
            mpeg1_decode_sequence(avctx, buf_ptr,
                                  input_size);
            break;

        case PICTURE_START_CODE:
			OutputDebugString("Picture Start Code");
            break;
        case EXT_START_CODE:
            OutputDebugString("Extension Start Code");
            break;
        case USER_START_CODE:
            OutputDebugString("User Start Code");
            break;
        case GOP_START_CODE:
			OutputDebugString("GOP Start Code");
            break;
		default:
			// Why?
			break;
		}
	}
}


static int CSequenceHeaders::DecodeSequenceHeader(AVCodecContext *avctx, const uint8_t *buf, int buf_size)
{
    Mpeg1Context *s1 = avctx->priv_data;
    MpegEncContext *s = &s1->mpeg_enc_ctx;
    int width,height;
    int i, v, j;

    init_get_bits(&s->gb, buf, buf_size*8);

    width = get_bits(&s->gb, 12);
    height = get_bits(&s->gb, 12);
    if (width <= 0 || height <= 0 ||
        (width % 2) != 0 || (height % 2) != 0)
        return -1;
    s->aspect_ratio_info= get_bits(&s->gb, 4);
    if (s->aspect_ratio_info == 0)
        return -1;
    s->frame_rate_index = get_bits(&s->gb, 4);
    if (s->frame_rate_index == 0 || s->frame_rate_index > 13)
        return -1;
    s->bit_rate = get_bits(&s->gb, 18) * 400;
    if (get_bits1(&s->gb) == 0) // marker 
        return -1;
    s->width = width;
    s->height = height;

    s->avctx->rc_buffer_size= get_bits(&s->gb, 10) * 1024*16;
    skip_bits(&s->gb, 1);

    // get matrix 
    if (get_bits1(&s->gb)) {
        for(i=0;i<64;i++) {
            v = get_bits(&s->gb, 8);
            if(v==0){
                av_log(s->avctx, AV_LOG_ERROR, "intra matrix damaged\n");
                return -1;
            }
            j = s->dsp.idct_permutation[ ff_zigzag_direct[i] ];
            s->intra_matrix[j] = v;
            s->chroma_intra_matrix[j] = v;
        }
#ifdef DEBUG
        dprintf("intra matrix present\n");
        for(i=0;i<64;i++)
            dprintf(" %d", s->intra_matrix[s->dsp.idct_permutation[i]]);
        printf("\n");
#endif
    } else {
        for(i=0;i<64;i++) {
            j = s->dsp.idct_permutation[i];
            v = ff_mpeg1_default_intra_matrix[i];
            s->intra_matrix[j] = v;
            s->chroma_intra_matrix[j] = v;
        }
    }
    if (get_bits1(&s->gb)) {
        for(i=0;i<64;i++) {
            v = get_bits(&s->gb, 8);
            if(v==0){
                av_log(s->avctx, AV_LOG_ERROR, "inter matrix damaged\n");
                return -1;
            }
            j = s->dsp.idct_permutation[ ff_zigzag_direct[i] ];
            s->inter_matrix[j] = v;
            s->chroma_inter_matrix[j] = v;
        }
#ifdef DEBUG
        dprintf("non intra matrix present\n");
        for(i=0;i<64;i++)
            dprintf(" %d", s->inter_matrix[s->dsp.idct_permutation[i]]);
        printf("\n");
#endif
    } else {
        for(i=0;i<64;i++) {
            int j= s->dsp.idct_permutation[i];
            v = ff_mpeg1_default_non_intra_matrix[i];
            s->inter_matrix[j] = v;
            s->chroma_inter_matrix[j] = v;
        }
    }

    if(show_bits(&s->gb, 23) != 0){
        av_log(s->avctx, AV_LOG_ERROR, "sequence header damaged\n");
        return -1;
    }

    // we set mpeg2 parameters so that it emulates mpeg1
    s->progressive_sequence = 1;
    s->progressive_frame = 1;
    s->picture_structure = PICT_FRAME;
    s->frame_pred_frame_dct = 1;
    s->chroma_format = 1;
    s->codec_id= s->avctx->codec_id= CODEC_ID_MPEG1VIDEO;
    avctx->sub_id = 1; // indicates mpeg1
    s->out_format = FMT_MPEG1;
    s->swap_uv = 0;//AFAIK VCR2 don't have SEQ_HEADER
    if(s->flags & CODEC_FLAG_LOW_DELAY) s->low_delay=1;

    if(s->avctx->debug & FF_DEBUG_PICT_INFO)
        av_log(s->avctx, AV_LOG_DEBUG, "vbv buffer: %d, bitrate:%d\n",
               s->avctx->rc_buffer_size, s->bit_rate);

    return 0;
}
*/