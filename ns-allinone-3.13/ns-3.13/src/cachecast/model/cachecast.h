/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_H__
#define __CACHECAST_H__

#include <vector>
#include "ns3/socket.h"
#include "ns3/packet.h"

namespace ns3 {

/* ... */
class CacheCast
{

public:    
    bool Msend(Ptr<Packet> packet);
    void AddSocket(Ptr <Socket> socket);
    std::vector <Socket>* m_sockets;
    
};


} //end namespace ns3

#endif /* __CACHECAST_H__ */

