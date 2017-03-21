/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2016, Delft Robotics Institute
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of the Delft Robotics Institute, nor the names
 *    of its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \author G.A. vd. Hoorn (TU Delft Robotics Institute)
 */

#include "motoman_driver/io_ctrl.h"
#include "motoman_driver/simple_message/messages/motoman_read_single_io_message.h"
#include "motoman_driver/simple_message/messages/motoman_read_single_io_reply_message.h"
#include "motoman_driver/simple_message/messages/motoman_write_single_io_message.h"
#include "motoman_driver/simple_message/messages/motoman_write_single_io_reply_message.h"
#include "motoman_driver/simple_message/messages/motoman_read_group_io_message.h"
#include "motoman_driver/simple_message/messages/motoman_read_group_io_reply_message.h"
#include "motoman_driver/simple_message/messages/motoman_write_group_io_message.h"
#include "motoman_driver/simple_message/messages/motoman_write_group_io_reply_message.h"
#include "ros/ros.h"
#include "simple_message/simple_message.h"
#include <string>


namespace ReadSingleIOReplyResults = motoman::simple_message::io_ctrl_reply::ReadSingleIOReplyResults;
namespace WriteSingleIOReplyResults = motoman::simple_message::io_ctrl_reply::WriteSingleIOReplyResults;

using motoman::simple_message::io_ctrl::ReadSingleIO;
using motoman::simple_message::io_ctrl_message::ReadSingleIOMessage;
using motoman::simple_message::io_ctrl_reply_message::ReadSingleIOReplyMessage;
using motoman::simple_message::io_ctrl::WriteSingleIO;
using motoman::simple_message::io_ctrl_message::WriteSingleIOMessage;
using motoman::simple_message::io_ctrl_reply_message::WriteSingleIOReplyMessage;

namespace ReadGroupIOReplyResults = motoman::simple_message::io_ctrl_reply::ReadGroupIOReplyResults;
namespace WriteGroupIOReplyResults = motoman::simple_message::io_ctrl_reply::WriteGroupIOReplyResults;

using motoman::simple_message::io_ctrl::ReadGroupIO;
using motoman::simple_message::io_ctrl_message::ReadGroupIOMessage;
using motoman::simple_message::io_ctrl_reply_message::ReadGroupIOReplyMessage;
using motoman::simple_message::io_ctrl::WriteGroupIO;
using motoman::simple_message::io_ctrl_message::WriteGroupIOMessage;
using motoman::simple_message::io_ctrl_reply_message::WriteGroupIOReplyMessage;

using industrial::simple_message::SimpleMessage;
using industrial::shared_types::shared_int;


namespace motoman
{
namespace io_ctrl
{

bool MotomanIoCtrl::init(SmplMsgConnection* connection)
{
  connection_ = connection;
  return true;
}

bool MotomanIoCtrl::readSingleIO(shared_int address, shared_int &value)
{
  ReadSingleIOReply reply;

  if (!sendAndReceive(address, reply))
  {
    ROS_ERROR("Failed to send READ_SINGLE_IO command");
    return false;
  }

  value = reply.getValue();

  return (reply.getResultCode() == ReadSingleIOReplyResults::SUCCESS);
}

bool MotomanIoCtrl::writeSingleIO(shared_int address, shared_int value)
{
  WriteSingleIOReply reply;

  if (!sendAndReceive(address, value, reply))
  {
    ROS_ERROR("Failed to send WRITE_SINGLE_IO command");
    return false;
  }

  return (reply.getResultCode() == WriteSingleIOReplyResults::SUCCESS);
}

bool MotomanIoCtrl::readGroupIO(shared_int address, shared_int &value)
{
  ReadGroupIOReply reply;

  if (!sendAndReceive(address, reply))
  {
    ROS_ERROR("Failed to send READ_GROUP_IO command");
    return false;
  }

  value = reply.getValue();

  return (reply.getResultCode() == ReadGroupIOReplyResults::SUCCESS);
}

bool MotomanIoCtrl::writeGroupIO(shared_int address, shared_int value)
{
  WriteGroupIOReply reply;

  if (!sendAndReceive(address, value, reply))
  {
    ROS_ERROR("Failed to send WRITE_GROUP_IO command");
    return false;
  }

  return (reply.getResultCode() == WriteGroupIOReplyResults::SUCCESS);
}

  
bool MotomanIoCtrl::sendAndReceive(shared_int address, ReadSingleIOReply &reply)
{
  SimpleMessage req, res;
  ReadSingleIO data;
  ReadSingleIOMessage read_io_msg;
  ReadSingleIOReplyMessage read_io_reply;

  data.init(address);
  read_io_msg.init(data);
  read_io_msg.toRequest(req);

  if (!this->connection_->sendAndReceiveMsg(req, res))
  {
    ROS_ERROR("Failed to send ReadSingleIO message");
    return false;
  }

  read_io_reply.init(res);
  reply.copyFrom(read_io_reply.reply_);

  return true;
}

bool MotomanIoCtrl::sendAndReceive(shared_int address, shared_int value, WriteSingleIOReply &reply)
{
  SimpleMessage req, res;
  WriteSingleIO data;
  WriteSingleIOMessage write_io_msg;
  WriteSingleIOReplyMessage write_io_reply;

  data.init(address, value);
  write_io_msg.init(data);
  write_io_msg.toRequest(req);

  if (!this->connection_->sendAndReceiveMsg(req, res))
  {
    ROS_ERROR("Failed to send WriteSingleIO message");
    return false;
  }

  write_io_reply.init(res);
  reply.copyFrom(write_io_reply.reply_);

  return true;
}

bool MotomanIoCtrl::sendAndReceive(shared_int address, ReadGroupIOReply &reply)
{
  SimpleMessage req, res;
  ReadGroupIO data;
  ReadGroupIOMessage read_io_msg;
  ReadGroupIOReplyMessage read_io_reply;

  data.init(address);
  read_io_msg.init(data);
  read_io_msg.toRequest(req);

  if (!this->connection_->sendAndReceiveMsg(req, res))
  {
    ROS_ERROR("Failed to send ReadGroupIO message");
    return false;
  }

  read_io_reply.init(res);
  reply.copyFrom(read_io_reply.reply_);

  return true;
}

bool MotomanIoCtrl::sendAndReceive(shared_int address, shared_int value, WriteGroupIOReply &reply)
{
  SimpleMessage req, res;
  WriteGroupIO data;
  WriteGroupIOMessage write_io_msg;
  WriteGroupIOReplyMessage write_io_reply;

  data.init(address, value);
  write_io_msg.init(data);
  write_io_msg.toRequest(req);

  if (!this->connection_->sendAndReceiveMsg(req, res))
  {
    ROS_ERROR("Failed to send WriteGroupIO message");
    return false;
  }

  write_io_reply.init(res);
  reply.copyFrom(write_io_reply.reply_);

  return true;
}

  
} // io_ctrl

} // motoman
