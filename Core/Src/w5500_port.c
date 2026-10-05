#include "w5500_port.h"

#include "wizchip_conf.h"
#include "w5500.h"

extern SPI_HandleTypeDef hspi1;

void W5500_Select(void)
{
    HAL_GPIO_WritePin(W5500_CS_GPIO_Port,
                      W5500_CS_Pin,
                      GPIO_PIN_RESET);
}

void W5500_Unselect(void)
{
    HAL_GPIO_WritePin(W5500_CS_GPIO_Port,
                      W5500_CS_Pin,
                      GPIO_PIN_SET);
}

void W5500_Reset(void)
{
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port,
                      W5500_RST_Pin,
                      GPIO_PIN_RESET);

    HAL_Delay(10);

    HAL_GPIO_WritePin(W5500_RST_GPIO_Port,
                      W5500_RST_Pin,
                      GPIO_PIN_SET);

    HAL_Delay(100);
}

void W5500_WriteByte(uint8_t byte)
{
    HAL_SPI_Transmit(&hspi1, &byte, 1, HAL_MAX_DELAY);
}

uint8_t W5500_ReadByte(void)
{
    uint8_t tx = 0xFF;
    uint8_t rx = 0;

    HAL_SPI_TransmitReceive(&hspi1,
                            &tx,
                            &rx,
                            1,
                            HAL_MAX_DELAY);

    return rx;
}

void W5500_Init(void)
{
    /* Reset W5500 */
    W5500_Reset();

    /* Register CS callback */
    reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);

    /* Register SPI callback */
    reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);
}
