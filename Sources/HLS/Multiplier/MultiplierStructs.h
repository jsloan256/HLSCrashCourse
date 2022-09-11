#ifndef __MULTIPLIERSTRUCTS_H__
#define __MULTIPLIERSTRUCTS_H__

template<typename Tf, typename T1>
struct MultiplierControlRegistersT
{
  Tf RadiansPerSample;
  Tf Vp;
  T1 StartSG;
};

#endif
