#ifndef __MP3CTRL_H__
#define __MP3CTRL_H__

void MP3Control1_Initial_IO(void);
void MP3Control1_Set(void);
void MP3Control1_Clear(void);
void MP3Control2_Set(void);
void MP3Control2_Clear(void);
void MP3Control3_Set(void);
void MP3Control3_Clear(void);
void MP3Control4_Set(void);
void MP3Control4_Clear(void);

void MP3KeyControl1_PlayPause(void);
void MP3KeyControl1_Stop(void);
void MP3KeyControl1_Previous(void);
void MP3KeyControl1_Next(void);
void MP3KeyControl1_VolumeDec(void);
void MP3KeyControl1_VolumeInc(void);

#endif /*__MP3CTRL_H__*/