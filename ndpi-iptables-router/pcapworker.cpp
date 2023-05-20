#include "pcapworker.h"
#include <net/ethernet.h>


PcapWorker::PcapWorker(QObject *parent)
    : QThread(parent)
{
    ndpi_struct = ndpi_init_detection_module(4);
    if (ndpi_struct == nullptr) {
        qDebug() << "ERROR: Could not initialize nDPI library.";
        return;
    }
}
PcapWorker::~PcapWorker() {
    if (ndpi_struct != nullptr)
        ndpi_exit_detection_module(ndpi_struct);
}
void PcapWorker::run() {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    handle = pcap_open_offline(filename.toLocal8Bit().constData(), errbuf);
    if (handle == nullptr) {
        qDebug() << "Couldn't open pcap file" << filename << ": " << errbuf;
        return;
    }

    // Loop over all packets in the pcap file
    struct pcap_pkthdr header;
    const u_char *packet;
    while ((packet = pcap_next(handle, &header)) != nullptr) {
        struct ether_header *eth_header = (struct ether_header *) packet;
        if (ntohs(eth_header->ether_type) != ETHERTYPE_IP) {
            continue;  // Not an IP packet
        }
        struct iphdr *ip_header = (struct iphdr *) (packet + ETHER_HDR_LEN);
        ndpi_flow_struct flow ;
        ndpi_hw_struct *src = nullptr, *dst = nullptr;
        ndpi_protocol protocol = ndpi_detection_process_packet(
            ndpi_struct, &flow, packet, header.len, header.ts.tv_sec);
        char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];

        inet_ntop(AF_INET, &(ip_header->saddr), src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip_header->daddr), dst_ip, INET_ADDRSTRLEN);

        // Combine the source and destination IP addresses, protocol information into a string
        QString info1 = QString("Src IP: %1, Dst IP: %2, Protocol: %3")
                           .arg(src_ip, dst_ip, QString::fromStdString(ndpi_get_proto_name(ndpi_struct, protocol.app_protocol)));

        // Convert the protocol information to a string and emit the signal
        QString info = QString::fromStdString(ndpi_get_proto_name(ndpi_struct, protocol.app_protocol));
        qDebug() << info << " " << info1;
        emit packetInfo(info, src_ip, dst_ip, QString::fromStdString(ndpi_get_proto_name(ndpi_struct, protocol.app_protocol)));

        // Check if the thread should stop
        if (isInterruptionRequested()) {
            break;
        }
    }

    pcap_close(handle);
}
