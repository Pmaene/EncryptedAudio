#include <stdlib.h>
#include <time.h>

#ifdef __MACH__
    #include <mach/clock.h>
    #include <mach/mach.h>
#endif

#include "protocol.h"

#include "sender.h"
#include "receiver.h"

void _handshake();
void _createChannel();

void _getTime(struct timespec *ts);

int main(int argc, char **argv) {
    struct timespec difference;
    struct timespec startTime;
    struct timespec stopTime;

    _getTime(&startTime);

    // Construct
    sender_construct();
    receiver_construct();

    // Handshake
    _handshake();

	// Derivation of the AES- and hashKey
	sender_deriveKey();
    printf("\n");
	receiver_deriveKey();
    printf("\n");

    // Destruct
    sender_destruct();
    receiver_destruct();

    // Execution Time
    _getTime(&stopTime);

    if ((stopTime.tv_nsec-startTime.tv_nsec) < 0) {
        difference.tv_sec = stopTime.tv_sec-startTime.tv_sec-1;
        difference.tv_nsec = 1000000000+stopTime.tv_nsec-startTime.tv_nsec;
    } else {
        difference.tv_sec = stopTime.tv_sec-startTime.tv_sec;
        difference.tv_nsec = stopTime.tv_nsec-startTime.tv_nsec;
    }

    printf("# Execution Time\n");
    printf("%ds %lums\n", difference.tv_sec, difference.tv_nsec/1000000);

    exit(EXIT_SUCCESS);
}

void _handshake() {
    unsigned short i;
    unsigned short j;

    printf("# Key Exchange\n\n");

    // SenderHello
    field_t senderKeyExchangePacket[ENC_KEY_PACKET_CHARS];
    for (j = 0; j < ENC_KEY_PACKET_CHARS; j++)
        senderKeyExchangePacket[j] = 0;
    sender_senderHello(senderKeyExchangePacket);

    printf("-| senderKeyExchangePacket\n");
    for (i = 0; i < ENC_KEY_PACKET_CHARS; i++)
        printf("%x", senderKeyExchangePacket[i]);

    printf("\n\n");

    // ReceiverHello
    field_t receiverKeyExchangePacket[ENC_KEY_PACKET_CHARS];
    for (j = 0; j < ENC_KEY_PACKET_CHARS; j++)
        receiverKeyExchangePacket[j] = 0;
    receiver_receiverHello(receiverKeyExchangePacket, senderKeyExchangePacket);

    printf("-| receiverKeyExchangePacket\n");
    for (i = 0; i < ENC_KEY_PACKET_CHARS; i++)
        printf("%x", receiverKeyExchangePacket[i]);

    printf("\n\n");

    // SenderAcknowledge
    field_t senderAcknowledgePacket[ENC_KEY_PACKET_CHARS];
    for (j = 0; j < ENC_KEY_PACKET_CHARS; j++)
        senderAcknowledgePacket[j] = 0;
    sender_senderAcknowledge(senderAcknowledgePacket, receiverKeyExchangePacket);

    printf("-| senderAcknowledgePacket\n");
    for (i = 0; i < ENC_KEY_PACKET_CHARS; i++)
        printf("%x", senderAcknowledgePacket[i]);

    printf("\n\n");
}

void _createChannel() {
}

void _getTime(struct timespec *time) {
    #ifdef __MACH__
      clock_serv_t clock;
      mach_timespec_t machTime;
      host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &clock);
      clock_get_time(clock, &machTime);
      mach_port_deallocate(mach_task_self(), clock);
      time->tv_sec = machTime.tv_sec;
      time->tv_nsec = machTime.tv_nsec;
    #else
      clock_gettime(CLOCK_REALTIME, time);
    #endif
}