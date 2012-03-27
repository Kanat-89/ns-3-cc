/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_PID_H__
#define __CACHECAST_PID_H__

// #include "ns3/point-to-point-net-device.h"
// #include "ns3/queue.h"
// #include "ns3/callback.h"
// #include <vector>
#include "ns3/object.h"

namespace ns3 {

/**
 * /brief CacheCast payload ID.
 * One object of this class is added to a CacheCast supported node
 * so that the payload ID is synchronized on each node.
 * One (and only one) instance of this object should be aggregated to a node.
 */
class CacheCastPid : public Object
{
public:
  /**
   * /brief Construct an empty CacheCastPid
   */
  CacheCastPid ();

  /**
   * \brief returns the current payload ID
   */
  uint32_t GetPayloadId () const;

  /**
   * \brief Calculate a new payload ID.
   * This is called when a new batch of packet should be sent.
   */
  uint32_t CalculateNewPayloadId ();

  static TypeId GetTypeId (void);
  TypeId GetInstanceTypeId (void) const;
  
private:
  /** The current payload ID */
  uint32_t m_payloadId;
  /** The previous time of a wrap around of payload IDs*/
  double m_preTime;
};

} // namespace ns3

#endif /* __CACHECAST_PID_H__ */
