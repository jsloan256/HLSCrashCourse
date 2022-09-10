#ifndef __SIGNALGENERATORSTRUCTS_H__
#define __SIGNALGENERATORSTRUCTS_H__

template<typename Tf, typename T1>
struct SignalGeneratorControlRegistersT
{
  Tf RadiansPerSample;
  Tf Vpp;
  T1 StartSG;
};

#endif