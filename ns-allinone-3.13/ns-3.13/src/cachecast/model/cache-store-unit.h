/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHE_STORE_UNIT_H__
#define __CACHE_STORE_UNIT_H__

#include "ns3/object.h"
#include "ns3/packet.h"
#include "cachecast-element.h"

namespace ns3 {

/**
 * /brief Cache Store Unit
 *
 */
class CacheStoreUnit : public CacheCastElement
{
public:
  /**
   * /brief Construct an empty CacheStoreUnit
   */
  CacheStoreUnit ();

  /** 
   * Documented in CacheCastElement 
   */
  virtual bool HandlePacket (Ptr<Packet> p);

  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
};

} // namespace ns3

#endif /* __CACHE_STORE_UNIT_H__ */
