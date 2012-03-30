/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef __CACHECAST_H__
#define __CACHECAST_H__

#include <vector>
#include <stdint.h>
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
    typedef std::vector<Ptr<Socket> >::const_iterator Iterator;
 
    static TypeId GetTypeId (void);     
    bool Msend(Ptr<Packet> packet);
    void AddSocket(Ptr<Socket> socket);
    void RemoveSocket(Ptr<Socket> socket);
    
    void Merge(CacheCast cc);
   
    Iterator Begin (void) const;
    Iterator End (void) const;
 
    Iterator BeginFailedSockets (void) const;
    Iterator EndFailedSockets (void) const;

    
};


} //end namespace ns3

#endif /* __CACHECAST_H__ */

