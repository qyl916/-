/***************************************************************************/
/*                                                                         */
/* beeper.h                                                                */
/*   提供蜂鸣器的部分功能的程序接口。                                      */
/*                                                                         */
/***************************************************************************/
#ifndef __BEEPER_H__
#define __BEEPER_H__

#ifdef __cplusplus
extern "C"{
#endif

  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    BEEPER_Set_Tune                                                    */
  /*  <Description>                                                        */
  /*    写入音调数据。                                                     */
  /*  <Input>                                                              */
  /*    tune :: 音调信息                                                   */
  /*  <Note>                                                               */
  /*    12*9共108个音，C0是-48，C#0是-47，C4是0，以此类推，一直到          */
  /*    B9（71）。                                                         */
  /*                                                                       */
void BEEPER_Set_Tune(signed char tune);

  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    BEEPER_Set_Length                                                  */
  /*  <Description>                                                        */
  /*    写入声音长度。                                                     */
  /*  <Input>                                                              */
  /*    length :: 音调长度，单位毫秒。                                     */
  /*  <Note>                                                               */
  /*    0表示不限制长度，无限播放。                                        */
  /*                                                                       */
void BEEPER_Set_Length(unsigned char length);

  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    BEEPER_Start                                                       */
  /*  <Description>                                                        */
  /*    开始播放。                                                         */
  /*                                                                       */
void BEEPER_Start(void);

  /*************************************************************************/
  /*                                                                       */
  /*  <Function>                                                           */
  /*    BEEPER_Stop                                                        */
  /*  <Description>                                                        */
  /*    停止播放。                                                         */
  /*                                                                       */
void BEEPER_Stop(void);

#ifdef __cplusplus
}
#endif

#endif
