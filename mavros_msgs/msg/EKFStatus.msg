# Current ardupilot estimator state
#
# https://mavlink.io/en/messages/ardupilotmega.html#EKF_STATUS_REPORT

std_msgs/Header header

float32 vel_ratio
float32 pos_horiz_ratio
float32 pos_vert_ratio
float32 mag_ratio
float32 hagl_ratio
float32 tas_ratio
float32 pos_horiz_accuracy
float32 pos_vert_accuracy