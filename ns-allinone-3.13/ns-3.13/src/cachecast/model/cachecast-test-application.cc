/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/log.h"
#include "ns3/cachecast-module.h"
#include "ns3/packet.h"
#include "ns3/address.h"
#include "ns3/inet-socket-address.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastTestApplication");

using namespace ns3;

NS_OBJECT_ENSURE_REGISTERED (CacheCastTestApplication);

TypeId
CacheCastTestApplication::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCastTestApplication")
    .SetParent<Application> ()
    .AddConstructor<CacheCastTestApplication> ()
  ;

  return tid;
}

CacheCastTestApplication::CacheCastTestApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
CacheCastTestApplication::SetAddress (Address address)
{
  NS_LOG_FUNCTION (this);
  m_address = address;
}

void
CacheCastTestApplication::SocketFailed (uint32_t socketIndex)
{
  NS_LOG_INFO (socketIndex << "hurray\n");
}

void
CacheCastTestApplication::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

//   Ptr<Node> node = GetNode();
//   for (uint32_t i = 0; i < node->GetNDevices (); i++)
//   {
//     Ptr<CacheCastServerNetDevice> ccDev = DynamicCast<CacheCastServerNetDevice> (node->GetDevice (i));
//     if (ccDev != 0)
//     {
//       ccDev->SetFailedCallback (MakeCallback (&CacheCastTestApplication::SocketFailed, this));
//     }
//   }


//   m_sock = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::UdpSocketFactory"));

//   NS_ASSERT_MSG (m_sock->GetSocketType () == Socket::NS3_SOCK_DGRAM,
//       "CacheCast only supports UDP packets");

  Ptr<Socket> sock1 = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  sock1->Bind();
  sock1->Connect (m_address);

  Ptr<Socket> sock2 = Socket::CreateSocket(GetNode (), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  sock2->Bind();
  sock2->Connect (m_address);

  int NUM = 2;

  CacheCast cc;
  cc.AddSocket (sock1);
  cc.AddSocket (sock2);

  Ptr<Packet> packet = Create<Packet> (1000);
  NS_LOG_INFO ("Packet size: " << packet->GetSize ());

  cc.Msend(packet);

//   for (int i = 0; i < NUM; i++)
//     {
// //       CacheCastTag tag (i-1, 1000);
// //       packet->AddPacketTag (tag);
//     
// //       m_sock->Send (packet);
// //       NS_LOG_INFO ("Sent " << packet->GetSize () << " bytes to " <<
// //           InetSocketAddress::ConvertFrom (m_address).GetIpv4 ());
//     }

  

//   Ptr<Packet> packet = Create<Packet> (1000);
// 
// 
//   Ptr<Packet> p = Copy<Packet> (packet);
// 
// 
//   CacheCastTag tag (NUM-1, 1000, true);
//   p->AddPacketTag (tag);


//   std::cerr << "test " << p->PeekPacketTag (tag) << "\n";
//   std::cerr << "test " << packet->PeekPacketTag (tag) << "\n";


//   sock->Send (p);
//   NS_LOG_INFO ("Sent " << packet->GetSize () << " bytes to " <<
//       InetSocketAddress::ConvertFrom (m_address).GetIpv4 ());
}

void
CacheCastTestApplication::StopApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

//   m_sock->Close();
}
