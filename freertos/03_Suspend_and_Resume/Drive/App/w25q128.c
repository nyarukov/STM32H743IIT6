#include "w25q128.h"
/**
 * @brief 初始化SPI
 */
void W25Q128_Init(void)
{
    SoftSPI_Init();
}
/**
 * @brief 读取ID
 * @return DID编号
 */
void W25Q128_ReadID(uint8_t *MID, uint16_t *DID)
{
    uint8_t cmd[1];
    uint8_t ID[3];
    cmd[0] = CMD_JEDEC_ID;
    SoftSPI_CS(0);
    SoftSPI_SendByte(cmd,1);
    SoftSPI_ReceiveByte(ID, 3);
    SoftSPI_CS(1);
    *MID = ID[0];
    *DID = (ID[1] << 8) | ID[2];
}
/**
 * @brief 复位
 */
void W25Q128_RESET_DEVICE(void)
{
    uint8_t cmd[1];
    cmd[0] = CMD_RESET_DEVICE;
    SoftSPI_CS(0);
    SoftSPI_SendByte(cmd, 1);
    SoftSPI_CS(1);
}
/**
 * @brief 写使能
 */
void W25Q128_Write_ENABLE(void)
{
    uint8_t cmd[1];
    cmd[0] = CMD_WRITE_ENABLE;
    SoftSPI_CS(0);
    SoftSPI_SendByte(cmd, 1);
    SoftSPI_CS(1);
}
/**
 * @brief 写禁止
 */
void W25Q128_Write_DISABLE(void)
{
    uint8_t cmd[1];
    cmd[0] = CMD_WRITE_DISABLE;
    SoftSPI_CS(0);
    SoftSPI_SendByte(cmd, 1);
    SoftSPI_CS(1);
}
/**
 * @brief 读状态
 */
void W25Q128_Start(void)
{
    uint8_t cmd[2]={0};
    uint8_t start[2]={0};
    cmd[0] = CMD_READ_STATUS_REGISTER_1;
    do
    {
        SoftSPI_CS(0);
        SoftSPI_SendReceiveByte(cmd,start,2);
        SoftSPI_CS(1);
    } while ((start[1] & 0x1) == 0x1);
}
/**
 * @brief 擦除扇区
 * @param Sector:扇区编号
 */
void W25Q128_SectorErase(uint32_t Addr)
{
    uint8_t cmd[4];
    cmd[0] = CMD_SECTOR_ERASE_4KB;
    cmd[1] = ADDRESS_23_16(Addr * 4096);
    cmd[2] = ADDRESS_15_8(Addr * 4096);
    cmd[3] = ADDRESS_7_0(Addr * 4096);

    W25Q128_Start();
    W25Q128_Write_ENABLE();
    SoftSPI_CS(0);
    SoftSPI_SendByte(cmd, 4);
    SoftSPI_CS(1);
}
/**
 * @brief 全擦除
 */
void W25Q128_ChipErase(void)
{
    uint8_t cmd[1];
    cmd[0] = CMD_CHIP_ERASE;

    W25Q128_Start();
    W25Q128_Write_ENABLE();
    SoftSPI_CS(0);
    SoftSPI_SendByte(cmd, 1);
    SoftSPI_CS(1);
}
/**
 * @brief 写数据
 * @param Addr:页地址
 * @param Txdata:指向数据缓冲区的指针
 * @param length:要发送的数据量
 */
void W25Q128_Page(uint32_t Addr, uint8_t *Txdata, uint16_t length)
{
    uint8_t cmd[4];
    cmd[0] = CMD_PAGE_PROGRAM;
    cmd[1] = ADDRESS_23_16(Addr * 256);
    cmd[2] = ADDRESS_15_8(Addr * 256);
    cmd[3] = ADDRESS_7_0(Addr * 256);

    W25Q128_Start();
    W25Q128_Write_ENABLE();
    SoftSPI_CS(0);
    SoftSPI_SendByte(cmd, 4);
    SoftSPI_SendByte(Txdata, length);
    SoftSPI_CS(1);
}
/**
 * @brief 读数据
 * @param Addr:地址
 * @param Txdata:指向数据缓冲区的指针
 * @param length:要接受的数据量
 */
void W25Q128_ReadData(uint32_t Addr, uint8_t *Rxdata, uint16_t length)
{
    uint8_t cmd[4];
    cmd[0] = CMD_READ_DATA;
    cmd[1] = ADDRESS_23_16(Addr);
    cmd[2] = ADDRESS_15_8(Addr);
    cmd[3] = ADDRESS_7_0(Addr);

    W25Q128_Start();
    W25Q128_Write_ENABLE();
    SoftSPI_CS(0);
    SoftSPI_SendByte(cmd, 4);

    SoftSPI_ReceiveByte(Rxdata, length);
    SoftSPI_CS(1);
}
