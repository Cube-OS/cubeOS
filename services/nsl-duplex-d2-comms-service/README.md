# NSL Duplex Communications Service

This communications service provides communications functionality over the NSL
Duplex radio.

## Running

This service expects a service configuration file in either the default location
or to be passed in at runtime like so `cargo run -- -c config.toml`.

The service expects the following sections and settings to be present:

```toml
# Service specific configuration
[nsl-duplex-comms-service]
# Serial bus to use for talking with the radio
bus = "/dev/ttyUSB0"
# Specifies how frequently the service sends ping packets when the downlink queue is empty (seconds)
ping_freq = 10

# GraphQL configuration
[nsl-duplex-comms-service.addr]
# IP to bind GraphQL server to
ip = "127.0.0.1"
# Port to listen on for GraphQL queries
port = 8140

# Communications service configuration
[nsl-duplex-comms-service.comms]
# Maximum number of concurrent message handlers
max_num_handlers = 10
# Ports to listen for local traffic on
downlink_ports = [14011]
#  Timeout when listening for packet response (milliseconds)
timeout = 1
# IP to bind Communications service listener to
ip = "0.0.0.0"
```

When the service has started correctly it will display output like so:

```
2019-01-18T13:00:32.512854973-06:00 INFO  nsl_dupex_d2_comms_service - NSL Duplex Communications Service starting on /dev/ttyUSB0
2019-01-18T13:00:32.513053752-06:00 INFO comms_service::service - Communication service started
2019-01-18T13:00:32.513855-06:00 INFO cubeos_service::service - Listening on: 127.0.0.1:8080
```
