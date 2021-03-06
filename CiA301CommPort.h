#ifndef CIA301COMMPORT_H
#define CIA301COMMPORT_H


#include <iostream>
#include <bitset>
#include <err.h>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>


#include "candatatypes.h"


#define USE_TIMEOUT 200 //miliseconds timeout


using namespace std;

class CiA301CommPort
{
public:
    CiA301CommPort(int newPortFileDescriptor, uint8_t new_id);

    long ReadSDO(vector<uint8_t> address, int subindex);
    long ReadSDO(const vector<uint8_t> &address);

    long WriteNMT(const vector<uint8_t> &nmtCommand);
    long WritePDO(const vector<uint8_t> &command);

    long FlushBuffer();
    long WriteSDO(const vector<uint8_t> &address, const vector<uint8_t> &value);
private:

    //methods
    long CanOpenToCanBus(const co_msg &input, can_msg &output);
    long CanBusToCanOpen(const can_msg &input, co_msg &output);


    int SendMessage(co_msg input);
    int SendCanMessage(can_msg &input);

    int WaitForReadMessage(co_msg &output, unsigned int canIndex);

#define FIND_RETRY 100
    int ReadCobId(uint16_t expected_cobid, co_msg &output);
    int read_timeout(int fd, can_msg *buf, unsigned int timeout);
    long GetMsg(can_msg &msg);



    //variables
    int portFileDescriptor;
    uint8_t id;

    can_msg send_msg;
    can_msg input;
    vector<can_msg> readBuffer;
    vector<unsigned int> readInbox;

    co_msg SetCanOpenMsg(unsigned short id_co, unsigned short rtr,  vector<uint8_t> coDataFrame);
};


namespace sdo
{

const uint16_t tx0=0x580;
const uint16_t rx0=0x600;

}
namespace pdo
{

const uint16_t tx0=0x180;
const uint16_t rx0=0x200;

}


#endif // CIA301COMMPORT_H
