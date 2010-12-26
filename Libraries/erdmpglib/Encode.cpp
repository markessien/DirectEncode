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

#include "StdAfx.h"
#include "AudioResample.h"
#include "encode.h"
#include <malloc.h>
#include <stdint.h>


#define MAX_AUDIO_PACKET_SIZE (128 * 1024 * 10)


CEncode::CEncode(void)
{
	m_pCallbackFunc = NULL;

	av_register_all();

	m_lockStop.Unlock();

	m_pResample = new CAudioResample();
	m_bFramerateCorrection = true;
	m_bAudioCorrection = true;
	m_memProtocol.Register();
	m_bPostMultiplex = false;
	m_pAudioOutBuf= NULL;
	m_nAudioInputFrameSize = 0;
	m_nAudioOutBufSize = 0;
	m_pVideoOutBuf = NULL;
	m_nVideoOutBufSize = 0;
	m_nAudioValidData = 0;
	m_nAudioSamplesWritten = 0;
	m_pImgResampleCtx = NULL;
	m_bResizeRequired = true;
	m_bRegistered = false;
	m_pAudioResampleCtx = NULL;
	m_bResampleRequired = true;
	m_szVideoFileName[0] = 0;
	m_szAudioFileName[0] = 0;
	m_pAudioStream = NULL;
	m_pVideoStream = NULL;
	
	m_pAudioInBuf = NULL;
	m_pAudioOutBuf = 0;
	m_pVideoOutBuf = NULL;
	m_pPictureRGB = NULL;
	m_pPictureYUV_before_resize = NULL;
	m_pPictureYUV_after_resize = NULL;
	m_pPictureYUV_after_deinterlace = NULL;

	m_pOutputFormatVideo = NULL;
	m_pOutputFormatAudio = NULL;
	m_pOutputFormat = NULL;
	m_pFormatContextAudio = NULL;
	m_pFormatContextVideo = NULL;
	m_pFormatContext = NULL;

	m_pAudioResampleCtx = NULL;
	m_pImgResampleCtx = NULL;

	m_fifo.buffer = NULL;
	m_bHeaderWritten = false;

	m_bStillImageEncoding = false;


	m_logoOverlay.CreateLogo();

}

CEncode::~CEncode(void)
{
	delete m_pResample;
	m_pResample = NULL;
	_ASSERT(m_pAudioOutBuf == NULL);
	_ASSERT(m_pVideoOutBuf == NULL);
	_ASSERT(m_pImgResampleCtx == NULL);
	_ASSERT(m_pAudioResampleCtx == NULL);
}

AVStream* CEncode::AddAudioStream(AVFormatContext *oc, int codec_id)
{
    AVCodecContext *c = NULL;
    AVStream *st = NULL;

    st = av_new_stream(oc, 1);
    if (st == NULL) {
        Error("Could not allocate audio stream\n");
        return NULL;
    }

    c = st->codec;
    c->codec_id = (CodecID)codec_id;
    c->codec_type = CODEC_TYPE_AUDIO;
    c->bit_rate = m_EncodeParams.GetParams().nOutputAudioBitrate;
    c->sample_rate = m_EncodeParams.GetParams().nOutputAudioSampleRate;
    c->channels = m_EncodeParams.GetParams().nOutputAudioChannels;

	// c->level = 13; 
	// OutputDebugString("Changed audio level!!!");
//	c->time_base= (AVRational){1, m_EncodeParams.GetParams().nOutputAudioSampleRate};


	c->strict_std_compliance = 0;

    if (oc->oformat->flags & AVFMT_GLOBALHEADER) {
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;
    }

	if (m_EncodeParams.GetParams().vbrAudio)
	{
		if (m_EncodeParams.GetParams().nOutputAudioBitrate < m_EncodeParams.GetParams().nOutputAudioBitrateMin)
			c->bit_rate = m_EncodeParams.GetParams().nOutputAudioBitrateMin;
		else
			c->bit_rate = m_EncodeParams.GetParams().nOutputAudioBitrate;
		c->rc_max_rate = m_EncodeParams.GetParams().nOutputAudioBitrateMax;
		c->rc_min_rate = m_EncodeParams.GetParams().nOutputAudioBitrateMin;
		c->bit_rate = (c->rc_min_rate + c->rc_max_rate) / 2;
		c->bit_rate_tolerance = 4000 * 1000;
		c->rc_buffer_size = 1024 * 8 * 20;
		c->rc_initial_buffer_occupancy = c->rc_buffer_size*3/4;
		c->rc_buffer_aggressivity = 1.0;
	}

	if (c->channels == 0)
		Error("Audio Channel Count not specified");

	if (c->sample_rate == 0)
		Error("Audio Sample Rate Count not specified");

	if (c->bit_rate == 0)
		Error("Audio Bit Rate Count not specified");

	if (m_EncodeParams.GetParams().wfexAudioSrc.nChannels == 0 ||
		m_EncodeParams.GetParams().wfexAudioSrc.nSamplesPerSec == 0 ||
		m_EncodeParams.GetParams().wfexAudioSrc.wBitsPerSample == 0)
	{
		Error("Input audio information not specified. See EncodeParams.wfexAudioSrc");
	}

    return st;
}

HRESULT CEncode::OpenAudio(AVFormatContext *oc, AVStream *st)
{
    AVCodecContext *c;
    AVCodec *codec;

    c = st->codec;

    codec = avcodec_find_encoder(c->codec_id);
    if (!codec) {
        Error("Audio Codec not found");
        return E_FAIL;
    }

    if (avcodec_open(c, codec) < 0) {
        Error("Could not open audio codec");
        return E_FAIL;;
    }

    m_nAudioOutBufSize = 10000;
    m_pAudioOutBuf = (uint8_t*)malloc(m_nAudioOutBufSize);

    // ugly hack for PCM codecs (will be removed ASAP with new PCM
    //   support to compute the input frame size in samples
    if (c->frame_size <= 1) {
        m_nAudioInputFrameSize = m_nAudioOutBufSize / c->channels;
        switch(st->codec->codec_id) {
        case CODEC_ID_PCM_S16LE:
        case CODEC_ID_PCM_S16BE:
        case CODEC_ID_PCM_U16LE:
        case CODEC_ID_PCM_U16BE:
            m_nAudioInputFrameSize >>= 1;
            break;
        default:
            break;
        }
    } else {
        m_nAudioInputFrameSize = c->frame_size;
    }

    // m_pAudioInBuf = (BYTE*)malloc(m_nAudioInputFrameSize * 2 * c->channels);
	m_pAudioInBuf = (unsigned __int8*)malloc(2 * MAX_AUDIO_PACKET_SIZE);

	av_fifo_init(&m_fifo, 2 * MAX_AUDIO_PACKET_SIZE);

	long nInputChannels = m_EncodeParams.GetParams().wfexAudioSrc.nChannels;
	long nOutputChannels = m_EncodeParams.GetParams().nOutputAudioChannels;
	long nInputSampleRate = m_EncodeParams.GetParams().wfexAudioSrc.nSamplesPerSec;
	long nOutputSampleRate = m_EncodeParams.GetParams().nOutputAudioSampleRate;

	
	if (nOutputChannels == nInputChannels &&
		nInputSampleRate == nOutputSampleRate) 
	{
		m_bResampleRequired = false;
	}
	else
	{
		printf("Configuring ACM Resample\n");

		WAVEFORMATEX wfxDst;
		wfxDst.wFormatTag = 1;
		wfxDst.nChannels = nOutputChannels;
		wfxDst.nSamplesPerSec = nOutputSampleRate;
		wfxDst.wBitsPerSample = 16;
		wfxDst.nBlockAlign = (unsigned short)((wfxDst.nChannels * wfxDst.wBitsPerSample) / 8);
		wfxDst.nAvgBytesPerSec = wfxDst.nSamplesPerSec * wfxDst.nBlockAlign;
		wfxDst.cbSize = 0;

		HRESULT hr = m_pResample->SpecifyFormats(m_EncodeParams.GetParams().wfexAudioSrc, wfxDst);
		if (FAILED(hr))
			printf("Resample Failed");
	}
	// wtih 5.1 input, the audio streams are pre-chosen for us
	// we may want to support multiple audio streams tho.

	printf("Audio Format Resample: \nOutput Channels:%lu - Input channels: %lu\nOutput Sample Rate: %lu - Input Sample Rate: %lu\n",
			nOutputChannels, nInputChannels, nOutputSampleRate, nInputSampleRate);

	/*
	m_pAudioResampleCtx = audio_resample_init(nOutputChannels, nInputChannels,
											  nOutputSampleRate, nInputSampleRate);
	if(!m_pAudioResampleCtx) {
		Error("Cannot resample!");
		return E_FAIL;;
	}
	*/

	return S_OK;
}


void CEncode::CloseAudio()
{
	try
	{
		if (m_pAudioOutBuf)
		{
			avcodec_close(m_pAudioStream->codec);
			free(m_pAudioOutBuf);
			m_pAudioOutBuf = NULL;
		}

		if (m_pAudioInBuf)
		{
			free(m_pAudioInBuf);
			m_pAudioInBuf = NULL;
		}
	}
	catch  (...)
	{
		// dunno why this crashes with graphedit
	}
}

AVStream* CEncode::AddVideoStream(AVFormatContext *oc, int codec_id)
{
    AVCodecContext *c;
    AVStream *st;

    st = av_new_stream(oc, 0);
    if (st == NULL) {
        Error("Could not alloc stream\n");
        return NULL;
    }
    
    c = st->codec;
    c->codec_id = (CodecID)codec_id;
    c->codec_type = CODEC_TYPE_VIDEO;
	

	/*
    if (video_qscale || same_quality) {
        video_enc->flags |= CODEC_FLAG_QSCALE;
        video_enc->global_quality=
            st->quality = FF_QP2LAMBDA * video_qscale;
    }
*/
	/* Not relevant yet
    if (video_qscale || same_quality) {
        c->flags |= CODEC_FLAG_QSCALE;
        c->global_quality=
            st->quality = FF_QP2LAMBDA * video_qscale;
    } */

	c->intra_matrix = NULL;
	c->inter_matrix = NULL;
	c->pre_me = 0; // pre motion estimation

	bool b_frames = false;
    if (b_frames) {
        c->max_b_frames = b_frames;
		c->b_quant_factor = 2.0;
    }

	// qmin must be >= 1 and <= 51
	// min video quantiser scale (VBR)
    c->qmin = m_EncodeParams.GetParams().nQualityMin;
    c->qmax = m_EncodeParams.GetParams().nQualityMax;

    c->lmin = 2*FF_QP2LAMBDA;;
    c->lmax = 31*FF_QP2LAMBDA;
    c->rc_qsquish = 0.0;
    c->mb_lmin = 2*FF_QP2LAMBDA;
    c->mb_lmax = 31*FF_QP2LAMBDA;
    c->max_qdiff = 3;
    c->qblur = 0.5;
    c->qcompress = 0.5;
    c->rc_eq = "tex^qComp";
    c->workaround_bugs = FF_BUG_AUTODETECT;
    c->thread_count = 1;
    c->rc_override = NULL;
    c->rc_override_count = 0;

    c->rc_initial_cplx= 0;
    c->i_quant_factor = -0.8f;
    c->b_quant_factor = 1.25;
    c->i_quant_offset = 0.0;
    c->b_quant_offset = 1.25;
    c->intra_quant_bias = FF_DEFAULT_QUANT_BIAS;
    c->inter_quant_bias = FF_DEFAULT_QUANT_BIAS;
    c->me_threshold= 0;
    c->mb_threshold= 0;
    c->intra_dc_precision = 0;
    c->strict_std_compliance = 0;
    c->error_rate = 0;
    c->scenechange_threshold= 0;
    c->me_range = 0;
    c->me_penalty_compensation= 256;
    c->frame_skip_threshold= 0;
    c->frame_skip_factor= 0;
    c->frame_skip_exp= 0;

	c->me_method = ME_EPZS;

	c->strict_std_compliance = 1;

    /* two pass mode
    if (do_pass) {
        if (do_pass == 1) {
            c->flags |= CODEC_FLAG_PASS1;
        } else {
            c->flags |= CODEC_FLAG_PASS2;
        }
    } */


	switch (m_EncodeParams.GetParams().vbrVideo)
	{
	case BITRATEMODE_CQ_VBR:
	case BITRATEMODE_CQ:
		{
			c->flags |= CODEC_FLAG_QSCALE;
			float fQuality = (m_EncodeParams.GetParams().nOutputVideoQuality / 100.0f) * m_EncodeParams.GetParams().nQualityMax;
			fQuality = m_EncodeParams.GetParams().nQualityMax - fQuality;
			st->quality = (FF_QP2LAMBDA * fQuality);
			c->global_quality = st->quality;
			if (m_EncodeParams.GetParams().nOutputVideoBitrate < m_EncodeParams.GetParams().nOutputVideoBitrateMin)
				c->bit_rate = m_EncodeParams.GetParams().nOutputVideoBitrateMin;
			else
				c->bit_rate = m_EncodeParams.GetParams().nOutputVideoBitrate;
			c->rc_max_rate = m_EncodeParams.GetParams().nOutputVideoBitrateMax;
			c->rc_min_rate = m_EncodeParams.GetParams().nOutputVideoBitrateMin;
			c->bit_rate = (c->rc_min_rate + c->rc_max_rate) / 2;
			c->bit_rate_tolerance = 4000 * 1000;
		}
		break;
	case BITRATEMODE_CBR:
		{
			c->bit_rate = m_EncodeParams.GetParams().nOutputVideoBitrate;
			c->rc_max_rate = m_EncodeParams.GetParams().nOutputVideoBitrate;
			c->rc_min_rate = m_EncodeParams.GetParams().nOutputVideoBitrate;
			c->bit_rate_tolerance = 4000 * 1000;
		}
		break;
	case BITRATEMODE_VBR_2PASS:
	case BITRATEMODE_MVBR:
		{
			if (m_EncodeParams.GetParams().nOutputVideoBitrate < m_EncodeParams.GetParams().nOutputVideoBitrateMin)
				c->bit_rate = m_EncodeParams.GetParams().nOutputVideoBitrateMin;
			else
				c->bit_rate = m_EncodeParams.GetParams().nOutputVideoBitrate;
			c->rc_max_rate = m_EncodeParams.GetParams().nOutputVideoBitrateMax;
			c->rc_min_rate = m_EncodeParams.GetParams().nOutputVideoBitrateMin;
			c->bit_rate = (c->rc_min_rate + c->rc_max_rate) / 2;
			c->bit_rate_tolerance = 4000 * 1000;
			// OutputDebugString("CHANGED BITRATE TOLERANCE\n");
		}
		break;
	}
	

	float q = 255;
	c->global_quality = st->quality = FF_QP2LAMBDA * q; // From 0 to 255


	c->rc_buffer_size = m_EncodeParams.GetParams().nOutputVideoBufferSize;
	c->rc_initial_buffer_occupancy = c->rc_buffer_size*3/4;
	c->rc_buffer_aggressivity = 1.0;
    
	c->codec_tag = 0;

	// resolution must be a multiple of two
	c->width = m_EncodeParams.GetParams().nOutputX;  
	c->height = m_EncodeParams.GetParams().nOutputY;

    // frames per second
	c->time_base.den = m_EncodeParams.GetParams().nOutputFPSDen;  
    c->time_base.num = m_EncodeParams.GetParams().nOutputFPSNum;
	c->pix_fmt = STREAM_PIX_FMT;

	if (m_EncodeParams.GetParams().nProfile != -1)
		c->profile = m_EncodeParams.GetParams().nProfile; // 1 = High Profile
	else
		c->profile = 0;

	if (m_EncodeParams.GetParams().nLevel != -1)
		c->level = m_EncodeParams.GetParams().nLevel; // 4 = High Level
	else
		c->level = 10; // Low Level

	switch (m_EncodeParams.GetParams().aspectRatio)
	{
	case ASPECTRATIO_1TO1:
		m_EncodeParams.GetParams().fPixelAspectRatio = (float)1.22222;
		c->sample_aspect_ratio.den = 1;
		c->sample_aspect_ratio.num = 1;
		break;
	case ASPECTRATIO_4TO3:
		m_EncodeParams.GetParams().fPixelAspectRatio = (float)1.3333f;
		c->sample_aspect_ratio = av_d2q(m_EncodeParams.GetParams().fPixelAspectRatio*c->height/c->width, 255);
		break;
	case ASPECTRATIO_16TO9:
		m_EncodeParams.GetParams().fPixelAspectRatio = (float)1.77777777;
		c->sample_aspect_ratio = av_d2q(m_EncodeParams.GetParams().fPixelAspectRatio*c->height/c->width, 255);
		break;
	case ASPECTRATIO_2D11TO1:
		m_EncodeParams.GetParams().fPixelAspectRatio = (float)2.111111111;
		c->sample_aspect_ratio = av_d2q(m_EncodeParams.GetParams().fPixelAspectRatio*c->height/c->width, 255);
		break;
	}


	if (m_EncodeParams.GetParams().bIntraOnly)
		c->gop_size = 0;
	else
		c->gop_size = m_EncodeParams.GetParams().nOutputVideoGOPSize; /* emit one intra frame every twelve frames at most */

	c->max_b_frames = 0; // mp4 compatibility, still used in mpeg-1
	c->b_quant_factor = 2.0;

    if (c->codec_id == CODEC_ID_MPEG2VIDEO &&
		m_EncodeParams.GetParams().systemsOutputFormat != SYSTEMSFORMAT_DVB) {
        /* just for testing, we also add B frames */
        c->max_b_frames = 2;
		c->b_quant_factor = 2.0;
    }
    if (c->codec_id == CODEC_ID_MPEG1VIDEO){
        /* needed to avoid using macroblocks in which some coeffs overflow 
           this doesnt happen with normal video, it just happens here as the 
           motion of the chroma plane doesnt match the luma plane */
        c->mb_decision=2;
    }
    // some formats want stream headers to be seperate
	
    if(strcmp(oc->oformat->name, "mp4") == 0 || 
	   strcmp(oc->oformat->name, "mov") == 0 || 
	   strcmp(oc->oformat->name, "3gp") == 0 ||
	   strcmp(oc->oformat->name, "3g2") == 0 ||
	   strcmp(oc->oformat->name, "psp") == 0)
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;
//	else
//		c->flags2 |= CODEC_FLAG2_LOCAL_HEADER; // ?

	if (m_EncodeParams.GetParams().bForceInterlaceDCT) {
		c->flags |= CODEC_FLAG_INTERLACED_DCT;
    }
    
	if (m_EncodeParams.GetParams().bForceInterlaceME) {
        c->flags |= CODEC_FLAG_INTERLACED_ME;
    }

	if (m_EncodeParams.GetParams().bClosedGOP) {
		c->flags |= CODEC_FLAG_CLOSED_GOP;
		c->scenechange_threshold = 1000000001;
	}

	if (m_EncodeParams.GetParams().nOutputX != m_EncodeParams.GetParams().nInputX ||
		m_EncodeParams.GetParams().nOutputY != m_EncodeParams.GetParams().nInputY)
	{
		m_pImgResampleCtx = img_resample_init( 
                    m_EncodeParams.GetParams().nOutputX, m_EncodeParams.GetParams().nOutputY,
                    m_EncodeParams.GetParams().nInputX, m_EncodeParams.GetParams().nInputY);
		m_bResizeRequired = true;
	}
	else
		m_bResizeRequired = false;

    return st;
}

AVFrame* CEncode::AllocPicture(int pix_fmt, int width, int height)
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;
    
    picture = avcodec_alloc_frame();
    if (!picture)
        return NULL;
    size = avpicture_get_size(pix_fmt, width, height);
    picture_buf = (uint8_t*)malloc(size);
    if (!picture_buf) {
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)picture, picture_buf, 
                   pix_fmt, width, height);
    return picture;
}

int CEncode::StreamOpen(ByteIOContext *s)
{
	/*
	URLProtocol *up;	
    up = first_protocol;
    while (up != NULL) 
	{
        if (strcmp("byte_buf", up->name))
            break;
        up = up->next;
    }

	URLContext *uc;
	uc = (URLContext*)av_malloc(sizeof(URLContext));
    if (!uc) {
        return -1;
    }
    // strcpy(uc->filename, "");
    uc->prot = up;
    uc->flags = 0;
    uc->is_streamed = 0; // default = not streamed
    uc->max_packet_size = 0 // default: stream file
    
    int err = url_fdopen(s, uc);
    if (err < 0) {
        url_close(uc);
        return err;
    }
	*/
    return 0;
}


HRESULT CEncode::OpenVideo(AVFormatContext *oc, AVStream *st)
{
    AVCodec *codec;
    AVCodecContext *c;

    c = st->codec;

    // find the video encoder
    codec = avcodec_find_encoder(c->codec_id);
    if (!codec) {
        Error("Video codec not found\n");
        return E_FAIL;
    }

    // open the codec
    if (avcodec_open(c, codec) < 0) {
        Error("Could not open codec\n");
        return E_FAIL;;
    }

	_ASSERT(m_pVideoOutBuf == NULL);
    m_pVideoOutBuf = NULL;
    m_nVideoOutBufSize = 200000;
    m_pVideoOutBuf = (uint8_t*)malloc(m_nVideoOutBufSize);

    // allocate the encoded raw picture
	_ASSERT(m_pPictureYUV_before_resize == NULL);
    m_pPictureYUV_before_resize = AllocPicture(c->pix_fmt, m_EncodeParams.GetParams().nInputX, m_EncodeParams.GetParams().nInputY);
    if (m_pPictureYUV_before_resize == NULL) {
        Error("Could not allocate picture\n");
        return E_FAIL;;
    }

	m_pPictureYUV_after_resize = AllocPicture(c->pix_fmt, m_EncodeParams.GetParams().nOutputX, m_EncodeParams.GetParams().nOutputY);
    if (m_pPictureYUV_before_resize == NULL) {
        Error("Could not allocate picture\n");
        return E_FAIL;;
    }
	_ASSERT(m_pPictureRGB == NULL);
	m_pPictureRGB = avcodec_alloc_frame();
	_ASSERT(m_pPictureRGB);

	m_pPictureYUV_after_deinterlace = AllocPicture(c->pix_fmt, m_EncodeParams.GetParams().nOutputX, m_EncodeParams.GetParams().nOutputY);
    if (m_pPictureYUV_after_deinterlace == NULL) {
        Error("Could not allocate picture\n");
        return E_FAIL;;
    }

	return S_OK;
}

void CEncode::CloseVideo()
{
	if (m_pPictureYUV_before_resize)
	{
		free(m_pPictureYUV_before_resize->data[0]);
		m_pPictureYUV_before_resize->data[0] = NULL;
		av_free(m_pPictureYUV_before_resize);
		m_pPictureYUV_before_resize = NULL;
	}

	if (m_pPictureYUV_after_resize)
	{
		free(m_pPictureYUV_after_resize->data[0]);
		m_pPictureYUV_after_resize->data[0] = NULL;
		av_free(m_pPictureYUV_after_resize);
		m_pPictureYUV_after_resize = NULL;
	}

	if (m_pPictureYUV_after_deinterlace)
	{
		free(m_pPictureYUV_after_deinterlace->data[0]);
		m_pPictureYUV_after_deinterlace->data[0] = NULL;
		av_free(m_pPictureYUV_after_deinterlace);
		m_pPictureYUV_after_deinterlace = NULL;
	}

	if (m_pPictureRGB)
	{
		av_free(m_pPictureRGB);
		m_pPictureRGB = NULL;
	}

	if (m_pVideoOutBuf)
	{
		free(m_pVideoOutBuf);
		m_pVideoOutBuf = NULL;

		_ASSERT(m_pVideoStream->codec);
		avcodec_close(m_pVideoStream->codec);
	}

	if (m_pVideoStream)
	{
		av_free(m_pVideoStream);
		m_pVideoStream = NULL;
	}
}

HRESULT CEncode::GetAVFiles(char *pstrOutputFile)
{
	strcpy(m_szVideoFileName, pstrOutputFile);
	strcpy(m_szAudioFileName, pstrOutputFile);

	RemoveExtension(m_szVideoFileName);
	RemoveExtension(m_szAudioFileName);

	if (m_bStillImageEncoding)
	{
		strcat(m_szVideoFileName, (".lo.mpg"));
		strcat(m_szAudioFileName, (".hi.mpg"));
	}
	else
	{
		if (m_EncodeParams.GetParams().videoOutputFormat == VIDEOFORMAT_NONE)
			strcpy(m_szAudioFileName, pstrOutputFile);
		else
		{
			strcat(m_szVideoFileName, ("_vid.mpg"));
			strcat(m_szAudioFileName, ("_aud.mpg"));
		}
	}

	return S_OK;
}

void CEncode::RemoveExtension(char *pstr)
{
	// We check if there is at all an extension

	char* pszSlash = strrchr(pstr, '\\');
	char* pszDot = strrchr(pstr, '.');

	if (pszSlash < pszDot && pszDot)
	{
		pszDot[0] = 0;
	}
}



HRESULT CEncode::StartConversion()
{
	m_nAudioSamplesWritten = 0;

	// configure for selected format
	CEncodeParameters::FormatResult res = m_EncodeParams.ConfigureForSelectedFormat();
	
	if (res.bMultiplexing)
	{
		m_pOutputFormat = guess_format(res.pstrSystems, NULL, NULL);
		m_pOutputFormatVideo = m_pOutputFormat;
		m_pOutputFormatAudio = m_pOutputFormat;
	}
	else
	{
		if (res.pstrVideo)
			m_pOutputFormatVideo = guess_format(res.pstrVideo, NULL, NULL);

		if (res.pstrAudio)
			m_pOutputFormatAudio = guess_format(res.pstrAudio, NULL, NULL);
	}

	if (res.audioCodec != CODEC_ID_NONE)
	{
		m_pOutputFormat->audio_codec = res.audioCodec;
	}

	if (res.videoCodec != CODEC_ID_NONE)
	{
		m_pOutputFormat->video_codec = res.videoCodec;
	}


	if (m_pOutputFormat == NULL && m_pOutputFormatVideo == NULL)
	{
		_ASSERT(FALSE);
		return E_POINTER;
	}

	res.FreeAll();

	double dFramerate = (double)m_EncodeParams.GetParams().nOutputFPSDen / (double)m_EncodeParams.GetParams().nOutputFPSNum;
	m_Timestamps.Start(dFramerate, m_EncodeParams.GetParams().wfexAudioSrc.nSamplesPerSec);

	return CreateMediaFile(m_EncodeParams.GetParams().bMultiplex && m_EncodeParams.GetParams().bWriteSystemsFile && m_EncodeParams.GetParams().bDirectMultiplexing, 
						   m_EncodeParams.GetParams().bWriteVideoStream, 
						   m_EncodeParams.GetParams().bWriteAudioStream);
}

HRESULT CEncode::SetBufferCallback(unsigned char* pUserData, BufferCallback pCallback)
{
	m_pUserData = pUserData;
	m_pCallbackFunc = pCallback;
	return S_OK;
}

HRESULT CEncode::CreateMediaFile(bool bSystems, bool bVideo, bool bAudio)
{
	char * pstrOutputFile = m_EncodeParams.GetParams().szOutputFile;

	m_memProtocol.SetCallback(this);

	if (bSystems)
	{
		m_pFormatContext = av_alloc_format_context();
		if (m_pFormatContext == NULL) {
			return E_POINTER;
		}

		m_pFormatContextVideo = m_pFormatContext;
		m_pFormatContextAudio = m_pFormatContext;
		m_pFormatContext->oformat = m_pOutputFormat;
	}

	if (bVideo)
	{
		if (m_pFormatContextVideo == NULL)
		{
			m_pFormatContextVideo = av_alloc_format_context();
			if (m_pFormatContextVideo == NULL) {
				return E_POINTER;
			}
			

			m_pFormatContextVideo->oformat = m_pOutputFormatVideo;
			_snprintf(m_pFormatContextVideo->filename, sizeof(m_pFormatContextVideo->filename), 
			  "%s", m_szVideoFileName);
		}

		m_pVideoStream = NULL;
		if (m_pOutputFormatVideo->video_codec != CODEC_ID_NONE) {
			m_pVideoStream = AddVideoStream(m_pFormatContextVideo, m_pOutputFormatVideo->video_codec);
		}
	}

	if (bAudio && m_pOutputFormatAudio)
	{
		if (m_pFormatContextAudio == NULL)
		{
			m_pFormatContextAudio = av_alloc_format_context();
			if (m_pFormatContextAudio == NULL)
				return E_POINTER;

			m_pFormatContextAudio->oformat = m_pOutputFormatAudio;

			_snprintf(m_pFormatContextAudio->filename, sizeof(m_pFormatContextAudio->filename), 
			  "%s", m_szAudioFileName);
		}

		m_pAudioStream = NULL;
		if (m_pOutputFormatAudio->audio_codec != CODEC_ID_NONE) {
			m_pAudioStream = AddAudioStream(m_pFormatContextAudio, m_pOutputFormatAudio->audio_codec);
		}
	}

	if (m_pFormatContext)
	{
		_snprintf(m_pFormatContext->filename, sizeof(m_pFormatContext->filename), 
				  "%s", pstrOutputFile);

		AVFormatParameters ap;
		memset(&ap, 0, sizeof(ap));
		// ap.image_format = NULL;
		if (av_set_parameters(m_pFormatContext, &ap) < 0) {
		    Error("Invalid output format parameters\n");
			return E_FAIL;
		}

		
		m_pFormatContext->packet_size= m_EncodeParams.GetParams().nMuxPacketSize;
	    m_pFormatContext->mux_rate= m_EncodeParams.GetParams().nMuxRate;
		m_pFormatContext->preload= (int)(m_EncodeParams.GetParams().fMuxPreload * AV_TIME_BASE);
		m_pFormatContext->max_delay = (int)(m_EncodeParams.GetParams().fMuxMaxDelay * AV_TIME_BASE);
	}
	else
	{
		if (m_pFormatContextAudio)
		{
			if (av_set_parameters(m_pFormatContextAudio, NULL) < 0) {
			    Error("Invalid output format parameters\n");
				return E_FAIL;
			}
		}

		if (m_pFormatContextVideo)
		{
			if (av_set_parameters(m_pFormatContextVideo, NULL) < 0) {
			    Error("Invalid output format parameters\n");
				return E_FAIL;
			}
		}
	}

	HRESULT hrVideo = S_OK;
	if (m_pVideoStream)
	{
        if (FAILED(OpenVideo(m_pFormatContextVideo, m_pVideoStream)))
		{
			hrVideo = E_FAIL;
		}
	}

	if (m_pAudioStream)
	{
        if (FAILED(OpenAudio(m_pFormatContextAudio, m_pAudioStream)))
		{
			if (FAILED(hrVideo))
			{
				StopConversion();
				return E_FAIL;
			}
		}
	}


	if (m_pFormatContext)
	{	
		char sz[128];
		sprintf(sz, "memory://systems/%lu", m_memProtocol.GetCount());
	//	MessageBox(0, sz, 0, 0);
		m_memProtocol.AddID(m_memProtocol.GetCount(), sz);

		// if (url_fopen(&m_pFormatContext->pb, "c://jamjam.mpg", URL_WRONLY) < 0) 
		if (url_fopen(&m_pFormatContext->pb, sz, URL_WRONLY) < 0) 
		{
			_ASSERT(FALSE);
			return E_FAIL;
		}

		av_write_header(m_pFormatContext);
		m_bHeaderWritten = true;
	}
	else
	{
		if (m_pFormatContextVideo)
		{
			m_memProtocol.AddID(1, "memory://video");
			if (url_fopen(&m_pFormatContextVideo->pb, "memory://video", URL_WRONLY) < 0) 
			{
				_ASSERT(FALSE);
				return E_FAIL;
			}

			av_write_header(m_pFormatContextVideo);
		}

		if (m_pFormatContextAudio)
		{
			m_memProtocol.AddID(2, "memory://audio");
			if (url_fopen(&m_pFormatContextAudio->pb, "memory://audio", URL_WRONLY) < 0) 
			{
				_ASSERT(FALSE);
				return E_FAIL;
			}

			av_write_header(m_pFormatContextAudio);
		}

		m_bHeaderWritten = true;
	}

	return S_OK;
}


HRESULT CEncode::EncodeRemainingFrames(void)
{
	// encode the delayed video frames
	if (m_pVideoStream && m_pVideoOutBuf)
	{
		AVCodecContext* pCodec = m_pVideoStream->codec;

		int out_size = avcodec_encode_video(pCodec, m_pVideoOutBuf, m_nVideoOutBufSize, NULL);
		while (out_size > 0)
		{
			AVPacket pkt;
			av_init_packet(&pkt);
			
			pkt.pts= av_rescale_q(pCodec->coded_frame->pts, pCodec->time_base, m_pVideoStream->time_base);
			if(pCodec->coded_frame->key_frame)
				pkt.flags |= PKT_FLAG_KEY;
			pkt.stream_index= m_pVideoStream->index;
			pkt.data= m_pVideoOutBuf;
			pkt.size= out_size;
			
			// write the compressed frame in the media file
			av_interleaved_write_frame(m_pFormatContextVideo, &pkt);

			out_size = avcodec_encode_video(pCodec, m_pVideoOutBuf, m_nVideoOutBufSize, NULL);
		}
	}

	if (m_pAudioStream && m_pAudioOutBuf)
	{
		AVCodecContext* pCodec = m_pAudioStream->codec;

		int out_size = avcodec_encode_audio(pCodec, m_pAudioOutBuf, m_nAudioOutBufSize, NULL);
		while (out_size > 0)
		{
			AVPacket pkt;
			av_init_packet(&pkt);
			
			pkt.pts= av_rescale_q(pCodec->coded_frame->pts, pCodec->time_base, m_pAudioStream->time_base);
			if(pCodec->coded_frame->key_frame)
				pkt.flags |= PKT_FLAG_KEY;
			pkt.stream_index= m_pAudioStream->index;
			pkt.data= m_pAudioOutBuf;
			pkt.size= out_size;
			
			// write the compressed frame in the media file
			av_interleaved_write_frame(m_pFormatContextAudio, &pkt);

			out_size = avcodec_encode_audio(pCodec, m_pAudioOutBuf, m_nAudioOutBufSize, NULL);
		}
	}

	return S_OK;
}


HRESULT CEncode::StopConversion(void)
{
	m_lockStop.WaitForUnlock(INFINITE);
	m_lockStop.Lock();

	EncodeRemainingFrames();

	if (m_bHeaderWritten)
	{
		if (m_pFormatContext)
		{
			av_write_trailer(m_pFormatContext);
		}
		else
		{
			if (m_pFormatContextVideo)
				av_write_trailer(m_pFormatContextVideo);

			if (m_pFormatContextAudio)
				av_write_trailer(m_pFormatContextAudio);
		}

		m_bHeaderWritten = false;
	}

	if (m_pVideoStream)
        CloseVideo();

    if (m_pAudioStream)
        CloseAudio();

	if (m_pFormatContextVideo && m_pFormatContextVideo != m_pFormatContext)
	{
		for(int i = 0; i < m_pFormatContextVideo->nb_streams; i++) {
			av_freep(&m_pFormatContextVideo->streams[i]);
		}
		
		m_pVideoStream = NULL;

#if defined(NEW_VERSION)
		if (m_pFormatContextVideo->pb->buffer != NULL)
			url_fclose(m_pFormatContextVideo->pb);

#else
		if (m_pFormatContextVideo->pb.buffer != NULL)
			url_fclose(&(m_pFormatContextVideo->pb));
#endif

		av_free(m_pFormatContextVideo);
		m_pFormatContextVideo = NULL;
	}

	if (m_pFormatContextAudio && m_pFormatContextAudio != m_pFormatContext)
	{
		for(int i = 0; i < m_pFormatContextAudio->nb_streams; i++) {
			av_freep(&m_pFormatContextAudio->streams[i]);
		}

		m_pAudioStream = NULL;

#if defined(NEW_VERSION)
		if (m_pFormatContextAudio->pb->buffer != NULL)
			url_fclose(m_pFormatContextAudio->pb);
#else
		if (m_pFormatContextAudio->pb.buffer != NULL)
			url_fclose(&(m_pFormatContextAudio->pb));
#endif
		av_free(m_pFormatContextAudio);
		m_pFormatContextAudio = NULL;
	}
	
	if (m_pFormatContext)
	{
		if (m_pFormatContextVideo == m_pFormatContext)
			m_pFormatContextVideo = NULL;
		
		if (m_pFormatContextAudio == m_pFormatContext)
			m_pFormatContextAudio = NULL;

#if defined(NEW_VERSION)
		if (m_pFormatContext->pb->buffer)
		{
			url_fclose(m_pFormatContext->pb);
		}
#else
		if (m_pFormatContext->pb.buffer)
		{
			url_fclose(&(m_pFormatContext->pb));
		}
#endif

		// TODO ?? change i = 1 if assert crash
		for(int i = 1; i < m_pFormatContext->nb_streams; i++) {
			av_free(m_pFormatContext->streams[i]);
		}
	    
		m_pAudioStream = NULL;		
		m_pVideoStream = NULL;


		av_free(m_pFormatContext);
		m_pFormatContext = NULL;
	}

	if (m_fifo.buffer)
	{
		av_fifo_free(&m_fifo);
		m_fifo.buffer = NULL;
	}

	if (m_bResizeRequired && m_pImgResampleCtx)
	{
		img_resample_close(this->m_pImgResampleCtx);
		m_pImgResampleCtx = NULL;
		m_bResizeRequired = false;
	}

	if (m_pAudioResampleCtx)
	{
		audio_resample_close(m_pAudioResampleCtx);
		m_pAudioResampleCtx = NULL;
		m_bResampleRequired = true;
	}

	m_pOutputFormatVideo = NULL;
	m_pOutputFormatAudio = NULL;
	m_pOutputFormat = NULL;
//	av_free_static();
// TODO: was this removed or what?
	m_lockStop.Unlock();

	return S_OK;
}

AVFrame* CEncode::AdjustFrameToOutput(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime)
{
	// this function will resize and deinterlace the output video frame
	// in the unregistered version, it will write the logo on the video

	if (m_pVideoStream == NULL)
		return NULL;

	if (m_bRegistered == false)
		m_logoOverlay.OverlayLogo((unsigned char*)pBuf, m_EncodeParams.GetParams().nInputX, m_EncodeParams.GetParams().nInputY);

	AVCodecContext* pCodec = m_pVideoStream->codec;

	if (m_pPictureRGB == NULL)
		return NULL;

	// point the ptr to the buffer
	m_pPictureRGB->data[0] = (unsigned __int8 *)pBuf;
    m_pPictureRGB->linesize[0] = m_EncodeParams.GetParams().nInputX * 3;
  
	// convert from rgb24 to yuv 420
	img_convert((AVPicture*)m_pPictureYUV_before_resize, pCodec->pix_fmt, 
                    (AVPicture *)m_pPictureRGB, PIX_FMT_BGR24,
                    m_EncodeParams.GetParams().nInputX, m_EncodeParams.GetParams().nInputY);

	AVFrame* pFrameToEncode = m_pPictureYUV_before_resize;

	if (m_EncodeParams.GetParams().bDeInterlace)
	{
		if (avpicture_deinterlace((AVPicture*)m_pPictureYUV_after_deinterlace, 
								  (AVPicture*)m_pPictureYUV_before_resize, 
                                  pCodec->pix_fmt, 
								  m_EncodeParams.GetParams().nInputX, 
								  m_EncodeParams.GetParams().nInputY) < 0) 
		{	
			_ASSERT(FALSE);
			m_EncodeParams.GetParams().bDeInterlace = false; // stop trying
		}
		else
			pFrameToEncode = m_pPictureYUV_after_deinterlace;
	}

	/* resampling could be done before raw format conversion in
       some cases to go faster */
    /* only works for YUV420P */
	if (m_bResizeRequired) 
	{
        img_resample(m_pImgResampleCtx, 
					 (AVPicture*)m_pPictureYUV_after_resize, 
					 (AVPicture*)pFrameToEncode);

		pFrameToEncode = m_pPictureYUV_after_resize;
	}

	return pFrameToEncode;

}

HRESULT CEncode::WriteVideoSample(AVFrame* pFrameToEncode)
{
	AVCodecContext* pCodec = m_pVideoStream->codec;
	// long nOutSize = avcodec_encode_video(pCodec, m_pVideoOutBuf, m_nVideoOutBufSize, NULL);

	pFrameToEncode->pts = AV_NOPTS_VALUE;
	long nOutSize = avcodec_encode_video(pCodec, m_pVideoOutBuf, m_nVideoOutBufSize, pFrameToEncode);
	_ASSERT(nOutSize >= 0);

	if (nOutSize > 0) 
	{
		AVPacket pkt;
		av_init_packet(&pkt);
	 	pkt.stream_index = m_pVideoStream->index;
		pkt.data = m_pVideoOutBuf;
		pkt.size = nOutSize;
		
		if (pCodec->coded_frame && pCodec->coded_frame->pts != AV_NOPTS_VALUE)
			pkt.pts= av_rescale_q(pCodec->coded_frame->pts, pCodec->time_base, m_pVideoStream->time_base);

		if (pCodec->coded_frame && pCodec->coded_frame->key_frame)
			pkt.flags |= PKT_FLAG_KEY;

		// write the compressed frame in the media file

		LARGE_INTEGER i4;
		QueryPerformanceCounter(&i4);

		// av_write_frame(m_pFormatContextVideo, &pkt);
		av_interleaved_write_frame(m_pFormatContextVideo, &pkt);

		/*
		LARGE_INTEGER ires;
		QueryPerformanceCounter(&ires);

		static LONGLONG i = 0;
		
	//	if (ires.QuadPart - i4.QuadPart > i)
			i = ires.QuadPart - i4.QuadPart;

//		Trace(" | Time4 : %I64d", i / 10000);
*/

	}


	m_Timestamps.IncrementOutputFrameCount();

	return S_OK;
}


HRESULT CEncode::EncodeVideoSample(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime)
{


	// Get the number of times that this particular frame has to be repeated so
	// that the framerate is corrected to match the specified output framerate
	int nTimesToEncodeThisFrame =  m_Timestamps.GetVideoOutputFrameRepeatCount(llStartTime, llEndTime);
	_ASSERT(nTimesToEncodeThisFrame >= 0);

	if (llStartTime == -1 && llEndTime == -1)
		nTimesToEncodeThisFrame = 1;

	if (nTimesToEncodeThisFrame <= 0) 
	{
		Trace("Dropping Frame\n");
		return S_FALSE; // if a 0 is returned, we need to drop this frame
	}

	if (m_bFramerateCorrection == false)
		nTimesToEncodeThisFrame = 1;

	// resize and deinterlace source frame to match the specified output size and
	// interlace settings
	AVFrame* pFrameToEncode = AdjustFrameToOutput((unsigned __int8 *)pBuf, nLen, llStartTime, llEndTime);
	if (pFrameToEncode == NULL)
		return S_FALSE;

	// write the frame the specified number of times to the file
	for (int i=0;i<nTimesToEncodeThisFrame;i++)
	{
		Trace("Repeating Frame: %lu\n", nTimesToEncodeThisFrame);
		// ASSERT(nTimesToEncodeThisFrame == 0);
		WriteVideoSample(pFrameToEncode);
	}

	return S_OK;
}

int CEncode::MemWrite(int nID, unsigned char *buf, int size)
{
	m_pCallbackFunc(m_pUserData, buf, size, 1, 0, nID);
	return 0;
}

int CEncode::MemClose(int nID)
{
	m_pCallbackFunc(m_pUserData, 0, 0, 2, 0, nID);
	return 0;
}

int CEncode::MemOpen(int nID)
{
	m_pCallbackFunc(m_pUserData, 0, 0, 0, 0, nID);
	return 0;
}

signed __int64 CEncode::MemSeek(int nID, signed __int64 seekPos)
{
	return m_pCallbackFunc(m_pUserData, 0, 0, 3, seekPos, nID);
}


#define PROFILE(x) printf(x);

HRESULT CEncode::EncodeAudioBuffer(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime)
{
	if (m_pAudioStream == NULL || m_pFormatContextAudio == NULL || pBuf == NULL)
		return E_POINTER;


	AVCodecContext* pCodec = m_pAudioStream->codec;
//	_ASSERT(m_pAudioResampleCtx);
//	if (m_pAudioResampleCtx == NULL)
//		return E_POINTER;

	if (m_bResampleRequired)
	{
		printf("Resampling Audio: Input Len %lu. StartTime=%lu, EndTime=%lu. TimeLen=%lu\n", nLen, (long)llStartTime, (long)llEndTime, (long)(llEndTime-llStartTime));

		long size_out = 0;
		m_pResample->Resample(pBuf, nLen, &m_pAudioInBuf, size_out);
		pBuf = m_pAudioInBuf;
		nLen = size_out;

		
		// printf("Resample Done. Size:%lu\n", nLen);
			/*
		// printf("-----");
		// printf("Len:%lu, Channels:%lu\n", nLen, m_EncodeParams.GetParams().nOutputAudioChannels);

		// resample audio. 'nb_samples' is the number of input samples
		// int audio_resample(ReSampleContext *s, short *output, short *input, int nb_samples)

		// long outputLen = (m_EncodeParams.GetParams().wfexAudioSrc.nChannels * 2)

		long nInputChannels = m_EncodeParams.GetParams().wfexAudioSrc.nChannels;
		long nOutputChannels = m_EncodeParams.GetParams().nOutputAudioChannels;
		long nInputSampleRate = m_EncodeParams.GetParams().wfexAudioSrc.nSamplesPerSec;
		long nOutputSampleRate = m_EncodeParams.GetParams().nOutputAudioSampleRate;

		long numberOfInputSamples = nLen / (m_EncodeParams.GetParams().wfexAudioSrc.nChannels * 2);
		long outputSize = numberOfInputSamples * nOutputChannels * 2;

		//printf("Required Output Buffer Size = %lu. Cur Buffer Size = %lu\n", outputSize, 2 * MAX_AUDIO_PACKET_SIZE);

		//printf("Buf=%lu\n", pBuf);

		int size_out = 0;
		unsigned __int8* pResampledAudio = NULL;
		// if (
		// __try
		{
		//	printf("Input Audio Sample=%lu\n", numberOfInputSamples);

	//		PROFILE("About to resample");
			pResampledAudio = m_pAudioInBuf;
			size_out = audio_resample(m_pAudioResampleCtx, 
									  (short*)pResampledAudio, (short *)pBuf,
									  numberOfInputSamples);
			printf("Size out: %lu\n", size_out);
		}
		// __except
		// {
		//	printf("Resample overflow. Sample:%lu\n", (long)llStartTime);
		// }

		size_out = size_out * m_EncodeParams.GetParams().nOutputAudioChannels * 2;

		pBuf = pResampledAudio;
		nLen = size_out;

		*/
		// OutputDebugString("RESAMPLE COMMENTED OUT!");
	}

//	PROFILE("About to write chunk into fifo");

	// get the size of the chunks we want to write
	long nChunkSize = m_nAudioInputFrameSize * 2 * pCodec->channels;

	// put the new data we just received into the fifo
	av_fifo_write(&m_fifo, pBuf, nLen);

	// printf("Wrote Fifo\n");

	// so long we have at least nChunkSize in the fifo...
	while (av_fifo_size(&m_fifo) >= nChunkSize)
	{
	//	printf("In while");

			// read some data
			av_fifo_read(&m_fifo, m_pAudioInBuf, nChunkSize);

		    AVPacket pkt;
			av_init_packet(&pkt);
			pkt.size = avcodec_encode_audio(pCodec, m_pAudioOutBuf, m_nAudioOutBufSize, (short*)m_pAudioInBuf);
			_ASSERT(pkt.size >= 0);
			pkt.pts= av_rescale_q(pCodec->coded_frame->pts, pCodec->time_base, m_pAudioStream->time_base);
			pkt.flags |= PKT_FLAG_KEY;
			pkt.stream_index= m_pAudioStream->index;
			pkt.data= m_pAudioOutBuf;

			// write the compressed frame in the media file
			// if (av_interleaved_write_frame(m_pFormatContextAudio, &pkt) != 0) {
			if (av_interleaved_write_frame(m_pFormatContextAudio, &pkt) != 0) {
			
				_ASSERT(FALSE);
				Error("Error while writing audio frame\n");
				return E_FAIL;
			}

			m_nAudioSamplesWritten += m_nAudioInputFrameSize;
    }

	return S_OK;
}


HRESULT CEncode::EncodeAudioWithDriftCorrection(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime)
{
	


	return S_OK;
}



HRESULT CEncode::EncodeAudioSample(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime)
{
	// m_Timestamps.AddAudioSample(llStartTime, llEndTime);

	return EncodeAudioBuffer(pBuf, nLen, llStartTime, llEndTime);

	if (m_bAudioCorrection == false || (llStartTime == 0 && llEndTime == 0 && nLen != 0))
		return EncodeAudioBuffer(pBuf, nLen, llStartTime, llEndTime);
	
	long bytesPerSamplesSrc = m_EncodeParams.GetParams().wfexAudioSrc.wBitsPerSample / 8;

//	PROFILE("Entering Audio Encode");
	
//	printf("Bits per sample=%lu\n", m_EncodeParams.GetParams().wfexAudioSrc.wBitsPerSample);

	// get number of samples to add to correct the time problem
	LONGLONG llCorrectionTime = 0;
	int nSamplesToAdd = m_Timestamps.GetAudioSampleCorrection(llStartTime, llEndTime, llCorrectionTime);
	int nSamplesToAddBytes = nSamplesToAdd * m_EncodeParams.GetParams().wfexAudioSrc.nChannels * bytesPerSamplesSrc;

	// nSamplesToAddBytes = 0;
//	printf("Start Time: %lu, End Time: %lu\n", (long)llStartTime, (long)llEndTime);

//	printf("Drift Correction: To Add = %lu\n", nSamplesToAdd);

	
	static int first_enc = 0;
	if (first_enc == 0)
	{
		first_enc = 1;
		nSamplesToAddBytes = 0;
		m_Timestamps.IncrementAudioDrift(-llCorrectionTime);
	}

	// 58392 causes a crash
//	if (nSamplesToAddBytes > 25000)
//	 	nSamplesToAddBytes = 25000;

	// nSamplesToAddBytes = 0;

	/*
	long nLeftOver = 0;
	if (nSamplesToAddBytes >= (2 * MAX_AUDIO_PACKET_SIZE) - 1)
	{
		nLeftOver = nSamplesToAddBytes - ((2 * MAX_AUDIO_PACKET_SIZE) - 1);
		nSamplesToAddBytes = (2 * MAX_AUDIO_PACKET_SIZE) - 1;
	}
	*/

	// if there is a positive or negative difference in samples
	if (nSamplesToAddBytes)
	{
//		PROFILE("Adding Bytes");

		if (nSamplesToAddBytes > 0)
		{
			int loop_count = 0;
			while (nSamplesToAddBytes > 0)
			{
				loop_count++;
				printf("Silence Loop:%lu\n", loop_count);

				// Potential bug here: The max len of our
				// silence is the full buffer. But at the
				// bottom we copy stuff into this buffer
				// Is our buffer really 2*max_audio_pack?

				// there is a hole
				long nSilence = nSamplesToAddBytes; // get number of bytes to add
				if (nSilence >=(2 * MAX_AUDIO_PACKET_SIZE) - 1)
				{
					// If larger than our buffer, truncate to buffer size
					nSilence = (2 * MAX_AUDIO_PACKET_SIZE) - 1;
					PROFILE("Silence truncated");
				}

				// Subtract the amount of silence we will use from the silence buffer
				nSamplesToAddBytes -= nSilence;

				_ASSERT(nSilence);
				nLen += nSilence;
				if (nLen > 2 * MAX_AUDIO_PACKET_SIZE)
					printf("FATAL BUFFER OVERFLOW\n");

				_ASSERT(nLen < 2 * MAX_AUDIO_PACKET_SIZE);

				// create new buffer
				BYTE* pBufWithSilence = (BYTE*)malloc(nLen);


				// set it to silence
				BYTE bSilence = m_EncodeParams.GetParams().wfexAudioSrc.wBitsPerSample == 8 ? 128 : 0;
				FillMemory((BYTE*)pBufWithSilence, nLen, bSilence);

//				PROFILE("About to copy\n");

				// the bug here is that if we loop this more than once, we will
				// write the same audio several times into the buffer
				// copy the original buffer into it
				memcpy(pBufWithSilence + nSilence, pBuf, nLen - nSilence);

//				PROFILE("About to encode\n");

				// encode the buffer with silence prepended
				EncodeAudioBuffer((unsigned __int8*)pBufWithSilence, nLen, llStartTime, llEndTime);

				// delete that buffer
				delete [] pBufWithSilence;
			
			}

			m_Timestamps.IncrementAudioDrift(-llCorrectionTime);
		}
		else if (nSamplesToAddBytes < 0)
		{
			printf("Removing bytes!\n");

//			PROFILE("Removing Bytes");
			_ASSERT(nSamplesToAddBytes);

			int nSamplesToRemoveBytes = -nSamplesToAddBytes;
			
			// we want to remove the first n bytes, so mov ptr by that much
			pBuf += nSamplesToRemoveBytes;

			// and reduce the len by that much
			nLen -= nSamplesToRemoveBytes;

			EncodeAudioBuffer(pBuf, nLen, llStartTime, llEndTime);

			m_Timestamps.IncrementAudioDrift(llCorrectionTime);
		}
	}
	else
	{
		// printf("Calling encode direct\n");

//		PROFILE("Calling Buffer Encode");
		EncodeAudioBuffer(pBuf, nLen, llStartTime, llEndTime);
	}


	return S_OK;
}

void CEncode::Error(char* pstr)
{
	MessageBox(0, pstr, "Encoder Error", 0);
//	OutputDebugString(pstr);
//	_ASSERT(FALSE);
}

HRESULT CEncode::SetEncodeParameter(char* pstrParameterName, char* pstrParameterValue)
{
	return m_EncodeParams.SetEncodeParameter(pstrParameterName, pstrParameterValue);
}

long CEncode::SetEncodeParams(EncodeParameters* params)
{
	m_EncodeParams.SetEncodeParams(params);

	if (m_EncodeParams.GetParams().systemsOutputFormat == SYSTEMSFORMAT_VCD_STILL ||
		m_EncodeParams.GetParams().systemsOutputFormat == SYSTEMSFORMAT_SVCD_STILL)
		m_bStillImageEncoding = true;

	return S_OK;
}



void CEncode::SetRegistered(bool b)
{
	m_bRegistered = b;
}

HRESULT CEncode::FileMultiplex(char *pstrFile1, char *pstrFile2, char* pstrOutputFile, int nFormat, int nExtra)
{
	switch (nFormat)
	{
	case SYSTEMSFORMAT_VCD_STILL:
		{
			m_Multiplex.SetFiles(pstrFile1, pstrFile2, pstrOutputFile);
			m_Multiplex.SetParameters((EnumSystemsOutputFormat)nFormat, 2352 * 75 * 8, false, 0, false);
		}
		break;
	case SYSTEMSFORMAT_SVCD_STILL:
		{
			char* pstrFile = pstrFile2 ? pstrFile2 : pstrFile1;
			m_Multiplex.SetFiles(NULL, pstrFile, pstrOutputFile);
			m_Multiplex.SetParameters((EnumSystemsOutputFormat)nFormat, 2352 * 75 * 8, false, 0, false);
		}
		break;
	default:
		{
			m_Multiplex.SetFiles(m_EncodeParams.GetParams().bWriteAudioStream ? pstrFile1 : NULL,
							 m_EncodeParams.GetParams().bWriteVideoStream ? pstrFile2 : NULL,
							 pstrOutputFile);
		}
	}

	m_Multiplex.StartMultiplex(false);
	m_Multiplex.StopMultiplex();

	return S_OK;
}

