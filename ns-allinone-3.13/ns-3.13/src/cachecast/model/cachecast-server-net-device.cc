#include "ns3/log.h"
#include "cachecast-server-net-device.h"
//#include "cachecast-header.h"

NS_LOG_COMPONENT_DEFINE ("CacheCastServerNetDevice");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CacheCastServerNetDevice);

CacheCastServerNetDevice::CacheCastServerNetDevice ()
  : PointToPointNetDevice()
//   : m_payloadId (0),
//     m_payloadSize (0),
//     m_originalSize (0)
{

}

} // namespace ns3

