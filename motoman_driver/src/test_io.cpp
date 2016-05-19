
#include "motoman_driver/io_ctrl.h"

#include "simple_message/simple_message.h"
#include "simple_message/smpl_msg_connection.h"
#include "simple_message/socket/tcp_client.h"

#include <ros/ros.h>

#include <sysexits.h>


using industrial::shared_types::shared_int;
using industrial::tcp_client::TcpClient;
using motoman::io_ctrl::MotomanIoCtrl;



int main(int argc, char** argv)
{
  const int FS100_motion_port = 50240;  // FS100 uses a "non-standard" port to comply with MotoPlus guidelines
  const int TEST_IO_POINT = 27010;

  // initialize node
  ros::init(argc, argv, "motoman_io_test");
  ros::NodeHandle nh;

  // override IP/port with ROS params, if available
  std::string ip;
  int port;
  ros::param::param<std::string>("robot_ip_address", ip, "");
  ros::param::param<int>("~port", port, FS100_motion_port);

  // check for valid parameter values
  if (ip.empty())
  {
    ROS_ERROR("No valid robot IP address found.  Please set ROS 'robot_ip_address' param");
    return EX_USAGE;
  }
  if (port <= 0)
  {
    ROS_ERROR("No valid robot IP port found.  Please set ROS '~port' param");
    return EX_USAGE;
  }

  char* ip_addr = strdup(ip.c_str());
  ROS_INFO("IO Tester connecting to IP address: '%s:%d'", ip_addr, port);

  // create a connection
  TcpClient tcp_conx;
  tcp_conx.init(ip_addr, port);
  free(ip_addr);
  tcp_conx.makeConnect();

  ROS_INFO("Connected.");


  // create the 'IO controller' instance
  MotomanIoCtrl io_ctrl;
  io_ctrl.init(&tcp_conx);


  // test
  shared_int io_val = -1;

#if 1
  if (!io_ctrl.readSingleIO(TEST_IO_POINT, io_val))
  {
    ROS_ERROR("Reading element %d failed, exiting", TEST_IO_POINT);
    return EX_IOERR;
  }
  ROS_INFO("Element %d value: %d", TEST_IO_POINT, io_val);
#endif


#if 0
  ROS_INFO("Starting toggle in 5 seconds ..");

  ros::Duration(5.0).sleep();

  ROS_INFO("toggling ..");

  // toggle an IO at 1 second intervals
  while (ros::ok())
  {
    ros::Duration(1.0).sleep();

    io_val = (io_val + 1) & 0x1;
    io_ctrl.writeSingleIO(TEST_IO_POINT, io_val);
  }
#endif


  ros::Duration(2.0).sleep();
  ROS_INFO("stop");

  return EX_OK;
}
