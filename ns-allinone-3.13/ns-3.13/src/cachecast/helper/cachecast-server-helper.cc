/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "cachecast-server-helper.h"

#include "ns3/abort.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/cachecast-net-device.h"
#include "ns3/cachecast-channel.h"
// #include "ns3/point-to-point-remote-channel.h"
#include "ns3/queue.h"
#include "ns3/config.h"
#include "ns3/packet.h"
#include "ns3/names.h"
#include "ns3/mpi-interface.h"
#include "ns3/mpi-receiver.h"
#include "ns3/trace-helper.h"

#include "ns3/cachecast-pid.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastServerHelper");

namespace ns3 {

CacheCastServerHelper::CacheCastServerHelper ()
{
  //TODO change to CacheCastNetDevice
  m_deviceFactory.SetTypeId ("ns3::CacheCastNetDevice");
  m_queueFactory.SetTypeId ("ns3::DropTailQueue");
  m_serverDeviceFactory.SetTypeId ("ns3::CacheCastServerNetDevice");
  m_channelFactory.SetTypeId ("ns3::CacheCastChannel");
//   m_remoteChannelFactory.SetTypeId ("ns3::PointToPointRemoteChannel");
}

// void 
// CacheCastServerHelper::SetQueue (std::string type,
//                               std::string n1, const AttributeValue &v1,
//                               std::string n2, const AttributeValue &v2,
//                               std::string n3, const AttributeValue &v3,
//                               std::string n4, const AttributeValue &v4)
// {
//   m_queueFactory.SetTypeId (type);
//   m_queueFactory.Set (n1, v1);
//   m_queueFactory.Set (n2, v2);
//   m_queueFactory.Set (n3, v3);
//   m_queueFactory.Set (n4, v4);
// }

void 
CacheCastServerHelper::SetDeviceAttribute (std::string n1, const AttributeValue &v1)
{
  // TODO enable and check inheritance of attributes
//   m_serverDeviceFactory.Set (n1, v1);
  m_deviceFactory.Set (n1, v1);
}

void 
CacheCastServerHelper::SetChannelAttribute (std::string n1, const AttributeValue &v1)
{
  m_channelFactory.Set (n1, v1);
//   m_remoteChannelFactory.Set (n1, v1);
}

// void 
// CacheCastServerHelper::EnablePcapInternal (std::string prefix, Ptr<NetDevice> nd, bool promiscuous, bool explicitFilename)
// {
//   //
//   // All of the Pcap enable functions vector through here including the ones
//   // that are wandering through all of devices on perhaps all of the nodes in
//   // the system.  We can only deal with devices of type CacheCastNetDevice.
//   //
//   Ptr<CacheCastNetDevice> device = nd->GetObject<CacheCastNetDevice> ();
//   if (device == 0)
//     {
//       NS_LOG_INFO ("CacheCastServerHelper::EnablePcapInternal(): Device " << device << " not of type ns3::CacheCastNetDevice");
//       return;
//     }
// 
//   PcapHelper pcapHelper;
// 
//   std::string filename;
//   if (explicitFilename)
//     {
//       filename = prefix;
//     }
//   else
//     {
//       filename = pcapHelper.GetFilenameFromDevice (prefix, device);
//     }
// 
//   Ptr<PcapFileWrapper> file = pcapHelper.CreateFile (filename, std::ios::out, 
//                                                      PcapHelper::DLT_PPP);
//   pcapHelper.HookDefaultSink<CacheCastNetDevice> (device, "PromiscSniffer", file);
// }

// void 
// CacheCastServerHelper::EnableAsciiInternal (
//   Ptr<OutputStreamWrapper> stream, 
//   std::string prefix, 
//   Ptr<NetDevice> nd,
//   bool explicitFilename)
// {
//   //
//   // All of the ascii enable functions vector through here including the ones
//   // that are wandering through all of devices on perhaps all of the nodes in
//   // the system.  We can only deal with devices of type CacheCastNetDevice.
//   //
//   Ptr<CacheCastNetDevice> device = nd->GetObject<CacheCastNetDevice> ();
//   if (device == 0)
//     {
//       NS_LOG_INFO ("CacheCastServerHelper::EnableAsciiInternal(): Device " << device << 
//                    " not of type ns3::CacheCastNetDevice");
//       return;
//     }
// 
//   //
//   // Our default trace sinks are going to use packet printing, so we have to 
//   // make sure that is turned on.
//   //
//   Packet::EnablePrinting ();
// 
//   //
//   // If we are not provided an OutputStreamWrapper, we are expected to create 
//   // one using the usual trace filename conventions and do a Hook*WithoutContext
//   // since there will be one file per context and therefore the context would
//   // be redundant.
//   //
//   if (stream == 0)
//     {
//       //
//       // Set up an output stream object to deal with private ofstream copy 
//       // constructor and lifetime issues.  Let the helper decide the actual
//       // name of the file given the prefix.
//       //
//       AsciiTraceHelper asciiTraceHelper;
// 
//       std::string filename;
//       if (explicitFilename)
//         {
//           filename = prefix;
//         }
//       else
//         {
//           filename = asciiTraceHelper.GetFilenameFromDevice (prefix, device);
//         }
// 
//       Ptr<OutputStreamWrapper> theStream = asciiTraceHelper.CreateFileStream (filename);
// 
//       //
//       // The MacRx trace source provides our "r" event.
//       //
//       asciiTraceHelper.HookDefaultReceiveSinkWithoutContext<CacheCastNetDevice> (device, "MacRx", theStream);
// 
//       //
//       // The "+", '-', and 'd' events are driven by trace sources actually in the
//       // transmit queue.
//       //
//       Ptr<Queue> queue = device->GetQueue ();
//       asciiTraceHelper.HookDefaultEnqueueSinkWithoutContext<Queue> (queue, "Enqueue", theStream);
//       asciiTraceHelper.HookDefaultDropSinkWithoutContext<Queue> (queue, "Drop", theStream);
//       asciiTraceHelper.HookDefaultDequeueSinkWithoutContext<Queue> (queue, "Dequeue", theStream);
// 
//       // PhyRxDrop trace source for "d" event
//       asciiTraceHelper.HookDefaultDropSinkWithoutContext<CacheCastNetDevice> (device, "PhyRxDrop", theStream);
// 
//       return;
//     }
// 
//   //
//   // If we are provided an OutputStreamWrapper, we are expected to use it, and
//   // to providd a context.  We are free to come up with our own context if we
//   // want, and use the AsciiTraceHelper Hook*WithContext functions, but for 
//   // compatibility and simplicity, we just use Config::Connect and let it deal
//   // with the context.
//   //
//   // Note that we are going to use the default trace sinks provided by the 
//   // ascii trace helper.  There is actually no AsciiTraceHelper in sight here,
//   // but the default trace sinks are actually publicly available static 
//   // functions that are always there waiting for just such a case.
//   //
//   uint32_t nodeid = nd->GetNode ()->GetId ();
//   uint32_t deviceid = nd->GetIfIndex ();
//   std::ostringstream oss;
// 
//   oss << "/NodeList/" << nd->GetNode ()->GetId () << "/DeviceList/" << deviceid << "/$ns3::CacheCastNetDevice/MacRx";
//   Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultReceiveSinkWithContext, stream));
// 
//   oss.str ("");
//   oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::CacheCastNetDevice/TxQueue/Enqueue";
//   Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultEnqueueSinkWithContext, stream));
// 
//   oss.str ("");
//   oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::CacheCastNetDevice/TxQueue/Dequeue";
//   Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultDequeueSinkWithContext, stream));
// 
//   oss.str ("");
//   oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::CacheCastNetDevice/TxQueue/Drop";
//   Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultDropSinkWithContext, stream));
// 
//   oss.str ("");
//   oss << "/NodeList/" << nodeid << "/DeviceList/" << deviceid << "/$ns3::CacheCastNetDevice/PhyRxDrop";
//   Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultDropSinkWithContext, stream));
// }

NetDeviceContainer
CacheCastServerHelper::Install (Ptr<Node> server, Ptr<Node> node)
{
  // TODO this will be handled when CacheCastNetDevice is ready
  // Assuming a Queue and an Address is assigned to the nodeDevice
  NS_ASSERT (node != 0);
  NS_ASSERT (server != 0);

  /* Add a CacheCastPid to the server node */
  if (!server->GetObject<CacheCastPid> ()) {
    Ptr<CacheCastPid> ccp = Create<CacheCastPid> ();
    server->AggregateObject(ccp);
  }

  NetDeviceContainer container;

  /* Setup server */
  Ptr<CacheCastServerNetDevice> serverDevice = m_serverDeviceFactory.Create<CacheCastServerNetDevice> ();
  Ptr<Queue> serverQueue = m_queueFactory.Create<Queue> ();
  serverDevice->SetAddress (Mac48Address::Allocate ());
  serverDevice->SetQueue (serverQueue);
  server->AddDevice (serverDevice);

  /* Setup node */
  //TODO change to CacheCastNetDevice
  Ptr<CacheCastNetDevice> nodeDevice = m_deviceFactory.Create<CacheCastNetDevice> ();
  Ptr<Queue> nodeQueue = m_queueFactory.Create<Queue> ();
  nodeDevice->SetAddress (Mac48Address::Allocate ());
  nodeDevice->SetQueue(nodeQueue);
  node->AddDevice (nodeDevice);
  
  Ptr<CacheCastChannel> channel = m_channelFactory.Create<CacheCastChannel> ();
  serverDevice->Attach (channel);
  nodeDevice->Attach (channel);
  container.Add (serverDevice);
  container.Add (nodeDevice);

  return container;
}

NetDeviceContainer 
CacheCastServerHelper::Install (NodeContainer c)
{
  NS_ASSERT (c.GetN () == 2);
  return Install (c.Get (0), c.Get (1));
}

} // namespace ns3

