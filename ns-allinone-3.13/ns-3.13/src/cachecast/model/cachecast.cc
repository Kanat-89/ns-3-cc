/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "cachecast.h"

NS_LOG_COMPONENT_DEFINE ("CacheCast");


namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED (CacheCast);



void 
CacheCast::AddSocket (Ptr<Socket> socket)
{
    m_sockets.push_back (socket);
}

bool 
CacheCast::Msend(Ptr<Packet> packet)
{
    vector<Socket>*:: iterator socket;
    bool failed;
    for(socket = m_sockets.begin(); socket != m_sockets.end(); ++socket)
    {
        if(socket->Send(packet) < 0){
           failed = true; 
        }  
    }
    return successful; 
}

}//end namespace ns3

