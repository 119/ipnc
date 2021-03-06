/** ===========================================================================
 * @file serial_config.c
 *
 * @path $(IPNCPATH)\sys_adm\system_server
 *
 * @desc
 * .
 * Copyright (c) Appro Photoelectron Inc.  2009
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 *
 * =========================================================================== */
#include "serial_config.h"

int opentty(int ch)
{
    int fd;
    char devname[30];
    bzero(devname, 30);
    if (ch == 0 || ch == 1)
    {
        sprintf(devname, "/dev/tts/%d", ch);
    }
    else if (ch == 2 || ch == 3)
    {
        sprintf(devname, "/dev/ttyXX%d", ch - 2);
    }
    fd = open(devname, O_RDWR | O_NOCTTY | O_NDELAY);
    if ( - 1 == fd)
    {
        /* 不能打开串口一*/
        perror(" 提示错误！");
        return  - 1;
    }
    return fd;
}

int set_data_stop_parity(int fd, int databits, int stopbits, int parity)
{
    struct termios options;
    if (tcgetattr(fd, &options) != 0)
    {
        perror("set_data_stop_parity");
        return  - 1;
    } options.c_cflag &= ~CSIZE;
    switch (databits)
    {
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag |= CS8;
            break;
        default:
            fprintf(stderr, "Unsupported data size\n");
            return  - 1;
    }
    switch (parity)
    {
        case 0:
            options.c_cflag &= ~PARENB; /* Clear parity enable */
            options.c_iflag &= ~INPCK; /* Enable parity checking */
            break;
        case 1:
            //odd
            options.c_cflag |= (PARODD | PARENB);
            options.c_iflag |= INPCK; /* Disnable parity checking */
            break;
        case 2:
            //even
            options.c_cflag |= PARENB; /* Enable parity */
            options.c_cflag &= ~PARODD;
            options.c_iflag |= INPCK; /* Disnable parity checking */
            break;
        case 3:
             /*as no parity*/ // space parity
            options.c_cflag |= (PARENB | CMSPAR);
            break;
        case 4:
             /*as no parity*/ // mask parity
            options.c_cflag |= (PARENB | PARODD | CMSPAR);
            break;
        default:
            fprintf(stderr, "Unsupported parity\n");
            return  - 1;
    }

    switch (stopbits)
    {
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;
        case 2:
            options.c_cflag |= CSTOPB;
            break;
        default:
            fprintf(stderr, "Unsupported stop bits\n");
            return  - 1;
    }
    /* Set input parity option */
    if (parity != 0)
    {
        options.c_iflag |= INPCK;
    }
    options.c_cc[VTIME] = 150; // 15 seconds
    options.c_cc[VMIN] = 0;

    tcflush(fd, TCIFLUSH); /* Update the options and do it NOW */
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("SetupSerial 3");
        return  - 1;
    }
    return 0;
}

/**
 *@brief  设置串口通信速率
 *@param  fd     类型 int  打开串口的文件句柄
 *@param  speed  类型 int  串口速度
 *@return  void
 */
int speed_arr[] =
{
    B38400, B19200, B115200, B9600, B4800, B2400, B1200, B300,
};
int name_arr[] =
{
    38400, 19200, 115200, 9600, 4800, 2400, 1200, 300,
};
void set_speed(int fd, int speed)
{
    int i;
    int status;
    struct termios Opt;
    tcgetattr(fd, &Opt);
    for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++)
    {
        if (speed == name_arr[i])
        {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);
            if (status != 0)
            {
                perror("tcsetattr fd");
                return ;
            } tcflush(fd, TCIOFLUSH);
        }
    }
}


int vl_SetSpeed(int rs232ch, int speed)
{
    int fd = opentty(rs232ch);
    if (fd ==  - 1)
    {
        perror("open serial failed!\n");
        close(fd);
        return  - 1;
    }
    set_speed(fd, speed);
    close(fd);
    return 0;
}

int vl_Set_data_stop_parity(int rs232ch, int databit, int stopbit, int parity)
{
    int fd = opentty(rs232ch);
    if (fd ==  - 1)
    {
        perror("open serial failed!\n");
        close(fd);
        return  - 1;
    }
    if (set_data_stop_parity(fd, databit, stopbit, parity) ==  - 1)
    {
        perror("vl_Set_data_stop_parity");
        close(fd);
        return  - 1;
    }
    close(fd);
    return 0;
}

int set_databit(int fd, int databits)
{
    struct termios options;
    if (tcgetattr(fd, &options) != 0)
    {
        perror("SetupSerial 1");
        return  - 1;
    } options.c_cflag &= ~CSIZE;
    switch (databits) /*设置数据位数*/
    {
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag |= CS8;
            break;
        default:
            fprintf(stderr, "Unsupported data size\n");
            return  - 1;
    }
    /* Set input parity option */
    tcflush(fd, TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("set_databit error!\n");
        return  - 1;
    }
    return 0;
}

int set_parity(int fd, int parity)
{
    struct termios options;
    if (tcgetattr(fd, &options) != 0)
    {
        perror("set_parity error");
        return  - 1;
    } options.c_cflag &= ~CSIZE;

    switch (parity)
    {
        case 0:
             /*as no parity*/
            options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            break;
        case 1:
            options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
            options.c_iflag |= INPCK; /* Disnable parity checking */
            break;
        case 2:
            options.c_cflag |= PARENB; /* Enable parity */
            options.c_cflag &= ~PARODD; /* 转换为偶效验*/
            options.c_iflag |= INPCK; /* Disnable parity checking */
            break;
        case 3:
             /*as no parity*/
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            break;
        default:
            fprintf(stderr, "Unsupported parity\n");
            return  - 1;
    }
    /* Set input parity option */
    if (parity != 0)
    {
        options.c_iflag |= (INPCK | ISTRIP);
    }
    tcflush(fd, TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("set_parity error!\n");
        return  - 1;
    }
    return 0;

}

int set_stopbit(int fd, int stopbits)
{
    struct termios options;
    if (tcgetattr(fd, &options) != 0)
    {
        perror("set_parity error");
        return  - 1;
    } options.c_cflag &= ~CSIZE;

    /* 设置停止位*/
    switch (stopbits)
    {
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;
        case 2:
            options.c_cflag |= CSTOPB;
            break;
        default:
            fprintf(stderr, "Unsupported stop bits\n");
            return  - 1;
    }

    tcflush(fd, TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("set_stopbit error!\n");
        return  - 1;
    }
    return 0;
}

int set_streamctrl(int fd, int streamctrl)
{
    struct termios options;
    if (tcgetattr(fd, &options) != 0)
    {
        perror("SetupSerial 1");
        return  - 1;
    } options.c_cflag &= ~CSIZE;
    switch (streamctrl) /*设置数据位数*/
    {
        case 0:
            //null
            options.c_cflag &= ~CRTSCTS;
            options.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        case 1:
            //hard streamctrl
            options.c_cflag |= CRTSCTS;
            break;
        case 2:
            //soft streamctrl
            options.c_iflag &= ~(IXON | IXOFF | IXANY);
            break;
        default:
            fprintf(stderr, "Unsupported data size\n");
            return  - 1;
    }
    /* Set input parity option */
    tcflush(fd, TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("set_streamctrl error!\n");
        return  - 1;
    }
    return 0;
}

int vl_SetDatabit(int rs232ch, int databit)
{
    int fd = opentty(rs232ch);
    if (fd ==  - 1)
    {
        perror("open serial failed!\n");
        close(fd);
        return  - 1;
    }
    if (set_databit(fd, databit) ==  - 1)
    {
        perror("vl_SetDatabit failed!\n");
        close(fd);
        return  - 1;
    }
    close(fd);
    return 0;
}

int vl_SetStopbit(int rs232ch, int stopbit)
{
    int fd = opentty(rs232ch);
    if (fd ==  - 1)
    {
        perror("open serial failed!\n");
        close(fd);
        return  - 1;
    }
    if (set_stopbit(fd, stopbit) ==  - 1)
    {
        perror("vl_SetStopbit failed!\n");
        close(fd);
        return  - 1;
    }
    close(fd);
    return 0;
}

int vl_SetParity(int rs232ch, int parity)
{
    int fd = opentty(rs232ch);
    if (fd ==  - 1)
    {
        perror("open serial failed!\n");
        close(fd);
        return  - 1;
    }
    if (set_parity(fd, parity) ==  - 1)
    {
        perror("vl_SetParity failed!\n");
        close(fd);
        return  - 1;
    }
    close(fd);
    return 0;
}

int vl_SetStreamCtrl(int rs232ch, int streamctrl)
{
    int fd = opentty(rs232ch);
    if (fd ==  - 1)
    {
        perror("open serial failed!\n");
        close(fd);
        return  - 1;
    }
    if (set_streamctrl(fd, streamctrl) ==  - 1)
    {
        perror("set_streamctrl failed!\n");
        close(fd);
        return  - 1;
    }
    close(fd);
    return 0;
}
