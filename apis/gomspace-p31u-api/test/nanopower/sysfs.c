/*
 * Copyright (C) 2017 Kubos Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cmocka.h>
#include <errno.h>
#include <gomspace-p31u-api.h>
#include <unistd.h>

uint8_t  last_cmd;
uint16_t last_param;

/* Returns a file descriptor or -1 on failure */
int __wrap_open(const char * filename, int flags)
{
    return mock_type(int);
}

/* Returns 0 on success and -1 on failure */
int __wrap_close(int fd)
{
    return mock_type(int);
}

/*
 * Returns 0 on success (or occasionally a positive value) and -1 on failure
 */
int __wrap_ioctl(int fd, unsigned long request, long addr, ...)
{
    /*
     * This shouldn't ever actually fail, it's just a convenient place to
     * check that we're still sending to the correct slave address
     */
    if (addr != 0x02)
    {
        fprintf(stderr, "I2C slave address is wrong!\n");
        return -1;
    }

    return 0;
}

/* Returns number of bytes "written" or -1 on failure */
ssize_t __wrap_write(int fd, const char * buf, size_t count)
{
    /* Verify that we're sending the correct command */
    uint8_t cmd = buf[0];
    check_expected(cmd);

    if (count > 4)
    {
        check_expected(buf);
    }

    if (cmd == 0x55)
    {
        /* Special dummy value for testing mismatched command in response */
        last_cmd = 0x11;
    }
    else
    {
        last_cmd = cmd;
    }

    return (ssize_t) count;
}

/* Returns number of bytes "read" or -1 on failure */
ssize_t __wrap_read(int fd, char * buf, size_t count)
{
    ssize_t len = (ssize_t) count;

    if (len < 0)
    {
        /* Only relevant when we make the read call fail */
        errno = EREMOTEIO;
        return -1;
    }

    check_expected(len);

    uint8_t * resp = (uint8_t *) mock();

    if (len > 1)
    {

        eps_resp_header * resp_hdr = (eps_resp_header *) resp;

        resp_hdr->cmd = last_cmd;

        memcpy(buf, resp, (int) len);
    }
    else
    {
        memcpy(buf, resp, 1);
    }

    return len;
}
