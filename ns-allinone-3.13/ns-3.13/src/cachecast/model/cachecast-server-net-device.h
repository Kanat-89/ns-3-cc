/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_SERVER_NET_DEVICE_H__
#define __CACHECAST_SERVER_NET_DEVICE_H__

#include "ns3/point-to-point-net-device.h"

namespace ns3 {

/**
 * /brief CacheCast NetDevice
 */
class CacheCastServerNetDevice : public PointToPointNetDevice
{
public:
  /**
   * /brief Construct an empty CacheCastServerNetDevice
   */
  CacheCastServerNetDevice ();

  void GetTest();

private:
  int m_test;

};

} // namespace ns3

#endif /* __CACHECAST_SERVER_NET_DEVICE_H__ */
