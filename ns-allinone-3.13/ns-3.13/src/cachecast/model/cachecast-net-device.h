/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_NET_DEVICE_H__
#define __CACHECAST_NET_DEVICE_H__

#include "ns3/point-to-point-net-device.h"

namespace ns3 {

/**
 * /brief CacheCast NetDevice
 */
class CacheCastNetDevice : public PointToPointNetDevice
{
public:
  /**
   * /brief Construct an empty CacheCastNetDevice
   */
  CacheCastNetDevice ();

  void GetTest();

private:
  int m_test;

};

} // namespace ns3

#endif /* __CACHECAST_NET_DEVICE_H__ */
