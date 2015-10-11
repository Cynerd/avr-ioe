This example shows simple SPI communication. It uses two MCUs. One is configured
as master. Other is configured as slave. Master has button connected to its input
and slave has output led. Button status is mirrored by slave led.

Connection
----------
Both MCUs needs basic power connections and crystal.
Except of that, they need following other connections.

| Mater pin | Slave pin | Other connections | Description          |
|-----------|-----------|-------------------|----------------------|
| PB1       |           | Led               | Indication of button |
|           | PB1       | Led               | Receive led          |
| PB2       | PB2       |                   | SS                   |
| PB3       | PB3       |                   | MOSI                 |
| PB4       | PB4       |                   | MISO                 |
| PB5       | PB5       |                   | SCL                  |
| PC1       |           | Pull down button  | Input button         |
