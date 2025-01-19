#ifndef SPI_H_INCLUDE
#define SPI_H_INCLUDE

#include <stdint.h>

/**
 * @brief SPI driver status codes.
 */
typedef enum spi_status_e {
    SPI_OK = 0,                ///< Operation successful.
    SPI_CONFIGERR_PERIPH = 1,  ///< Configuration error in peripheral.
} spi_status_t;

/**
 * @brief SPI mode configurations.
 */
typedef enum spi_mode_e {
    SPI_MODE_0 = 0, ///< Clock polarity: 0, Clock phase: 0
    SPI_MODE_1 = 1, ///< Clock polarity: 0, Clock phase: 1
    SPI_MODE_2 = 2, ///< Clock polarity: 1, Clock phase: 0
    SPI_MODE_3 = 3, ///< Clock polarity: 1, Clock phase: 1
} spi_mode_t;

/**
 * @brief SPI side configurations (master or slave).
 */
typedef enum spi_side_e {
    SPI_SIDE_SLAVE = 0,  ///< SPI operates as a slave.
    SPI_SIDE_MASTER = 1, ///< SPI operates as a master.
} spi_side_t;

/**
 * @brief Initializes the SPI peripheral.
 *
 * This driver supports mode and speed settings. On the MCU used in the KL05 
 * development board, there is only one possible combination for SPI outputs.
 *
 * @param mode SPI mode (see `spi_mode_t` for more details).
 * @param speed Desired speed in Hz. If the exact speed cannot be achieved, 
 * the driver will set the closest possible value.
 * @param side SPI communication type. If set to `SPI_SIDE_MASTER`, the MCU will 
 * act as the master. If set to `SPI_SIDE_SLAVE`, the MCU will act as the slave, 
 * using pin PTA5 as the slave select (SS) pin.
 * 
 * Hardcoded pin configuration:
 * - MISO on PTA6
 * - MOSI on PTA7
 * - SCK on PTB0
 * - SS on PTA5 (slave mode only)
 *
 * @return spi_status_t Driver status code. Returns `SPI_OK` if successful,
 * or `SPI_CONFIGERR_PERIPH` if there was an error in the configuration.
 */
spi_status_t spi_init(spi_mode_t mode, uint32_t speed, spi_side_t side);

/**
 * @brief Performs an SPI transaction as the master.
 *
 * Sends 8-bit data to the SPI device and returns the data received 
 * during the transaction.
 *
 * @param data 8-bit data to send to the device.
 * @return uint8_t Data read from the device during the transaction.
 */
uint8_t spi_master_write(uint8_t data);

/**
 * @brief Writes data to the SPI bus in slave mode.
 *
 * This function sends 8-bit data to the SPI master. The implementation 
 * should include a timeout mechanism (currently not implemented).
 *
 * @param data 8-bit data to send to the master.
 */
void spi_slave_write(uint8_t data);

/**
 * @brief Checks if new data is available in the SPI buffer.
 *
 * @return uint8_t Non-zero value if new data was received from the master.
 */
uint8_t spi_slave_receive(void);

/**
 * @brief Reads data from the SPI buffer in slave mode.
 *
 * Use `spi_slave_receive` to check if new data is available before 
 * calling this function.
 *
 * @return uint8_t Data from the SPI buffer.
 */
uint8_t spi_slave_read(void);

#endif // SPI_H_INCLUDE
