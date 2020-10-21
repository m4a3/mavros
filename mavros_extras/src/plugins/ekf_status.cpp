/**
 * @brief EKF Status plugin
 * @file ekf_status.cpp
 * @author Charlie Burge <charlieburge@yahoo.com>
 *
 * @addtogroup plugin
 * @{
 */
/*
 * Copyright 2020 Charlie Burge.
 *
 * This file is part of the mavros package and subject to the license terms
 * in the top-level LICENSE file of the mavros repository.
 * https://github.com/mavlink/mavros/tree/master/LICENSE.md
 */
#include <mavros/mavros_plugin.h>

#include <mavros_msgs/EKFStatus.h>

namespace mavros {
namespace extra_plugins {
/**
 * @brief EKF Status plugin
 *
 * 1. Publish the EKF innovations from FCU to ROS
 */
class EkfStatusPlugin : public plugin::PluginBase {
public:
	EkfStatusPlugin() : PluginBase(),
		ekf_status_nh("~ekf_status")
	{ }

	void initialize(UAS &uas_) override
	{
		PluginBase::initialize(uas_);
		ekf_status_pub_ = ekf_status_nh.advertise<mavros_msgs::EKFStatus>("ekf_status", 1);
	}

	Subscriptions get_subscriptions() override
	{
		return {
			       make_handler( &EkfStatusPlugin::handle_ekf_status_msg )
		};
	}

private:
	ros::NodeHandle ekf_status_nh;

	ros::Publisher ekf_status_pub_;
	mavros_msgs::EKFStatus ekf_status_;


	/* MAvlink msg handlers */
	/**
	 * @brief Publish EKF_STATUS message (MAvlink ArduPilot mega) received from FCU.
	 * The message is already decoded by Mavlink, we only need to convert to ROS.
	 * Details and units: https://mavlink.io/en/messages/ardupilotmega.html#EKF_STATUS_REPORT
	 */
    void handle_ekf_status_msg(const mavlink::mavlink_message_t *msg, mavlink::ardupilotmega::msg::EKF_STATUS_REPORT &status)
	{
		ekf_status_->header.stamp = ros::Time::now();

		ekf_status_->velocity_variance = status.velocity_variance
		ekf_status_->pos_horiz_variance = status.pos_horiz_variance
		ekf_status_->pos_vert_variance = status.pos_vert_variance
		ekf_status_->compass_variance = status.compass_variance
		ekf_status_->terrain_alt_variance = status.terrain_alt_variance
		ekf_status_->airspeed_variance = status.airspeed_variance

		ekf_status_pub_.publish(ekf_status_);
	}
};
}	// namespace extra_plugins
}	// namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::extra_plugins::EkfStatusPlugin, mavros::plugin::PluginBase)
