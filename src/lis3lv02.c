/*
 * File:   lis3lv02.c
 * Author: Santiago Dominguez Vidal
 *
 * Created on 19 de mayo de 2021, 20:30
 */

#include "lis3lv02.h"

/**
 * @brief function to get lis3lv02 device ID
 * @return accelerometer ID
 */
uint8_t lis3_getID(){
    uint8_t id;
    ClearCSSWSPI();
    WriteSWSPI(WHO_AM_I | 0x80);
    id = WriteSWSPI(0x00);
    SetCSSWSPI();
    return id;
}
/**
 * @brief function to initialize lis3lv02
 * @return 
 */
bool lis3_begin(){
    return (lis3_getID() == LIS3_ID);
}
/**
 * @brief function to set power mode, data rate and enable all axis
 * @param power
 * @param datarate
 */
void lis3_set_power_datarate(lis3lv02_power_t power, lis3lv02_datarate_t datarate){
    uint8_t wdata = 0x07;   //XYZ enabled
    switch(power){
        case LIS3LV02_POWERDOWN:
            break;
        case LIS3LV02_POWERON:
            wdata |= 0b01 << 6; break;
    }
    switch(datarate){
        case LIS3LV02_DATARATE_40HZ:
            break;
        case LIS3LV02_DATARATE_160HZ:
            wdata |= 0b01 << 4; break;
        case LIS3LV02_DATARATE_640HZ:
            wdata |= 0b10 << 4; break;
        case LIS3LV02_DATARATE_2560HZ:
            wdata |= 0b11 << 4; break;
    }
    ClearCSSWSPI();
    WriteSWSPI(CTRL_REG1 /*| 0x80*/);
    WriteSWSPI(wdata);
    SetCSSWSPI();
}
/**
 * @brief Function to select full scale, data update mode, enable interrupt,
 *        enable data-ready generation, set spi mode and select data alignment
 * @param scale
 * @param update
 * @param inte
 * @param drdy
 */
void lis3_set_scale_update_int_drdy_spimode(lis3lv02_scale_t scale, lis3lv02_block_update_t update, lis3lv02_int_enable_t inte, lis3lv02_drdy_enable_t drdy, lis3lv02_spimode_t spimode){
    uint8_t wdata = 0x01;   //16 bit representation
    switch(scale){
        case LIS3LV02_SCALE_2G:
            break;
        case LIS3LV02_SCALE_6G:
            wdata |= 0b1 << 7; break;
    }
    switch(update){
        case LIS3LV02_CONTINUOUS:
            break;
        case LIS3LV02_BLOCKED:
            wdata |= 0b1 << 6; break;
    }
    switch(inte){
        case LIS3LV02_INT_DISABLED:
            break;
        case LIS3LV02_INT_ENABLED:
            wdata |= 0b1 << 3; break;
    }
    switch(drdy){
        case LIS3LV02_DRDY_DISABLED:
            break;
        case LIS3LV02_DRDY_ENABLED:
            wdata |= 0b1 << 2; break;
    }
    switch(spimode){
        case LIS3LV02_SPI_4W:
            break;
        case LIS3LV02_SPI_3W:
            wdata |= 0b1 << 1; break;
    }
    ClearCSSWSPI();
    WriteSWSPI(CTRL_REG2);
    WriteSWSPI(wdata);
    SetCSSWSPI();
}
/**
 * @brief
 * @param clock
 * @param dirdet
 * @param freefall
 * @param data
 * @param freq
 */
void lis3_set_filter_options(lis3lv02_clock_t clock, lis3lv02_filter_enable_t dirdet, lis3lv02_filter_enable_t freefall, lis3lv02_filter_enable_t data, lis3lv02_filter_freq_t freq){
    uint8_t wdata = 0x00;
    switch(clock){
        case LIS3LV02_INTERNAL_OSC:
            break;
        case LIS3LV02_EXTERNAL_PAD:
            wdata |= 0b1 << 7; break;
    }
    switch(dirdet){
        case LIS3LV02_FILTER_BYPASSED:
            break;
        case LIS3LV02_FILTER_ENABLED:
            wdata |= 0b1 << 6; break;
    }
    switch(freefall){
        case LIS3LV02_FILTER_BYPASSED:
            break;
        case LIS3LV02_FILTER_ENABLED:
            wdata |= 0b1 << 5; break;
    }
    switch(data){
        case LIS3LV02_FILTER_BYPASSED:
            break;
        case LIS3LV02_FILTER_ENABLED:
            wdata |= 0b1 << 4; break;
    }
    switch(freq){   //f_cutoff = (0.318/HPC)*(ODRx/2)
        case LIS3LV02_FILTER_HPC_512:
            break;
        case LIS3LV02_FILTER_HPC_1024:
            wdata |= 0b01; break;
        case LIS3LV02_FILTER_HPC_2048:
            wdata |= 0b10; break;
        case LIS3LV02_FILTER_HPC_4096:
            wdata |= 0b11; break;
    }
    ClearCSSWSPI();
    WriteSWSPI(CTRL_REG3);
    WriteSWSPI(wdata);
    SetCSSWSPI();
}
/**
 * @brief Reset HP_FILTER_RESET register
 */
void lis3_reset_filter(){
    ClearCSSWSPI();
    WriteSWSPI(HP_FILTER_RESET | 0x80);
    WriteSWSPI(0x00);
    SetCSSWSPI();
}
/**
 * @brief Read STATUS_REG register content
 * @return
 */
uint8_t lis3_read_status_reg(){
    uint8_t rdata;
    ClearCSSWSPI();
    WriteSWSPI(STATUS_REG | 0x80);
    rdata = WriteSWSPI(0x00);
    SetCSSWSPI();
    return rdata;
}
/**
 * @brief
 * @return x
 */
int16_t lis3_get_acc_x(){
    uint16_t x;
    ClearCSSWSPI();
    WriteSWSPI(OUTX_H | 0x80);
    x = WriteSWSPI(0x00);
    x <<= 8;
    WriteSWSPI(OUTX_L | 0x80);
    x |= WriteSWSPI(0x00);
    SetCSSWSPI();
    return x;
}
/**
 * @brief
 * @return y
 */
int16_t lis3_get_acc_y(){
    uint16_t y;
    ClearCSSWSPI();
    WriteSWSPI(OUTY_H | 0x80);
    y = WriteSWSPI(0x00);
    y <<= 8;
    WriteSWSPI(OUTY_L | 0x80);
    y |= WriteSWSPI(0x00);
    SetCSSWSPI();
    return y;
}
/**
 * @brief
 * @return z
 */
int16_t lis3_get_acc_z(){
    uint16_t z;
    ClearCSSWSPI();
    WriteSWSPI(OUTZ_H | 0x80);
    z = WriteSWSPI(0x00);
    z <<= 8;
    WriteSWSPI(OUTZ_L | 0x80);
    z |= WriteSWSPI(0x00);
    SetCSSWSPI();
    return z;
}
/**
 * @brief
 * @return x
 */
int16_t lis3_get_acc_x16(){
    uint16_t x;
    ClearCSSWSPI();
    WriteSWSPI(OUTX_L | 0x80 | 0x40);
    x = WriteSWSPI(0x00);
    x |= (WriteSWSPI(0x00) << 8);
    SetCSSWSPI();
    return x;
}
/**
 * @brief
 * @return y
 */
int16_t lis3_get_acc_y16(){
    uint16_t y;
    ClearCSSWSPI();
    WriteSWSPI(OUTY_L | 0x80 | 0x40);
    y = WriteSWSPI(0x00);
    y |= (WriteSWSPI(0x00) << 8);
    SetCSSWSPI();
    return y;
}
/**
 * @brief
 * @return z
 */
int16_t lis3_get_acc_z16(){
    uint16_t z;
    ClearCSSWSPI();
    WriteSWSPI(OUTZ_L | 0x80 | 0x40);
    z = WriteSWSPI(0x00);
    z |= (WriteSWSPI(0x00) << 8);
    SetCSSWSPI();
    return z;
}