/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

/* 
 * This file is based on the PointToPointChannel
 *
 * Copyright info for the PointToPointChannel below
 */

/*
 * Copyright (c) 2007, 2008 University of Washington
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "cachecast-channel.h"
#include "cachecast-net-device.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastChannel");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastChannel);

TypeId 
CacheCastChannel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::CacheCastChannel")
    .SetParent<Channel> ()
    .AddConstructor<CacheCastChannel> ()
    .AddAttribute ("Delay", "Transmission delay through the channel",
                   TimeValue (Seconds (0)),
                   MakeTimeAccessor (&CacheCastChannel::m_delay),
                   MakeTimeChecker ())
    .AddTraceSource ("TxRxPointToPoint",
                     "Trace source indicating transmission of packet from the CacheCastChannel, used by the Animation interface.",
                     MakeTraceSourceAccessor (&CacheCastChannel::m_txrxPointToPoint))
  ;
  return tid;
}

//
// By default, you get a channel that 
// has an "infitely" fast transmission speed and zero delay.
CacheCastChannel::CacheCastChannel()
  :
    Channel (),
    m_delay (Seconds (0.)),
    m_nDevices (0)
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
CacheCastChannel::Attach (Ptr<CacheCastNetDevice> device)
{
  NS_LOG_FUNCTION (this << device);
  NS_ASSERT_MSG (m_nDevices < N_DEVICES, "Only two devices permitted");
  NS_ASSERT (device != 0);

  m_link[m_nDevices++].m_src = device;
//
// If we have both devices connected to the channel, then finish introducing
// the two halves and set the links to IDLE.
//
  if (m_nDevices == N_DEVICES)
    {
      m_link[0].m_dst = m_link[1].m_src;
      m_link[1].m_dst = m_link[0].m_src;
      m_link[0].m_state = IDLE;
      m_link[1].m_state = IDLE;
    }
}

bool
CacheCastChannel::TransmitStart (
  Ptr<Packet> p,
  Ptr<CacheCastNetDevice> src,
  Time txTime)
{
  NS_LOG_FUNCTION (this << p << src);
  NS_LOG_LOGIC ("UID is " << p->GetUid () << ")");

  NS_ASSERT (m_link[0].m_state != INITIALIZING);
  NS_ASSERT (m_link[1].m_state != INITIALIZING);

  uint32_t wire = src == m_link[0].m_src ? 0 : 1;

  Simulator::ScheduleWithContext (m_link[wire].m_dst->GetNode ()->GetId (),
                                  txTime + m_delay, &CacheCastNetDevice::Receive,
                                  m_link[wire].m_dst, p);

  // Call the tx anim callback on the net device
  m_txrxPointToPoint (p, src, m_link[wire].m_dst, txTime, txTime + m_delay);
  return true;
}

uint32_t 
CacheCastChannel::GetNDevices (void) const
{
  NS_LOG_FUNCTION_NOARGS ();
  return m_nDevices;
}

Ptr<CacheCastNetDevice>
CacheCastChannel::GetPointToPointDevice (uint32_t i) const
{
  NS_LOG_FUNCTION_NOARGS ();
  NS_ASSERT (i < 2);
  return m_link[i].m_src;
}

Ptr<NetDevice>
CacheCastChannel::GetDevice (uint32_t i) const
{
  NS_LOG_FUNCTION_NOARGS ();
  return GetPointToPointDevice (i);
}

Time
CacheCastChannel::GetDelay (void) const
{
  return m_delay;
}

Ptr<CacheCastNetDevice>
CacheCastChannel::GetSource (uint32_t i) const
{
  return m_link[i].m_src;
}

Ptr<CacheCastNetDevice>
CacheCastChannel::GetDestination (uint32_t i) const
{
  return m_link[i].m_dst;
}

bool
CacheCastChannel::IsInitialized (void) const
{
  NS_ASSERT (m_link[0].m_state != INITIALIZING);
  NS_ASSERT (m_link[1].m_state != INITIALIZING);
  return true;
}

} // namespace ns3
