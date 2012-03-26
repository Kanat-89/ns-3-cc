/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_H__
#define __CACHECAST_H__

#include <vector>
#include "ns3/socket.h"
#include "ns3/packet.h"

namespace ns3 {

/* ... */
class CacheCast : public Object
{
    std::vector <Ptr <Socket> > m_sockets; 
    std::vector <Ptr <Socket> > m_failed;
    
    void SetFailedSocket(uint32_t i);


public:
    static TypeId GetTypeId (void);     
    bool Msend(Ptr<Packet> packet);
    void AddSocket(Ptr<Socket> socket);
    
};


} //end namespace ns3

#endif /* __CACHECAST_H__ */

