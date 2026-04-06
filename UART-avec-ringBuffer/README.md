baud rate : 115200 / 10 = 11520 how many bytes can end up in pp
if we expect a delay 1000 ms
11520 / 1000 = 11.52 bytes per ms
11.52 * 10 = 115.199 items-buffer
round up in a power of 2
128 // round up in a power of 2, for max of ~10ms of latency
