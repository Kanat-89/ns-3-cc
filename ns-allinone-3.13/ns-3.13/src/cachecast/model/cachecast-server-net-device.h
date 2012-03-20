/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_SERVER_NET_DEVICE_H__
#define __CACHECAST_SERVER_NET_DEVICE_H__

#include "ns3/point-to-point-net-device.h"
#include "ns3/queue.h"

namespace ns3 {

/**
 * /brief CacheCast NetDevice
 */
class CacheCastServerNetDevice : public PointToPointNetDevice
{
public:
  static TypeId GetTypeId (void);
  /**
   * /brief Construct an empty CacheCastServerNetDevice
   */
  CacheCastServerNetDevice ();

  bool Send (Ptr<Packet> packet, const Address &dest, uint16_t protocolNumber);
  
private:
  /**
   * The queue which this CacheCastServerNetDevice uses to store the CacheCast packets
   * before they are sent as a batch onto the channel
   */
  Ptr<Queue> m_ccQueue;

  /**
   * The next free payload ID to use
   */
  uint32_t m_nextPayloadId;

};

} // namespace ns3

#endif /* __CACHECAST_SERVER_NET_DEVICE_H__ */
