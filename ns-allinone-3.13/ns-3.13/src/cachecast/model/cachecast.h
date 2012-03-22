/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_H__
#define __CACHECAST_H__

#include "ns3/socket.h"
#include <vector>

namespace ns3 {

/* ... */
class CacheCast
{
public:
    CacheCast ();
    void Add (Socket socket);

    bool Msend ();


}


} //end namespace ns3

#endif /* __CACHECAST_H__ */

