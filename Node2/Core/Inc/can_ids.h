#ifndef CAN_IDS_H
#define CAN_IDS_H

#include <stdint.h>

/* Bus: CAN1, 500 kbps, standard 11-bit IDs */

/* Sensor frame: Node A -> everyone, every ~60 ms
 *   byte 0-1 : distance in cm, little endian (0xFFFF = no echo)
 *   byte 2   : pot / accelerator 0..100
 */
#define CAN_ID_SENSOR         0x100U
#define CAN_DLC_SENSOR        3U
#define CAN_DIST_NO_ECHO      0xFFFFU

/* Node B declares sensor data stale after this long without a frame */
#define CAN_SENSOR_STALE_MS   300U

static inline void can_pack_sensor(uint8_t d[CAN_DLC_SENSOR], uint16_t dist, uint8_t pot)
{
    d[0] = (uint8_t)(dist & 0xFFU);
    d[1] = (uint8_t)(dist >> 8);
    d[2] = pot;
}

static inline void can_unpack_sensor(const uint8_t *d, uint16_t *dist, uint8_t *pot)
{
    *dist = (uint16_t)(d[0] | ((uint16_t)d[1] << 8));
    *pot  = d[2];
}

#endif /* CAN_IDS_H */