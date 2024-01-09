#include "softspi.h"

void SoftSPI_Init(void)
{

    GPIO_InitTypeDef SpiStruct;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    SpiStruct.Pin = SoftSPI_CS_Pin | SoftSPI_SCLK_Pin | SoftSPI_MOSI_Pin;
    SpiStruct.Mode = GPIO_MODE_OUTPUT_PP;
    SpiStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SoftSPI_PORT, &SpiStruct);
    __GPIO_SET_BIT(SoftSPI_PORT, GPIO_PIN_4);

    SpiStruct.Pin = SoftSPI_MISO_Pin;
    SpiStruct.Mode = GPIO_MODE_INPUT;
    SpiStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SoftSPI_PORT, &SpiStruct);
}

/**
 * @brief 以阻塞模式发送大量数据
 *
 * @param pTxData 指向传输数据缓冲区的指针
 * @param Size 要发送的数据量
 */
void SoftSPI_SendByte(uint8_t *pTxData, uint16_t Size)
{
    uint8_t i, j;
    for (i = 0; i <Size; i++)
    {
        for (j = 0; j < 8; j++)
        {
            SoftSPI_MOSI((pTxData[i]<<j) & 0x80 );
            SoftSPI_SCLK(1);
            SoftSPI_SCLK(0);
        }
    }
}
/**
 * @brief 以阻塞模式接收大量数据
 *
 * @param pRxdata 指向接收数据缓冲区的指针
 * @param Size 要接收的数据量
 */
void SoftSPI_ReceiveByte(uint8_t *pRxData, uint16_t Size)
{
    uint8_t i, j;
    for (i = 0; i < Size; i++)
    {
        for (j = 0; j < 8; j++)
        {
            SoftSPI_SCLK(1);
            pRxData[i] |= (SoftSPI_MISO<<(7-j));
            SoftSPI_SCLK(0);
        }
    }
}
/**
 * @brief 以阻塞模式发送和接收大量数据
 *
 * @param pTxData 指向传输数据缓冲区的指针
 * @param pRxData 指向接收数据缓冲区的指针
 * @param Size 要发送和接收的数据量
 */
void SoftSPI_SendReceiveByte(uint8_t *pTxData, uint8_t *pRxData, uint16_t Size)
{
    uint8_t i,j;
    for (i = 0; i < Size; i++)
    {
        pRxData[i]=0;
        for (j = 0; j < 8; j++)
        {
            SoftSPI_MOSI((pTxData[i]<<j) & 0x80);
            SoftSPI_SCLK(1);
            pRxData[i] |= (SoftSPI_MISO<<(7-j));
            SoftSPI_SCLK(0);
        }
    }
}

uint8_t SoftSPI_SendReceive(uint8_t TxData){
    uint8_t i;
    for (i = 0; i <8; i++)
    {
        SoftSPI_MOSI(TxData & 0x80);
        SoftSPI_SCLK(1);
        TxData<<=1;
        TxData |=SoftSPI_MISO;
        SoftSPI_SCLK(0);
    }
    return TxData;
}
