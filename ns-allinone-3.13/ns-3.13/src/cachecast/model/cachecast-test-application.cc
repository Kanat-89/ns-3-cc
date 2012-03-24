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
CacheCastTestApplication::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  m_sock = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  m_sock->Bind();
  m_sock->Connect (m_address);

  int NUM = 2;

  for (int i = 1; i < NUM; i++)
    {
      Ptr<Packet> packet = Create<Packet> (1000);
      CacheCastTag tag (1000);
      packet->AddPacketTag (tag);

      m_sock->Send (packet);
      NS_LOG_INFO ("Sent " << packet->GetSize () << " bytes to " <<
          InetSocketAddress::ConvertFrom (m_address).GetIpv4 ());
    }

  Ptr<Socket> sock = Socket::CreateSocket(GetNode (), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  sock->Bind();
  sock->Connect (m_address);

  Ptr<Packet> packet = Create<Packet> (1000);
  CacheCastTag tag (1000, true);
  packet->AddPacketTag (tag);

  sock->Send (packet);
  NS_LOG_INFO ("Sent " << packet->GetSize () << " bytes to " <<
      InetSocketAddress::ConvertFrom (m_address).GetIpv4 ());
}

void
CacheCastTestApplication::StopApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  m_sock->Close();
}
