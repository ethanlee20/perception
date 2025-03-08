struct data_s {
    /* ToF */
    unt32_t Timestamp; // time that the data point was gathered
    uint16_t tof_distance; // distance of the data point from tof sensor

    /* encoder data */
    float servo_angle; // reglative angle 

    /* IMU data*/

};