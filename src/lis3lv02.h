/* 
 * File:   lis3lv02.h
 * Author: Santiago Dominguez Vidal
 * Comments: simple lis3lv02 (SPI) library for basic usage
 * Revision history: 0.7 - 11/08/2021
 */

#include <stdint.h>
#include <stdbool.h>
#include <sw_spi.h>

#ifndef LIS3LV02_H
#define	LIS3LV02_H

#define WHO_AM_I        0x0F
#define OFFSET_X        0x16
#define OFFSET_Y        0x17
#define OFFSET_Z        0x18
#define GAIN_X          0x19
#define GAIN_Y          0x1A
#define GAIN_Z          0x1B
#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define HP_FILTER_RESET 0x23
#define STATUS_REG      0x27
#define OUTX_L          0x28
#define OUTX_H          0x29
#define OUTY_L          0x2A
#define OUTY_H          0x2B
#define OUTZ_L          0x2C
#define OUTZ_H          0x2D
#define FF_WU_CFG       0x30
#define FF_WU_SRC       0x31
#define FF_WU_ACK       0x32
#define FF_WU_THS_L     0x34
#define FF_WU_THS_H     0x35
#define FF_WU_DURATION  0x36
#define DD_CFG          0x38
#define DD_SRC          0x39
#define DD_ACK          0x3A
#define DD_THSI_L       0x3C
#define DD_THSI_H       0x3D
#define DD_THSE_L       0x3E
#define DD_THSE_H       0x3F

#define LIS3_ID  0x3A
#define BIT7 (0b1<<7)
#define BIT6 (0b1<<6)
#define BIT5 (0b1<<5)
#define BIT4 (0b1<<4)
#define BIT3 (0b1<<3)
#define BIT2 (0b1<<2)
#define BIT1 (0b1<<1)
#define BIT0 (0b1<<0)

/**
 * @brief Power setting
 */
typedef enum
{
    LIS3LV02_POWERDOWN,
    LIS3LV02_POWERON
} lis3lv02_power_t;

/**
 * @brief Output data rate setting
 */
typedef enum
{
    LIS3LV02_DATARATE_40HZ,
    LIS3LV02_DATARATE_160HZ,
    LIS3LV02_DATARATE_640HZ,
    LIS3LV02_DATARATE_2560HZ
} lis3lv02_datarate_t;

/**
 * @brief Accelerometer scale setting
 */
typedef enum
{
    LIS3LV02_SCALE_2G,
    LIS3LV02_SCALE_6G
} lis3lv02_scale_t;

/**
 * @brief Update data mode setting
 */
typedef enum
{
    LIS3LV02_CONTINUOUS,
    LIS3LV02_BLOCKED
}lis3lv02_block_update_t;

/**
 * @brief Interrupt enable/disable
 */
typedef enum
{
    LIS3LV02_INT_DISABLED,
    LIS3LV02_INT_ENABLED
}lis3lv02_int_enable_t;

/**
 * @brief Data-ready generation enable/disable
 */
typedef enum
{
    LIS3LV02_DRDY_DISABLED,
    LIS3LV02_DRDY_ENABLED
}lis3lv02_drdy_enable_t;

/**
 * @brief SPI mode selection
 */
typedef enum
{
    LIS3LV02_SPI_4W,
    LIS3LV02_SPI_3W
}lis3lv02_spimode_t;

/**
 * @brief Data alignment selection
 */
typedef enum
{
    LIS3LV02_DATA_12R,
    LIS3LV02_DATA_16L
}lis3lv02_alignment_t;

/**
 * @brief Fiter clock source selection
 */
typedef enum
{
    LIS3LV02_INTERNAL_OSC,
    LIS3LV02_EXTERNAL_PAD
}lis3lv02_clock_t;

/**
 * @brief Filter enable/disable
 */
typedef enum
{
    LIS3LV02_FILTER_BYPASSED,
    LIS3LV02_FILTER_ENABLED
}lis3lv02_filter_enable_t;

/**
 * @brief Filter frequency setting
 * f_cutoff = (0.318/HPC)*(ODRx/2)
 */
typedef enum
{
    LIS3LV02_FILTER_HPC_512,
    LIS3LV02_FILTER_HPC_1024,
    LIS3LV02_FILTER_HPC_2048,
    LIS3LV02_FILTER_HPC_4096
} lis3lv02_filter_freq_t;

uint8_t lis3_getID();
bool lis3_begin();

void lis3_set_power_datarate(lis3lv02_power_t power, lis3lv02_datarate_t datarate);
#define lis3_set_ctrl_reg1 lis3_set_power_datarate

void lis3_set_scale_update_int_drdy_spimode_alignment(lis3lv02_scale_t scale, lis3lv02_block_update_t update, lis3lv02_int_enable_t inte, lis3lv02_drdy_enable_t drdy, lis3lv02_spimode_t spimode, lis3lv02_alignment_t alignment);
#define lis3_set_ctrl_reg2 lis3_set_scale_update_int_drdy_spimode_alignment

void lis3_set_filter_options(lis3lv02_clock_t clock, lis3lv02_filter_enable_t dirdet, lis3lv02_filter_enable_t freefall, lis3lv02_filter_enable_t data, lis3lv02_filter_freq_t freq);
#define lis3_set_ctrl_reg3 lis3_set_filter_options

void lis3_reset_filter();

uint8_t lis3_read_status_reg();

int8_t lis3_get_acc_x_h();
uint8_t lis3_get_acc_x_l();

int8_t lis3_get_acc_y_h();
uint8_t lis3_get_acc_y_l();

int8_t lis3_get_acc_z_h();
uint8_t lis3_get_acc_z_l();

//16 bit alignment functions
int16_t lis3_get_acc_x();
int16_t lis3_get_acc_y();
int16_t lis3_get_acc_z();

int16_t lis3_get_acc_x16();
int16_t lis3_get_acc_y16();
int16_t lis3_get_acc_z16();
#endif

