/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_ELEMENT_H__
#define __CACHECAST_ELEMENT_H__

#include "ns3/object.h"
#include "ns3/packet.h"

namespace ns3 {

/**
 * /brief CacheCast packet handling element.
 *
 * Classes cen be derived from this class in order
 * to implement e.g. CSU and CMU.
 */
class CacheCastElement : public Object
{
public:
   /**
   * \brief This function does some packet manipulation 
   *        specified by the classes implementing it.
   *
   * The function must be implemented by all derived classes.
   *
   * \param p the packet to modify
   *
   * \returns true if the manipulation was successful,
   *          false otherwise
   */
  virtual bool HandlePacket (Ptr<Packet> p) = 0;

  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
};

} // namespace ns3

#endif /* __CACHECAST_ELEMENT_H__ */
